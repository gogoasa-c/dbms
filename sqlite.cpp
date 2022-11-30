// sqlite.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "clase_si_functii.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    vector<Table> tables;
    cout << "Alpha v1.5.2 spre 6 dar nu prea\n";
    cout << "ATENTIE: ENTER confirma inputul/comanda introdusa. EXIT incheie executia. Daca doriti anularea unei comenzi introduceti o comanda eronata.\n\n";   //IMPLEMENTAT. PARE SA FUNCTIONEZE

    while (true) {
        int aux = identify_command_type(split_string_into_words(take_user_input_and_convert_lowercase()), tables);     //am modificat return type-ul ca uneori dupa 2-3 display-uri de tabel nu mai functiona
                                                                                                                       //suspectam ca e fiindca aveam un while true in ea care se apela pe sine recursiv si poate nu ii placea asta idk
        if (aux == 0)
            break;//FUNCTIONEAZA
    }
   
    
    /* string currInput = "create table t id number 100 -1 nume varchar2 255 null";
    string* currInputWords = new string[100];
    currInputWords = split_string_into_words(currInput);
    identify_command_type(currInputWords, tables);
    cout << tables[0];
    delete[] currInputWords;

    currInputWords = new string[100];
    currInput = "display table t";
    currInputWords = split_string_into_words(currInput);
    identify_command_type(currInputWords, tables);*/
    

    /*TO DO LIST
    * 
    * 1) Functia "take_user_input_and_convert_lowercase()" se foloseste de functia "check_for_parenthesis_and_commas(string)" pentru a afisa mesaj de eroare daca sunt paranteze
    * puse aiurea, insa nu stiu cum sa o fac sa nu iasa cu totul din executia programului main, ci doar sa ignore stringul eronat si sa astepte o noua comanda corespunzatoare,
    * astfel ca am comentat parte din cod la functia "take_user_input_and_convert_lowercase()"
    * 
    * 2) Am "implementat" operatorul [], insa daca indexul este invalid, ar trebui sa returnam in continuare o referinta la clasa Entry, insa! problema este ca noi nu am implementat inca 
    * comanda "delete from", rezultand in inabilitatea de a sterge inregistrarea eronata din nume_tabel.entries[index_handicapat].
    * 
    * 3) DE TESTAT: implementarea operatorilor :
    *       - operatorii   >   <   >=   <=
    *       - operator      ==
    *       - operator      !
    *       - operator      []
    *       - operator      >>              //ex:   cin >> nume_tabel       (   istream& operator>>(istream& in, Table& tb)   )          
    * 
    * 
    * 
    *   NOTE IMPORTANTE DE CITIT:
    * 
    * 1) supraincarcarea operatorului >> pentru citire de entry noua in obiect de tip Table ar putea fi utilizat la implementarea comenzii UPDATE nume_tabela SET nume_coloana ...
    * 
    * 
    * 
    */

    return 0;
}
