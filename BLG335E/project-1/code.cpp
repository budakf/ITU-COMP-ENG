/*Fatih Budak
  150130006
  Algo-1 Project1
*/

#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<cmath>

using namespace std;

class warehouse{

private:
	int id;
	int x_axis;
	int y_axis;
	int distance;

public:
	warehouse();
	void set_id(int _id);
	void set_x_axis(int _x_axis);
	void set_y_axis(int _y_axis);
	void set_distance(int _distance);

	int get_id();
	int get_x_axis();
	int get_y_axis();
	int get_distance();

};
warehouse::warehouse(){

}

void warehouse::set_id(int _id){
	id = _id;
}

void warehouse::set_x_axis(int _x_axis){
	x_axis = _x_axis;
}

void warehouse::set_y_axis(int _y_axis){
	y_axis = _y_axis;
}

void warehouse::set_distance(int _distance){
	distance = _distance;
}

int warehouse::get_distance(){
	return distance;
}

int warehouse::get_id(){
	return id;
}

int warehouse::get_x_axis(){
	return x_axis;
}

int warehouse::get_y_axis(){
	return y_axis;
}

void insertion_sort(warehouse warehouse_array[], int N){  //Insertion Sort 
	
	int i, j;
	warehouse temp;

	for (j = 1; j < N; j++){
		temp = warehouse_array[j];

		for (i = j - 1; (i >= 0) && (warehouse_array[i].get_distance() > temp.get_distance()); i--){
			warehouse_array[i + 1] = warehouse_array[i];
		}
		warehouse_array[i + 1] = temp;
	}

}

void merge(warehouse warehouse_array[], int left, int middle, int right){
	int i, j, k=left;
	int n1 = middle - left + 1;
	int n2 = right - middle;
	
	warehouse *Left = new warehouse[n1];
	warehouse *Right = new warehouse[n2];

	for (i = 0; i < n1; i++)
		Left[i] = warehouse_array[left + i];
	for (j = 0; j < n2; j++)
		Right[j] = warehouse_array[middle + 1 + j];

	i = j = 0; 

	while (i < n1 && j < n2){
		if (Left[i].get_distance() <= Right[j].get_distance()){
			warehouse_array[k] = Left[i];
			i++;
		}
		else{
			warehouse_array[k] = Right[j];
			j++;
		}
		k++;
	}

	while (i < n1){
		warehouse_array[k] = Left[i];
		i++;
		k++;
	}

	while (j < n2){
		warehouse_array[k] = Right[j];
		j++;
		k++;
	}

	delete [] Left;
	delete [] Right;
}

void merge_sort(warehouse warehouse_array[], int left, int right){
	if (left < right){
		int middle = left + (right - left) / 2;
		merge_sort(warehouse_array, left, middle);
		merge_sort(warehouse_array, middle + 1, right);
		merge(warehouse_array, left, middle, right);
	}
}

void neww_array(warehouse warehouse_array[], int &N, int index){

	warehouse *neww=new warehouse[N - 1];
	int j = 0;

	for (int i = 0; i < N; i++){
		if (i != index)
			neww[j++] = warehouse_array[i];
	}

	//delete [] warehouse_array;
	N -= 1;
	//warehouse_array = new warehouse[N];

	for (int i = 0; i < N; i++){ 
		warehouse_array[i] = neww[i];
	}

	delete [] neww;
}

int linear_search(warehouse warehouse_array[], int N, int search_key){

	int min[2];
	min[0] = 0;
	min[1] = warehouse_array[0].get_distance() - search_key;

	for (int i = 1; i<N; i++){
		if (warehouse_array[i].get_distance() - search_key < min[1]){
			min[1] = warehouse_array[i].get_distance() - search_key;
			min[0] = i;
		}
	}
	
	return min[0];
}

int main(int argc, char * argv[]){
	
	int temp_id, temp_x_axis, temp_y_axis, temp_distance;	// Dosyadan okuma sýrasýnda kullanýlýrlar

	int N,K;
	string algo_types;
	int x_axis, y_axis;

	N = atoi(argv[1]);										// Konsoldan girilen main fonksiyonun parametrelerini anlamlý deðiþkenlere attýk
	K = atoi(argv[2]);
	algo_types = argv[3];
	x_axis = atoi(argv[4]);;
	y_axis = atoi(argv[5]);;
	
	ifstream reading("warehouselocations.txt",ios::in);		// okunacak ve yazýlacak dosyalar açýldý.
	ofstream writing("output.txt",ios::out);
	warehouse * warehouse_array=new warehouse[N];

	for (int i = 0; i < N; i++){
		reading >> temp_id >> temp_x_axis >> temp_y_axis;
		warehouse_array[i].set_id(temp_id);
		warehouse_array[i].set_x_axis(temp_x_axis);
		warehouse_array[i].set_y_axis(temp_y_axis);
		temp_distance = sqrt( pow(fabs(static_cast<double>(temp_x_axis - x_axis)), 2) + pow(fabs(static_cast<double>(temp_y_axis - y_axis)), 2) ); // fabs() a gerek yok düzelt
		warehouse_array[i].set_distance(temp_distance);
	}

	if (algo_types.compare("IS") == 0){         //Insertion Sort 
		insertion_sort(warehouse_array,N);
		for (int i = 0; i < K; i++){
			writing << warehouse_array[i].get_id() << "	" << warehouse_array[i].get_x_axis() << "	" << warehouse_array[i].get_y_axis() << "	" << warehouse_array[i].get_distance() << endl;
		}	
	}

	else if (algo_types.compare("MS") == 0){    // Merge Sort 
		merge_sort(warehouse_array, 0, N - 1);
		for (int i = 0; i < K; i++){
			writing << warehouse_array[i].get_id() << "	" << warehouse_array[i].get_x_axis() << "	" << warehouse_array[i].get_y_axis() << "	" << warehouse_array[i].get_distance() << endl;
		}
	}

	else if (algo_types.compare("LS") == 0){    // Linear Search
		int a;
		for (int i = 0; i < K; i++){
			a = linear_search(warehouse_array, N, 0);
			writing << warehouse_array[a].get_id() << "	" << warehouse_array[a].get_x_axis() << "	" << warehouse_array[a].get_y_axis() << "	" << warehouse_array[a].get_distance() << endl;
			neww_array(warehouse_array, N, a); 
		}
	}

	else{
		cout << "Wrong choice for algorithms.";
	}
	
	delete [] warehouse_array;

	return 0;
}