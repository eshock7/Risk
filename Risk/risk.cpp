#include<iostream>
#include<time.h>
#include<cstdlib>
using namespace std;

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
	int rolls[numrolls];
	initdice();
	for (int i = 0; i < numrolls; i++) {
		rolls[i] = rolldice();
	}
	for (int i = 0; i < numrolls - 1; i++) {
		for (int j = 0; j < numrolls - i - 1; j++){
			if (rolls[j] > rolls[j + 1]){
				swap(rolls, j, j + 1);
			}
		}
	}
	cout << rolls[0] << " is the smallest roll\n";
	cout << rolls[1] << " is the middle roll\n";
	cout << rolls[2] << " is the greatest roll\n";

	int f;
	cin >> f;
}