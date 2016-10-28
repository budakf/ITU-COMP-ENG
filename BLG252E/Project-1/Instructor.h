/*
Fatih Budak
150130006
Hw1
*/

#include<iostream>
#include<string>
#include<cstring>

using namespace std;

class instructor{
	
		string title;               //as a default private members
		string first_name;			
		string last_name;			
		string phone_num;
		string room_num;
		string user_name;
		string email;
		string t_courses;  //temporary for course
		string *main_courses; 
		int course_num;

		
public:                                // public members
		
		instructor();   // constructor
		instructor(string, string, string, string, string, string, string, string);  //Constructor with parameter
		void set_title(string);
		void set_f_name(string);
		void set_s_name(string);
		void set_p_num(string);
		void set_r_num(string);
		void set_u_name(string); 
		void set_email(string);
		void set_courses(string );

		string get_f_name() const;
		string get_s_name() const;
		string get_title() const;
		string get_p_num() const;
		string get_r_num() const;
		string get_u_name() const;
		string get_email() const;
		string * get_courses();
		int get_c_num();
		
		
		
};

instructor::instructor(){ };  

instructor::instructor(string t, string f_name, string s_name, string p_num, string r_num, string u_name, string e_mail, string c_ourses){

	title = t;
	first_name = f_name;
	last_name = s_name;
	phone_num= p_num;
	room_num = r_num;
	user_name = u_name;
	email = e_mail;
	t_courses = c_ourses;

}
void instructor::set_title(string a){title = a;  }

void instructor::set_f_name(string a){ first_name = a; }

void instructor::set_s_name(string a){ last_name = a; }

void instructor::set_u_name(string a){ user_name = a; }

void instructor::set_p_num(string a){ phone_num = a; }

void instructor::set_r_num(string a){ room_num = a; }

void instructor::set_email(string a){ email = a; }

void instructor::set_courses(string a){ 	//	 Parametre olarak gelen a stringini fonksiyonun sonunda
											//	 main_course'a atýyoruz ve course sayýsýný buluyoruz.
	course_num = 0;  
	main_courses = new string[10];
												
	char *array = new char[a.length() + 1]; 
	int i;

	for (i = 0; i < a.length(); i++){
		array[i] = a[i];
	}
	array[i] = '\0';		//Sonuna NULL karakter ekliyoruz

	char *temmpp = new char[strlen(array) + 1];
	temmpp = strtok(array, " ");          //strtok fonksiyonu boþluk a kadar olan kýsmý temmp e atýyo.
	
	i = 0; 
	while (temmpp){					//Eðer temmp NULL ise while dan çýkýyo

		main_courses[i++]=temmpp;
		course_num++;
		temmpp = strtok(NULL, " ");
		
	}
	

}

string instructor::get_title()const { return title; }

string instructor::get_f_name()const { return first_name; }

string instructor::get_s_name()const { return last_name; }

string instructor::get_u_name()const{ return user_name; }

string instructor::get_p_num()const { return phone_num; }

string instructor::get_r_num()const { return room_num; }

string instructor::get_email()const { return email; };

string * instructor::get_courses() { return main_courses; }

int instructor::get_c_num(){ return course_num; }
