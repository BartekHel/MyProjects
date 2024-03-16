#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<windows.h>
#include<iomanip>
#include "classes.h"
#include "template.h"

using namespace std;

void Tab1::odczyt(const string& nazwa, List<Tab1::Dane>& lista) {
    ifstream plik(nazwa);
    if (plik) {
        Dane dane;
        string linia;
        while (getline(plik, linia)) {
            stringstream ss(linia);

            getline(ss, linia, ',');
            dane.id = stoi(linia);

            getline(ss >> ws, dane.imie, ',');
            getline(ss >> ws, dane.nazwisko, ',');

            getline(ss, linia, '.');
            dane.dzien = stoi(linia);
            getline(ss, linia, '.');
            dane.miesiac = stoi(linia);
            getline(ss, linia, ',');
            dane.rok = stoi(linia);

            ss >> dane.plec;

            lista.push_back(dane);
        }
        plik.close();
    }
}



void Tab2::odczyt(const string& nazwa, List<Tab2::Wiezienie>& lista) {
    ifstream plik(nazwa);
    if (plik) {
        Wiezienie w11;
        string linia;
        while (getline(plik, linia)) {
            stringstream ss(linia);

            getline(ss, linia, ',');
            w11.id = stoi(linia);

            getline(ss >> ws, w11.przewinienie, ',');

            getline(ss, linia, ',');
            if (linia.find("lat") != string::npos) {
                w11.jednostka = "lat";
                linia.erase(linia.find("lat"), 3);
                w11.dlugosc = stoi(linia);
            }
            else if (linia.find("lata") != string::npos) {
                w11.jednostka = "lata";
                linia.erase(linia.find("lata"), 4);
                w11.dlugosc = stoi(linia);
            }
            else if (linia.find("rok") != string::npos) {
                w11.jednostka = "rok";
                linia.erase(linia.find("rok"), 3);
                w11.dlugosc = stoi(linia);
            }
            else if (linia.find("miesiecy") != string::npos) {
                w11.jednostka = "miesiecy";
                linia.erase(linia.find("miesiecy"), 8);
                w11.dlugosc = stoi(linia);
            }
            else if (linia.find("miesiace") != string::npos) {
                w11.jednostka = "miesiace";
                linia.erase(linia.find("miesiace"), 8);
                w11.dlugosc = stoi(linia);
            }
            else if (linia.find("miesiac") != string::npos) {
                w11.jednostka = "miesiac";
                linia.erase(linia.find("miesiac"), 8);
                w11.dlugosc = stoi(linia);
            }
            else {
                w11.jednostka = "czasu";
                w11.dlugosc = stoi(linia);
            }

            getline(ss >> ws, w11.cela, ',');

            lista.push_back(w11);
        }
        plik.close();
    }
}



void Interfejs::menu() {
    system("CLS");
    cout << "Rejestr wiezienny" << endl;
    cout << "1. Push" << endl;
    cout << "2. Pop" << endl;
    cout << "3. Remove" << endl;
    cout << "4. Get element" << endl;
    cout << "5. Get index" << endl;
    cout << "6. Sort" << endl;
    cout << "7. Count" << endl;
    cout << "8. Arrest length" << endl;
    cout << "9. Avarage arrest length" << endl;
    cout << "10. Avarage length greater than" << endl;
    cout << "11. Prison block check" << endl;
    cout << "12. Birth date check" << endl;
    cout << "13. Lists connections" << endl;
    cout << "14. Display" << endl;
    cout << "15. Clear" << endl;
    cout << "16. Save" << endl;
    cout << "0. Exit" << endl;
    cout << "Wybierz opcje: " << endl;
}

int Interfejs::wybor() {
    int choice;
    system("CLS");
    cout << "Wybierz liste: " << endl;
    cout << "1. Tabela z danymi osobowymi " << endl;
    cout << "2. Tabela z danymi wieziennymi " << endl;
    cout << "3. Tabela z tymczasowymi danymi osobowymi " << endl;
    cout << "4. Tabela z tymczasowymi danymi wieziennymi" << endl;
    cin >> choice;
    return choice;
}

void Interfejs::blad() {
    system("CLS");
    cout << "Blad! Niepoprawna opcja! " << endl;
    Sleep(1000);
}

void Interfejs::program(List<Tab1::Dane>& lista1, List<Tab2::Wiezienie>& lista2, const string& o) {
    List<Tab1::Dane> lista1_tmp;
    List<Tab2::Wiezienie> lista2_tmp;
    Tab1::Dane obj1;
    Tab2::Wiezienie obj2;
    string element;
    int choice, index;
    bool quit = false;
    char blok;
    int tab[6];

    do {
        menu();
        cin >> choice;
        switch (choice) {
        case 1:
            choice = wybor();
            system("CLS");
            cout << "Wybierz opcje: " << endl;
            cout << "1. Push_front " << endl;
            cout << "2. Push_back " << endl;
            if (choice == 1) {
                cin >> choice;
                system("CLS");
                cout << "Wpisz element: " << endl;
                cin >> obj1;
                if (choice == 1) {
                    lista1.push_front(obj1);
                    system("CLS");
                    cout << "Element zostal dodany na poczatek. " << endl;
                    Sleep(1000);
                }
                else if (choice == 2) {
                    lista1.push_back(obj1);
                    system("CLS");
                    cout << "Element zostal dodany na koniec. " << endl;
                    Sleep(1000);
                }
                else
                    blad();
            }
            else if (choice == 2) {
                cin >> choice;
                system("CLS");
                cout << "Wpisz element: " << endl;
                cin >> obj2;
                if (choice == 1) {
                    lista2.push_front(obj2);
                    system("CLS");
                    cout << "Element zostal dodany na poczatek. " << endl;
                    Sleep(1000);
                }
                else if (choice == 2) {
                    lista2.push_back(obj2);
                    system("CLS");
                    cout << "Element zostal dodany na koniec. " << endl;
                    Sleep(1000);
                }
                else
                    blad();
            }
            else if (choice == 3) {
                cin >> choice;
                system("CLS");
                cout << "Wpisz element: " << endl;
                cin >> obj1;
                if (choice == 1) {
                    lista1_tmp.push_front(obj1);
                    system("CLS");
                    cout << "Element zostal dodany na poczatek. " << endl;
                    Sleep(1000);
                }
                else if (choice == 2) {
                    lista1_tmp.push_back(obj1);
                    system("CLS");
                    cout << "Element zostal dodany na koniec. " << endl;
                    Sleep(1000);
                }
                else
                    blad();
            }
            else if (choice == 4) {
                cin >> choice;
                system("CLS");
                cout << "Wpisz element: " << endl;
                cin >> obj2;
                if (choice == 1) {
                    lista2_tmp.push_front(obj2);
                    system("CLS");
                    cout << "Element zostal dodany na poczatek. " << endl;
                    Sleep(1000);
                }
                else if (choice == 2) {
                    lista2_tmp.push_back(obj2);
                    system("CLS");
                    cout << "Element zostal dodany na koniec. " << endl;
                    Sleep(1000);
                }
                else
                    blad();
            }
            else
                 blad();
            break;
        case 2:
            choice = wybor();
            system("CLS");
            cout << "Wybierz opcje: " << endl;
            cout << "1. Pop_front " << endl;
            cout << "2. Pop_back " << endl;
            cout << "3. Pop (index) " << endl;
            if (choice == 1) {
                cin >> choice;
                if (choice == 1) {
                    lista1.pop_front();
                    system("CLS");
                    cout << "Element z poczatku zostal usuniety. " << endl;
                    Sleep(1000);
                }
                else if (choice == 2) {
                    lista1.pop_back();
                    system("CLS");
                    cout << "Element z konca zostal usuniety. " << endl;
                    Sleep(1000);
                }
                else if (choice == 3) {
                    system("CLS");
                    cout << "Wpisz index elementu, ktory chcesz usunac: " << endl;
                    cin >> index;
                    lista1.pop(index);
                    system("CLS");
                    cout << "Element o indexie " << index << " zostal usuniety. " << endl;
                    Sleep(1000);
                }
                else
                    blad();
            }
            else if (choice == 2) {
                cin >> choice;
                if (choice == 1) {
                    lista2.pop_front();
                    system("CLS");
                    cout << "Element z poczatku zostal usuniety. " << endl;
                    Sleep(1000);
                }
                else if (choice == 2) {
                    lista2.pop_back();
                    system("CLS");
                    cout << "Element z konca zostal usuniety. " << endl;
                    Sleep(1000);
                }
                else if (choice == 3) {
                    system("CLS");
                    cout << "Wpisz index elementu, ktory chcesz usunac: " << endl;
                    cin >> index;
                    lista2.pop(index);
                    system("CLS");
                    cout << "Element o id " << index << " zostal usuniety. " << endl;
                    Sleep(1000);
                }
                else
                    blad();
            }
            else if (choice == 3) {
                cin >> choice;
                if (choice == 1) {
                    lista1_tmp.pop_front();
                    system("CLS");
                    cout << "Element z poczatku zostal usuniety. " << endl;
                    Sleep(1000);
                }
                else if (choice == 2) {
                    lista1_tmp.pop_back();
                    system("CLS");
                    cout << "Element z konca zostal usuniety. " << endl;
                    Sleep(1000);
                }
                else if (choice == 3) {
                    system("CLS");
                    cout << "Wpisz index elementu, ktory chcesz usunac: " << endl;
                    cin >> index;
                    lista1_tmp.pop(index);
                    system("CLS");
                    cout << "Element o id " << index << " zostal usuniety. " << endl;
                    Sleep(1000);
                }
                else
                    blad();
            }
            else if (choice == 4) {
                cin >> choice;
                if (choice == 1) {
                    lista2_tmp.pop_front();
                    system("CLS");
                    cout << "Element z poczatku zostal usuniety. " << endl;
                    Sleep(1000);
                }
                else if (choice == 2) {
                    lista2_tmp.pop_back();
                    system("CLS");
                    cout << "Element z konca zostal usuniety. " << endl;
                    Sleep(1000);
                }
                else if (choice == 3) {
                    system("CLS");
                    cout << "Wpisz index elementu, ktory chcesz usunac: " << endl;
                    cin >> index;
                    lista2_tmp.pop(index);
                    system("CLS");
                    cout << "Element o id " << index << " zostal usuniety. " << endl;
                    Sleep(1000);
                }
                else
                    blad();
            }
            else
                blad();
            break;
        case 3:
            choice = wybor();
            system("CLS");
            cout << "Wpisz elementy, ktore chcesz usunac z listy: " << endl;
            if (choice == 1) {
                cin >> obj1;
                lista1.remove(obj1);
                system("CLS");
                cout << "Elementy zostaly usuniete. " << endl;
                Sleep(1000);
            }
            else if (choice == 2) {
                cin >> obj2;
                lista2.remove(obj2);
                system("CLS");
                cout << "Elementy zostaly usuniete. " << endl;
                Sleep(1000);
            }
            else if (choice == 3) {
                cin >> obj1;
                lista1_tmp.remove(obj1);
                system("CLS");
                cout << "Elementy zostaly usuniete. " << endl;
                Sleep(1000);
            }
            else if (choice == 4) {
                cin >> obj2;
                lista2_tmp.remove(obj2);
                system("CLS");
                cout << "Elementy zostaly usuniete. " << endl;
                Sleep(1000);
            }
            else
                blad();
            break;
        case 4:
            choice = wybor();
            system("CLS");
            cout << "Po czym chcesz wyszukac element? " << endl;
            cout << "1. Po indexie " << endl;
            cout << "2. Po id " << endl;
            if (choice == 1) {
                cin >> choice;
                system("CLS");
                if (choice == 1) {
                    cout << "Wpisz index szukanego elementu: " << endl;
                    cin >> index;
                    lista1_tmp.clear();
                    lista1_tmp.push_back(lista1.get_element(index));
                    system("CLS");
                    cout << "Element zostal zapisany w pamieci (w liscie tymczasowej). " << endl;
                    Sleep(1000);
                }
                else if (choice == 1) {
                    cout << "Wpisz id szukanego elementu: " << endl;
                    cin >> index;
                    lista1_tmp.clear();
                    lista1_tmp.push_back(lista1.get_element2(index));
                    system("CLS");
                    cout << "Element zostal zapisany w pamieci (w liscie tymczasowej). " << endl;
                    Sleep(1000);
                }
                else
                    blad();
            }
            else if (choice == 2) {
                cin >> choice;
                system("CLS");
                if (choice == 1) {
                    cout << "Wpisz index szukanego elementu: " << endl;
                    cin >> index;
                    lista2_tmp.clear();
                    lista2_tmp.push_back(lista2.get_element(index));
                    system("CLS");
                    cout << "Element zostal zapisany w pamieci (w liscie tymczasowej). " << endl;
                    Sleep(1000);
                }
                else if (choice == 1) {
                    cout << "Wpisz id szukanego elementu: " << endl;
                    cin >> index;
                    lista2_tmp.clear();
                    lista2_tmp.push_back(lista2.get_element2(index));
                    system("CLS");
                    cout << "Element zostal zapisany w pamieci (w liscie tymczasowej). " << endl;
                    Sleep(1000);
                }
                else
                    blad();
            }
            else if (choice == 3) {
                cin >> choice;
                system("CLS");
                if (choice == 1) {
                    cout << "Wpisz index szukanego elementu: " << endl;
                    cin >> index;
                    Tab1::Dane tmp1 = lista1_tmp.get_element(index);
                    lista1_tmp.clear();
                    lista1_tmp.push_back(tmp1);
                    system("CLS");
                    cout << "Element zostal zapisany w pamieci (w liscie tymczasowej). " << endl;
                    Sleep(1000);
                }
                else if (choice == 1) {
                    cout << "Wpisz id szukanego elementu: " << endl;
                    cin >> index;
                    Tab1::Dane tmp1 = lista1_tmp.get_element(index);
                    lista1_tmp.clear();
                    lista1_tmp.push_back(tmp1);
                    system("CLS");
                    cout << "Element zostal zapisany w pamieci (w liscie tymczasowej). " << endl;
                    Sleep(1000);
                }
                else
                    blad();
            }
            else if (choice == 4) {
                cin >> choice;
                system("CLS");
                if (choice == 1) {
                    cout << "Wpisz index szukanego elementu: " << endl;
                    cin >> index;
                    Tab2::Wiezienie tmp2 = lista2_tmp.get_element(index);
                    lista2_tmp.clear();
                    lista2_tmp.push_back(tmp2);
                    system("CLS");
                    cout << "Element zostal zapisany w pamieci (w liscie tymczasowej). " << endl;
                    Sleep(1000);
                }
                else if (choice == 1) {
                    cout << "Wpisz id szukanego elementu: " << endl;
                    cin >> index;
                    Tab2::Wiezienie tmp2 = lista2_tmp.get_element(index);
                    lista2_tmp.clear();
                    lista2_tmp.push_back(tmp2);
                    system("CLS");
                    cout << "Element zostal zapisany w pamieci (w liscie tymczasowej). " << endl;
                    Sleep(1000);
                }
                else
                    blad();
            }
            else
                 blad();
            break;
        case 5:
            choice = wybor();
            system("CLS");
            cout << "Wpisz element z szukanym indexem: " << endl;
            if (choice == 1) {
                cin >> obj1;
                system("CLS");
                cout << "Index: " << lista1.get_index(obj1) << endl;
                Sleep(2000);
            }
            else if (choice == 2) {
                cin >> obj2;
                system("CLS");
                cout << "Index: " << lista2.get_index(obj2) << endl;
                Sleep(2000);
            }
            else if (choice == 3) {
                cin >> obj1;
                system("CLS");
                cout << "Index: " << lista1_tmp.get_index(obj1) << endl;
                Sleep(2000);
            }
            else if (choice == 4) {
                cin >> obj2;
                system("CLS");
                cout << "Index: " << lista2_tmp.get_index(obj2) << endl;
                Sleep(2000);
            }
            else
                blad();
            break;
        case 6:
            choice = wybor();
            system("CLS");
            cout << "Jak chcesz posortowac dane?" << endl;
            cout << "1. Rosnaco" << endl;
            cout << "2. Malejaco" << endl;
            if (choice == 1) {
                cin >> choice;
                system("CLS");
                cout << "Wedlug czego chcesz posortowac? " << endl;
                cout << "1-id, 2-imie, 3-nazwisko, 4-data urodzenia, 5-plec " << endl;
                cin >> index;
                lista1.sort(choice, index);
                system("CLS");
                cout << "Lista zostala posortowana. " << endl;
                Sleep(1000);
            }
            else if (choice == 2) {
                cin >> choice;
                system("CLS");
                cout << "Wedlug czego chcesz posortowac? " << endl;
                cout << "1-id, 2-przewinienie, 3-dlugosc odsiadki, 4-cela " << endl;
                cin >> index;
                lista2.sort(choice, index);
                system("CLS");
                cout << "Lista zostala posortowana. " << endl;
                Sleep(1000);
            }
            else if (choice == 3) {
                cin >> choice;
                system("CLS");
                cout << "Wedlug czego chcesz posortowac? " << endl;
                cout << "1-id, 2-imie, 3-nazwisko, 4-data urodzenia, 5-plec " << endl;
                cin >> index;
                lista1_tmp.sort(choice, index);
                system("CLS");
                cout << "Lista zostala posortowana. " << endl;
                Sleep(1000);
            }
            else if (choice == 4) {
                cin >> choice;
                system("CLS");
                cout << "Wedlug czego chcesz posortowac? " << endl;
                cout << "1-id, 2-przewinienie, 3-dlugosc odsiadki, 4-cela " << endl;
                cin >> index;
                lista2_tmp.sort(choice, index);
                system("CLS");
                cout << "Lista zostala posortowana. " << endl;
                Sleep(1000);
            }
            else
                blad();
            break;
        case 7:
            choice = wybor();
            system("CLS");
            cout << "Ktory typ elementu chcesz zliczyc? " << endl;
            if (choice == 1) {
                cout << "1-id, 2-imie, 3-nazwisko, 4-dzien, 5-miesiac, 6-rok, 7-plec " << endl;
                cin >> choice;
                system("CLS");
                cout << "Wpisz ten element: " << endl;
                cin >> element;
                system("CLS");
                cout << element << " wystepuje w liscie " << lista1.element_count1(choice, element) << " razy. " << endl;
                Sleep(2000);
            }
            else if (choice == 2) {
                cout << "1-id, 2-przewinienie, 3-dlugosc, 4-jednostka, 5-cela " << endl;
                cin >> choice;
                system("CLS");
                cout << "Wpisz ten element: " << endl;
                cin >> element;
                system("CLS");
                cout << element << " wystepuje w liscie " << lista2.element_count2(choice, element) << " razy. " << endl;
                Sleep(2000);
            }
            else if (choice == 3) {
                cout << "1-id, 2-imie, 3-nazwisko, 4-dzien, 5-miesiac, 6-rok, 7-plec " << endl;
                cin >> choice;
                system("CLS");
                cout << "Wpisz ten element: " << endl;
                cin >> element;
                system("CLS");
                cout << element << " wystepuje w liscie " << lista1_tmp.element_count1(choice, element) << " razy. " << endl;
                Sleep(2000);
            }
            else if (choice == 4) {
                cout << "1-id, 2-przewinienie, 3-dlugosc, 4-jednostka, 5-cela " << endl;
                cin >> choice;
                system("CLS");
                cout << "Wpisz ten element: " << endl;
                cin >> element;
                system("CLS");
                cout << element << " wystepuje w liscie " << lista2_tmp.element_count2(choice, element) << " razy. " << endl;
                Sleep(2000);
            }
            else
                blad();
            break;
        case 8:
            system("CLS");
            cout << "Z ktorej listy chcesz go wyswietlic? " << endl;
            cout << "1. Tabela z danymi wieziennymi " << endl;
            cout << "2. Tabela z tymczasowymi danymi wieziennymi" << endl;
            cin >> choice;
            system("CLS");
            cout << "Podaj id elementu: " << endl;
            cin >> index;
            system("CLS");
            cout << "Element o id: " << index << endl;
            cout << "Kara wiezienia: ";
            if (choice == 1) {
                if (lista2.arrest_length(index) > 12) {
                    double tmp = lista2.arrest_length(index) / 12.0;
                    cout << setprecision(3) << tmp << " (lata) " << endl;
                }
                else
                    cout << lista2.arrest_length(index) << " (miesiace) " << endl;
                Sleep(3000);
            }
            else if (choice == 2) {
                if (lista2_tmp.arrest_length(index) > 12) {
                    double tmp = lista2_tmp.arrest_length(index) / 12.0;
                    cout << setprecision(3) << tmp << " (lata) " << endl;
                }
                else
                    cout << lista2_tmp.arrest_length(index) << " (miesiace) " << endl;
                Sleep(3000);
            }
            else
                blad();
            break;
        case 9:
            system("CLS");
            cout << "Z ktorej listy chcesz go wyswietlic? " << endl;
            cout << "1. Tabela z danymi wieziennymi " << endl;
            cout << "2. Tabela z tymczasowymi danymi wieziennymi" << endl;
            cin >> choice;
            system("CLS");
            cout << "Podaj przewinienie: (all - jezeli chcesz srednia wszyskich) " << endl;
            cin >> element;
            system("CLS");
            cout << "Przewinienie: " << element << endl;
            cout << "Srednia kara wiezienia: ";
            if (choice == 1) {
                if (lista2.arrest_average(element) > 12) {
                    double tmp = lista2.arrest_average(element) / 12.0;
                    cout << setprecision(3) << tmp << " (lata) " << endl;
                }
                else
                    cout << lista2.arrest_average(element) << " (miesiace) " << endl;
                Sleep(3000);
            }
            else if (choice == 2) {
                if (lista2_tmp.arrest_average(element) > 12) {
                    double tmp = lista2_tmp.arrest_average(element) / 12.0;
                    cout << setprecision(3) << tmp << " (lata) " << endl;
                }
                else
                    cout << lista2_tmp.arrest_average(element) << " (miesiace) " << endl;
                Sleep(3000);
            }
            else
                blad();
            break;
        case 10:
            system("CLS");
            cout << "Z ktorej listy chcesz go wyswietlic? " << endl;
            cout << "1. Tabela z danymi wieziennymi " << endl;
            cout << "2. Tabela z tymczasowymi danymi wieziennymi" << endl;
            cin >> choice;
            system("CLS");
            cout << "Podaj przewinienie: (all - jezeli chcesz srednia wszyskich) " << endl;
            cin >> element;
            cout << "oraz srednia dlugosc w miesiacach do porownania: " << endl;
            cin >> index;
            if (choice == 1) {
                lista2_tmp = lista2.avarage_greater(index, element);
                system("CLS");
                cout << "Lista z dluzszymi karami zostala zapisana w pamieci. " << endl;
                Sleep(2000);
            }
            else if (choice == 2) {
                lista2_tmp = lista2_tmp.avarage_greater(index, element);
                system("CLS");
                cout << "Lista z dluzszymi karami zostala zapisana w pamieci. " << endl;
                Sleep(2000);
            }
            else
                blad();
            break;
        case 11:
            system("CLS");
            cout << "Z ktorej listy chcesz go wyswietlic? " << endl;
            cout << "1. Tabela z danymi wieziennymi " << endl;
            cout << "2. Tabela z tymczasowymi danymi wieziennymi" << endl;
            cin >> choice;
            system("CLS");
            cout << "Podaj blok do sprawdzenia: " << endl;
            cin >> blok;
            if (choice == 1) {
                lista2_tmp = lista2.block_check(blok);
                system("CLS");
                cout << "Lista z blokami zostala zapisana w pamieci. " << endl;
                Sleep(1000);
            }
            else if (choice == 2) {
                lista2_tmp = lista2_tmp.block_check(blok);
                system("CLS");
                cout << "Lista z blokami zostala zapisana w pamieci. " << endl;
                Sleep(1000);
            }
            else
                blad();
            break;
        case 12:
            system("CLS");
            cout << "Z ktorej listy chcesz go wyswietlic? " << endl;
            cout << "1. Tabela z danymi osobowymi " << endl;
            cout << "2. Tabela z tymczasowymi danymi osobowymi" << endl;
            cin >> choice;
            system("CLS");
            if (choice == 1) {
                cout << "Podaj dolna granice daty: " << endl;
                cin >> tab[0] >> tab[1] >> tab[2];
                cout << "Teraz podaj gorna granice daty: " << endl;
                cin >> tab[3] >> tab[4] >> tab[5];
                lista1_tmp = lista1.born_during(tab[0], tab[1], tab[2], tab[3], tab[4], tab[5]);
                system("CLS");
                cout << "Lista z datami zostala zapisana w pamieci. " << endl;
                Sleep(1000);
            }
            else if (choice == 2) {
                cout << "Podaj dolna granice daty: " << endl;
                cin >> tab[0] >> tab[1] >> tab[2];
                cout << "Teraz podaj gorna granice daty: " << endl;
                cin >> tab[3] >> tab[4] >> tab[5];
                lista1_tmp = lista1_tmp.born_during(tab[0], tab[1], tab[2], tab[3], tab[4], tab[5]);
                system("CLS");
                cout << "Lista z datami zostala zapisana w pamieci. " << endl;
                Sleep(1000);
            }
            else
                blad();
            break;
        case 13:
            system("CLS");
            cout << "Jakie powiazania chcesz znalezc? " << endl;
            cout << "1. Tymczasowa lista danych wieziennych z danymi osobowymi " << endl;
            cout << "2. Tymczasowa lista danych osobowych z danymi wieziennymi " << endl;
            cin >> choice;
            if (choice == 1) {
                lista1_tmp = lista2_tmp.connections<Tab2::Wiezienie, Tab1::Dane>(lista1);
                system("CLS");
                cout << "Lista z powiazaniami zostala zapisana w pamieci. " << endl;
                Sleep(1000);
            }
            else if (choice == 2) {
                lista2_tmp = lista1_tmp.connections<Tab1::Dane, Tab2::Wiezienie>(lista2);
                system("CLS");
                cout << "Lista z powiazaniami zostala zapisana w pamieci. " << endl;
                Sleep(1000);
                }
            else
                blad();
            break;
        case 14:
            system("CLS");
            cout << "Chcesz wyswietlic wybrany element czy cala liste? " << endl;
            cout << "1. Jeden element" << endl;
            cout << "2. Cala lista" << endl;
            cin >> choice;
            if (choice == 1) {
                system("CLS");
                cout << "Podaj index elementu: " << endl;
                cin >> index;
                choice = wybor();
                system("CLS");
                if (choice == 1)
                    lista1.displayELement(index);
                else if (choice == 2)
                    lista2.displayELement(index);
                else if (choice == 3)
                    lista1_tmp.displayELement(index);
                else if (choice == 4)
                    lista2_tmp.displayELement(index);
                else
                    blad();
                Sleep(3000);
            }
            else if (choice == 2) {
                system("CLS");
                cout << "Z ktorej listy chcesz go wyswietlic? " << endl;
                cout << "1. Tabela z danymi osobowymi " << endl;
                cout << "2. Tabela z danymi wieziennymi " << endl;
                cout << "3. Tabela z tymczasowymi danymi osobowymi " << endl;
                cout << "4. Tabela z tymczasowymi danymi wieziennymi" << endl;
                cout << "5. Wszystkie " << endl;
                cin >> choice;
                system("CLS");
                if (choice == 1)
                    lista1.displayList();
                else if (choice == 2)
                    lista2.displayList();
                else if (choice == 3)
                    lista1_tmp.displayList();
                else if (choice == 4)
                    lista2_tmp.displayList();
                else if (choice == 5) {
                    cout << "1. Tabela z danymi osobowymi: " << endl;
                    lista1.displayList();
                    cout << endl << "2. Tabela z danymi wieziennymi: " << endl;
                    lista2.displayList();
                    cout << endl << "3. Tabela z tymczasowymi danymi osobowymi: " << endl;
                    lista1_tmp.displayList();
                    cout << endl << "4. Tabela z tymczasowymi danymi wieziennymi: " << endl;
                    lista2_tmp.displayList();
                    Sleep(7000);
                }
                else 
                    blad();
                Sleep(3000);
            }
            else
                blad();
            break;
        case 15:
            choice = wybor();
            if (choice == 1) {
                lista1.clear();
                system("CLS");
                cout << "Lista zostala wyczyszczona. " << endl;
                Sleep(1000);
            }
            else if (choice == 2) {
                lista2.clear();
                system("CLS");
                cout << "Lista zostala wyczyszczona. " << endl;
                Sleep(1000);
            }
            else if (choice == 3) {
                lista1_tmp.clear();
                system("CLS");
                cout << "Lista zostala wyczyszczona. " << endl;
                Sleep(1000);
            }
            else if (choice == 4) {
                lista2_tmp.clear();
                system("CLS");
                cout << "Lista zostala wyczyszczona. " << endl;
                Sleep(1000);
            }
            else
                blad();
            break;
        case 16:
            system("CLS");
            cout << "Chcesz zapisywac ciagiem (log), jest to zapis pojedynczy czy czyszczenie pliku? " << endl;
            cout << "1. Ciagiem" << endl;
            cout << "2. Pojedynczy" << endl;
            cout << "3. Czyszczenie pliku" << endl;
            cin >> choice;
            system("CLS");
            cout << "Ktora liste chcesz zapisac? " << endl;
            cout << "1. Tabela z danymi osobowymi " << endl;
            cout << "2. Tabela z danymi wieziennymi " << endl;
            cout << "3. Tabela z tymczasowymi danymi osobowymi " << endl;
            cout << "4. Tabela z tymczasowymi danymi wieziennymi" << endl;
            if (choice == 1) {
                cout << "5. Wszystkie" << endl;
                cin >> choice;
                if (choice == 1)
                    lista1.zapis2(o);
                else if (choice == 2)
                    lista2.zapis2(o);
                else if (choice == 3)
                    lista1_tmp.zapis2(o);
                else if (choice == 4)
                    lista2_tmp.zapis2(o);
                else if (choice == 5) {
                    lista1.zapis2(o);
                    lista2.zapis2(o);
                    lista1_tmp.zapis2(o);
                    lista2_tmp.zapis2(o);
                }
                system("CLS");
                cout << "Dane zostaly zapisane. " << endl;
                Sleep(1000);
            }
            else if (choice == 2) {
                cin >> choice;
                if (choice == 1)
                    lista1.zapis(o);
                else if (choice == 2)
                    lista2.zapis(o);
                else if (choice == 3)
                    lista1_tmp.zapis(o);
                else if (choice == 4)
                    lista2_tmp.zapis(o);
                else
                    blad();
                system("CLS");
                cout << "Dane zostaly zapisane. " << endl;
                Sleep(1000);
            }
            else if (choice == 3) {
                zapis_clear(o);
                system("CLS");
                cout << "Plik zostal wyczyszczony. " << endl;
                Sleep(1000);
            }
            else
                blad();
            break;
        case 0:
            quit = true;
            break;
        default:
            break;
        }
    } while (!quit);
    system("CLS");
}

void Interfejs::zapis_clear(const string& nazwa) {
    ofstream clear(nazwa);
    if (clear) {
        clear << "" << endl;
        clear.close();
    }
}



void parameters_check(int argc, char* argv[], string& i1, string& i2, string& o) {
    if (argc != 7) {
        cout << "Blad! Bledne parametry. (i1 i2 o)" << endl;
        exit(0);
    }

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-i1")
            i1 = argv[++i];
        else if (arg == "-i2")
            i2 = argv[++i];
        else if (arg == "-o")
            o = argv[++i];
        else {
            cout << "Blad! Nieznany parametr: " << arg << endl;
            exit(0);
        }
    }
    cout << "Dane z plikow zostaly wczytane. " << endl;
    Sleep(1000);
}