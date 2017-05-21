/*

Fatih Budak
150130006

*/

#include<iostream>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<cstring>

using namespace std;

class radix_klas{
	private:
		long long int *array;
		long long int *id;
	public:
		~radix_klas();
		radix_klas(int);
		long long int * get_array();
		long long int * get_id();
		void set_array(int, long long int);
		void set_id(int, long long int);
};

radix_klas::~radix_klas(){
	delete [] array;
}

radix_klas::radix_klas(int N){
	array = new long long int [N];
	id = new long long int[N];
}

long long int * radix_klas::get_array(){
	return array;
}

void radix_klas::set_array(int i, long long int number){
	array[i] = number;
}

long long int * radix_klas::get_id(){
	return id;
}

void radix_klas::set_id(int i, long long int number){
	id[i] = number;
}

void countSort(long long int *arr, long long int *id, int n, int number){

	long long  int * output = new long long int[n]; // output array
	long long  int * output_id = new long long int[n]; // output for id
	int i, count[10] = { 0 };

	for (i = 0; i < n; i++)
		count[(arr[i] / number) % 10]++;

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (i = n - 1; i >= 0; i--){
		output[count[(arr[i] / number) % 10] - 1] = arr[i];
		output_id[count[(arr[i] / number) % 10] - 1] = id[i];
		count[(arr[i] / number) % 10]--;
	}

	for (i = 0; i < n; i++){
		arr[i] = output[i];
		id[i] = output_id[i];
	}
		
		
}

void radixsort(long long int *array, long long int *id, int n){
	for (int i = 1; array[0] / i > 0; i *= 10)
		countSort(array, id, n, i);

}

int main(int argc, char **argv){
	
	long long int temp_id, temp_number;
	int i = 0;
	int N =atoi(argv[1]);
	radix_klas rad(N); //
	
	ifstream reading("numbers_to_sort.txt");
	ofstream writing("sorted_numbers.txt");

	while (i < N){ //
		reading >> temp_id >> temp_number;
		rad.set_id(i, temp_id);
		rad.set_array(i, temp_number);
		i++;
	
	}

	clock_t t;
	t = clock();
	radixsort(rad.get_array(), rad.get_id(), N); //
	t = clock() - t;
	cout << "Running Time: " << (double)t/CLOCKS_PER_SEC <<" seconds "<< endl;
	i = 0;
	while (i < N){	//
		writing << rad.get_id()[i] << " " << rad.get_array()[i] << endl;
		i++;
	}
	
}
