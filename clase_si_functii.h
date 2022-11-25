//aici gasim antetul/definitiile claselor si functiilor
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip> //pt select setw(dimensiune) sa se afiseze frumos
using namespace std;



class Table {
	string name;													//nume tabel
	vector<string> tableHead;										//vector stl cu capetele de tabel; tableHead.push_back(nume_coloana_1)
	vector<string> dataType;
	vector<int> dataSize;
	vector<string> implicitValue;
	vector<vector<string>> entries;									//matrice de string-uri unde stocam inregistrarile tabelului
	//fiecare linie din vector e aferenta unei inregistrari; entries[i] = inregistrarea i
	//fiecare coloana are cate o valoare; entries[i][j] = tableHead[j]
public:
	Table();
	Table(string* word);

	friend ostream& operator<<(ostream&, const Table&);
	friend void identify_command_type(string*, vector<Table>&);

	
};


string take_user_input_and_convert_lowercase();		//preia inputul decat de la tastatura (eventual va trebui modificata pt a prelua si din fisiere)
													//si converteste tot string-ul la lowercase pt a nu conta CAPS/NO CAPS

string* split_string_into_words(string);			//imparte string-ul initial in vector de string-uri care cuvinte/argumentele; word[j] = al j-lea 
													//cuvant/argument introdus de la tastatura
													//vom putea refolosi functia si pt a pasa la clase cuvant cu cuvant stringul si a asigna corespunzator
													//membrilor valorile din argumente

void identify_command_type(string*, vector<Table>&);					//returneaza 0 pt lucru cu TABLE, 1-4 pt comenzi CRUD

