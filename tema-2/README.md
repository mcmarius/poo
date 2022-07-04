# Tema 2

### ⚠ Puneți cât mai multe întrebări! Nu există întrebări greșite.
#### Semnalați orice fel de greșeli găsiți!

[//]: # (TODO de adăugat la sfârșit sintaxa în alte limbaje populare [ordonate aproximativ după popularitate]:)

[//]: # ( Java/Scala/Kotlin, C#, Python, JavaScript/TypeScript, Objective-C/Swift, Dart, PHP, R, Ruby, Perl)

[//]: # ( ?? plus clasificare static/dinamic typed??)

### Moșteniri

La tema 1 am folosit conceptul de POO numit compunere (sau compoziție):
```c++
class A {};

class B {
    A a;
};
```

**Compunerea** este utilă când vrem să modelăm legături de tipul "B **are** un A".

**Exemple:**
- un student **are** un nume
- o facultate **are** mai mulți studenți
- o aplicație **are** unul sau mai mulți utilizatori

---

**Moștenirea** este un alt concept de POO prin care dorim să modelăm legături de tipul "B **este un fel de** A".

Sintaxa pentru moștenire folosește `:`. Exemplu:
```c++
class A {};

class B : A {};
```
Cel mai adesea vom folosi termenii de **clasă de bază** și **clasă derivată**.

O clasă de bază reprezintă un concept general sau abstract care acoperă cât mai multe situații.

O clasă derivată reprezintă o particularizare a unei clase de bază pentru tratarea unor cazuri speciale
care nu pot fi modelate (ușor) într-un mod general în clasa de bază.

Pentru exemplul de mai sus, clasa A este clasă de bază, iar clasa B este clasă derivată:
```c++
class Baza {};

class Derivata : Baza {};
```

Un obiect de tip clasă derivată _este un fel de_ obiect de tip clasă de bază. Reciproca **nu** este adevărată!

**Exemple concrete:**
- o prună **este un fel de** fruct
- o bibliotecă universitară **este un fel de** bibliotecă
- un abonament promoțional **este un fel de** abonament

De asemenea, moștenirea este folosită pentru definirea de interfețe.
În contextul POO, o **interfață** este o clasă care declară una sau mai multe funcții.

De cele mai multe ori interfețele _nu oferă_ o implementare implicită a funcțiilor,
deoarece poate fi imposibil să definim o astfel de funcționalitate implicită care să fie general valabilă
pentru orice tip de date pe care l-am putea crea.

**Exemple de interfețe:**
- o interfață `Queue` cu funcțiile `push` și `pop`; interfața nu conține detalii despre modul de implementare
  - se poate implementa cu vectori, liste înlănțuite, ansamble etc.
- o interfață `Serializable` serializează obiecte, adică le transformă într-un format comun pentru a le stoca
  pe disc sau pentru a le transmite prin rețea
  - exemple de funcții declarate de interfață pentru transformări în diverse formate:
    `toJSON`, `.toCSV`, `toXLSX`, `toXML`, `toProtoBuf` etc.
  - nu orice obiect poate fi serializat: de exemplu, nu putem serializa o conexiune la o bază de date
- o interfață `Taggable` pentru gestionarea/generarea unor etichete și apoi căutarea obiectelor pe baza
  acestor etichete
  - interfața poate defini numeroase funcții ajutătoare
  - minimal ar fi (de exemplu) `void addTags(std::vector<‍std::string>)` și `bool hasTag(std::string)`
    - este suficient să știm că o derivată are clasa de bază `Taggable` pentru a apela funcțiile `addTags` și `hasTag`
  - de obicei am folosi această interfață pentru clase ce modelează tabele dintr-o bază de date

**Observații**
1. Moștenirea implementată corect ne ajută să extindem codul existent _fără să fie nevoie de multe modificări_
2. De obicei folosim compunerea pentru reutilizare de cod, **nu** moștenirea,
   deoarece avem mai multă flexibilitate și nu suntem nevoiți să păstrăm interfața anterioară.
3. Pentru a fi ușor de folosit, interfețele ar trebui să fie cât mai simple;
   nu este întotdeauna simplu să creăm astfel de interfețe.
4. Cuvântul interfață poate însemna:
   - o clasă care doar declară funcții fără să le definească
   - funcțiile publice dintr-o clasă sau dintr-un modul

[//]: # (constructori, destructori)

#### Constructori de inițializare, destructor

Constructorul clasei derivate apelează implicit constructorul clasei de bază fără parametri: 
```c++
#include <iostream>

class Baza {
public:
    Baza() { std::cout << "Constructor Bază\n"; }
    ~Baza() { std::cout << "Destructor Bază\n"; }
};

class Derivata : Baza {
public:
    Derivata() { std::cout << "Constructor Derivată\n"; }  // (1)
    ~Derivata() { std::cout << "Destructor Derivată\n"; }
};

int main() {
    Baza b;
    std::cout << "main: După b, înainte de d\n";
    Derivata d;
    std::cout << "main: sfârșit\n";
}
```

Linia marcată cu `(1)` este echivalentă cu următoarea linie:
```c++
    Derivata() : Baza() { std::cout << "Constructor Derivată\n"; }
```

În cazul claselor derivate, întâi se construiesc complet clasele de bază _în ordinea din definiția clasei derivate_,
apoi se construiește fiecare atribut al clasei derivate.

Dacă în clasa de bază nu avem constructor fără parametri, ce se întâmplă? Încercați să compilați codul următor:
```c++
#include <iostream>

class Baza {
private:
    int x;
public:
    Baza(int x_) : x(x_) { std::cout << "Constructor Bază\n"; }
    ~Baza() { std::cout << "Destructor Bază\n"; }
};

class Derivata : Baza {
public:
    Derivata() { std::cout << "Constructor Derivată\n"; }
    ~Derivata() { std::cout << "Destructor Derivată\n"; }
};

int main() {
    Baza b;
    std::cout << "main: După b, înainte de d\n";
    Derivata d;
    std::cout << "main: sfârșit\n";
}
```

Înlocuiți constructorul din derivată cu următorii constructori:
```c++
    Derivata() : Baza(1)              { std::cout << "Constructor 1 Derivată\n"; }
    Derivata(int x) : Baza(x)         { std::cout << "Constructor 2 Derivată\n"; }
    Derivata(const Baza& b) : Baza(b) { std::cout << "Constructor 3 Derivată\n"; }
```

Construiți obiecte în main astfel încât să se apeleze toți acești constructori.
Pentru ultimul constructor se mai apelează constructorul de inițializare din bază?

#### Atribute și funcții `private` și `protected`

Nu putem accesa atributul `x` sau funcția `f` din bază în clasa derivată:
```c++
#include <iostream>

class Baza {
private: // (1)
    int x;
    void f() { std::cout << "f\n"; }
public:
    Baza(int x_) : x(x_) { std::cout << "Constructor Bază: " << x << "\n"; f(); }
};

class Derivata : Baza {
public:
    Derivata() : Baza(1) { std::cout << "Constructor 1 Derivată: " << x << "\n"; f(); }
};

int main() {
    Derivata d;
}
```

Înlocuiți `private` de la linia `(1)` cu `protected`.

**Atenție!**

- Nu dorim să facem toate atributele/funcțiile din bază `protected`, deoarece aceste atribute/funcții ar deveni
  "globale" la nivelul ierarhiei și riscăm să nu mai putem modifica ușor baza fără să stricăm derivatele.
  - Dacă facem funcții sau atribute `protected` sau `public` în bază, deși nu ar fi necesar, lăsăm posibilitatea
    ca aceste funcții și atribute să fie folosite în mod direct și în derivate.
  - Ulterior, dacă avem nevoie să modificăm baza, nu vom putea modifica atributele și funcțiile
    `protected`/`public` fără să fie să modificăm și derivatele.
  - **Acesta este motivul pentru care dorim să folosim cât mai mult atribute și funcții `private`!**
- Este bine să avem cât mai puține atribute/funcții `protected`, deoarece dacă este nevoie să modificăm
  atributele/detaliile de implementare din bază, aceste modificări nu vor afecta derivatele.
- Chiar dacă `Derivata` este un fel de `Baza`, clasele trebuie considerate complet independente
  când vine vorba de detaliile de implementare, adică tot ce nu este `public` (sau `protected`).
  - Astfel, `Baza` nu ar trebui să facă vizibile derivatelor toate detaliile de implementare,
    ci doar strict minimul necesar. 

#### Moștenire publică

Să revenim la codul de la început:
```c++
class Baza {};
class Derivata : Baza {};
```

Moștenirea de mai sus este echivalentă cu următorul cod:
```c++
class Baza {};
class Derivata : private Baza {};
```

Moștenirea poate fi `private` (implicit), `protected` sau `public`. Tipul de moștenire determină modul de acces
al atributelor și funcțiilor din bază prin intermediul unui obiect de tip derivat.

**Exerciții:**
- Încercați să compilați codul de mai jos și urmăriți mesajele de eroare.
- Înlocuiți în codul de mai jos moștenirea `private` cu una `protected` și încercați să compilați din nou.
- Urmăriți din nou mesajele de eroare, apoi folosiți moștenire `public`.
- Ce rânduri trebuie comentate acum pentru ca programul să compileze?
  - Ce mai trebuie comentat dacă moștenirea este `protected`?
  - Ce mai trebuie comentat dacă moștenirea este `private`?

```c++
#include <iostream>

class Baza {
private:
    int x;
    void f1() { std::cout << "f1\n"; }
protected:
    int y;
    void f2() { std::cout << "f2\n"; }
public:
    int z;
    void f3() { std::cout << "f3\n"; }
};

class Derivata : private Baza {
    void g() {
        f1();
        f2();
        f3();
        std::cout << x << "\n";
        std::cout << y << "\n";
        std::cout << z << "\n";
    }
};

int main() {
    Baza b;
    b.f1();
    b.f2();
    b.f3();
    std::cout << "---\n";
    Derivata d;
    d.f1();
    d.f2();
    d.f3();
}
```

**Concluzii despre sintaxă:**
- Funcțiile și atributele `private` din bază sunt inaccesibile din derivată, indiferent de tipul de moștenire.
- Funcțiile și atributele `protected` din bază devin `private` în derivată dacă moștenirea este `private`.
- Funcțiile și atributele `public` din bază vor avea tipul de acces dat de tipul de moștenire

Verificați cu ajutorul codului de mai sus că obțineți rezultatele din acest tabel:

| Tip de acces &rArr; <br> Moștenire &dArr; |  public   | protected | private |
|:------------------------------------------|:---------:|:---------:|:-------:|
| **public**                                |  public   | protected | private |
| **protected**                             | protected | protected | private |
| **private**                               |  private  |  private  | private |

Nu trebuie să rețineți tabelul de mai sus. Încercați să îl deduceți!

**Concluzii despre tipul de moștenire:**
- în majoritatea cazurilor vom folosi doar moștenire publică, deoarece dorim să păstrăm interfața din bază
  - dacă nu folosim moștenire publică, derivata ar deveni implicit mai restrictivă decât baza,
    încălcând ideea de "Derivata _este un fel de_ Bază"
- trebuie să știți despre celelalte tipuri de moșteniri pentru examen
- moștenirile `private` și `protected` nu există în alte limbaje și se folosesc în situații rare; detalii
  [aici](https://isocpp.org/wiki/faq/private-inheritance)

**Observații**

1. Specificatorii de acces din C++ sunt la nivel de clasă: putem accesa atributele private ale unui alt obiect
   al aceleiași clase. Nu putem accesa atributele private sau protected ale unui obiect de tip bază,
   deoarece este vorba de altă clasă.

2. În situații rare, putem modifica în derivate interfața din derivate folosind clauze `using`.
În exemplul de mai jos, funcția `f1` este protected în bază și devine publică în derivată,
iar funcția `f2` este publică în bază și devine privată în derivată.
```c++
class Baza {
protected:
    void f1() {}
public:
    void f2() {}
};

class Derivata : public Baza {
private:
    using Baza::f2;
public:
    using Baza::f1;
};

int main() {
    Derivata d;
    d.f1();
    //d.f2();
}
```

Modificați baza astfel încât `f1` să fie privată. Mai puteam folosi `using`? De ce da sau de ce nu?

În încheierea acestei secțiuni, menționez o sintaxă specifică C++ ca exemplu de "așa nu".
Adăugați în funcția `main` următoarele rânduri.
```c++
    d.Baza::f1();
    d.Baza::f2();
```

Care rând compilează și de ce?

Această sintaxă ne permite să accesăm în afara claselor funcții din bază prin intermediul derivatelor.
Totuși, dacă avem nevoie să facem asta, ar trebui să ne întrebăm de ce mai folosim un obiect de tip derivat și
nu direct un obiect de tip bază. Motivul pentru care am creat clasa derivată este tocmai pentru că nu ne convenea
implementarea din bază.

Asemănător cu multe alte elemente de sintaxă din C++, și sintaxa de mai sus poate fi utilă în situații rare.
Dacă aflați exemple de situații, vă rog să îmi spuneți și mie.

[//]: # (Iar dacă tot am zis de situații rare, să vorbim despre moștenirea multiplă.)
[//]: # (s-a mai întrebat și altcineva, dar tot nu am găsit utilitatea: https://stackoverflow.com/questions/14288594/)

#### Constructor de copiere, `operator=` (recapitulare)

```c++
class student {};
```

Să ne amintim câteva reguli ale limbajului. Dacă nu definim nimic, compilatorul generează:
- constructor fără parametri: `student()`
- constructor de copiere: `student(const student& other)`
- operator= de copiere: `student& operator=(const student& other)`
- destructor: `~student()`
- constructor de mutare: `student(student&& other)`
- operator= de mutare: `student& operator=(student&& other)`


Dacă scriem orice fel de constructor (cu sau fără parametri), nu se mai generează constructorul fără parametri:
```c++
class student {
public:
    student(int) {}
};

int main() {
    student st; // eroare
}
```

Compilatorul generează în continuare funcțiile speciale dacă nu le suprascriem:
```c++
class student {
public:
    student() {}
};

int main() {
    student s1; // constr definit de noi
    student s2{s1}; // constr de copiere
    student s3{std::move(s2)}; // constr de mutare
    s1 = s2; // op= de copiere
    s2 = std::move(s3); // op= de mutare
    // destructor
}
```

Dacă definim doar destructorul, se generează constructorul fără parametri. cc și op= de copiere sunt generați,
dar sunt deprecated deoarece încalcă regula celor trei. Nu avem operațiile de mutare.

Aceleași reguli se aplică și dacă ne definim doar cc sau doar op= de copiere, deoarece s-ar încălca regula celor trei.

```c++
class student {
public:
    ~student() {}
};

int main() {
    student s1; // compilează
    student s2{s1}; // constr de copiere; compilează, dar este deprecated
    // student s3{std::move(s2)}; // constr de mutare; nu compilează
    s1 = s2; // op= de copiere; compilează, dar este deprecated
    // s2 = std::move(s3); // op= de mutare; nu compilează
    // destructor
}
```

Corect ar trebui să definim toate cele trei funcții dacă ne definim una dintre ele explicit:
```c++
class student {
public:
    ~student() {}
    student(const student& other) = default;
    student& operator=(const student& other) = default;
};
```

Dacă ne definim constructor de mutare sau operator= de mutare, nu mai avem cc și op= de copiere.

**Concluzie**

De cele mai multe ori, constructorul de copiere, operator= de copiere și destructorul generate de compilator
fac ce trebuie. Corect este să nu le scriem deloc pe niciunele sau să le scriem pe toate 3 (sau 5) cu `=default`.

În ceea ce privește operațiile de mutare, acestea sunt folosite pentru a evita copieri inutile. Opțiunile ar fi:
- păstrăm toate cele 5 operații: compilatorul va alege când e mai bine să copieze sau să mute
  - ori nu definim niciuna dintre cele 5 operații, ori le definim pe toate
- definim mutările și implicit ștergem copierile
- ștergem copierile și implicit dezactivăm și mutările
- destructorul este generat implicit în toate cazurile de mai sus
  - îl putem defini pentru simetrie doar dacă definim și copieri sau mutări

Detalii și sursa de inspirație [aici](https://howardhinnant.github.io/bloomberg_2016.pdf).

#### Constructor de copiere, `operator=` pentru derivate

În exemplul de mai jos, am suprascris toate funcțiile speciale (cc, op=, destructor) pentru a observa când se apelează.
Totuși, nu le-am suprascris corect pe toate. Încercați să rulați codul. Compilează?

```c++
#include <iostream>
#include <string>
#include <utility>

class student {
    std::string nume;
public:
    student(std::string nume_) : nume(std::move(nume_)) { std::cout << "constructor student: " << nume << "\n"; }
    student(const student& other) : nume(other.nume) { std::cout << "cc student: " << nume << "\n"; }
    student& operator=(const student& other) { nume = other.nume; std::cout << "op= student: " << nume << "\n"; return *this; }
    ~student() { std::cout << "destructor student: " << nume << "\n"; }
    friend std::ostream& operator<<(std::ostream& os, const student& st) { os << "st: " << st.nume << "\n"; return os; }
};

class profesor {
    std::string nume;
public:
    profesor(std::string nume_) : nume(std::move(nume_)) { std::cout << "constructor profesor: " << nume << "\n"; }
    profesor(const profesor& other) : nume(other.nume) { std::cout << "cc profesor: " << nume << "\n"; }
    profesor& operator=(const profesor& other) { nume = other.nume; std::cout << "op= profesor: " << nume << "\n"; return *this; }
    ~profesor() { std::cout << "destructor profesor: " << nume << "\n"; }
    friend std::ostream& operator<<(std::ostream& os, const profesor& p) { os << "prof: " << p.nume << "\n"; return os; }
};

class curs {
    profesor prof;
public:
    curs(const profesor& prof_) : prof(prof_) { std::cout << "constructor curs: " << prof << "\n"; }
    curs(const curs& other) : prof(other.prof) { std::cout << "cc curs: " << prof << "\n"; }
    curs& operator=(const curs& other) { prof = other.prof; std::cout << "op= curs: " << prof << "\n"; return *this; }
    ~curs() { std::cout << "destructor curs: " << prof << "\n"; }
    friend std::ostream& operator<<(std::ostream& os, const curs& c) { os << "curs: " << c.prof << "\n"; return os; }
};

class curs_obligatoriu : public curs {
    student st;
public:
    curs_obligatoriu(const student& st_) : st(st_) { std::cout << "constructor curs_obligatoriu: " << st << "\n"; }
    curs_obligatoriu(const curs_obligatoriu& other) : st(other.st) { std::cout << "cc curs_obligatoriu: " << st << "\n"; }
    curs_obligatoriu& operator=(const curs_obligatoriu& other) { st = other.st; std::cout << "op= curs_obligatoriu: " << st << "\n"; return *this; }
    ~curs_obligatoriu() { std::cout << "destructor curs_obligatoriu: " << st << "\n"; }
    friend std::ostream& operator<<(std::ostream& os, const curs_obligatoriu& c) { os << "curs_obligatoriu: " << c.st << "\n"; return os; }
};

int main() {
    student s{"a"};
    profesor p{"b"};
    curs_obligatoriu co{s};
}
```

Orice constructor al unei clase derivate definit explicit de noi apelează implicit constructorul **fără parametri**
al clasei de bază, indiferent dacă e vorba de constructori de inițializare, de copiere sau de alt fel.

Dacă adăugăm următorul constructor public în clasa `curs`, codul va compila. Programul funcționează corect acum?
```c++
    curs() : prof("prof") { std::cout << "constructor implicit curs\n"; }
```

Răspunsul este NU și primim și următorul warning (îl primeam și înainte):
```
main.cpp: In copy constructor ‘curs_obligatoriu::curs_obligatoriu(const curs_obligatoriu&)’:
main.cpp:40:5: warning: base class ‘class curs’ should be explicitly initialized in the copy constructor [-Wextra]
     40 |     curs_obligatoriu(const curs_obligatoriu& other) : st(other.st) { std::cout << "cc curs_obligatoriu: " << st << "\n"; }
        |     ^~~~~~~~~~~~~~~~
```

Pentru a remedia situația, trebuie să apelăm constructorul de copiere al clasei de bază. Acesta se va ocupa de
copierea atributelor din bază. Putem apela constructorul de copiere în acest mod chiar dacă este generat de compilator.

Noul constructor de copiere din clasa derivată va fi:
```c++
    curs_obligatoriu(const curs_obligatoriu& other) : curs(other), st(other.st) {
        std::cout << "cc curs_obligatoriu: " << st << "\n";
    }
```

Acum copierea se efectuează corect. Întâi se construiesc complet atributele din bază, iar abia apoi se construiesc
și atributele din clasa derivată.

Putem apela constructorul de copiere al clasei de bază cu un obiect de tip derivat deoarece
**orice obiect de tip derivată _este un fel de_ obiect de tip bază**, deci orice referință de tip `curs_obligatoriu`
poate fi convertită în mod implicit la o referință de tip `curs`.

Dacă nu suprascriem cc într-o clasă derivată, acesta va funcționa corect și va apela cc din bază, iar apoi
va apela cc pentru fiecare atribut din clasa derivată.

Indiferent de ordinea din lista de inițializare, ordinea inițializărilor este cea descrisă mai sus!

Dacă inversăm ordinea din lista de inițializare:
```c++
    curs_obligatoriu(const curs_obligatoriu& other) :  st(other.st), curs(other) {
        std::cout << "cc curs_obligatoriu: " << st << "\n";
    }
```

Primim warning, întrucât ordinea din cod nu coincide cu ordinea reală a execuției codului și induce confuzie.

```
main.cpp: In copy constructor ‘curs_obligatoriu::curs_obligatoriu(const curs_obligatoriu&)’:
main.cpp:37:13: warning: ‘curs_obligatoriu::st’ will be initialized after [-Wreorder]
     37 |     student st;
        |             ^~
main.cpp:40:78: warning:   base ‘curs’ [-Wreorder]
     40 |     curs_obligatoriu(const curs_obligatoriu& other) : st(other.st),curs(other) { std::cout << "cc curs_obligatoriu: " << st << "\n"; }
        |                                                                              ^
main.cpp:40:5: warning:   when initialized here [-Wreorder]
     40 |     curs_obligatoriu(const curs_obligatoriu& other) : st(other.st),curs(other) { std::cout << "cc curs_obligatoriu: " << st << "\n"; }
        |     ^~~~~~~~~~~~~~~~
```

Revenind la varianta anterioară a constructorului de copiere, funcționează corect tot programul de mai sus?

**Nu!**

Funcția operator= din derivată are același defect observat în constructorul de copiere, însă nu mai primim warning.
Codul pe care îl avem acum nu ne permite să demonstrăm acest lucru.

Vom adăuga următorul constructor în clasa `curs_obligatoriu`:
```c++
    curs_obligatoriu(const profesor& prof_) : curs(prof_), st("stud") {
        std::cout << "constructor curs_obligatoriu 2: " << prof_ << "\n";
    }
```

Iar în funcția `main` vom adăuga:
```c++
    std::cout << "-----\n";
    curs_obligatoriu co2{p}, co3{co2}, co4{profesor{"z"}};
    std::cout << co2 << " " << co3;
    std::cout << "----- op= (1) -----\n";
    co4 = co3;
    std::cout << "----- op= (2) -----\n";
    std::cout << co4 << " " << co3;
    std::cout << "-----\n";
```

Din mesajele de afișare ne interesează următorul fragment:
```
----- op= (2) -----
curs_obligatoriu: st: stud

 curs_obligatoriu: st: stud

-----
```

Pentru a observa bug-ul din `curs_obligatoriu::operator=`, este necesar să mai modificăm și afișarea pentru a afișa
atributele din bază:
```c++
    friend std::ostream& operator<<(std::ostream& os, const curs_obligatoriu& c) {
        os << static_cast<const curs&>(c);
        os << "curs_obligatoriu: " << c.st << "\n";
        return os;
    }
```

Trebuie să facem cast la clasa de bază pentru că un simplu `os << c` în interiorul funcției de mai sus ar
rezulta în apel recursiv infinit. Un cast de tip C (`os << (const curs&) c;`) nu ar exprima intenția la fel de bine
și ar fi mai nesigur.

Dacă rulăm programul din nou, ar trebui să observăm bug-ul:
```
----- op= (2) -----
curs: prof: z

curs_obligatoriu: st: stud

 curs: prof: b

curs_obligatoriu: st: stud

-----
```

Așadar, dacă suprascriem op= într-o clasă derivată, este necesar să apelăm în mod explicit op= al clasei de bază
pentru a copia (sau atribui) corect și atributele din clasa de bază:
```c++
    curs_obligatoriu& operator=(const curs_obligatoriu& other) {
        curs::operator=(other); // (1)
        // sau
        static_cast<curs&>(*this) = other; // (2)
        // sau
        curs& curs_ = *this; curs_ = other; // (3)

        st = other.st;
        std::cout << "op= curs_obligatoriu: " << st << "\n";
        return *this;
    }
```

Nu este necesară decât una dintre cele 3 variante de mai sus. La fel ca în cazul constructorului de copiere,
se efectuează o conversie implicită de la `curs_obligatoriu` la `curs`.

**Atenție!** Este necesar să folosim conversie la referințe, deoarece vrem ca și referința care vede doar
partea din bază să se refere la _aceleași_ obiecte.

Următorul cod ar crea un nou obiect temporar și ar face atribuirea părții din bază a lui `other`
în acest obiect temporar:
```c++
    curs_obligatoriu& operator=(const curs_obligatoriu& other) {
        curs curs_ = *this;
        curs_ = other;

        st = other.st;
        std::cout << "op= curs_obligatoriu: " << st << "\n";
        return *this;
    }
```

Dacă nu suprascriem op= într-o clasă derivată, acesta va funcționa corect și va apela op= din bază, iar apoi
va apela op= pentru fiecare atribut din clasa derivată.

**Concluzie**
- De cele mai multe ori **nu** avem nevoie să suprascriem cc și op=, nici pentru clase de bază, nici pentru derivate.
  Funcțiile cc și op= generate de compilator fac ce trebuie.
  - Dacă definim explicit cc/op= doar în bază, cc/op= din derivată generate de compilator vor apela cc/op= din bază.
  - Dacă definim explicit cc/op= doar în derivată, putem apela cc/op= din bază generate de compilator.
- Este necesar să suprascriem cc **și** op= doar în situații speciale. Singurele situații speciale în cazul nostru
  vor fi clasa/clasele în care avem atribute de tip pointer.

#### Exercițiu

Completați ierarhia de mai jos. Adăugați (o parte din) următoarele funcții/atribute ca să înțelegeți mai bine
ce se întâmplă:
- atribute `private` și `protected`
- constructori de inițializare, constructori de copiere, operator=, destructori
- funcții `private`, `protected` și `public`
- funcția main cu apeluri care să acopere tot ce ați definit mai sus

Folosiți oricât de multe mesaje de afișare considerați necesare.

```c++
class curs {};
class curs_obligatoriu : public curs {};
class curs_optional : public curs {};
```

### Funcții virtuale
#### Destructor
#### Interfață non-virtuală
#### Constructori virtuali
#### Funcție de afișare

#### Alte funcții virtuale

[//]: # (https://en.wikipedia.org/wiki/Call_super)

[//]: # (https://stackoverflow.com/a/30885842)

[//]: # (clone public, cc/op= protected, la fel pt cele de mutare)
[//]: # (https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-copy)
[//]: # (dilema cu cercul și elipsa)

#### Smart pointers
#### Dynamic cast

#### Copy and swap
#### RAII

#### Exercițiu

Adăugați și clasa următoare:
```c++
class curs_facultativ : public curs {};
```

Adăugați atribute și definiți tot ce este necesar în această clasă pentru a putea crea obiecte de acest tip.

Dacă ați implementat corect, ar trebui să modificați codul doar în main și în clasa definită acum.
Astfel, am demonstrat că moștenirea ne ajută să extindem codul existent _foarte ușor_, **fără modificări**
în codul care se folosește doar de interfața clasei de bază.

Partea dificilă este definirea adecvată a unei clase de bază. Întrucât cerințele se pot schimba pe parcurs,
proiectarea claselor se învață cel mai bine prin exercițiu și în timp.

### Excepții
#### Motivație

[//]: # (coduri de eroare, sintaxă, contraexemple)

#### Excepții predefinite
#### Ierarhie proprie

### Funcții și atribute statice

### Moștenire multiplă și virtuală

### Principiile SOLID

[//]: # (circle elipse problem)

[//]: # (### Fișiere header și fișiere sursă)

## Cerințe tema 2

Continuăm familiarizarea cu limbajul C++ (din nou) și învățăm alte noțiuni OOP de bază: moșteniri și excepții.

Cerințe comune:
- separarea codului din clase în fișiere header (`.h`/`.hpp` etc.) și surse (`.cpp` etc.)
  - clasele mici și legate între ele se pot afla în aceeași pereche de fișiere header-sursă
  - FĂRĂ using namespace std în fișiere `.h` la nivel global
    - pot fi declarații locale
- moșteniri
  - funcții virtuale (pure), constructori virtuali (clone)
    - funcțiile virtuale vor fi apelate prin pointeri la clasa de bază
    - pointerii la clasa de bază vor fi atribute ale altei clase, nu doar niște pointeri/referințe în main
  - apelarea constructorului din clasa de bază
  - smart pointers
  - dynamic_cast
- suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
- excepții
  - ierarhie proprie (cu baza std::exception sau derivată din std::exception)
  - utilizare cu sens: de exemplu, throw în constructor, try/catch în main
- funcții și atribute statice
- STL
- un tag de git pe un commit cu cod stabil
- fără variabile globale
- cât mai multe `const`, testat/apelat tot codul public de interes din `main`

Cerințe specifice:
- implementarea a două funcționalități noi specifice temei; pot fi folosite funcții virtuale în acest scop

#### Termen limită
- săptămâna 7 (20 noiembrie/2 aprilie): progres parțial
- **săptămâna 8 (27 noiembrie/9 aprilie): tema 2 gata**
- săptămâna 9 (4 decembrie/16 aprilie): (eventuale) modificări în urma feedback-ului
