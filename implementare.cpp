//aici implementam clasele si functiile propriu-zis
#include "clase_si_functii.h"
#include <iostream>
#include <string>
#define REAL_SIZE 100
using namespace std;

string take_user_input_and_convert_lowercase()
{
	string userInput = "";
	getline(cin, userInput);
	for (int i = 0; i < userInput.size(); i++) {
		if (userInput[i] >= 'A' && userInput[i] <= 'Z') {
			userInput[i] += 32;										//value of 'a' - 'A'
		}
	}
	
	return userInput;
}

string* split_string_into_words(string userInput)
{
	string word[REAL_SIZE] = {""};									//aici este probabil sa trebuiasca sa alocam dinamic daca permitem introducerea a prea multe coloane in tabele. nota: pt introducerea din fisiere, comenzile for vi despartite intre ele prin enter
	int i;
	/*for (i = 0; i < REAL_SIZE; i++) {								//daca alocam dinamic	
		word[i] = "";
	}*/
	int j = 0;														//index pt al catelea cuvant formam 
	word[0] = j;													//!!!ATENTIE!!! cuvant[0] va tine NR DE CUVINTE (pt a folosi in alocari dinamice vom folosi **stoi(cuvant[0])**
	//int controlSize = 0;											//controlam size-ul array-ului de string alocat dinamic
	unsigned int startedTyping = 0;									//ne ajuta sa ignoram multiple space-uri, pt a nu da eroare usor
	for (i = 0; i < userInput.size(); i++) {
		if (userInput[i] != ' ') {
			startedTyping++;
		}
		if (startedTyping) {										//adica != 0
			j++;													//odata ce nu avem space-uri, se ajunge la primul cuvant, apoi al doilea si tot asa
			word[0] = j;
			/*if (j >= controlSize) {								//pentru alocare dinamica
				controlSize += 100;

				delete[] word;
				word = new string[controlSize];
			}*/
			while (userInput[i] != ' ' && i < userInput.size()) {
				word[j] += userInput[i++];						//cat timp nu avem space-uri, adugam literele la cuvantul j pt a forma intregul argument cuvant[j]
			}
			startedTyping = 0;										//s-a ajuns la space, astfel ca incetam tastarea/adugarea argumentului trecut si trecem mai departe
		}
	}

	return word;
}

int identify_command_type(string* word) {
	if (word[2] == "table") return 0;
	//if (word[2] == "index") return 999; //optional conform cerintei
	if (word[1] == "insert") return 1;
	if (word[1] == "select") return 2;
	if (word[1] == "update") return 3;
	if (word[1] == "delete") return 4;

	return -1;
}