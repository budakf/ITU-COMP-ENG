#include<fstream>
#define _CRT_SECURE_NO_WARNINGS
struct node {
	char *data;
	node *next;
};

struct queue{
	int count;
	node * front;
	node * back;
	void create();
	bool isempty();
	void enqueue(char *);
	char * dequeue();
	void file_open();
	void file_close();
};





