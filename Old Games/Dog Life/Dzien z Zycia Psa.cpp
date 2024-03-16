#include <iostream>
#include <cstdlib>
#include <windows.h>

using namespace std;

int znakmenu, pies, licznik=0, wyjscie=0, ukonczenie=0;
string imie;

void menu();
void gra();
void wybor_psa();

int main()
{
    poczatek:
    menu();
    cout << ukonczenie << endl << pies << endl << imie << endl;
    if (znakmenu==1)
    {
        system("CLS");
        wybor_psa();
        gra();
        if (wyjscie=1)
            goto poczatek;
    }
    else
    {
        system("CLS");
        return 0;
    }
    return 0;
}

void menu()
{
    int x=0;
    while (x!=1&&x!=2&&x!=3&&x!=4&&x!=5)
    {
        poczatek:
        system("CLS");
        cout << " ...Dzien z Zycia Psa..." << endl;
        cout << '\t' << " 1.Graj" << endl;
        cout << '\t' << "  2.Samouczek" << endl;
        cout << '\t' << " 3.Wyjdz" << endl;
        if (ukonczenie==1&&pies==3&&imie=="Piri")
        {
            cout << "Ha wiedzialem ze wezmiesz Piri i buldog francuski i pewnie tez wzielas watrobke XD. Kocham cie!" << endl;
        }
        cin >> x;
        if (x==1)
        {
            znakmenu=1;
            imie=" ";
            pies=0;
            licznik=0;
        }
        else if (x==2)
        {
            system("CLS");
            cout << '\t' << "Sterowanie: przyciski 1 2 3 4 i zatwierdzenie enterem!" << endl << '\t' << "Polecam grac na powiekszonym oknie i przyblizyc uzywajac Ctrl i scrolla" << endl;
            cout << endl << '\t' << " 1.Wroc" << endl;
            cin >> x;
            goto poczatek;
        }
        else if (x==3)
        {
            znakmenu=0;
        }
    }
}

void wybor_psa()
{
    int x;
    while (x!=1&&x!=2&&x!=3)
    {
        system("CLS");
        cout << '\t' << "Wybierz swoja rase:" << endl;
        cout << endl << '\t' << " 1.Chihuahua" << endl;
        cout << '\t' << "  2.Jamnik" << endl;
        cout << '\t' << " 3.Buldog francuski" << endl;
        cin >> x;
    }
    if (x==1)
        pies=1;
    else if (x==2)
        pies=2;
    else if (x==3)
        pies=3;
}

void gra()
{
    int x;
    imie:
    licznik+=1;
    system("CLS");
    cout << '\t' << "Jak codziennie budzisz sie przy boku swojej pani. Jako ze jestes";
    if (pies==1)
        cout << " chihuahua..." << endl;
    if (pies==2)
        cout << " jamnikiem..." << endl;
    if (pies==3)
        cout << " buldogiem francuskim..." << endl;
    cout << '\t' << "Nadala ci imie " << imie << "." << endl;
    if (licznik==1)
    {
        cout << endl << '\t' << "Wprowadz imie psa:" << endl;
        cin >> imie;
        goto imie;
    }
    cout << endl << '\t' << " Nacisnij 1 aby kontynuowac" << endl;
    cin >> x;
    x=0;
    while (x!=1&&x!=2)
    {
    system("CLS");
    cout << '\t' << "Nagle czujesz cos w srodku brzuszka. Chce ci sie siku. Musisz obudzic pania!" << endl;
    cout << endl << '\t' << " 1.Szczekaj glosno" << endl;
    cout << '\t' << "  2.Wskocz na nia" << endl;
    cin >> x;
    if (x==1)
    {
        szczek:
        system("CLS");
        cout << '\t' << "Swoim szczekaniem obudziles juz pewnie pol osiedla lecz twoja pani dalej spi..." << endl;
        cout << endl << '\t' << " 1.Sprobuj zalizac ja na smierc" << endl;
        cin >> x;
        if (x==1)
            goto lizanie;
        else
            goto szczek;
    }
    else if (x==2)
    {
        tramp:
        system("CLS");
        cout << '\t' << "Skaczesz po niej jak po trampolinie ale nic to nie daje. Musisz wymyslic cos innego..." << endl;
        cout << endl << '\t' << " 1.Sprobuj zalizac ja na smierc" << endl;
        cin >> x;
        if (x==1)
            goto lizanie;
        else
            goto tramp;
    }
    }
    lizanie:
    system("CLS");
    cout << '\t' << "Soczysty liz po twarzy podzialal i od razu postawil twoja pania na nogi!" << endl;
    cout << endl << '\t' << " Nacisnij 1 aby kontynuowac" << endl;
    cin >> x;
    x=0;
    while (x!=1&&x!=2)
    {
    system("CLS");
    cout << '\t' << "Po powrocie ze spacerku poczules ze jestes glodny wiec poszedles do swojej jeszcze nieprzytomnej i nieogarnietej pani" << endl;
    cout << '\t' << "Na co masz ochote?" << endl;
    cout << endl << '\t' << " 1.Drogie smaczki" << endl;
    cout << '\t' << "  2.Szyneczka i kielbaska" << endl;
    cout << '\t' << " 3.Watrobka" << endl;
    cin >> x;
    if (x==1)
    {
        system("CLS");
        cout << '\t' << "Troche luksusu od czasu do czasu nie zaszkodzi" << endl;
        cout << endl << '\t' << " Nacisnij 1 aby kontynuowac" << endl;
        cin >> x;
    }
    else if (x==2)
    {
        system("CLS");
        cout << '\t' << "Czy moze byc cos lepszego niz kielbaska o poranku?" << endl;
        cout << endl << '\t' << " Nacisnij 1 aby kontynuowac" << endl;
        cin >> x;
    }
    else if (x==3)
    {
        if (pies==3)
        {
            system("CLS");
            cout << '\t' << "Buldogi francuskie kochaja watrobke... Przynajmniej niekotre ;)" << endl;
            cout << endl << '\t' << " Nacisnij 1 aby kontynuowac" << endl;
            cin >> x;
        }
        else
        {
            system("CLS");
            cout << "Zdrowa i przepyszna! Mniam, mniam.." << endl;
            cout << endl << '\t' << " Nacisnij 1 aby kontynuowac" << endl;
            cin >> x;
        }
    }
    }
    system("CLS");
    cout << '\t' << "Najedzony i wysiusiany peszedles spac..." << endl;
    cout << endl << '\t' << " Nacisnij 1 aby kontynuowac" << endl;
    cin >> x;
    x=0;
    while (x!=1)
    {
    system("CLS");
    cout << '\t' << "Przez wiekszosc dnia spales, jadles albo meczyles pania na spacerku." << endl;
    cout << '\t' << "Gdy wrociles z ostatniego wyjscia bylo juz pozno. Pani powoli szykowala sie do spania." << endl;
    cout << '\t' << "Polozyles sie na lozeczko tak jak to robia prawdziwe pieski i wtulony w pania zasnales." << endl;
    cout << '\t' << "Wiedziales ze to byl dobry dzien..." << endl;
    cout << endl << '\t' << " 1.Zasnij..." << endl;
    cin >> x;
    x=3;
        while (x!=1&&x!=0)
        {
            system("CLS");
            cout << '\t' << "Chcesz zagrac jeszcze raz(1) czy wyjsc z gry(0)?" << endl;
            cin >> x;
            if (x==1)
            {
                ukonczenie=1;
                wyjscie=1;
            }
            else if (x==0)
            {
                system("CLS");
                exit(0);
            }
        }
    }
}
