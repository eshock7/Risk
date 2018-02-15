#include<iostream>
#include<time.h>
#include<cstdlib>
using namespace std;

// attack:
//   roll 3x2 dice
//   calculate player loss

// battle_over:
//   attacker_count <=2  or defender_count == 0

// battle_win:
//   attacker_count > defender_count

// sim_battle:
//   store player count
//   do call attack
//   until battle_over
//   restore player count
//   return battle_win

// run_full_sim:
//   for i = 1 to 10000
//     call sim_battle
//     tally win/lose
//   print wins divided by 10000 as %

// real_battle:
//   ask attacker & defender soldier count
//   do
//     call run_full_sim
//     ask if player wants to attack
//     if no, break
//     call attack
//   until battle_over

void initdice(){
	srand(unsigned(time(NULL)));
}
int rolldice(){
	return (rand() % 6) + 1;
}
void swap(int array[], int x, int y){
	int temp;
	temp = array[x];
	array[x] = array[y];
	array[y] = temp;
}
const int numrolls = 3;
int main(){
	int attacker[numrolls];
	int defender[numrolls];
	initdice();
	for (int i = 0; i < numrolls; i++) {
		attacker[i] = rolldice();
		defender[i] = rolldice();
	}
	for (int i = 0; i < numrolls - 1; i++) {
		for (int j = 0; j < numrolls - i - 1; j++){
			if (attacker[j] > attacker[j + 1]){
				swap(attacker, j, j + 1);
			}
		}
	}
	for (int i = 0; i < numrolls - 1; i++) {
		for (int j = 0; j < numrolls - i - 1; j++){
			if (defender[j] > defender[j + 1]){
				swap(defender, j, j + 1);
			}
		}
	}
	cout << (attacker[0] > defender[0] ? "attacker" : "defender") << " wins first battle " << attacker[0] << " to " << defender[0] << "\n";
	cout << (attacker[1] > defender[1] ? "attacker" : "defender") << " wins second battle " << attacker[1] << " to " << defender[1] << "\n";
	cout << (attacker[2] > defender[2] ? "attacker" : "defender") << " wins last battle " << attacker[2] << " to " << defender[2] << "\n";

	int f;
	cin >> f;
}