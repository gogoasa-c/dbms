// sqlite.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "clase_si_functii.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    vector<Table> tables;
    cout << "Alpha v1.1\n";
    cout << "ATENTIE: ENTER confirma inputul/comanda introdusa. EXIT incheie executia. Daca doriti anularea unei comenzi introduceti o comanda eronata.\n\n";   //neimplementat inca

    //cout << identify_command_type(split_string_into_words(take_user_input_and_convert_lowercase()));                                                            //FUNCTIONEAZA
    string currInput = "create table t id number 100 -1 nume varchar2 255 null";
    string* currInputWords = new string[100];
    currInputWords = split_string_into_words(currInput);
    identify_command_type(currInputWords, tables);
    return 0;
}
