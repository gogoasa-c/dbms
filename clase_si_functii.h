// Proiect de echipa realziat de: Ghita Valentin, Gogoasa Cristian, Ionel Teodor

//aici gasim antetul/definitiile claselor si functiilor
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip> //pt select setw(dimensiune) sa se afiseze frumos (seteaza "weight"-ul cout-urilor, adica le forteaza sa afiseze un anumit numar de caractere)
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

	void operator=(const Header&);

	void setTableHead(vector<string> newTableHead);
	void setDataType(vector<string> newDataType);
	void setDataSize(vector<int> newDataSize);
	void setImplicitValue(vector<string> newImplicitValue);

	int getNrColumns();
	vector<string> getTableHead();
	vector<string> getDataType();
	vector<int> getDataSize();
	vector<string> getImplicitValue();

	friend ostream& operator <<(ostream&, const Header&);
	//friend istream& operator>>(istream& in, Table& tb);

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

	bool operator==(const Entry&);
	void operator=(const Entry&);

	operator int();
	//----------------------------------------------------------------------

	// GET

	int getNumberArguments();
	string* getArguments();

	// SET

	void setArguments(int newNumberArguments, string* newArguments);

	//----------------------------------------------------------------------

	friend ostream& operator<< (ostream&, const Entry&);

	~Entry();
};

class Table {
	static int numberCreatedTables;
	const int tableId;
	string name;//nume tabel
	Header head;
	vector<Entry> entries;//vector de entries unde stocam inregistrarile :D

public:
	Table();
	Table(string* word);
	Table(const Table&);

	Entry& operator[](int);						//create table t; t[0] => t.entries[0]; word[2] = numetabel; word[2][0] => t.entries[0]
	void operator=(const Table&);
	Table operator+(Table);
	Table& operator++();
	Table operator++(int);
	operator string();
	bool operator>(const Table&);
	bool operator>=(const Table&);
	bool operator<(const Table&);
	bool operator<=(const Table&);
	bool operator!();
	void addEntry(int, string*, Table&);
	//----------------------------------------------------------------------
	// GET
	string getName();
	vector<Entry> getEntries();
	vector<Entry>& getRefEntries();
	// SET
	void setName(string newName);
	void setEntries(vector<Entry> newEntries);
	//----------------------------------------------------------------------
	friend ostream& operator<<(ostream&, const Table&);
	friend istream& operator>>(istream&, Table&);
	friend int identify_command_type(string*, vector<Table>&); // l-am facut friend sa putem accesa campurile din clasa Table

	~Table();
};

class Database { //database va fi o clasa de tip singleton ergo constructor privat a.i. sa avem un singur obiect instantiat; p.s.: nu e varianta thread-safe
	static Database* instance; //pointerul cu ajutorul caruia vom instantia unicul obiect de tip Database
	vector<Table> tables; //vectorul in care tinem tabelele
	Database();
public:
	Database(const Database&) = delete; // nu trebuie sa fie clonabila

	void operator=(const Database&) = delete; // si nici asignabila

	static Database* getInstance();
	vector<Table>& getTables();
	void setTables(vector<Table>);
};

bool isNumber(string);
bool isFloatingPoint(string);
bool no_missing_arguments(string*);
bool check_for_parenthesis_and_commas(string);
string take_user_input_and_convert_lowercase();		//preia inputul decat de la tastatura (eventual va trebui modificata pt a prelua si din fisiere)
													//si converteste tot string-ul la lowercase pt a nu conta CAPS/NO CAPS

string* split_string_into_words(string);			//imparte string-ul initial in vector de string-uri care cuvinte/argumentele; word[j] = al j-lea 
													//cuvant/argument introdus de la tastatura
													//vom putea refolosi functia si pt a pasa la clase cuvant cu cuvant stringul si a asigna corespunzator
													//membrilor valorile din argumente
bool columnExists(string, vector<string>); // verifica daca coloana exista in header-ul unui tabel anume
bool columnExists(string, vector<string>, int&); // verifica daca coloana exista in header-ul unui tabel anume si intoarce pozitia pe care se afla coloana daca exista
bool TableExists(string, vector<Table>&);//verifica daca tabelul exista in vectorul de tabele
bool TableExists(string, vector<Table>&, int&); //verifica daca tabelul exista in vectorul de tabele si in int& modifica pozitia pe care l-a gasit
int identify_command_type(string*, vector<Table>&);	//functia principala care face majoritatea muncii
void menu();
