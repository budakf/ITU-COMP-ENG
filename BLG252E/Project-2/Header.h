/*
	Fatih Budak
	150130006	
	Hw-2
*/

#include<iostream>
#include<string>
#include<vector>

using namespace std;

enum last_state{ Lose = 0, Tie = 1, Win = 2 };  

class Base{ 				//abstract base class
	friend class list;
	
	protected:
		virtual void compare(Base &)  =0;  //
		
	public:
		Base(){};
		char type;
		last_state state;
		
};

//////////////////////////////////////////////////////////////

class Green : public Base{

	protected:
		void compare(Base &) ;

	public:
		Green(){ type = 'g'; }
};

void Green::compare(Base &a) { //Compare function for green 
	
	if (a.type == 'g'){
		a.state = Tie;
		state = Tie;
	}

	else if (a.type == 'b'){
		a.state = Lose ;
		state = Win;
	}

	else if (a.type == 'r'){
		a.state = Win;
		state = Lose;
	}

	else if (a.type == 'd'){
		a.state = Lose;
		state = Win;
	}

}

/////////////////////////////////////////////////////////////

class Blue : public Base{  //Compare function for blue

	protected:
		void compare(Base &) ;

	public:
		Blue(){ type = 'b'; }
};

void Blue::compare(Base &a) {

	if (a.type == 'b'){
		a.state = Tie;
		state = Tie;
	}

	else if (a.type == 'g'){
		a.state = Win;
		state = Lose;
	}

	else if (a.type == 'r'){
		a.state = Lose;
		state = Win;
	}

	else if (a.type == 'd'){
		a.state = Win;
		state = Lose;
	}


}

///////////////////////////////////////////////////////////////

class Red : public Base{	//Compare function for red

	protected:
		void compare(Base &) ;

	public:
		Red(){ type = 'r'; }
};

void Red::compare(Base &a) {

	if (a.type == 'r'){
		a.state = Tie;
		state = Tie;
	}

	else if (a.type == 'g'){
		a.state = Lose;
		state = Win;
	}

	else if (a.type == 'b'){
		a.state = Win;
		state = Lose;
	}

	else if (a.type == 'd'){
		a.state = Win;
		state = Lose;
	}

}

////////////////////////////////////////////////////////////////

class Darkred : public Red{		//Compare function for darkred

	protected:
		void compare(Base &) ;

	public:
		Darkred(){ type = 'd'; }
};

void Darkred::compare(Base &a) {

	if (a.type == 'd'){
		a.state = Tie;
		state = Tie;
	}

	else if (a.type == 'b'){
		a.state = Lose;
		state = Win;
	}

	else if (a.type == 'g'){
		a.state = Win;
		state = Lose;
	}

	else if (a.type == 'r'){
		a.state = Lose;
		state = Win;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////

class listnode{
	friend class list;
	Base *eleman;
	listnode *next;
	listnode *previous;
	
	public:
		listnode(Base &);  //constructor

};

listnode::listnode(Base &n){
	eleman = &n;
	next = NULL;
	previous =NULL;
}


class list{
  
	listnode *head;
	
public:
	list();	 						//constructor
	bool insert(Base &);
	void compare_list_elements();
	~list();          				//destructor
};

list::list(){          //definition of constructor
	head = NULL; 
}

list::~list(){   //definition of destructor

	listnode *temp;
	
	while(head){       
		 temp=head;
		 head=head->next;
		 delete temp;
	}

}

void show_result( vector <last_state> result1 , vector <last_state> result2){			// this function  shows results only
	
	int score1[3]={0},score2[3]={0};  // 0=Lose  1=Tie  2=Win 
	
	cout <<"Score1 : ";
	for(int i=0;i<result1.size();i++)
		cout <<result1[i] <<" ";
		
	cout <<endl <<"Score2 : ";
	for(int i=0;i<result1.size();i++)
		cout <<result2[i] <<" ";
	
	for(int i=0;i<result1.size();i++){
		
		if(result1[i]==Lose){
			score1[0]++;
			score2[2]++;
		}
		
		else if(result1[i]==Tie){
			score1[1]++;
			score2[1]++;
		}
		
		else if(result1[i]==Win){
			score1[2]++;
			score2[0]++;
		}
	}

	int total1 = score1[0]*0 + score1[1]*1 + score1[2]*2;
	int total2 = score2[0]*0 + score2[1]*1 + score2[2]*2;
	
	cout << endl << "Total Score1:" << " Lose:" << score1[0] << " Tie:" << score1[1] << " Win:" << score1[2];
	cout << endl << "Total Score2:" << " Lose:" << score2[0] << " Tie:" << score2[1] << " Win:" << score2[2];

	if (total1 > total2)
		cout << endl << "Winner: Player1"<<endl;
	else if(total2 > total1)
		cout << endl << "Winner: Player2"<<endl;
	else
		cout << endl << "Winner: Tie" <<endl;
		
}


void list::compare_list_elements(){  // Compare fonksiyonlarý bu fonksiyon içerisinde kullanýyoruz
	
	vector<last_state> result1 , result2;  // 

	listnode *temp = head;
	
	while(temp->next)
		temp=temp->next;
		
	while (temp->previous){
		temp->eleman->compare(*(temp->previous->eleman));
		
		result1.push_back(temp->eleman->state);	
		result2.push_back(temp->previous->eleman->state);
		
		if (temp->previous->previous)
			temp = temp->previous->previous;
		else
			break;
	}
		
	show_result(result1,result2);
}

bool list::insert( Base & n){  // to add new object to head of list

	listnode *neww;
	
	if (head){
		neww=new listnode(n);
		neww->next=head;
		head->previous=neww;
		neww->previous=NULL;
		head=neww;		
	}
	
	else{
		head = new listnode(n);
		head->next=NULL;
		head->previous=NULL;			
	}
	
	return true;
}


