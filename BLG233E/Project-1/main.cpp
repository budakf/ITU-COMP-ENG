/*
* Student Name: FATÝH BUDAK	
* Student ID : 150130006
* Date:09.10.2015
*/

#include<iostream>
#include<stdlib.h>
#include<iomanip>
#include<ctype.h>

#include "file_operation.h"

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

using namespace std;
  
void print_menu(); 
bool operation(char);
void insert_record();
void print_catalogue(); 
void search_book_by_author();
void search_book_by_booktype();
void update_record();
void remove_record(); 

typedef File Dosya; 
Dosya file;        

int main(){

	file.open();
	bool end = false;
	char choice;
	while (!end) { 
		print_menu(); 
		cin >> choice;
		end = operation(choice); 
		} 	
	file.close();
	return EXIT_SUCCESS;
}


void print_menu(){ // In this function, be printed only menu.  

	system(CLEAR); 
	cout << endl << endl;
	cout << "Please select the operation to perform and enter the operation code" << endl;
	cout << "(P) Print the whole catalogue,"<< endl;
	cout << "(A) Search the catalogue by author," << endl;
	cout << "(T) Search the catalogue by book type," << endl;
	cout << "(I) Insert a new book record," << endl;
	cout << "(U) Update an existing book record," << endl;	
	cout << "(R) Remove a book record," << endl;
	cout << "(E) Exit the program," << endl;
	cout << endl;
	cout << "Your selection is: ";	
}

bool operation(char choice){ // In this function, by using switch case, be considered user's choice and according to choice, be made operation such as deletion, update  

	bool exit = false;

	switch (choice) { 
		case 'P' : case 'p' :
			print_catalogue();
			break;
	
		case 'A' : case 'a' :
			search_book_by_author();
			break;

		case 'T' : case 't' :
			search_book_by_booktype();
			break;

		case 'I' : case 'i' :
			insert_record();
			break;

		case 'U' : case 'u' :
			update_record();
			break;

		case 'R' : case 'r' :
			remove_record();
			break;

		case 'E' : case 'e' :
			cout << "Are you sure you want to exit the program? (Y/N):";
			cin >> choice;
			if(choice=='Y' || choice=='y')
				exit=true;
			break;

		default :
			cout << "Error: You have entered an invalid choice" << endl; 
			cout << "Please try again :" ;
			cin >> choice;
			exit=operation(choice);
			break;
	
	}

	return exit;

}
 
void insert_record(){
	book_record var;

	cout<< "Name: ";
	cin.ignore(1000,'\n');
	cin.getline(var.authorName,NAME_LENGTH);

	cout<< "Surname: ";
	cin.getline(var.authorSurname,NAME_LENGTH); 

	cout<< "Book Title: ";
	cin.getline(var.title,NAME_LENGTH);

	cout<< "Book Type: ";
	cin.getline(var.bookType,TYPE_LENGTH);
	  
	cout<< "ISBN: ";
	cin >> var.ISBN ;
	while(file.search_Isbn(var.ISBN)>0){
		cout<<"****The ISBN number is already exist, so try again****"<<endl;
		cout<< "ISBN: ";
		cin >> var.ISBN ;
	}

	cout<< "Location: "; 
	cin >> var.location ;
	while(var.location>9999){
		cout<<"****Location cannot be greater than 9999 try again****"<<endl;
		cout<< "Location: ";
		cin >> var.location ;
	}

	file.insert(&var);
	cout << "****Record added****" << endl; 
	getchar();
	getchar();
}

void print_catalogue(){ //Thanks to this function, all records are printed in screen. 
	file.print();
	getchar();
}

void search_book_by_author(){ 
	char name[NAME_LENGTH];
	cout << "Please enter the authorname that you want to search: ";
	cin.ignore(1000,'\n');
	cin.getline(name,NAME_LENGTH);
	int found=file.search_by_author(name);
	if(found==0)
		cout << " Could not find a record matching your search criteria ";
	else
		cout<< "****Record(s) is/are found****";
	getchar();
} 
 
void search_book_by_booktype(){ 
	char type[NAME_LENGTH];
	cout << "Please enter the book type that you want to search: ";
	cin.ignore(1000,'\n');
	cin.getline(type,NAME_LENGTH);
	int found=file.search_by_booktype(type);
	if(found==0)
		cout << " Could not find a record matching your search criteria ";
	else
		cout<< "****Record(s) is/are found****";
	getchar();

}

void update_record(){
	book_record neww;
	int Isbn; 
	cout << "Please enter the ISBN of the record: ";
	cin >> Isbn;

	int index=file.search_Isbn(Isbn);

	if (index!=0){
		cout << "Name: ";
		cin.ignore(1000,'\n');
		cin.getline(neww.authorName,NAME_LENGTH);

		cout << "Surname: ";
		cin.getline(neww.authorSurname,NAME_LENGTH);
		 
		cout<< "Book Title: ";
		cin.getline(neww.title,NAME_LENGTH); 

		cout<< "Book Type: ";
		cin.getline(neww.bookType,TYPE_LENGTH);

		cout<< "ISBN: ";
		cin >> neww.ISBN ;

		cout<< "Location: ";
		cin >> neww.location ;
		file.update(index, &neww);
    }
	 
	else
		cout << "****Could not update the record****";

	getchar();
	getchar();

}

void remove_record(){
	FILE *ptr;
	book_record temp;
	int Isbn;
	cout << "Please enter the ISBN of the record: ";
	cin >> Isbn;
	
	int index=file.search_Isbn(Isbn);
	if (index!=0){
		file.remove(index); 
		ptr=fopen("temporary.txt","w+"); 
		if(ptr){ 
			fseek(file.book,0,SEEK_SET); 
			fseek(ptr,0,SEEK_END);
			fread(&temp,sizeof(book_record),1,file.book);
			while(!(feof(file.book))){
				if(temp.authorName[0]=='\0'){
					fread(&temp,sizeof(book_record),1,file.book);
					continue;
				}
				fwrite(&temp,sizeof(book_record),1,ptr);
				fread(&temp,sizeof(book_record),1,file.book); 
			} 
			
		}
		file.close();
		fopen("Library.txt","w+");
		 
		fseek(file.book,0,SEEK_SET);
		fseek(ptr,0,SEEK_SET);
		fread(&temp,sizeof(book_record),1,ptr);
		while(!(feof(ptr))){
			fwrite(&temp,sizeof(book_record),1,file.book);
			fread(&temp,sizeof(book_record),1,ptr);
		}
		
		fclose(ptr);
	} 

	else
		cout << "****Could not remove the record because it cannot be found the record that you want to remove****";

	getchar();
	getchar(); 
}
