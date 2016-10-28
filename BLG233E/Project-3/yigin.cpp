#include<iostream>
#include<cstring>
#include"stack.h"

using namespace std;

void stack::create(){
	head == NULL;
	sayac = 0;
}

bool stack::isempty(){
	return head == NULL;
}

void stack::push(char *var){
	Node *neww = new Node;
	neww->data = new char[strlen(var)+1];
	strcpy(neww->data, var);
	neww->next == NULL;

	if (head == NULL)
		head = neww;

	else{
		neww->next = head;
		head = neww;
	}

	sayac++;
	
}

char * stack::pop(){
	char *var;
	Node *temp;
	temp = head;

	if (head->next==NULL)
		head = NULL;
		

	else
		head = head->next;

	var = new char[strlen(temp->data) + 1];
	strcpy(var, temp->data);
	delete temp;
	sayac--;
	return var;
}
