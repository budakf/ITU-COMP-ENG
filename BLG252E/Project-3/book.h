/*
* @Author
* Student Name: Fatih BUDAK
* Student ID : 15013006
* Date: 08.05.2016
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

class Book {

	string label;
	double weight, length, width;
	char tip;

public:
	Book(){}
	Book(string, double, double, double);
	char get_tip();
	double get_weight();  //
	double get_length();  //
	double get_width();   //
	string get_label();   //
	friend ostream & operator<<(ostream &output, Book &x){
		output << "Book Label :" << x.get_label() << " # " << x.get_length() << "x" << x.get_width() << "  " << x.get_weight() << " kg " << endl;
		return output;
	}

};

Book::Book(string lab, double w, double l, double wi) {

	label = lab;
	weight = w;
	length = l;
	width = wi;
	tip = 'b';
}
char Book::get_tip(){ return tip; }
double Book::get_weight(){ return weight; }
double Book::get_length(){ return length; }
double Book::get_width(){ return width; }
string Book::get_label(){ return label; }
