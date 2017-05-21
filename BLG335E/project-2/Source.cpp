#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<map>
#include<cstring>

using namespace std;

class LINE{
	public:
		LINE();
		vector <int>& get_line_number();
		vector <string>& get_sentence();
		vector <string>& get_number();
	private:
		vector <int> line_number;
		vector <string> sentence, number;

};
vector <int>& LINE::get_line_number(){
	return line_number;
}
vector <string>& LINE::get_sentence(){
	return sentence;
}
vector <string>& LINE::get_number(){
	return number;
}
LINE::LINE(){}

///////////////////
ofstream writing("novel.txt", ios::app);
void swap_for_string(string &a, string &b){

	string t = a;
	a = b;
	b = t;
}

void swap(int* a, int* b){
	
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(vector <string>& sentence, vector <string>& number, vector <int>::iterator arr, int low, int high){
	
	int pivot = arr[high];
	int i = (low - 1);
	int temp;
	for (int j = low; j <= high - 1; j++){
		if (arr[j] <= pivot){
			i++;
			swap(&arr[i], &arr[j]);
			swap_for_string(sentence[i], sentence[j]);
			swap_for_string(number[i], number[j]);
		}
	}

	swap(&arr[i + 1], &arr[high]);
	swap_for_string(sentence[i+1], sentence[high]);
	swap_for_string(number[i + 1], number[high]);

	return (i + 1);
}

int partition_3(vector <int>::iterator arr, int low, int high){

	int pivot = arr[high];
	int i = (low - 1);
	int temp;
	for (int j = low; j <= high - 1; j++){
		if (arr[j] <= pivot){
			i++;
			swap(&arr[i], &arr[j]);
		}
	}

	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quick_Sort(vector <string>& sentence, vector <string>& number, vector <int>::iterator arr, int low, int high, int M, int N, int *counter){
	
	(*counter)++;

	if ((*counter) == M){
		cout << arr[N];
	}

	if (low < high){
		int pi = partition(sentence, number, arr, low, high);
		quick_Sort(sentence, number, arr, low, pi - 1, M, N, counter);
		quick_Sort(sentence, number, arr, pi + 1, high, M, N, counter);
	}
}

int random_partition(vector <int>::iterator arr, int p, int r){
	
	srand(255);
	int i = p + rand() % (r - p + 1);
	int temp;
	swap(&arr[r], &arr[i]);
	return partition_3(arr, p, r);
}

void random_quick_sort(vector <int>::iterator arr, int p, int r){
	
	int q;
	if (p<r){
		q = random_partition(arr, p, r);
		random_quick_sort(arr, p, q - 1);
		random_quick_sort(arr, q + 1, r);
	}
}

void assist_operation(vector <string> &temp, string &sentORnum){
	int i = 0;
	int j = 1;
	string x = "";

	while (j<sentORnum.length()){
		if (sentORnum[j] != '_' && sentORnum[j] != '{' && sentORnum[j] != '}'){
			x += sentORnum[j];
		}
		else if (sentORnum[j] == '_' || sentORnum[j] == '}'){
			temp.push_back(x);
			x = "";
		}
		j++;
	}
	//cout << temp[i] << endl;

}

void type_cast_and_call_random_quick_sort(vector <string> &temp_num, vector <int> &temp_sayi){
	
	int i = 0;
	while (i < temp_num.size()){
		temp_sayi.push_back(atoi(temp_num[i++].c_str()));
	}
	vector <int>::iterator arr = temp_sayi.begin();
	random_quick_sort(arr, 0, temp_sayi.size()-1);
}

void mapping_operation(vector <string> temp_sent, vector <string> temp_num, map<int, string> &associative_array, string number, string sentence){
	
	assist_operation(temp_sent,sentence);
	assist_operation(temp_num,number);
	vector <int> temp_sayi;
	int i = 0;
	while (i < temp_num.size()){
		associative_array[atoi(temp_num[i].c_str())] = temp_sent[i];
		i++;
	}
	type_cast_and_call_random_quick_sort(temp_num, temp_sayi);
	int j = 0;
	while (j < i)
		writing << associative_array[temp_sayi[j++]] << " ";

	writing << endl;
}

void quick_Sort_third_part(vector <int>::iterator arr, int low, int high){

	if (low < high){
		int pi = partition_3(arr, low, high);
		quick_Sort_third_part(arr, low, pi - 1);
		quick_Sort_third_part(arr, pi + 1, high);
	}
}

//////////////////

int main(int argc, char * argv[]){

	if (atoi(argv[1])==1){
		ifstream reading("mobydick.txt");
		int M, N;
		M = atoi(argv[2]);
		N = atoi(argv[3]);
		int int_temp;
		int zero = 0;
		int *counter = &zero;
		string string_temp1, string_temp2;
		LINE line;

		while (!reading.eof()){
			reading >> int_temp >> string_temp1 >> string_temp2;
			line.get_line_number().push_back(int_temp);
			line.get_sentence().push_back(string_temp1);
			line.get_number().push_back(string_temp2);
		}

		quick_Sort(line.get_sentence(), line.get_number(), line.get_line_number().begin(), 0, line.get_line_number().size() - 1, M, N, counter);

		int i = 0;
		map<int, string> associative_array;
		vector <string> temp_sent;
		vector <string> temp_num;

		while (i < line.get_number().size() - 1){
			mapping_operation(temp_sent, temp_num, associative_array, line.get_number()[i], line.get_sentence()[i]);
			i++;
		}
	}

	else if (atoi(argv[1]) == 2){
		int int_temp;
		ifstream reading_2("numbers_to_sort.txt");
		ofstream writing_2("numbers.txt");
		int K = atoi(argv[2]);
		vector <int> array;
		for (int i = 0; i < K; i++){
			reading_2 >> int_temp;
			array.push_back(int_temp);
		}
		vector <int>::iterator arr = array.begin();
		quick_Sort_third_part(array.begin(), 0, array.size() - 1);

		for (int i = 0; i < K; i++){
			writing_2 << array[i] << endl;
		}
	}

	return 0;
}
