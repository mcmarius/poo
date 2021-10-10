## Exerciții

### Laboratorul 1

#### 1. Listă simplu înlănțuită

Există mai multe abordări de implementare, de exemplu top-down (de la general la particular sau de la mare la mic) și bottom-up (invers). Probabil sunteți mai obișnuiți cu abordarea bottom-up, adică de exemplu să definiți structuri și funcții și abia apoi să apelați codul din `main`.

Întrucât unul dintre scopurile OOP este să permită o dezvoltare mai ușoară/rapidă în cazul proiectelor mari, vom încerca să folosim o abordare de tip top-down. Prin urmare, începem cu `main` și descriem ce funcționalități dorim să aibă lista noastră. Pentru început, vrem operații de bază: adăugare/eliminare/modificare elemente și afișarea listei.

```c++
#include "lista_simpla.h"
#include <iostream>

int main() {
    lista_simpla lista;
    lista.afisare();
    lista.adauga(1);
    lista.afisare();
    lista.adauga(3);
    lista.afisare();
    lista.adauga(2, false);
    lista.afisare();
    lista.adauga(2);
    lista.adauga_val_poz(10, 2); // indexare de la 1
    lista.afisare();
    // std::cout << lista;
    lista.elimina_poz(2);
    lista.afisare();
    // std::cout << lista;
    lista.elimina_val(2);
    lista.afisare();
    // std::cout << lista;
    lista.modifica_val_poz(1, 14);
    lista.afisare();
    // std::cout << lista;
    return 0;
}
```

Dacă încercăm să compilăm, compilatorul/editorul ne va spune care sunt următorii pași:
- crearea fișierului `lista_simpla.h`
- crearea clasei `lista_simpla`
- declararea și definirea funcțiilor membre

În fișierul `lista_simpla.h` vom scrie următoarele (`#ifndef`-ul ar trebui generat de editor):

```c++
#ifndef LISTA_SIMPLA_H
#define LISTA_SIMPLA_H

class lista_simpla {
public:
    void adauga(int val, bool inceput=true) {}
    void adauga_val_poz(int val, int poz) {}
    void afisare() {}
    void elimina_poz(int poz) {}
    void elimina_val(int val) {}
    void modifica_val_poz(int val, int poz) {}
};

#endif // LISTA_SIMPLA_H
```

Dacă explicațiile de [aici](https://github.com/mcmarius/prog-calc/blob/master/laborator-4/README.md#organizarea-codului-%C3%AEn-fi%C8%99iere-separate-1) despre include guards/`#pragma once` nu sunt clare/suficiente, ping me.

În acest moment, codul ar trebui să compileze. Din nou, ping me dacă ce descriu aici nu reflectă realitatea.

Cu toate că avem un cod care compilează, acesta nu face nimic. Pentru implementarea listei, avem nevoie și de o clasă `nod`. Întrucât nu vom putea folosi în mod independent clasa `nod`, o vom adăuga în interiorul clasei `lista_simpla`, în partea `private`:

```c++

    class nod {
    public:
        nod(int val) : val(val), urm(nullptr) {}
        int get_val() { return val; }
        nod* get_urm() { return urm; }
        void set_val(int val) { this->val = val; }
        void set_urm(nod* urm) { this->urm = urm; }

    private:
        int val;
        nod *urm;
    };
```

Nu putem folosi în mod independent clasa `nod` deoarece nu putem garanta că nu vor fi erori de memorie, chiar dacă ne definim constructor de copiere (cc), destructor și operator= (op=).

În mod normal, pentru astfel de clase ajutătoare care nu au prea mult cod, ar fi suficient să folosim un `struct` și să nu mai avem getteri și setteri. Totuși, vom folosi aceste funcții pentru a ne obișnui cu conceptele de OOP.

Pasul următor este să implementăm funcțiile din listă:

```c++
// în interiorul clasei lista_simpla
public:
    void adauga(int val, bool inceput=true) {
        nod* nod_nou = new nod{val};
        if(start == nullptr) {
            start = nod_nou;
            return;
        }
        if(inceput) {
            nod_nou->set_urm(start);
            start = nod_nou;
        }
        else { // adaugam la sfarsitul listei
            nod *urm = start->get_urm();
            while(urm != nullptr && urm->get_urm() != nullptr) {
                urm = urm->get_urm();
            }
            if(urm)
                urm->set_urm(nod_nou);
            else
                start->set_urm(nod_nou);
        }
    }

private:
    // dupa ce am definit clasa nod
    nod *start = nullptr;
```

Observație: dacă nu inițializăm `start` cu `nullptr`, atunci pointerul este neinițializat și **nu** are valoarea `nullptr`, ci arată către o zonă de memorie la întâmplare.

Spre deosebire de `malloc`/`free` pe care le foloseam în C, `new`/`delete` apelează constructorul/destructorul. O altă alternativă sunt smart pointers, dar vom vedea mai târziu.

Am folosit `new`, deci trebuie să folosim undeva și `delete`:

```c++
    ~lista_simpla() {
        while(start != nullptr) {
            nod* tmp = start;
            start = start->get_urm();
            delete tmp;
        }
    }
```

Dacă totul compilează până acum, să adăugăm și funcția de afișare:

```c++
// în interiorul clasei lista_simpla
    void afisare() {
        if(start == nullptr) {
            std::cout << "()\n";
            return;
        }
        nod* tmp = start;
        while(tmp->get_urm()) {
            std::cout << "(" << tmp->get_val() << ") -> ";
            tmp = tmp->get_urm();
        }
        std::cout << "(" << tmp->get_val() << ")\n";
    }
```

Înainte de a trece mai departe, ar fi bine să testăm în `main` dacă clasa `lista_simpla` chiar funcționează corect. La început de tot, vom apela funcția `verifica_lista_simpla`:

```c++
void verifica_lista_simpla() {
    lista_simpla l1, l2;

    std::cout << "l1: ";
    l1.afisare();
    std::cout << "l2: ";
    l2.afisare();
    l1.adauga(1);
    l2.adauga(2);
    std::cout << "l1: ";
    l1.afisare();
    std::cout << "l2: ";
    l2.afisare();
    {
        lista_simpla l3{l1};
        std::cout << "l1: ";
        l1.afisare();
        std::cout << "l3: ";
        l3.afisare();
        l3.adauga(3, false);
        std::cout << "l1: ";
        l1.afisare();
        std::cout << "l3: ";
        l3.afisare();
    }
    std::cout << "l1: ";
    l1.afisare();
    {
        lista_simpla l4;
        l4.adauga(4);
        std::cout << "l2: ";
        l2.afisare();
        std::cout << "l4: ";
        l4.afisare();
        l2 = l4;
        std::cout << "l2: ";
        l2.afisare();
        std::cout << "l4: ";
        l4.afisare();
        l4.adauga(5, false);
        std::cout << "l2: ";
        l2.afisare();
        std::cout << "l4: ";
        l4.afisare();
    }    
    std::cout << "l2: ";
    l2.afisare();
}
```

Constructorul de copiere funcționează corect? Dar `operator=`?

În astfel de situații, când ne ocupăm _noi_ de administrarea memoriei, este necesar să suprascriem funcțiile pe care ni le generează compilatorul.

Aici, noi am suprascris destructorul generat de compilator pentru a nu avea memory leaks. ["Regula celor trei"](https://en.cppreference.com/w/cpp/language/rule_of_three) ne spune că dacă avem nevoie de comportament special pentru cel puțin unul dintre cc/destructor/op=, cel mai probabil avem de făcut ceva special pentru toate cele trei și trebuie să le scriem _noi_ pe toate.

Dacă suprascriem constructorul de copiere (cc) și compilăm fără să avem `operator=` (op=), primim warning, deoarece este cel mai probabil o greșeală. În cazul în care definim doar destructorul, nu primim warning deoarece e mai greu pentru compilator să își dea seama dacă e o greșeală.

Ca regulă generală, avem nevoie să ne definim cc/op=/destructor atunci când lucrăm cu pointeri din C.

În cazul constructorului de copiere, nu avem un obiect deja existent și lucrurile sunt mai simple:

```c++
// în clasa lista_simpla

    lista_simpla(const lista_simpla& copie) {
        if(copie.start != nullptr) {
            nod *tmp_copie = copie.start;
            start = new nod{tmp_copie->get_val()};
            nod* tmp = start;
            while(tmp_copie->get_urm()) {
                nod* nod_nou = new nod{tmp_copie->get_urm()->get_val()};
                tmp->set_urm(nod_nou);
                tmp = tmp->get_urm();
            }
        }
    }
```

Implicit, dacă nu ne definim constructori, compilatorul generează automat constructor fără parametri. Acum că am definit constructorul de copiere, nu se mai generează constructorul fără parametri, așa că trebuie să adăugăm și

```c++
    lista_simpla() = default;
```

Iar acum la `l1` și `l3` nu ar mai trebui să fie probleme.

La op=, lucrurile sunt un pic mai complicate, deoarece obiectul pe care îl suprascriem este deja creat și există cazul particular `x = x;`:

```c++
// în clasa lista_simpla

    lista_simpla& operator=(const lista_simpla& copie) {
        if(this != &copie) {
            nod *old_start = start;
            if(copie.start == nullptr) {
                start = nullptr;
            }
            else {
                nod *tmp_copie = copie.start;
                start = new nod{tmp_copie->get_val()};
                nod* tmp = start;
                while(tmp_copie->get_urm()) {
                    nod* nod_nou = new nod{tmp_copie->get_urm()->get_val()};
                    tmp->set_urm(nod_nou);
                    tmp = tmp->get_urm();
                }
            }
            // daca nu stergem datele anterioare, avem memory leak
            // daca una dintre alocarile de mai sus nu a reusit, putem restaura datele vechi:
            //     acesta e motivul pentru care nu am inceput prin a sterge datele vechi
            // altfel, daca am copiat datele cu succes, stergem lista anterioara din obiectul curent
            while(old_start != nullptr) {
                nod* tmp = old_start;
                old_start = old_start->get_urm();
                delete tmp;
            }
        }
        return *this;
    }
```

Observăm totuși că în op= repetăm cod din cc și destructor. Dacă avem de făcut anumite optimizări (de exemplu să nu dezalocăm lista, ci doar să marcăm nodurile ca fiind nefolosite), atunci nu prea avem de ales și codul din op= va fi mai complicat.

Altfel, dacă oricum trebuie să "resetăm" obiectul, putem să ne folosim de "copy-and-swap":

```c++

// în clasa lista_simpla

    lista_simpla& operator=(lista_simpla copie) {
        // la transmiterea prin valoare se apeleaza constructorul de copiere
        swap(*this, copie);

        return *this;
    } // la iesirea din functie se apeleaza destructorul pentru obiectul temporar
```

Totuși, trebuie să ne definim funcția `swap`:

```c++
// în clasa lista_simpla, tot în partea publică
    friend void swap(lista_simpla& l1, lista_simpla& l2) {
        using std::swap;
        swap(l1.start, l2.start);
    }
```

Și așa am scris mult mai puțin cod și nici nu ne-am repetat. Totuși, când **nu** e bine să folosim copy-and-swap?

La modul general, atunci când vrem să refolosim resurse sau când operația de construire a unui nou obiect este costisitoare.

Exemple de resurse: memorie, fișiere deja deschise, conexiuni la servere/baze de date.

Exemple de operații costisitoare: calibrări de hardware, diverse calcule, caching.

Pentru a putea testa codul _în mod automat_, vom adăuga `operator<<`. Acesta va fi ca o funcție similară cu funcția de afișare, doar că ceva mai generală. Vom vedea în curând de ce vrem asta.

```c++
// în clasa lista_simpla

    friend std::ostream& operator<<(std::ostream& out, const lista_simpla& lista) {
        if(lista.start == nullptr) {
            out << "()\n";
            return out;
        }
        nod* tmp = lista.start;
        while(tmp->get_urm()) {
            out << "(" << tmp->get_val() << ") -> ";
            tmp = tmp->get_urm();
        }
        out << "(" << tmp->get_val() << ")\n";
        return out;
    }
```

Dacă nu dorim să repetăm codul, funcția `afisare` va deveni `std::cout << *this;`: `std::cout` este un obiect de tip `std::ostream`.

Ca să înțelegem de ce e mai general `operator<<` față de funcția de afișare de mai devreme, vom redirecționa textul din `operator<<` al clasei `lista_simpla` către un șir de caractere (mai corect spus string sub formă de stream), nu către `std::cout`. Pentru `std::ostringstream` vom include header-ul `<sstream>`, iar undeva în `main` adăugăm:

```c++
    std::ostringstream output;
    output << "start: ";
    output << lista;
    output << "gata\n";
    std::cout << output.str();
```

În acest mod, putem să scriem teste automate pentru toate funcțiile din clasa noastră. De ce vrem teste automate? Dacă e nevoie să facem modificări la implementare, nu este nevoie să mai verificăm manual dacă am stricat ceva prin restul codului. De asemenea, pentru restul funcțiilor, voi adăuga doar testele, iar voi puteți să vă verificați mai ușor dacă ați implementat lucrurile corect.

Observație: testele nu ne rezolvă în mod magic toate problemele. Putem avea bug-uri sau omisiuni și în cazul testelor (de exemplu, să uităm cazuri particulare sau să nu testăm ce trebuie).

Pentru biblioteca pe care aș vrea să o folosim, [μt](https://github.com/boost-ext/ut), este nevoie de un compilator relativ nou care să implementeze câteva features de C++20 (de exemplu gcc >= 9). Din nefericire, CodeBlocks vine cu gcc 8 :disappointed: . Dacă nu puteți să vă instalați un compilator mai nou, există și varianta cu GitHub Actions (sau alt serviciu de CI). Ping me pentru detalii.

Pentru teste, vom face un nou fișier cu un alt `main` (în `CMakeLists.txt` se va face un nou executabil).

Fișierul va avea următorul conținut:

```c++
#include <sstream>

#include <boost/ut.hpp>

#include "lista_simpla.h"

namespace ut = boost::ut;

ut::suite t_lista_simpla = [] {
    using namespace ut;
    using namespace std::string_literals;

    "lista goala"_test = [] {
        std::ostringstream output;
        lista_simpla lista;
        output << lista;
        expect("()\n"s == output.str());
    };

    "adauga"_test = [] {
        lista_simpla lista;
        std::ostringstream output;
        lista.adauga(2);
        output << lista;
        expect("(2)\n"s == output.str());

        lista_simpla l2;
        l2.adauga(2, false);
        output.str(""s);
        output.clear();
        output << l2;
        expect("(2)\n"s == output.str());

        output.str(""s);
        output.clear();
        lista.adauga(3);
        output << lista;
        expect("(3) -> (2)\n"s == output.str());

        output.str(""s);
        output.clear();
        lista.adauga(3, false);
        output << lista;
        expect("(3) -> (2) -> (3)\n"s == output.str());
    };

    "constructor de copiere"_test = [] {
        lista_simpla l1;
        l1.adauga(1);
        lista_simpla l2{l1};
        l1.adauga(3);
        l2.adauga(2);
        std::ostringstream output1;
        std::ostringstream output2;
        output1 << l1;
        output2 << l2;
        expect("(3) -> (1)\n"s == output1.str());
        expect("(2) -> (1)\n"s == output2.str());
    };

    "operator="_test = [] {
        lista_simpla l1;
        l1.adauga(1);
        lista_simpla l2;
        l2 = l1;
        l1.adauga(3);
        l2.adauga(2);
        std::ostringstream output1;
        std::ostringstream output2;
        output1 << l1;
        output2 << l2;
        expect("(3) -> (1)\n"s == output1.str());
        expect("(2) -> (1)\n"s == output2.str());
    };
};

int main() {}
```

În folderul `laborator-1` aveți adăugate teste și pentru funcțiile de adăugare/eliminare/modificare pe care nu le-am implementat. Implementați voi aceste funcții și verificați să treacă toate testele 😄 trebuie să scoateți acele `skip / ` din fața testelor pentru că altfel acele teste nu se execută.

-----

Exerciții liste simplu înlănțuite:
- adăugați mesaje de afișare specifice în constructori, op= și destructori; se creează/distrug câte obiecte v-ați aștepta? (puteți comenta din codul din `main` dacă vi se par prea multe)
- adăugați la nod un constructor care să seteze `urm`; folosiți apoi parametri impliciți pentru a avea un singur constructor
- adăugați la listă un constructor care primește un întreg ca parametru
- adăugați la listă un constructor care primește un `std::vector<int>` de întregi ca parametru (trebuie `#include <vector>`) și adaugă toate elementele din vector în listă
  - iterați prin vector în două moduri: `for(auto elem : vector)` și cu `for` simplu, folosind `.size()` pentru a afla numărul de elemente din vector
- implementați operația de concatenare a două liste

#### 2. Listă dublu înlănțuită

#### 3. Mulțime ordonată

Exerciții:
- folosind un vector
- folosind o listă simplu/dublu înlănțuită
