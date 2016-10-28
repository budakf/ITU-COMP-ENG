#include<iostream>
#include<cstring>
#include"queue.h"
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

void queue::create(){
	front = NULL;
	back = NULL;
	count = 0;
}

bool queue::isempty(){
	return (front == NULL);
}

void queue::enqueue(char *data){

	node *neww = new node;
	neww->data = new char[strlen(data) + 1];
	//neww->data=data;
	strcpy(neww->data,data);
	
	if (!front){
		front = neww;
		back = front;
		count++;
	}

	else{
		back->next = neww;
		back = neww;
		count++;
	}

}

char *queue::dequeue(){

	char *temp;
	node *p = new node;
	p = front;

	if (front->next == NULL){
		front == NULL;
	}

	else{
		front = front->next;
	}

	int x = strlen(p->data)+1;
    temp = new char[x];
	strcpy(temp, p->data);
	delete p;
	count--;
	
	return temp;

}	



