/*
Fatih Budak
150130006
*/

#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>

using namespace std;

class myHash {

private:
	string *myHashTable;			 // Stores words.
	int totalEntries;			// Stores the current number of entries in the table.

public:
	int _tableSize;
	int collision ;
	myHash(int tableSize);      //** Creates a hash table that can store up to tableSize entries. (Constructor)
	~myHash();
	void insert(string s);     // Inserts w into the hash table. 
	int hashFunc(string s);	  //** Computes the hash value of w. 
	bool retrieve(string s); // Finds index of a given word in the hash table, if it isn't in the table, starts for spell checking and suggests similiar
							// words if any found. 30 POINTS
	bool remove(string s); // Removes given word from the dictionary.
	string * get_myHashTable();
	void set_myHashTable(string, int );
};	

myHash::myHash(int tableSize){
	this->collision = 0;
	this->totalEntries = 0;
	this->_tableSize = tableSize;
	myHashTable = new string[_tableSize];
	for (int i = 0; i < _tableSize; i++)
		myHashTable[i] = "*";				// * shows us this index is empty.
}

myHash::~myHash(){
	delete[] this->myHashTable;
}

string * myHash::get_myHashTable(){
	return this->myHashTable;
}

void myHash::set_myHashTable(string s, int index){
	this->myHashTable[index] = s;
}

void myHash::insert(string s){
	
	int temp_collision = 0;
	int key = this->hashFunc(s);
	int i;

	for (i = key; i <= this->_tableSize; i++){

		if (i >= this->_tableSize && this->totalEntries <= this->_tableSize)
			i %= this->_tableSize;

		if (this->totalEntries == this->_tableSize){
			cout << "WARNING: There are no empty space in the hash table for the word: " << s << endl;
			break;
		}

		if ( myHashTable[i] == "*" || myHashTable[i] == "#" ){ // # shows us this index deleted before   * shows us this index is empty
			myHashTable[i] = s;
			this->totalEntries++;
			cout << "INSERT: The word '" << s << "' is put in the cell number " << key << endl;
			break;
		}
		else if (myHashTable[i] == s){
			cout << "h(x) result is " << i << " for: " << s << endl;
			cout << "WARNING: The word '" << s << "' is already in the dictionary!" << endl;
			break;
		}
		else
			temp_collision++;

	}

	cout << "COLLISIONS : " << temp_collision << endl;
	this->collision += temp_collision;
}	

int myHash::hashFunc(string s){

	long long int x=1;
	for(int i = 0; i < s.length(); i++){
		x *= (s[i] - 0);
		if (x>337)
			x %= 337;
	}

	x %= 337;
	return x;
}

bool myHash::remove(string s){
	int temp_collision = 0;
	int key = this->hashFunc(s);

	for (int i = key; i <= this->_tableSize; i++){

		if (i >= this->_tableSize && this->totalEntries <= this->_tableSize)
			i %= this->_tableSize;

		if (this->myHashTable[i] == s){
			this->totalEntries--;
			this->myHashTable[i] = "#";				// this index is marked as deleted with "#*"
			cout << "REMOVE: The word '" << s << "' is removed from the dictionary." << endl;
			cout << "COLLISIONS : " << temp_collision << endl;
			this->collision += temp_collision;
			return true;
		}
		temp_collision++;

		if (i == key - 1){
			cout << "WARNING: The word '" << s << "' couldn't be found in the dictionary" << endl;
			break;
		}
	}	
	
	
	cout << "COLLISIONS : " << temp_collision << endl;
	this->collision += temp_collision;
	return false;
}	

bool myHash::retrieve(string s){
	int temp_collision = 0;
	int key = this->hashFunc(s);
	int i;          
	for (i = key;  i < this->_tableSize; i++){ //If we do not found s in first slot we apply linear probing from current slot to next EMPTY slot (not deleted slot).
		
		if (i >= this->_tableSize && this->totalEntries <= this->_tableSize)
			i %= this->_tableSize;

		if (this->myHashTable[i] == s){
			cout << "RETRIEVE: The word '" << s << "' found in the dictionary with index: " << key << endl;
			cout << "COLLISIONS : " << temp_collision << endl;
			this->collision += temp_collision;
			return true; //
		}
		else if (this->myHashTable[i] == "*"){ // until first next EMPTY slot
			temp_collision++;
			break;
		}
		
		temp_collision++;

		if (i == key - 1){
			break;
		}
	}
	
	cout << "SUGGESTIONS for " << s << ": ";
	int different_letter;
	bool flag = false;
	
	for (int i = 0; i < this->_tableSize; i++){
		different_letter = 0;
		if (this->myHashTable[i].length() == s.length() && s.length() !=1 ){
			for (int j = 0; j < s.length(); j++){
				if (this->myHashTable[i][j] != s[j])
					different_letter++;
			}
			if (different_letter == 1){
				cout << this->myHashTable[i] << " ";
				flag = true;
			}	
		}

		else if (this->myHashTable[i].length() == s.length() && s.length() == 1){ // Örneðin aranan ve bulunamayan string ifade tek karakter ise ( a, b gibi)
			for (int j = 0; j < s.length(); j++){								  // *(empty slot) ve #(deleted slot) ý suggestion olarak vermemiþ oluyoruz bu kod bloðu sayesinde	
				if (this->myHashTable[i][j] != s[j])
					different_letter++;
			}
			if (different_letter == 1){
				if (this->myHashTable[i] != "#" && this->myHashTable[i] != "*")
					cout << this->myHashTable[i] << " ";
				flag = true;
			}
		}
	}
	
	cout << endl;
	if (!flag)
		cout << "No any suggestion" << endl;
	else
		cout << "COLLISIONS : " << temp_collision << endl;
	this->collision += temp_collision;
	
	return false;
}	
	
int main(int argc, char ** argv){
		
	/*int ascii = 'a' - 0;
	cout << ascii;*/
	
	string file_name = argv[1];    //   "words.txt"; 
	int N = atoi(argv[2]);    //	337;	  //table_size;
	bool which = false;
	string temp_line, temp_func_name, temp_word;
	ofstream writing("150130006_output.txt");
	ifstream reading(file_name.c_str());
	myHash mine(N);
	
	while (!reading.eof()){  // 
		temp_func_name = "";
		temp_word = "";
		
		reading >> temp_line;

		for (int i = 0; i < temp_line.length(); i++){

			if (temp_line[i] != ':' && !which )
				temp_func_name += temp_line[i];

			else if (temp_line[i] == ':')
				which = true;
				
			else if (temp_line[i] != ':' && which )
				temp_word += temp_line[i];

		}

		if (temp_func_name == "insert"){
			mine.insert(temp_word);
			cout << endl;
		}
			

		else if (temp_func_name == "delete"){
			mine.remove(temp_word);
			cout << endl;
		}
			
		else if (temp_func_name == "retrieve"){
			mine.retrieve(temp_word);
			cout << endl;
		}
		
		which = false;
		
	}	
	
	cout << endl << "Total Collision is: " << mine.collision;

	for (int i = 0; i < N; i++){
		if (mine.get_myHashTable()[i] == "*") // empty slot marker is deleted from hash table
			mine.set_myHashTable(" ", i);
		else if (mine.get_myHashTable()[i] == "#") //deleted slot marker is deleted from hash table
			mine.set_myHashTable(" ", i);
		writing << i << ": " << mine.get_myHashTable()[i] << endl;

	}

	cout << endl << "Final form of hash table is saved as 150130006_output.txt" << endl;
	
	getchar();
	
	return 0;
}