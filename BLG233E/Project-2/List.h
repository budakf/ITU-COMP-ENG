/*
* Student Name: Fatih Budak
* Student ID : 150130006
* Date: 07/11/2015
*/

#ifndef LIST_H
#define LIST_H

#include"kayit.h"

struct List{

	void create();
	customer * customer_create();
	void add(); //
	void process(); 
	void search(); //
	void remove(); //

	customer *head;
	customer *head_n;
	int nodecount;

	void open_file(); //
	void close_file(); //
	void read_from_file(); //
	void write2file(); // 
	char *taken; // dosyadan alýnan buna atýlýyor.. 
	bool choose_operation(char secim); //

};
#endif

