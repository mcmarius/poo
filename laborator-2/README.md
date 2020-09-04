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

### Tema 1

Scopul acestei teme este familiarizarea cu limbajul C++ și cu unele concepte OOP de bază.

Cerințe comune:
- constructori (expliciți) de inițializare și de copiere
- destructor
- `operator=`
- funcții membru publice
- atribute și alte funcții vor fi obligatoriu `private`
- GitHub Actions sau ceva similar (pentru Continuous Integration)
  - fără warnings: `-Wall -Wextra -pedantic -Weffc++`, eventual cu `-Werror` și un linter (`cppcheck`)
  - fără memory leaks: vom folosi `valgrind` sau `-fsanitize`
  - testarea *tuturor* funcțiilor publice în `main`: vom folosi `gcovr`
- ideal, implementarea unei funcționalități mai dificile

<!--
Grupare muzicală/artistică
Orchestră
Trupă
Artist solo
Album
Piesă
----------
Organizator
Participant
Invitație
Eveniment
----------
Dispozitiv inteligent
Smartphone
Smartwatch
SmartTV
Sisteme de operare: Android, iOS
----------
Drum: rutier, forestier, potecă
Turist: amator, expert
Hartă - mai multe drumuri și obiective
Obiectiv (turistic)
----------
Sportiv
Probă
Concurs
Premii
Palmares
Clasament
----------
Muzeu
Sală
Lucrare: desen, tablou, sculptură
Expoziție: permanentă, temporară
----------
Furnizor
Mobilă
Dulap
Bibliotecă
Birou
Vitrină
Masă
----------
Dispozitiv de iluminat
Bec clasic
Bec cu LED
Neon
Lampă cu gaz
Lumânare
Făclie
----------
Editură
Publicație
Ziar
Revistă
Carte
Dicționar
Manual
----------
Alte variante: școală/liceu/facultate (orar, examene, rechizite, echipamente), magazin (aprovizionare, livrări, service), companie (angajați, recrutări), jocuri, structuri de date (stivă -> vector/listă, coadă -> vector/listă, listă simplu/dublu înlănțuită eventual circulară), software: seturi de date, misc (cuaternioni)
-->

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

Sunt apelați în mod automat de către compilator atunci când obiectul își încetează existența:
- la ieșirea din "scope"-ul în care a fost creat obiectul, adică atunci când execuția ajunge la `}` corespunzătoare acoladei de început a acelui "scope"
- la folosirea operatorilor `delete` și `delete[]`
- la sfârșitul programului pentru obiecte alocate static sau global

Se poate apela explicit destructorul, dar nu vrem asta! De ce? Deoarece se va apela de două ori!

### Constructori de copiere

## Exerciții
[Înapoi la cuprins](#cuprins)



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
