/*
* Student Name: FATÝH BUDAK	
* Student ID : 150130006
* Date:09.10.2015
*/

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include "file_operation.h"

using namespace std;


void File::open(){ // this function open the file whose name is Library.txt.
	filename =new char[12];
	strcpy(filename,"Library.txt");
	if((book=fopen(filename,"r+"))==0)
		if( (book=fopen(filename,"w+"))==0){
			cerr << "Cannot open file" << endl;
			exit(1);
		}
}

void File::close(){ // this function close the file.
	fclose(book);
}

void File::insert(book_record *addptr){  // Through the function, user insert the record that want to save 
	fseek(book,0,SEEK_END);
	fwrite(addptr,sizeof(book_record),1,book);
}

int File::search_by_author(char *author_name){ // This function is used to make search, according to author name. 
	book_record a;
	int index=0;
	int found=0;
	fseek(book,0,SEEK_SET);
	fread(&a,sizeof(book_record),1,book);

	//cout  << "       Name       " << "     Surname     "  << "   Book Title    "  << "Book Type " << "  " << "ISBN" << "  " << "Location" <<endl ;
	while(!feof(book)){
		if(strncasecmp(a.authorName,author_name,sizeof(a.authorName))==0){
			index++;
			cout << "  name:" << a.authorName << "  surname:" << a.authorSurname << "  title:"  << a.title << "  booktype:"  << a.bookType << "  ISBN:" << a.ISBN  << "  location:" << setfill ('0') << setw (4) << a.location <<endl;
			found++;
		}
		fread(&a,sizeof(book_record),1,book);
	}
	return found;
}

int File::search_by_booktype(char type[20]){ // This function make search, according to type of book
	book_record a;
	int found=0;
	fseek(book,0,SEEK_SET);
	fread(&a,sizeof(book_record),1,book);

	//cout  << "       Name       " << "     Surname     "  << "   Book Title    "  << "Book Type " << "  " << "ISBN" << "  " << "Location" <<endl ;
	while(!feof(book)){
		if(strncasecmp(a.bookType,type,sizeof(a.bookType))==0){
			found++;
			cout << "  name:" << a.authorName << "  surname:" << a.authorSurname << "  title:"  << a.title << "  booktype:"  << a.bookType << "  ISBN:" << a.ISBN << "  location:" << setfill ('0') << setw (4) << a.location <<endl;	
		}
	fread(&a,sizeof(book_record),1,book);
	}
	
	return found;
}

int File::search_Isbn(int Isbn_num){ // This function make search, according to ISBN number because program asks ISBN, in update and remove operations.
	book_record var;
	int index=0;
	fseek(book,0,SEEK_SET);
	fread(&var,sizeof(book_record),1,book);

	while(!feof(book)){
		index++;
		if(var.ISBN==Isbn_num){
			return index;
		}
			
	fread(&var,sizeof(book_record),1,book);
	}
	return 0;
}


///////////////////////////////////////////////////////////////////////

void File::remove(int index){ // this function make blank record that user wants to delete.
	if(index!=0){
		book_record a={"","","",0,0,""};
		if(fseek(book,sizeof(book_record)*(index-1),SEEK_SET)==0)
			fwrite(&a,sizeof(book_record),1,book);
		cout << "****The record that you want to remove is removed****";
	}

}

void File::update(int index, book_record *a){ 
	if(fseek(book,sizeof(book_record)*(index-1),SEEK_SET)==0)
		fwrite(a,sizeof(book_record),1,book);
	cout << "****The record that you want to update is updated****";

}
 
void File::print(){
	book_record var;
	int index=0;
	fseek(book,0,SEEK_SET);
	fread(&var,sizeof(book_record),1,book);

//	cout  << "       Name       "<< "     Surname     "  << "   Book Title    "  << "Book Type " << "  " << "ISBN" << "  " << "Location" <<endl ;
	while(!feof(book)){
		index++;
		cout << "  name:"<< var.authorName << "  surname:" << var.authorSurname << "  title:"  << var.title << "  booktype:"  << var.bookType  << "  ISBN:" << var.ISBN << "  location:" << setfill ('0') << setw (4) << var.location <<endl;
		fread(&var,sizeof(book_record),1,book);	
	}
	if(index==0)
		cout << "****There is no record****";

	getchar();
}
