// sqlite.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "dummy.h"
using namespace std;

int main()
{
    cout << "Hello World!\n";
    Dummy a(5);
    std::cout << "\nFct de grad I a obiectului Dummy:a este = " << a.functie(7, -3);

    return 0;
}
