#include <iostream>
#include "classes.h"
#include "template.h"

using namespace std;

int main(int argc, char* argv[])
{
    string i1="Dane1.txt", i2="Dane2.txt", o="Dane3.txt";
    //string i1, i2, o;
    //parameters_check(argc, argv, i1, i2, o);

    List<Tab1::Dane> lista1;
    List<Tab2::Wiezienie> lista2;
    Tab1 tab1;
    Tab2 tab2;

    tab1.odczyt(i1, lista1);
    tab2.odczyt(i2, lista2);

    Interfejs interfejs;
    interfejs.program(lista1, lista2, o);

    return 0;
}