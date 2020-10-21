# Laboratorul 2

### ⚠ Puneți cât mai multe întrebări! Nu există întrebări greșite.
#### Semnalați orice fel de greșeli găsiți!

# Cuprins
## [Programe discutate](#programe-discutate-1)
## [Exerciții](#exerciții-1)
## [Întrebări, erori și orice nu a fost acoperit deja](#întrebări-erori-diverse)
## [Resurse recomandate](#resurse-recomandate-1)

## Programe discutate

### [Tema 1](#tema-1-1)
### [Constructori de inițializare](#constructori-de-inițializare-1)
### [Destructori](#destructori-1)
### [Constructori de copiere](#constructori-de-copiere-1)
### [`operator=` și regula celor trei](#operator-și-regula-celor-trei-1)

### Tema 1

Scopul acestei teme este familiarizarea cu limbajul C++ și cu unele concepte OOP de bază. **Nu vă complicați!**

Cerințe comune:
- minim 2-3 clase folosind compunere; puteți adăuga și clase pentru moștenire, dar vor fi în plus față de acelea 2-3
- constructori (expliciți) de inițializare și de copiere
- destructor
- `operator=`
- `operator<<` (pentru afișare)
- funcții membru publice
- atribute și alte funcții vor fi obligatoriu `private` (și, evident, fără variabile globale; discutăm excepțiile)
- cât mai multe `const`
- codul trebuie să fie pe un repo la care să am acces (preferabil repo de `git`)
- GitHub Actions sau ceva similar (pentru Continuous Integration) (**exemplu [aici](https://github.com/mcmarius/demo-poo/blob/mcmarius-patch-1/.github/workflows/ccpp.yml)**)
  - fără warnings: `-Wall -Wextra -pedantic -Weffc++`, eventual cu `-Werror` și un linter (`cppcheck`)
  - fără memory leaks: vom folosi `valgrind` sau `-fsanitize`
  - testarea *tuturor* funcțiilor publice în `main`
    - vom folosi `gcovr` pentru a ne da seama ce părți din program (nu) se execută
    - vom folosi instrucțiuni `assert`/`static_assert` pentru testarea în sine
    - dacă o funcție publică nu este folosită, probabil nu avem nevoie de acea funcție; o ștergem sau o facem `private`
  - `.gitignore` ca să fie mai ușor de văzut diferențele
- ideal, implementarea unei funcționalități mai dificile

#### Teme propuse
- Grupare muzicală/artistică
- Orchestră
- Trupă
- Artist solo
- Album
- Piesă
  - Single
  - Cover
  - Colaborare
  - Remaster
  - Colind
----------
- Instrument muzical
  - de suflat
    - din lemn
    - de alamă
  - de percuție
  - cu coarde
    - lovite
    - ciupite

----------
- Organizator
- Participant
- Invitație
- Eveniment

----------
- Dispozitiv inteligent
- Smartphone
- Smartwatch
- SmartTV
- Sisteme de operare: Android, iOS

----------
- Drum: rutier, forestier, potecă
- Turist: amator, expert
- Hartă - mai multe drumuri și obiective
- Obiectiv (turistic)

----------
- Sportiv
- Probă
- Concurs
- Premii
- Palmares
- Clasament

----------
- Muzeu
- Sală
- Lucrare: desen, tablou, sculptură
- Expoziție: permanentă, temporară

----------
- Furnizor
- Mobilă
- Dulap
- Bibliotecă
- Birou
- Vitrină
- Masă

----------
- Dispozitiv de iluminat
- Bec clasic
- Bec cu LED
- Neon
- Lampă cu gaz
- Lumânare
- Făclie

----------
- Editură
- Publicație
- Ziar
- Revistă
- Carte
- Dicționar
- Manual

----------
- Reminder
- To-do list
- Listă de cumpărături
- Alarmă
- Zi de naștere/onomastică
- Factură

----------
- Mijloc de transport/Vehicul
- Bicicletă
- Trotinetă
- Mașină
- Dubă
- Autobuz
- Metrou
- Tramvai
- Troleibuz
- Taxi
- Camion

----------
- Locuință
- Apartament
- Casă
- Castel
- Cort
- Casă în copac
- Rulotă

----------
- Ceas
- Ceas deșteptător
- Ceas cu pendul
- Ceas cu cuc
- Ceas digital

----------
- Reclamă
  - Produs
- Anunț la ziar
- Plasare de produs
  - Colaborator/Influensăr
- Rețele de socializare
- Recomandare personală

----------
- Verificare: listă de probe
- Probă
- Probă scrisă
- Probă orală
- Test psihologic
- Test fizic
- Test tehnic

----------
- Suprafață
- Hârtie
- Carton
- Tablă de sticlă
- Tablă de plastic
- Instrument de scris
- Creion
- Stilou
- Pix simplu
- Pix cu gel
- Marker
- Cretă

----------
- Aplicație de fitness
- Exercitiu
- Mâini
- Picioare
- Mixt

----------
- Cofetărie
- Produs/Desert
- Tort
- Prăjitură
- Produs de patiserie: chec, cozonac, fursec, altele
- Comandă
- Personal

----------
- Simulator de vreme
- Statistică
- Fenomen meteorologic
- Ploaie
- Ninsoare
- Caniculă

----------
- Model de plată
- Subscripție/Abonament
  - nominal
  - pentru un grup de persoane
  - posibilitate de demo: timp sau număr de utilizări
- Donație (pay what you want)
- Achiziție
  - individuală
  - bundle

----------
- Participant
  - admin
  - membru
  - spectator/vizitator
- Tichet
- Propunere/Feature
- Defect/Bug
- Întrebare
- Dezbatere/Discuție

----------
Alte variante: școală/liceu/facultate (orar, examene, rechizite, echipamente), magazin (aprovizionare, livrări, service), companie (angajați, recrutări), jocuri, structuri de date (stivă -> vector/listă, coadă -> vector/listă, listă simplu/dublu înlănțuită eventual circulară), software: seturi de date, misc (cuaternioni)


### Constructori de inițializare

```c++
#include <iostream>

class mancare {
protected:
    std::string nume;
public:
    mancare(const std::string& nume) : nume{nume} {
        std::cout << "In constructorul din clasa mancare";
    }
};

struct felie {
    enum { ALBA, INTEGRALA } tip;

    felie() {
        std::cout << "In constructorul din structura felie";
    }
};

struct ingredient {
    std::string nume;

    ingredient(const std::string& nume) : nume{nume} {
        std::cout << "In constructorul din structura ingredient";
    }
};

class sandwich : public mancare {
    felie f[2];
    std::vector<ingredient> ingrediente;
public:
    sandwich(const std::string& nume) : mancare{nume} {
        std::cout << "In constructorul din clasa sandwich";
    }
};

int main() {
    sandwich s("simplu");
    {
        sandwich m = sandwich("mare");
        sandwich g = "gol";
    }
}
```

### Destructori

Sunt generați de compilator dacă nu îi definim explicit.

Sunt apelați în mod automat de compilator atunci când obiectul își încetează existența:
- la ieșirea din "scope"-ul în care a fost creat obiectul, adică atunci când execuția ajunge la `}` corespunzătoare acoladei de început a acelui "scope"
- la folosirea operatorilor `delete` și `delete[]`
- la sfârșitul programului pentru obiecte alocate static sau global

Se poate apela explicit destructorul, dar nu vrem asta! De ce? Deoarece se va apela de două ori!

Dacă totuși insistați, există (cel puțin) [un caz particular](https://isocpp.org/wiki/faq/dtors#placement-new) în care destructorul chiar trebuie apelat în mod explicit.

### Constructori de copiere

Sunt generați de compilator dacă nu îi definim explicit.

Sunt apelați în mod automat de compilator atunci când este nevoie de copiere. Când este nevoie?
- la apelarea explicită a acestui constructor (evident)
- la transmiterea prin valoare a parametrilor funcțiilor
- la întoarcerea unui obiect prin valoare dintr-o funcție

### `operator=` și regula celor trei

Orice clasă are definit `operator=` de compilator dacă nu îl definim explicit.

Acest operator, numit operator de atribuire, se apelează atunci când facem atribuiri. Excepție:
```c++
class cls {};
cls ob1, ob2 = ob1; // se apeleaza cc, nu op=
cls ob3;
ob3 = ob1; // se apeleaza op=
```

De ce există distincția între constructorul de copiere și operatorul de atribuire?
- în primul caz, obiectul nu există
- în al doilea caz, obiectul există și putem avea resurse alocate pe care le-am putea refolosi

**Ce înseamnă "regula celor trei"?**

Dacă a fost nevoie să definim în mod *explicit* constructorul de copiere, operatorul de atribuire *sau* destructorul, înseamnă că **trebuie** să le definim pe toate trei.

**De discutat mai târziu**
- copy-and-swap
- excepții (chiar sunt necesare?)
- static

## Exerciții
[Înapoi la cuprins](#cuprins)
- constructori
- destructori
- constructori de copiere
- conversii și constructori expliciți (?)

## Întrebări, erori, diverse
[Înapoi la cuprins](#cuprins)

* 🚧

## Resurse recomandate
- [cppreference.com](https://en.cppreference.com/w/cpp)
- [StackOverflow](https://stackoverflow.com/questions/tagged/cpp?tab=Votes)
- [ISO C++ FAQ](https://isocpp.org/faq/)
- [Diverse standarde (draft) ale limbajului](https://en.cppreference.com/w/cpp/links) sau ca [HTML (neoficial)](https://github.com/timsong-cpp/cppwp) (sau [aici](https://stackoverflow.com/questions/81656/where-do-i-find-the-current-c-or-c-standard-documents#4653479))

### Resurse de evitat
- GeeksforGeeks: util pentru algoritmică (unele voci pe internet contestă și asta), dar la partea de programare trebuie **evitat**
  - ca exemplu, încurajează utilizarea headerelor nestandard (`<bits/stdc++.h>`)
  - aproape oricine poate scrie articole, nu este neapărat verificată corectitudinea soluțiilor
