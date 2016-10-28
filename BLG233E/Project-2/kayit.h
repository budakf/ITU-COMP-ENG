/*
* Student Name: Fatih Budak
* Student ID : 150130006
* Date: 07/11/2015
*/

struct transaction{
	char transaction_name[15];
	transaction *next;
};

struct customer{

	char name[15];
	char surname[15];
	char customer_type;
	char number_of_transaction;
	transaction *transaction_ptr;
	customer *next;
};
