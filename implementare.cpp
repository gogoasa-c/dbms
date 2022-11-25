//aici implementam clasele si functiile propriu-zis
#include "clase_si_functii.h"

using namespace std;




Table::Table() {

}

Table::Table(string* word) { //pt coloanele tabelului/capul de tabel
	int size = stoi(word[0]);
	int i = 3; //incepe cu poz 3 unde sunt efectiv argumentele lui create table
	this->name = word[i++]; //ia numele de pe poz 3 si creste i
	while(i <= size) { //ia fiecare nume de coloana, dataType, dataSize, dataSize, implicitValue si le baga in vectorii aferenti
		this->tableHead.push_back(word[i++]); 
		this->dataType.push_back(word[i++]);
		this->dataSize.push_back(stoi(word[i++]));
		this->implicitValue.push_back(word[i++]);
	}
}

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
	int controlSize = 100;											//controlam size-ul array-ului de string alocat dinamic
	string* word = new string[controlSize];							//nota: pt introducerea din fisiere, comenzile for vi despartite intre ele prin enter ;; word[index] = ""
	string* aux = NULL;
	int i, numberWords = 0, k;										//i = initial contor apoi index pt a cata litera din string ;; numberWords = index pt al catelea cuvant formam ;; k = index similar lui numberWords dar folosim pt resize de word prin ajutorul lui aux 
	word[0] = to_string(numberWords);								//!!!ATENTIE!!! cuvant[0] va tine NR DE CUVINTE (pt a folosi in alocari dinamice vom folosi **stoi(cuvant[0])**
	unsigned int startedTyping = 0;									//ne ajuta sa ignoram multiple space-uri, pt a nu da eroare usor
	for (i = 0; i < userInput.size(); i++) {
		if (userInput[i] != ' ') {
			startedTyping++;
		}
		if (startedTyping) {										//adica != 0
			numberWords++;											//odata ce nu avem space-uri, se ajunge la primul cuvant, apoi al doilea si tot asa
			word[0] = to_string(numberWords);						//word[0] = "5". stoi(word[5] == int 5); IMPORTANT! vom folosi valoarea stocata la word[0] pt a sti cate argumente avem. daca sunt 5, argumentele se vor afla pe pozitiile interval [1, 5]
			if (numberWords >= controlSize) {						//pentru alocare dinamica
				string* aux = new string[controlSize];
				for (k = 0; k < controlSize; k++) {
					aux[k] = word[k];
				}
				controlSize += 100;
				delete[] word;
				word = new string[controlSize];
				for (k = 0; k < controlSize - 100; k++) {
					word[k] = aux[k];
				}
			}
			while (userInput[i] != ' ' && i < userInput.size()) {
				word[numberWords] += userInput[i++];				//cat timp nu avem space-uri, adugam literele la cuvantul numberWords pt a forma intregul argument cuvant[numberWords]
			}
			startedTyping = 0;										//s-a ajuns la space, astfel ca incetam tastarea/adugarea argumentului trecut si trecem mai departe
		}
	}

	//!!!NU UITAM SA DEZALOCAM MEMORIA DUPA CE NU MAI AVEM NEVOIE DE VECTORUL DE CUVINTE!!!
 
	//delete[] word													//asta se va face probabil in constructorii din clasele care isi creaza metodele pe baza argumentelor functiilor sql
	delete[] aux;
	return word;
}

int identify_command_type(string* word, vector<Table>& tables) {
	if (word[2] == "table") {
		if (word[1] == "create") {
			Table currTable(word);
			tables.push_back(currTable);
		}
		else if(word[1] == "drop") {
			for (int i = 0; i < tables.size(); i++) {
				(tables[i].name)
			}
		}
		else {

		}
	}
	//if (word[2] == "index") return 999;							//optional conform cerintei
	if (word[1] == "insert") {

	}
	
	if (word[1] == "select") return 2;
	if (word[1] == "update") return 3;
	if (word[1] == "delete") return 4;
	
	return -1;
}