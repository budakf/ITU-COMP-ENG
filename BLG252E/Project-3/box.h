/*
* @Author
* Student Name: Fatih BUDAK
* Student ID : 15013006
* Date: 08.05.2016
*/

#ifndef Box_H           
#define Box_H 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;


template <class Type>
class Box {

	double weight, length, width;
	double maximum_Allowed_Weight;
	Type *array;
	int how_many_elements;
	double total_weight;
	char tip;
	int size;

public:
	Box(){};
	Box(double, double, double, double);
	void add(Type &);
	void add(Type *, int);
	void setContainsBattery(bool);
	Type* get_array();
	char get_tip();
	double get_maximum_Allowed_Weight();//
	double get_weight();  //
	double get_length();  //
	double get_width();   //
	double get_total_weight();  //
	int get_how_many_elements();  //
	void operator=(Box);
	Type& operator[] (int);   //

	friend ostream & operator<<(ostream &output, Box<Type> &x){ //
		
		if (x.get_array()->get_tip() == 't')
			output << endl << "***** Box<Toy> *****" << endl;

		else if (x.get_array()->get_tip() == 'b')
			output << endl << "***** Box<Book> *****" << endl;
		
		else if((x.get_tip() == 'x'))
			output << endl << "***** Box<Box<Toy>> *****" << endl;
		
		else
			output << endl << "***** Box<Toy> *****" << endl;	
		
		output << "Box item count: " << x.get_how_many_elements() << endl;
		output << "Size: " << x.get_length() << "x" << x.get_width() << " Box Weight: " << x.get_weight() << "kg Total/Maximum Allowed Weight: " << x.get_total_weight() << "kg/" << x.get_maximum_Allowed_Weight() << "kg" << endl;
		output << "Items: " << endl;

		for (int i = 0; i < x.get_how_many_elements(); i++){
			output << i + 1 << ":" << x.get_array()[i];
		}
		output << "******************" << endl;
		return output;
	}


	//~Box();
};

template<class Type>
void Box<Type>::operator=(Box<Type> x)       
{                                          
	Type* var = new Type[x.get_how_many_elements()];

	for (int i = 0; i<x.get_how_many_elements(); i++)      
		var[i] = x[i];

	array = var;
	
	length = x.get_length();
	width = x.get_width();
	how_many_elements = x.get_how_many_elements();
	weight = x.get_weight();
	maximum_Allowed_Weight = x.get_maximum_Allowed_Weight();
	total_weight = x.get_total_weight();
	

}


template<class Type>
char Box<Type>::get_tip(){ return tip; }

template<class Type>
Box<Type>::Box(double w, double l, double wi, double max){
	array = NULL;
	weight = w;
	length = l;
	width = wi;
	maximum_Allowed_Weight = max;
	total_weight = w;
	how_many_elements = 0;
	tip = 'x';
	size = 1;
}


template<class Type>
void Box<Type>::add(Type &thing){
	if (array == NULL) array = new Type[size];
	if (total_weight + thing.get_weight() > maximum_Allowed_Weight) throw (const string) "The total weight of the contained objects including the box may not exceed the maximum allowed weight for the box!";
	if ((thing.get_length()>length && thing.get_length()>width) || (thing.get_width()>length  && thing.get_width()>width)) throw  (const string) "The dimensions of the contained object should be equal or smaller than those of the box!";

	total_weight += thing.get_weight();
	array[how_many_elements] = thing;
	how_many_elements++;

	if (how_many_elements == size){
		Type * temp = new Type[size + 1];
		for (int i = 0; i<size; i++)
			temp[i] = array[i];

		delete[] array;
		size *= 2;

		array = new Type[size];

		for (int i = 0; i<how_many_elements; i++)
			array[i] = temp[i];

	}
}

//////////////////////////////////////

template<class Type>
void Box<Type>::add(Type *thing, int x){

	for (int i = 0; i < x; i++)
		this->add(*(thing + i));

}

///////////////////////////////
template<class Type>
Type* Box<Type>::get_array(){ return array; }

template<class Type>
double Box<Type>::get_maximum_Allowed_Weight(){ return maximum_Allowed_Weight; }

template<class Type>
double Box<Type>::get_weight(){ return weight; }

template<class Type>
double Box<Type>::get_length(){ return length; }

template<class Type>
double Box<Type>::get_width(){ return width; }

template<class Type>
double Box<Type>::get_total_weight(){ return total_weight; }

template<class Type>
int Box<Type>::get_how_many_elements(){ return how_many_elements; }

template<class Type>
Type& Box<Type>::operator[] (int x){
	if (x >= how_many_elements) throw (const string) "Index out of bounds!";
	return array[x];

}

#endif
