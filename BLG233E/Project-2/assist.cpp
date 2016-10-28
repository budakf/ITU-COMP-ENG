/*
* Student Name: Fatih Budak
* Student ID : 150130006
* Date: 07/11/2015
*/

#include<iostream>
#include <fstream>
#include<string>
#include<string.h>
#include"List.h"
#include<ctype.h>
using namespace std;

#define _CRT_SECURE_NO_WARNINGS
char choice;
ofstream outputfile;   // Dosya ya yazma iþlemi için 
ifstream inputfile;

void List::create(){
	 
	head = NULL;
	nodecount=0;
}


void List::open_file(){

	inputfile.open("input_file.txt");
	
	if (inputfile.is_open()) {
		outputfile.open("output_file.txt");
		if (!outputfile.is_open())
			cout << "Output file could not be opened" << endl;
	}
	else
		cout << "Input file could not be found " << endl; 

}


void List::read_from_file(){

	string var;
	bool end = false;

	while (getline(inputfile, var)){
		 
		taken = new char[var.length()+1];
		int i = 0; 

		for (i = 0; var[i] != '\0'; i++)
			taken[i] = var[i];

		taken[i++] = '\n';
		//taken[i] = NULL;

		//cout << taken[0] <<" " ;  // denemek için

		char secim;

		if ((taken[0]<='z' && taken[0]>='a') || (taken[0]<='Z' && taken[0]>='A')){
			choice = taken[0];
			secim = taken[0];
			taken += 2;
		}

		else{
			choice = taken[3];
			secim = taken[3];
			taken += 5;
		} 

		//cout << secim << "    ";

		end = choose_operation(secim);
	
		if (end == true) break;
	}
	
}

bool List::choose_operation(char secim){

	bool sonlandir = false;

	switch (secim){

	case 'A': case 'a':
		add();
		write2file();
		break;

	case 'R': case 'r':
		remove();
		break;

	case 'V': case 'v':
		process();
		write2file();
		break;

	case 'P': case 'p':
		write2file();
		break;

	case 'S': case 's':
		search(); 
		break;

	case 'E': case 'e':
		sonlandir = true;
		write2file();
		break;

	}
	// cout << liste.head->transaction_ptr->transaction_name; // Denemek için..
	return sonlandir;

}


customer * List::customer_create(){  

	customer *neww;
	transaction *yeni;
	transaction *yeni_2;
	transaction *yeni_3;
	yeni_2 = new transaction;
	yeni_3 = new transaction;
	neww = new customer;
	yeni = new transaction;
	neww->next = NULL;
	yeni->next = NULL;
	yeni_2->next = NULL;
	yeni_3->next = NULL;

	int i=0;

	neww->transaction_ptr = yeni;
	
	//taken += 5; // taken artýk name in ilk harfini gösteriyor..

	for (i = 0; taken[i] !=';'; i++)
		neww->name[i] = taken[i];

	neww->name[i] = '\0';
	taken += i + 1;
	
	for (i = 0; taken[i] !=';'; i++)
		neww->surname[i] = taken[i]; 

	neww->surname[i] = '\0';
	taken += i + 1;

	neww->customer_type = taken[0];
	neww->number_of_transaction = taken[2];

	taken += 4; // taken artýk transaction'larýn birincisinin ilk harfini gösteriyor..

	//int count = 0;
	for (i = 0; taken[i] != '\n' && taken[i] != ';'; i++){

			yeni->transaction_name[i] = taken[i];
	}

	yeni->transaction_name[i] = '\0';

	if (taken[i] == ';'){ 
		yeni->transaction_name[i] = '\0';  
		yeni->next = yeni_2;
		yeni_2->next = NULL;
		taken += strlen(yeni->transaction_name)+1;

		for (i = 0; taken[i] != '\n' && taken[i] != ';'; i++){
			if (taken[i] != ';')
				yeni_2->transaction_name[i] = taken[i];
		}

		yeni_2->transaction_name[i] = '\0';
	}
		
	if (taken[i] == ';'){
		yeni_2->transaction_name[i] = '\0';
		yeni_2->next = yeni_3;
		yeni_3->next = NULL;
		taken += strlen(yeni_2->transaction_name)+1;

		for (i = 0; taken[i] != '\n' && taken[i] != ';'; i++){
			
				yeni_3->transaction_name[i] = taken[i];
		}
		yeni_3->transaction_name[i] = '\0';

	}


	return neww;
}


void List::add(){

	customer *behind;
	customer *traverse=head;
	customer *neww;
	neww = new customer;
	neww = customer_create();
	
	if (head == NULL){
		head = neww; 
		head->next = NULL;
		nodecount++;
		return;
		
	}

	else {  // head NULL deðilse ...

		if (neww->customer_type > traverse->customer_type){ 

			head = neww;
			head->next = traverse;
			nodecount++;
			return;
		}

		while (traverse && neww->customer_type <= traverse->customer_type){
			behind = traverse;
			traverse = traverse->next;

		}

		if (!traverse){

			behind->next = neww;
		}
		else{
			behind->next = neww;
			neww->next = traverse;
		}

	}

}

void List::search(){

	int i;
	char isim[15], soyisim[15];

	for (i = 0; taken[i] != ';'; i++){
		isim[i] = taken[i]; 
	}
	if (i != 15)
		isim[i] = '\0'; 
	taken += i+1;
	

	for (i = 0; taken[i] != '\n'; i++){
		soyisim[i] = taken[i];
	}
	if (i != 15)
		soyisim[i] = '\0';
	taken += i+1;

	customer *ptr=head;

	while (ptr){

		if (strcmp(ptr->name, isim) == 0 && strcmp(ptr->surname, soyisim) == 0){
			
			outputfile << isim << "  " << soyisim << "  could be found " << endl << endl;
			return;
		}
		ptr = ptr->next;
	}
	
	outputfile << isim << "  " << soyisim << "  could not be found " << endl << endl;

	return;
}

void List::remove(){

	int i;
	char isim[15], soyisim[15], musteri_tipi;

	for (i = 0; taken[i] != ';'; i++){
		isim[i] = taken[i];
	}
	if (i != 15)
		isim[i] = '\0';
	taken += i + 1;


	for (i = 0; taken[i] != ';'; i++){
		soyisim[i] = taken[i];
	}
	if (i != 15)
		soyisim[i] = '\0';
	taken += i + 1;
	 
	musteri_tipi = taken[0]; 
	customer *traverse, *behind=NULL;
	traverse = head;

	while (traverse){

		if (strcmp(traverse->name, isim) == 0 && strcmp(traverse->surname, soyisim) == 0 && (musteri_tipi==traverse->customer_type) ){

			if (!behind){
				head = head->next;
				delete [] traverse;
				outputfile << isim <<"  " << soyisim << " is removed."<<endl<<endl;
				return;
			}

			else if (behind){
				behind->next = traverse->next;
				delete[] traverse;
				outputfile << isim << "  " << soyisim << " is removed." << endl << endl;
				return;
			}

		}

		behind = traverse;
		traverse = traverse->next;
	}

	outputfile << isim << "  " << soyisim << " is not found to remove" << endl << endl;

}

void List::process(){

	customer *traverse=head;
	customer *Temp = head;
	customer *behind;
	transaction *a=traverse->transaction_ptr;
	transaction *b;
	if (traverse->customer_type == 'N'){
		while (traverse->transaction_ptr){
			b = traverse->transaction_ptr;
			traverse->transaction_ptr = traverse->transaction_ptr->next;
			delete [] b;
		}
		head = traverse->next;
		delete [] traverse;
	}

	else if (traverse->customer_type == 'P'){
		transaction *temp = traverse->transaction_ptr;
		
		if (traverse->transaction_ptr->next != NULL){
			a=a->next;
			traverse->transaction_ptr = a;
			delete [] temp;

			while ( Temp->customer_type == traverse->customer_type ){
				behind = traverse;
				traverse = traverse->next;
				if (traverse == NULL)	break;

			}
			
			if (!traverse ){
				behind->next = Temp;
				head = head->next;
				Temp->next = NULL;
			}

			else{
				behind->next = Temp;
				head = head->next;
				Temp->next = traverse;

			}

		}

		else if (traverse->transaction_ptr->next == NULL){
			head = traverse->next;
			delete [] traverse;
		}


	}




}


void List::write2file(){
	  
	customer *ptr = head;
	switch (choice){
		case 'A': case 'a':
			outputfile << "New customer is added.\n\n";
			break;
			 
		case 'V': case 'v':
			outputfile << "Next transaction is processed.\n\n";
			break; 
			 
		case 'P': case 'p':
			
			while (ptr){
				outputfile << ptr->name << " " << ptr->surname << " " << ptr->customer_type << " " << ptr->transaction_ptr->transaction_name;
				if (ptr->transaction_ptr->next){
					outputfile << " " << ptr->transaction_ptr->next->transaction_name;
					if (ptr->transaction_ptr->next->next)
						outputfile << " " << ptr->transaction_ptr->next->next->transaction_name;
				}
				
				outputfile << "\n";
				ptr= ptr->next;
			}
			outputfile << "\n";
			break;

		case 'E': case 'e':
			outputfile << "Program exits.\n";
			break;

	}

}
 

void List::close_file(){
	outputfile.close();
	inputfile.close();
}
