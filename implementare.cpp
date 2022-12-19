//aici implementam clasele si functiile propriu-zis
// Proiect de echipa realziat de: Ghita Valentin, Gogoasa Cristian, Ionel Teodor
#include "clase_si_functii.h"

using namespace std;

int Table::numberCreatedTables = 0;

Database* Database::instance = nullptr;

int selectID = 0, displayID = 0; // pt fisiere sa tinem minte care fisier e la afisarea de "Rapoarte"


bool fileExists(char* name) { // verificam daca exista fisierul respectiv
	ifstream f(name); // .c_str transforma std::string-ul in char*
	return f.good();
}

Database::Database() {
	//nu e nevoie sa faca nimic
}

Database* Database::getInstance() {
	if (!Database::instance) { // creaza unica instanta a clasei Database
		instance = new Database;
	}
	return Database::instance;
}

vector<Table>& Database::getTables() { // intoarce referinta la tables sa putem modifica vectorul
	return this->tables;
}

vector<Table> Database::getTablesNoRef() { // intoarce referinta la tables sa putem modifica vectorul
	return this->tables;
}

void Database::setTables(vector<Table> t) { 
	this->tables = t;
}

Header::Header() {

}

Header::Header(string* word) {
	if (word == nullptr) {
		return;
	}
	int size = stoi(word[0]);
	int i = 3; //incepe cu poz 3 unde sunt efectiv argumentele lui create table
	i++;
	while (i <= size) { //ia fiecare nume de coloana, dataType, dataSize, dataSize, implicitValue si le baga in vectorii aferenti
		this->tableHead.push_back(word[i++]);
		this->dataType.push_back(word[i++]);
		this->dataSize.push_back(stoi(word[i++]));
		this->implicitValue.push_back(word[i++]);
	}
}

Header::Header(const Header& h) {
	this->tableHead = h.tableHead;
	this->dataType = h.dataType;
	this->dataSize = h.dataSize;
	this->implicitValue = h.implicitValue;
}

Header::~Header() {

}

void Header::writeToFiles(const char* fileName) {
	ofstream f(fileName);
	if (!f.good()) {
		return;
	}
	f << *this;
	f.close();
}


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
	if (newNumberArguments > 0 && newArguments != NULL) {
		this->numberArguments = newNumberArguments;
		this->arguments = new string[numberArguments];
		int j = 0;
		for (int i = 0; i < newNumberArguments; i++) {
			this->arguments[i] = newArguments[i];
		}
	}
	else {
		this->numberArguments = 0;
		this->arguments = NULL;
	}
}

void Entry::operator=(const Entry& e) {
	try{
		if (e.numberArguments < 0 || e.arguments == nullptr) {
			exception e("\nEntry invalid operator=!\n");
			throw e;
		}
		this->numberArguments = e.numberArguments;
		this->arguments = new string[this->numberArguments];
		for (int i = 0; i < this->numberArguments; i++) {
			this->arguments[i] = e.arguments[i];
		}
	}
	catch (exception e) {
		cout << e.what();
	}

}

Entry::~Entry() {
	if (this->arguments != nullptr ) {
		delete[] this->arguments;
	}
}

Table::Table(const Table& t):tableId(numberCreatedTables){
	numberCreatedTables++;
	this->name = t.name;
	this->head = t.head;
	this->entries = t.entries;
}

Table::Table(): head(nullptr), tableId(numberCreatedTables){
	numberCreatedTables++;
	this->name = "null";
}

Table::Table(string* word): head(word), tableId(numberCreatedTables){ //pt coloanele tabelului/capul de tabel
	numberCreatedTables++;
	this->name = word[3];
}

Table::~Table() {
	
}

void Table::addEntry(int numberArguments, string* arguments, Table& table) {
	try{//insert into table_name values((col1, col2, col3), (col11, col12, col13), ...)
		if ((stoi(arguments[0]) - 4) % table.head.getNrColumns() != 0) {
			exception e("\nNumar invalid de argumente!\n");
			throw e;
		}
		
		int j = 0; // am adaugat asta ca sa verificam ca argumentele pasate se afla in limite (compar efectiv lungimea sirului din arguments cu maxSize-ul argumentului si anume table.head.getDataSize()[j]
		for(int i=5; i<=stoi(arguments[0]); i++){
			if(arguments[i].size() > table.head.getDataSize()[j]){
				exception e("\nValoarea introdusa intrece limitele coloanei!\n");
				throw e;
			}
			++j;
			if (j == table.head.getDataSize().size()) {
				j = 0;
			}
		}
		//abia daca trec de check fac un entry nou pe care il pushez
		j = 5;
		while(j < stoi(arguments[0])) {
			string* aux = new string[table.head.getNrColumns()];
			for (int i = 0; i < table.head.getNrColumns(); i++) {
				aux[i] = arguments[j];
				j++;
			}
			
			Entry* ent = new Entry(table.head.getNrColumns(), aux);
			table.entries.push_back(*ent);
			delete[] aux;
		}
	}
	catch (exception e) {
		cout << e.what();
	}
}

bool Entry::operator==(const Entry& ent) {
	if (this->numberArguments != ent.numberArguments) {
		return false;
	}
	if (this->numberArguments == ent.numberArguments) {
		for (int i = 0; i < this->numberArguments; i++) {
			if (this->arguments[i] != ent.arguments[i]) {
				return false;
			}
		}
	}
	return true;
}

Entry::operator int() {
	return this->numberArguments;
}

Entry& Table::operator[](int index) {
	try {
		if (index < 0 || index >= this->entries.size()) { //e cu || conditia ca nu poate sa fie si mai mic decat 0 index si mai mare decat marimea entry-urilor care e numar pozitiv
			exception e("\nIndex invalid!\n");
			throw e;
		}

		return this->entries[index];
	}
	catch (exception e) {
		cout << e.what();
		Entry ent(0, nullptr); // cred ca asta voiati sa faceti
		return ent;
	}	
}

void Header::operator=(const Header& h) {
	this->tableHead = h.tableHead;
	this->dataType = h.dataType;
	this->dataSize = h.dataSize;
	this->implicitValue = h.implicitValue;
}

void Table::operator=(const Table& t) {
	this->name = t.name;
	this->head = t.head;
	this->entries = t.entries;
}

Table Table::operator+(Table t) {
	Table copie;
	
	if (this->head.getTableHead() == t.head.getTableHead() && this->head.getDataType() == t.head.getDataType() && this->head.getDataSize() == t.head.getDataSize() && this->head.getImplicitValue() == t.head.getImplicitValue()) {
		copie = *this;
		for (int i = 0; i < this->head.getTableHead().size(); i++) {
			copie.addEntry(t.entries[i].getNumberArguments(), t.entries[i].getArguments(), t);
		}
	}
	
	return copie;
}

Table& Table::operator++() {
	cin >> *this;
	return *this;
}

Table Table::operator++(int) {
	Table copie = *this;
	cin >> *this;
	return copie;
}

Table::operator string() {
	return this->name;
}

bool Table::operator>(const Table& aux) {
	if (this->entries.size() > aux.entries.size())
		return true;
	return false;
}

bool Table::operator>=(const Table& aux) {
	if (this->entries.size() >= aux.entries.size())
		return true;
	return false;
}

bool Table::operator<(const Table& aux) {
	if (this->entries.size() < aux.entries.size())
		return true;
	return false;
}

bool Table::operator<=(const Table& aux) {
	if (this->entries.size() <= aux.entries.size())
		return true;
	return false;
}

bool Table::operator!() {
	if (this->entries.size() == 0)
		return true;
	else
		return false;
}

ofstream& operator <<(ofstream& out, const Header& head) {
	out << endl;
	for (int i = 0; i < head.tableHead.size(); i++) {
		out << "++++++++++++++++++++++";
	}
	out << endl;
	for (int i = 0; i < head.tableHead.size(); i++) {
		out << head.tableHead[i] << "|";
		out << head.dataType[i] << "|";
		out << "" << head.dataSize[i] << "|"; // nu merge fara "", nu stiu, suntem ca in fast inverse square root quake 3 cautati pe google
		out << head.implicitValue[i] << "\t";
	}
	out << endl;
	for (int i = 0; i < head.tableHead.size(); i++) {
		out << "++++++++++++++++++++++";
	}
	return out;
}

ostream& operator<< (ostream& out, const Header& head) {
	out << endl;
	for (int i = 0; i < head.tableHead.size(); i++) {
		out << "++++++++++++++++++++++";
	}
	out << endl;
	for (int i = 0; i < head.tableHead.size(); i++) {
		out << head.tableHead[i] << "|";
		out << head.dataType[i] << "|";
		out << head.dataSize[i] << "|";
		out << head.implicitValue[i] << "\t";
	}
	out << endl;
	for (int i = 0; i < head.tableHead.size(); i++) {
		out << "++++++++++++++++++++++";
	}
	return out;
}

ostream& operator<< (ostream& out, const Entry& ent) {
	ios init(NULL);
	init.copyfmt(out);
	out << setw(15);

	for (int i = 0; i < ent.numberArguments; i++) {
		out << ent.arguments[i] << "\t\t";
	}

	cout.copyfmt(init);
	return out;
}

ofstream& operator<< (ofstream& out, const Entry& ent) {
	ios init(NULL);
	init.copyfmt(out);
	out << setw(15);

	for (int i = 0; i < ent.numberArguments; i++) {
		out << ent.arguments[i] << "\t\t";
	}

	cout.copyfmt(init);
	return out;
}

ostream& operator<<(ostream& out, const Table& tab) { //afisaj tabel
		Header h = tab.head;
		out << endl;
		for (int i = 0; i < h.getTableHead().size()/2; i++) {
			out << '\t' << '\t';
		}
		out << tab.name;
		for (int i = h.getTableHead().size()/2; i < h.getTableHead().size(); i++) {
			out << '\t' << '\t';
		}
		out << tab.head;
		out << endl;
		for (int i = 0; i < tab.entries.size(); i++) {
			out << tab.entries[i] << "\n";
		}
		return out;
}

ofstream& operator<<(ofstream& out, const Table& tab) {
	Header h = tab.head;
	out << endl;
	for (int i = 0; i < h.getTableHead().size() / 2; i++) {
		out << "\t" << '\t';
	}
	out << tab.name;
	for (int i = h.getTableHead().size() / 2; i < h.getTableHead().size(); i++) {
		out << "\t" << '\t';
	}
	out << tab.head;
	out << endl;
	for (int i = 0; i < tab.entries.size(); i++) {
		out << tab.entries[i] << "\n";
	}
	return out;
}

istream& operator>>(istream& in, Table& tb) {						 //cin >> numeTabel => un nou entry in vectorul entries al clasei Table
	int nrArgumente = tb.head.getNrColumns();
	string* argumente = new string[nrArgumente];
	for (int i = 0; i < nrArgumente; i++) {
		cout << "\n" << tb.head.getTableHead()[i] << " : ";
		getline(in, argumente[i]);
	}
	tb.addEntry(nrArgumente, argumente, tb);

	delete[] argumente;
	return in;
}

bool check_for_parenthesis_and_commas(string userInput)
{
	int openedParanthesis = 0;
	if (userInput.size() == 0) {
		return true;
	}
	if (userInput[userInput.size() - 1] == ',') {
		return false;
	}
	for (int i = 0; i < userInput.size(); i++) {
		if (userInput[i] == '(') {
			openedParanthesis++;
		}
		if (userInput[i] == ')') {
			openedParanthesis--;
		}

		if (userInput[i] == ',' && i<userInput.size() - 1) { //added condition to check if i less than userInput.size() - 1 as to not overflow out of string size
			if (userInput[i + 1] != ' ') {							//had been checked in the first if condition of the function so it shouldn't reach out of bound values
				return false;
			}
		}
	}

	if (openedParanthesis) {
		return false;
	}

	return true;
}

string take_user_input_and_convert_lowercase()
{
	string userInput = "";
	getline(cin, userInput);
	if (check_for_parenthesis_and_commas(userInput)) {
		for (int i = 0; i < userInput.size(); i++) {
			if (userInput[i] >= 'A' && userInput[i] <= 'Z') {
				userInput[i] += 32;										//value of 'a' - 'A'
			}
		}
	}
	else {
		cout << "\nSintaxa gresita! Sintaxa corecta are virgule, dupa virgule spatii, iar toate parantezele deschise trebuie si inchise!\n";
		userInput = "invalid";
	}

	return userInput;
}

string* split_string_into_words(string userInput)
{
	if (userInput == "invalid") {
		return nullptr;
	}
	int controlSize = 100;											//controlam size-ul array-ului de string alocat dinamic
	string* word = new string[controlSize];							//nota: pt introducerea din fisiere, comenzile for vi despartite intre ele prin enter ;; word[index] = ""
	string* aux = NULL;
	int i, numberWords = 0, k;										//i = initial contor apoi index pt a cata litera din string ;; numberWords = index pt al catelea cuvant formam ;; k = index similar lui numberWords dar folosim pt resize de word prin ajutorul lui aux 
	word[0] = to_string(numberWords);								//!!!ATENTIE!!! cuvant[0] va tine NR DE CUVINTE (pt a folosi in alocari dinamice vom folosi **stoi(cuvant[0])**
	unsigned int startedTyping = 0;									//ne ajuta sa ignoram multiple space-uri, pt a nu da eroare usor
	for (i = 0; i < userInput.size(); i++) {
		if (userInput[i] != ' ' && userInput[i] != '(' && userInput[i] != ')' && userInput[i] != ',') {
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
			while (userInput[i] != ' ' && userInput[i] != '(' && userInput[i] != ')' && userInput[i] != ',' && i < userInput.size()) {
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

bool columnExists(string col, vector<string> columns) {
	for (int i = 0; i < columns.size(); i++) {
		if (col == columns[i]) {
			return true;
		}
	}
	return false;
}

bool columnExists(string col, vector<string> columns, int& position) {
	for (int i = 0; i < columns.size(); i++) {
		if (col == columns[i]) {
			position = i;
			return true;
		}
	}
	return false;
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

bool isNumber(string s) {
	for (int i = 0; i < s.length(); i++) {
		if (isdigit(s[i]) == 0) {
			return false;
		}
	}
	return true;
}

bool isFloatingPoint(string s) {
	bool hasPoint = false;
	for (int i = 0; i < s.length(); i++) {
		if (isdigit(s[i]) == 0) {
			if(!hasPoint && s[i] == '.') {
				hasPoint = true;
				
			}
			else{
				return false;
			}
		}
	}
	return true;
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
				int i = 5;
				do {
					if (word[i] != "text" && word[i] != "float" && word[i] != "int") {
						exception* e = new exception("\n\nSintaxa gresita! Sintaxa corecta: create table table_name ((column1, c1_data_type, c1_size, c1_default_value,) (column2, c2_data_type, c2_size...), ...)\n");
						throw e;
						return false;
					}
					i++;
					if (!isNumber(word[i])) {
						exception* e = new exception("\nSintaxa gresita! Sintaxa corecta: create table table_name ((column1, c1_data_type, c1_size, c1_default_value,) (column2, c2_data_type, c2_size...), ...)\n");
						throw e;
						return false;
					}
					i += 3;
				} while (i < stoi(word[0]));
				return true;
			}
			else {// 5 6 9 10 13 14
				exception* e = new exception("\nSintaxa gresita! Sintaxa corecta: create table table_name ((column1, c1_data_type, c1_size, c1_default_value,) (column2, c2_data_type, c2_size...), ...)\n");
				throw e;
				return false;
			}
		}
		else if (word[1] == "drop") {
			if (word[2] != "table" || stoi(word[0]) > 3) {
				exception* e = new exception("\nSintaxa gresita! Sintaxa corecta: drop table nume_tabel");
				throw e;
				return false;
			}
		}
		else if (word[1] == "display") {
			if (word[2] != "table" || stoi(word[0]) > 3) {
				exception* e = new exception("\nSintaxa gresita! Sintaxa corecta: display table nume_tabel");
				throw e;
				return false;
			}
			return true;
		}
		else if (word[1] == "insert") {
			if (word[2] == "into") {
				if (word[4] != "values") {
					exception* e = new exception("\nSintaxa gresita! Sintaxa corecta: insert into table_name values (c1_data, c2_data ...)");
					throw e;
					return false;
				}
				return true;
			}
			else {
				exception* e = new exception("\nSintaxa gresita! Sintaxa corecta: insert into table_name values (c1_data, c2_data...)");
				throw e;
				return false;
			}
		}
		else if (word[1] == "select") {
			//nu prea avem cum face check aici pe select. trebuie sa vedem numele de coloane mai jos in identify_command_type(); rezolvat in identify_command_type
			return true;
		}
		else if (word[1] == "delete") {
			if (stoi(word[0]) != 7) {
				exception* e = new exception("\nNumar gresit de argumente. Comanda are sintaxa:   delete from nume_tabela where nume_coloana = valoare    si primeste 7 argumente!\n");
				throw e;
				return false;
			}
			if (word[2] == "from") {
				if (word[4] != "where" || word[6] != "=") {
					exception* e = new exception("\nSintaxa gresita! Sintaxa corecta: delete from nume_tabela where nume_coloana = valoare");
					throw e;
					return false;
				}
			}
			else {
				exception* e = new exception("\nSintaxa gresita! Sintaxa corecta: delete from nume_tabela where nume_coloana = valoare");
				throw e;
				return false;
			}
		}
		else if (word[1] == "update") {
			if (stoi(word[0]) != 10) {
				exception* e = new exception("\nNumar gresit de argumente. Comanda are sintaxa:   UPDATE nume_tabela SET nume_coloana = valoare WHERE nume_coloana = valoare    si primeste 10 argumente!\n");
				throw e;
				return false;
			}
			if (word[3] != "set" || word[5] != "=" || word[7] != "where" || word[9] != "=") {
				exception* e = new exception("\nSintaxa gresita! Sintaxa corecta: UPDATE nume_tabela SET nume_coloana = valoare WHERE nume_coloana = valoare\n");
				throw e;
				return false;
			}
		}
		else if (word[1] != "create" && word[1] != "drop" && word[1] != "display" && word[1] != "insert" && word[1] != "delete" && word[1] != "update") {
			exception* e = new exception("\nComanda inexistenta!\n");
			throw e;
			return false;
		}
		return true;
	}
	catch (exception* e) {
		cout << "\n" << e->what() << "\n";
	}
}

int identify_command_type(string* word, vector<Table>& tables) {
	if (word == nullptr) {
		return 1;//check pentru input invalid
	}
	if (word[1] == "exit") {
		return 0;
	}
	else {
		if (!no_missing_arguments(word)) {
			return 1;
		}
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
					cout << "\nNu exista tabelul " << word[3] << endl;
				}
				else {
					cout << tables[position];
					string fileName = "display_"; // alcatuim numele fisierului in care urmeaza sa scriem :D
					fileName += to_string(displayID); // ii lipim id-ul la final
					displayID++;
					fileName += ".txt"; // si extensia
					tables[position].writeToFiles(fileName.c_str()); // dupa care il scriem in fisier
				}
			}
		}
		else if (word[1] == "insert") {//if (word[2] == "index") return 999;							//optional conform cerintei
			int position = -1;
			bool exists = TableExists(word[3], tables, position);
			if(exists) {
				tables[position].addEntry(tables[position].head.getTableHead().size(), word, tables[position]);
				
			}
			else {
				cout << "\nTabel inexistent\n";
			}
		}
		else if (word[1] == "select") { // select (coloana1, coloana2, coloana3, ...) from tabel where nume_coloana = valoare
			if (word[2] == "all") { // select all from tabel [where nume_coloana = valoare]
				int position = -1; // incepem cu poz -1 ca mai sus la insert
				bool exists = TableExists(word[4], tables, position); // gasim tabelul din care afisam
				if (exists) {
					if (word[5] == "where") { // vedem daca e cu where sau nu
						vector<string> tabHeads = tables[position].head.getTableHead(); // copiem capul de tabel cu numele doar
						int colPosition = -1;
						bool colExists = columnExists(word[6], tabHeads, colPosition); // verificam daca exista coloana
						if (colExists) { // daca exista 
							cout << tables[position].head; // dam output la capul de tabel
							string fileName = "select_"; // alcatuim numele fisierului in care urmeaza sa scriem :D
							fileName += to_string(selectID); // ii lipim id-ul la final
							selectID++;
							fileName += ".txt"; // si extensia
							tables[position].head.writeToFiles(fileName.c_str());
							for (int i = 0; i < tables[position].getEntries().size(); i++) { // si dupa cautam sa dam match intre valoare de pe coloana respectiva si valoarea introdusa de la tastatura
								if (tables[position].getEntries()[i].getArguments()[colPosition] == word[8]) {
									cout << endl << tables[position].getEntries()[i]; // cand o gasim, cout
									tables[position].getEntries()[i].writeToFiles(fileName.c_str());
								}
							}
						}
						else {
							cout << "\nColoana nu exista!\n";
							return 1;
						}
					} // daca nu e cu where ii dam direct print
					else {
						cout << tables[position];
						string fileName = "select_"; // alcatuim numele fisierului in care urmeaza sa scriem :D
						fileName += to_string(selectID); // ii lipim id-ul la final
						selectID++;
						fileName += ".txt"; // si extensia
						tables[position].writeToFiles(fileName.c_str()); // dupa care il scriem in fisier
					}
				}
				else {
					cout << "\nTabel inexistent\n";
					return 1;
				}
			}
			else { //mergem si vedem despre ce tabel e vorba
				int i = 1, fromPosition = -1; // stim ca numele tabelului se afla dupa fix dupa from
				while (i < stoi(word[0])) {
					if (word[i] == "from") {
						fromPosition = i; //am gasit from-ul deci e ok. gata
						break;
					}
					++i;
				}
				i = 1;
				int wherePosition = -1;
				while (i < stoi(word[0])) {
					if (word[i] == "where") {
						wherePosition = i;
						break;
					}
					++i;
				}
				
				// select (coloana1, coloana2, coloana3, ...) from tabel where nume_coloana = valoare
				if (fromPosition == -1) { // daca nu l-am gasit, e problema de sintaxa
					cout << "\nSintaxa gresita! Sintaxa corecta: select coloana1, coloana2, coloana3, ... from nume_tabel [where coloana = valoare]\n";
					return 1;
				}
				//ok hai sa cautam tabelul
				int tablePosition = -1; // incepem cu poz -1 ca mai sus la insert
				bool exists = TableExists(word[fromPosition+1], tables, tablePosition); // gasim tabelul din care afisam
				if (exists) { // daca exista tabelul sa vedem daca coloanele sunt in el :D
					string fileName = "select_"; // alcatuim numele fisierului in care urmeaza sa scriem :D
					fileName += to_string(selectID); // ii lipim id-ul la final
					selectID++;
					fileName += ".txt"; // si extensia
					//implementare mai rapciugoasa dar ar fi mai mare durerea de cap sa fac cu inheritance
					ofstream fileOutput(fileName.c_str()); // am deschis fisierul
					
					vector<string> tabHeads = tables[tablePosition].head.getTableHead(); // copiem capul de tabel cu numele doar
					vector<int> columnPositions; // aici tinem pozitiile coloanelor cand le gasim
					for (int i = 2; i < fromPosition; i++) { // vedem despre ce coloane e vorba
						int colPosition = -1;
						bool colExists = columnExists(word[i], tabHeads, colPosition); // verificam daca exista coloana
						if (colExists) { // exista coloana? super
							columnPositions.push_back(colPosition); // bagam pozitia ei in columnPositions
						}
						else {
							cout << "\nColoana inexistenta!\n"; // nu exista? nasol
							return 1; // nu mai facem nimic
						}
					}
					cout << endl;
					fileOutput << endl;
					for(int i=0; i<columnPositions.size(); i++){
						cout << "++++++++++++++++++++++";
						fileOutput << "++++++++++++++++++++++";
					}
					cout << endl;
					fileOutput << endl;
					for (int i = 0; i < columnPositions.size(); i++) { // aici vreau sa afisez capetele de tabel (doar numele lor)
						ios init(NULL); 
						init.copyfmt(cout);
						cout << setw(15);
						fileOutput << setw(15);
						cout << tables[tablePosition].head.getTableHead()[columnPositions[i]] << "\t\t";
						fileOutput << tables[tablePosition].head.getTableHead()[columnPositions[i]] << "\t\t";
						cout.copyfmt(init);
						fileOutput.copyfmt(init);
					}
					cout << endl;
					fileOutput << endl;
					for (int i = 0; i < columnPositions.size(); i++) {
						cout << "++++++++++++++++++++++"; // afisaj frumos
						fileOutput << "++++++++++++++++++++++";
					}
					cout << endl;
					fileOutput << endl;
					if(wherePosition == -1){
						for (int j = 0; j < tables[tablePosition].entries.size(); j++) { // pentru fiecare entry
							for (int i = 0; i < columnPositions.size(); i++) { // aici trecem prin vectorul cu pozitiile coloanelor si afisam coloanele
								ios init(NULL);
								init.copyfmt(cout);
								cout << setw(15);
								fileOutput << setw(15);
								cout << tables[tablePosition].entries[j].getArguments()[columnPositions[i]] << "\t\t";
								fileOutput << tables[tablePosition].entries[j].getArguments()[columnPositions[i]] << "\t\t";
								cout.copyfmt(init);
								fileOutput.copyfmt(init);

							} // tables[tablePositions] = tabelul curent
							//.entries = intram in vectorul entries
							//[j] ca luam al j-lea entry ca facem for-ul exterior cu j pe vectorul de entries
							// .getArguments() = .arguments[columnPositions[i]] pentru ca pozitiile coloanelor sunt actually in columnPositions
							cout << endl;
							fileOutput << endl;
						}
					}
					else {
						int restrictionColumnPos = -1;
						bool restrictionExists = columnExists(word[wherePosition + 1], tables[tablePosition].head.getTableHead(), restrictionColumnPos);
						if (!restrictionExists) { // mergem si cautam coloana in functie de care facem check-ul pe where, daca nu exista return
							cout << "\nColoana restrictie inexistenta!\n"; 
							return 1;
						}//in schimb, daca exista, mergem cu 2 for-uri nested ca mai sus si afisam doar ce se potriveste cu restriction-ul
						for (int j = 0; j < tables[tablePosition].entries.size(); j++) { // pentru fiecare entry
							bool afisat = false;
							for (int i = 0; i < columnPositions.size(); i++) { // aici trecem prin vectorul cu pozitiile coloanelor si afisam coloanele
								if(tables[tablePosition].entries[j].getArguments()[restrictionColumnPos] == word[wherePosition + 3]) {
									ios init(NULL);
									init.copyfmt(cout);
									cout << setw(15);
									fileOutput << setw(15);
									cout << tables[tablePosition].entries[j].getArguments()[columnPositions[i]] << "\t\t";
									fileOutput << tables[tablePosition].entries[j].getArguments()[columnPositions[i]] << "\t\t";
									cout.copyfmt(init);
									fileOutput.copyfmt(init);
									afisat = true;
								}

							}
							if(afisat){
								cout << endl;
								fileOutput << endl;
							}
						}
					}
				}
				else {
					cout << "\nTabel inexistent!\n";
					return 1;
				}
				
			}
		}
		else if (word[1] == "delete") {															 // DELETE FROM nume_tabela WHERE nume_coloana = valoare (DELETE permite doar o coloana în clauza WHERE)
			string tableName = word[3];															 // numele tabelei din care urmeaza sa stergem inregistrari
			int pozTable = -1;																	 // pozitia tabelei in vectorul de tabele (-1 daca nu exista)
			if (TableExists(tableName, tables, pozTable)) {						   				 // functie care verifica existenta tabelei in vectorul de tabele si modifica prin referinta pozitia tabelei in caz ca tabela exista 
				string columnName = word[5];									 				 // numele coloanei pe care o egalam cu o valoare anume, iar inregistrarile care au pe coloana columnName valoare precizata vor fi sterse
				int pozColumn = -1;															     // pozitia coloanei pt care cautam inregistrari ce urmeaza a fi sterse
				if (columnExists(columnName, tables[pozTable].head.getTableHead(), pozColumn)) { // tables[pozTable].head.getTableHead() inseamna ca in vectorul de tabele tables, ne ducem la tabela pe care o dorim a 
																								 // carei pozitie este pozTable, apoi ne ducem la membrul head, iar apoi la metoda getTableHead() care returneaza vector<string>
					string searchedValue = word[7];												 // stringul corespunzator lui "valoare" din sintaxa este word[7]
					vector<Entry> newEntries;
					for (int i = 0; i < tables[pozTable].getEntries().size(); i++) {
						if (tables[pozTable].getRefEntries()[i].getArguments()[pozColumn] != searchedValue) { // cand gasim entry care se potriveste
							newEntries.push_back(tables[pozTable].getEntries()[i]);
						}
					}
					tables[pozTable].getRefEntries() = newEntries;
					
				}
				else {
					cout << "\nColoana inexistenta!\n";
				}
			}
			else {
				cout << "\nTabel inexistent!\n";
			}
		}
		else if (word[1] == "update") {																//UPDATE nume_tabela SET nume_coloana = valoare WHERE nume_coloana = valoare (coloana SET poate fi diferita de cea WHERE; UPDATE merge doar pentru o coloana)
			string tableName = word[2];
			int pozTable = -1;																	 
			if (TableExists(tableName, tables, pozTable)) {
				string columnName1 = word[4];
				int pozColumn1 = -1;
				if (columnExists(columnName1, tables[pozTable].head.getTableHead(), pozColumn1)) {
					string setValue = word[6];
					string lookForValue = word[10];
					string columnName2 = word[8];
					int pozColumn2 = -1;
					if (columnExists(columnName2, tables[pozTable].head.getTableHead(), pozColumn2)) {
						for (int i = 0; i < tables[pozTable].getEntries().size(); i++) {						//trecem prin fiecare entry al tabelei pe rand
							if (tables[pozTable].getEntries()[i].getArguments()[pozColumn2] == lookForValue) {  //daca entry-ul i are argumentul[pozColumn2] = valoarea dupa care setam

								int numberArguments = tables[pozTable].entries[i].getNumberArguments();			//numarul de argumente al entry-ului i
								string* newArguments = new string[numberArguments];
								for (int j = 0; j < numberArguments; j++) {
									newArguments[j] = tables[pozTable].entries[i].getArguments()[j];			//egalam newArguments cu argumentele vechi mai intai
								}
								//imi cer scuze pentru check-ul asta lung
								if ((tables[pozTable].head.getDataType()[pozColumn1] == "int" && isNumber(setValue)) || (tables[pozTable].head.getDataType()[pozColumn1] == "float" && (isNumber(setValue) || isFloatingPoint(setValue))) || (tables[pozTable].head.getDataType()[pozColumn1] == "text" && !isNumber(setValue))) { // aici trebuie sa vina un check daca e ok valoarea cu tipul de data
									newArguments[pozColumn1] = setValue;											//pozitia in newArguments pe care vrem sa o modificam ia valoarea pe care vrem s-o 
									tables[pozTable].entries[i].setArguments(numberArguments, newArguments);
								}
								else {
									cout << "\nTip de data introdus incompatibil!\n";
								}
								delete[] newArguments;
							}
						}
					}
					else {
						cout << "\nColoana " << columnName2 << " nu exista!" << "\n";
					}
				}
				else {
					cout << "\nColoana " << columnName1 << " nu exista!" << "\n";
				}
			}
			else {
				cout << "\nTabel inexistent!\n";
			}
		}
		delete[] word;
		return 1;
	}
}

void menu(int& argsc, char* argsv[]) {
	Database* db = db->getInstance();
	
	fstream f1, f2;

	f1.open("headers-in-binary.txt", ios::in | ios::binary);
	if (f1.is_open())
		read_headers_from_binary_file(f1, db->getTables());
	else {
		cout << "\nheaders-in-binary.txt doesn't exists in the program path and therefore will be created at the end of execution in order to load data\n";
	}
	f1.close();

	f2.open("content-in-binary.txt", ios::in | ios::binary);
	if (f2.is_open())
		read_content_from_binary_file(f2, db->getTables());
	else {
		cout << "\ncontent-in-binary.txt doesn't exists in the program path and therefore will be created at the end of execution in order to load data\n";
	}
	f2.close();

	
	cout << "Beta 2.0\n";
	cout << "ATENTIE: ENTER confirma inputul/comanda introdusa. EXIT incheie executia. Daca doriti anularea unei comenzi introduceti o comanda eronata.\n\n";   //IMPLEMENTAT. PARE SA FUNCTIONEZE
	db->readFromFiles(argsc, argsv);
	while (true) {
		int aux = identify_command_type(split_string_into_words(take_user_input_and_convert_lowercase()), db->getTables());
		if (aux == 0)
			break;//FUNCTIONEAZA
	}


	f1.open("headers-in-binary.txt", ios::out | ios::trunc | ios::binary);
	if (f1.is_open())
		write_headers_to_binary_file(f1, db->getTables());	
	else
		cout << "\nERROR headers-in-binary.txt cannot be opened. See if the file exists and if it is in the correct path. If yes, check if you have permisions\n";
	f1.close();

	f2.open("content-in-binary.txt", ios::out | ios::trunc | ios::binary);
	if (f2.is_open())
		write_content_to_binary_file(f2, db->getTables());
	else
		cout << "\nERROR content-in-binary.txt cannot be opened. See if the file exists and if it is in the correct path. If yes, check if you have permisions\n";
	f2.close();
}

//---------------------------------> TABLE CLASS <-------------------------------------
// GET for Table class
string Table::getName() {
	return this->name;
}

int Header::getNrColumns() {
	return this->tableHead.size();
}

vector<string> Header::getTableHead()
{
	return this->tableHead;
}

vector<string> Header::getDataType()
{
	return this->dataType;
}

vector<int> Header::getDataSize()
{
	return this->dataSize;
}

vector<string> Header::getImplicitValue()
{
	return this->implicitValue;
}

vector<Entry> Table::getEntries()
{
	return this->entries;
}

vector<Entry>& Table::getRefEntries()
{
	return this->entries;
}

Header Table::getHeader()
{
	return this->head;
}

// SET for Table class
void Table::setName(string newName)
{
	if(newName.length()>1)
	{
		this->name = newName;
	}
}

void Header::setTableHead(vector<string> newTableHead)
{
	if(!newTableHead.empty())
	this->tableHead = newTableHead;
}

void Header::setDataType(vector<string> newDataType)
{
	if(!newDataType.empty())
	this->dataType = newDataType;
}

void Header::setDataSize(vector<int> newDataSize)
{
	if(!newDataSize.empty())
	this->dataSize = newDataSize;
}

void Header::setImplicitValue(vector<string> newImplicitValue)
{
	if(!newImplicitValue.empty())
	this->implicitValue = newImplicitValue;
}

void Table::setEntries(vector<Entry> newEntries)
{
	if(!newEntries.empty())
	this->entries = newEntries;
}

void Table::writeToFiles(const char* fileName) {
	ofstream f(fileName);
	if (!f.good()) {
		return;
	}
	f << *this;
	f.close();
}

//---------------------------------> ENTRY CLASS <-------------------------------------
// GET for Entry class
int Entry::getNumberArguments()
{
	return this->numberArguments;
}

string* Entry::getArguments()
{
	return this->arguments;
}

// SET for Entry class
void Entry::setArguments(int newNumberArguments, string* newArguments)
{
	try
	{
		if (newNumberArguments != this->numberArguments)
		{
			exception e("\nNumar invalid de argumente!\n");
			throw e;
		}
		if (newNumberArguments > 0 && newArguments != nullptr)
		{
			delete[] this->arguments;
			this->numberArguments = newNumberArguments;
			this->arguments = new string[newNumberArguments];
			for (int i = 0; i < newNumberArguments; i++)
			{
				this->arguments[i] = newArguments[i];
			}
		}
	}
	catch (exception e) 
	{
		cout << e.what();
	}
}

void Entry::writeToFiles(const char* fileName) {
	ofstream f(fileName, ios::app);
	if (!f.good()) {
		return;
	}
	f << endl << *this;
	f.close();
}

void take_user_input_from_file(ifstream& f, vector<string>& inputs) { // crapa aici in functie momentan 
	int i = 0;
	string aux;
	char* auxCh = new char[150];
	bool allInputValid = true;
	while(f.getline(auxCh, 149)){ // citim in auxCh care tine minte linia ca un char*
		aux = auxCh; // facem conversia intr-un std::string
		if (aux.size() == 0) {
			continue;
		}
		if (check_for_parenthesis_and_commas(aux)) {
			for (int i = 0; i < aux.size(); i++) {
				if (aux[i] >= 'A' && aux[i] <= 'Z') {
					aux[i] += 32;										//value of 'a' - 'A'
				}
			}
		}
		else {
			cout << "\nSintaxa gresita! Sintaxa corecta are virgule, dupa virgule spatii, iar toate parantezele deschise trebuie si inchise!\n";
			aux = "invalid";
			allInputValid = false;
		}
		inputs.push_back(aux);
	}
	delete[] auxCh;
}

void Database::readFromFiles(int& argsc, char* argsv[]) {
	vector<char*> textFiles;
	bool allValidFiles = true;
	try {
		if (argsc > 6) {
			throw new exception("\nPrea multe fisiere text introudse");
		}
		for (int i = 1; i < argsc; i++) {
			char* aux = argsv[i] + (strlen(argsv[i]) - 4); // ia ultimele patru caractere din argument
			if (!strcmp(".txt", aux)) { // daca aux == ".txt"
				if(fileExists(argsv[i])) {
					textFiles.push_back(argsv[i]); // tinem minte fisierul ca fisier text
				}
				else {
					allValidFiles = false;
					throw new exception("\nUnul sau mai multe fisiere nu exista!");
				}
			}
			else {
				allValidFiles = false;
				throw new exception("\nUnul sau mai multe fisiere nu au extensia .txt! Command Line Input invalid!");
			}
		}
	}
	catch (exception e) {
		cout << e.what() << endl;
	}
	if (allValidFiles) { // daca toate fisierele au extensia valida
		for (int i = 0; i < textFiles.size(); i++) { // luam fiecare fisier in parte si executam comenzile in el 
			ifstream f(textFiles[i]);

			vector<string> inputs;
			take_user_input_from_file(f, inputs); // inputurile din fisier
			for (int j = 0; j < inputs.size(); j++) {
				string* lineWords = split_string_into_words(inputs[j]);
				identify_command_type(lineWords, this->getTables());
			}

			f.close();
		}
	}
}

void write_headers_to_binary_file(fstream& f, vector<Table>& t)
{
	//deoarece toate tabele existente trebuie sa aiba deja un format corespunzator, m-am gandit in fisierul binar
	//in loc de : sizeof(vector1) data(vector1) int float sizeof(vector2) data(vector2) ... etc (formatul de la seminarul 11 de poo)
	//sa am : int N (numar_de_tabele);; nume_tabel_1 header_1 (adica tableHead_1[j], dataType_1[j], dataSize_1[j], implicitValue_1[j]), ... nume_tabel_N header_N 
	//(unde j este nr coloane ale tabelului la care face referinta)
	//din moment ce oricum size-ul vectorilor stl din header au toti aceeasi marime, anume egala cu numarul de tabele existente in baza de date 
	
	//in final rezulta ceva de genul:
	//nr_tabele ;; nume_tabel[i] ;; nr_coloane_tabel[i] ;; header[i] ( == tableHead_[i][j], dataType_[i][j], dataSize_[i][j], implicitValue_[i][j] , unde j = nr coloane, j=[0, nr_coloane]) ;; 

	//ex vizionat in text:
	//2 lungime_nume_tabel_1(=9) angajati 2 lungime_string(=5) nume lungime_string(=5) text 20 lungime_string(=1) 0 lungime_string salariu lungime_string int 10 lungime_string 0
	//		lungime_nume_tabel_2 firme 2 lungime_string cui lungime_string text 6 lungime_string 0 lungime_string capital lungime_string int 30 lungime_string 0
	
	int nrTables = t.size();
	string name;
	string headerInfo;		//that will be tableHead, dataType or implicitValue
	int headerDataSize;		//dataSize
	int lenght;				//va stoca lungimile vectorilor ce urmeaza a fi scrisi in fisier in binar
	int nrColumns;			//numarul de coloane al unui tabel la un moment dat

	f.write((char*)&nrTables, sizeof(int));			//cate tabele avem in total

	for (int i = 0; i < nrTables; i++) {			//pt fiecare tabel vom afisa nume, header
		name = t[i].getName();
		lenght = name.size() + 1;
		f.write((char*)&lenght, sizeof(int));
		f.write(name.data(), lenght * sizeof(char));

		nrColumns = t[i].getHeader().getTableHead().size();
		f.write((char*)&nrColumns, sizeof(int));
		for (int j = 0; j < nrColumns; j++) {				//pt atatea coloane cate are tabelul, vom afisa headerul respectiv
			//pentru tableHead
			headerInfo = t[i].getHeader().getTableHead()[j];
			lenght = headerInfo.size() + 1;
			f.write((char*)&lenght, sizeof(int));
			f.write(headerInfo.data(), lenght * sizeof(char));
			//pt dataType
			headerInfo = t[i].getHeader().getDataType()[j];
			lenght = headerInfo.size() + 1;
			f.write((char*)&lenght, sizeof(int));
			f.write(headerInfo.data(), lenght * sizeof(char));
			//pt dataSize
			headerDataSize = t[i].getHeader().getDataSize()[j];
			f.write((char*)&headerDataSize, sizeof(int));
			//pt implicitValue
			headerInfo = t[i].getHeader().getImplicitValue()[j];
			lenght = headerInfo.size() + 1;
			f.write((char*)&lenght, sizeof(int));
			f.write(headerInfo.data(), lenght * sizeof(char));
		}	
	}
}

void write_content_to_binary_file(fstream& f, vector<Table>& t)
{
	//vom face referinta la structura tabelelor cunoscuta deja din clasa HEAD a fiecarei tabele in parte, astfel ca vom cunoaste deja lucruri esentiale, precum:
	//nr de coloane care este egal cu numarul de argumente din entry-urile respectivei tabele (vezi clasa Table si Head)
	//si in momentul apelarii acestei functii avel deja create tabelele cu formatul lor, insa goale, fara entry-uri
	
	//format:
	//nr_tabele ;; nr_entries[i] ;; entries[i][0] ... entries[i][j] ;; (unde i = nr de tabele;   j = nr entries per tabela)
	
	//ex vizionat in text:
	//4 3 lungime_string(=9) Valentin lungime_string(=5) 1000 lungime_string(=9) Cristian lungime_string(=5) 2000 lungime_string(=7) Teodor lungime_string(=5) 3000 0 7 lungime_string mar 
	//		lungime_string banana lungime_string para lungime_string mandarina lungime_string portocala lungime_string nectarina lungime_string gutuie 0

	int nrTables = t.size();
	int nrEntries;									//nr of entries per table[i], where i is count for loop
	int nrColumns;	// == Entry::numberArguments
	int lenght;
	int nrArguments;	//look into class Entry
	string partOfEntry;	//holds the i-th string at the i iteration of the loop of the member string* arguments of class Entry

	f.write((char*)&nrTables, sizeof(int));
	for (int i = 0; i < nrTables; i++) {
		nrColumns = t[i].getHeader().getTableHead().size();
		nrEntries = t[i].getEntries().size();
		f.write((char*)&nrEntries, sizeof(int));
		for (int j = 0; j < nrEntries; j++) {
			nrArguments = t[i].getEntries()[j].getNumberArguments();
			//aici se mai putea si sa scriem in fisier nr de argumente ale fiecarui entry in parte, dar deja stim ca este egal cu nr de coloane al fiecarei tabele
			for (int k = 0; k < nrArguments; k++) {
				lenght = t[i].getEntries()[j].getArguments()[k].size() + 1;
				f.write((char*)&lenght, sizeof(int));
				partOfEntry = t[i].getEntries()[j].getArguments()[k];
				f.write(partOfEntry.data(), lenght * sizeof(char));
			}
		}
	}
}

void read_headers_from_binary_file(fstream& f, vector<Table>& t)
{
	//ex vizionat in text:
	//2 lungime_nume_tabel_1(=9) angajati 2 lungime_string(=5) nume lungime_string(=5) text 20 lungime_string(=1) 0 lungime_string salariu lungime_string int 10 lungime_string 0
	//		lungime_nume_tabel_2 firme 2 lungime_string cui lungime_string text 6 lungime_string 0 lungime_string capital lungime_string int 30 lungime_string 0
	//see write_headers_to_binary_file for more info regarding format and such
	
	//deoarece codul este extrem de haotic gasesc rezonabil sa citesc din fisierul binar intr-un string* pe care sa-l pasez functiei ce interpreteaza comenzi
	//de parca aceasta ar fi fost pass-ata de la consola. O alta optiune ar fi fost folosirea de constructori si metode, insa odata incercata te loveste realitatea

	int nrTables;
	int nrColumns;	//nr de coloane a unei tabele la un moment dat
	int length;		//lungimea unui vector de diferite tipuri care trebuie citit
	int commandLength; //the length of the i-th command
	int dataSize;	//will hold dataSize[i][j] of i table and j column
	int number;
	int z;			//contor that is used to keep count on when we reach the 3rd element of the header which is int and not string
					//so we give it a different treatment when reading from file and interpreting the data that was read
	string str;		//string auxiliar urmand a fi folosit pentru diferite citiri
	string* command = NULL; //create table t nume text 10 0 salariu int 6 0 urmand a fi pasat lui identify_command_type

	f.read((char*)&nrTables, sizeof(int));
	for (int i = 0; i < nrTables; i++) {	
		f.read((char*)&length, sizeof(int));
		char* buffer = new char[length];
		f.read(buffer, length);
		str = buffer;
		delete[] buffer;
		f.read((char*)&nrColumns, sizeof(int));
		commandLength = 4 + nrColumns * 4;		//primele 4 sunt nr de argumente, create, table, nume_tabela
		command = new string[commandLength]; 
		number = commandLength - 1;
		command[0] = to_string(number);
		command[1] = "create";
		command[2] = "table";
		command[3] = str;

		z = 0;
		for (int j = 0; j < nrColumns*4; j++) {
			z++;
			if (z == 3) {
				z = -1;
				f.read((char*)&dataSize, sizeof(int));
				command[j + 4] = to_string(dataSize);
				continue;
			}
			f.read((char*)&length, sizeof(int));
			char* buffer = new char[length];
			f.read(buffer, length);
			command[j + 4] = buffer;
			delete[] buffer;
		}
		
		identify_command_type(command, t); //identify_command_type(.,.) also does DELETE[] command;; doing it twice will cause undefined behaviour
	}
}

void read_content_from_binary_file(fstream& f, vector<Table>& t)
{
	//ex vizionat in text:
	//4 3 lungime_string(=9) Valentin lungime_string(=5) 1000 lungime_string(=9) Cristian lungime_string(=5) 2000 lungime_string(=7) Teodor lungime_string(=5) 3000 0 7 lungime_string mar 
	//		lungime_string banana lungime_string para lungime_string mandarina lungime_string portocala lungime_string nectarina lungime_string gutuie 0
	//see write_content_to_binary_filefor more info regarding format and such eventual si read_headers_...

	int nrTables;
	int nrEntries;
	int nrColumns; //numberArguments from class Entry of i-th table
	int length;		//lungimea unui vector de diferite tipuri care trebuie citit
	int commandLength; //the length of the i-th command
	int number;
	string str;		//string auxiliar urmand a fi folosit pentru diferite citiri
	string* command = NULL; //insert into t values Adrian, 1000 urmand a fi pasat lui identify_command_type

	f.read((char*)&nrTables, sizeof(int));
	for (int i = 0; i < nrTables; i++) {
		f.read((char*)&nrEntries, sizeof(int));
		nrColumns = t[i].getHeader().getTableHead().size();
		for (int j = 0; j < nrEntries; j++) {
			commandLength = 5 + nrColumns;
			command = new string[commandLength];
			number = commandLength - 1;
			command[0] = to_string(number);
			command[1] = "insert";
			command[2] = "into";
			command[3] = t[i].getName();
			command[4] = "values";
			for (int k = 0; k < nrColumns; k++) {
				f.read((char*)&length, sizeof(int));
				char* buffer = new char[length];
				f.read(buffer, length);
				command[k + 5] = buffer;
				delete[] buffer;
			}
			identify_command_type(command, t); //this function also does delete[] command
		}
	}
}