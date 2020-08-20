# Laboratorul 1

### ⚠ Puneți cât mai multe întrebări! Nu există întrebări greșite.
#### Semnalați orice fel de greșeli găsiți!

# Cuprins
## [Configurarea mediului de lucru](#configurarea-mediului-de-lucru-1)
## [Programe introductive](#programe-introductive-1)
## [Exerciții](#exerciții-1)
## [Întrebări, erori și orice nu a fost acoperit deja](#întrebări-erori-diverse)
## [Resurse recomandate](#resurse-recomandate-1)

## Configurarea mediului de lucru

Vom folosi următoarele opțiuni de compilator: `-Wall -Wextra -pedantic -Weffc++` și, eventual, `-std=c++11` (sau alte versiuni). Ca versiuni de compilator, sunt de preferat acelea mai noi. Dacă folosiți MinGW, optați pentru varianta pe 64 de biți.

## Programe introductive

### [Cel mai simplu program](#cel-mai-simplu-program-1)
### ["Hello, world!"](#hello-world-1)

### Cel mai simplu program

Cel mai simplu program nu este cel cu "Hello World", ci acesta:
```c++
int main() {}
```
De ce? Pentru că, implicit, dacă se ajunge la sfârșitul funcției `main`, se returnează automat zero (detalii [aici](https://stackoverflow.com/a/204483)). Această regulă este valabilă **doar** pentru funcția `main`. Pentru toate celelalte funcții, este **obligatoriu** să specificăm valoarea de retur pe toate ramurile. Și este bine să punem `return 0;` și în `main`, mai ales dacă avem ramuri pe care returnăm alte valori (pentru a semnala un eșec).

Ce putem învăța din acest exemplu? Două lucruri: tipuri de date și funcții.

#### Tipuri de date

În limbajul C++, putem clasifica [tipurile de date](https://en.cppreference.com/w/cpp/language/type) în două mari categorii: simple și compuse.

#### Funcții



### "Hello, world!"

```c++
#include <iostream>

int main() {
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
```

De ce nu am folosit `using namespace std;`? Pentru că acest namespace conține *extrem de multe* funcții cu care am putea intra în conflict de nume. Dacă alegeți să folosiți această instrucțiune, trebuie să fiți conștienți de consecințele pe care le are. Scopul acestor namespace-uri tocmai acesta ar fi, să prefixăm numele funcțiilor cu numele namespace-ului pentru a evita complet coliziunile de nume. Mai multe detalii puteți citi [aici](https://isocpp.org/wiki/faq/coding-standards#using-namespace-std) și [aici](https://stackoverflow.com/q/1452721/).

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
  - faptul că nu (mai) găsim draft-uri disponibile pentru standardele C++98/C++03 ar trebui să ne transmită ceva 😉
  - mai ales în contextul în care toate compilatoarele cunoscute au implementat C++11
  - le-am adăugat mai mult ca să știți că există, nu e nevoie să vă uitați peste ele

### Resurse de evitat
- cărțile lui Herbert Schildt (de ce? [pentru că](https://www.seebs.net/c/c_tcn4e.html) și [pentru că](http://www.lysator.liu.se/c/schildt.html) și... [pentru că](https://web.archive.org/web/20000816131043/http://www.qnx.com/~glen/deadbeef/2764.html))
- cplusplus.com (deoarece nu este actualizat sau are informații incomplete)
