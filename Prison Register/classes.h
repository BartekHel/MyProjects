#pragma once
#include<iostream>

using namespace std;

/**
* Pierwsza z klas zawierajaca w sobie strukture odpowiedzialna za przechowywanie danych osobowych.
* Zaprzyjazniona z szablonem klasy Lista.
*/
class Tab1 {
    template<typename U> friend class List;
public:
/**
* Struktura przechowujaca dane osobowe takie jak id, imie, nazwisko, date urodzenia oraz plec.
* Posiada 2 konstruktory - bezargumentowy z wartosciami domyslnymi oraz wieloargumentowy.
*/
    struct Dane {
        int id;
        string imie;
        string nazwisko;
        int dzien;
        int miesiac;
        int rok;
        char plec;

        /** Konstruktor bezagrumentowy z wartosciami domyslnymi.
        */
        Dane() : id(0), imie(" "), nazwisko(" "), dzien(0), miesiac(0), rok(0), plec(' ') {}
        /** Konstruktor wieloargumentowy.
        */
        Dane(int id, string imie, string nazwisko, int dzien, int miesiac, int rok, char plec) : id(id), imie(imie), nazwisko(nazwisko), dzien(dzien), miesiac(miesiac), rok(rok), plec(plec) {}
    };

    /** Metoda odpowiedzialna za odczyt danych z pliku.
    */
    void odczyt(const string&, List<Tab1::Dane>&);
    /** Operator porownania.
    */
    friend bool operator==(const Tab1::Dane& dane1, const Tab1::Dane& dane2) {
        return dane1.id == dane2.id && dane1.imie == dane2.imie && dane1.nazwisko == dane2.nazwisko && dane1.dzien == dane2.dzien && dane1.miesiac == dane2.miesiac && dane1.rok == dane2.rok && dane1.plec == dane2.plec;
    }
    /** Operator mniejszosci.
    */
    friend bool operator<(const Tab1::Dane& dane1, const Tab1::Dane& dane2) {
        if (dane1.id != dane2.id)
            return dane1.id < dane2.id;
        else if (dane1.imie != dane2.imie)
            return dane1.imie < dane2.imie;
        else if (dane1.nazwisko != dane2.nazwisko)
            return dane1.nazwisko < dane2.nazwisko;
        else if (dane1.dzien != dane2.dzien)
            return dane1.dzien < dane2.dzien;
        else if (dane1.miesiac != dane2.miesiac)
            return dane1.miesiac < dane2.miesiac;
        else if (dane1.rok != dane2.rok)
            return dane1.rok < dane2.rok;
        else if (dane1.plec != dane2.plec)
            return dane1.plec < dane2.plec;
        return false;
    }
    /** Operator wejscia strumieniowego.
    */
    friend istream& operator>>(istream& in, Tab1::Dane& dane) {
        in >> dane.id >> dane.imie >> dane.nazwisko >> dane.dzien >> dane.miesiac >> dane.rok >> dane.plec;
        return in;
    }
    /** Destruktor klasy Tab1.
    */
    ~Tab1() {}
};



/**
* Druga z klas zawierajaca w sobie strukture odpowiedzialna za przechowywanie danych wieziennych.
* Zaprzyjazniona z szablonem klasy Lista.
*/
class Tab2 {
    template<typename U> friend class List;
public:
/**
* Struktura przechowujaca dane wiezienne takie jak id, przewinienie, dlugosc kary oraz numer celi wraz z blokiem wieziennym.
* Posiada 2 konstruktory - bezargumentowy z wartosciami domyslnymi oraz wieloargumentowy.
*/
    struct Wiezienie {
        int id;
        string przewinienie;
        int dlugosc;
        string jednostka;
        string cela;

        /** Konstruktor bezagrumentowy z wartosciami domyslnymi.
        */
        Wiezienie() : id(0), przewinienie(" "), dlugosc(0), jednostka(" "), cela(" ") {}
        /** Konstruktor wieloargumentowy.
        */
        Wiezienie(int id, string przewinienie, int dlugosc, string jednostka, string cela) : id(id), przewinienie(przewinienie), dlugosc(dlugosc), jednostka(jednostka), cela(cela) {}
    };

    /** Metoda odpowiedzialna za odczyt danych z pliku.
    */
    void odczyt(const string&, List<Tab2::Wiezienie>&);
    /** Operator porownania.
    */
    friend bool operator==(const Tab2::Wiezienie& w11_1, const Tab2::Wiezienie& w11_2) {
        return w11_1.id == w11_2.id && w11_1.przewinienie == w11_2.przewinienie && w11_1.dlugosc == w11_2.dlugosc && w11_1.jednostka == w11_2.jednostka && w11_1.cela == w11_2.cela;
    }
    /** Operator mniejszosci.
    */
    friend bool operator<(const Tab2::Wiezienie& w11_1, const Tab2::Wiezienie& w11_2) {
        if (w11_1.id != w11_2.id)
            return w11_1.id < w11_2.id;
        else if (w11_1.przewinienie != w11_2.przewinienie)
            return w11_1.przewinienie < w11_2.przewinienie;
        else if (w11_1.dlugosc != w11_2.dlugosc)
            return w11_1.dlugosc < w11_2.dlugosc;
        else if (w11_1.jednostka != w11_2.jednostka)
            return w11_1.jednostka < w11_2.jednostka;
        else if (w11_1.cela != w11_2.cela)
            return w11_1.cela < w11_2.cela;
        return false;
    }
    /** Operator wejscia strumieniowego.
    */
    friend istream& operator>>(istream& in, Tab2::Wiezienie& w11) {
        in >> w11.id >> w11.przewinienie >> w11.dlugosc >> w11.jednostka >> w11.cela;
        return in;
    }
    /** Destruktor klasy Tab2.
    */
    ~Tab2() {}
};



/**
* Klasa odpowiedzialna za wyswietlanie interfejsu uzytkownikowi.
*/
class Interfejs {
public:
    /** Metoda wyswietlajaca liste opcji do wyboru w menu.
    */
    void menu();
    /** Metoda wyswietlajaca wszystkie listy, na ktorych mozna dokonywac roznych operacji.
    */
    int wybor();
    /** Metoda wyswietlajaca komunikat o bledzie wyboru.
    */
    void blad();
    /** Metoda odpowiedzialna za dzialanie calego interfejsu.
    * Mozna w niej dokonywac wyborow operacji oraz listy.
    */
    void program(List<Tab1::Dane>&, List<Tab2::Wiezienie>&, const string&);
    /** Metoda czyszczaca plik wyjsciowy.
    */
    void zapis_clear(const string&);
};


/** Funkcja odpowiedzilna za sprawdzenie poprawnosci argumentow podanych w konsoli.
* Przypisuje odpowiednie nazwy plikow do danych wejsciowych/wyjsciowych.
*/
void parameters_check(int, char* [], string&, string&, string&);