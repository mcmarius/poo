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

<!--
Grupare muzicală/artistică
Orchestră
Trupă
Artist solo
Album
Piesă
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
