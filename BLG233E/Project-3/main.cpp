#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "queue.h" 
#include "stack.h"
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

queue q;
void swap(int *, int *);
void random(int [], int);
void main_operation();

int main()
{
	
	q.create();
	int dizi[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
				  32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52 };

	int i, n = 52;
	random(dizi, n);

	for (i = 0; i < 52; i++){

		if (dizi[i] == 1) q.enqueue((char *)"S:A");
		
		else if (dizi[i] == 2) q.enqueue((char *)"S:2");

		else if (dizi[i] == 3) q.enqueue((char *)"S:3");

		else if (dizi[i] == 4) q.enqueue((char *)"S:4");

		else if (dizi[i] == 5) q.enqueue((char *)"S:5");

		else if (dizi[i] == 6) q.enqueue((char *)"S:6");

		else if (dizi[i] == 7) q.enqueue((char *)"S:7");

		else if (dizi[i] == 8) q.enqueue((char *)"S:8");

		else if (dizi[i] == 9) q.enqueue((char *)"S:9");
	
		else if (dizi[i] == 10) q.enqueue((char *)"S:10");

		else if (dizi[i] == 11) q.enqueue((char *)"S:J");

		else if (dizi[i] == 12) q.enqueue((char *)"S:Q");

		else if (dizi[i] == 13) q.enqueue((char *)"S:K");   // 
		
		else if (dizi[i] == 14)	q.enqueue((char *)"C:A");

		else if (dizi[i] == 15)	q.enqueue((char *)"C:2");

		else if (dizi[i] == 16) q.enqueue((char *)"C:3");

		else if (dizi[i] == 17) q.enqueue((char *)"C:4");

		else if (dizi[i] == 18)	q.enqueue((char *)"C:5");

		else if (dizi[i] == 19) q.enqueue((char *)"C:6");

		else if (dizi[i] == 20) q.enqueue((char *)"C:7");

		else if (dizi[i] == 21)	q.enqueue((char *)"C:8");

		else if (dizi[i] == 22) q.enqueue((char *)"C:9");

		else if (dizi[i] == 23) q.enqueue((char *)"C:10");

		else if (dizi[i] == 24) q.enqueue((char *)"C:J");

		else if (dizi[i] == 25) q.enqueue((char *)"C:Q");

		else if (dizi[i] == 26)	q.enqueue((char *)"C:K");   //
		
		else if (dizi[i] == 27)	q.enqueue((char *)"D:A");

		else if (dizi[i] == 28)	q.enqueue((char *)"D:2");

		else if (dizi[i] == 29)	q.enqueue((char *)"D:3");

		else if (dizi[i] == 30)	q.enqueue((char *)"D:4");

		else if (dizi[i] == 31)	q.enqueue((char *)"D:5");

		else if (dizi[i] == 32)	q.enqueue((char *)"D:6");

		else if (dizi[i] == 33)	q.enqueue((char *)"D:7");

		else if (dizi[i] == 34)	q.enqueue((char *)"D:8");

		else if (dizi[i] == 35)	q.enqueue((char *)"D:9");

		else if (dizi[i] == 36)	q.enqueue((char *)"D:10");

		else if (dizi[i] == 37)	q.enqueue((char *)"D:J");

		else if (dizi[i] == 38)	q.enqueue((char *)"D:Q");

		else if (dizi[i] == 39)	q.enqueue((char *)"D:K");   //

		else if (dizi[i] == 40)	q.enqueue((char *)"H:A");

		else if (dizi[i] == 41)	q.enqueue((char *)"H:2");

		else if (dizi[i] == 42)	q.enqueue((char *)"H:3");

		else if (dizi[i] == 43)	q.enqueue((char *)"H:4");

		else if (dizi[i] == 44)	q.enqueue((char *)"H:5");

		else if (dizi[i] == 45)	q.enqueue((char *)"H:6");

		else if (dizi[i] == 46)	q.enqueue((char *)"H:7");

		else if (dizi[i] == 47)	q.enqueue((char *)"H:8");

		else if (dizi[i] == 48)	q.enqueue((char *)"H:9");

		else if (dizi[i] == 49)	q.enqueue((char *)"H:10");

		else if (dizi[i] == 50)	q.enqueue((char *)"H:J");   //11
		
		else if (dizi[i] == 51)	q.enqueue((char *)"H:Q");   //12

		else if (dizi[i] == 52)	q.enqueue((char *)"H:K");   //13
	
	}

	main_operation();
	
	return 0;
}

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void random(int array[], int n){
	srand(time(NULL));
	int j, i = n - 1;

	if (i == 0)
		return;

	else{
		j = rand() % (i + 1);
		swap(&array[i], &array[j]);
		random(array, n - 1);
	}
}

void main_operation(){

	ofstream output;
	output.open("output.txt");

	if (!output.is_open())
		cout << "Output file could not be opened" << endl;

	stack s;
	s.create();

	queue fortune;
	fortune.create();

	char *a;
	int i;
	string var;
	bool bbreak=false;

	node *temp = q.front;
	int k=1;

	output << "Shuffled deck :"<<endl ;
	while (k<53){
		output <<k++ <<":" << temp->data <<endl;
		temp = temp->next;
	}
	output << "Fortune - telling steps :"<<endl;

	while (!q.isempty()){
	
		for (i = 1; i <=13; i++){
				
			if (q.count==0){
				bbreak = true;
				break;
			}

			var = q.dequeue();
			      
			int x = var.length() + 1;
			a = new char[x];

			int j;

			for ( j = 0; j < x; j++){ // string den char pointer a attýk.
				a[j] = var[j];
			}
			a[j] = '\0';
			
			s.push(a);
			output << i << ":"<<a <<" ";
			if (i==10 && a[3]=='0' && a[2]=='1'){ // 10

				fortune.enqueue(s.pop());
				i = 0;
				output << "match" <<endl;
				while (s.sayac > 0){
					q.enqueue(s.pop());
				}
			}
			else if (i == 11 && a[2] == 'J'){ //11
				
				fortune.enqueue(s.pop());
				i = 0;
				output << "match" << endl;
				while (s.sayac != 0){
					q.enqueue(s.pop());
				}

			}

			else if (i == 12 && a[2] == 'Q'){

				fortune.enqueue(s.pop());
				i = 0;
				output << "match" << endl;
				while (s.sayac != 0){
					q.enqueue(s.pop());
				}

			}

			else if (i == 13){

				if (a[2] == 'K'){
					fortune.enqueue(s.pop());
					i = 0;
					output << "match" << endl;
					while (s.sayac > 0){
						q.enqueue(s.pop());
					}
				}
				else{
					while (s.sayac > 0){
						s.pop();
					}
					output << "unmatch" << endl;
					i = 0;
				}
			}

			else if (i == 1 && a[2] == 'A'){
				fortune.enqueue(s.pop());
				i = 0;
				output << "match" << endl;
				while (s.sayac > 0){
					q.enqueue(s.pop());
				}

			}

			else if ( /*i!=10 && i!=11 && i!=12 && i!=13  &&*/ i!=1 && i == (a[2] - '0') ){ // 1 2 3 4 5 6 7 8 9 için

				fortune.enqueue(s.pop());
				i = 0;
				output << "match" << endl;
				while (s.sayac>0){
					q.enqueue(s.pop());
				}

			}
			else{
				output << "unmatch" << endl;
			}
			 			
		}
		if (bbreak) break;
		
	}

	while (s.sayac>0){  // stack te kalanlarý pop ediyoruz eðer varsa.
		s.pop();
	} 
	
	int sum = 0;
	
	output <<"Fortune Results:" << endl;
	while (fortune.count != 0){
		
		var = fortune.dequeue();

		int x = var.length() + 1;
		a = new char[x];

		int j;

		for (j = 0; j < x; j++){ // string den char pointer a attýk.
			a[j] = var[j];
		}
		a[j] = '\0';

		if (var[3] == '0' && var[2]=='1')
			sum += 10;

		if (var[2] == '2')
			sum += 2;

		if (var[2] == 'A')
			sum += 1;

		if (var[2] == '3')
			sum += 3;

		if (var[2] == '4')
			sum += 4;

		if (var[2] == '5')
			sum += 5;

		if (var[2] == '6')
			sum += 6;

		if (var[2] == '7')
			sum += 7;

		if (var[2] == '8')
			sum += 8;

		if (var[2] == '9')
			sum += 9;

		if (var[2] == 'J')
			sum += 11;

		if (var[2] == 'Q')
			sum += 12;

		if (var[2] == 'K')
			sum += 13;
		

		output << a << endl;

	}

	output << "Sum:"<<sum;
	
	if (sum<50)
		output <<endl << "Bad Luck!" ;

	else
		output <<endl << "Fortune will come true";

	output.close();
}
