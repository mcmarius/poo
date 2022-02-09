# Laboratorul 1

### ⚠ Puneți cât mai multe întrebări! Nu există întrebări greșite.
#### Semnalați orice fel de greșeli găsiți!

## Programe introductive

### Cel mai simplu program

Cel mai simplu program nu este cel cu "Hello World", ci acesta:
```c++
int main() {}
```
De ce? Pentru că, implicit, dacă se ajunge la sfârșitul funcției `main`, se returnează automat zero
(detalii [aici](https://stackoverflow.com/a/204483)). Această regulă este valabilă **doar** pentru
funcția `main`. Pentru toate celelalte funcții, este **obligatoriu** să specificăm valoarea de retur
pe toate ramurile. Și este bine să punem `return 0;` și în `main`, mai ales dacă avem ramuri pe care
returnăm alte valori (pentru a semnala un eșec).

Ce putem învăța din acest exemplu? Două lucruri: tipuri de date și funcții.

**Tipuri de date**

În limbajul C++, putem clasifica [tipurile de date](https://en.cppreference.com/w/cpp/language/type) în două mari categorii: simple și compuse.

Prin tipuri de date simple înțelegem `int`, `double`, `char`, `void`, `bool` și altele asemenea, cu `short`/`long`/`unsigned` unde e cazul.

Prin tipuri de date compuse înțelegem vectori, pointeri, referințe, enumerări, uniuni, structuri, clase, funcții. Acestea două din urmă sunt folosite cu ajutorul șabloanelor pentru a scrie cod cât mai generic.

[//]: # (Astfel, putem răspunde la întrebarea pe care &#40;nu&#41; v-ați pus-o deja:)

[//]: # (**De ce învățăm la OOP C++ și nu altceva &#40;de exemplu Java&#41;?**)

[//]: # ()
[//]: # (Pentru că este mai simplu să treci de la ceva complicat la ceva simplu, iar limbajul C++ este mai general în ceea ce privește conceptele de OOP &#40;cel puțin cele predate în facultate&#41;.)

[//]: # ()
[//]: # (Pe de altă parte, dacă întâi înveți ceva simplu, poate fi dificil să scapi de anumite preconcepții atunci când treci de la acel ceva simplu la ceva complex &#40;de exemplu o trecere de la Java la C++&#41;.)

[//]: # ()
[//]: # (~Pentru că programa nu e actualizată~. Dacă ne limităm la versiunile de C++ dinainte de 2011, afirmația anterioară este adevărată ☹)

[//]: # ()
[//]: # (C++ din 2011 încoace este cunoscut ca C++ modern și poate fi considerat relevant și în prezent.
 Versiunile mai vechi nu sunt relevante decât dacă aveți ghinionul să nimeriți pe proiecte vechi care nu
  pot fi actualizate ușor. Puteți arunca o privire
   [aici]&#40;https://www.jetbrains.com/lp/devecosystem-2020/cpp/&#41;.)

[//]: # ()
[//]: # (**Ce oferă C++ pentru a continua să fie relevant?**)

[//]: # ()
[//]: # (Pe scurt, siguranța tipurilor de date. Se verifică *la compilare* dacă toate operațiile
 pe care le facem respectă constrângerile tipurilor de date. Acest fapt ne ajută să obținem programe
  mai sigure și cu mai puține bug-uri. Cel puțin în teorie. Dezavantajul? Compilarea poate să dureze
   destul de mult în cazul proiectelor de mari dimensiuni.)

[//]: # (**Dar asta nu era valabil și înainte de C++11?**)

[//]: # ()
[//]: # (Parțial. În C++ modern au fost introduse multe funcționalități care îmbunătățesc în mod semnificativ situația:)

[//]: # (- deducerea automată a tipurilor &#40;cu `auto`&#41;)

[//]: # (- elemente de programare funcțională &#40;funcții anonime&#41;)

[//]: # (- administrarea automată a memoriei &#40;evitarea pe cât posibil a alocărilor dinamice explicite&#41;)

[//]: # (- șabloane cu număr variabil de argumente &#40;variadic templates&#41;)

[//]: # (- multithreading)

[//]: # (- aserțiuni la compilare)

[//]: # (- și altele, dar cele de mai sus sunt printre cele mai importante)

[//]: # ()
[//]: # (TL;DR: multe dintre funcționalitățile de mai sus ne ajută să scriem cod mai sigur,
 deoarece lăsăm compilatorul să efectueze verificări de tipuri de date și să se ocupe de
  alocări/dezalocări de memorie *la momentul compilării*.)

[//]: # ()
[//]: # (Limbajele ca Java sau Python folosesc GC &#40;garbage collection&#41;, operație de eliberare a
 memoriei *la execuție*. Chiar dacă în cazul limbajului Java situația nu mai este atât de dramatică, încă
  nu are tipuri de date cu adevărat generice. Succesul limbajului Java este dat de faptul că este mai simplu
   de învățat decât C++ și de faptul că, la momentul apariției sale, oferea administrarea automată a memoriei
    și verificări mai stricte de tipuri.)

[//]: # (**Este mai bun C++ decât Java sau invers?**)

[//]: # ()
[//]: # (Nici, nici. Depinde foarte mult de ce anume vrem să facem. Trebuie să alegem tehnologiile
 potrivite pentru problema respectivă pe care vrem să o rezolvăm, nu să folosim ceva doar că ne place,
  deși există altceva "consacrat".)

[//]: # ()
[//]: # (**Concluzia?**)

[//]: # ()
[//]: # (Verificarea tipurilor de date este importantă pentru prevenirea bug-urilor.)

**Funcții**

Momentan nu voi detalia acest subiect. De aceea, ne interesează doar două aspecte ale funcțiilor:
- parametrii
- tipul de retur

Orice funcție are zero sau mai mulți parametri și un tip de retur. Dacă nu întoarcem nimic, folosim tipul `void`.

Parametrii se transmit prin valoare sau prin referință (cu `&`). Dacă transmitem prin valoare, se efectuează o **copie**. Exemplu:
```c++
int aduna(int a, int b) {
    return a + b;
}
// exemplu de apelare: int x = aduna(3, 5);
// alt exemplu: int x = 1, y = 2; int z = aduna(x, y);

// presupunem ca am inclus <iostream>
void citire(int a, int &b) {
    std::cin >> a >> b;
}
// apelare: int x = 1, y = 2; citire(x, y); std::cout << x << " " << y << "\n";
// presupunem ca am introdus 4 si 5
// se va afisa 1 5: de ce?
// in cazul lui `a` se transmite prin valoare si se face o copie care se distruge la iesirea din apelul functiei
// in cazul lui `b` se transmite prin referinta si nu se face nicio copie
```
Observație: în limbajul C++, este bine să evităm pe cât putem pointerii, deoarece ei există mai mult
pentru a oferi compatibilitate cu limbajul C. Spre deosebire de pointeri, referințele au proprietatea
că nu pot fi nule. Detalii [aici](https://isocpp.org/wiki/faq/references#refs-vs-ptrs).

### "Hello, world!"

```c++
#include <iostream>

int main() {
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
```

De ce nu am folosit `using namespace std;`? Pentru că acest namespace conține *extrem de multe* funcții
cu care am putea intra în conflict de nume. Dacă alegeți să folosiți această instrucțiune, trebuie să
fiți conștienți de consecințele pe care le are. Scopul acestor namespace-uri tocmai acesta ar fi,
să prefixăm numele funcțiilor cu numele namespace-ului pentru a evita complet coliziunile de nume.
Mai multe detalii despre acest subiect puteți citi
[aici](https://isocpp.org/wiki/faq/coding-standards#using-namespace-std)
și [aici](https://stackoverflow.com/q/1452721/).

### "Hello, world!" cu clase

```c++
#include <iostream>

class Persoana {
public:
    Persoana() {
        std::cout << "In constructor!\n";
    }

    ~Persoana() {
        std::cout << "In destructor!\n";
    }

    void saluta() {
        std::cout << "In functie membru publica!\n";
    }

private:
    void secret() {
        std::cout << "In functie membru privata!\n";
    }
};

int main() {
    Persoana p;
    p.saluta();
    // p.secret();  // eroare: nu putem apela functii membru private
    return 0;
}
```
Observații:
- încercați să decomentați linia comentată
  - apelați funcția membru privată din funcția membru publică: se poate?
- în clasele din C++, orice funcție/operator/atribut este implicit considerat `private` (adică ascuns)
  - folosim [specificatori de acces](https://en.cppreference.com/w/cpp/language/access) `public`/`protected`/`private` pentru a schimba acest comportament
  - un specificator de acces este "valabil" până la sfârșitul definiției clasei sau până este întâlnit alt specificator de acces
  - este doar ceva de gust dacă declarăm întâi elementele publice și apoi pe cele private sau invers
  - în al doilea caz, putem omite primul specificator `private`, întrucât acesta va fi implicit
- constructorii și destructorul se apelează în mod **automat**!
- convențiile de denumire a claselor și a funcțiilor (membru) nu contează dpdv tehnic
  - cel mai important este să folosiți aceleași convenții peste tot la nivel de program/proiect
  - puteți citi mai multe [aici](https://isocpp.org/wiki/faq/coding-standards) (același link din secțiunea anterioară)
- în cazul structurilor (cu `struct`), specificatorul de acces implicit este `public` pentru a păstra compatibilitatea cu limbajul C

### Atribute

```c++
#include <iostream>

class Persoana {
public:
    Persoana(std::string nume);
    ~Persoana();

    void saluta();

private:
    std::string nume;

    void secret();
};

Persoana::Persoana(std::string nume) {
    this->nume = nume;
    std::cout << "In constructor!\n";
}

Persoana::~Persoana() {
    std::cout << "In destructor!\n";
}

void Persoana::saluta() {
    std::cout << "Sunt " << nume << "!\n";
}

void Persoana::secret() {
    std::cout << "In functie membru privata!\n";
}

int main() {
    Persoana p("Marius");
    p.saluta();
    // p.secret();  // eroare: nu putem apela functii membru private
    // std::cout << p.nume;  // eroare: nu putem accesa atribute private
    // Persoana pers;  // eroare: nu exista constructorul Persoana::Persoana()
    return 0;
}
```
Observații:
- **important**: declarăm orice fel de atribute ca fiind `private`, deoarece câteva dintre principiile programării orientate pe obiecte sunt încapsularea și ascunderea datelor:
  - ideea este să abstractizăm detaliile de reprezentare a datelor prin funcții membru cu scopul de a putea schimba în viitor modul de reprezentare al datelor fără să stricăm codul existent
  - acest lucru este posibil cât timp reușim să avem *aceeași interfață publică*, deoarece este mai important rezultatul final decât detaliile de implementare
    - (în ideea că implementarea nu este extrem de ineficientă)
- am *definit* funcțiile membru în afara clasei, deoarece așa avem o privire de ansamblu asupra membrilor clasei și nu suntem distrași de detaliile de implementare
  - atunci când definim funcțiile în altă parte decât în locul în care au fost definite, este necesară utilizarea operatorului de rezoluție de scop `::`
    - de ce? pentru că este posibil ca o funcție cu același nume să fie declarată în alt loc din program:
      - fie avem un mecanism prin care putem să facem diferența între două funcții declarate cu același nume în locuri diferite din program
      - fie trebuie să folosim nume unice *la nivel de program*: ca exemplu, această restricție este valabilă în limbajul C
    - aplicarea operatorului `::` se face asupra *numelui funcției*, iar tipul de retur rămâne la fel (`void` în exemplu)
- am *declarat* funcțiile membru în interiorul clasei (altfel nu se poate)
- dacă definim o funcție în interiorul clasei, declarația este în același loc cu definiția
- există unele operații repetitive care sunt identice pentru majoritatea claselor:
  - pentru exemplul de mai sus, este vorba de constructorul de inițializare și destructor
  - aceste funcții (membru) pot fi generate automat de către editor (de exemplu CLion)
  - iar noi ar trebui să adăugăm doar mesajele de afișare...
  - ... pe care le-am adăugat doar cu scop ilustrativ ca să înțelegeți ordinea de apelare a constructorilor și a destructorilor; vom reveni asupra acestui subiect
  - se poate începe cu scrierea funcției `main`, iar restul codului să fie generat de editor și abia apoi modificat unde este cazul
- putem avea mai mulți constructori, mai ales dacă avem mai multe atribute
  - înlocuiți constructorul cu `Persoana::Persoana(std::string nume = "(lipsa)")`
    - în limbajul C++ este permisă supraîncărcarea funcțiilor (constructorii sunt niște funcții mai speciale)
    - o modalitate de a supraîncărca funcții este prin utilizarea valorilor implicite (`= "(lipsa)"`)
    - astfel, avem doi constructori, iar declarația `Persoana pers;` va fi validă
- destructorul este unul singur: de ce?
  - deoarece este apelat automat de compilator și nu ar trebui să avem vreun motiv să eliberăm resursele în moduri diferite pentru același tip de obiect
  - dacă vi se pare că ar fi nevoie de doi destructori, cel mai probabil ar trebui să aveți două clase, întrucât aveți nevoie de două abstractizări diferite

### Moștenire

La programul anterior adăugăm următoarea clasă:
```c++
class Angajat : Persoana {
    int salary;

public:
    Angajat(int salary) : salary{salary} {}
};
```
Observații:
- în cazul claselor, moștenirea este implicit `private`
- în cazul structurilor, moștenirea este implicit `public`, pentru a păstra consistența cu specificatorii de acces
- moștenirea înseamnă că toate atributele și funcțiile membru ale clasei de bază `Persoana` sunt preluate de clasa derivată `Angajat`
- moștenirea clasei B din clasa A se folosește atunci când are sens să spunem că B este un fel de A (relație "IS-A(N)": B is an A)
- `salary{salary}` se numește listă de inițializare
  - înainte de C++11, exista doar sintaxa `salary(salary)`
  - primul `salary` se referă la atributul `salary` al clasei
  - al doilea `salary` se referă la parametrul trimis constructorului
  - dacă doream să modificăm parametrul primit, scriam `salary{salary * 10}`
  - este de preferat sintaxa cu acolade dacă putem folosi C++ modern, deoarece aceasta nu permite conversii implicite cu posibile pierderi de informație: de exemplu, o conversie implicită de la `long long` la `int`
- nu mai facem nimic în corpul constructorului, dar este necesar să fie prezent pentru ca programul să fie corect dpdv sintactic
**Putem apela constructorii clasei de bază din clasa derivată?**

Da. Aceștia se vor apela în ordinea în care apar în definiția clasei și nu în ordinea apelării din lista de inițializare:
```c++
class Angajat : Persoana {
    int salary;

public:
    Angajat(std::string nume, int salary) : Persoana(nume), salary{salary} {}
};
```

### Compunere

Compunerea are sens atunci când clasa B face parte din clasa A (relație "HAS-A(N)": A has a B). Exemplu:
```c++
struct Dorinta {
    std::string nume;
    Dorinta(const std::string& nume = "") : nume{nume} {}
};

class Persoana {
public:
    Persoana(std::string nume);
    ~Persoana();

    void saluta();

private:
    std::string nume;
    Dorinta dorinta;

    void secret();
};
```
