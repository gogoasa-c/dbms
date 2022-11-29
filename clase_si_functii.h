

//aici gasim antetul/definitiile claselor si functiilor
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip> //pt select setw(dimensiune) sa se afiseze frumos
using namespace std;

class Entry {//clasa entry care va constitui un vector<Entry> entries in clasa Table
	int numberArguments;//numar argumente
	string* arguments;//vector de string-uri alocat dinamic
public:
	Entry();
	Entry(int); 
	Entry(int, string*);
	Entry(const Entry&);
	friend ostream& operator<< (ostream&, const Entry&);

	~Entry();
};

class Table {
	string name;													//nume tabel
	vector<string> tableHead;										//vector stl cu capetele de tabel; tableHead.push_back(nume_coloana_1)
	vector<string> dataType;
	vector<int> dataSize;
	vector<string> implicitValue;
	//vector<vector<string>> entries;									//matrice de string-uri unde stocam inregistrarile tabelului
	vector<Entry> entries;//vector de entries unde stocam inregistrarile :D
	//fiecare linie din vector e aferenta unei inregistrari; entries[i] = inregistrarea i
	//fiecare coloana are cate o valoare; entries[i][j] = tableHead[j]
public:
	Table();
	Table(string* word);
	Table(const Table&);

	void addEntry(int, string*, Table&);
	string getName();

	friend ostream& operator<<(ostream&, const Table&);
	friend int identify_command_type(string*, vector<Table>&);

	~Table();
};


string take_user_input_and_convert_lowercase();		//preia inputul decat de la tastatura (eventual va trebui modificata pt a prelua si din fisiere)
													//si converteste tot string-ul la lowercase pt a nu conta CAPS/NO CAPS

string* split_string_into_words(string);			//imparte string-ul initial in vector de string-uri care cuvinte/argumentele; word[j] = al j-lea 
													//cuvant/argument introdus de la tastatura
													//vom putea refolosi functia si pt a pasa la clase cuvant cu cuvant stringul si a asigna corespunzator
													//membrilor valorile din argumente

bool TableExists(string, vector<Table>&);//verifica daca tabelul exista in vectorul de tabele
bool TableExists(string, vector<Table>&, int&); //verifica daca tabelul exista in vectorul de tabele si in int& modifica pozitia pe care l-a gasit

int identify_command_type(string*, vector<Table>&);					//returneaza 0 pt lucru cu TABLE, 1-4 pt comenzi CRUD

