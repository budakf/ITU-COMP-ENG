/*
* Student Name: FATÝH BUDAK	
* Student ID : 150130006
* Date:09.10.2015
*/

#define NAME_LENGTH 20
#define TYPE_LENGTH 10

struct book_record {
	char authorName [20], authorSurname [20], title[20];
	int ISBN, location;
	char bookType[10];
};