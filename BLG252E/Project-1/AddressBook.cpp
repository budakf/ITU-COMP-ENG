/*
Fatih Budak
150130006
Hw1
*/

#include<iostream>
#include<string>
#include<cstring>
#include"Instructorlist.h"

using namespace std;

class addressbook{
	
	public:
		instructor_list List;
		addressbook(); // constructor
		bool operations();					// Kullanýcýdan bilgi aldýðýmýz fonksiyonlar
		void print_operations();
		void add_new_instructor();
		void list_instructors();
		void delete_instructor();
		void search_by_name();
		void search_by_surname();
		void search_by_phonenum();
		void search_by_roomnum();
				

};

addressbook::addressbook(){ //Default values are recorded with Constructor
	List.add_inst("Assist. Prof. Dr.", "Gulsen", "Eryigit", "1234", "3303", "gulsenc", "gulsenc@itu.edu.tr", "BLG123 BLG456 BLG789");
	List.add_inst("Assist. Prof. Dr.", "Sanem", "Kabadayi", "2994", "3311", "kabadayi", "kabadayi@itu.edu.tr", "BLG456 BLG321 BLG357");
	List.add_inst("Assist. Prof. Dr.", "Hatice", "Kose", "2901", "3315", "kose", "kose@itu.edu.tr", "BLG357 BLG789 BLG246");
}


int main(){

	int first = 0;
	addressbook adres;
	adres.print_operations();
	bool x=adres.operations();
		

	return 0;
}

void addressbook::print_operations( ){
	
	cout<<"1. Add a new instructor"<<endl;
	cout<<"2. Delete an instructor"<<endl;
	cout<<"3. List all instructors"<<endl;
	cout<<"4. Search by Name"<<endl;
	cout<<"5. Search by Surname"<<endl;
	cout<<"6. Search by Telephone Number"<<endl;
	cout<<"7. Search by Room Number"<<endl;
	cout<<"8. Exit"<<endl<<endl;
		
	
}

bool addressbook::operations(){
	
	bool var=false;
	string x="Y";
	char cho; // for choice

	while (x == "Y" || x == "y"){
		cout <<endl << "Enter the number for operation you want to perform :" << endl;
		cin >> cho;

		switch (cho){

		case '1':
			this->add_new_instructor();  // add new instructor
			break;

		case '2':
			this->delete_instructor();	// delete instructor 
			break;

		case '3':
			this->list_instructors();  //print list of instructor 
			break;

		case '4':
			this->search_by_name();		//search by name
			break;

		case '5':
			this->search_by_surname(); //search by surname 
			break;

		case '6':
			this->search_by_phonenum(); //search by phone number 
			break;

		case '7':
			this->search_by_roomnum(); //search by room number
			break;

		case '8':
			var = true;
			cout << "Exit Program" << endl;

			if (var)
				return var;
			break;

		default:

			cout << "Invalid Input" << endl;
			break;

		}
		
		cout << "Do you want to perform another operation?(Y/N)";
		cin >> x;

		while (x != "Y" && x != "y" && x != "N" && x != "n"){

			if (x == "Y" || x == "y")
				this->print_operations();

			else if (x == "N" || x == "n")
				return var;

			else{
				cout << "Do you want to perform another operation?(Y/N)";
				cin >> x;
			}

		}

		if (x == "Y" || x == "y")
			this->print_operations();

	}
	
	return var;
	
}

void addressbook::add_new_instructor(){
	
	string title, first_name, last_name, phone_num, room_num, user_name, email, courses; 

	cout << "Enter the Title:" << endl;
	cin.ignore(1000, '\n');
	getline(cin, title);

	cout << "Enter the First Name:" << endl;
	getline(cin,first_name);

	cout<<"Enter the Last Name:"<<endl;
	getline(cin, last_name);

	cout<<"Enter the Telephone Number:"<<endl;
	getline(cin,phone_num);

	cout<<"Enter the Room Number:"<<endl;
	getline(cin,room_num);

	cout<<"Enter the User Name:"<<endl;
	getline(cin,user_name);

	email = user_name + "@itu.edu.tr";

	cout<<"Enter the Courses:"<<endl;                                           
	getline(cin,courses); 

	List.add_inst(title, first_name, last_name, phone_num, room_num, user_name, email, courses);	// Fonksiyona gönderiyoruz
	
}

void addressbook::list_instructors(){

	List.list_inst();
}

void addressbook::delete_instructor(){
	
	string name, surname;
	
	cout << "Enter the First Name:" << endl;
	cin.ignore(1000, '\n');
	getline(cin, name);

	cout << "Enter the Last Name:" << endl;
	getline(cin, surname);

	List.delete_inst(name,surname); // Fonksiyona gönderiyoruz

}

void addressbook::search_by_name(){

	string first_name;

	cout << "Enter the First Name:" << endl;
	cin.ignore(1000, '\n');
	getline(cin, first_name);

	List.search_name_inst(first_name); // Fonksiyona gönderiyoruz
	
}

void addressbook::search_by_surname(){
	
	string sur_name;

	cout << "Enter the SurName:" << endl;
	cin.ignore(1000, '\n');
	getline(cin, sur_name);

	List.search_surname_inst(sur_name); // Fonksiyona gönderiyoruz


}

void addressbook::search_by_phonenum(){

	string phone;

	cout << "Enter the Phone Number:" << endl;
	cin.ignore(1000, '\n');
	getline(cin,phone);

	List.search_phonenum_inst(phone); // Fonksiyona gönderiyoruz

}

void addressbook::search_by_roomnum(){

	string room;

	cout << "Enter the Room Number:" << endl;
	cin.ignore(1000, '\n');
	getline(cin, room);

	List.search_roomnum_inst(room); // Fonksiyona gönderiyoruz

}
