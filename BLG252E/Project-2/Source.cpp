/*
	Fatih Budak
	150130006	
	Hw-2
*/

#include<iostream>
#include<string>
#include<fstream>
#include"Header.h"

using namespace std;

void read_file(string &p){  //this function reads to file 
	ifstream my_file;
	my_file.open("deck.txt");

	string row1, row2;

	if (my_file.is_open()){
		getline(my_file, row1);
		getline(my_file, row2);
	}

	for (unsigned int i = 0; i<row1.length(); i += 2){
		p += row1[i];  
		p += row2[i];
	}
	
}

int main(){
	int i;
	string p;
	read_file(p);   

	cout << "Player1: ";					// 0 2 4 6.. for Player1  in p string
	for (i = 0; i < p.length(); i+=2)
		cout << p[i]<<" ";

	cout <<endl << "Player2: ";				//	 1 3 5 7.. for Player2  in p string
	for (i = 1; i < p.length(); i += 2)
		cout << p[i] << " ";

	cout << endl;

	list Liste;
	
	Red r;
	Green g;
	Blue b;
	Darkred d;
	
	for (i = 0; i < p.length(); i++){
		
		if (p[i]=='R')
			Liste.insert(r);
		
		else if (p[i] == 'D')
			Liste.insert(d);

		else if (p[i] == 'G')
			Liste.insert(g);

		else if (p[i] == 'B')
			Liste.insert(b);
	}

	Liste.compare_list_elements();
	
	return 0;
}
