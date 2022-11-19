// sqlite.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "clase_si_functii.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    cout << "Alpha v1.1\n";
    cout << "ATENTIE: ENTER confirma inputul/comanda introdusa. EXIT incheie executia. Daca doriti anularea unei comenzi introduceti o comanda eronata.\n\n";   //neimplementat inca

    cout << identify_command_type(split_string_into_words(take_user_input_and_convert_lowercase()));                                                            //FUNCTIONEAZA

    return 0;
}
