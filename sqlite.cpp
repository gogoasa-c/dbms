// sqlite.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "clase_si_functii.h"
#include <iostream>

using namespace std;

int main()
{
    Database* db = db->getInstance();

    vector<Table> tables;
    cout << "Beta v0.9\n";
    cout << "ATENTIE: ENTER confirma inputul/comanda introdusa. EXIT incheie executia. Daca doriti anularea unei comenzi introduceti o comanda eronata.\n\n";   //IMPLEMENTAT. PARE SA FUNCTIONEZE

    while (true) {
        int aux = identify_command_type(split_string_into_words(take_user_input_and_convert_lowercase()), db->getTables());     //am modificat return type-ul ca uneori dupa 2-3 display-uri de tabel nu mai functiona
                                                                                                                       //suspectam ca e fiindca aveam un while true in ea care se apela pe sine recursiv si poate nu ii placea asta idk
        if (aux == 0)
            break;//FUNCTIONEAZA
    }
    
    /*TO DO LIST (PT PERFECTIONARE / LUSTRUIRE)
    * 
    * -1) Argumentele noastre sunt toate de tip string si desi ar trebui sa aiba tip de text/int/ etc ele pot fi totusi introduse aiurea. (ex: coloana de tip int poate prin insert sa aiba in entry la coloana de tip int valoarea abcdefg)
    * 
    * 0) DELETE-ul m-a infrant. im sorry. SOS
    * 
    * 1) Daca tipul de coloana introdus in comanda create table este int, inregistrarea accepta in continuare litere text pe care le introuce prin insert into nume_tabel values ...
    *     
    * 2) insert into nu permite inserarea decat a unui singur entry la un moment dat. probabil ca ar trebui sa permita introucerea a multiple entry-uri daca e cazul.
    * 
    * 3) de adaugat membru constant si static (ex: constant poate fi un index; static poate fi numarul tabelei)
    * 
    * 4) de adaugat celelalte supraincarcari de operatori necesari din cerinta proiectului (minim un operator matematic (+,-,* sau /) ;; ++ sau -- (cu cele 2 forme) ;; operatorul cast (catre orice tip) explicit sau implicit)
    * 
    */

    
    
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



    return 0;
}
