#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int znakmenu, zawodnik=0, losowo=0, zycie1, zycie2, krew1=0, krew2=0, dmg, licznik=0, atak, blok1=0, blok2=0, wygrana=0, przeciwnik, blad, liczblok1=0, liczblok2=0, lepszeAI=1, bloklepiej=0;
int rzad1=0, rzad2=0, rzadlicz=0, kolejka=0, spr=0, atakAI=0, rzadlicz2=0, rzad3=0, rzad4=0, spr2=0, kolejka2=0, symbolataku, koniec=0, koniec2=0;

void menu();
void wybor_zawodnika();
void losowosc();
void walka();
void krew();
void zycie();
void smierc();
void arena();
void AI();
void komunikat();

int main()
{
    srand(time(NULL));
    menu:
    przeciwnik=0;
    menu();
    if (znakmenu==1)
    {
        losowo=0;
        zawodnik=0;
        wybor_zawodnika();
        if (znakmenu==1)
            goto menu;
        blad=0;
        losowosc();
        if(blad==1)
            goto menu;
        zycie();
        krew();
        arena();
        goto menu;
    }
    else
    {
        system("CLS");
        exit(0);
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
        cout << "     ...GRAB-ARENA..." << endl;
        cout << '\t' << " 1.Graj" << endl;
        cout << '\t' << "  2.Samouczek" << endl;
        cout << '\t' << " 3.Wybor przeciwnika" << endl;
        cout << '\t' << "  4.Autorzy" << endl;
        cout << '\t' << " 5.Wyjdz" << endl;
        while(!(cin>>x))
        {
            cin.clear();
            cin.sync();
            goto poczatek;
        }
        if (x==1)
            znakmenu=1;
        else if (x==2)
        {
            prob1:
            system("CLS");
            cout << '\t' << "Sterowanie: przyciski 1 2 3 4 5 i zatwierdzenie ENTEREM!" << endl << '\t' << "Polecam grac w powiekszonym oknie i przyblizyc uzywajac Ctrl i scrolla w gore." << endl << '\t' << "W grze masz za zadanie pokonac przeciwnika obnizajac mu hp do 0. Punkty krwi sluza do wykonywania atakow. Dostajesz je co ture. 2 pierwsze ataki zadaja dmg a 3 daje ci ochrone na 1 runde." << endl;
            cout << endl << '\t' << " 1.Wroc" << endl;
            while(!(cin>>x))
            {
                cin.clear();
                cin.sync();
                goto prob1;
            }
            goto poczatek;
        }
        else if (x==3)
        {
            system("CLS");
            if (wygrana==1)
            {
            prob2:
            system("CLS");
            cout << '\t' << "Z kim chcesz walczyc?" << endl;
            cout << endl << '\t' << " 1.Pablo" << endl;
            cout << '\t' << "  2.SzimiX" << endl;
            cout << '\t' << " 3.Janka" << endl;
            cout << endl << '\t' << " 4.Losowo" << endl;
            while(!(cin>>x))
            {
                cin.clear();
                cin.sync();
                goto prob2;
            }
            przeciwnik=x;
            goto poczatek;
            }
            else
            {
                prob3:
                system("CLS");
                cout << '\t' << "Musisz wygrac 1 mecz!" << endl;
                cout << endl << '\t' << " 1.Wroc" << endl;
                while(!(cin>>x))
                {
                    cin.clear();
                    cin.sync();
                    goto prob3;
                }
                goto poczatek;
            }
        }
        else if (x==4)
        {
            autor:
            system("CLS");
            cout << '\t' << "Made by: Bartosz Helinski     v0.0.3" << endl;
            cout << endl << '\t' << " Dzial bugow: Michal Lipiec" << endl;
            cout << endl << '\t' << "  Dzial marketingu: Alexander Kocaj" << endl;
            cout << endl << endl << '\t' << "Kliknij 1 aby wrocic" << endl;
            while(!(cin>>x))
            {
                cin.clear();
                cin.sync();
                goto autor;
            }
            goto poczatek;
        }
        else if (x==5)
            znakmenu=0;
    }
}

void wybor_zawodnika()
{
    int x=0;
    znakmenu=0;
    while (x!=1&&x!=2&&x!=3)
    {
        wybor:
        system("CLS");
        cout << '\t' << "Witaj na arenie Grabow!" << endl;
        cout << '\t' << "Wybierz swojego graba:" << endl;
        cout << endl << '\t' << " 1.Pablo" << endl;
        cout << '\t' << "  2.SzimiX" << endl;
        cout << '\t' << " 3.Janka" << endl;
        cout << endl << '\t' << "  4.Wroc" << endl;
        while(!(cin>>x))
        {
            cin.clear();
            cin.sync();
            goto wybor;
        }
        if (x==1)
        {
            x=0;
            while (x!=1&&x!=2)
            {
            prob1:
            system("CLS");
            cout << '\t' << "Pablo - tank. Niezwykle potezny i wytrzymaly, lecz wolny i posiadajacy niewiele punktow krwi zawodnik..." << endl;
            cout << '\t' << "Atak podstawowy: uderzenie piescia" << endl;
            cout << '\t' << "Atak specjalny: mocny kopniak" << endl;
            cout << '\t' << "Blok: tarcza" << endl;
            cout << endl << '\t' << "Czy chcesz wybrac tego zawdonika?" << endl;
            cout << '\t' << " 1.Tak" << endl;
            cout << '\t' << "  2.Nie" << endl;
            while(!(cin>>x))
            {
                cin.clear();
                cin.sync();
                goto prob1;
            }
            if (x==1)
            {
                zawodnik=1;
            }
            else if (x==2)
            {
                goto wybor;
            }
            }

        }
        else if (x==2)
        {
            x=0;
            while (x!=1&&x!=2)
            {
            prob2:
            system("CLS");
            cout << '\t' << "SzimiX - mistrz obrazen. Mimo ze nie jest narbardziej wytrzymalym zawodnikiem, jego potezne ataki potrafia bez problemu pokierweszowac przeciwnikow..." << endl;
            cout << '\t' << "Atak podstawowy: szybkie ciosy" << endl;
            cout << '\t' << "Atak specjalny: strzal z wiatrowki" << endl;
            cout << '\t' << "Blok: unik" << endl;
            cout << endl << '\t' << "Czy chcesz wybrac tego zawdonika?" << endl;
            cout << '\t' << " 1.Tak" << endl;
            cout << '\t' << "  2.Nie" << endl;
            while(!(cin>>x))
            {
                cin.clear();
                cin.sync();
                goto prob2;
            }
            if (x==1)
            {
                zawodnik=2;
            }
            else if (x==2)
            {
                goto wybor;
            }
            }

        }
        else if (x==3)
        {
            x=0;
            while (x!=1&&x!=2)
            {
            prob3:
            system("CLS");
            cout << '\t' << "Janka - czarownica. Umie rzuczac niezwykle potezne czary i klatwy na przeciwnikow, mimo obrony wciaz moze atakowac..." << endl;
            cout << '\t' << "Atak podstawowy: zamachniecie miotla" << endl;
            cout << '\t' << "Atak specjalny: klatwa" << endl;
            cout << '\t' << "Blok: magiczna bariera" << endl;
            cout << endl << '\t' << "Czy chcesz wybrac tego zawdonika?" << endl;
            cout << '\t' << " 1.Tak" << endl;
            cout << '\t' << "  2.Nie" << endl;
            while(!(cin>>x))
            {
                cin.clear();
                cin.sync();
                goto prob3;
            }
            if (x==1)
            {
                zawodnik=3;
            }
            else if (x==2)
            {
                goto wybor;
            }
            }

        }
        else if (x==4)
        {
            znakmenu=1;
            break;
        }
    }
}

void losowosc()
{
    int x;
    system("CLS");
    if ((przeciwnik==0)||(przeciwnik==4))
    {
    if (zawodnik==1)
        losowo=rand()%2+2;
    if (zawodnik==2)
    {
        losowo=rand()%2+3;
        if (losowo==4)
            losowo=1;
    }
    if (zawodnik==3)
        losowo=rand()%2+1;
    }
    else
    {
        if (zawodnik==1&&przeciwnik==1)
        {
            prob1:
            system("CLS");
            cout << '\t' << "Musisz wybrac innego przeciwnika!" << endl;
            cout << endl << '\t' << "Kliknij 1 aby wrocic" << endl;
            blad=1;
            while(!(cin>>x))
            {
                cin.clear();
                cin.sync();
                goto  prob1;
            }
        }
        else if (zawodnik==1&&przeciwnik!=1)
            losowo=przeciwnik;
        if (zawodnik==2&&przeciwnik==2)
        {
            prob2:
            system("CLS");
            cout << '\t' << "Musisz wybrac innego przeciwnika!" << endl;
            cout << endl << '\t' << "Kliknij 1 aby wrocic" << endl;
            blad=1;
            while(!(cin>>x))
            {
                cin.clear();
                cin.sync();
                goto prob2;
            }
        }
        else if (zawodnik==2&&przeciwnik!=2)
            losowo=przeciwnik;
        if (zawodnik==3&&przeciwnik==3)
        {
            prob3:
            system("CLS");
            cout << '\t' << "Musisz wybrac innego przeciwnika!" << endl;
            cout << endl << '\t' << "Kliknij 1 aby wrocic" << endl;
            blad=1;
            while(!(cin>>x))
            {
                cin.clear();
                cin.sync();
                goto prob3;
            }
        }
        else if (zawodnik==3&&przeciwnik!=3)
            losowo=przeciwnik;
    }
}

void walka()
{
    int y, x;
    licznik=0;
    prob1:
    system("CLS");
    cout << '\t' << "Ty zaczynasz!" << endl;
    cout << endl << '\t' << "Kliknij 1 aby rozpoczac bitwe!" << endl;
    while(!(cin>>y))
    {
        cin.clear();
        cin.sync();
        goto prob1;
    }
    poczatek:
    system("CLS");
    if (x==3)
        blok1=1;
    x=0;
    licznik+=1;
    krew1+=licznik;
    krew2+=licznik;
    if (krew1<10)
        krew1+=10;
    if (krew2<10)
        krew2+=10;
    if ((zycie1<=0)||((zycie1<=0)&&(zycie2<=0)))
        smierc();
    else
    {
    srodek:
    system("CLS");
    cout << '\t' << "Tura: " << licznik << endl << endl;
    if (zawodnik==1)
        cout << endl << '\t' << "     PABLO";
    else if (zawodnik==2)
        cout << endl << '\t' << "     SZIMIX";
    else if (zawodnik==3)
        cout << endl << '\t' << "     JANKA";
    cout << "                       vs                      ";
    if (losowo==1)
        cout << "PABLO" << endl;
    else if (losowo==2)
        cout << "SZIMIX" << endl;
    else if (losowo==3)
        cout << "JANKA"  << endl;
    cout << endl << '\t' << "Twoje zycie: " << zycie1;
    cout << "                                ";
    cout << "Zycie przeciwnika: " << zycie2;
    cout << endl << endl << '\t' << "Twoje punkty krwi: " << krew1;
    cout << "                            ";
    cout << "Punkty krwi przeciwnika: " << krew2 << endl;
    if (blok1==1)
        cout << endl << '\t' << "Blok!";
    else
        cout << endl << '\t' << "     ";
    cout << "                                            ";
    if (blok2==1)
        cout << "Blok!" << endl;
    cout << endl << endl << endl << '\t' << "Twoje ataki: " << "                                    " << "Ataki przeciwnika:" << endl;;
    if (zawodnik==1)
    {
        cout << endl << '\t' << "1.Uderzenie piescia - koszt 7 pk                ";
        if (losowo==2)
            cout << " 1.Szybkie ciosy" << endl;
        else if (losowo==3)
            cout << " 1.Zamachniecie miotla" << endl;
        cout << endl << '\t' << " 2.Mocny kopniak - koszt 250 pk                  ";
        if (losowo==2)
            cout << " 2.Strzal z wiatrowki" << endl;
        else if (losowo==3)
            cout << " 2.Klatwa" << endl;
        cout << endl << '\t' << "3.Tarcza - koszt 8 pk                           ";
        if (losowo==2)
            cout << " 3.Unik" << endl;
        else if (losowo==3)
            cout << " 3.Magiczna bariera" << endl;
        cout << endl << '\t' << " 4.Odpoczynek - dodaje 3 pk                      ";
        if (losowo==2)
            cout << " 4.Odpoczynek" << endl;
        else if (losowo==3)
            cout << " 4.Odpoczynek" << endl;
        while(!(cin>>x))
        {
            cin.clear();
            cin.sync();
            goto srodek;
        }
        if (x==1)
        {
            if ((rzadlicz==2)&&(spr==x))
            {
                licz1:
                cout << endl << '\t' << "Jestes zmeczony uzywaniem ciagle tego samego ataku wiec postanawiasz wybrac inny..." << endl;
                Sleep(1000);
                goto srodek;
            }
            if ((kolejka==1)&&(spr==x))
            {
                kolejka=0;
                goto licz1;
            }
            if (krew1>=7)
            {
                if(blok2==0)
                {
                    system("CLS");
                    krew1-=7;
                    zycie2-=300;
                    cout << '\t' << "Wynik:" << endl;
                    cout << '\t' << "Uderzeniem piescia zadajesz 300 dmg!" << endl;
                    cout << endl << '\t' << "Teraz ruch wykonuje twoj przeciwnik..." << endl;
                    Sleep(2000);
                }
                else
                {
                    system("CLS");
                    krew1-=7;
                    zycie2-=100;
                    cout << '\t' << "Wynik:" << endl;
                    cout << '\t' << "Przeciwnik uzyl bloku - zadajesz tylko 100 dmg!" << endl;
                    cout << endl << '\t' << "Teraz ruch wykonuje twoj przeciwnik..." << endl;
                    Sleep(2000);
                }
            }
            else
            {
                cout << endl << '\t' << "Nie masz wystarczajacej liczby punktow krwi!" << endl;
                Sleep(1000);
                goto srodek;
            }
        }
        else if (x==2)
        {
            if ((rzadlicz==2)&&(spr==x))
            {
                licz2:
                cout << endl << '\t' << "Jestes zmeczony uzywaniem ciagle tego samego ataku wiec postanawiasz wybrac inny..." << endl;
                Sleep(1000);
                goto srodek;
            }
            if ((kolejka==1)&&(spr==x))
            {
                kolejka=0;
                goto licz2;
            }
             if (krew1>=250)
            {
                if(blok2==0)
                {
                system("CLS");
                krew1-=250;
                zycie2-=8000;
                cout << '\t' << "Wynik:" << endl;
                cout << '\t' << "Mocnym kopniakiem zadajesz az 8 000 dmg!" << endl;
                cout << endl << '\t' << "Teraz ruch wykonuje twoj przeciwnik..." << endl;
                Sleep(2000);
                }
                else
                {
                    system("CLS");
                    krew1-=250;
                    zycie2-=2000;
                    cout << '\t' << "Wynik:" << endl;
                    cout << '\t' << "Przeciwnik uzyl bloku - zadajesz tylko 2 000 dmg!" << endl;
                    cout << endl << '\t' << "Teraz ruch wykonuje twoj przeciwnik..." << endl;
                    Sleep(2000);
                }
            }
            else
            {
                cout << endl << '\t' << "Nie masz wystarczajacej liczby punktow krwi!" << endl;
                Sleep(1000);
                goto srodek;
            }
        }
        else if (x==3)
        {
            if ((rzadlicz==2&&(spr==x)))
            {
                licz3:
                cout << endl << '\t' << "Jestes zmeczony uzywaniem ciagle tego samego ataku wiec postanawiasz wybrac inny..." << endl;
                Sleep(1000);
                goto srodek;
            }
            if ((kolejka==1)&&(spr==x))
            {
                kolejka=0;
                goto licz3;
            }
            if (krew1>=8)
            {
                system("CLS");
                krew1-=8;
                cout << '\t' << "Wynik:" << endl;
                cout << '\t' << "Oslona chroni cie przed czescia zwyklego dmg w nastepnej turze!" << endl;
                cout << endl << '\t' << "Teraz ruch wykonuje twoj przeciwnik..." << endl;
                Sleep(2000);
            }
            else
            {
                cout << endl << '\t' << "Nie masz wystarczajacej liczby punktow krwi!" << endl;
                Sleep(1000);
                goto srodek;
            }
        }
        else if (x==4)
        {
            if ((rzadlicz==2)&&(krew1>=20)&&(spr==x))
            {
                licz4:
                cout << endl << '\t' << "Jestes zmeczony uzywaniem ciagle tego samego ataku wiec postanawiasz wybrac inny..." << endl;
                Sleep(1000);
                goto srodek;
            }
            if ((kolejka==1)&&(krew1>=20)&&(spr==x))
            {
                kolejka=0;
                goto licz4;
            }
            else
            {
            system("CLS");
            krew1+=3;
            cout << '\t' << "Wynik:" << endl;
            cout << '\t' << "Odpoczynek daje ci dodatkowe 3 punkty krwi!" << endl;
            cout << endl << '\t' << "Teraz ruch wykonuje twoj przeciwnik..." << endl;
            Sleep(2000);
            }
        }
        else
            goto srodek;
    }
    else if (zawodnik==2)
    {
        cout << endl << '\t' << "1.Szybkie ciosy - koszt 5 pk                    ";
        if (losowo==1)
            cout << " 1.Uderzenie piescia" << endl;
        else if (losowo==3)
            cout << " 1.Zamachniecie miotla" << endl;
        cout << endl << '\t' << " 2.Strzal z wiatrowki - koszt 100 pk             ";
        if (losowo==1)
            cout << " 2.Mocny kopniak" << endl;
        else if (losowo==3)
            cout << " 2.Klatwa" << endl;
        cout << endl << '\t' << "3.Unik - koszt 7 pk                             ";
        if (losowo==1)
            cout << " 3.Tarcza" << endl;
        else if (losowo==3)
            cout << " 3.Magiczna bariera" << endl;
        cout << endl << '\t' << " 4.Odpoczynek - dodaje 3 pk                      ";
        if (losowo==1)
            cout << " 4.Odpoczynek" << endl;
        else if (losowo==3)
            cout << " 4.Odpoczynek" << endl;
        while(!(cin>>x))
        {
            cin.clear();
            cin.sync();
            goto srodek;
        }
         if (x==1)
        {
            if ((rzadlicz==2)&&(spr==x))
            {
                licz5:
                cout << endl << '\t' << "Jestes zmeczony uzywaniem ciagle tego samego ataku wiec postanawiasz wybrac inny..." << endl;
                Sleep(1000);
                goto srodek;
            }
            if ((kolejka==1)&&(spr==x))
            {
                kolejka=0;
                goto licz5;
            }
            if (krew1>=5)
            {
                if (blok2==0)
                {
                system("CLS");
                krew1-=5;
                zycie2-=500;
                cout << '\t' << "Wynik:" << endl;
                cout << '\t' << "Szybkim uderzeniem zadajesz 500 dmg!" << endl;
                cout << endl << '\t' << "Teraz ruch wykonuje twoj przeciwnik..." << endl;
                Sleep(2000);
                }
                else
                {
                    system("CLS");
                    krew1-=5;
                    zycie2-=10;
                    cout << '\t' << "Wynik:" << endl;
                    cout << '\t' << "Przeciwnik uzyl bloku - zadajesz tylko 10 dmg!" << endl;
                    cout << endl << '\t' << "Teraz ruch wykonuje twoj przeciwnik..." << endl;
                    Sleep(2000);
                }
            }
            else
            {
                cout << endl << '\t' << "Nie masz wystarczajacej liczby punktow krwi!" << endl;
                Sleep(1000);
                goto srodek;
            }
        }
        else if (x==2)
        {
            if ((rzadlicz==2)&&(spr==x))
            {
                licz6:
                cout << endl << '\t' << "Jestes zmeczony uzywaniem ciagle tego samego ataku wiec postanawiasz wybrac inny..." << endl;
                Sleep(1000);
                goto srodek;
            }
            if ((kolejka==1)&&(spr==x))
            {
                kolejka=0;
                goto licz6;
            }
             if (krew1>=100)
            {
                if (blok2==0)
                {
                system("CLS");
                krew1-=100;
                zycie2-=2000;
                cout << '\t' << "Wynik:" << endl;
                cout << '\t' << "Strzalem z wiatrowki zadajesz 2 000 dmg od broni palnej!" << endl;
                cout << endl << '\t' << "Teraz ruch wykonuje twoj przeciwnik..." << endl;
                Sleep(2000);
                }
                else
                {
                    system("CLS");
                    krew1-=100;
                    zycie2-=1500;
                    cout << '\t' << "Wynik:" << endl;
                    cout << '\t' << "Przeciwnik uzyl bloku - zadajesz 1 500 dmg od broni palnej!" << endl;
                    cout << endl << '\t' << "Teraz ruch wykonuje twoj przeciwnik..." << endl;
                    Sleep(2000);
                }
            }
            else
            {
                cout << endl << '\t' << "Nie masz wystarczajacej liczby punktow krwi!" << endl;
                Sleep(1000);
                goto srodek;
            }
        }
        else if (x==3)
        {
            if ((rzadlicz==2)&&(spr==x))
            {
                licz7:
                cout << endl << '\t' << "Jestes zmeczony uzywaniem ciagle tego samego ataku wiec postanawiasz wybrac inny..." << endl;
                Sleep(1000);
                goto srodek;
            }
            if ((kolejka==1)&&(spr==x))
            {
                kolejka=0;
                goto licz7;
            }
            if (krew1>=7)
            {
                system("CLS");
                krew1-=7;
                cout << '\t' << "Wynik:" << endl;
                cout << '\t' << "Unik chroni cie przed czescia zwyklego dmg w nastepnej turze!" << endl;
                cout << endl << '\t' << "Teraz ruch wykonuje twoj przeciwnik..." << endl;
                Sleep(2000);
            }
            else
            {
                cout << endl << '\t' << "Nie masz wystarczajacej liczby punktow krwi!" << endl;
                Sleep(1000);
                goto srodek;
            }
        }
        else if (x==4)
        {
            if ((rzadlicz==2)&&(krew1>=20)&&(spr==x))
            {
                licz8:
                cout << endl << '\t' << "Jestes zmeczony uzywaniem ciagle tego samego ataku wiec postanawiasz wybrac inny..." << endl;
                Sleep(1000);
                goto srodek;
            }
            if ((kolejka==1)&&(krew1>=20)&&(spr==x))
            {
                kolejka=0;
                goto licz8;
            }
            else
            {
            system("CLS");
            krew1+=3;
            cout << '\t' << "Wynik:" << endl;
            cout << '\t' << "Odpoczynek daje ci dodatkowe 3 punkty krwi!" << endl;
            cout << endl << '\t' << "Teraz ruch wykonuje twoj przeciwnik..." << endl;
            Sleep(2000);
            }
        }
        else
            goto srodek;
    }
    else if (zawodnik==3)
    {
        cout << endl << '\t' << "1.Zamachniecie miotla - koszt 7 pk              ";
        if (losowo==1)
            cout << " 1.Uderzenie piescia" << endl;
        else if (losowo==2)
            cout << " 1.Szybkie ciosy" << endl;
        cout << endl << '\t' << " 2.Klatwa - koszt 150 pk                         ";
        if (losowo==1)
            cout << " 2.Mocny kopniak" << endl;
        else if (losowo==2)
            cout << " 2.Strzal z wiatrowki" << endl;
        cout << endl << '\t' << "3.Magiczna bariera - koszt 10 pk                ";
        if (losowo==1)
            cout << " 3.Tarcza" << endl;
        else if (losowo==2)
            cout << " 3.Unik" << endl;
        cout << endl << '\t' << " 4.Odpoczynek - dodaje 3 pk                      ";
        if (losowo==1)
            cout << " 4.Odpoczynek" << endl;
        else if (losowo==2)
            cout << " 4.Odpoczynek" << endl;
        while(!(cin>>x))
        {
            cin.clear();
            cin.sync();
            goto srodek;
        }
        if (x==1)
        {
            if ((rzadlicz==2)&&(spr==x))
            {
                licz9:
                cout << endl << '\t' << "Jestes zmeczony uzywaniem ciagle tego samego ataku wiec postanawiasz wybrac inny..." << endl;
                Sleep(1000);
                goto srodek;
            }
            if ((kolejka==1)&&(spr==x))
            {
                kolejka=0;
                goto licz9;
            }
            if (krew1>=7)
            {
                if (blok2==0)
                {
                system("CLS");
                krew1-=7;
                zycie2-=350;
                cout << '\t' << "Wynik:" << endl;
                cout << '\t' << "Uderzeniem miotla zadajesz 350 dmg!" << endl;
                cout << endl << '\t' << "Teraz ruch wykonuje twoj przeciwnik..." << endl;
                Sleep(2000);
                }
                else
                {
                    system("CLS");
                    krew1-=7;
                    zycie2-=10;
                    cout << '\t' << "Wynik:" << endl;
                    cout << '\t' << "Przeciwnik uzyl bloku - zadajesz tylko 10 dmg!" << endl;
                    cout << endl << '\t' << "Teraz ruch wykonuje twoj przeciwnik..." << endl;
                    Sleep(2000);
                }
            }
            else
            {
                cout << endl << '\t' << "Nie masz wystarczajacej liczby punktow krwi!" << endl;
                Sleep(1000);
                goto srodek;
            }
        }
        else if (x==2)
        {
            if ((rzadlicz==2)&&(spr==x))
            {
                licz10:
                cout << endl << '\t' << "Jestes zmeczony uzywaniem ciagle tego samego ataku wiec postanawiasz wybrac inny..." << endl;
                Sleep(1000);
                goto srodek;
            }
            if ((kolejka==1)&&(spr==x))
            {
                kolejka=0;
                goto licz10;
            }
             if (krew1>=150)
            {
                if (blok2==0)
                {
                system("CLS");
                krew1-=150;
                zycie2-=1000;
                zycie1+=1000;
                cout << '\t' << "Wynik:" << endl;
                cout << '\t' << "Klatwa zadajesz 1 000 dmg i leczysz sobie 1 000 hp!" << endl;
                cout << endl << '\t' << "Teraz ruch wykonuje twoj przeciwnik..." << endl;
                Sleep(2000);
                }
                else
                {
                    system("CLS");
                    krew1-=150;
                    zycie2-=500;
                    zycie1+=1000;
                    cout << '\t' << "Wynik:" << endl;
                    cout << '\t' << "Przeciwnik uzyl bloku - zadajesz 500 dmg magicznego i leczysz sobie 1 000 hp!" << endl;
                    cout << endl << '\t' << "Teraz ruch wykonuje twoj przeciwnik..." << endl;
                    Sleep(2000);
                }
            }
            else
            {
                cout << endl << '\t' << "Nie masz wystarczajacej liczby punktow krwi!" << endl;
                Sleep(1000);
                goto srodek;
            }
        }
        else if (x==3)
        {
            if ((rzadlicz==2)&&(spr==x))
            {
                licz11:
                cout << endl << '\t' << "Jestes zmeczony uzywaniem ciagle tego samego ataku wiec postanawiasz wybrac inny..." << endl;
                Sleep(1000);
                goto srodek;
            }
            if ((kolejka==1)&&(spr==x))
            {
                kolejka=0;
                goto licz11;
            }
            if (krew1>=10)
            {
                system("CLS");
                krew1-=10;
                zycie2-=100;
                cout << '\t' << "Wynik:" << endl;
                cout << '\t' << "Magiczna tarcza chroni cie przed czescia zwyklego dmg w nastepnej turze oraz zadajesz 100 dmg magicznego!" << endl;
                cout << endl << '\t' << "Teraz ruch wykonuje twoj przeciwnik..." << endl;
                Sleep(2000);
            }
            else
            {
                cout << endl << '\t' << "Nie masz wystarczajacej liczby punktow krwi!" << endl;
                Sleep(1000);
                goto srodek;
            }
        }
        else if (x==4)
        {
            if ((rzadlicz==2)&&(krew1>=30)&&(spr==x))
            {
                licz12:
                cout << endl << '\t' << "Jestes zmeczony uzywaniem ciagle tego samego ataku wiec postanawiasz wybrac inny..." << endl;
                Sleep(1000);
                goto srodek;
            }
            if ((kolejka==1)&&(krew1>=20)&&(spr==x))
            {
                kolejka=0;
                goto licz12;
            }
            else
            {
            system("CLS");
            krew1+=3;
            cout << '\t' << "Wynik:" << endl;
            cout << '\t' << "Odpoczynek daje ci dodatkowe 3 punkty krwi!" << endl;
            cout << endl << '\t' << "Teraz ruch wykonuje twoj przeciwnik..." << endl;
            Sleep(2000);
            }
        }
        else
            goto srodek;
    }
    if ((zycie2<=0)||((zycie1<=0)&&(zycie2<=0)))
        smierc();
    else
    {
        blok2=0;
        if ((lepszeAI==1)&&(blok1==1))
            bloklepiej=1;
        if ((lepszeAI==1)&&(x==4))
            atakAI=1;
        AI();
        komunikat();
        blok1=0;
        bloklepiej=0;
        atakAI=0;
    if (rzadlicz==0)
    {
        rzad1=x;
        goto licz;
    }
    else
        rzad1=x;
    if (rzad2==rzad1)
    {
        licz:
        rzad2=rzad1;
        rzadlicz+=1;
        if (rzadlicz==2)
        {
            kolejka=1;
            spr=rzad2;
        }
    }
    else
        rzadlicz=0;
        goto poczatek;
    }
    }
}

void zycie()
{
    if (zawodnik==1)
        zycie1=9000;
    else if (zawodnik==2)
        zycie1=6000;
    else if (zawodnik==3)
        zycie1=7500;
    if (losowo==1)
        zycie2=9000;
    else if (losowo==2)
        zycie2=6000;
    else if (losowo==3)
        zycie2=7500;
}

void krew()
{
    if (zawodnik==1)
        krew1=35;
    else if (zawodnik==2)
        krew1=50;
    else if (zawodnik==3)
        krew1=75;
    if (losowo==1)
        krew2=35;
    else if (losowo==2)
        krew2=50;
    else if (losowo==3)
        krew2=75;
}

void komunikat()
{
    int x;
    cout << endl << endl << endl << '\t' << "Wynik: " << endl;
    if (losowo==1)
    {
        if ((atak==1)||(atak==4))
        {
            if (blok1==0)
            {
            cout << '\t' << "Przeciwnik zadaje ci 300 dmg!" << endl;
            cout << endl << '\t' << "Poczekaj na zakonczenie tury..." << endl;
            Sleep(2000);
            }
            else
            {
                cout << '\t' << "Twoj blok absorbuje czesc obrazen. Dostajesz tylko 100 dmg!" << endl;
                cout << endl << '\t' << "Poczekaj na zakonczenie tury..." << endl;
                Sleep(2000);
            }
        }
        if ((atak==2)||(atak==5)||(atak==6))
        {
            if (blok1==0)
            {
            cout << '\t' << "Przeciwnik zadaje ci 8 000 dmg!" << endl;
            cout << endl << '\t' << "Poczekaj na zakonczenie tury..." << endl;
            Sleep(2000);
            }
            else
            {
                cout << '\t' << "Twoj blok absorbuje czesc obrazen. Dostajesz tylko 2 000 dmg!" << endl;
                cout << endl << '\t' << "Poczekaj na zakonczenie tury..." << endl;
                Sleep(2000);
            }
        }
        if (atak==3)
        {
            cout << '\t' << "Przeciwnik uzywa oslony. Zdobywa odpornosc na czesc normalnych obrazenia w nastepnej turze!" << endl;
            cout << endl << '\t' << "Poczekaj na zakonczenie tury..." << endl;
            Sleep(2000);
        }
        if (atak==7)
        {
            cout << '\t' << "Przeciwnik uzywa odpoczynku. Zdobywa 3 punkty krwi w nastepnej turze!" << endl;
            cout << endl << '\t' << "Poczekaj na zakonczenie tury..." << endl;
            Sleep(2000);
        }
    }
    else if (losowo==2)
    {
        if ((atak==1)||(atak==4))
        {
            if (blok1==0)
            {
            cout << '\t' << "Przeciwnik zadaje ci 500 dmg!" << endl;
            cout << endl << '\t' << "Poczekaj na zakonczenie tury..." << endl;
            Sleep(2000);
            }
            else
            {
                cout << '\t' << "Twoj blok absorbuje czesc obrazen. Dostajesz tylko 10 dmg!" << endl;
                cout << endl << '\t' << "Poczekaj na zakonczenie tury..." << endl;
                Sleep(2000);
            }
        }
        if ((atak==2)||(atak==5)||(atak==6))
        {
            if (blok1==0)
            {
            cout << '\t' << "Przeciwnik zadaje ci 2 000 dmg od broni palnej!" << endl;
            cout << endl << '\t' << "Poczekaj na zakonczenie tury..." << endl;
            Sleep(2000);
            }
            else
            {
                cout << '\t' << "Twoj blok absorbuje czesc obrazen. Dostajesz tylko 1 500 dmg od broni palnej!" << endl;
                cout << endl << '\t' << "Poczekaj na zakonczenie tury..." << endl;
                Sleep(2000);
            }
        }
        if (atak==3)
        {
            cout << '\t' << "Przeciwnik uzywa uniku. Zdobywa odpornosc na czesc normalnych obrazen w nastepnej turze!" << endl;
            cout << endl << '\t' << "Poczekaj na zakonczenie tury..." << endl;
            Sleep(2000);
        }
        if (atak==7)
        {
            cout << '\t' << "Przeciwnik uzywa odpoczynku. Zdobywa 3 punkty krwi w nastepnej turze!" << endl;
            cout << endl << '\t' << "Poczekaj na zakonczenie tury..." << endl;
            Sleep(2000);
        }
    }
    else if (losowo==3)
    {
        if ((atak==1)||(atak==4))
        {
            if (blok1==0)
            {
            cout << '\t' << "Przeciwnik zadaje ci 350 dmg!" << endl;
            cout << endl << '\t' << "Poczekaj na zakonczenie tury..." << endl;
            Sleep(2000);
            }
            else
            {
                cout << '\t' << "Twoj blok absorbuje czesc obrazen. Dostajesz 10 dmg!" << endl;
                cout << endl << '\t' << "Poczekaj na zakonczenie tury..." << endl;
                Sleep(2000);
            }
        }
        if ((atak==2)||(atak==5)||(atak==6))
        {
            if (blok1==0)
            {
            cout << '\t' << "Przeciwnik zadaje ci 1 000 dmg i leczy sobie 1 000 hp!" << endl;
            cout << endl << '\t' << "Poczekaj na zakonczenie tury..." << endl;
            Sleep(2000);
            }
            else
            {
                cout << '\t' << "Twoj blok absorbuje czesc obrazen. Dostajesz 500 dmg od czarow a przeciwnik leczy sobie 1 000 hp!" << endl;
                cout << endl << '\t' << "Poczekaj na zakonczenie tury..." << endl;
                Sleep(2000);
            }
        }
        if (atak==3)
        {
            cout << '\t' << "Przeciwnik uzywa magicznej tarczy i zadaje ci 100 dmg magicznego. Zdobywa odpornosc na czesc normalnych obrazen w nastepnej turze!" << endl;
            cout << endl << '\t' << "Poczekaj na zakonczenie tury..." << endl;
            Sleep(2000);
        }
        if (atak==7)
        {
            cout << '\t' << "Przeciwnik uzywa odpoczynku. Zdobywa 3 punkty krwi w nastepnej turze!" << endl;
            cout << endl << '\t' << "Poczekaj na zakonczenie tury..." << endl;
            Sleep(2000);
        }
    }
}
void AI()
{
    if (losowo==1)
    {
        los1:
        atak=rand()%7+1;
        if (bloklepiej==1)
        {
            if ((atak==4)||(atak==2)||(atak==5)||(atak==6))
                goto los1;
        }
        else if (bloklepiej==0)
        {
            if (krew2>=250)
                atak=2;
        }
        if (zawodnik==1)
        {
            if (krew1>=240)
            {
            koniec+=1;
            if(koniec<2)
            atak=3;
            }
        }
        else if (zawodnik==2)
        {
            if (krew1>=90)
            {
            koniec+=1;
            if(koniec<2)
            atak=3;
            }
        }
        else if (zawodnik==3)
        {
            if (krew1>=140)
            {
            koniec+=1;
            if(koniec<2)
            atak=3;
            }
        }
        else
            koniec=0;
        if ((atakAI==1)&&(bloklepiej==0))
        {
            koniec2+=1;
            if ((atak==3)||(atak==4)&&(koniec2<2))
                goto los1;
        }
        else
            koniec2=0;
        if ((atak==1)||(atak==4))
        {
        if ((rzadlicz2==2)&&(spr2==symbolataku))
            {
                licz1:
                goto los1;
            }
        if ((kolejka2==1)&&(spr2==symbolataku))
            {
                kolejka2=0;
                goto licz1;
            }
            if (krew2>=7)
            {
                if (blok1==0)
                {
                    krew2-=7;
                    zycie1-=300;
                }
                else
                {
                    krew2-=7;
                    zycie1-=100;
                }
            }
            else
                goto los1;
        }
        else if ((atak==2)||(atak==5)||(atak==6))
        {
        if ((rzadlicz2==2)&&(spr2==symbolataku))
            {
                licz2:
                goto los1;
            }
        if ((kolejka2==1)&&(spr2==symbolataku))
            {
                kolejka2=0;
                goto licz2;
            }
            if (krew2>=250)
            {
                if (blok1==0)
                {
                krew2-=250;
                zycie1-=8000;
                }
                else
                {
                    krew2-=250;
                    zycie1-=2000;
                }
            }
            else
                goto los1;
        }
        else if (atak==3)
        {
        if ((rzadlicz2==2)&&(spr2==symbolataku))
            {
                licz3:
                goto los1;
            }
        if ((kolejka2==1)&&(spr2==symbolataku))
            {
                kolejka2=0;
                goto licz3;
            }
            if (krew2>=8)
            {
                krew2-=8;
                blok2=1;
            }
            else
                goto los1;
        }
        else if (atak==7)
        {
            krew2+=3;
        }
    }
    else if (losowo==2)
    {
        los2:
        atak=rand()%7+1;
        if (bloklepiej==1)
        {
            if ((atak==4)||(atak==2)||(atak==5)||(atak==6))
                goto los2;
        }
        else if (bloklepiej==0)
        {
            if (krew2>=100)
                atak=2;
        }
        if (zawodnik==1)
        {
            if (krew1>=240)
            {
            koniec+=1;
            if(koniec<2)
            atak=3;
            }
        }
        else if (zawodnik==2)
        {
            if (krew1>=90)
            {
            koniec+=1;
            if(koniec<2)
            atak=3;
            }
        }
        else if (zawodnik==3)
        {
            if (krew1>=140)
            {
            koniec+=1;
            if(koniec<2)
            atak=3;
            }
        }
        else
            koniec=0;
        if ((atakAI==1)&&(bloklepiej==0))
        {
            koniec2+=1;
            if ((atak==3)||(atak==4)&&(koniec2<2))
                goto los2;
        }
        else
            koniec2=0;
        if ((atak==1)||(atak==4))
        {
        if ((rzadlicz2==2)&&(spr2==symbolataku))
            {
                licz4:
                goto los2;
            }
        if ((kolejka2==1)&&(spr2==symbolataku))
            {
                kolejka2=0;
                goto licz4;
            }
            if (krew2>=5)
            {
                if (blok1==0)
                {
                krew2-=5;
                zycie1-=500;
                }
                else
                {
                    krew2-=5;
                    zycie1-=10;
                }
            }
            else
                goto los2;
        }
        else if ((atak==2)||(atak==5)||(atak==6))
        {
        if ((rzadlicz2==2)&&(spr2==symbolataku))
            {
                licz5:
                goto los2;
            }
        if ((kolejka2==1)&&(spr2==symbolataku))
            {
                kolejka2=0;
                goto licz5;
            }
            if (krew2>=100)
            {
                if (blok1==0)
                {
                krew2-=100;
                zycie1-=2000;
                }
                else
                {
                    krew2-=100;
                    zycie1-=1500;
                }
            }
            else
                goto los2;
        }
        else if (atak==3)
        {
        if ((rzadlicz2==2)&&(spr2==symbolataku))
            {
                licz6:
                goto los2;
            }
        if ((kolejka2==1)&&(spr2==symbolataku))
            {
                kolejka2=0;
                goto licz6;
            }
            if (krew2>=7)
            {
                krew2-=7;
                blok2=1;
            }
            else
                goto los2;
        }
        else if (atak==7)
        {
            krew2+=3;
        }
    }
    else if (losowo==3)
    {
        los3:
        atak=rand()%7+1;
        if (bloklepiej==1)
        {
            if ((atak==1)||(atak==2)||(atak==5)||(atak==6))
                goto los3;
        }
        else if (bloklepiej==0)
        {
            if (krew2>=150)
                atak=2;
        }
        if (zawodnik==1)
        {
            if (krew1>=240)
            {
            koniec+=1;
            if(koniec<2)
            atak=3;
            }
        }
        else if (zawodnik==2)
        {
            if (krew1>=90)
            {
            koniec+=1;
            if(koniec<2)
            atak=3;
            }
        }
        else if (zawodnik==3)
        {
            if (krew1>=140)
            {
            koniec+=1;
            if(koniec<2)
            atak=3;
            }
        }
        else
            koniec=0;
        if ((atakAI==1)&&(bloklepiej==0))
        {
            koniec2+=1;
            if ((atak==3)||(atak==4)&&(koniec2<2))
                goto los3;
        }
        else
            koniec2=0;
        if ((atak==1)||(atak==4))
        {
        if ((rzadlicz2==2)&&(spr2==symbolataku))
            {
                licz7:
                goto los3;
            }
        if ((kolejka2==1)&&(spr2==symbolataku))
            {
                kolejka2=0;
                goto licz7;
            }
            if (krew2>=7)
            {
                if (blok1==0)
                {
                krew2-=7;
                zycie1-=350;
                }
                else
                {
                    krew2-=7;
                    zycie1-=10;
                }
            }
            else
                goto los3;
        }
        else if ((atak==2)||(atak==5)||(atak==6))
        {
        if ((rzadlicz2==2)&&(spr2==symbolataku))
            {
                licz8:
                goto los3;
            }
        if ((kolejka2==1)&&(spr2==symbolataku))
            {
                kolejka2=0;
                goto licz8;
            }
            if (krew2>=150)
            {
                if (blok1==0)
                {
                krew2-=150;
                zycie1-=1000;
                zycie2+=1000;
                }
                else
                {
                    krew2-=150;
                    zycie1-=500;
                    zycie2+=1000;
                }
            }
            else
                goto los3;
        }
        else if (atak==3)
        {
        if ((rzadlicz2==2)&&(spr2==symbolataku))
            {
                licz9:
                goto los3;
            }
        if ((kolejka2==1)&&(spr2==symbolataku))
            {
                kolejka2=0;
                goto licz9;
            }
            if (krew2>=10)
            {
                krew2-=10;
                zycie1-=100;
                blok2=1;
            }
            else
                goto los3;
        }
        else if (atak==7)
        {
            krew2+=3;
        }
    }
    if ((atak==1)||(atak==4))
        symbolataku=1;
    if ((atak==2)||(atak==5)||(atak==6))
        symbolataku=2;
    if (atak==3)
        symbolataku=3;
    if (rzadlicz2==0)
    {
        rzad3=symbolataku;
        goto licz;
    }
    else
        rzad3=symbolataku;
    if (rzad4==rzad3)
    {
        licz:
        rzad4=rzad3;
        rzadlicz2+=1;
        if (rzadlicz2==2)
        {
            kolejka2=1;
            spr2=rzad4;
        }
    }
    else
        rzadlicz2=0;
}

void smierc()
{
    system("CLS");
    if (zycie1<=0)
    {
        cout << endl << '\t' << "Przegrales! Przeciwnik okazal sie silnijeszy. Moze nastepnym razem bedziesz miec wiecej szczescia..." << endl;
        cout << endl << '\t' << "Wracanie do menu..." << endl;
        Sleep(5000);
    }
    if (zycie2<=0)
    {
        cout << endl << '\t' << "Wygrales! Mozesz byc z siebie dumny pokonales przeciwnika zachowujac przy tym wszystkie palce. Brawo..." << endl;
        cout << endl << '\t' << "Wracanie do menu..." << endl;
        Sleep(5000);
        wygrana=1;
    }
    if ((zycie1<=0)&&(zycie2<=0))
    {
        cout << endl << '\t' << "Remis! Tym razem przeciwnik okazal sie rowny tobie wiec razem mimo powybijanych zebow odchodzicie w strone slonca..." << endl;
        cout << endl << '\t' << "Wracanie do menu..." << endl;
        Sleep(5000);
    }
}

void arena()
{
    int x;
    prob1:
    system("CLS");
    cout << '\t' << "Czas rozpoczac bitwe!" << endl;
    cout << '\t' << "Tym razem zmierzysz sie z ";
    if (losowo==1)
        cout << "Pablem!" << endl;
    else if (losowo==2)
        cout << "SzimiXem!" << endl;
    else if (losowo==3)
        cout << "Janka!"  << endl;
    cout << endl << '\t' << "Kliknij 1 aby rozpoczac bitwe lub 0 aby wrocic do menu"  << endl;
    while(!(cin>>x))
    {
        cin.clear();
        cin.sync();
        goto prob1;
    }
    if (x!=0)
    {
    walka();
    }
}
