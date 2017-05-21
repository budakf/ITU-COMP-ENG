#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>

using namespace std;

struct RBNode{

	string name;  // name is also key of each nodes
	char color;
	int age;
	char gender;
	int num_adult;  //
	int num_non_adult; //
	RBNode *parent;	//points to parent of this node
	RBNode * right;	//points to right-node of this node
	RBNode * left;	//points to left-node of this node

};

class RBTree{

private:
	RBNode *root;

public:
	RBTree();
	~RBTree();
	void set_root(RBNode *);
	RBNode * get_root();
	void Tree_insert(RBTree &, RBNode*);
	void RBInsert(RBTree &, RBNode *);
	int pre_Order(RBNode *, int);
	void print(RBNode *, int);
	void Left_Rotate(RBNode *);
	void Right_Rotate(RBNode *);
	void count_both(RBNode *);
	void n_th_adult(RBNode *, int);
	void n_th_non_adult(RBNode *, int);

};

RBTree::RBTree(){
	this->root = NULL;
}

RBTree::~RBTree(){
	delete this->root;
}

void RBTree::set_root(RBNode * new_node){
	this->root = new RBNode;
	this->root = new_node;
	this->root->color = 'B';
	this->root->parent = NULL;
	this->root->left = NULL;
	this->root->right = NULL;
	this->root->num_non_adult = 0;
	this->root->num_adult = 0;
		
}

RBNode * RBTree::get_root(){ return root; }

void RBTree::n_th_adult(RBNode *_root, int i){

	RBNode * traverse = new RBNode;
	traverse = _root;
	int temp;
	
	if (!traverse)
		return;

	if (traverse->age >= 18){
		if (traverse->left)
			temp = traverse->left->num_adult + 1;
		else
			temp = 1;
	}
	
	else{
		if (traverse->left)
			temp = traverse->left->num_adult;
		else
			temp = 0;
	}
		
	
	if (i == temp) 	
		cout << traverse->name << endl;

	else if (i < temp)	
		n_th_adult(traverse->left, i);

	else 
		n_th_adult(traverse->right, i - temp);
}

void RBTree::n_th_non_adult(RBNode * _root, int i){

	RBNode * traverse = new RBNode;
	traverse = _root;
	int temp;
	bool flag = false;
	
	if (!traverse)
		return;
		
	if (traverse->age < 18){
		if (traverse->left)
			temp = traverse->left->num_non_adult + 1;
		else
			temp = 1;
	}

	else{
		if (traverse->left){
			temp = traverse->left->num_non_adult;
			flag = true;
		}
			
		else
			temp = 0;
	}


	if (i == temp && !flag) 
		cout << traverse->name << endl;
	else if (i == temp && flag)
		cout << traverse->left->name << endl;

	else if(i < temp) 
		n_th_non_adult(traverse->left, i);

	else	
		n_th_non_adult(traverse->right, i - temp);
}

void RBTree::count_both(RBNode * _root){
	RBNode *traverse = new RBNode;
	traverse = _root;

	if (traverse == NULL)
		return;
	
	else{
		if (traverse->age >= 18){
			traverse->num_adult++;
		}
		else{
			traverse->num_non_adult++;
		}
		count_both(traverse->left);
		count_both(traverse->right);
	}

	if (traverse->parent){
		traverse->parent->num_adult += traverse->num_adult;
		traverse->parent->num_non_adult += traverse->num_non_adult;
		//cout << traverse->parent->name << "  " << traverse->parent->num_adult << "  " << traverse->parent->num_non_adult << endl;
	}
}

int RBTree::pre_Order(RBNode *_root, int depth){
	int depthOFnode = depth;

	if (!_root)
		return depthOFnode;
	else{
		this->print(_root, depthOFnode);
		depthOFnode = pre_Order(_root->left, depth + 1);
		depthOFnode = pre_Order(_root->right, depth + 1);
	}

}

void RBTree::print(RBNode * _root, int depth){
	while (depth--)
		cout << "-";
	cout << "(" << _root->color << ") " << _root->name << " " << _root->gender << " " << _root->age << endl; // << "  " << _root->num_adult << " " << _root->num_non_adult
}

void RBTree::Left_Rotate(RBNode * neww){

	RBNode *right_neww = neww->right;

	if (!right_neww)
		return;

	else{
		neww->right = right_neww->left;

		if (neww->right)
			right_neww->parent = neww;

		right_neww->parent = neww->parent;

		if (!neww->parent)
			this->set_root(right_neww);

		else{

			if (neww == neww->parent->left)
				neww->parent->left = right_neww;

			else
				neww->parent->right = right_neww;
		}
	}

	right_neww->left = neww;
	neww->parent = right_neww;
	
}

void RBTree::Right_Rotate(RBNode * neww){

	RBNode *left_neww = neww->left;

	if (!left_neww)
		return;

	else{
		neww->left = left_neww->right;

		if (neww->left)
			left_neww->parent = neww;

		left_neww->parent = neww->parent;

		if (!neww->parent)
			this->set_root(left_neww);

		else{

			if (neww == neww->parent->right)
				neww->parent->right = left_neww;

			else
				neww->parent->left = left_neww;
		}
	}

	left_neww->right = neww;
	neww->parent = left_neww;

}

void RBTree::Tree_insert(RBTree &my_tree, RBNode *new_node){
	RBNode * traverse = root;
	RBNode * neww = new RBNode;
	*neww = *new_node;
	bool root_flag = false; //silinecek
	RBNode * parent_neww;
	RBNode *grand_neww;

	if (!this->get_root()){
		this->set_root(neww);
		//cout << this->get_root()->color << "  " << this->get_root()->name << endl;
		root_flag = true; //silinecek
	}
	else{
		while (traverse){

			if (neww->name[0] <= traverse->name[0]){
				if (!traverse->left){
					traverse->left = neww;
					neww->parent = traverse;
					//cout << neww->color << " L " << traverse->left->name << endl;
					break;
				}
				else if (traverse->left)
					traverse = traverse->left;	
			}
			else{
				if (! traverse->right){
					traverse->right = neww;
					neww->parent = traverse;
					//cout << neww->color << " R  " << traverse->right->name << endl;
					break;
				}

				else if (traverse->right)
					traverse = traverse->right;
			}

		}
	}

	//////////////////// For RB Tree, fixing operations /////////////////////////
	
	while (neww != this->get_root() && neww->parent->color == 'R'){
		parent_neww = neww->parent;				
		grand_neww = neww->parent->parent;

		if (parent_neww == grand_neww->left){
			RBNode *uncle = grand_neww->right;
			if (uncle){
				if (uncle->color == 'R'){  
					uncle->color = 'B';
					grand_neww->color = 'R';		// CASE 1 Recoloring 
					parent_neww->color = 'B';
					neww = grand_neww;
				}
			}
			else{
				if (neww == parent_neww->right){  
					neww = parent_neww;
					this->Left_Rotate(neww);			// CASE 2 Left Rotate
					parent_neww = neww->parent;
				}
				neww = parent_neww;
				this->Right_Rotate(grand_neww);  // CASE 3 Right Rotate
				grand_neww->color = 'R';
				parent_neww->color = 'B';
		   }
		 
		}
		
		else{
			RBNode * uncle = grand_neww->left;
			if (uncle){
				if (uncle->color == 'R'){			
					grand_neww->color = 'R';
					uncle->color = 'B';					//CASE 1 Recoloring
					parent_neww->color = 'B';
					neww = grand_neww;
				}
			}
			else{
				if (neww == parent_neww->left){  
					neww = parent_neww;
					this->Right_Rotate(neww);	// CASE 2  Right Rotate
					parent_neww = neww->parent;
				}
				neww = parent_neww;
				this->Left_Rotate(grand_neww);   //CASE 3	Left Rotate	
				parent_neww->color = 'B';
				grand_neww->color = 'R';
				
			}
		}

	}

	this->get_root()->color = 'B';

}

void RBTree::RBInsert(RBTree &my_tree, RBNode *new_node){
	Tree_insert(my_tree, new_node);
}

int main(int argc, char ** argv){

	string filename = argv[1];
	RBTree my_rbtree;
	RBNode *new_rbnode = new RBNode;
	string name;
	char gender;
	int age;
	ifstream reading( filename.c_str()); // "input.txt"

	while (!reading.eof()){

		reading >> name >> gender >> age;
		new_rbnode->name = name;
		new_rbnode->gender = gender;
		new_rbnode->age = age;
		new_rbnode->color = 'R';
		new_rbnode->left = NULL;
		new_rbnode->right = NULL;
		new_rbnode->parent = NULL;
		new_rbnode->num_adult = 0;
		new_rbnode->num_non_adult = 0;

		my_rbtree.RBInsert(my_rbtree, new_rbnode);
		//cout << new_rbnode.name << "  " << new_rbnode.gender << "  " << new_rbnode.age << endl;	

	}
	my_rbtree.count_both(my_rbtree.get_root());
	my_rbtree.pre_Order(my_rbtree.get_root(), 0);
	cout << endl << "5th Adult: ";
	my_rbtree.n_th_adult(my_rbtree.get_root(), 5);
	cout << "3rd Non-Adult: ";
	my_rbtree.n_th_non_adult(my_rbtree.get_root(), 3);

	return 0;
}
