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

class Toy {

	string label;
	double weight, length, width;
	bool containsBattery;
	char tip;

public:
	Toy(){}
	Toy(string lab, double w, double l, double wi, bool c);
	char get_tip();  //
	double get_weight();  //
	double get_length();  //
	double get_width();   //
	void setContainsBattery(bool);  //
	string get_label();   //
	bool get_containsBattery();  //

	friend ostream & operator<<(ostream &output, Toy &x){
		output << "Toy Label : " << x.get_label() << " # " << x.get_length() << "x" << x.get_width() <<"  "<< x.get_weight()<<" kg ";
		if (!x.get_containsBattery())
			output << "No Battery"<<endl;
		else
			output << "Contains Battery" << endl;

		return output;
	}

};

Toy::Toy(string lab, double w, double l, double wi, bool c){
	label = lab;
	weight = w;
	length = l;
	width = wi;
	containsBattery = c;
	tip = 't';
}
char Toy::get_tip(){ return tip; }
double Toy::get_weight(){ return weight; }
double Toy::get_length(){ return length; }
double Toy::get_width(){ return width; }
string Toy::get_label(){ return label; }  
bool Toy::get_containsBattery(){ return containsBattery; }

void Toy::setContainsBattery(bool x){
	
	containsBattery = x;
}
