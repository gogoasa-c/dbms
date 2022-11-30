

//aici gasim antetul/definitiile claselor si functiilor
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip> //pt select setw(dimensiune) sa se afiseze frumos
using namespace std;

class Header {
	vector<string> tableHead;
	vector<string> dataType;
	vector<int> dataSize;
	vector<string> implicitValue;
public:
	Header();
	Header(string*);
	Header(const Header&);

	void setTableHead(vector<string> newTableHead);
	void setDataType(vector<string> newDataType);
	void setDataSize(vector<int> newDataSize);
	void setImplicitValue(vector<string> newImplicitValue);

	vector<string> getTableHead();
	vector<string> getDataType();
	vector<int> getDataSize();
	vector<string> getImplicitValue();

	friend ostream& operator <<(ostream&, const Header&);

	~Header();

};

class Entry {//clasa entry care va constitui un vector<Entry> entries in clasa Table
	int numberArguments;//numar argumente
	string* arguments;//vector de string-uri alocat dinamic
public:
	Entry();
	Entry(int); 
	Entry(int, string*);
	Entry(const Entry&);

	//----------------------------------------------------------------------

	// GET

	int getNumberArguments();
	string* getArguments();

	// SET

	void setNumberArguments(int newNumberArguments, string* newArguments);

	//----------------------------------------------------------------------

	friend ostream& operator<< (ostream&, const Entry&);

	~Entry();
};

class Table {
	string name;//nume tabel
	Header head;
	vector<Entry> entries;//vector de entries unde stocam inregistrarile :D
	
public:
	Table();
	Table(string* word);
	Table(const Table&);

	void addEntry(int, string*, Table&);

	//----------------------------------------------------------------------

	// GET

	string getName();
	
	vector<Entry> getEntries();

	// SET

	void setName(string newName);
	
	void setEntries(vector<Entry> newEntries);

	//----------------------------------------------------------------------

	friend ostream& operator<<(ostream&, const Table&);
	friend int identify_command_type(string*, vector<Table>&);

	~Table();
};

bool isNumber(string);
bool no_missing_arguments(string*);
string take_user_input_and_convert_lowercase();		//preia inputul decat de la tastatura (eventual va trebui modificata pt a prelua si din fisiere)
													//si converteste tot string-ul la lowercase pt a nu conta CAPS/NO CAPS

string* split_string_into_words(string);			//imparte string-ul initial in vector de string-uri care cuvinte/argumentele; word[j] = al j-lea 
													//cuvant/argument introdus de la tastatura
													//vom putea refolosi functia si pt a pasa la clase cuvant cu cuvant stringul si a asigna corespunzator
													//membrilor valorile din argumente

bool TableExists(string, vector<Table>&);//verifica daca tabelul exista in vectorul de tabele
bool TableExists(string, vector<Table>&, int&); //verifica daca tabelul exista in vectorul de tabele si in int& modifica pozitia pe care l-a gasit

int identify_command_type(string*, vector<Table>&);					//returneaza 0 pt lucru cu TABLE, 1-4 pt comenzi CRUD

