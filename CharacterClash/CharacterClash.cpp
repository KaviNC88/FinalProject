//This program makes files on characters and pits them against one another
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void characterCreator(string); // prototyping functions
string fileNameMaker(string);
void fight(string, string);

int main() {
	char createACharacter;  //creating all my variables
	int characterCount, fighter, opponent;
	string fighterName, opponentName, count;
	ofstream fout;
	ifstream fin;

	cout << "Welcome to character clash!" << endl << "Would you like to create a new character(y or n)? ";
	cin >> createACharacter;

	while (createACharacter != 'y' && createACharacter != 'n') { // loop makes sure they answer either y or n
		cout << "(y or n): ";
		cin >> createACharacter;
		cout << endl;
	}

	if (createACharacter == 'y') {
		fin.open("characterCounter.txt"); 
		fin >> characterCount; //finds how many characters there already are
		fin.close(); 

		characterCount++;
		string fileName = fileNameMaker(to_string(characterCount));

		fout.open("characterCounter.txt"); 
		fout << characterCount; //updates amount of characters
		fout.close();

		characterCreator(fileName);
	}

	fin.open("characterCounter.txt"); 
	fin >> characterCount; // gets the character count for line 47
	fin.close();
	cout << "Time to pick fighters!" << endl << "What number fighter will you chose(1 through " << characterCount << ")? ";
	cin >> fighter;
	while (fighter < 1 || fighter > characterCount) {
		cout << "Please selecet a number between 1 and " << characterCount << endl; // makes sure they select a valid fighter number
	}


	string fighterFile = fileNameMaker(to_string(fighter));

	fin.open(fighterFile);
	fin >> fighterName; // finds the name of the fighter you chose
	fin.close();

	cout << "You chose " << fighterName << "!" << " What number opponent will you choose(1 through " << characterCount << ")? ";
	cin >> opponent;
	while (opponent < 1 || opponent > characterCount) {
		cout << "Please selecet a number between 1 and " << characterCount << endl; // makes sure they select a valid fighter number
	}

	string opponentFile = fileNameMaker(to_string(opponent));

	fin.open(opponentFile);
	fin >> opponentName; // finds the name of the opponent you chose
	fin.close();

	cout << "Your opponent is " << opponentName << "!" << endl << "Time to Fight!!" << endl;

	fight(fighterFile, opponentFile);

	return 0;
}

void characterCreator(string fileName) { // creates a new file for a new character, includes name and stats
	string name;
	int attack, defense;
	ofstream fout;

	cout << "What is your character's name?" << endl;
	cin >> name;

	cout << "What is " << name << "'s Attack stat?" << endl;
	cin >> attack;

	cout << "What is " << name << "'s Defense stat?" << endl;
	cin >> defense;

	fout.open(fileName);
	if (fout.is_open()) {
		fout << name << "\t" << attack << "\t" << defense; 
	}
	fout.close();
}

string fileNameMaker(string number) { // makes a file name out of an integer, for ease of access
	string fileName = "character_" + number + ".txt"; 
	return fileName;
}

void fight(string fighter, string opponent) {
	string fighterName, opponentName;
	int fAttack, fDefense, oAttack, oDefense;
	bool fDead = false, oDead = false;
	ifstream fin;

	fin.open(fighter);
	fin >> fighterName >> fAttack >> fDefense; 
	fin.close();

	fin.open(opponent);
	fin >> opponentName >> oAttack >> oDefense;
	fin.close();

	if (fAttack > oDefense) { // compares the attack and defense to see who, if any, dies
		cout << fighterName << " struck down " << opponentName << "!" << endl;
		oDead = true;
	}
	if (oAttack > fDefense) {
		cout << opponentName << " struck down " << fighterName << "!" << endl;
		fDead = true;
	}


	if (!fDead && oDead) { // evaluates the state of both fighters to determine the outcome of the battle
		cout << "The fight goes to " << fighterName << "!\nYou win!!";
	}
	else if (fDead && !oDead) {
		cout << "The fight goes to " << opponentName << "!\nYou Lose!!";
	}
	else if (fDead && oDead) {
		cout << "Both fighters are dead, and the fight ends in a draw!";
	}
	else if (!fDead && !oDead) {
		cout << "Both fighters still stand, and the fight ends in a draw";
	}
}