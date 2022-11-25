// sqlite.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "clase_si_functii.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    vector<Table> tables;
    cout << "Alpha v1.5\n";
    cout << "ATENTIE: ENTER confirma inputul/comanda introdusa. EXIT incheie executia. Daca doriti anularea unei comenzi introduceti o comanda eronata.\n\n";   //IMPLEMENTAT. PARE SA FUNCTIONEZE

    identify_command_type(split_string_into_words(take_user_input_and_convert_lowercase()), tables);                                                            //FUNCTIONEAZA
   
    
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
    * 1)break(exit) instruction does infinite loop in identify_command_type(); - doesnt ent program execution
    * 2)identify command type doesn't check if missing arguments. ex:: word[3] = inexistent => mesaj aiurea
    * 3)we could try to convert the functions that were implemented into classes
    *   reference:
    *           •	incepeti cu o functie/clasa generica care identifica tipul de comanda (SELECT, UPDATE etc.)
                •   Implementati clase specifice care vor valida un format si parametri specifici tipului de comanda

    */

    return 0;
}
