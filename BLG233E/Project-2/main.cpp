/*
* Student Name: Fatih Budak
* Student ID : 150130006
* Date: 07/11/2015
*/

#include<iostream>
#include"List.h"
#include<string.h>
#include <fstream>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

List liste;

int main(){
	 
	liste.open_file();
	liste.create();  
	
	cout << "BANKING LIST APPLICATION:" << endl; 

	liste.read_from_file();

	liste.close_file();

	return 0;
}
