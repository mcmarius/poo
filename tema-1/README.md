# Tema 1

### ⚠ Puneți cât mai multe întrebări! Nu există întrebări greșite.
#### Semnalați orice fel de greșeli găsiți!

Înainte de a parcurge aceste materiale, ar trebui să aveți configurat
[mediul de lucru](/env).

Pentru proiect, voi presupune că ați făcut un repository nou pe baza
[acestui repository template](https://github.com/mcmarius/oop-template) și că v-ați clonat local
repository-ul vostru. Dacă nu doriți să folosiți acest template, trebuie să ajungeți la o configurație
echivalentă:
- gitignore
- CMakelists.txt (sau un fișier pentru alt sistem de build portabil)
- flags pentru warnings (de asemenea trebuie să fie portabile)
- eventualele configurații pentru biblioteci externe de asemenea trebuie să fie portabile
- serviciu de integrare continuă (pe scurt CI = continuous integration)
- fișier README cu o scurtă descriere

Pentru diverse exerciții, este suficient să vă configurați afișarea de warnings. Desigur, trebuie să
și țineți cont de warnings și să le eliminați pentru că **nu sunt degeaba**.

## Introducere/recapitulare C și C++

Limbajul C++ a apărut prin anii 1979-1985, inițial ca o extensie a limbajului C.

Limbajul C a apărut prin anii 1969-1973 ca o îmbunătățire a limbajului B. Limbajul B este o versiune
"simplificată" a limbajului BCPL pentru a ocupa mai puțină memorie ca să aibă loc pe unele calculatoare
de atunci (8 KB). BCPL a apărut la sfârșitul anilor 1960.

#### De ce a fost nevoie de noi limbaje?

Pentru **tipuri de date mai sigure** prin care descriem ce vrem să implementăm. Cu cât punem mai multe informații
despre tipurile de date în cod, cu atât mai mult ne poate ajuta compilatorul să ne semnaleze situațiile când
tipurile de date nu se potrivesc. Asta înseamnă **mai puține bug-uri**.

În limbajele B și BCPL, singurul tip de date era "word" (echivalent cu word-ul hardware din assembly),
adică un număr care poate fi tratat ori ca întreg, ori ca adresă de memorie în funcție de context.

Limbajul C a adăugat mai multe tipuri de date pentru verificarea corectitudinii
tipurilor de date de către compilator.

C++ oferă siguranță și mai mare a tipurilor de date prin cât mai multe verificări
efectuate la pasul de compilare.

#### De ce au (avut) succes C și C++?

C++ a devenit popular datorită C. C a devenit foarte popular datorită legăturii strânse cu **Unix**.
Alte aspecte de interes: **portabilitate, eficiență și performanță**, adică nu trebuie scris cod specific
pentru fiecare arhitectură, consumă puține resurse și merge repede. La vremea când au apărut aceste limbaje,
alternativele pentru cod eficient erau limbajele de asamblare și... cam atât.

Fortran este performant, însă este util doar pentru calcule numerice. C și C++ sunt pentru uz general.

De ce C și nu Pascal? C a apărut din nevoi practice (pentru a rescrie Unix din limbaj de asamblare în C pentru
a fi portabil) și a fost foarte util pentru industrie și cercetare; Pascal a fost creat inițial doar ca
instrument de învățare și nu a avut succes pe termen lung.

#### Ce dezavantaj are acest succes al C și C++?

Trebuie păstrată **compatibilitatea cu versiuni mai vechi** (backwards compatibility).
Codul scris acum câteva zeci de ani ar trebui
să compileze fără (prea multe) modificări și cu versiuni mai noi de compilatoare.

La vremea când a apărut limbajul C, deja erau multe programe scrise în B și BCPL.

Anumite reguli ale limbajului C sunt o consecință a nevoii de a face programe scrise în B și BCPL să
funcționeze în continuare și în C fără prea multe modificări.

Întrucât C++ a fost dezvoltat într-o primă fază ca extensie a limbajului C, și C++ a preluat reguli bizare.

#### De ce C++ e din ce în ce mai complicat?

Cu fiecare versiune, C++ adaugă noi funcționalități pentru a remedia problemele istorice sau alte probleme
introduse în versiuni anterioare.

Cu toate acestea, trebuie păstrată în mare parte compatibilitatea cu versiuni mai vechi de C++ pentru că
altfel nu putem folosi biblioteci externe dezvoltate acum multe zeci de ani.
De asemenea, costul pentru a rescrie diverse biblioteci ar fi prea mare.

#### De ce învățăm C++ în 202x?

~~Pentru că așa e programa.~~ Pentru că nici alternativele nu sunt mai grozave. C++ are avantajul
că este general și e mai ușor ulterior să treci la ceva mai specific.

Dezavantajul este că C++ este _prea_ general. Evident, e mai greu să înveți ceva general decât ceva specific.

[//]: # (
Întrebarea mai bună nu ar fi de ce facem C++ la OOP, ci de ce la specializarea Informatică nu se mai face C.
)

#### Încă mai este C++ un limbaj relevant în 202x?

Încă este [folosit][stackoverflow-survey-2021]. Versiunile de C++ moderne (>=11) sunt relevante.

Dacă e să ne luăm după anumite [sondaje](https://www.jetbrains.com/lp/devecosystem-2021/cpp/),
doar 6% mai folosesc versiuni vechi de C++ vechi și nu vor să treacă pe versiuni mai noi.

### Noțiuni de bază din C și C++

Rulați exemplele următoare, vedeți ce se întâmplă, apoi faceți câteva modificări, vedeți din nou ce se întâmplă
și încercați să înțelegeți de ce merge sau de ce nu merge.

Orice cod compilat de C/C++ poate fi încadrat în două categorii: executabile sau biblioteci.

Un executabil trebuie să aibă o singură funcție numită `main` care întoarce un număr întreg (`int`). Dacă
executabilul a rulat cu succes, se va întoarce 0.
```c++
int main() {
    return 0;
}
```

Strict pentru funcția `main` există o regulă specială și putem să nu mai punem `return 0` la sfârșit:
```c++
int main() {}
```

**Pentru toate celelalte funcții care nu sunt `void`, trebuie obligatoriu să avem `return` pe toate ramurile
de execuție! Altfel... 🔥️**

#### Spații de nume (namespaces)

Spațiile de nume (namespaces) grupează diverse componente legate între ele sub un singur nume pentru a evita
conflicte de nume cu alte componente din alt spațiu de nume.

**Evitarea conflictelor** este principalul beneficiu al spațiilor de nume. Clauzele `using namespace` elimină
această separare logică și favorizează apariția conflictelor de nume. În acest caz, degeaba mai avem namespaces
dacă punem totul la grămadă.

Din acest motiv, nu voi folosi `using namespace std;`. Nu vreau să îmi pierd timpul cu erori ușor de prevenit.

Singurele excepții sunt namespace-urile mici, de exemplu `using namespace std::literals;`.

**Nu folosiți `using namespace std;` în fișiere header!** În fișierele .cpp nu prea contează, dar prefer să
folosesc aceleași convenții peste tot. Detalii la secțiunea despre etapele compilării.

Detalii din surse de încredere:
[aici](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rs-using-directive) și
[aici](https://isocpp.org/wiki/faq/coding-standards#using-namespace-std).

**Exemplu**

Echipa A definește o funcție `scrie` și folosește spațiul de nume `EchipaA`. Prin urmare, numele complet al
funcției va fi `EchipaA::scrie`.

Echipa B definește o funcție `scrie` și folosește spațiul de nume `EchipaB`. Prin urmare, numele complet al
funcției va fi `EchipaB::scrie`. Funcția aceasta nu are vreo legătură cu `EchipaA::scrie`, doar se nimerește
să aibă același nume.

Echipa C are nevoie de funcționalități dezvoltate de ambele echipe A și B. Dacă echipa C folosește clauze
`using namespace`, va pierde mult timp să depaneze situația și să elimine conflictele, întrucât mesajele de
eroare din C++ în caz de coliziuni de nume pot fi kilometrice.

#### Variabile

O variabilă este caracterizată de:
- nume
- tip de date: `int`, `double`, definit de noi [etc.](https://en.cppreference.com/w/c/language/type)
- valoarea reținută
- adresa de memorie unde se află variabila
- scop: blocul de acolade cel mai aproape de definiția variabilei
- durată: "locală", "globală" (în ghilimele pentru că nu e prea corect, dar lăsăm așa momentan)

Am pus link către tipurile de date predefinite din C deoarece în C++ sunt enorm de multe
tipuri de date predefinite.

Putem afla adresa unei variabile `x` folosind `&x`.

```c++
#include <iostream>

int main() {
    int x = 10, y = -5;
    double z = 1.1;

    std::cout << "Variabila x are valoarea " << x << " și se află la adresa " << &x << "\n";
    x = x - 3;
    std::cout << "Variabila x are valoarea " << x << " și se află la adresa " << &x << "\n";
    ++x; // x = x + 1;
    std::cout << "Variabila x are valoarea " << x << " și se află la adresa " << &x << "\n";

    std::cout << "Variabila y are valoarea " << y << " și se află la adresa " << &y << "\n";
    y -= 4; // y = y - 4;
    std::cout << "Variabila y are valoarea " << y << " și se află la adresa " << &y << "\n";

    std::cout << "Variabila z are valoarea " << z << " și se află la adresa " << &z << "\n";
    z *= 3.3; // z = z * 3.3;
    std::cout << "Variabila z are valoarea " << z << " și se află la adresa " << &z << "\n";

    {
        int x = 100;
        std::cout << "Variabila x are valoarea " << x << " și se află la adresa " << &x << "\n";
    }
    std::cout << "Variabila x are valoarea " << x << " și se află la adresa " << &x << "\n";
}
```

Pentru orice tip de date putem folosi operatorul `sizeof` ca să aflăm câți bytes ocupă o variabilă declarată
cu acel tip de date. Putem aplica `sizeof` și pe o variabilă, dar va fi luat în considerare tipul de date.
`sizeof` este determinat la compilare.

```c++
#include <iostream>

int main() {
    std::cout << "Pe acest mediu de lucru, sizeof(int) este " << sizeof(int) << "\n";
    std::cout << "Pe acest mediu de lucru, sizeof(long) este " << sizeof(long) << "\n";
    std::cout << "Pe acest mediu de lucru, sizeof(double) este " << sizeof(double) << "\n";
}
```

Ce se înțelege prin mediu de lucru?

Sistem de operare, compilator, procesor.

**Înainte de a folosi valoarea unei variabile** (pentru calcule, afișări etc.),
**orice variabilă trebuie inițializată!**

Implicit, variabilele au o valoare nedeterminată, inițializate cu ce se găsește prin memorie. Din acest motiv,
putem considera că de fapt nu sunt inițializate. Variabilele de tipuri primitive (`int`, `double` etc.)
nu sunt inițializate implicit cu zero deoarece acest proces este considerat costisitor în lumea C/C++.

Totodată, utilizarea variabilelor neinițializate este o cauză de defecte (bug-uri) foarte frecventă.

Pentru a încerca să prevenim astfel de defecte (și nu numai), va trebui să ținem cont de warnings și să le
eliminăm. Oricum nu avem de ales 😉️

#### Pointeri 👻

Am văzut mai devreme că putem afla adresa unei variabile `x` folosind `&x`. Ce tip de date are expresia `&x`?

Dacă `x` este de tip `int`, atunci `&x` are tipul de date `int*`. Putem să declarăm o variabilă de tip `int*`
pe care o vom folosi să reținem adrese de variabile de tip `int`:

```c++
#include <iostream>

int main() {
    int x = 10, y = -5;
    double z = 1.1;

    std::cout << "Variabila x are valoarea " << x << " și se află la adresa " << &x << "\n";
    std::cout << "Variabila y are valoarea " << y << " și se află la adresa " << &y << "\n";
    std::cout << "Variabila z are valoarea " << z << " și se află la adresa " << &z << "\n";

    int* ptr = &x;
    std::cout << "Variabila ptr are valoarea " << ptr << " și se află la adresa " << &ptr << "\n";
    ptr = &y;
    std::cout << "Variabila ptr are valoarea " << ptr << " și se află la adresa " << &ptr << "\n";
    // ptr = &z; // eroare: ptr știe să rețină doar adrese de `int`, nu și adrese de `double`
}
```

Variabila `ptr` este un **pointer** la `int`, având tipul de date `int*`.

La rândul său, și variabila `ptr` este reținută undeva în memorie, deci îi putem afla adresa cu `&ptr`. Am
putea reține această adresă folosind o variabilă de tip `int**`. O astfel de variabilă ar fi pointer la `int*`.

Tipurile de date `int*` și `int**` sunt două tipuri de date distincte.

**Ce mai putem face cu pointerii?**

Putem afla valoarea reținută de variabila a cărei adrese e reținută de pointer.
Procesul se numește dereferențiere.

**Surse majore de bug-uri: dereferențierea unui pointer invalid!**

**Exemple: pointer neinițializat, pointer nul, pointer agățat (dangling pointer).**

Un pointer agățat înseamnă că la un moment dat era pointer valid, însă nu mai este (de exemplu, este
reținută adresa unei variabile care a fost distrusă).

```c++
#include <iostream>

int main() {
    int x = 10, y = -5;

    std::cout << "Variabila x are valoarea " << x << " și se află la adresa " << &x << "\n";
    std::cout << "Variabila y are valoarea " << y << " și se află la adresa " << &y << "\n";

    int* ptr = &x;
    std::cout << "Variabila ptr are valoarea " << ptr << " și se află la adresa " << &ptr << "\n";
    std::cout << "Prin dereferențierea variabilei ptr obținem valoarea " << *ptr << "\n";
    x += 5;
    std::cout << "Prin dereferențierea variabilei ptr obținem valoarea " << *ptr << "\n";

    ptr = &y;
    std::cout << "Variabila ptr are valoarea " << ptr << " și se află la adresa " << &ptr << "\n";
    std::cout << "Prin dereferențierea variabilei ptr obținem valoarea " << *ptr << "\n";
    y = 3;
    std::cout << "Prin dereferențierea variabilei ptr obținem valoarea " << *ptr << "\n";
    
    {
        int h;
        h = 4;
        ptr = &h;
    }
    // ptr este acum dangling pointer!!!
    // eroare!!! // std::cout << "Prin dereferențierea ptr obținem valoarea " << *ptr << "\n";

    ptr = nullptr; // ptr este acum nul!!!
    // eroare!!! // std::cout << "Prin dereferențierea ptr obținem valoarea " << *ptr << "\n";
    int* ptr2; // ptr2 este neinițializat!!!
    // eroare!!! // std::cout << "Prin dereferențierea ptr2 obținem valoarea " << *ptr2 << "\n";
}
```

Putem modifica valoarea unei variabile în mod indirect, prin intermediul unui pointer.

```c++
#include <iostream>

int main() {
    int x = 10, y = -5;

    std::cout << "Variabila x are valoarea " << x << " și se află la adresa " << &x << "\n";
    std::cout << "Variabila y are valoarea " << y << " și se află la adresa " << &y << "\n";

    int* ptr = &x;
    std::cout << "Variabila ptr are valoarea " << ptr << " și se află la adresa " << &ptr << "\n";
    std::cout << "Prin dereferențierea variabilei ptr obținem valoarea " << *ptr << "\n";
    std::cout << "Variabila x are valoarea " << x << " și se află la adresa " << &x << "\n";
    *ptr += 5;
    std::cout << "Prin dereferențierea variabilei ptr obținem valoarea " << *ptr << "\n";
    std::cout << "Variabila x are valoarea " << x << " și se află la adresa " << &x << "\n";

    ptr = &y;
    std::cout << "Variabila ptr are valoarea " << ptr << " și se află la adresa " << &ptr << "\n";
    std::cout << "Prin dereferențierea variabilei ptr obținem valoarea " << *ptr << "\n";
    std::cout << "Variabila y are valoarea " << y << " și se află la adresa " << &y << "\n";
    *ptr = 3;
    std::cout << "Prin dereferențierea variabilei ptr obținem valoarea " << *ptr << "\n";
    std::cout << "Variabila y are valoarea " << y << " și se află la adresa " << &y << "\n";
}
```

Cât ocupă un pointer?

Depinde de mediul de lucru. De obicei, ocupă 4 sau 8 bytes, indiferent de tipul de pointer.

```c++
#include <iostream>

int main() {
    std::cout << "Pe acest mediu de lucru, sizeof(int*) este " << sizeof(int*) << "\n";
    std::cout << "Pe acest mediu de lucru, sizeof(int**) este " << sizeof(int**) << "\n";
    std::cout << "Pe acest mediu de lucru, sizeof(int***) este " << sizeof(int***) << "\n";
    std::cout << "Pe acest mediu de lucru, sizeof(long*) este " << sizeof(long*) << "\n";
    std::cout << "Pe acest mediu de lucru, sizeof(double*) este " << sizeof(double*) << "\n";
}
```

#### Funcții

Cel mai simplu tip de funcție: o funcție care nu primește parametri și nu întoarce nimic.
```c++
#include <iostream>

void f() {
    std::cout << "f()\n";
}

int main() {
    f();
}
```

În C, parametrii se pot transmite doar prin valoare. În C++, parametrii se pot transmite prin valoare sau prin
referință.

La transmiterea parametrilor prin valoare, se creează câte o copie locală pentru fiecare parametru, iar
acea copie există numai în corpul funcției respective. Modificările făcute în interiorul funcției asupra
parametrilor transmiși prin valoare nu se vor vedea în afara funcției:
```c++
#include <iostream>

void f(int x) {
    std::cout << "f: x: " << x << "\n";
    ++x;
    std::cout << "f: x: " << x << "\n";
}

int main() {
    int x;
    x = 2;
    std::cout << "main: x: " << x << "\n";
    f(x);
    std::cout << "main: x: " << x << "\n";
}
```

Desigur, nu era nevoie ca ambele variabile să se numească `x`.

Următorul exemplu folosește tot transmitere prin valoare:
```c++
#include <iostream>

void f(int* ptr) {
    std::cout << "f: *ptr: " << *ptr << "\n";
    ++(*ptr);
    std::cout << "f: *ptr: " << *ptr << "\n";
}

int main() {
    int x;
    x = 2;
    std::cout << "main: x: " << x << "\n";
    f(&x);
    std::cout << "main: x: " << x << "\n";
}
```

De ce este transmitere prin valoare? Să facem câteva modificări:
```c++
#include <iostream>

void f(int* ptr) {
    std::cout << "f: *ptr: " << *ptr << ", ptr: " << ptr << "\n";
    ++(*ptr);
    std::cout << "f: *ptr: " << *ptr << ", ptr: " << ptr << "\n";
    int z = 10;
    ptr = &z;
    std::cout << "f: *ptr: " << *ptr << ", ptr: " << ptr << "\n";
}

int main() {
    int x;
    int* ptr;
    x = 2;
    ptr = &x;
    std::cout << "main: x: " << x << ", *ptr: " << *ptr << ", ptr: " << ptr << "\n";
    f(ptr);
    std::cout << "main: x: " << x << ", *ptr: " << *ptr << ", ptr: " << ptr << "\n";
}
```

De ce există referințe și transmitere prin referință în C++?

Deoarece C++ vrea să fie un limbaj mai sigur, iar pointerii ar trebui întotdeauna inițializați ca să nu avem
bug-uri. Totuși, C++ nu a vrut să modifice semantica pointerilor pentru că altfel ar fi pierdut compatibilitatea
cu limbajul C.

Prin urmare, a fost introdus un nou tip de date care să fie ca pointerii, nepermițând lipsa inițializării. De
asemenea, referințele nu pot fi nule prin definiție. Mai mult, odată ce au fost inițializate, referințele nu
pot arăta către altă variabilă (pentru a nu arăta către ceva invalid - dangling pointer).

Astfel, se poate spune și că referințele sunt un alias sau un alt nume pentru o variabilă. Adresa unei
referințe este de fapt adresa variabilei spre care arată referința.

Putem observa că modificările asupra variabilei transmise prin referință sunt vizibile după apelul funcției:
```c++
#include <iostream>

void f(int& ref) {
    std::cout << "f: ref: " << ref << ", &ref: " << &ref << "\n";
    ++ref;
    std::cout << "f: ref: " << ref << ", &ref: " << &ref << "\n";
    int z = 10;
    ref = z; // nu se modifică variabila către care arată ref
             // se atribuie 10 (valoarea lui z) variabilei referite
    std::cout << "f: ref: " << ref << ", &ref: " << &ref << "\n";
}

int main() {
    int x;
    // int& ref; // eroare - nu este inițializată la declarare!
    int& ref = x;
    x = 2;
    std::cout << "main: x: " << x << ", ref: " << ref << ", &ref: " << &ref << "\n";
    f(x);
    std::cout << "main: x: " << x << ", ref: " << ref << ", &ref: " << &ref << "\n";
}
```

La întoarcerea din funcții prin valoare se efectuează o copie a variabilei din clauza `return`.

La întoarcerea din funcții prin referință **nu se efectuează copieri. Prin urmare, NU întoarcem referințe
la variabile locale, deoarece acele variabile nu vor mai exista!**

Vom avea aceeași eroare și dacă întoarcem prin valoare un pointer care reține adresa unei variabile locale.  

#### Definire vs declarare

Prin definirea unei variabile, a unei funcții sau al unui tip de date, descriem complet
variabila/funcția/tipul de date. O definiție implică automat declararea variabilei/funcției/tipului de date.
Reciproca **nu este adevărată!**

O declarare (fără definiție) doar anunță faptul că acea variabilă sau acea funcție există undeva în program.
De multe ori nu avem nevoie de definiția completă a unei funcții ca să o putem apela, deci este suficientă
declararea.

Declararea variabilelor (fără definiție) este folosită de obicei doar pentru variabile "globale". Nu intru
în detalii pentru că **nu folosim variabile globale la acest curs!**

În ceea ce privește tipurile de date, nu avem nevoie decât de declarația tipului de date dacă vom crea doar
o variabilă de tip pointer la acel tip de date (sau referință - dar referințele sunt implementate intern
prin pointeri), întrucât un pointer este simplu de construit: acesta doar reține o adresă de memorie.

De obicei toți pointerii au același `sizeof`: de obicei, acesta este 4 sau 8 bytes.

Avem nevoie de definiția completă a tipului de date numai atunci când vrem să construim o variabilă
de acel tip de date, deoarece avem nevoie de `sizeof`-ul acelui tip de date.

Momentan vom vedea exemple doar cu definiții și declarații de funcții:
```c++
#include <iostream>

void f(); // declarație fără definiție

int main() {
    // void f(); // declarație fără definiție
    f();
}
```
Putem pune declarații atât "globale", cât și locale. Declarația promite că undeva în fișierele noastre sursă
(sau în biblioteci) există definită funcția `void f()`. Prin urmare, după ce am declarat funcția, avem voie să o
apelăm.

Totuși, am mințit că există funcția `void f()` Programul a compilat, dar a crăpat la etapa de linking (legarea
tuturor surselor compilate (fișiere obiect) și bibliotecilor):
```
/usr/bin/ld: /tmp/ccYSCOlt.o: in function `main':
main.cpp:(.text+0x9): undefined reference to `f()'
collect2: error: ld returned 1 exit status
```

Odată ce am declarat o funcție, o putem apela din acel punct în jos. De definit o putem defini mai jos în
același fișier sau în alt fișier. Totuși, definiția nu trebuie să se repete.
```c++
#include <iostream>

void g() { // declarație și definiție
    // f(); // eroare: declarația lui f este valabilă doar în main!
    std::cout << "g()\n";
}

int main() {
    // f(); // eroare: f nu a fost încă declarat
    void f(); // declarație fără definiție
    f();
    g();
}

void f() {
    std::cout << "f()\n";
}
```

#### Citire și afișare

Pentru a putea modifica variabilele, funcțiile de citire primesc variabilele prin referință. Și funcțiile de
afișare primesc variabilele tot prin referință, dar vom vedea ulterior prin ce diferă.
```c++
#include <iostream>

int main() {
    int x;
    std::cout << "x: ";
    std::cin >> x;
    std::cout << "Am citit " << x << "\n";
}
```

Nu sunt fan citiri de la tastatură pentru că nu putem automatiza rularea/testarea codului. Consider citirile de
la tastatură o pierdere de timp. Dacă alegeți această variantă, salvați ce introduceți de la tastatură într-un
fișier, apoi puteți face copy-paste din fișier în terminal ca să nu pierdeți timpul de fiecare dată.

Din nefericire, sunt mai dificil de automatizat apăsările de taste speciale: săgeți, escape etc. 

#### Instrucțiuni condiționale și repetitive

Dacă avem o singură instrucțiune, nu este nevoie de acolade. Totuși, dacă avem `if`-uri imbricate, este
bine să punem acolade ca să fie executate cum ne așteptăm ramurile `else if`/`else`.
```c++
#include <iostream>

int main() {
    int x = 3;

    if(x%3 == 0) {
        std::cout << "rest 0\n";
    }
    else if(x%3 == 1) {
        std::cout << "rest 1\n";
    }
    else {
        std::cout << "altceva\n";
    }
}
```

Instrucțiunea `switch` este similară cu `if`, doar că face numai comparații de egalitate. Poate face codul
mai ușor de citit în anumite situații, mai ales în cazul enumerărilor.

Trebuie să punem câte o instrucțiune `break` după fiecare ramură; altfel, execuția continuă pe următorul
`case`, chiar dacă nu este respectată condiția.

Putem folosi instrucțiunea specială `[[fallthrough]];` pentru a ilustra că suntem conștienți că lipsește
`break` și dorim efectul de "cascadă" (util dacă tratăm mai multe cazuri aproximativ la fel).
Altfel, vom primi warning.
```c++
#include <iostream>

int main() {
    int x = 11;

    switch(x%7) {
    case 0:
        std::cout << "rest 0\n";
        break;
    case 1:
        std::cout << "rest 1\n";
        break;
    case 2:
        std::cout << "rest 2\n";
        [[fallthrough]]; // C++17
    case 3:
        std::cout << "rest 2 sau 3\n";
        break;
    default:
        std::cout << "altceva\n";
        break;
    }
}
```

Avem 3 instrucțiuni repetitive: `for`, `while` și `do`/`while`.
```c++
#include <iostream>

int main() {
    int x = 5;
    while(x > 0) {
        std::cout << "while: x: " << x << "\n";
        --x;
    }

    do {
        std::cout << "do while 1: x: " << x << "\n";
        --x;
    } while(x > 0);

    do {
        std::cout << "do while 2: x: " << x << "\n";
        ++x;
    } while(x < 3);
    
    for(int i = 0; i < x; ++i)
        std::cout << "for 1: i: " << i << "\n";

    for(int i = x; i >= 0; --i)
        std::cout << "for 2: i: " << i << "\n";
}
```

**Atenție!** Dacă la ultimul `for` am fi folosit un tip de date fără semn (`unsigned i = x;`), codul ar fi
rulat la infinit! Dacă am vrea să folosim `unsigned`, am putea avea următorul cod:
```c++
#include <iostream>

int main() {
    for(unsigned i = 5; ; --i) {
        std::cout << "for: i: " << i << "\n";
        if(i == 0)
            break;
    }
```

Analog lui `break` avem `continue`:
```c++
#include <iostream>

int main() {
    for(unsigned i = 0; i < 4; ++i) {
        if(i < 2)
            continue;
        std::cout << "for: i: " << i << "\n";
    }
```

#### Tablouri, vectori

În C, este imposibil de făcut distincția între un pointer și un vector, deoarece vectorii sunt convertiți
la pointeri la primul element atunci când vectorii sunt transmiși unei funcții. Asta înseamnă și că nu putem
ști numărul de elemente.

În C++ avem [`std::array`](https://en.cppreference.com/w/cpp/container/array) pentru vectori de dimensiune
fixă, cunoscută la momentul compilării. De asemenea, avem
[`std::vector`](https://en.cppreference.com/w/cpp/container/vector) dacă nu știm numărul (maxim) de elemente.

`std::vector` se ocupă automat de gestiunea memoriei la runtime.

```c++
#include <array>
#include <vector>
#include <iostream>

int main() {
    std::array<int, 4> arr1 = {1, -1, 42, 8};
    // std::array<int, 4> arr1{1, -1, 42, 8}; // echivalent
    std::cout << arr1[0] << "\n";
    std::array<int, 3> arr2;
    arr2[0] = 3;
    arr2[1] = 2;
    //arr2[2] = 1;
    // arr[3] = 0; // nu se fac verificări, crapă urât la runtime, segmentation fault
    // std::get<3>(arr2) = 0; // verificare la compilare
    // arr2.at(3) = 0; // verificare la runtime - mai multe detalii la excepții
    std::cout << "arr1.size(): " << arr1.size() << "\n";
    std::cout << "arr2.size(): " << arr2.size() << "\n";

    std::vector<double> vec1{2.3};
    vec1.push_back(3.1);  // [2.3, 3.1]
    vec1[1] = 2;          // [2.3, 2]     // nu se fac verificări
    // vec1.at(1) = 2;                    // verificare la runtime
    // pt std::vector nu putem face verificări la compilare
    int x = vec1.back();  // x == 2
    std::cout << "x: " << x << "\n";
    vec1.pop_back();      // [2.3]
    std::vector<int> vec2(3, 1); // [1, 1, 1]
    vec2.push_back(2);
    std::cout << "vec1.size(): " << vec1.size() << "\n";
    std::cout << "vec2.size(): " << vec2.size() << "\n";
}
```

Pentru a parcurge elementele unui std::array/std::vector, avem următoarele variante:
```c++
#include <iostream>

int main() {
    std::array<int, 4> arr = {1, -1, 42, 8};
    for(unsigned i = 0; i < arr.size(); ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";
    for(auto& elem : arr)
        std::cout << elem << " ";
    std::cout << "\n";

    std::vector<int> vec(3, 1); // [1, 1, 1]
    vec.push_back(2);
    for(unsigned i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << " ";
    std::cout << "\n";
    for(const auto& elem : vec)
        std::cout << elem << " ";
    std::cout << "\n";
    
}
```

Este de preferat varianta cu `for(auto& elem : arr)`, deoarece nu apelăm funcția `size()` la fiecare iterație.
Folosim `const` dacă nu dorim să modificăm elementele.

#### Șiruri de caractere

Șirurile de caractere sunt un dezastru și în C, și în C++. Dacă vrem să facem prelucrări corecte pe șiruri
de caractere, trebuie să folosim biblioteci specializate. C și C++ nu oferă funcții de prelucrare pentru
șiruri de caractere codificate ca UTF-8 (cel mai folosit standard din prezent (2022)).

Dacă găsiți o bibliotecă de C/C++ care știe să facă normalizări (pentru comparații de egalitate), să
aibă o interfață decentă/ușor de folosit (adică nu [ICU](https://icu.unicode.org/)) și să nu fie un chin
pasul de compilare (adică nu ICU), vă rog să îmi spuneți. Pentru prelucrări mai simple, am găsit
[utf8_string](https://github.com/Gumichan01/utf8_string) și [tiny-utf8](https://github.com/DuffsDevice/tiny-utf8).

C++ ne va provoca destule bătăi de cap, așa că nu are rost să ne punem singuri bețe în roate. Prin urmare,
nu are rost să folosim șirurile de caractere din C și să gestionăm manual alocările de memorie.

De aceea, vom folosi [`std::string`](https://en.cppreference.com/w/cpp/string/basic_string/basic_string):
```c++
#include <string>
#include <iostream>

int main() {
    std::string str = "asd";
    str += "efg";
    std::cout << str << "\n";
    if(str == "asd")
        std::cout << "match!\n";
}
```

#### Structuri, uniuni, enumerări

La acest curs nu vom folosi structuri și uniuni. Le putem ignora.

Enumerările sunt folosite pentru a documenta codul și eventual pentru a evita constante magice:
```c++
enum Semafor { Rosu, Galben, Verde };

int main() {
    Semafor sem;
    sem = Semafor::Rosu;
    sem = Galben;
}
```

Intern, enumerările sunt întregi. Dacă nu specificăm altfel, numerotarea începe de la 0 și se
incrementează cu 1.

Dacă nu ne interesează foarte tare conversia cu numerele întregi, este mai bine să folosim `enum class`,
deoarece numele constantelor nu mai sunt globale, ci sunt localizate:
```c++
enum class Semafor { Rosu, Galben, Verde };

int main() {
    Semafor sem;
    sem = Semafor::Rosu;
    // sem = Galben; // eroare
}
```

Altă variantă ar fi să punem un `enum` simplu într-un spațiu de nume (namespace).

De obicei folosim instrucțiuni `switch` când vrem să tratăm cazurile unei enumerări, iar editoarele ne pot
avertiza dacă am uitat un caz (de exemplu dacă am adăugat ulterior un câmp în enumerare și nu avem o ramură
implicită):
```c++
#include <iostream>

enum class Semafor { Rosu, Galben, Verde };

int main() {
    Semafor sem;
    sem = Semafor::Rosu;
    switch(sem) {
        case Semafor::Rosu:
            std::cout << "ROȘU!\n";
            break;
        case Semafor::Galben:
            std::cout << "Galben!\n";
            break;
        case Semafor::Verde:
            std::cout << "Verde!\n";
            break;
        default:
            std::cout << "Defect\n";
            break;
    }
}
```

#### Alocare dinamică

În C, funcțiile standard pentru alocare/dezalocare dinamică de memorie sunt `malloc`, `realloc` și `free`.
Funcțiile `malloc`/`realloc` întorc un pointer la începutul zonei de memorie alocată, iar `free` primește
acest pointer ca să elibereze zona de memorie respectivă.

În C++ modern **nu avem nevoie de alocări dinamice explicite** dacă nu facem ceva low-level. Ne complicăm
existența inutil și putem avea tot felul de bug-uri subtile sau greu de depanat.

Biblioteca standard de C++ ne pune la dispoziție suficient de multe tipuri de date pentru a nu avea nevoie
să ne ocupăm noi explicit de gestionarea memoriei pentru situațiile uzuale. Nu are rost să reinventăm roata.

Dacă totuși dorim asta, avem `new`/`new[]` și `delete`/`delete[]`: `new`-urile întâi apelează `malloc` și apoi
constructorul/constructorii, iar `delete`-urile întâi apelează destructorul/destructorii și apoi `free`. Nu
există echivalent `realloc` în C++.

Tot ce alocăm explicit cu funcțiile/operatorii de alocare trebuie să eliberăm cu funcțiile/operatorii pereche.
În caz contrar, avem memory leaks sau alte erori de memorie.

Pentru a detecta erorile de memorie, folosim programe specializate (valgrind, GCC/Clang sanitizers).
Pe Windows nu am găsit un astfel de program care să fie gratuit și să mai și funcționeze.

#### Directive de preprocesare

Directiva `#include` face un simplu copy-paste dintr-un fișier în altul.
Putem avea conflicte urâte dacă nu avem grijă.

Modulele au apărut în C++ de-abia din C++20, însă nu sunt implementate de toate compilatoarele și cu atât
mai puțin de majoritatea bibliotecilor externe.

Directiva `#define` face un simplu find-and-replace. O folosim doar pentru include guards (vedem la headers).

Directivele `#ifdef`/`#else`/`#endif` le folosim la include guards și pentru compilare condiționată. Noi nu
vom folosi direct compilarea condiționată, ci vom folosi biblioteci care să facă asta. De obicei, condiționăm
compilarea pentru anumite sisteme de operare sau arhitecturi de procesor.

Directivele `#pragma` sunt directive nonstandard, neportabile și depind de compilator. Totuși, pentru ce facem
noi aici, putem considera în regulă `#pragma once` ca alternativă la include guards.

#### Bibliotecile standard

Găsim documentația pentru bibliotecile standard de C și C++ pe cppreference.

Biblioteca standard de C este de obicei furnizată de sistemul de operare. Exemple: glibc sau musl pe Linux,
MSVCRT sau UCRT pe Windows. Din acest motiv, biblioteca de C nu este de obicei inclusă în executabile.
Întrucât limbajul C este relativ simplu, există numeroase implementări alternative.

Headerele standard pentru biblioteca C sunt denumite în C sub forma `<header.h>`: `<stdio.h>`, `<stdlib.h>` etc.

În C++, headerele din biblioteca C de forma `<header.h>` sunt accesibile ca `<cheader>` deoarece sunt
incluse în spațiul de nume `std`: `<cstdio>`, `<cstdlib>` etc.


Pentru limbajul C++ nu există multe implementări "la zi" pentru C++ și biblioteca standard asociată.
Compilatoarele de C++ vin de obicei la pachet cu biblioteca standard de C++. Exemple: libstdc++ sau
libc++ pe Linux/macOS, libstdc++-6.dll pe MinGW și acele "Visual C++ Redistributable Runtime" pe MSVC.

### Despre compilarea în C și C++

[//]: # (TODO)

## Concepte de bază de OOP în C++

### Clase și obiecte

O clasă reprezintă un tipar după care construim obiecte. Un obiect este o instanță a unei clase.

[//]: # (Clasele seamănă cu structurile, în sensul că grupează mai multe atribute)

[//]: # (&#40;eventual distincte&#41; la un loc.)

[//]: # ()
[//]: # (Din punct de vedere al sintaxei de C++, structurile sunt &#40;cu mici excepții&#41; echivalente)
[//]: # (cu clasele pentru)
[//]: # (a păstra compatibilitatea cu limbajul C. Totuși, convenția este să folosim structuri pentru a descrie)
[//]: # (obiecte simple și clase pentru a reprezenta obiecte mai complicate.)

[//]: # ()
[//]: # (În cadrul acestui curs vom folosi numai clase.)

[//]: # (În practică, este mai eficient în anumite situații să folosim structuri.)

Exemple cu ce știm până acum:
```c++
// definirea unei clase
class Student {};

// definirea altei clase
class Facultate {
    // momentan nu avem nimic aici
};

int main() {
    // construirea unor obiecte
    Student s1, s2;
    Student s3 = Student();
    Student s4 = Student{};
    Facultate fmi;
    // alte câteva moduri de a construi obiecte
    Student s5{};
    Student s6(s5), s7{s5}, s8 = Student(s6), s9 = Student{s7};
}
```

**Atenție!** Din cauză că limbajul C++ a fost inițial o extensie a limbajului C, a preluat sintaxa pentru a
declara funcții. În exemplul următor, `s2` și `s3` sunt declarații de funcții: ambele sunt funcții care nu
primesc parametri și întorc prin valoare un obiect de tip `Student`.

Cu toate acestea, `s6` și `s8` din exemplul de mai sus sunt obiecte, nu declarații de funcții.
Din această cauză, limbajul C++ are o gramatică ambiguă; sintaxa cu acolade încearcă să remedieze situația.

Doar `s1` este un obiect construit în exemplul de mai jos!

```c++
class Student {};

int main() {
    Student s1, s2();
    Student s3();
}
```

De aceea preferăm pe cât posibil sintaxa de inițializare cu acolade (a fost introdusă în C++11).

### Compunere

Clasele de până acum nu sunt prea interesante, așa că vom adăuga niște atribute.

[//]: # (Am zis mai înainte că seamănă cu structurile,)

Compunerea exprimă relații de tipul "are" ("has a/an" în engleză). Dacă putem forma propoziții _cu sens_ de felul
"un obiect de tip A **are** un atribut de tip B", înseamnă că avem compunere.

De exemplu, un student **are** un nume (de tip șir de caractere) și se află într-un anumit an, iar o facultate
**are** nume și **are** mai mulți studenți:
```c++
#include <string>
#include <vector>

class Student {
    std::string nume;
    int an;
};

class Facultate {
    std::string nume;
    std::vector<Student> studenti;
};
```

Nu întotdeauna putem forma propoziții simple (sau cu sens) cu verbul "are". Dacă vreți o formulare generală, atunci
am putea spune că avem compunere între clasele A și B dacă un obiect de tip A **are** ca atribut caracteristic
un obiect de tip B.

### Încapsulare

Înainte de a vorbi despre constructori, să încercăm să folosim clasele definite mai sus:
```c++
// codul din exemplul anterior

int main() {
    Student st;
    st.nume = "Nume"; // eroare
}
```

De ce primim eroare? Implicit, tot ce definim într-o clasă nu poate fi accesat, deoarece specificatorul de acces
implicit este `private`. Asta înseamnă că definiția clasei `Student` este echivalentă cu:
```c++
class Student {
private:
    std::string nume;
    int an;
};
```

_Dacă vrem să picăm la acest curs_, putem scrie în felul următor, iar codul din `main` va compila:
```c++
class Student {
public:
    std::string nume;
    int an;
};
```

**De ce am pica? De ce nu vrem să avem atribute publice?**

Dacă punem ceva `public`, atunci este imposibil să putem modifica ulterior acele părți publice ale implementării
**fără să stricăm codul care depinde de atributele publice**.

Ce am putea strica?

Dacă decidem că nu vrem ca numele să mai fie `std::string` sau vrem să redenumim acest atribut, atunci stricăm
codul client: în cazul nostru, codul din funcția `main`.

Desigur, am putea redenumi noi manual și în `main`, însă într-un scenariu realist este posibil să fim nevoiți să
facem multe astfel de modificări ce pot buși codul client, iar clientul respectiv nu va putea face toate
modificările necesare în timp util.

**De ce și-a făcut clientul update la o nouă versiune a codului nostru?**

Pentru că avea nevoie de noi funcționalități.

**Putem evita să stricăm pe viitor codul client?**

Da. Facem absolut totul `private` în afară de minimul necesar de care are nevoie clientul. Acest procedeu
poartă numele de **încapsulare**.

### Getters, setters

Getterii și setterii rezolvă parțial problema (îi putem genera din editor):
```c++
#include <string>
#include <iostream>

class Student {
private:
    std::string nume;
    int an;
public:
    const std::string& getNume() const { return nume; }
    int getAn() const { return an; }
    void setNume(const std::string& nume_) { nume = nume_; }
    void setAn(int an_) { an = an_; }
};

int main() {
    Student st;
    st.setNume("Nume");
    st.setAn(1);
    std::cout << "Studentul " << st.getNume() << " este în anul " << st.getAn() << "\n";
}
```

De ce rezolvă problema doar **parțial?**

Deoarece tot nu am ascuns complet detaliile de implementare, iar cu getters/setters este imposibil să facem
acest lucru complet, întrucât, la rândul lor, getters/setters depind în mod direct de atributele private.

De cele mai multe ori, vom avea nevoie doar de câțiva getters (cât mai puțini, strictul necesar) și nu vom
folosi setters deloc.

Dacă nu folosim setters, cum putem inițializa atributele obiectului? Cu ajutorul constructorilor.

### Constructorul fără parametri

**Constructorii au rolul de a inițializa atributele obiectului și de a aloca diverse resurse.** Pentru
eliberarea acestor resurse, se folosesc [destructori](#destructor).

Secțiunea se numește astfel deoarece putem avea un singur astfel de constructor.

Să revenim la primul rând din `main`:
```c++
Student st;
```

În mod automat, compilatorul generează un constructor fără parametri pentru clasa `Student`. Acest constructor
apelează constructorii fără parametri ai atributelor definite în clasa respectivă.

În cazul tipurilor de date primitive (`int`, `char`, `double`, pointeri etc.), acestea **nu vor fi inițializate.**
Mai riguros spus, vor fi inițializate cu o valoare nedeterminată. Mai puțin riguros: ce se nimerește să fie
în zona respectivă de memorie.

**Exercițiu:** afișați valoarea atributului `an` imediat după construirea obiectului:
ar trebui să vă apară o valoare aleatoare.
Partea tristă este că probabil nu puteți vedea acest lucru pe Windows.

Așadar, înainte de a folosi un obiect, **trebuie să inițializăm toate atributele.**

De ce nu face asta limbajul C++ în mod implicit?

Deoarece filozofia limbajelor C și C++ este să nu faci operații dacă nu ai neapărat nevoie de ele
([zero-overhead principle](https://en.cppreference.com/w/cpp/language/Zero-overhead_principle)).
Inițializarea este o astfel de operație, întrucât acele atribute s-ar inițializa de două ori dacă
ar exista și o inițializare implicită.

Din acest motiv engine-urile de jocuri, de browsers și alte componente eficiente sunt scrise în C sau C++
și nu în alte limbaje mai "moderne" care au din start inițializări automate.

Să revenim la definiția clasei și să ne definim noi în mod explicit constructorul fără parametri ca să
vedem că este apelat:
```c++
#include <string>
#include <iostream>

class Student {
private:
    std::string nume;
    int an;
public:
    Student() { std::cout << "Constructor Student fără params;\n" }
};

int main() {
    std::cout << "Înainte de apel constructor\n";
    Student st;
    std::cout << "După apel constructor\n";
}
```

Acest constructor este apelat în toate situațiile de mai sus unde nu aveam nimic între paranteze sau acolade
și unde nu era vorba de o declarație de funcție.

Ce se întâmplă dacă facem constructorul privat? **Încercați!**

#### Constructori cu `=default` și `=delete`

Dacă nu vrem să avem constructor fără parametri, putem face așa:
```c++
class Student {
private:
    std::string nume;
    int an;
public:
    Student() = delete;
};
```

Dacă **nu** avem tipuri de date primitive, atunci putem arăta mai clar că vrem constructor fără parametri astfel:
```c++
class Student {
private:
    std::string nume;
    std::string prenume;
public:
    Student() = default;
};
```

Observație: dacă vrem să avem constructorul `= default` "pe bune", îl lăsăm în interiorul definiției clasei.
Dacă este definit cu `= default` în afara clasei, atunci este tratat diferit 🙃

**Exercițiu:** adăugați un constructor fără parametri cu `= default` în clasa `Facultate`, schimbați vectorul
cu un singur student și puneți un mesaj de afișare în constructorul fără parametri al clasei `Student`. Apoi
în funcția `main` construiți un obiect de tip `Facultate`.

Ce se întâmplă dacă în `Student` constructorul fără parametri este `= delete;`, iar în clasa `Facultate`
constructorul fără parametri este `= default;`? Mai este generat un constructor fără parametri pentru
`Facultate`? **Verificați ce se întâmplă!**

### Constructori de inițializare

Secțiunea se numește astfel deoarece putem avea mai mulți astfel de constructori.

Acum vom înțelege de ce **nu avem nevoie de setters**. Știm deja că primim un constructor fără parametri
din partea compilatorului dacă nu ne definim noi acest constructor, iar acesta este apelat automat când facem un
obiect. Să revedem ce cod aveam înainte:
```c++
#include <string>
#include <iostream>

class Student {
private:
    std::string nume;
    int an;
public:
    const std::string& getNume() const { return nume; }
    int getAn() const { return an; }
    void setNume(const std::string& nume_) { nume = nume_; }
    void setAn(int an_) { an = an_; }
};

int main() {
    Student st;
    st.setNume("Nume");
    st.setAn(1);
    std::cout << "Studentul " << st.getNume() << " este în anul " << st.getAn() << "\n";
}
```

De ce vrem să scăpăm de setters? Din 2 motive:
- constructorul oricum este apelat în mod automat
- în programe mai mari este **foarte** posibil să uităm să apelăm toți setters
pentru toate obiectele în toate situațiile
- este mai eficient din constructori, dar vom vedea mai târziu de ce

Să definim un prim constructor de inițializare: 
```c++
#include <string>
#include <iostream>

class Student {
private:
    std::string nume;
    int an;
public:
    Student(const std::string& nume_, int an_) : nume{nume_}, an{an_} {
        std::cout << "Constr de inițializare Student\n";
    }

    const std::string& getNume() const { return nume; }
    int getAn() const { return an; }
};

int main() {
    Student st{"Nume", 1};
    std::cout << "Studentul " << st.getNume() << " este în anul " << st.getAn() << "\n";
}
```

Partea dintre `:` și acolada de la constructor (ultimul caracter de pe acel rând înainte de rândul nou)
se numește listă de inițializare: `nume{nume_}, an{an_}`.

În momentul în care execuția codului ajunge la acolada constructorului, toate atributele trebuie să fie
inițializate. Nu putem construi un obiect întreg dacă nu avem înainte complete toate piesele componente.

Implicit, compilatorul va încerca să apeleze constructorul fără parametri pentru fiecare atribut în parte.
Dacă acest constructor nu este public sau a fost șters, primim eroare la compilare. Menționez din nou că
atributele primitive nu sunt inițializate (cu ce ne-am aștepta) în mod automat. 

Observație: regulile de inițializare din C++ sunt foarte complicate, dar pentru ce avem nevoie aici vom
considera adevărat paragraful anterior, chiar dacă sunt omise niște detalii.

Câteva întrebări pentru voi:
- mai putem construi obiecte folosind constructorul fără parametri?
- ce putem face dacă totuși vrem constructorul fără parametri?
- mai funcționează clasa `Facultate`? Dacă da, funcționează corect?
- putem avea listă de inițializare și pentru constructorul fără parametri?

**Exerciții:** completați codul următor:
```c++
class Facultate {
    std::string nume;
    Student stud;
public:
    Facultate(
            const std::string& numeFacultate,
            const std::string& numeStudent, int anStudent) : nume(?), stud(?) {}

    Facultate(const std::string& numeFacultate, const Student& student_) : nume(?), stud(?) {}
};
```

Adăugați în constructori mesaje de afișare ca să știți dacă execuția codului ajunge acolo, iar apoi construiți
obiecte în `main` astfel încât să fie apelați ambii constructori din `Facultate`.

În cazul celui de-al doilea constructor se mai apelează constructorul nostru de inițializare din `Student`?

Nu, deoarece compilatorul generează și un constructor de copiere, chiar dacă avem definit un constructor
de inițializare cu parametri. De ce? Pentru că este natural să putem copia obiecte.

### Constructor de copiere

Secțiunea se numește astfel deoarece de cele mai multe ori vrem un singur astfel de constructor.
Voi prescurta acest constructor cu cc.

Pentru a demonstra ipoteza de mai sus, să ne definim constructorul de copiere (cc) pentru clasa `Student`:
```c++
class Student {
    std::string nume;
    int an;
public:
    Student(const Student& other) : nume{other.nume}, an{other.an} {
        std::cout << "Constr de copiere Student\n";
    }
};
```

Compilatorul nu mai generează constructorul fără parametri dacă ne definim noi un constructor, indiferent de
categoria constructorului (fără parametri, de inițializare, de copiere etc).

În schimb, cc este generat întotdeauna dacă nu îl redefinim sau ștergem.

Verificați acum că se apelează constructorul de copiere atunci când construim un obiect de tip `Facultate` cu
ajutorul constructorului de inițializare cu 2 parametri. Dacă nu se apelează, vă rog să îmi dați mesaj.

Transmiteți studentul prin valoare în constructorul din `Facultate`. Se mai apelează încă o dată cc?

#### În ce situații se apelează constructorul de copiere?
- atunci când apelăm implicit/explicit constructorul de copiere (evident)
- în liste de inițializare
- la transmiterea prin valoare la apeluri de funcții/constructori
- la întoarcerea obiectelor din funcții prin valoare

**Constructorul de copiere nu se apelează la transmiterea parametrilor prin referință și nici la
întoarcerea obiectelor din funcții prin referință!**

Așadar, atunci când definim constructorul de copiere, **obligatoriu** trebuie să transmitem obiectul inițial
prin referință ca să **nu** se apeleze cc. Dacă am transmite prin valoare, s-ar apela cc, care ar apela cc,
care ar apela...

Dacă nu punem referință `const`, vom avea surprize neplăcute. Putem să avem și cc fără `const`, însă
pentru acest laborator cel mai probabil nu vom da de astfel de situații.

CC definit de compilator este cu `const` dacă toate atributele au CC cu `const`. Altfel o să fie generat
cc fără `const` și acolo apar surprizele.

#### Când avem nevoie de constructorul de copiere?

Pentru tema 1 avem nevoie ca să știm cum funcționează.

În general avem nevoie de cc numai atunci când avem atribute speciale (de exemplu pointeri sau conexiuni la
servere) sau când vrem să facem debugging.

La tema 2 (și la colocviu) vom avea atribute de tip pointeri sau vectori de pointeri și atunci vom suprascrie
cc pentru că altfel codul nu va face ce trebuie.

**În majoritatea situațiilor NU avem nevoie să redefinim cc deoarece cc generat de compilator funcționează
corect!**

Verificați că cc funcționează corect.

În alte limbaje, cc poartă numele de "clone" (sau "deep copy"). Vom face și noi "deep copy" la tema 2 pentru
că nu avem de ales.

**Observație!** Dacă redefinim cc, trebuie să fim atenți când adăugăm noi atribute în clasă, deoarece acestea
nu vor fi copiate dacă nu cerem asta în mod explicit. **Verificați!**

Putem folosi `= default` și `= delete` și pentru a forța generarea/ștergerea constructorilor de copiere
generați de compilator.

### Constructor de mutare

Întrucât în multe situații se creează multe obiecte temporare, a apărut nevoia de a elimina din aceste copieri
pentru a îmbunătăți performanța.

```c++
#include <string>
#include <utility>
#include <iostream>

class Student {
    std::string nume;
    int an;
public:
    Student(const std::string& nume_, int an_) : nume{nume_}, an{an_} {
        std::cout << "Constr de inițializare Student\n";
    }

    Student(const Student& other) : nume{other.nume}, an{other.an} {
        std::cout << "Constr de copiere Student\n";
    }

    Student(Student&& other) : nume{std::move(other.nume)}, an{std::move(other.an)} {
        std::cout << "Constr de mutare Student\n";
    }
};

class Facultate {
    std::string nume;
    Student stud;
public:
    //Facultate(const std::string& nume_, const Student& stud_) : nume{nume_}, stud{stud_} {}
    Facultate(const std::string& nume_, Student stud_) : nume{nume_}, stud{std::move(stud_)} {}
    //Facultate(const std::string& nume_, Student&& stud_) : nume{nume_}, stud{std::move(stud_)} {}
};

int main() {
    Facultate f1{"fmi", Student{"s1", 1}};
    // Facultate f1{"fmi", {"s1", 1}}; // dacă nu avem constructorul explicit, merge și așa
}
```

Care este diferența față de cc?

În cazul cc, fiecare atribut era copiat și construit de la zero. În total se construiesc complet două obiecte.

Pentru constructorul de mutare (cm), se construiește un obiect plin,
iar apoi se "mută" conținutul într-un nou obiect. În total se construiește complet _un singur obiect_.

În cazul constructorului de mutare, obiectul inițial ajunge într-o stare nedefinită. Putem considera că
rămâne "gol". Cel mai bine nu mai facem nimic cu obiectul inițial.
Oricum, de cele mai multe ori, acest obiect inițial este temporar.

Constructorii de mutare sunt (mult) mai eficienți, deoarece ca implementare doar interschimbă niște pointeri.

**Exercițiu:** reveniți la acest exemplu după ce citiți despre destructor, iar apoi afișați în destructor
valorile atributelor. Ce observați?

Putem folosi `= default` și `= delete` și pentru a forța generarea/ștergerea constructorilor de mutare
generați de compilator.

### `operator=` de copiere

Să încercăm să scriem un pic diferit constructorul de inițializare din `Facultate`:
```c++
#include <string>
#include <utility>
#include <iostream>

class Student {
    std::string nume;
    int an;
public:
    Student(const std::string& nume_, int an_) : nume{nume_}, an{an_} {
        std::cout << "Constr de inițializare Student\n";
    }

    Student(const Student& other) : nume{other.nume}, an{other.an} {
        std::cout << "Constr de copiere Student\n";
    }
};

class Facultate {
    std::string nume;
    Student stud;
public:
    Facultate(const std::string& nume_, const Student& stud_) {
        nume = nume_;
        stud = stud_;
    }
};

int main() {
    Facultate f1{"fmi", Student{"s1", 1}};
}
```

Hopa, nu merge!

Nu merge deoarece în `Student` nu avem constructor fără parametri, iar în constructorul din `Facultate` trebuie
să avem construite **toate** atributele **înainte** de acolada deschisă a constructorului.

Să adăugăm un constructor fără parametri în clasa `Student`. Sau, și mai bine, să punem parametri impliciți
la constructorul deja existent:
```c++
    Student(const std::string& nume_ = "st", int an_ = 1) : nume{nume_}, an{an_} {
        std::cout << "Constr de inițializare Student\n";
    }
```

Observăm că nu mai este apelat constructorul de copiere. Totuși, se construiesc două obiecte. Primul este
obiectul temporar din `main`, iar al doilea este creat în mod implicit înainte de prima acoladă a
constructorului din `Facultate`.

**Exercițiu:** afișați numele studentului înainte și după rândul cu `stud = stud_;`.

La rândurile `nume = nume_;` și `stud = stud;` se apelează funcțiile `operator=` de copiere (op= pe scurt)
generate de compilator în mod automat pentru a putea face atribuiri în mod natural.

Diferența dintre cc și op= este aceea că în cazul cc noi **nu** avem deja construit un obiect (fix atunci îl
construim), pe când în cazul op= noi avem deja obiectul construit complet și rescriem atributele.

Asemănarea dintre cc și op= este aceea că lăsăm obiectul inițial intact.

#### De ce avem nevoie și de cc, și de op=?

Deoarece în cazul op= putem recicla anumite resurse pentru a nu le aloca de la zero din nou. De asemenea,
nu vrem să rescriem întotdeauna toate atributele (de exemplu id-uri).

Exemplu de resurse: memorie, fișiere, conexiuni la servere.

Să vedem că într-adevăr se apelează `operator=`:
```c++
#include <string>
#include <utility>
#include <iostream>

class Student {
    std::string nume;
    int an;
public:
    Student(const std::string& nume_ = "st", int an_ = 1) : nume{nume_}, an{an_} {
        std::cout << "Constr de inițializare Student\n";
    }

    Student(const Student& other) : nume{other.nume}, an{other.an} {
        std::cout << "Constr de copiere Student\n";
    }

    Student& operator=(const Student& other) {
        nume = other.nume;
        an = other.an;
        std::cout << "operator= copiere Student\n";
        return *this;
    }
};

class Facultate {
    std::string nume;
    Student stud;
public:
    Facultate(const std::string& nume_, const Student& stud_) {
        nume = nume_;
        stud = stud_;
    }
};

int main() {
    Facultate f1{"fmi", Student{"s1", 1}};
}
```

#### De ce vrem să scriem constructorii cu liste de inițializare și nu cu atribuiri?

Deoarece nu are sens să construim de la zero niște obiecte ca apoi pe rândul următor să aruncăm la
gunoi vechile valori și să facem _din nou_ același lucru cu valorile primite ca parametru. În acest fel,
puteți considera că atributele sunt construite de două ori.

Dacă folosim liste de inițializare, atributele sunt inițializate o singură dată și este și mai eficient.

#### Când se apelează `operator=` de copiere?

În toate situațiile în care facem atribuiri, mai puțin la construirea de obiecte și când am apela
`operator=` de mutare (vezi mai jos):
```c++
int main() {
    Student s1 = Student{"st1", 1};
    Student s2 = Student("st2", 1);
    Student s3 = s1; // cc
    s2 = s3; // doar aici se apelează op=
}
```

Adăugați mesaje de afișare după fiecare rând în exemplul de mai sus pentru a verifica acest lucru.

#### Ne interesează self-assignment?

Da, însă pentru ce facem noi funcționează cum trebuie. Detalii
[aici](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-copy-self).

#### De ce întoarcem referință la `Student`?

Întoarcem referință pentru a nu mai face o copie și nu întoarcem `void` pentru a putea face atribuiri înlănțuite:
```c++
int main() {
    Student s1{"s1", 1}, s2{"s3", 1}, s3{"s3", 1};
    s3 = s2 = s1;
    // atribuirea de mai sus este echivalentă cu cea de mai jos
    s3.operator=(s2.operator=(s1));
    // și este echivalentă cu
    s3 = (s2 = s1);
}
```

#### Dacă avem o funcție care întoarce prin valoare un obiect, se apelează și cc, și op= de copiere?

La modul pur teoretic da; în realitate se fac optimizări, iar compilatoarele sunt acum obligate să
implementeze anumite optimizări pentru a respecta specificațiile limbajului. Mai multe detalii
[aici](https://en.cppreference.com/w/cpp/language/copy_elision) și
[aici](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Cr-value-return).

#### Dacă avem resurse speciale (de exemplu pointeri), la ce trebuie să avem grijă cu `operator=`?

Discutăm la tema 2, este mai complicat. Trebuie avut grijă la excepții, dar și excepțiile sunt tot la tema 2.

Dacă vrem să reciclăm resurse și să facem optimizări, este mult de lucru, dar această gestiune detaliată a
resurselor este posibilă numai în C++.

În schimb, dacă vrem o implementare sigură, dar fără bătăi de cap, folosim copy-and-swap. Inevitabil va fi mai
ineficientă, dar este ușor de realizat. Vom vedea un exemplu la tema 2.

În curs/seminar/materialele altor laboranți nu am văzut un `operator=` implementat corect.

Putem folosi `= default` și `= delete` și pentru a forța generarea/ștergerea op= de copiere
generați de compilator.

### `operator=` de mutare

Este analog constructorului de mutare. De obicei, când folosim cc, folosim op= de căutare. Când folosim cm,
folosim op= de mutare.

Regulile de definire implicită sunt mai complicate dacă vrem să avem și copiere, și mutare.

În C++ modern, de obicei este preferată mutarea, iar dacă nu este posibilă mutarea, se trece la copiere.
La acest curs nu suntem atât de moderni (încă), așa că vom implementa doar cc și op= de copiere.

Aceleași comentarii ca mai sus referitoare la self-assignment. Detalii
[aici](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-move-self).

Exemplu cu op= de mutare:
```c++
#include <string>
#include <utility>
#include <iostream>

class Student {
    std::string nume;
    int an;
public:
    Student(const std::string& nume_ = "st", int an_ = 1) : nume{nume_}, an{an_} {
        std::cout << "Constr de inițializare Student\n";
    }

    Student(Student&& other) : nume{std::move(other.nume)}, an{std::move(other.an)} {
        std::cout << "Constr de mutare Student\n";
    }

    Student& operator=(Student&& other) {
        nume = std::move(other.nume);
        an = std::move(other.an);
        std::cout << "operator= mutare Student\n";
        return *this;
    }
};

int main() {
    
    Student s1 = Student{"st1", 1};
    Student s2 = Student("st2", 1);
    Student s3 = std::move(s1); // constr de mutare
    s2 = std::move(s3); // doar aici se apelează op= de mutare
}
```

Putem folosi `= default` și `= delete` și pentru a forța generarea/ștergerea op= de mutare
generați de compilator.

### Destructor

Secțiunea se numește astfel deoarece putem avea un singur destructor. Desigur, după cum ne-am obișnuit,
C++ are excepții și în zona asta, dar nu ne interesează la această materie.

**Rolul destructorului este de a elibera eventualele resurse alocate în constructori sau op=.** La tema 2
avem neapărat nevoie de destructori. La tema 1 este mai mult de formă, să știm că există, ce rol are
și când este apelat.

Destructorul se apelează în mod **automat** atunci când obiectul își încetează existența.
Un obiect trăiește numai până la acolada închisă a blocului în care a fost declarată.

Destructorii se apelează în ordine inversă față de constructori (indiferent de tipul de constructor).

Exemplu:
```c++
#include <string>
#include <iostream>

class Student {
    std::string nume;
    int an;
public:
    Student(const std::string& nume_, int an_) : nume{nume_}, an{an_} {
        std::cout << "Constr de inițializare Student\n";
    }

    Student(const Student& other) : nume{other.nume}, an{other.an} {
        std::cout << "Constr de copiere Student\n";
    }

    ~Student() {
        std::cout << "Destr Student\n";
    }
};

class Facultate {
    std::string nume;
    Student stud;
public:
    Facultate(const std::string& nume_, const Student& stud_) : nume{nume_}, stud{stud_} {
        std::cout << "Constr de inițializare Facultate\n";
    }
};

int main() {
    Facultate f1{"fmi", Student{"s1", 1}};
}
```

Putem folosi `= default` și `= delete` și pentru a forța generarea/ștergerea destructorilor
generați de compilator.

Destructorii sunt generați în mod implicit de către compilator dacă nu îi definim/ștergem explicit. Dacă
un atribut al unui obiect nu poate fi construit (deoarece are constructori sau destructor inaccesibili),
atunci destructorul este șters în mod implicit. De ce? Dacă nu putem avea părțile componente, nu putem
avea nici întregul.

Dacă destructorul nu este public, obiectul nu poate fi distrus! De aceea, dacă obiectul nu va putea fi
distrus, nici nu îl vom putea construi.

**Exerciții:** adăugați destructor și pentru `Facultate`. Adăugați destructori și pentru exemplele anterioare.
Ce observați în cazul constructorilor de copiere? Dar în cazul celor de mutare?

Dacă vrem ca un obiect să trăiască în afara scopului în care a fost declarat, folosim alocare dinamică.
În acel caz, alocăm și eliberăm memoria în mod explicit. Totuși, nici în acest caz NU apelăm noi în mod
explicit destructorul.

În limbajul C++ modern, dacă nu facem ceva low-level, cel mai probabil nu avem nevoie de alocări dinamice
explicite. La teme, în majoritatea cazurilor nu veți avea nevoie de așa ceva.

Vom vorbi despre alocare dinamică la tema 2.

**NU apelăm niciodată manual destructorii în mod direct deoarece sunt oricum apelați automat!**
Dacă îi apelăm și noi, se vor apela de două ori și pot apărea bug-uri dificil de depanat.

Excepție: limbajul ne permite să apelăm manual destructorii deoarece
[există situații](https://isocpp.org/wiki/faq/dtors#placement-new)
în care este nevoie de acest lucru. Totuși, noi nu vom avea de-a face cu astfel de situații.

### Reprezentarea unui obiect ca șir de caractere

De ce vrem să reprezentăm obiectele ca șiruri de caractere (strings)?

Pentru că este ceva standard și ne așteptăm să fie definită această funcționalitate.
Dacă facem afișarea cu o funcție, aceasta poate fi numită în foarte multe feluri:
`afis`, `afiseaza`, `afisare`, `display`, `show`, `print`, `represent` etc.

În alte limbaje, funcția se numește `toString`, `ToString`, `description`, `repr`, `__repr__`.

În C++, realizăm acest lucru prin suprascrierea `operator<<` ca funcție de sine stătătoare, de
regulă ca funcție prieten (`friend`). Exemplu:
```c++
#include <string>
#include <iostream>

class Student {
    std::string nume;
    int an;
public:
    Student(const std::string& nume_, int an_) : nume{nume_}, an{an_} {
        std::cout << "Constr de inițializare Student\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Student& st) {
        os << "Nume: " << st.nume << ", an: " << st.an << "\n";
        return os;
    }
};

int main() {
    Student s1{"st1", 1}, s2{"st2", 1};
    std::cout << s1 << s2;
    // echivalent cu
    (std::cout << s1) << s2;
    // echivalent cu
    operator<<(operator<<(std::cout, s1), s2);
}
```

Folosim transmiterea parametrilor prin referință pentru a evita copieri. Întoarcem prin referință
ca să evităm copieri și ca să putem înlănțui apelurile.

Obiectul de afișat este `const`, deoarece nu vrem să fie modificat doar pentru că l-am afișat. Pe
de altă parte, `os` nu poate fi `const`, deoarece stream-ul de afișare se modifică în urma... afișării.

Funcțiile prieten (`friend`) ne permit accesul la câmpurile private ca să nu mai fie nevoie de getters.
Afișarea este o operație foarte comună și este strâns legată de clasă, motiv pentru care este în regulă
să putem accesa în mod direct atributele private (într-un cadru restrâns).

În biblioteca standard, avem ca funcție ajutătoare `std::to_string`. Totuși, nu avem definit `operator<<`
pentru toate tipurile de date, deoarece există prea multe posibilități de a face asta (care pot afecta
performanța), iar C++ încearcă să fie un limbaj general și să acopere cât mai multe cazuri.

De exemplu, în cazul vectorilor nu am vrea să afișăm toate elementele dacă acestea sunt extrem de multe.

În multe biblioteci externe este furnizat `operator<<` pentru tipurile de date cel mai frecvent
folosite din acele biblioteci. Această convenție facilitează compunerea implementărilor de
`operator<<` a atributelor componente.

**Exerciții:** adăugați `operator<<` pentru clasa `Facultate`. Înlocuiți la loc studentul cu un vector
de studenți. Ce ar trebui făcut la afișare? Las următorul cod ajutător:
```c++
#include <vector>
#include <iostream>

class Student {
    std::string nume = "st";
    int an = 1;
public:
    friend std::ostream& operator<<(std::ostream& os, const Student& st) {
        os << "Nume: " << st.nume << ", an: " << st.an << "\n";
        return os;
    }
};

int main() {
    std::vector<int> vec{1, 2, 3, 4, 5};
    vec.push_back(6);
    for(unsigned i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";
    std::vector<Student> vec2{Student{}, Student{}, Student{}};
    for(const auto& stud : vec2) {
        std::cout << stud;
    }
}
```

### Funcții membru, `*this`

Funcțiile membru sunt funcții care fac parte din definiția unei clase. Funcțiile membru trebuie declarate
în interiorul clasei, însă pot fi definite și în afara clasei.

Excepție: funcții `friend`.

În funcțiile membru vom implementa funcționalitățile specifice fiecărei teme în parte. Nu sunt multe
de zis aici, întrucât fiecare va implementa ce are nevoie.

Funcțiile membru nestatice au acces la obiectul curent și la atributele sale prin intermediul pointerului
`this`. Avem acces la `this` și în constructori, op= de copiere/mutare și destructor.

Nu avem acces la `this` în funcțiile prieten deoarece acestea sunt funcții libere și nu aparțin clasei.

Exemplu:
```c++
class Student {
    std::string nume = "st";
    int an = 1;
    static const int AN_MAX = 3; // fără static aici trebuie să suprascriu cc/op=
public:
    void promoveaza() {
        if(an < AN_MAX) {
          ++an;
          // echivalent cu
          // ++this->an;
        }
    }
};
```

De ce `this` este pointer și nu referință?

Din motive istorice: `this` a fost introdus în limbaj înainte să existe referințele.

### Regula celor trei/cinci/zero

Dacă a fost nevoie să definim în mod *explicit* constructorul de copiere, operatorul de atribuire
*sau* destructorul, înseamnă că cel mai probabil **trebuie** să le definim pe toate trei pentru ca
programul să funcționeze într-un mod intuitiv și să provoace cât mai puține bătăi de cap.

Vom avea pointeri la tema 2. La tema 1 aplicăm regula celor trei ca să știm când se apelează funcțiile
membru speciale: cc, op=, destructor.

Detalii [aici](https://en.cppreference.com/w/cpp/language/rule_of_three).

[//]: # (- copy-and-swap)
[//]: # (- excepții &#40;chiar sunt necesare?&#41;)
[//]: # (- static)

[//]: # (constructori/operatori de conversie)

## Cerințe tema 1

Scopul primei teme este familiarizarea cu limbajul C++ și cu unele concepte OOP de bază. La sfârșitul
săptămânii 4 ar trebui să aveți implementate minim 3 funcționalități pe care le considerați esențiale.

**Nu vă apucați de implementat până nu ați primit OK-ul! Aș vrea să discut cu fiecare în parte pentru
a stabili interfața.**

Cerințe comune:
- minim 3-4 clase folosind compunere; puteți adăuga și clase pentru moștenire,
dar vor fi în plus față de acele prime 3-4 clase
- constructori (expliciți) de inițializare pentru fiecare clasă
- regula celor trei pentru o clasă: constructor de copiere, `operator=` de copiere și destructor
- `operator<<` pentru **toate** clasele
- minim 3 funcții membru publice **în afară de** getters/citiri/afișări/adăugări triviale de elemente în vectori
  - nu ar trebui să aveți nevoie de setters; cât mai puțini getters
----
- atribute și alte funcții vor fi obligatoriu `private`; **fără variabile globale**
- cât mai multe `const`
- ⚠ obiectele trebuie să fie create în main sau citite dintr-un fișier: cât mai puține citiri de la tastatură
deoarece e pierdere de timp (discutăm excepțiile)
- apelarea/testarea *tuturor* funcțiilor publice în `main`; dacă nu le apelăm, la ce le-am mai definit?
  - apelarea se va face direct sau indirect: din `main` se pot apela funcții care construiesc obiecte
  cu clasele definite și folosesc aceste obiecte
- ideal, implementarea unei funcționalități mai dificile/complexe

Cerințe comune (organizatorice):
- codul trebuie să fie pe un repository de `git` la care să am acces (nu e obligatoriu să fie github dpmdv)
- obligatoriu `.gitignore`
- **NU faceți commit prin upload la fișiere din browser** deoarece nu se ia în considerare fișierul `.gitignore`;
nu fiți leneși!
- un tag de git pe un commit cu cod stabil
- obligatoriu un serviciu de integrare continuă (CI) cu minim 2 sisteme de operare diferite și
minim 2 compilatoare diferite
  - recomand să folosiți GitHub Actions deoarece e inclus în repository-ul template
  - fără warnings din partea compilatoarelor
  - fără warnings din partea instrumentelor de analiză statică
  - fără memory leaks

#### Termen limită
- săptămâna 3 (23 octombrie/5 martie): stabilirea claselor și implementarea parțială a acestora
- **săptămâna 4 (30 octombrie/12 martie): tema 1 gata**
- săptămâna 5 (6 noiembrie/19 martie): (eventuale) modificări în urma feedback-ului


### Cum putem testa funcțiile membru speciale?

Ne definim operatorul `==` (și `!=` dacă nu folosim C++20; îi poate genera editorul), apoi:
```c++
#include <cassert>
#include <iostream>

class Student { /* o implementare de mai sus */ };

int main() {
    Student st1{"st1", 1};
    Student st2{st1};
    assert((std::cout << "cc: Atributele se copiază corect\n", st1 == st2));
    st2.promoveaza();
    assert((std::cout << "cc: Modificarea copiei nu modifică obiectul inițial\n", st1 != st2));
    st1 = st2;
    assert((std::cout << "op=: Atributele se copiază corect\n", st1 == st2));
    st1.promoveaza();
    assert((std::cout << "op=: Modificarea copiei nu modifică obiectul inițial\n", st1 != st2));
}
```

#### Teme propuse

**Încercați să veniți cu propriile idei. Dacă nu aveți inspirație, uitați-vă pe
[proiectele din anii trecuți](/HoF.md).**

**Nu vă recomand temele propuse!**

Schițele de teme propuse oferă niște clase pentru crearea unor compuneri și a unor ierarhii
(pentru moșteniri - tema 2). Totuși, trebuie să stabiliți de la început o parte dintre funcționalitățile
pe care vi le propuneți să le implementați.

**Nu vă apucați de implementat până nu ați primit OK-ul! Aș vrea să discut cu fiecare în parte.**

Temele propuse sunt [aici](teme_propuse.md).

## Resurse
- [cppreference.com](https://en.cppreference.com/w/cpp)
- [ISO C++ FAQ](https://isocpp.org/faq/)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- [Diverse standarde (draft) ale limbajului](https://en.cppreference.com/w/cpp/links) sau ca
[HTML (neoficial)](https://github.com/timsong-cpp/cppwp) (sau
[aici](https://stackoverflow.com/questions/81656/where-do-i-find-the-current-c-or-c-standard-documents#4653479))
  - faptul că nu (mai) găsim draft-uri disponibile pentru standardele C++98/C++03 ar trebui să ne transmită ceva 😉
  - mai ales în contextul în care toate compilatoarele cunoscute au implementat C++11, C++14 și C++17
  - le-am adăugat mai mult ca să știți că există, nu e nevoie să vă uitați peste ele

[stackoverflow-survey-2021]: https://insights.stackoverflow.com/survey/2021
