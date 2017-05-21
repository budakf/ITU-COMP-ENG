#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<vector>
#include<queue>
#include<stack>
#include<ctime>

using namespace std;

int generated_node=0;			//Analyzing Purpose Only 
int node_kept_in_memory=0;		//Analyzing Purpose Only 

class Node{

	private:
		int **matrix;
		char *directions; // 1 2 3 4 5 6 7  ..... indisler kullanýlacak
		int **indises;
		int *sizes;
		int block_number;

	public:
		Node();
		void set_first_state();
		void build_matrix(int, int, int, char, int);
		void set_matrix(int, int, int, char, int);
		void set_indices(int, int, int);
		void set_directions(int, char);
		void set_sizes(int, int);
		int ** get_matrix();
		int ** get_indises();
		char * get_directions();
		int * get_sizes();
		int get_block_number();
		void set_block_number(int );
};

int Node::get_block_number(){
	return this->block_number;
}

void Node::set_block_number(int num){
	this->block_number = num;
}

void Node::set_first_state(){
	
	this->indises = new int* [this->block_number];	// 1 2 3 4 5 6 7. indisler 
	for (int i = 0; i < this->block_number; i++)
		indises[i] = new int[2];

	//////////////////////////////
	this->sizes = new int[this->block_number];
	//////////////////////////////
	this->directions = new char [this->block_number+1];
}

Node::Node(){

	this->matrix = new int* [6];
	for (int i = 0; i < 6; i++)
		matrix[i] = new int[6];

	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			matrix[i][j] = 0;

}

void Node::build_matrix(int r, int c, int s, char d, int type){ // type==counter

	this->set_matrix(r, c, s, d, type);
	this->set_indices(type, r, c);
	this->set_directions(type,d);
	this->set_sizes(type, s);
}

void Node::set_matrix(int r, int c, int s, char d, int type){

	if (d == 'h')
		while (s--)
			this->matrix[r][c++] = type;

	else
		while (s--)
			this->matrix[r--][c] = type;
}

void Node::set_indices(int t, int r, int c){

		this->indises[t][0] = r;
		this->indises[t][1] = c;
}

void Node::set_directions(int type, char d){
	this->directions[type] = d;
}

void Node::set_sizes(int type, int s){

	this->sizes[type] = s;
}

int ** Node::get_matrix(){
	
	return this->matrix;
}

int ** Node::get_indises(){

	return this->indises;
}

char * Node::get_directions(){

	return this->directions;
}

int * Node::get_sizes(){

	return this->sizes;
}

class Graph{

	private:
		Node *root;

	public:
		queue <Node*> C1;
		stack <Node*> C2;
		vector <Node*> compare;
		vector<Node*>::iterator it;

		Node *children;
		Graph();
		void set_root(Node *);
		Node * get_root();
		void build_child(Node *);
	
};				

Graph::Graph(){
	this->root = new Node;
}

void Graph::set_root(Node *r){

	this->root = r;
	this->C1.push(root);
	this->C2.push(root);
	this->compare.push_back(root);
	this->it = compare.begin();
}	

Node * Graph::get_root(){

	return root;
}

void Graph::build_child(Node *ancestor){

	for (int i = 0; i < 6; i++)
	for (int j = 0; j < 6; j++)
		this->children->get_matrix()[i][j] = ancestor->get_matrix()[i][j];

	for (int i = 1; i < ancestor->get_block_number(); i++)
	for (int j = 0; j < 2; j++)
		this->children->get_indises()[i][j] = ancestor->get_indises()[i][j];

	for (int i = 1; i < ancestor->get_block_number(); i++){
		this->children->set_sizes(i, ancestor->get_sizes()[i]);
		this->children->get_directions()[i] = ancestor->get_directions()[i];
		//cout << this->children[num].get_directions()[i]<<" ";
	}

}


int compareFunction(vector <Node *> &all, Node * neww){

	int fark;
	//cout <<"all.size : " << all.size() << endl;
	vector <Node *>::iterator ite = all.begin();

	while (ite != all.end()){
		fark = 36; //
		for (int i = 0; i < 6; i++){ // 0 6
			for (int j = 0; j < 6; j++) //  3 6
			if (neww->get_matrix()[i][j] == (*ite)->get_matrix()[i][j])
				fark--;
		}

		if (fark == 0){
			//cout << endl << "Aynisi";
			return 1;
		}
		ite++;
	}

	//cout << endl << "Aynisi degil";
	all.push_back(neww);
	return 0;
			
}

void print2file(ofstream &writing, Node *child ){
	
	int *x=new int[child->get_block_number()]{0};
	for(int which=1; which<child->get_block_number();which++){
		for (int i = 0; i < 6; i++){
			for (int j = 0; j < 6; j++)
				if(child->get_matrix()[i][j]==which && x[which]==0){
					if(child->get_directions()[which] =='h'){
						writing <<child->get_indises()[which][0]+1 <<" " <<child->get_indises()[which][1]+1 <<" " <<child->get_sizes()[which] <<" " << child->get_directions()[which]<<endl;
						x[which]++;
					}
					else if(child->get_directions()[which] =='v') {
						writing <<child->get_indises()[which][0] +1   <<" " <<child->get_indises()[which][1]+1 <<" " <<child->get_sizes()[which] <<" " << child->get_directions()[which]<<endl;
						x[which]++;
					}
				}
		}
	}
	writing<<endl;
	
}

void state_transition_funcforBFS(Graph *mine, Node *Root ,ofstream &writing){


	for (int i = 1; i<Root->get_block_number() ; i++){  // 7 tane blok var 1 2 3 4 5 6 7
		if (Root->get_directions()[i] == 'h'){
			if (Root->get_indises()[i][1] - 1 >= 0 && Root->get_matrix()[Root->get_indises()[i][0]][Root->get_indises()[i][1] - 1] == 0){
				mine->children = new Node;
				mine->children->set_block_number(Root->get_block_number());
				mine->children->set_first_state();
				mine->build_child(Root);
				mine->children->get_matrix()[Root->get_indises()[i][0]][Root->get_indises()[i][1] - 1] = i;
				mine->children->get_matrix()[Root->get_indises()[i][0]][Root->get_indises()[i][1] + Root->get_sizes()[i] - 1] = 0;
				mine->children->get_indises()[i][1]--;
				generated_node++;
				if (compareFunction(mine->compare, mine->children) == 0){
					mine->C1.push(mine->children);
					node_kept_in_memory++;
				}
				if ((mine->children->get_matrix()[2][5] == 1) || (mine->children->get_matrix()[2][3] == 0 && mine->children->get_matrix()[2][4] == 0 && mine->children->get_matrix()[2][5] == 0)){
					print2file(writing, mine->children);
					return;
				}

			}
			if (Root->get_indises()[i][1] + Root->get_sizes()[i] <= 5 && Root->get_matrix()[Root->get_indises()[i][0]][Root->get_indises()[i][1] + Root->get_sizes()[i]] == 0){
				mine->children = new Node;
				mine->children->set_block_number(Root->get_block_number());
				mine->children->set_first_state();
				mine->build_child(Root);
				mine->children->get_matrix()[Root->get_indises()[i][0]][Root->get_indises()[i][1] + Root->get_sizes()[i]] = i;
				mine->children->get_matrix()[Root->get_indises()[i][0]][Root->get_indises()[i][1]] = 0;
				mine->children->get_indises()[i][1]++;
				generated_node++;
				if (compareFunction(mine->compare, mine->children) == 0){
					mine->C1.push(mine->children);
					node_kept_in_memory++;
				}
				if ((mine->children->get_matrix()[2][5] == 1) || (mine->children->get_matrix()[2][3] == 0 && mine->children->get_matrix()[2][4] == 0 && mine->children->get_matrix()[2][5] == 0)){
					print2file(writing, mine->children);
					return;
				}
			}	
		}

		else{
			if (Root->get_indises()[i][0] + 1 <= 5 && Root->get_matrix()[Root->get_indises()[i][0] + 1][Root->get_indises()[i][1]] == 0){
				mine->children = new Node;
				mine->children->set_block_number(Root->get_block_number());
				mine->children->set_first_state();
				
				mine->build_child(Root);
				mine->children->get_matrix()[Root->get_indises()[i][0] + 1][Root->get_indises()[i][1]] = i;
				mine->children->get_matrix()[Root->get_indises()[i][0] - Root->get_sizes()[i] + 1][Root->get_indises()[i][1]] = 0;
				mine->children->get_indises()[i][0]++;
				generated_node++;
				if (compareFunction(mine->compare, mine->children) == 0){
					mine->C1.push(mine->children);
					node_kept_in_memory++;
				}
				if ((mine->children->get_matrix()[2][5] == 1) || (mine->children->get_matrix()[2][3] == 0 && mine->children->get_matrix()[2][4] == 0 && mine->children->get_matrix()[2][5] == 0)){
					print2file(writing, mine->children);
					return;
				}
			}
			if (Root->get_indises()[i][0] - Root->get_sizes()[i] >= 0 && Root->get_matrix()[Root->get_indises()[i][0] - Root->get_sizes()[i]][Root->get_indises()[i][1]] == 0){
				mine->children = new Node;
				mine->children->set_block_number(Root->get_block_number());
				mine->children->set_first_state();
				
				mine->build_child(Root);
				mine->children->get_matrix()[Root->get_indises()[i][0] - Root->get_sizes()[i]][Root->get_indises()[i][1]] = i;
				mine->children->get_matrix()[Root->get_indises()[i][0]][Root->get_indises()[i][1]] = 0;
				mine->children->get_indises()[i][0]--;
				generated_node++;
				if (compareFunction(mine->compare, mine->children) == 0){
					mine->C1.push(mine->children);
					node_kept_in_memory++;
				}
				if ((mine->children->get_matrix()[2][5] == 1) || (mine->children->get_matrix()[2][3] == 0 && mine->children->get_matrix()[2][4] == 0 && mine->children->get_matrix()[2][5] == 0)){
					print2file(writing, mine->children);
					return;
				}
			}
		}	
	}

	if (mine->C1.size() == 0){
		cout << "Kuyruk Boþ";
		return;
	}

	else if (mine->C1.size()){
		Node *temp = new Node;
		temp = mine->C1.front();
		print2file(writing, mine->children);
		mine->C1.pop();
		state_transition_funcforBFS(mine, temp, writing); // recursion
		
	}

}

void state_transition_funcforDFS(Graph *mine, Node *Root ,ofstream &writing){

	for (int i = 1; i < Root->get_block_number(); i++){ // 7 tane blok var 1 2 3 4 5 6 7
		if (Root->get_directions()[i] == 'h'){
			if (Root->get_indises()[i][1] - 1 >= 0 && Root->get_matrix()[Root->get_indises()[i][0]][Root->get_indises()[i][1] - 1] == 0){
				mine->children = new Node;
				mine->children->set_block_number(Root->get_block_number());
				mine->children->set_first_state();
				
				mine->build_child(Root);
				mine->children->get_matrix()[Root->get_indises()[i][0]][Root->get_indises()[i][1] - 1] = i;
				mine->children->get_matrix()[Root->get_indises()[i][0]][Root->get_indises()[i][1] + Root->get_sizes()[i] - 1] = 0;
				mine->children->get_indises()[i][1]--;
				generated_node++;//
				if (compareFunction(mine->compare, mine->children) == 0){
					mine->C2.push(mine->children);
					node_kept_in_memory++;
				}
				if ((mine->children->get_matrix()[2][5] == 1) || (mine->children->get_matrix()[2][3] == 0 && mine->children->get_matrix()[2][4] == 0 && mine->children->get_matrix()[2][5] == 0)){
					print2file(writing, mine->children);
					return;
				}

			}
			if (Root->get_indises()[i][1] + Root->get_sizes()[i] <= 5 && Root->get_matrix()[Root->get_indises()[i][0]][Root->get_indises()[i][1] + Root->get_sizes()[i]] == 0){
				mine->children = new Node;
				mine->children->set_block_number(Root->get_block_number());
				mine->children->set_first_state();
				
				mine->build_child(Root);
				mine->children->get_matrix()[Root->get_indises()[i][0]][Root->get_indises()[i][1] + Root->get_sizes()[i]] = i;
				mine->children->get_matrix()[Root->get_indises()[i][0]][Root->get_indises()[i][1]] = 0;
				mine->children->get_indises()[i][1]++;
				generated_node++;//
				if (compareFunction(mine->compare, mine->children) == 0){
					mine->C2.push(mine->children);
					node_kept_in_memory++;
				}
				if ((mine->children->get_matrix()[2][5] == 1) || (mine->children->get_matrix()[2][3] == 0 && mine->children->get_matrix()[2][4] == 0 && mine->children->get_matrix()[2][5] == 0)){
					print2file(writing, mine->children);
					return;
				}
			}
		}

		else{
			if (Root->get_indises()[i][0] + 1 <= 5 && Root->get_matrix()[Root->get_indises()[i][0] + 1][Root->get_indises()[i][1]] == 0){
				mine->children = new Node;
				mine->children->set_block_number(Root->get_block_number());
				mine->children->set_first_state();
				
				mine->build_child(Root);
				mine->children->get_matrix()[Root->get_indises()[i][0] + 1][Root->get_indises()[i][1]] = i;
				mine->children->get_matrix()[Root->get_indises()[i][0] - Root->get_sizes()[i] + 1][Root->get_indises()[i][1]] = 0;
				mine->children->get_indises()[i][0]++;
				generated_node++;//
				if (compareFunction(mine->compare, mine->children) == 0){
					mine->C2.push(mine->children);
					node_kept_in_memory++;
				}
				if ((mine->children->get_matrix()[2][5] == 1) || (mine->children->get_matrix()[2][3] == 0 && mine->children->get_matrix()[2][4] == 0 && mine->children->get_matrix()[2][5] == 0)){
					print2file(writing, mine->children);
					return;
				}
			}
			if (Root->get_indises()[i][0] - Root->get_sizes()[i] >= 0 && Root->get_matrix()[Root->get_indises()[i][0] - Root->get_sizes()[i]][Root->get_indises()[i][1]] == 0){
				mine->children = new Node;
				mine->children->set_block_number(Root->get_block_number());
				mine->children->set_first_state();
				
				mine->build_child(Root);
				mine->children->get_matrix()[Root->get_indises()[i][0] - Root->get_sizes()[i]][Root->get_indises()[i][1]] = i;
				mine->children->get_matrix()[Root->get_indises()[i][0]][Root->get_indises()[i][1]] = 0;
				mine->children->get_indises()[i][0]--;
				generated_node++;//
				if (compareFunction(mine->compare, mine->children) == 0){
					mine->C2.push(mine->children);
					node_kept_in_memory++;
				}
				if ((mine->children->get_matrix()[2][5] == 1) || (mine->children->get_matrix()[2][3] == 0 && mine->children->get_matrix()[2][4] == 0 && mine->children->get_matrix()[2][5] == 0)){
					print2file(writing, mine->children);
					return;
				}
			}
		}
	}

	if (mine->C2.size() == 0){
		cout << "Kuyruk Boþ";
		return;
	}

	else if (mine->C2.size()){
		Node *temp = new Node;
		temp = mine->C2.top();
		print2file(writing, mine->children);		
		mine->C2.pop();
		state_transition_funcforDFS(mine, temp, writing);

	}

}

int main(int argc, char **argv){

	string bfsORdfs = argv[1];
	string input    = argv[2];
	string output   = argv[3];
	clock_t t;
	int row, column, size;
	char direction;
	
	ifstream reading;
	reading.open(input.c_str());     //
	ofstream writing(output.c_str());			
	reading >> row >> column >> size >> direction;
	int count = 0;
	
	while (!reading.eof()){
		reading >> row >> column >> size >> direction;
		count++;
	}
	
	reading.close();
	
	Node *first_state = new Node;
	first_state->set_block_number(count+1);
	first_state->set_first_state();
	
	Graph *my_graph = new Graph;
	count=1;
	reading.open(input.c_str()); 
	reading >> row >> column >> size >> direction;
	while (!reading.eof()){ 
		first_state->build_matrix(row-1,column-1,size,direction,count);
		reading >> row >> column >> size >> direction;
		count++;
	}
	reading.close();
		
	my_graph->set_root(first_state);

	Node * Temp = new Node;
	Temp = my_graph->C1.front();
	my_graph->C1.pop();
	
	print2file(writing, first_state);
	
	if (bfsORdfs == "bfs"){
		t=clock();
		state_transition_funcforBFS(my_graph, Temp, writing);
		cout<< "BFS" << endl;
		cout<<"the number of nodes generated: "<< generated_node << endl << "BFS Running time :"  << static_cast<float>(clock()-t)/CLOCKS_PER_SEC <<" seconds " << endl ;
		cout<< "the maximum number of nodes kept in the memory: "<< node_kept_in_memory << endl;
	}
		
	else if (bfsORdfs == "dfs"){
		t=clock();
		state_transition_funcforDFS(my_graph, Temp, writing);
		cout<< "DFS" << endl;
		cout<< "the number of nodes generated: "<< generated_node << endl << "DFS Running time :"  << static_cast<float>(clock()-t)/CLOCKS_PER_SEC <<" seconds "<< endl;
		cout<< "the maximum number of nodes kept in the memory: "<< node_kept_in_memory << endl;
	}
		
	else
		cout << "Invalid parameter";
	
	writing.close();
	return 0;
}



