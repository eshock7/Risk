#include<iostream>
#include<sstream>
#include<string>
#include<time.h>
#include<cstdlib>
using namespace std;

void initdice();
void realbattle();
int runfullsim(int attacksoldiers, int defendsoldiers);
bool simbattle(int attacksoldiers, int defendsoldiers);
void attack(int *ptr_attacksoldiers, int *ptr_defendsoldiers,bool print);
void attackrolls(int attackernumrolls, int defendernumrolls, int *ptr_attacklosses, int *ptr_defendlosses, bool print);
bool battleover(int attacksoldiers, int defendsoldiers);
int rolldice();
void swap(int array[], int x, int y);

int main(){
	initdice();
	realbattle();
	string temp;
	cin >> temp;
	return 0;
}

// Dice and sorting utility functions.
void initdice(){
	srand(unsigned(time(NULL)));
}

// real_battle:
//   ask attacker & defender soldier count
//   do
//     call run_full_sim
//     ask if player wants to attack
//     if no, break
//     call attack
//   until battle_over
void realbattle(){
	int attacksoldiers = 0;
	int defendsoldiers = 0;
	while (attacksoldiers < 2){
		cout << "How many soldiers are attacking? ";
		cin >> attacksoldiers;
		if (cin.fail()){
			cin.clear();
			cin.ignore(80, '\n');
		}
	}
	while (defendsoldiers < 1){
		cout << "How many soldiers are defending? ";
		cin >> defendsoldiers;
		if (cin.fail()){
			cin.clear();
			cin.ignore(80, '\n');
		}
	}
	
	do{
		string response = "";
		cout << "There are " << attacksoldiers << " attacking.\n";
		cout << "There are " << defendsoldiers << " defending.\n";
		//RUN SIMULATION
		int percentwins = runfullsim(attacksoldiers, defendsoldiers);
		cout<< "You have a "<<percentwins<<"% chance of winning the battle.\n";
		while (response != "y" && response != "n"){
			cout << "Do you want to attack?(y/n) ";
			cin >> response;
		}
		if (response == "n")
			break;
		attack(&attacksoldiers, &defendsoldiers,true);
	} while (!battleover(attacksoldiers, defendsoldiers));
	cout << "The battle is over!  Attacker has " << attacksoldiers << ". Defender has " << defendsoldiers << ".\n";
	if (defendsoldiers == 0)
		cout << "Attacker wins!\n";
	else
		cout << "Defender wins!\n";
}

// run_full_sim:
//   for i = 1 to 10000
//     call sim_battle
//     tally win/lose
//   print wins divided by 10000 as %
int runfullsim(int attacksoldiers, int defendsoldiers){
	int wins=0;
	for (int i = 0; i < 100000; i++){
		if (simbattle(attacksoldiers, defendsoldiers))
			wins++;
	}
	return 100*wins / 100000;
}
// sim_battle:
//   store player count
//   do call attack
//   until battle_over
//   restore player count
//   return battle_win
bool simbattle(int attacksoldiers, int defendsoldiers){
	do{
		attack(&attacksoldiers, &defendsoldiers,false);
	} while (!battleover(attacksoldiers, defendsoldiers));
	if (defendsoldiers == 0)
		return true;
	else
		return false;
}

// Roll dice.  Deduct soldiers by loss counts.
void attack(int *ptr_attacksoldiers, int *ptr_defendsoldiers,bool print){
	int attacksoldiers = *ptr_attacksoldiers;
	int defendsoldiers = *ptr_defendsoldiers;
	int attacklosses, defendlosses;
	attackrolls(attacksoldiers - 1, defendsoldiers, &attacklosses, &defendlosses,print);
	if (print)
		cout << "Attacker lost " << attacklosses << " soldiers and defender lost " << defendlosses << " soldiers.\n";
	attacksoldiers -= attacklosses;
	defendsoldiers -= defendlosses;
	*ptr_attacksoldiers = attacksoldiers;
	*ptr_defendsoldiers = defendsoldiers;
}

// Take the number of soldiers who can attack or defend.  Limit 3.  Roll dice and sort descending.
// Compare pairs of dice.  Attacker must have greater to win.  Tie goes to defender.
// Count losses.
void attackrolls(int attackernumrolls,int defendernumrolls, int *ptr_attacklosses, int *ptr_defendlosses,bool print){
	const int maxrolls = 3;
	int attacker[maxrolls];
	int defender[maxrolls];
	int usablerolls;
	int attackerlosses = 0;
	int defenderlosses = 0;

	if (attackernumrolls > maxrolls)
		attackernumrolls = maxrolls;
	if (defendernumrolls > maxrolls)
		defendernumrolls = maxrolls;
	if (attackernumrolls < defendernumrolls)
		usablerolls = attackernumrolls;
	else
		usablerolls = defendernumrolls;

	for (int i = 0; i < attackernumrolls; i++)
		attacker[i] = rolldice();
	for (int i = 0; i < defendernumrolls; i++)
		defender[i] = rolldice();

	for (int i = 0; i < attackernumrolls - 1; i++) {
		for (int j = 0; j < attackernumrolls - i - 1; j++){
			if (attacker[j] < attacker[j + 1]){
				swap(attacker, j, j + 1);
			}
		}
	}
	for (int i = 0; i < defendernumrolls - 1; i++) {
		for (int j = 0; j < defendernumrolls - i - 1; j++){
			if (defender[j] < defender[j + 1]){
				swap(defender, j, j + 1);
			}
		}
	}
	if (print){
		cout << "Attacker rolled";
		for (int i = 0; i < attackernumrolls; i++) {
			cout << " " << attacker[i];
		}
		cout << ".\n";
		cout << "Defender rolled";
		for (int i = 0; i < defendernumrolls; i++) {
			cout << " " << defender[i];
		}
		cout << ".\n";
	}
	for (int i = 0; i < usablerolls; i++) {
		if (attacker[i] > defender[i])
			defenderlosses++;
		else
			attackerlosses++;
	}
	*ptr_attacklosses = attackerlosses;
	*ptr_defendlosses = defenderlosses;
}

// Take the number of soldiers for each side.  Battle isn't over until attacker has 1 or defender has 0.
// battle_over:
//   attacker_count <2  or defender_count == 0
bool battleover(int attacksoldiers, int defendsoldiers){
	if (attacksoldiers < 2 || defendsoldiers == 0)
		return true;
	else
		return false;
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
