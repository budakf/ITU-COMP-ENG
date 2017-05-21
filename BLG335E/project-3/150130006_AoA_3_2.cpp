/*

Fatih Budak
150130006

*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <cmath>
#include <ctime>

#define NN 10000

using namespace std;

class logs{
private:
	int game_id;
	char clan_name;
	int attacker_id;
	int attacked_id;

public:
	logs();
	~logs();

	int get_game_id();
	char get_clan_name();
	int get_attacker_id();
	int get_attacked_id();

	void set_game_id(int);
	void set_clan_name(char);
	void set_attacker_id(int);
	void set_attacked_id(int);

};

logs::logs(){}
logs::~logs(){}

int logs::get_game_id(){
	return game_id;
}
char logs::get_clan_name(){
	return clan_name;
}
int logs::get_attacker_id(){
	return attacker_id;
}
int logs::get_attacked_id(){
	return attacked_id;
}

void logs::set_game_id(int id){
	game_id = id;
}
void logs::set_clan_name(char name){
	clan_name = name;
}
void logs::set_attacker_id(int _attacker_id){
	attacker_id = _attacker_id;
}
void logs::set_attacked_id(int _attacked_id){
	attacked_id = _attacked_id;
}


class player{
private:
	int id;
	int cp;

public:
	player();
	~player();
	int get_id();
	int  get_cp();
	void set_id(int);
	void set_cp(int);
};

player::player(){}
player::~player(){}
int player::get_id(){
	return id;
}
int player::get_cp(){
	return cp;
}
void player::set_id(int _id){
	id = _id;
}
void player::set_cp(int _cp){
	cp = _cp;
}

void swap(player &a, player &b){
	player temp;
	temp = a;
	a = b;
	b = temp;
}

void heapify(player *arr, int n, int i){
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && arr[l].get_cp() < arr[largest].get_cp())
		largest = l;

	if (r < n && arr[r].get_cp() < arr[largest].get_cp())
		largest = r;

	if (largest != i){
		swap(arr[i], arr[largest]);
		heapify(arr, n, largest);
	}
}

void heap_sort(player *arr, int n){
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	for (int i = n - 1; i >= 0; i--){
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}

int main(int argc, char * argv[]){

	if (atoi(argv[1]) == 1){
		cout << "in PART B-1"<< endl;
		int temp_id, temp_cp;
		int N = atoi(argv[2]);
		player *A_clan = new player[N]; //
		ifstream reading_a("ClanA.txt");
		ofstream writing_a("A_sorted.txt");
		int i = 0;
		while (i < N){ //
			reading_a >> temp_id >> temp_cp;
			A_clan[i].set_id(temp_id);
			A_clan[i].set_cp(temp_cp);
			i++;
		}

		clock_t t;
		t= clock();
		heap_sort(A_clan, N);
		t = clock() - t;
		cout << "Running Time: " << (double)t / CLOCKS_PER_SEC <<" seconds "<< endl;
		
		i = 0;
		while (i < N){
			writing_a << A_clan[i].get_id() << " " << A_clan[i].get_cp() << endl;
			i++;
		}
	}

	else if (atoi(argv[1]) == 2){
		cout << "in PART B-2"<< endl;
		int game_id, attacker_id, attacked_id;
		char clan_name;

		int temp_id, temp_cp;
		player *A_clan = new player[NN]; //
		player *B_clan = new player[NN]; //
		logs *LOG = new logs[1000];

		ifstream reading_a("ClanA.txt");
		ifstream reading_b("ClanB.txt");
		ifstream reading_game("gamelogs.txt");
		ofstream writing_a_results("A_results.txt");
		
		int i = 0;
		while (i < NN){ //
			reading_a >> temp_id >> temp_cp;
			A_clan[i].set_id(temp_id);
			A_clan[i].set_cp(temp_cp);

			reading_b >> temp_id >> temp_cp;
			B_clan[i].set_id(temp_id);
			B_clan[i].set_cp(temp_cp);
			
			if (i < 1000){
				reading_game >> game_id >> clan_name >> attacker_id >> attacked_id;
				LOG[i].set_game_id(game_id);
				LOG[i].set_clan_name(clan_name);
				LOG[i].set_attacker_id(attacker_id);
				LOG[i].set_attacked_id(attacked_id);
			}
			
			i++;			
		}
		
		heap_sort(A_clan, NN);
		heap_sort(B_clan, NN);
		
		i = 0;
		int attacker;
		int attacked;
		int x;
		int y;
		while (i < 1){
			attacker = LOG[i].get_attacker_id();
			attacked = LOG[i].get_attacked_id();

			if (LOG[i].get_clan_name() == 'A'){
				if (attacker == 0){
					A_clan[attacker].set_cp(A_clan[attacker].get_cp() + (B_clan[attacked].get_cp() / 2) );
					x= B_clan[attacked].get_cp() - (B_clan[attacked].get_cp() / 2);
					if (x < 0)
						B_clan[attacked].set_cp(0);
					else
						B_clan[attacked].set_cp(x);
				}

				else if (attacker >= 1 && attacker <= 7){
					A_clan[attacker].set_cp(A_clan[attacker].get_cp() + 500);
					x = B_clan[attacked].get_cp() - 500;
					if (x < 0)
						B_clan[attacked].set_cp(0);
					else
						B_clan[attacked].set_cp(x);
				}

				else if (attacker > 7){
					y = A_clan[attacker].get_cp() + (abs(log(attacker) - log(attacked)) + 1) * 30;
					A_clan[attacker].set_cp(y);
					x = B_clan[attacked].get_cp() - 120;
					if (x < 0)
						B_clan[attacked].set_cp(0);
					else
						B_clan[attacked].set_cp(x);
				}
				
			}
		
			else{
				if (attacker == 0){
					B_clan[attacker].set_cp(B_clan[attacker].get_cp() + (A_clan[attacked].get_cp() / 2));
					x = A_clan[attacked].get_cp() - (A_clan[attacked].get_cp() / 2);
					if (x < 0)
						A_clan[attacked].set_cp(0);
					else
						A_clan[attacked].set_cp(x);
				}

				else if (attacker >= 1 && attacker <= 7){
					B_clan[attacker].set_cp(B_clan[attacker].get_cp() + 500);
					x = A_clan[attacked].get_cp() - 500;
					if (x < 0)
						A_clan[attacked].set_cp(0);
					else
						A_clan[attacked].set_cp(x);
				}

				else if (attacker > 7){
					y = B_clan[attacker].get_cp() + (abs(log(attacker) - log(attacked)) + 1) * 30;
					B_clan[attacker].set_cp(y);
					x = A_clan[attacked].get_cp() - 120;
					if (x < 0)
						A_clan[attacked].set_cp(0);
					else
						A_clan[attacked].set_cp(x);
				}
				
			} 

			heap_sort(A_clan, NN );
			heap_sort(B_clan, NN );
			i++;

		}
				
		int Total_A_Clan = 0;
		int Total_B_Clan = 0;
		i = 0;
		while (i < NN ){
			writing_a_results << A_clan[i].get_id() << " " << A_clan[i].get_cp() << endl;
			Total_A_Clan += A_clan[i].get_cp();
			Total_B_Clan += B_clan[i].get_cp();
			i++;
		}

		cout << "Total Cp of A: " << Total_A_Clan << endl;
		cout << "Total Cp of B: " << Total_B_Clan << endl;

		if (Total_B_Clan>Total_A_Clan){
			cout << "Winner of Tournament is Clan B" << endl;
		}
		else
			cout << "Winner of Tournament is Clan A" << endl;

	
	}
	

	return 0;
}
