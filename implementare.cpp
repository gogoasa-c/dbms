//aici implementam clasele si functiile propriu-zis
#include "clase_si_functii.h"

using namespace std;

bool push_back_flag = false;

Entry::Entry(const Entry& e) {
	this->numberArguments = e.numberArguments;
	this->arguments = new string[this->numberArguments];
	for (int i = 0; i < numberArguments; i++) {
		this->arguments[i] = e.arguments[i];
	}
}

Entry::Entry() {
	this->arguments = nullptr;
	this->numberArguments = 0;
}

Entry::Entry(int newNumberArguments):numberArguments(newNumberArguments) { 
	this->arguments = new string[numberArguments];

}

Entry::Entry(int newNumberArguments, string* newArguments) {
	try{
		if ((stoi(newArguments[0]) - 4) != newNumberArguments) { //scad 4 ca sa nu numaram si primele 4 cuvinte din comanda: insert into table_name values 
			exception e("\nNumar invalid de argumente!");
			throw e;
		}
		this->numberArguments = newNumberArguments;
		this->arguments = new string[numberArguments];
		int j = 0;
		for (int i = 5; i <= stoi(newArguments[0]); i++) { //si incepem cu al 5-lea cuvant pana la final
			this->arguments[j] = newArguments[i];
			++j;
		}
	}
	catch (exception e) {
		cout << e.what();
		this->numberArguments = 0;
		this->arguments = nullptr;
	}
}

Entry::~Entry() {
	if (this->arguments != nullptr ) {
		delete[] this->arguments;
	}
}

Table::Table(const Table& t) {
	this->name = t.name;
	this->tableHead = t.tableHead;
	this->dataType = t.dataType;
	this->dataSize = t.dataSize;
	this->implicitValue = t.implicitValue;
	this->entries = t.entries;
}

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

Table::~Table() {

}

void Table::addEntry(int numberArguments, string* arguments, Table& table) {
	Entry* ent = new Entry(numberArguments, arguments);
	push_back_flag = true;
	table.entries.push_back(*ent);
	push_back_flag = false;
}

string Table::getName() {
	return this->name;
}

ostream& operator<< (ostream& out, const Entry& ent) {
	for (int i = 0; i < ent.numberArguments; i++) {
		out << ent.arguments[i] << '\t';
	}
	return out;
}

ostream& operator<<(ostream& out, const Table& tab) { //afisaj tabel
		out << endl;
		out << "\n                    " << tab.name << "                    ";
		out << endl;
		out << "+---------------Table--------------------+";
		
		out << endl;
		
		for (int i = 0; i < tab.tableHead.size(); i++) { //afisam fiecare coloana cu dataType, dataSize si valoarea implicita
			out << tab.tableHead[i] << "/";
			out << tab.dataType[i] << "/";
			out << tab.dataSize[i] << "/";
			out << tab.implicitValue[i] << "\t";
		}
		
		out << endl;
		out << "+-----------------------------------------+";
		out << endl;
		/*for (int i = 0; i < tab.entries.size(); i++) {
			out << i << ".\t";
			for (int j = 0; j < tab.entries[i].size(); i++) {
				out << tab.entries[i][j] << "\t";
			}
		}*/
		for (int i = 0; i < tab.entries.size(); i++) {
			out << tab.entries[i] << "\n";
		}
		
		return out;
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

bool TableExists(string word, vector<Table>& tables) {
	for (int i = 0; i < tables.size(); i++) {
		if (word == tables[i].getName()) {
			return true;
		}
	}
	return false;
}
bool TableExists(string word, vector<Table>& tables, int& position) {
	for (int i = 0; i < tables.size(); i++) {
		if (word == tables[i].getName()) {
			position = i;
			return true;
		}
	}
	return false;
}

bool no_missing_arguments(string* word) {
	try{
		if (stoi(word[0]) < 3 && word[1] != "exit") {
			exception* e = new exception("\nNu exista nicio comanda cu structura introdusa!");
			throw e;
			return false;
		}
		else if (word[1] == "create") {
			if (word[2] == "table") {
				
			}
			else {
				exception* e = new exception("\nSintaxa gresita! Sintaxa corecta: create table table_name column1 c1_data_type c1_size c1_default_value column2 ...");
				throw e;
				return false;
			}
		}
		else if (word[1] == "drop") {

		}
		else if (word[1] == "display") {

		}
		else if (word[1] == "insert") {
			if (word[2] == "into") {
				 
			}
			else {
				exception* e = new exception("\nSintaxa gresita! Sintaxa corecta: insert into table_name values c1_data c2_data ...");
				throw e;
				return false;
			}
		}
		return true;
	}
	catch (exception* e) {
		cout << "\n" << e->what();
	}
}

int identify_command_type(string* word, vector<Table>& tables) {
	if (word[1] == "exit") {
		return 0;
	}
	else {
		if (word[2] == "table") { //daca e vorba de o comanda ce implica table
			if (word[1] == "create") { // vedem daca e create, daca da, facem un tabel nou in vectorul tables
				bool exists = TableExists(word[3], tables);
				
				if (!exists) {
					Table currTable(word);
					tables.push_back(currTable);
				}
				else {
					cout << "\nTabelul " << word[3] << " deja exista!";
				}
			}
			else if (word[1] == "drop") { //altfel vedem daca e drop, daca da, droppam tabelul daca are numele introdus
				int position = -1;
				bool exists = TableExists(word[3], tables, position);
				if (!exists) {
					cout << "\nNu exista tabelul " << word[3];
				}
				else {
					tables.erase(tables.begin() + position);
				}

			}
			else if (word[1] == "display") { //altfel vedem daca e display, daca da, il afisam, daca exista
				int position = -1;
				bool exists = TableExists(word[3], tables, position);
				if (!exists) {
					cout << "\nNu exista tabelul " << word[3];
				}
				else {
					cout << tables[position];
				}
			}
		}
		//if (word[2] == "index") return 999;							//optional conform cerintei
		if (word[1] == "insert") {
			int position = -1;
			bool exists = TableExists(word[3], tables, position);
			if(exists) {
				//Entry* ent = new Entry(tables[position].tableHead.size(), word); //nu stiu de ce nu merge help
				//tables[position].entries.push_back(*ent); problema e cu push_back-ul asta
				
				tables[position].addEntry(tables[position].tableHead.size(), word, tables[position]);
				
			}
			else {
			
			}
		}

		//if (word[1] == "select") return 2;
		//if (word[1] == "update") return 3;
		//if (word[1] == "delete") return 4;
		
		delete[] word;
		//identify_command_type(split_string_into_words(take_user_input_and_convert_lowercase()), tables);
		return 1;
		//return -1;
	}
	//return 0;
}