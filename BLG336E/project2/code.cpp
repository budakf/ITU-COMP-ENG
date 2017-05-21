/*
Fatih Budak
150130006
*/
#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

class Parser{

private:
	vector <string> line; // is also tagged line

public:
	vector <string> & getter_line();
	void setter_line(string);
	void extractParseTree(vector <string> &, int, ofstream&);
	Parser();
	void erase_line();
};

Parser::Parser(){
	line.resize(0);
}
vector <string> & Parser::getter_line(){
	return line;
}

void Parser::setter_line(string sentence){
	int num = 0;
	string temp="";
	int i = 0;
	while (i < sentence.length()){
		if (sentence[i] != ' '){
			temp += sentence[i];
		}
		if (sentence[i] == ' ' || (i == sentence.length() - 1 && sentence[i] != ' ')){
			this->line.push_back(temp);
			temp = "";
		}
		i++;
	}

}

void Parser::extractParseTree(vector <string> & sentence, int len, ofstream& writing){

	string ss="";
	if (len==1){
		if (sentence.size() != 1)
			writing << "SYNTAX ERROR" << endl;
		else
			writing << sentence[0] << endl;
		return;
	}
			

		
	else{
		ss += sentence[len - 2][0];
		ss += sentence[len - 2][1];
		ss += ' ';
		ss += sentence[len - 1][0];
		ss += sentence[len - 1][1];

		if (ss == "PR NN" || ss == "PR NP"){ //PP
			sentence[len - 2].insert(0, "PP[");
			sentence[len - 2] += ' ';
			sentence[len - 2] += sentence[len - 1];
			sentence[len - 2] += ']';
			//cout << sentence[len - 2] << endl;
			sentence.erase(sentence.begin() + len - 1);
			len = sentence.size();
			extractParseTree(sentence, len, writing);
		}
		else if (ss == "NN NN" || ss == "AD NN" || ss == "AD NP" || ss == "DT NP" || ss == "DT NN"){ //NP
			sentence[len - 2].insert(0, "NP[");
			sentence[len - 2] += ' ';
			sentence[len - 2] += sentence[len - 1];
			sentence[len - 2] += ']';
			//cout << sentence[len - 2] << endl;
			sentence.erase(sentence.begin() + len - 1);
			len = sentence.size();
			extractParseTree(sentence, len, writing);
		}
		else if (ss == "VR PP" || ss == "NN VR" || ss == "NP VR" || ss == "VR NP"){ //VP
			sentence[len - 2].insert(0, "VP[");
			sentence[len - 2] += ' ';
			sentence[len - 2] += sentence[len - 1];
			sentence[len - 2] += ']';
			//cout << sentence[len - 2] << endl;
			sentence.erase(sentence.begin() + len - 1);
			len = sentence.size();
			extractParseTree(sentence, len, writing);
		}
		else if ((ss == "NP VP" || ss == "NN VP") && sentence.size() == 2 ){ //SS
			sentence[len - 2].insert(0, "SS[");
			sentence[len - 2] += ' ';
			sentence[len - 2] += sentence[len - 1];
			sentence[len - 2] += ']';
			//cout << sentence[len - 2] << endl;
			sentence.erase(sentence.begin() + len - 1);
			len = sentence.size();
			extractParseTree(sentence, len, writing);
		}
		else{
			//cout << sentence[len - 2] << endl;
			extractParseTree(sentence, len - 1, writing);
		}
	}
}

string Tagged2POS(string & sentence){

	string new_sentence = "";
	string temp = "";
	int length = sentence.length();
	int i = 0;
	while (i < length){
		if (sentence[i] != ' '){
			temp += sentence[i];
		}
		if (sentence[i] == ' ' || (i == length - 1 && sentence[i] != ' ')){
			if (temp == "that" || temp == "this" || temp == "a" || temp == "the"){
				new_sentence += "DT(";
				new_sentence += temp;
				if (i == length - 1)
					new_sentence += ")";
				else
					new_sentence += ") ";
			}
			else if (temp == "book" || temp == "flight" || temp == "cat" || temp == "mat" || temp == "i" || temp == "ý" || temp == "you" || temp == "they"){
				new_sentence += "NN(";
				new_sentence += temp;
				if (i == length - 1)
					new_sentence += ")";
				else
					new_sentence += ") ";
			}

			else if (temp == "booked" || temp == "included" || temp == "preferred" || temp == "sat"){
				new_sentence += "VR(";
				new_sentence += temp;
				if (i == length - 1)
					new_sentence += ")";
				else
					new_sentence += ") ";
			}

			else if (temp == "from" || temp == "to" || temp == "on" || temp == "near" || temp == "through"){
				new_sentence += "PR(";
				new_sentence += temp;
				if (i == length - 1)
					new_sentence += ")";
				else
					new_sentence += ") ";
			}

			else if (temp == "big" || temp == "heavy" || temp == "beautiful" || temp == "cheap"){
				new_sentence += "AD(";
				new_sentence += temp;
				if (i == length - 1)
					new_sentence += ")";
				else
					new_sentence += ") ";
			}

			temp = "";
		}
		i++;
	}

	return new_sentence;

}

void Parser::erase_line(){
	this->line.erase(line.begin(), line.end());
}

int main(int argc, char ** argv){
		
	ifstream reading(argv[1]);  //"input.txt"
	ofstream writing("output.txt");
	string temp;
	Parser pars;
	int i = 0;
	while(!reading.eof()){
		getline(reading, temp);
		temp[0] = tolower(temp[0]);
		pars.setter_line(Tagged2POS(temp) );
		pars.extractParseTree(pars.getter_line(), pars.getter_line().size(),writing);
		pars.erase_line();
		
	}	

	reading.close();
	writing.close();

	return 0;
}
