/*
Fatih Budak
150130006
Hw1
*/
#include<cstring>
#include"Instructor.h"
class instructor_list{
	
	public:
		instructor * inst_list;
		int how_many;     // in list, how many member
		int size;			//size of list
		instructor_list();   //constructor
		void add_inst(string, string, string, string, string, string, string, string);
		void list_inst();
		void delete_inst(string, string);
		void search_name_inst(string);
		void search_surname_inst(string);
		void search_phonenum_inst(string);
		void search_roomnum_inst(string);
		~instructor_list();  //destructor
		
	
};   

instructor_list::~instructor_list(){
	delete [] inst_list;
}

instructor_list::instructor_list(){ //constructor
	size = 2; 
	how_many = 0;
	inst_list = new instructor[size];
}

void instructor_list::add_inst(string t, string f, string l, string p, string r, string u, string e, string c){
	
	bool is_duplicate = true;
	for (int i = 0; i < how_many; i++){ //Duplicate olup olmadýðýna bakýyoruz
		if (strcmp(inst_list[i].get_f_name().c_str(), f.c_str()) == 0 && strcmp(inst_list[i].get_s_name().c_str(), l.c_str()) == 0)
			is_duplicate = false;
	}

	if (is_duplicate){

		instructor neww;
		neww.set_title(t);   // deðerleri setter  fonksiyonlara yolladýk
		neww.set_f_name(f);
		neww.set_s_name(l);
		neww.set_p_num(p);
		neww.set_r_num(r);
		neww.set_u_name(u);
		neww.set_email(e);
		neww.set_courses(c);

		if (how_many >= size){

			instructor * temp = new instructor[size + 1];

			for (int i = 0; i <= size - 1; i++){
				temp[i] = inst_list[i];
			}

			delete[] inst_list;

			inst_list = new instructor[size * 2];

			for (int i = 0; i <= size - 1; i++){
				inst_list[i] = temp[i];
			}

			size *= 2;
		}

		
		how_many++;
		inst_list[how_many - 1] = neww;  //
		
		if (how_many>3)
			cout << "New Instructor has been added" << endl;
		
	}

	else{
		cout << "!!Duplicate!!"<<endl;
	}
}

void instructor_list::list_inst(){

	int i = 0;
	cout << "---------- List of all Instructor in Computer Engineering of ITU ---------" << endl << endl;
	
	for (; i <=how_many-1; i++){
		cout << "Title: " << inst_list[i].get_title() << endl;
		cout << "First Name: " << inst_list[i].get_f_name()<< endl;
		cout << "Surname: " << inst_list[i].get_s_name() << endl;
		cout << "Telephone Number: " << inst_list[i].get_p_num() << endl;
		cout << "Room Number: " << inst_list[i].get_r_num() << endl;
		cout << "User Name: " << inst_list[i].get_u_name() << endl;
		cout << "Email: " << inst_list[i].get_email() << endl;
		cout << "Courses: [";

		
		for (int j = 0; j < inst_list[i].get_c_num(); j++){
			
			cout << inst_list[i].get_courses()[j];

			if (j != inst_list[i].get_c_num() - 1)
				cout << ", ";

		
			}

		cout << "]" << endl << endl;
		cout << endl << "---------------------------" << endl;
	}

}

void instructor_list::delete_inst(string f_name, string s_name){

	int i = 0,which=-1;

	for (; i <= how_many-1; i++){
		if (!(strcmp(inst_list[i].get_f_name().c_str(), f_name.c_str())) && !(strcmp(inst_list[i].get_s_name().c_str(), s_name.c_str()))){
			which = i;
		}
		
	}

	if (which == -1){
		cout << "Not found" << endl;
	}

	else{
		
		instructor *temp = new instructor[size];

		for (int i = 0; i <=how_many-1; i++){
			
			if (i < which)
				temp[i] = inst_list[i];
			
			else if (i>which)
				temp[i-1] = inst_list[i];
			
		}

		delete[] inst_list;
		inst_list = new instructor[size];

		for (int i = 0; i < how_many; i++){
			inst_list[i] = temp[i];
		}
		how_many--;

		cout << "Instructor has been deleted"<<endl;
	}

	
}

void instructor_list::search_name_inst(string f_name){

	cout << "--------- Search Results --------" << endl;
	int i = 0, which = -1;

	for (; i <= how_many; i++){
		if (!( strcmp(inst_list[i].get_f_name().c_str(), f_name.c_str()) )){
			which = i;
		}

	}

	if (which == -1){
		cout << "Not Found" << endl;

	}

	else{
		cout << "Title : " << inst_list[which].get_title() << endl;
		cout << "First Name : " << inst_list[which].get_f_name() << endl;
		cout << "Suname : " << inst_list[which].get_s_name() << endl;
		cout << "Telephone Number : " << inst_list[which].get_p_num() << endl;
		cout << "Room Number : " << inst_list[which].get_r_num() << endl;
		cout << "User Name : " << inst_list[which].get_u_name() << endl;
		cout << "E-mail : " << inst_list[which].get_email() << endl;
		cout << "Courses : [";
		
		for (int j = 0; j < inst_list[which].get_c_num(); j++){

			if (j == inst_list[which].get_c_num() - 1)
				cout << inst_list[which].get_courses()[j];

			else
				cout << inst_list[which].get_courses()[j] << ", ";

		}

		cout << "]" << endl;
		cout << endl << "---------------------------" << endl;
	}

}

void  instructor_list::search_surname_inst(string s_name){

	cout << "--------- Search Results --------" << endl;

	int i = 0, which = -1;

	for (; i < how_many; i++){
		if (!(strcmp(inst_list[i].get_s_name().c_str(), s_name.c_str()))){
			which = i;
		}

	}

	if (which == -1){
		cout << "Not Found" << endl;

	}

	else{
		cout << "Title : " << inst_list[which].get_title()<< endl;
		cout << "First Name : " << inst_list[which].get_f_name() << endl;
		cout << "Suname : " << inst_list[which].get_s_name() << endl;
		cout << "Telephone Number : " << inst_list[which].get_p_num() << endl;
		cout << "Room Number : " << inst_list[which].get_r_num() << endl;
		cout << "User Name : " << inst_list[which].get_u_name() << endl;
		cout << "E-mail : " << inst_list[which].get_email() << endl;
		cout << "Courses : [";
		
		for (int j = 0; j < inst_list[which].get_c_num(); j++){

			if (j == inst_list[which].get_c_num() - 1)
				cout << inst_list[which].get_courses()[j];

			else
				cout << inst_list[which].get_courses()[j] << ", ";

		}

		cout << "]" << endl;
		cout << endl << "---------------------------" << endl;
	}



}

void instructor_list::search_phonenum_inst(string phone){

	cout << "--------- Search Results --------" << endl;

	int i = 0, which = -1;

	for (; i <= how_many; i++){
		if (!(strcmp(inst_list[i].get_p_num().c_str(), phone.c_str()))){
			which = i;
		}

	}

	if (which == -1){
		cout << "Not Found" << endl;

	}

	else{
		cout << "Title : " << inst_list[which].get_title() << endl;
		cout << "First Name : " << inst_list[which].get_f_name() << endl;
		cout << "Suname : " << inst_list[which].get_s_name() << endl;
		cout << "Telephone Number : " << inst_list[which].get_p_num() << endl;
		cout << "Room Number : " << inst_list[which].get_r_num() << endl;
		cout << "User Name : " << inst_list[which].get_u_name() << endl;
		cout << "E-mail : " << inst_list[which].get_email() << endl;
		cout << "Courses : [";
		
		for (int j = 0; j < inst_list[which].get_c_num(); j++){

			if (j == inst_list[which].get_c_num() - 1)
				cout << inst_list[which].get_courses()[j];

			else
				cout << inst_list[which].get_courses()[j] << ", ";

		}

		cout << "]" << endl;
		cout << endl << "---------------------------" << endl;
	}


}

void instructor_list::search_roomnum_inst(string room){

	cout << "------------ Search Results -----------" << endl;

	int i = 0, which = -1;

	for (; i <= how_many; i++){
		if (!(strcmp(inst_list[i].get_r_num().c_str(), room.c_str()))){
			which = i;
		}

	}

	if (which == -1){
		cout << "Not Found" << endl;

	}

	else{
		cout << "Title : " << inst_list[which].get_title() << endl;
		cout << "First Name : " << inst_list[which].get_f_name() << endl;
		cout << "Suname : " << inst_list[which].get_s_name() << endl;
		cout << "Telephone Number : " << inst_list[which].get_p_num() << endl;
		cout << "Room Number : " << inst_list[which].get_r_num() << endl;
		cout << "User Name : " << inst_list[which].get_u_name() << endl;
		cout << "E-mail : " << inst_list[which].get_email() << endl;
		cout << "Courses : [";
		
		for (int j = 0; j < inst_list[which].get_c_num(); j++){

			if (j == inst_list[which].get_c_num() - 1)
				cout << inst_list[which].get_courses()[j];

			else
				cout << inst_list[which].get_courses()[j] << ", ";

		}

		cout << "]" << endl;
		cout << endl << "---------------------------" << endl;
	}

}

