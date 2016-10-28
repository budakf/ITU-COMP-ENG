/*
* Student Name: FATÝH BUDAK	
* Student ID : 150130006
* Date:09.10.2015
*/

#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H
#include <stdio.h>
#include "record_book.h"

struct File{
	char *filename;
	FILE *book;
	void open();//
	void print();//
	void close();//
	void insert(book_record *);//
	int search_by_author(char []);//
	int search_Isbn(int Isbn_num);//
	int search_by_booktype(char []);//
	void remove(int Isbn_num);
	void update(int Isbn_num, book_record *);//
};
#endif
