// sqlite.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "clase_si_functii.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    cout << "Alpha v1.1\n";
    cout << "ATENTIE: ENTER confirma inputul/comanda introdusa. EXIT incheie executia. Daca doriti anularea unei comenzi introduceti o comanda eronata.\n\n"; //neimplementat inca

    //exemplificat pe pasi ar trebui sa functioneze asa insa string v[100] nu este valoare asignabila si da eroare la functia split_...
    /*string v[100];
    string test = take_user_input_and_convert_lowercase();
    string v[100] = split_string_into_words(test);
    int rez = identify_command_type(v);*/

    //std::copy(split_string_into_words(test), split_string_into_words(test) + 99, v); // asa da eroare dar pe net zice ca e o metoda sa copiezi oarecum?

    //cout << identify_command_type(split_string_into_words(take_user_input_and_convert_lowercase())); //ideal ar trebui sa mearga asa dar da eroare

    return 0;
}
