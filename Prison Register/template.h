#pragma once
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

/**
* Klasa template-owa przedstawiajaca pojedynczy element (Node) w liscie.
* Zaprzyjazniona z klasa glowna czyli Lista.
* Posiada element typu T zawierajaca dane oraz wskaznik na kolejny element listy.
*/
template<typename T>
class Node {
    template<typename U> friend class List;

    T data;
    shared_ptr<Node<T>> next;

public:
    /** Konstruktor jednoargumentowy.
    */
    Node(T obj) : data(obj), next(NULL) {}
    /** Destruktor klasy Node.
    */
    ~Node() {}
};

/**
* Najwazniejsza klasa w programie.
* Jest to template listy jednokierunkowej.
* Posiada rozne metody, operatory oraz konstrukotry pozwalajace na roznego rodzaje operacje na liscie.
* Kompatybilna ze wszystkimi podstawowymi typami danych oraz m.in. testowanymi w tym programie dwoma klasami.
* Zaprzyjazniona z klasami, na ktorych jest testowana czyli Tab1 oraz Tab2.
*/
template<typename T>
class List {
    friend class Tab1;
    friend class Tab2;
    shared_ptr<Node<T>> head;

public:
    /** Konstruktor bezargumentowy z wartoscia domyslna head.
    */
    List() : head(NULL) {}
    /** Konstruktor kopiujacy.
    */
    List(const List& lista) : head(NULL) {
        shared_ptr<Node<T>> ptr = lista.head;
        while (ptr != NULL) {
            push_back(ptr->data);
            ptr = ptr->next;
        }
    }
    /** Konstruktor przenoszacy.
    */
    List(List&& lista) {
        head = NULL;
        shared_ptr<Node<T>> ptr = lista.head;
        while (ptr != NULL) {
            push_back(move(ptr->data));
            ptr = ptr->next;
        }
        lista.head = NULL;
    }
    /** Metoda zwracajaca wskaznik na head.
    */
    const shared_ptr<Node<T>>& get_head() const { return head; }
    /** Metoda dodajaca element na poczatek listy.
    */
    void push_front(const T&);
    /** Metoda dodajaca element na koniec listy.
    */
    void push_back(const T&);
    /** Metoda usuwajaca element z poczatku listy.
    */
    void pop_front();
    /** Metoda usuwajaca element z konca listy.
    */
    void pop_back();
    /** Metoda usuwajaca element z wybranego miejsca w liscie.
    */
    void pop(const int);
    /** Metoda zwracajaca element w liscie o zadanym indexie.
    */
    T get_element(const int);
    /** Metoda zwracajaca element w liscie o zadanym id.
    */
    T get_element2(const int);
    /** Metoda zwracajaca index wybranego elementu.
    */
    int get_index(const T&);
    /** Metoda zwracajaca index elementu o wskazanym id.
    */
    int get_index(const int);
    /** Metoda usuwajaca wybrany element z listy.
    */
    void remove(const T&);
    /** Metoda mowiaca czy jeden element jest wiekszy od drugiego.
    */
    bool greater(const T&, const T&);
    /** Metoda mowiaca czy jeden element jest mniejszy od drugiego.
    */
    bool smaller(const T&, const T&);
    /** Metoda mowiaca czy jeden element typu Tab1::Dane jest wiekszy od drugiego.
    */
    bool greater(const Tab1::Dane&, const Tab1::Dane&, const int);
    /** Metoda mowiaca czy jeden element typu Tab1::Dane jest mniejszy od drugiego.
    */
    bool smaller(const Tab1::Dane&, const Tab1::Dane&, const int);
    /** Metoda mowiaca czy jeden element typu Tab2::Wiezienie jest wiekszy od drugiego.
    */
    bool greater(const Tab2::Wiezienie&, const Tab2::Wiezienie&, const int);
    /** Metoda mowiaca czy jeden element typu Tab2::Wiezienie jest mniejszy od drugiego.
    */
    bool smaller(const Tab2::Wiezienie&, const Tab2::Wiezienie&, const int);
    /** Metoda sortujaca cala liste.
    */
    void sort(const int);
    /** Metoda sortujaca wybrany rodzaj danych w liscie.
    */
    void sort(const int, const int);
    /** Metoda zliczajaca wybrany element w liscie.
    */
    int element_count(const string&);
    /** Metoda zliczajaca wybrany element w liscie typu Tab1::Dane.
    */
    int element_count1(const int, const string&);
    /** Metoda zliczajaca wybrany element w liscie typu Tab2::Wiezienie.
    */
    int element_count2(const int, const string&);
    /** Metoda wyliczajaca dlugosc pobytu w areszcie wybranego elementu.
    */
    int arrest_length(const int);
    /** Metoda mowiaca co sredniej dlugosci pobytu w areszcie wybranego lub wszystkich elementow.
    */
    double arrest_average(const string&);
    /** Metoda zwracajaca liste elementow, ktorych dlugosc pobytu w areszcie jest dluzna niz podana przez uzytkownika.
    */
    List<T> avarage_greater(const double, const string&);
    /** Metoda zwracajaca liste elementow, ktore sa z bloku wieziennego podanego przez uzytkownika.
    */
    List<T> block_check(const char);
    /** Metoda zwracajaca liste elementow, ktorych data urodzin miesci sie w przedziale podanym przez uzytkownika.
    */
    List<T> born_during(const int, const int, const int, const int, const int, const int);
    /** Metoda czyszczaca liste.
    */
    void clear();
    /** Metoda zwracajaca rozmiar listy.
    */
    int size();
    /** Metoda mowiaca o tym czy lista jest pusta.
    */
    bool is_empty();
    /** Metoda odpowiedzialna za serializacje danych w liscie do pliku binarnego (oprocz stringow).
    */
    void serialization(const string&);
    /** Metoda odpowiedzialna za deserializacje danych w pliku binarnym do listy (oprocz stringow).
    */
    void deserialization(const string&);
    /** Metoda odpowiedzialna za serializacje danych w liscie do pliku binarnego (tylko stringi).
    */
    void serialization_string(const string&);
    /** Metoda odpowiedzialna za deserializacje danych w pliku binarnym do listy (tylko stringi).
    */
    void deserialization_string(const string&);
    /** Metoda odpowiedzialna za wyswietlenie wybranego elementu w liscie.
    */
    void displayELement(const int);
    /** Metoda odpowiedzialna za wyswietlenie calej listy.
    */
    void displayList();
    /** Metoda odpowiedzialna za zapis listy do pliku.
    */
    void zapis(const string&);
    /** Metoda odpowiedzialna za zapis listy do pliku bez czyszczenia zawartosci pliku (log).
    */
    void zapis2(const string&);
    /** Metoda zwracajaca liste elementow powiazanych przez id z inna lista.
    */
    template<typename T, typename U>
    List<U> connections(const List<U>& lista) {
        List<U> result;
        shared_ptr<Node<T>> ptr = head;
        while (ptr != NULL) {
            shared_ptr<Node<U>> ptr1 = lista.get_head();
            while (ptr1 != NULL) {
                if (ptr->data.id == ptr1->data.id)
                    result.push_back(ptr1->data);
                ptr1 = ptr1->next;
            }
            ptr = ptr->next;
        }
        return result;
    }
    /** Operator przypisania.
    */
    List& operator=(const List& lista) {
        if (this == &lista) {
            return *this;
        }
        clear();
        shared_ptr<Node<T>> ptr = lista.head;
        while (ptr != NULL) {
            push_back(ptr->data);
            ptr = ptr->next;
        }
        return *this;
    }
    /** Operator przeniesienia.
    */
    List& operator=(List&& lista) {
        if (this == &lista) {
            return *this;
        }
        clear();
        shared_ptr<Node<T>> ptr = lista.head;
        while (ptr != NULL) {
            push_back(move(ptr->data));
            ptr = ptr->next;
        }
        lista.head = NULL;
        return *this;
    }
    /** Destruktor klasy Node.
    */
    ~List() {}
};

template<typename T>
void List<T>::push_front(const T& obj) {
    shared_ptr<Node<T>> node = make_shared<Node<T>>(obj);
    node->data = obj;

    if (head != NULL)
        node->next = head;
    head = node;
}

template<typename T>
void List<T>::push_back(const T& obj) {
    shared_ptr<Node<T>> node = make_shared<Node<T>>(obj);
    node->data = obj;

    if (head == NULL)
        head = node;
    else {
        shared_ptr<Node<T>> ptr = head;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = node;
    }
}

template<typename T>
void List<T>::pop_front() {
    if (head != NULL)
        head = head->next;
}

template<typename T>
void List<T>::pop_back() {
    if (head == NULL)
        return;
    else if (head->next == NULL)
        head = NULL;
    else {
        shared_ptr<Node<T>> ptr = head;
        while (ptr->next->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = NULL;
    }
}

template<typename T>
void List<T>::pop(const int index) {
    if (head == NULL || index < 0 || index >= size())
        return;
    else if (index == 0)
        pop_front();
    else {
        shared_ptr<Node<T>> ptr = head;
        int count = 0;
        while (++count != index)
            ptr = ptr->next;
        ptr->next = ptr->next->next;
    }
}

template<typename T>
T List<T>::get_element(const int index) {
    if (head != NULL) {
        shared_ptr<Node<T>> ptr = head;
        int count = 0;
        while (ptr != NULL) {
            if (count++ == index)
                return ptr->data;
            ptr = ptr->next;
        }
    }
    return T();
}

template<typename T>
T List<T>::get_element2(const int id) {
    if (head != NULL) {
        shared_ptr<Node<T>> ptr = head;
        while (ptr != NULL) {
            if (ptr->data.id == id)
                return ptr->data;
            ptr = ptr->next;
        }
    }
    return T();
}

template<typename T>
int List<T>::get_index(const T& dane) {
    if (head == NULL) {
        return -1;
    }
    shared_ptr<Node<T>> ptr = head;
    int index = 0;
    while (ptr != NULL) {
        if (ptr->data == dane) {
            return index;
        }
        ptr = ptr->next;
        ++index;
    }
    return -1;
}

template<typename T>
int List<T>::get_index(const int id) {
    if (head == NULL) {
        return -1;
    }
    shared_ptr<Node<T>> ptr = head;
    int index = 0;
    while (ptr != NULL) {
        if (ptr->data.id == id) {
            return index;
        }
        ptr = ptr->next;
        ++index;
    }
    return -1;
}

template<typename T>
void List<T>::remove(const T& obj) {
    if (head == NULL)
        return;
    else {
        shared_ptr<Node<T>> ptr = head;
        int index = 0;
        while (ptr != NULL) {
            if (obj == ptr->data) {
                pop(index);
                --index;
            }
            ++index;
            ptr = ptr->next;
        }
    }
}

template<class T>
bool List<T>::greater(const T& x, const T& y) {
    return !(x < y);
}

template<class T>
bool List<T>::smaller(const T& x, const T& y) {
    return (x < y);
}

template<class T>
bool List<T>::greater(const Tab1::Dane& a, const Tab1::Dane& b, const int choice) {
    switch (choice) {
    case 1:
        return a.id > b.id;
        break;
    case 2:
        return a.imie > b.imie;
        break;
    case 3:
        return a.nazwisko > b.nazwisko;
        break;
    case 4:
        if (a.rok != b.rok)
            return a.rok < b.rok;
        else if (a.miesiac != b.miesiac)
            return a.miesiac > b.miesiac;
        else
            return a.dzien > b.dzien;
        break;
    case 5:
        return a.plec > b.plec;
        break;
    default:
        return a.id > b.id;
        break;
    }
}

template<class T>
bool List<T>::smaller(const Tab1::Dane& a, const Tab1::Dane& b, const int choice) {
    switch (choice) {
        case 1:
            return a.id < b.id;
            break;
        case 2:
            return a.imie < b.imie;
            break;
        case 3:
            return a.nazwisko < b.nazwisko;
            break;
        case 4:
            if (a.rok != b.rok)
                return a.rok < b.rok;
            else if (a.miesiac != b.miesiac)
                return a.miesiac < b.miesiac;
            else
                return a.dzien < b.dzien;
            break;
        case 5:
            return a.plec < b.plec;
            break;
        default:
            return a.id < b.id;
            break;
    }
}

template<class T>
bool List<T>::greater(const Tab2::Wiezienie& a, const Tab2::Wiezienie& b, const int choice) {
    switch (choice) {
    case 1:
        return a.id > b.id;
        break;
    case 2:
        return a.przewinienie > b.przewinienie;
        break;
    case 3: {
        int months_a = a.dlugosc;
        if (a.jednostka == "lat" || a.jednostka == "lata" || a.jednostka == "rok")
            months_a *= 12;
        else
            months_a *= 1;

        int months_b = b.dlugosc;
        if (b.jednostka == "lat" || b.jednostka == "lata" || b.jednostka == "rok")
            months_b *= 12;
        else
            months_b *= 1;

        if (months_a != months_b)
            return months_a > months_b;
        break;
    }
    case 4:
        return a.cela > b.cela;
        break;
    default:
        return a.id > b.id;
        break;
    }
}

template<class T>
bool List<T>::smaller(const Tab2::Wiezienie& a, const Tab2::Wiezienie& b, const int choice) {
    switch (choice) {
    case 1:
        return a.id < b.id;
        break;
    case 2:
        return a.przewinienie < b.przewinienie;
        break;
    case 3: {
        int months_a = a.dlugosc;
        if (a.jednostka == "lat" || a.jednostka == "lata" || a.jednostka == "rok")
            months_a *= 12;
        else
            months_a *= 1;

        int months_b = b.dlugosc;
        if (b.jednostka == "lat" || b.jednostka == "lata" || b.jednostka == "rok")
            months_b *= 12;
        else
            months_b *= 1;

        if (months_a != months_b)
            return months_a < months_b;
        break;
    }
    case 4:
        return a.cela < b.cela;
        break;
    default:
        return a.id < b.id;
        break;
    }
}

template<typename T>
void List<T>::sort(const int sort) {
    shared_ptr<Node<T>> ptr;
    T min;
    int count = 0;
    if (sort == 1)
        while (count != size()) {
            ptr = head;
            min = ptr->data;
            for (int i = 0; i < size() - count; ++i) {
                if (smaller(ptr->data, min))
                    min = ptr->data;
                ptr = ptr->next;
            }
            ++count;
            push_back(min);
            pop(get_index(min));
        }
    else if (sort == 2)
        while (count != size()) {
            ptr = head;
            min = ptr->data;
            for (int i = 0; i < size() - count; ++i) {
                if (greater(ptr->data, min))
                    min = ptr->data;
                ptr = ptr->next;
            }
            ++count;
            push_back(min);
            pop(get_index(min));
        }
}

template<typename T>
void List<T>::sort(const int sort, const int choice) {
    shared_ptr<Node<T>> ptr;
    T min;
    int count = 0;
    if (sort == 1)
        while (count != size()) {
            ptr = head;
            min = ptr->data;
            for (int i = 0; i < size() - count; ++i) {
                if (smaller(ptr->data, min, choice))
                    min = ptr->data;
                ptr = ptr->next;
            }
            ++count;
            push_back(min);
            pop(get_index(min));
        }
    else if (sort == 2)
        while (count != size()) {
            ptr = head;
            min = ptr->data;
            for (int i = 0; i < size() - count; ++i) {
                if (greater(ptr->data, min, choice))
                    min = ptr->data;
                ptr = ptr->next;
            }
            ++count;
            push_back(min);
            pop(get_index(min));
        }
}

template<typename T>
int List<T>::element_count(const string& obj) {
    shared_ptr<Node<T>> ptr = head;
    int count = 0;
    while (ptr != NULL) {
        if (to_string(ptr->data) == obj)
            ++count;
        ptr = ptr->next;
    }
    return count;
}

template<typename T>
int List<T>::element_count1(const int element, const string& obj) {
    shared_ptr<Node<T>> ptr = head;
    int count = 0;
    while (ptr != NULL) {
        switch (element) {
        case 1:
            if (to_string(ptr->data.id) == obj)
                ++count;
            break;
        case 2:
            if (ptr->data.imie == obj)
                ++count;
            break;
        case 3:
            if (ptr->data.nazwisko == obj)
                ++count;
            break;
        case 4:
            if (to_string(ptr->data.dzien) == obj)
                ++count;
            break;
        case 5:
            if (to_string(ptr->data.miesiac) == obj)
                ++count;
            break;
        case 6:
            if (to_string(ptr->data.rok) == obj)
                ++count;
            break;
        case 7:
            if (ptr->data.plec == obj[0])
                ++count;
            break;
        default:
            return 0;
            break;
        }
        ptr = ptr->next;
    }
    return count;
}

template<typename T>
int List<T>::element_count2(const int element, const string& obj) {
    shared_ptr<Node<T>> ptr = head;
    int count = 0;
    while (ptr != NULL) {
        switch (element) {
        case 1:
            if (to_string(ptr->data.id) == obj)
                ++count;
            break;
        case 2:
            if (ptr->data.przewinienie == obj)
                ++count;
            break;
        case 3:
            if (to_string(ptr->data.dlugosc) == obj)
                ++count;
            break;
        case 4:
            if (ptr->data.jednostka == obj)
                ++count;
            break;
        case 5:
            if (ptr->data.cela == obj)
                ++count;
            break;
        default:
            return 0;
            break;
        }
        ptr = ptr->next;
    }
    return count;
}

template<typename T>
int List<T>::arrest_length(const int id) {
    shared_ptr<Node<T>> ptr = head;
    int sum = 0;
    while (ptr != NULL) {
        if (ptr->data.id == id) {
            int months = ptr->data.dlugosc;
            if (ptr->data.jednostka == "lat" || ptr->data.jednostka == "lata" || ptr->data.jednostka == "rok")
                months *= 12;
            else
                months *= 1;
            sum += months;
        }
        ptr = ptr->next;
    }
    return sum;
}

template<typename T>
double List<T>::arrest_average(const string& co) {
    shared_ptr<Node<T>> ptr = head;
    int sum = 0, count = 0, tmp = 0;
    double sr;
    try {
        tmp = stoi(co);
    }
    catch (const invalid_argument& exp) {

    }
    while (ptr != NULL) {
        if (ptr->data.przewinienie == co || co == "all" || ptr->data.id == tmp) {
            int months = ptr->data.dlugosc;
            if (ptr->data.jednostka == "lat" || ptr->data.jednostka == "lata" || ptr->data.jednostka == "rok")
                months *= 12;
            else
                months *= 1;
            sum += months;
            ++count;
        }
        ptr = ptr->next;
    }
    if (count == 0)
        return 0;
    sr = sum / count;
    return sr;
}

template<typename T>
List<T> List<T>::avarage_greater(const double length, const string& co) {
    List<T> result;
    int count = 0, months = 0;
    sort(1, 1);
    shared_ptr<Node<T>> ptr = head;
    while (ptr != NULL) {
        if (ptr->data.przewinienie == co || co == "all") {
            if (ptr->next != NULL && ptr->data.id == (ptr->next)->data.id && count == 0) {
                shared_ptr<Node<T>> ptr2 = ptr;
                int sum = 0;
                double sr;
                while (ptr2 != NULL) {
                    months = ptr2->data.dlugosc;
                    if (ptr2->data.jednostka == "lat" || ptr2->data.jednostka == "lata" || ptr2->data.jednostka == "rok")
                        months *= 12;
                    else
                        months *= 1;
                    sum += months;
                    ++count;

                    if (ptr2->next == NULL || ptr2->data.id != (ptr2->next)->data.id)
                        break;
                    ptr2 = ptr2->next;
                }
                sr = sum / count * 1.0;
                if (sr <= length) {
                    ptr = ptr2;
                    count = 0;
                }
                sum = 0;
            }
            else if (count == 0) {
                months = ptr->data.dlugosc;
                if (ptr->data.jednostka == "lat" || ptr->data.jednostka == "lata" || ptr->data.jednostka == "rok")
                    months *= 12;
                else
                    months *= 1;
                if (months > length)
                    result.push_back(ptr->data);
            }
            if (count > 0) {
                result.push_back(ptr->data);
                --count;
            }
        }
        ptr = ptr->next;
    }
    return result;
}

template<typename T>
List<T> List<T>::block_check(const char blok) {
    List<T> result;
    shared_ptr<Node<T>> ptr = head;
    while (ptr != NULL) {
        if (ptr->data.cela.back() == blok && result.element_count2(1, to_string(ptr->data.id)) == 0)
            result.push_back(ptr->data);
        ptr = ptr->next;
    }
    return result;
}

template<typename T>
List<T> List<T>::born_during(const int from_day, const int from_month, const int from_year, const int to_day, const int to_month, const int to_year) {
    List<T> result;
    shared_ptr<Node<T>> ptr = head;
    while (ptr != NULL) {
        if (ptr->data.rok > from_year && ptr->data.rok < to_year)
            result.push_back(ptr->data);
        else if (from_year == to_year && ptr->data.rok == from_year) {
            if (ptr->data.miesiac > from_month && ptr->data.miesiac < to_month)
                result.push_back(ptr->data);
            else if (from_month == to_month && ptr->data.miesiac == from_month) {
                if (ptr->data.dzien >= from_day && ptr->data.dzien <= to_day)
                    result.push_back(ptr->data);
            }
            else if (ptr->data.miesiac == from_month) {
                if (ptr->data.dzien >= from_day)
                    result.push_back(ptr->data);
            }
            else if (ptr->data.miesiac == to_month) {
                if (ptr->data.dzien <= to_day)
                    result.push_back(ptr->data);
            }
        }
        else if (ptr->data.rok == from_year) {
            if (ptr->data.miesiac > from_month)
                result.push_back(ptr->data);
            else if (ptr->data.miesiac == from_month)
                if (ptr->data.dzien >= from_day)
                    result.push_back(ptr->data);
        }
        else if (ptr->data.rok == to_year) {
            if (ptr->data.miesiac < to_month)
                result.push_back(ptr->data);
            else if (ptr->data.miesiac == to_month)
                if (ptr->data.dzien <= to_day)
                    result.push_back(ptr->data);
        }
        ptr = ptr->next;
    }
    return result;
}

template<typename T>
void List<T>::clear() {
    while (size() != 0) {
        pop_front();
    }
}

template<typename T>
int List<T>::size() {
    shared_ptr<Node<T>> ptr = head;
    int count = 0;
    while (ptr != NULL) {
        ++count;
        ptr = ptr->next;
    }
    return count;
}

template<typename T>
bool List<T>::is_empty() {
    if (head == NULL)
        return true;
    return false;
}

template<typename T>
void List<T>::serialization(const string& nazwa) {
    ofstream plik(nazwa, ios::binary);
    if (plik) {
        shared_ptr<Node<T>> ptr = head;
        while (ptr != NULL) {
            plik.write(reinterpret_cast<char*>(&ptr->data), sizeof(T));
            ptr = ptr->next;
        }
        plik.close();
    }
}

template<typename T>
void List<T>::deserialization(const string& nazwa) {
    ifstream plik(nazwa, ios::binary);
    if (plik) {
        while (plik) {
            T data;
            plik.read(reinterpret_cast<char*>(&data), sizeof(T));
            if (!plik.eof())
                push_back(data);
        }
        plik.close();
    }
}

template<typename T>
void List<T>::serialization_string(const string& nazwa) {
    ofstream plik(nazwa, ios::binary);
    if (plik) {
        shared_ptr<Node<T>> ptr = head;
        while (ptr != NULL) {
            int length = ptr->data.length();
            plik.write(reinterpret_cast<char*>(&length), sizeof(int));
            plik.write(ptr->data.c_str(), length);

            ptr = ptr->next;
        }
        plik.close();
    }
}

template<typename T>
void List<T>::deserialization_string(const string& nazwa) {
    ifstream plik(nazwa, ios::binary);
    if (plik) {
        while (plik) {
            int length;
            plik.read(reinterpret_cast<char*>(&length), sizeof(int));

            if (!plik.eof()) {
                char* tmp = new char[length];
                plik.read(tmp, length);
                T data(tmp, length);
                push_back(data);
                delete[] tmp;
            }
        }
        plik.close();
    }
}

template <typename T>
void List<T>::displayELement(const int index) {
    shared_ptr<Node<T>> ptr = head;
    if (ptr == NULL)
        cout << "List is empty! " << endl;
    else if (index >= 0 && index < size()) {
        cout << "Element: " << endl;
        int count = 0;
        while (count++ != index) {
            ptr = ptr->next;
        }
        if constexpr (is_same_v<T, Tab1::Dane>) {
            cout << ptr->data.id << " " << ptr->data.imie << " " << ptr->data.nazwisko << " "
                << ptr->data.dzien << " " << ptr->data.miesiac << " " << ptr->data.rok << " " << ptr->data.plec << endl;
        }
        else if constexpr (is_same_v<T, Tab2::Wiezienie>) {
            cout << ptr->data.id << " " << ptr->data.przewinienie << " " << ptr->data.dlugosc << " "
                << ptr->data.jednostka << " " << ptr->data.cela << endl;
        }
        else
            cout << ptr->data << " " << endl;
    }
}

template <typename T>
void List<T>::displayList() {
    shared_ptr<Node<T>> ptr = head;
    if (ptr == NULL)
        cout << "List is empty! " << endl;
    else {
        cout << "Lista zawiera: " << endl;
        while (ptr != NULL) {
            if constexpr (is_same_v<T, Tab1::Dane>) {
                cout << ptr->data.id << ", " << ptr->data.imie << ", " << ptr->data.nazwisko << ", "
                    << ptr->data.dzien << "." << ptr->data.miesiac << "." << ptr->data.rok << ", " << ptr->data.plec << endl;
            }
            else if constexpr (is_same_v<T, Tab2::Wiezienie>) {
                cout << ptr->data.id << ", " << ptr->data.przewinienie << ", " << ptr->data.dlugosc << ", "
                    << ptr->data.jednostka << ", " << ptr->data.cela << endl;
            }
            else
                cout << ptr->data << " " << endl;
            ptr = ptr->next;
        }
    }
}

template <typename T>
void List<T>::zapis(const string& nazwa) {
    ofstream plik(nazwa);
    if (plik) {
        shared_ptr<Node<T>> ptr = head;
        if (ptr == NULL)
            plik << endl << "List is empty! " << endl;
        else {
            plik << endl << "List contains: " << endl;
            while (ptr != NULL) {
                if constexpr (is_same_v<T, Tab1::Dane>) {
                    plik << ptr->data.id << ", " << ptr->data.imie << ", " << ptr->data.nazwisko << ", " << ptr->data.dzien << "." << ptr->data.miesiac << "." << ptr->data.rok << ", " << ptr->data.plec << endl;
                }
                else if constexpr (is_same_v<T, Tab2::Wiezienie>) {
                    plik << ptr->data.id << ", " << ptr->data.przewinienie << ", " << ptr->data.dlugosc << " " << ptr->data.jednostka << ", " << ptr->data.cela << endl;
                }
                else
                    plik << ptr->data << " " << endl;
                ptr = ptr->next;
            }
        }
        plik.close();
    }
    else
        cout << "Blad! Nie mozna otworzyc pliku! " << endl;
}

template <typename T>
void List<T>::zapis2(const string& nazwa) {
    ofstream plik(nazwa, ios::app);
    if (plik) {
        shared_ptr<Node<T>> ptr = head;
        if (ptr == NULL)
            plik << endl << "List is empty! " << endl;
        else {
            plik << endl << "List contains: " << endl;
            while (ptr != NULL) {
                if constexpr (is_same_v<T, Tab1::Dane>) {
                    plik << ptr->data.id << ", " << ptr->data.imie << ", " << ptr->data.nazwisko << ", " << ptr->data.dzien << "." << ptr->data.miesiac << "." << ptr->data.rok << ", " << ptr->data.plec << endl;
                }
                else if constexpr (is_same_v<T, Tab2::Wiezienie>) {
                    plik << ptr->data.id << ", " << ptr->data.przewinienie << ", " << ptr->data.dlugosc << " " << ptr->data.jednostka << ", " << ptr->data.cela << endl;
                }
                else
                    plik << ptr->data << " " << endl;
                ptr = ptr->next;
            }
        }
        plik.close();
    }
    else
        cout << "Blad! Nie mozna otworzyc pliku! " << endl;
}