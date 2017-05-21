#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<climits>

using namespace std;

void create_graph(int **graph, string * rev_str, int num_rev, int * rev_int, string * pub_str, int num_pub){

	int i, j;
	i = j = 0;
	while (i < num_rev){    // source ile reviewer arasındaki edgeleri ekledik
		graph[0][i + 1] = rev_int[i++];
	}

	i = num_rev + 1;
	//cout << i << "   " << num_rev + num_pub + 1;
	while (i < num_rev + num_pub + 1){               // sink ile publicaiton arasındaki edgeleri ekledik
		if (pub_str[j++][0] == 'C')
			graph[i][num_rev + num_pub + 1] = 3;
		else
			graph[i][num_rev + num_pub + 1] = 2;
		i++;
	}

	i = 0;
	while (i < num_rev){          // reviewer'lar ile publication'lar arasındaki edgeleri ekledik
		j = num_rev + 1;
		if (rev_str[i].length() == 5){							// For Prof
			//cout << rev_str[i] << endl;
			while (j < num_rev + num_pub + 1)
				graph[i + 1][j++] = 1;
		}

		else if (rev_str[i].length() == 8){						// For Assist Prof
			//cout << rev_str[i] << endl;
			for (int k = 0; k < num_pub; k++){
				if (pub_str[k][0] != 'J')
					graph[i + 1][j] = 1;
				j++;
			}
		}
		else{												// For Assistant
			//cout << rev_str[i] << endl;
			for (int k = 0; k < num_pub; k++){
				if (pub_str[k][0] == 'W')
					graph[i + 1][j] = 1;
				j++;
			}
		}
		i++;
	}

}


int FordFulkerson(int **graph, bool * visited, int **flow, int s, int t, int number, int size){

	visited[s] = true;
	int capacity,i;
	i = 0;
	if (s == t)
		return number;

	while (i++ < size){
		capacity = graph[s][i] - flow[s][i];
		if (capacity > 0 && visited[i] == false){
			int return_value = FordFulkerson(graph, visited, flow, i, t, number < capacity ? number : capacity, size);
			if (return_value != 0){
				flow[s][i] += return_value;
				flow[i][s] -= return_value;
				return return_value;
			}
		}
	}

	return 0;
}


int main(int argc, char**argv){

	string * rev_str;
	int    * rev_int;
	string * pub_str;
	int i, num_p, num_r, max_flow;
	i = max_flow = 0;
	ifstream rev(argv[1]);       //     argv[1]  "reviewer.txt"
	ifstream pub(argv[2]);   //   argv[2]      "publications.txt"
	ofstream output("output.txt");
	pub >> num_p;
	rev >> num_r;

	rev_str = new string[num_r];
	rev_int = new int[num_r];
	pub_str = new string[num_p];

	int **graph = new int *[num_p + num_r + 2];
	for (int i = 0; i < num_p + num_r + 2; ++i)
		graph[i] = new int[num_p + num_r + 2];

	for (int i = 0; i < num_p + num_r + 2; i++)
	for (int k = 0; k < num_p + num_r + 2; k++)
		graph[i][k] = 0;

	int **flow = new int *[num_p + num_r + 2];  // For flow network
	for (int i = 0; i < num_p + num_r + 2; ++i)
		flow[i] = new int[num_p + num_r + 2];

	for (int i = 0; i < num_p + num_r + 2; i++)
	for (int k = 0; k < num_p + num_r + 2; k++)
		flow[i][k] = 0;

	bool * visited = new bool[num_p + num_r + 2];   // for  visited array
	for (int i = 0; i < num_p + num_r + 2; i++)
		visited[i] = false;

	while (!rev.eof()){
		rev >> rev_str[i];
		rev >> rev_int[i];
		i++;
	}
	i = 0;
	while (!pub.eof()){
		pub >> pub_str[i];
		i++;
	}

	create_graph(graph, rev_str, num_r, rev_int, pub_str, num_p);

	/*cout << "My Graph:" << endl;
	for (int i = 0; i < num_p + num_r + 2; i++){
		for (int k = 0; k < num_p + num_r + 2; k++)
			cout << graph[i][k] << " ";
		cout << endl;
	}*/

	while (int x = FordFulkerson(graph, visited, flow, 0, (num_p + num_r + 1), INT_MAX, (num_p + num_r + 2))){
		max_flow += x;
		for (int i = 0; i < num_p + num_r + 2; i++)
			visited[i] = false;
	}

	//cout << endl << "Maximum Flow:" << endl << max_flow << endl;

	/*cout << endl << "My Flow:" << endl;
	for (int i = 0; i < num_p + num_r + 2; i++){
		for (int k = 0; k < num_p + num_r + 2; k++)
			cout << abs(flow[i][k]) << " ";
		cout << endl;
	}*/

	int k;
	int sayac;
	for (int i = num_r + 1; i < num_p + num_r + 1; i++){
		if (i != num_r + 1)
			output << endl << pub_str[i - (num_r + 1)];
		else
			output << pub_str[i - (num_r + 1)];

		sayac = 0;
		for (int j = 1; j < num_p + 1; j++){
			if (abs(flow[i][j]) == 1){
				sayac++;
				if (sayac == 1)
					output << " is assigned to: " << rev_str[j - 1] << ", ";
				else if (sayac > 1 && pub_str[i - (num_r + 1)][0] != 'C')
					output << rev_str[j - 1] << ".";
				else if (sayac ==2 && pub_str[i - (num_r + 1)][0] == 'C')
					output << rev_str[j - 1] << ", ";
				else if (sayac == 3 && pub_str[i - (num_r + 1)][0] == 'C')
					output << rev_str[j - 1] << ".";

			}
		}
		if (sayac == 0)
			output << " is NOT assigned";
	}

	output << endl;
	//getchar();

}