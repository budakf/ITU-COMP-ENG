struct Node{
	char * data;
	Node *next;
};

struct stack{
	int sayac;
	Node *head;
	void create();
	bool isempty();
	void push(char *);
	char * pop();


};
