#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int n=10, m=10;

int wyjscie=0, znakmenu, znakwyboru, ukonczenie=0, kluczedom=0, bandaz=0 , siekiera=0, jedzenie=0, woda=0, drewno=0, przeszukanie=0, latarka=0, odpoczynek=0, zdrowie, zdrow, godzina1, godzina2;
int godz1, godz2, kluczeauto=0;
string tab[n][m];


void menu();
void wyborgry();
void rozdzial1();
void rozdzial2();
void rozdzial3();
void mapa();

int main()
{
    srand(time(NULL));
    int x;
    menu:
    menu();
    if (znakmenu==0)
    {
        system("CLS");
        return 0;
    }
    else
    {
        jeszczeraz:
        system("CLS");
        wyborgry();
        if (znakwyboru==2)
        {
            system("CLS");
            if (ukonczenie==0)
            {
                cout << '\t' << "Nie masz jeszcze zadnych saveow!" << endl;
                cout << endl << '\t' << "Nacisnij 1 aby kontynuowac" << endl;
                cin >> x;
                if (x==9)
                    goto cheat1;
                else
                    goto jeszczeraz;
            }
            else if (ukonczenie==1)
            {
                save1:
                system("CLS");
                cout << '\t' << "Wybierz rozdzial:" << endl;
                cout << '\t' << " 1.Rozdzial 1" << endl << '\t' << "  2.Rozdzial 2" << endl << '\t' << " 3.Cofnij" << endl;
                cin >> x;
                if (x==1)
                    goto rozdzial1;
                else if (x==2)
                    rozdzial2();
                else if (x==3)
                    goto menu;
                else
                    goto save1;
            }
            else if (ukonczenie==2)
            {
                cheat1:
                system("CLS");
                cout << '\t' << "Wybierz rozdzial:" << endl;
                cout << '\t' << " 1.Rozdzial 1" << endl << '\t' << "  2.Rozdzial 2" << endl << '\t' << " 3.Rozdzial 3" << endl << '\t' << "  4.Cofnij" << endl;
                cin >> x;
                if (x==1)
                    goto rozdzial1;
                else if (x==2)
                    rozdzial2();
                else if (x==3)
                    rozdzial3();
                else if (x==4)
                    goto menu;
                else
                    goto cheat1;
            }
        }
        else if (znakwyboru==3)
            goto menu;
        else if (znakwyboru==1)
            {
                rozdzial1:
                rozdzial1();
                if (wyjscie==1)
                    goto menu;
            }
        if (ukonczenie==1)
        {
            rozdzial1uk:
            system("CLS");
            cout << '\t' << "Koniec Rozdzialu 1!" << endl;
            cout << endl << '\t' << "Twoj ekwipunek to: " << endl;
            if (kluczedom==1)
                cout << '\t' << "-klucze do chaty" << endl;
            cout << endl << '\t' << "Stan zdrowia: " << zdrowie << endl;
            cout << endl << '\t' << "Godzina 23:" << godzina1 << endl;
            cout << endl << '\t' << "Nacisnij 1 aby kontynuowac lub 0 aby wrocic do menu" << endl;
            cin >> x;
            if (x==1)
                rozdzial2();
                if (ukonczenie==2)
                    goto rozdzial2uk;
            if (wyjscie==1)
                    goto menu;
            else if (x==0)
                goto menu;
            else
                goto rozdzial1uk;
        }
        if (ukonczenie==2)
        {
            rozdzial2uk:
            system("CLS");
            cout << '\t' << "Koniec Rozdzialu 2!" << endl;
            cout << endl << '\t' << "Twoj ekwipunek to: " << endl;
            if (bandaz==1)
                cout << '\t' << "-bandaz" << endl;
            if (siekiera==1)
                cout << '\t' << "-siekierka" << endl;
            if (jedzenie==1)
                cout << '\t' << "-jedzenie" << endl;
            if (woda==1)
                cout << '\t' << "-woda" << endl;
            if (drewno==1)
                cout << '\t' << "-drewno" << endl;
            if (latarka==1)
                cout << '\t' << "-latarka" << endl;
            cout << endl << '\t' << "Stan zdrowia: " << zdrowie << endl;
            cout << endl << '\t' << "Godzina 10:" << godzina2 << endl;
            cout << endl << '\t' << "Nacisnij 1 aby kontynuowac lub 0 aby wrocic do menu" << endl;
            cin >> x;
            if (x==1)
                rozdzial3();
                if (wyjscie==1)
                    goto menu;
            else if (x==0)
                goto menu;
            else
                goto rozdzial2uk;
        }
    }
    return 0;
}

void mapa()
{
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
            tab[i][j]="||||";
        }
    }for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
            tab[i][j]="x";
            cout << tab[i][j];
        }
        cout << endl;
    }
    tab[4][3]="dom|";
    tab[7][7]="auto";
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
            cout << tab[i][j];
        }
        cout << endl;
    }
}

void menu()
{
    int x=0;
    while (x!=1&&x!=2&&x!=3&&x!=4&&x!=5)
    {
        poczatek:
        system("CLS");
        cout << " ...WHEN THE SUN GOES DOWN..." << '\t' << "v0.0.3" << endl;
        cout << '\t' << " 1.Graj" << endl;
        cout << '\t' << "    2.Opcje" << endl;
        cout << '\t' << " 3.Autorzy" << endl;
        cout << '\t' << "    4.Samouczek" << endl;
        cout << '\t' << " 5.Wyjdz" << endl;
        cin >> x;
        if (x==1)
        {
            znakmenu=1;
        }
        else if (x==2)
        {
            while (x!=1||x!=2)
            {
                system("CLS");
                cout << '\t' << "Wybierz jezyk: " << endl;
                cout << '\t' << " 1.Polski" << endl << '\t' << "  2.Angielski" << endl << '\t' << " 3.Wroc" << endl;
                cin >> x;
                if (x==1)
                {
                    system("CLS");
                    cout << '\t' << "Wybrales j.polski" << endl;
                    cout << endl << '\t' << "Nacisnij 1 aby kontynuowac" << endl;
                    cin >> x;
                    goto poczatek;
                }
                else if (x==2)
                {
                    system("CLS");
                    cout << '\t' << "Jeszcze nie obslugiwany" << endl;
                    cout << endl << '\t' << "Nacisnij 1 aby kontynuowac" << endl;
                    cin >> x;
                    goto poczatek;
                }
                else if (x==3)
                    goto poczatek;
            }
        }
        else if (x==3)
        {
            system("CLS");
            cout << '\t' << "Made by: Bartosz Helinski" << endl;
            cout << endl << '\t' << " 1.Wroc" << endl;
            cin >> x;
            goto poczatek;
        }
        else if (x==4)
        {
            system("CLS");
            cout << '\t' << "W grze musisz dokonywac wyborow. Niektore spowoduja niepowtarzalne wydarzenia a inne sprowadza cie do tej samej sytuacji." << endl << endl << '\t' <<  "Sterowanie - wybory: 1-4;   kontynuacja: dowolna cyfra;   wyjscie: 0;   podnoszenie przedmiotow: automatyczne(+);   wymagany przedmiot: !;   aby zatwierdzic: ENTER" << endl << endl << '\t' << "Zalecane jest granie w powiekszonym oknie oraz przyblizenie uzywacjac Ctrl i scrolla myszki." << endl << endl << '\t' << "Savey sa robione po kazdym rozdziale. Pamietaj tez ze w grze istnieje system hp wiec dbaj o niego poniewaz gdzy hp spadnie do 0... nie ma juz odwrotu..." << endl << endl << '\t'  << "Nie jest to jeszcze ukonczona wersja. Badz wyrozumialy :) Zycze udanej zabawy..." << endl << endl;
            cout << endl << '\t' << " 1.Wroc" << endl;
            cin >> x;
            goto poczatek;
        }
        else if (x==5)
        {
            znakmenu=0;
        }
    }
}

void wyborgry()
{
    int x=0;
    while (x!=1&&x!=2&&x!=3)
    {
        system("CLS");
        cout << '\t' << " 1.Nowa gra" << endl;
        cout << '\t' << "  2.Kontynuuj" << endl;
        cout << '\t' << " 3.Cofnij" << endl;
        cin >> x;
        if (x==1)
        {
            wyjscie=0;
            ukonczenie=0;
            znakwyboru=1;
            zdrowie=rand()%21+50;
            godzina1=rand()%50+10;
            godzina2=rand()%50+10;
        }
        else if (x==2)
        {
            znakwyboru=2;
            godz1=rand()%50+10;
            godz2=rand()%50+10;
            zdrow=rand()%21+50;
            godzina1=godz1;
            godzina2=godz2;
            zdrowie=zdrow;
        }
        else if (x==3)
            znakwyboru=3;
    }
}

void rozdzial1()
{
    int x, puk=0;
    system("CLS");
    cout << '\t' << "Rozdzial 1: \"Chata w lesie\"" << endl;
    cout << endl << '\t' << "Nacisnij 1 aby rozpoczac lub 0 aby wrocic do menu" << endl;
    cin >> x;
    if (x!=0)
    {
    jeszczeraz1:
    system("CLS");
    cout << '\t' << "Obudziles sie w lesie. Nie wiesz kim jestes ani gdzie sie znajdujesz." << endl << '\t' << "Jest noc a jedyne co widzisz to polykajace swiatlo gdzies w oddali..." << endl;
    cout << endl << '\t' << " 1.Idz w strone swiatla" << endl;
    cin >> x;
    if (x==1)
    {
        jeszczeraz2:
        system("CLS");
        cout << '\t' << "Wyczerpany dochodzisz do chaty. W lesie slychac dziwne, niepokojace odglosy. Pukasz w drzwi ale wydaje sie ze nikogo nie ma w srodku..." << endl;
        cout << endl << '\t' << " 1.Sprobuj wejsc do srodka" << endl;
        cout << '\t' << "  2.Spojrz przez okno" << endl;
        cin >> x;
        if (x==1)
        {
            jeszczeraz3:
            system("CLS");
            cout << '\t' << "Niestety drzwi okazuja sie byc zamkniete..." << endl;
            cout << endl << '\t' << " 1.Sprobuj wejsc przez okno" << endl;
            cout << '\t' << "  2.Pukaj dalej" << endl;
            cin >> x;
            if (x==1)
                goto przezokno;
            else if (x==2)
            {
                pukpuk:
                puk++;
                system("CLS");
                cout << '\t' << "Dalej nikt nie odpowiada..." << endl;
                cout << endl << '\t' << " 1.Sprobuj wejsc przez okno" << endl;
                cout << '\t' << "  2.Pukaj dalej" << endl;
                cin >> x;
                if(puk>=10)
                {
                    system("CLS");
                    cout << '\t' << "Otwiera ci stary mezczyzna. Pijecie razem herbate. Przypomina ci sie jak kumple dla zartow cie tu przywiezli. Prosisz mezczyne o podwozke a on sie zgadza. Tej nocy na pewno nie zapomnisz juz nigdy." << endl;
                    cout << '\t' << "Koniec!!!" << endl << "Odblokowales ukryte zakonczenie. Brawo!!!" << endl;
                    cout << '\t' << "Wcisznij 1 aby kontynuowac!" << endl;
                    cin >> x;
                    goto koniec;
                }
                if (x==1)
                    goto jeszczeraz4;
                else
                    goto pukpuk;
            }
            else
                goto jeszczeraz3;
        }
        else if (x==2)
        {
            jeszczeraz4:
            system("CLS");
            cout << '\t' << "Przez zniszczone okno widzisz palacy sie w piecu ogien, klucze oraz stara kartke wiszaca na scianie..." << endl;
            cout << endl << '\t' << " 1.Sprobuj wejsc" << endl;
            cout << '\t' << "  2.Wroc do drzwi" << endl;
            cin >> x;
            if (x==2)
                goto jeszczeraz3;
            else if (x==1)
            {
                przezokno:
                jeszczeraz5:
                system("CLS");
                cout << '\t' << "Potluczonym szklem skaleczyles sie w reke, rana krwawi ale udalo ci sie dostac do srodka." << endl << '\t' << "Bierzesz klucze i podchodzisz do tajemniczej kartki na scianie." << endl << '\t' << "Widnieje tam napis :" << endl << '\t' << "\" Dla mnie jest juz za pozno ale jesli to czytasz to masz jeszcze szanse." << endl << '\t' << "Pamietaj! - zabarykaduj okna, zadbaj o zapas prowiantu oraz NIE WYCHODZ W NOCY Z CHATY!!! ...one nie lubia swiatla..." << endl << '\t' << "A i nie otwieraj piwnicy... lepiej zebym tam zostal juz na zawsze... \" (+klucze do domku)(stan zdrowia--)" << endl;
                kluczedom+=1;
                zdrowie-=10;
                cout << endl << '\t' << " 1.Sprawdz co jest w piwnicy" << endl;
                cout << '\t' << "  2.Zamknij drzwi i poloz sie spac" << endl;
                cout << '\t' << "   3.Sprawdz dziwne odglosy na zewnatrz" << endl;
                cin >> x;
                if (x==1)
                {
                    piwnica:
                    system("CLS");
                    cout << '\t' << "Bierzesz klucze i powoli otwierasz klape piwnicy. Schodzisz w dol. Widzisz stojacego w kacie mezczyzne..." << endl;
                    cout << endl << '\t' << " 1.Wroc na gore i zamknij klape" << endl;
                    cout << '\t' << "  2.Powoli podejdz do niego" << endl;
                    cin >> x;
                    if (x==1)
                    {
                        powrot:
                        system("CLS");
                        cout << '\t' << "Udajesz sie na gore i szybko zamykasz klape na klucz. Jestes wyczerpany decydaujesz sie polozyc w lozku..." << endl;
                        cout << endl << '\t' << " 1.Pojdz spac" << endl;
                        cin >> x;
                        if (x==1)
                        {
                            goto sen;
                        }
                        else
                            goto powrot;
                    }
                    else if (x==2)
                    {
                        system("CLS");
                        cout << '\t' << "Powoli podchodzisz do mezczyny. Lapiesz go za bark aby sprawdzic czy nic mu nie jest, lecz on rzuca sie na ciebie probujac cie ugryzc" << endl << '\t' << "Udaje cie sie go odepchnac ale on nie ustepuje... nie pozostawil ci wyboru musiales go zabic... niestety zanim skonal zdazyl ugryzc cie w szyje." << endl << '\t' << "Czujesz sie coraz slabszy, wczolgujesz sie na gore po schodach, lecz spadasz z nich. Ostatni co widzisz widzisz to zakrwawiony mlotek w twej dloni..." << endl;
                        smierc:
                        cout << endl << '\t' << "Ncisnij 1 aby kontynuowac" << endl;
                        cin >> x;
                        system("CLS");
                        cout << '\t' << "Dolaczyles do swiata cienii... chcesz sprobowac jeszcze raz?(1) czy wrocic do menu?(0)" << endl;
                        cin >> x;
                        if (x==1)
                            goto jeszczeraz1;
                        else if (x==0)
                            wyjscie=1;
                        else
                            goto smierc;
                    }
                    else
                        goto piwnica;
                }
                else if (x==2)
                {
                    sen:
                    system("CLS");
                    cout << '\t' << "Obracajac sie z boku na bok myslisz o przerazajacych odglosach z lasu. Zamknales drzwi i wiesz ze narazie jestes bezpieczny w domu, lecz wszystkie te dzwieki nie daja ci spokoju..." << endl;
                    cout << endl << '\t' << " 1.Zasnij" << endl;
                    cout << '\t' << "  2.Sprawdz zrodla halasu" << endl;
                    cin >> x;
                    if (x==1)
                        ukonczenie=1;
                    else if (x==2)
                        goto jeszczeraz6;
                    else
                        goto sen;
                }
                else if (x==3)
                {
                    jeszczeraz6:
                    system("CLS");
                    cout << '\t' << "Powolnym krokiem wychodzisz na zwenatrz. Widzisz trzy sylwetki ukryte w ceiniu. Jecza i cos mamrocza..." << endl;
                    cout << endl << '\t' << " 1.Podejdz do nich" << endl;
                    cout << '\t' << "  2.Wroc szybko do chaty i zamknij drzwi" << endl;
                    cin >> x;
                    if (x==1)
                    {
                        system("CLS");
                        cout << '\t' << "Powoli posuwasz sie w strone sylwetek. Jestes coraz blizej. Kiedy jestes w odleglosci 2 metrow czujesz jak cos lapie cie za noge i wciaga pod ziemie..." << endl << '\t' << "Czujesz jak twoje mieso zostaje rozrywane na kawalki. Czujesz niewyobrazalny bol... az w koncy nie czujesz nic..." << endl;
                        goto smierc;
                    }
                    else if (x==2)
                    {
                        jeszczceraz7:
                        system("CLS");
                        cout << '\t' << "Jeki nie ustaja ale ty juz jestes bezpieczny w domu..." << endl;
                        cout << endl << '\t' << " 1.Pojdz spac" << endl;
                        cout << '\t' << "  2.Sprawdz piwnice" << endl;
                        cin >> x;
                        if (x==1)
                            goto sen;
                        else if (x==2)
                        {
                            goto piwnica;
                        }
                        else
                            goto jeszczceraz7;
                    }
                    else
                        goto jeszczeraz6;
                }
                else
                    goto jeszczeraz5;
            }
            else
                goto jeszczeraz4;
        }
        else
            goto jeszczeraz2;
    }
    else
        goto jeszczeraz1;
    }
    else
    {
        koniec:
        system("CLS");
        wyjscie=1;
    }
}

void rozdzial2()
{
    int x;
    system("CLS");
    cout << '\t' << "Rozdzial 2: \"Dom i szopa\"" << endl;
    cout << endl << '\t' << "Nacisnij 1 aby rozpoczac lub 0 aby wrocic do menu" << endl;
    cin >> x;
    if (x!=0)
    {
    jeszczeraz1:
    system("CLS");
    cout << '\t' << "Pierwsze promienie swiatla budza cie. Jestes caly obolaly. Ranna reka boli coraz bardziej..." << endl;
    cout << endl << '\t' << " 1.Przeszukaj chate" << endl;
    cout << '\t' << "  2.Wyjdz na zewnatrz" << endl;
    cout << '\t' << " 3.Zdobadz drewno i prowiant (!siekiera, odpoczynek)" << endl;
    cin >> x;
    if (x==1&&przeszukanie<=0)
    {
        jeszczeraz3:
        system("CLS");
        cout << '\t' << "Przeszukania oplacily sie. Znalazles: bandaz, latarke oraz pare puszek konserw... (+bandaz, latarka, jedzenie)" << endl;
        przeszukanie=1;
        latarka=1;
        bandaz=1;
        jedzenie=1;
        cout << endl << '\t' << " 1.Opatrz rane" << endl;
        cout << '\t' << "  2.Zjedz konserwe" << endl;
        cout << '\t' << " 3.Wroc" << endl;
        cin >> x;
        if (x==1)
        {
            bandaz:
            system("CLS");
            cout << '\t' << "Znalezionym bandazem opatrzyles rane. Czujesz sie duzo lepiej... (+odpoczynek)(-bandaz)" << endl;
            zdrowie+=30;
            bandaz=0;
            odpoczynek=1;
            cout << endl << '\t' << " 1.Zjedz konserwe" << endl;
            cout << '\t' << "  2.Wyjdz na zewnatrz" << endl;
            cin >> x;
            if (x==1&&jedzenie==1)
                goto jedzenie;
            else if (x==1&&jedzenie==0)
            {
                jedzeniebrak:
                system("CLS");
                cout << '\t' << "Zuzyles juz cale jedzenie!" << endl;
                cout << endl << '\t' << " 1.Wroc" << endl;
                cin >> x;
                if (x==1)
                goto bandaz;
                else goto jedzeniebrak;
            }
            else if (x==2)
                goto jeszczeraz2;
            else
                goto bandaz;
        }
        else if (x==2)
        {
            jedzenie:
            system("CLS");
            cout << '\t' << "Dzieki konserwom czujesz sie syty i wypoczety. Niestety reka wciaz boli... (+odpoczynek)(-jedzenie)" << endl;
            zdrowie+=20;
            jedzenie=0;
            odpoczynek=1;
            cout << endl << '\t' << " 1.Opatrz rane" << endl;
            cout << '\t' << "  2.Wyjdz na zewnatrz" << endl;
            cin >> x;
            if (x==1&&bandaz==1)
                goto bandaz;
            else if (x==1&&bandaz==0)
            {
                bandazbrak:
                system("CLS");
                cout << '\t' << "Zuzyles juz bandaz!" << endl;
                cout << endl << '\t' << " 1.Wroc" << endl;
                cin >> x;
                if (x==1)
                goto jedzenie;
                else goto bandazbrak;
            }
            else if (x==2)
                goto jeszczeraz2;
            else
                goto jedzenie;
        }
        else if (x==3)
            goto jeszczeraz1;
        else
            goto jeszczeraz3;
    }
    else if (x==1&&przeszukanie==1)
    {
        juzprzeszukane:
        system("CLS");
        cout << '\t' << "Przeszukales juz chate!" << endl;
        cout << endl << '\t' << " 1.Opatrz rane" << endl;
        cout << '\t' << "  2.Zjedz konserwe" << endl;
        cout << '\t' << " 3.Cofnij" << endl;
        cin >> x;
        if (x==1&&bandaz==1)
        {
            bandaz2:
            system("CLS");
            cout << '\t' << "Znalezionym bandazem opatrzyles rane. Czujesz sie duzo lepiej... (+odpoczynek)(-bandaz)" << endl;
            zdrowie+=30;
            bandaz=0;
            cout << endl << '\t' << " 1.Zjedz konserwe" << endl;
            cout << '\t' << "  2.Wyjdz na zewnatrz" << endl;
            cin >> x;
            if (x==1&&jedzenie==1)
                goto jedzenie2;
            else if (x==1&&jedzenie==0)
                goto brakbandaza;
            else if (x==2)
                goto jeszczeraz2;
            else
                goto bandaz2;
        }
        else if (x==1&&bandaz==0)
        {
            brakbandaza:
            system("CLS");
            cout << '\t' << "Zuzyles juz bandaz!" << endl;
            cout << endl << '\t' << " 1.Wroc" << endl;
            cin >> x;
            if (x==1)
                goto juzprzeszukane;
            else
                goto brakbandaza;
        }
        else if (x==2&&jedzenie==1)
        {
            jedzenie2:
            system("CLS");
            cout << '\t' << "Dzieki konserwom czujesz sie syty i wypoczety. Niestety reka wciaz boli... (+odpoczynek)(-jedzenie)" << endl;
            zdrowie+=20;
            jedzenie=0;
            cout << endl << '\t' << " 1.Opatrz rane" << endl;
            cout << '\t' << "  2.Wyjdz na zewnatrz" << endl;
            cin >> x;
            if (x==1&&bandaz==1)
                goto bandaz2;
            else if (x==1&&bandaz==0)
                goto brakbandaza;
            else if (x==2)
                goto jeszczeraz2;
            else
                goto jedzenie2;
        }
        else if (x==2&&jedzenie==0)
        {
            brakjedzenia:
            system("CLS");
            cout << '\t' << "Zuzyles juz cale jedzenie!" << endl;
            cout << endl << '\t' << " 1.Wroc" << endl;
            cin >> x;
            if (x==1)
                goto juzprzeszukane;
            else
                goto brakjedzenia;
        }
        else if (x==3)
            goto jeszczeraz1;
        else
            goto juzprzeszukane;
    }
    else if (x==2)
    {
        jeszczeraz2:
        system("CLS");
        cout << '\t' << "Slonce dopiero wstaje. Widzisz otaczajacy cie las. Dookola nie widzisz nikogo. Kawalek od chaty zauwazasz baniak na wode oraz stara szope... (+woda)" << endl;
        woda+=1;
        cout << endl << '\t' << " 1.Wroc do chaty" <<endl;
        cout << '\t' << "  2.Idz do szopy" << endl;
        cout << '\t' << " 3.Napij sie wody" <<endl;
        cin >> x;
        if (x==1)
        {
            goto jeszczeraz1;
        }
        else if (x==2)
        {
            jeszczeraz4:
            system("CLS");
            cout << '\t' << "Drzwi od szopy sa otwarte wiec wchodzisz do srodka. Wydaje sie byc pusta. Lezy tam tylko resztka drewna na opal oraz siekiera." << endl << '\t' << "Nagle zauwazasz dziurke od klucza w podlodze. Niestety zaden z twoich tam nie pauje... (+drewno, siekiera)" << endl;
            drewno=1;
            siekiera=1;
            cout << endl << '\t' << " 1.Wroc" << endl;
            cin >> x;
            if (x==1)
            {
                goto jeszczeraz2;
            }
            else
                goto jeszczeraz4;
        }
        else if (x==3&&woda>=1)
        {
            woda1:
            system("CLS");
            cout << '\t' << "Zaspokoiles pragnienie. Niestety wciaz doskwiera ci bol reki i glod... (+odpoczynek)(-woda)" << endl;
            zdrowie+=10;
            woda-=999;
            odpoczynek=1;
            cout << '\t' << " 1.Wroc" << endl;
            cin >> x;
            if (x==1)
                goto jeszczeraz2;
            else
                goto woda1;
        }
        else if (x==3&&woda<=0)
        {
            woda2:
            system("CLS");
            cout << '\t' << "Niestety wykorzystales juz cala wode!" << endl;
            cout << '\t' << " 1.Wroc" << endl;
            cin >> x;
            if (x==1)
                goto jeszczeraz2;
            else
                goto woda2;
        }
        else
            goto jeszczeraz2;
    }
    else if (x==3&&siekiera==0&&odpoczynek==0)
    {
        brak1:
        system("CLS");
        cout << '\t' << "Musisz jeszcze odpoczac i zdobyc siekiere!" << endl;
        cout << endl << '\t' << " 1.Wroc" << endl;
        cin >> x;
        if (x==1)
            goto jeszczeraz1;
        else
            goto brak1;
    }
    else if (x==3&&siekiera==1&&odpoczynek==0)
    {
        brak2:
        system("CLS");
        cout << '\t' << "Musisz jeszcze odpoczac!" << endl;
        cout << endl << '\t' << " 1.Wroc" << endl;
        cin >> x;
        if (x==1)
            goto jeszczeraz1;
        else
            goto brak2;
    }
    else if (x==3&&siekiera==0&&odpoczynek==1)
    {
        brak3:
        system("CLS");
        cout << '\t' << "Musisz jeszcze zdobyc siekiere!" << endl;
        cout << endl << '\t' << " 1.Wroc" << endl;
        cin >> x;
        if (x==1)
            goto jeszczeraz1;
        else
            goto brak3;
    }
    else if (x==3&&siekiera==1&&odpoczynek==1)
    {
        jest1:
        system("CLS");
        cout << '\t' << "Wypoczety i gotowy do pracy ruszyles w las szukac szansy na przetrwanie..." << endl;
        cout << endl << '\t' << " 1.Wyrusz w las" << endl;
        ukonczenie=2;
        cin >> x;
        if (x!=1)
            goto jest1;
    }
    else
        goto jeszczeraz1;
    }
    else
    {
        system("CLS");
        wyjscie=1;
    }

}
void rozdzial3()
{
    int x;
    system("CLS");
    cout << '\t' << "Rozdzial 3: \"Wyprawa\"" << endl;
    cout << endl << '\t' << "Nacisnij 1 aby rozpoczac lub 0 aby wrocic do menu" << endl;
    cin >> x;
    if (x!=0)
    {
    poczatek3:
    system("CLS");
    cout << '\t' << "Maszerujac miedzy drzewami w poszukiwaniu jedzenia natrafiasz na stary i zepsuty samochod. Przez brudne szyby nie widac co znajduje sie w srodku..." << endl;
    cout << endl << '\t' << " 1.Sprawdz wnetrze pojazdu" << endl;
    cout << '\t' << "  2.Sprawdz bagaznik" << endl;
    cout << '\t' << " 3.Idz dalej" << endl;
    cin >> x;
    if (x==1)
    {
        system("CLS");
        cout << '\t' << "Powolnym ruchem otwierasz drzwi samochodu. Nagle slyszysz jakies piski ze srodka..." << endl;
        cout << endl << '\t' << " 1.Otworz drzwi" << endl;
        cout << '\t' << "  2.Odsun sie od auta" << endl;
        cin >> x;
        if (x==1)
        {
            poczatek4:
            system("CLS");
            cout << '\t' << "Pewnym ruchem otwierzassz drzwi. Ngale z jego wnetrza wyskakuje... wiewiorka... to ona musiala byc sprawca tych piskow..." << endl;
            cout << endl << '\t' << " 1.Przeszukaj srodek" << endl;
            cin >> x;
            if (x==1)
            {
                poczatek5:
                system("CLS");
                cout << '\t' << "Znajdzujesz kluczyki do auta i stare ubrania..." << endl;
                cout << endl << '\t' << " 1.Wroc" << endl;
                kluczeauto=1;
                cin >> x;
                if (x==1)
                    goto poczatek3;
                else
                    goto poczatek5;
            }
            else
                goto poczatek4;
        }
        else
            goto poczatek3;
    }
    else if (x==2)
    {
        system("CLS");
        if (kluczeauto==0)
        {
            bagaznik1:
            cout << '\t' << "Probujesz otworzyc klape bagaznika ale ani drgnie. Jest zamknieta. Musisz znalezc klucz..." << endl;
            cout << endl << '\t' << " 1.Wroc" << endl;
            cin >> x;
            if (x==1)
                goto poczatek3;
            else
                goto bagaznik1;
        }
        else
        {
            cout << '\t' << "Znalezionymi kluczami otwierasz bagaznik. W srodku znajdujesz mape..." << endl;
            cout << endl << '\t' << " 1.Spojrz na mape" << endl;
            cin >> x;
            mapa();
            cin >> x;
        }
    }
    else if (x==3)
    {
        system("CLS");
        cout << "narazie tyle" << endl;
    }
    else
        goto poczatek3;
    }
    else
    {
        system("CLS");
        wyjscie=1;
    }
}
