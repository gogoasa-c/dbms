//aici gasim antetul/definitiile claselor si functiilor
#pragma once
#include <iostream>
#include <string>
using namespace std;

string take_user_input_and_convert_lowercase();		//preia inputul decat de la tastatura (eventual va trebui modificata pt a prelua si din fisiere)
													//si converteste tot string-ul la lowercase pt a nu conta CAPS/NO CAPS

string* split_string_into_words(string);			//imparte string-ul initial in vector de string-uri care cuvinte/argumentele; word[j] = al j-lea 
													//cuvant/argument introdus de la tastatura
													//vom putea refolosi functia si pt a pasa la clase cuvant cu cuvant stringul si a asigna corespunzator
													//membrilor valorile din argumente

int identify_command_type(string*);					//returneaza 0 pt lucru cu TABLE, 1-4 pt comenzi CRUD

