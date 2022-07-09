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

Nu trebuie să rețineți acest tabel. Încercați să îl deduceți!

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
Un exemplu ar fi la funcțiile virtuale pure (detalii în [secțiunea respectivă](#funcții-virtuale)).
Dacă aflați alte exemple de situații, vă rog să îmi spuneți și mie.

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
- op= din clasa de bază este moștenit de către derivată, dar este ascuns
  - în curs este greșit: dacă nu era moștenit, nu îl puteam apela din derivată

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

Cuvântul cheie `virtual` poate fi folosit în C++ în două situații:
- funcții membre virtuale într-o clasă
- moșteniri virtuale pentru clase de bază în cazul moștenirilor multiple

În această secțiune vorbim doar despre funcții virtuale.
Funcțiile virtuale trebuie să aibă **același antet** și în bază, și în derivate.
Există o singură excepție de la regulă pe care o discutăm mai târziu.

Există câteva funcții într-o clasă care nu pot fi funcții virtuale:
- constructorii
- funcțiile statice: doar funcțiile membre pot fi virtuale
- funcțiile friend: același motiv ca mai sus

Pot fi virtuali și operatorii binari, dar în practică nu ne ajută să îi facem virtuali din
cauză că trebuie să păstrăm același antet:
- nu am putea primi ca argument un obiect de tip derivat
- nu s-ar păstra simetria între operanzi
- nu este nevoie să facem operatorii virtuali ca să apelăm în interiorul lor funcții virtuale

Exemple de operatori pe care nu are rost să îi supraîncărcăm:
- `operator=` și alți operatori de atribuire
- operatori de comparație și de egalitate
- operatori aritmetici și logici

---

Așadar, lăsând la o parte restricțiile de mai sus, orice funcție membru poate fi virtuală:
```c++
class student {};

class curs {
private:
    virtual void f() {}
protected:
    virtual int f(int x) { return x + 1; }
public:
    virtual student h() { return student{}; }
};
```

Din punctul de vedere al sintaxei, nu contează pentru declarația unei funcții virtuale
specificatorul de acces, lista de parametri sau tipul de retur.

**Întrebare preliminară 1: ce sizeof are o clasă goală?**

```c++
#include <iostream>

class cls {};

int main() {
    std::cout << "sizeof(cls): " << sizeof(cls) << "\n";

    cls c1, c2;
    std::cout << &c1 << " " << &c2 << "\n";
    cls *c3 = new cls, *c4 = new cls;
    std::cout << c3 << " " << c4 << "\n";
    delete c3;
    delete c4;
}
```

**De ce 1 și nu 0?**

Deoarece compilatorul trebuie să garanteze că orice obiect nou are o adresă diferită.

**Întrebare preliminară 2: ce sizeof au următoarele clase?**

Vom presupune `sizeof(int) == 4` și `sizeof(double) == sizeof(long long) == 8`. Prin definiție, `sizeof(char)` este 1.

```c++
#include <iostream>

class cls1 {
    char t;
    int u;
    double v;
    char w;
    long long x;
};

class cls2 {
    char t;
    char w;
    int u;
    double v;
    long long x;
};
class cls3 {
    double v;
    long long x;
    int u;
    char t;
    char w;
};

int main() {
    std::cout << "sizeof(cls1): " << sizeof(cls1) << "\n";
    std::cout << "sizeof(cls2): " << sizeof(cls2) << "\n";
    std::cout << "sizeof(cls3): " << sizeof(cls3) << "\n";
}
```

Fiecare câmp al unei clase trebuie să fie aliniat la multiplu de `sizeof` al acelui tip de date pentru a
putea calcula rapid adresa din memorie a acelui câmp. Din acest motiv, dacă avem un câmp anterior cu `sizeof`
diferit și următoarea adresă nu este multiplu de `sizeof`-ul câmpului următor, compilatorul adaugă bytes (sau biți)
pentru aliniere (padding).

Așadar, obiectele din clasele de mai sus sunt reprezentate în memorie în felul următor:
```c++
class cls1 {
    char t;      // 1 byte
                 // 3 bytes (padding)
    int u;       // 4 bytes
    double v;    // 8 bytes
    char w;      // 1 byte
                 // 7 bytes (padding)
    long long x; // 8 bytes
};

class cls2 {
    char t;      // 1 byte
    char w;      // 1 byte
                 // 2 bytes (padding)
    int u;       // 4 bytes
    double v;    // 8 bytes
    long long x; // 8 bytes
};
class cls3 {
    double v;    // 8 bytes
    long long x; // 8 bytes
    int u;       // 4 bytes
    char t;      // 1 byte
    char w;      // 1 byte
                 // 2 bytes (padding)
};
```

Ca extensie non-standard a limbajului, multe compilatoare oferă directiva de preprocesare `#pragma pack(n)`,
unde `n` reprezintă multiplul la care să se facă alinierea. Pentru exemplul de mai sus, `sizeof`-ul fiecărei
clase de mai devreme va fi 22.

Dacă mai aveam un câmp `char` în clasă, am avea `sizeof` tot 24, deoarece mai trebuie un byte de padding
ca să fie multiplu de 2 (parametrul din directiva `#pragma pack`). Dacă folosim `#pragma pack(1)`,
obținem 23 de bytes.

Această directivă ne ajută să obținem consum mai mic de memorie, sacrificând timpul de execuție: adresele
câmpurilor obiectelor se calculează mult mai lent, iar asta se întâmplă de fiecare dată când accesăm un câmp.

**Exercițiu:** definiți minim 2-3 clase folosind compunere și moștenire, fiecare cu minim un atribut. Reordonați
și/sau schimbați atributele pentru a înțelege regulile de aliniere.

---

Revenind la funcții virtuale...

**De ce nu sunt toate funcțiile automat virtuale?**

```c++
#include <iostream>

class curs_nv1 {};

class curs_nv2 {
public:
    void f() {}
};

class curs_v1 {
public:
    virtual void f() {}
};

class curs_v2 {
public:
    virtual void f() {}
    virtual void g() {}
};

int main() {
    std::cout << "sizeof(curs_nv1): " << sizeof(curs_nv1) << "\n";
    std::cout << "sizeof(curs_nv2): " << sizeof(curs_nv2) << "\n";
    std::cout << "sizeof(curs_v1): " << sizeof(curs_v1) << "\n";
    std::cout << "sizeof(curs_v2): " << sizeof(curs_v2) << "\n";
}
```

Câteva observații:
- clasele `curs_nv2` și `curs_v1` sunt aproape identice și diferă doar prin cuvântul cheie `virtual`
- clasele `curs_nv1` și `curs_nv2` au același `sizeof`, nu contează numărul de funcții
- clasele `curs_v1` și `curs_v2` au același `sizeof`, nu contează numărul de funcții

Virtualizarea se activează dacă avem _cel puțin o funcție virtuală_. Dacă avem o funcție virtuală, am plătit
costul activării virtualizării și putem marca oricâte alte funcții cu `virtual` fără să plătim un cost suplimentar.

Pe de altă parte, nu vrem să folosim virtualizarea în orice clasă, întrucât costul nu este neglijabil
în programe mari: dacă avem 100 de milioane de obiecte, costul acestui virtual înseamnă 400-800 MB.

**Dimensiunea unui obiect crește cu 4 sau cu 8 bytes dacă avem cel puțin o funcție virtuală?**

Virtualizarea funcțiilor adaugă un pointer ascuns către un vector de (pointeri la) funcții. Obiectul va avea
atâția bytes în plus câți are un pointer pe acel sistem de calcul.

Sizeof-ul unui pointer este de obicei 4 bytes pe sisteme de operare pe 32 de biți sau dacă folosim un compilator
care generează executabile pe 32 de biți. Pe sisteme de operare pe 64 de biți, sizeof-ul unui pointer
este de obicei 8 bytes.

Acesta este motivul pentru care limitarea de RAM este de 4 GB pe sisteme de operare pe 32 de biți sau pentru
executabile pe 32 de biți. Pe de altă parte, programele pe 64 de biți consumă mai multă memorie.

În Java, consumul de memorie este (mult) mai mare deoarece toate funcțiile sunt virtuale.

**Ce face `virtual` în cazul funcțiilor?**

Virtualizarea funcțiilor ne permite să suprascriem (înlocuim) implementarea unei funcții din bază într-o clasă
derivată:
```c++
#include <iostream>

class baza {
public:
    virtual void f() { std::cout << "f baza\n"; }
};

class derivata : public baza {
public:
    virtual void f() { std::cout << "f derivata\n"; }
};

void g1(baza& b) {
    b.f();
}

void g2(baza* b) {
    b->f();
}

void h(baza b) {
    b.f();
}

int main() {
    baza b;
    derivata d;
    std::cout << "----- g1(b) -----\n";
    g1(b);
    std::cout << "----- g2(&b) -----\n";
    g2(&b);
    std::cout << "----- h(b) -----\n";
    h(b);
    std::cout << "----- g1(d) -----\n";
    g1(d);
    std::cout << "----- g2(&d) -----\n";
    g2(&d);
    std::cout << "----- h(d) -----\n";
    h(d);
}
```

Observăm faptul că virtualizarea este folosită în funcțiile `g1` și `g2` atunci când transmitem din main
obiectul `d`, însă nu și în cazul funcției `h`.

Virtualizarea apelează funcția virtuală din clasa _cea mai derivată_ dacă folosim _referințe_ sau _pointeri_
către bază! Dacă folosim direct un obiect de tip derivat, se face un apel normal de funcție
și nu avem nevoie de `virtual`.

În cazul funcției `h`, transmiterea parametrului este prin valoare, deci se apelează constructorul de copiere
pentru clasa `baza`! Acest constructor are nevoie să construiască doar un obiect de tip `baza`, deci va prelua
doar partea din clasa de bază a obiectului `d` din funcția main. Situațiile de acest fel poartă numele de
**object slicing** (felierea obiectului) și reprezintă bug-uri în multe cazuri.

Pentru a documenta mai bine codul și pentru a preveni diverse defecte, se recomandă folosirea cuvântului cheie
`override` (sau mai rar `final`) pentru a verifica _la compilare_ că antetul din derivată se potrivește cu
antetul din bază. Astfel, documentăm că funcția este suprascrisă și nu supraîncărcată de o funcție cu antet similar,
iar compilatorul ne dă eroare la compilare.

Cuvântul cheie `final` apare în următoarele contexte:
- clasele marcate cu `final` nu pot fi moștenire
- funcțiile virtuale marcate cu `final` nu pot fi suprascrise

Cuvântul cheie `final` este folosit foarte rar deoarece nu putem prezice viitorul și de multe ori avem nevoie
să suprascriem funcționalități existente. Acest `final` ne-ar pune bețe în roate și ar trebui să facem cârpeli
(de exemplu mult cod duplicat). Din punctul meu de vedere, este o greșeală istorică.

În derivate nu are rost să folosim și `virtual`, și `override`:
- `virtual` folosim doar în bază pentru a documenta ce ar putea fi suprascris
- `override` implică `virtual` în derivate
  - am folosi `virtual` într-o derivată doar pentru funcții din derivată care nu apar
    în bază și ar fi suprascrise de o clasă și mai derivată
- dacă folosim doar `virtual` în derivată, nu este imediat evident care dintre aceste funcții suprascriu
- dacă nu folosim nici `virtual`, nici `override` în derivate, riscăm să supraîncărcăm funcția în loc să o suprascriem
  ceva din bază și care sunt specifice doar derivatei
- `final` implică `virtual` și `override` în derivate
  - totuși, nu are sens să facem funcție virtuală `final` în bază, deci am folosi `final` doar în derivate

Un exemplu concret de funcții virtuale:
```c++
class curs {
    int lab;
protected:
    int examen;
public:
    curs(int lab_, int examen_) : lab(lab_), examen(examen_) {}
    virtual double nota_lab() const { return lab; }
    virtual double nota_finala() const { return (nota_lab() * 0.5) + (examen * 0.5); }
};

class curs_obligatoriu : public curs {
public:
    curs_obligatoriu(int lab_, int examen_) : curs(lab_, examen_) {}
    double nota_finala() const override { return (nota_lab() * 0.3) + (examen * 0.7); }
};

class curs_cu_bonus : public curs {
    int bonus;
public:
    curs_cu_bonus(int lab_, int examen_, int bonus_) : curs(lab_, examen_), bonus(bonus_) {}
    double nota_finala() const override { return (nota_lab() * 0.4) + (examen * 0.6) + (bonus / 10); }
};
```

În cazul tuturor claselor, implementarea cea mai derivată pentru funcția `nota_lab` este în clasa de bază:
o clasă nu este obligată să suprascrie toate funcțiile virtuale.

Funcțiile virtuale trebuie să păstreze antetul, inclusiv partea cu `const` (dacă funcția este `const`).

**Exercițiu:** adăugați funcția `main` și încă o funcție care să primească pointer sau referință la `curs`.
Construiți obiecte în `main` și apelați funcția menționată anterior pentru a ilustra virtualizarea.
Creați o nouă clasă derivată în care să suprascrieți doar funcția `nota_lab`.

În secțiunea următoare vom vedea în ce situații chiar este util să folosim funcții virtuale.

În alte situații, "are sens" să activăm virtualizarea doar dacă nu știm ce alte optimizări de memorie să facem
în viitor și vrem ceva low-effort. Cu alte cuvinte, implementăm ineficient și punem `virtual` ca să avem
mai târziu ce să reparăm 🙃️

#### Destructor

Folosim destructor virtual doar dacă avem nevoie și de alte funcții virtuale. Nu este obligatoriu să facem
destructorii virtuali, chiar dacă facem moșteniri!

Aceste remarci au condus la următoarea convenție:
_destructorul ar trebui să fie public și virtual sau protected și non-virtual_.

Să luăm pe rând cele două cazuri.

**Destructor public și virtual**

Să ne amintim ce fac operatorii `new` și `delete`:
- `new` apelează `malloc` pentru a aloca dinamic o zonă de memorie, apoi apelează constructorul
- `delete` apelează destructorul, apoi apelează `free` pentru a elibera zona de memorie

Avem nevoie să facem destructorul virtual dacă avem nevoie să alocăm dinamic obiecte din clase derivate
la care să ne referim prin pointeri de bază:
```c++
#include <iostream>

class baza_nv {
public:
    ~baza_nv() { std::cout << "destructor baza_nv\n"; }
};

class derivata_nv : public baza_nv {
public:
    ~derivata_nv() { std::cout << "destructor derivata_nv\n"; }
};

class baza_v {
public:
    virtual ~baza_v() { std::cout << "destructor baza_v\n"; }
};

class derivata_v : public baza_v {
public:
    ~derivata_v() override { std::cout << "destructor derivata_v\n"; }
};

void non_virtuale() {
    std::cout << "----- begin non_virtuale() -----\n";
    baza_nv b1;
    derivata_nv d1;
    baza_nv* b2 = new baza_nv;
    delete b2;
    std::cout << "----- delete 1 -----\n";
    derivata_nv* d2 = new derivata_nv;
    delete d2;
    std::cout << "----- delete 2 -----\n";
    baza_nv* b3 = new derivata_nv;
    delete b3;
    std::cout << "----- delete 3 -----\n";
    //derivata_nv* d3 = new baza_nv;
    //delete d3;
    std::cout << "----- end non_virtuale() -----\n";
}

void virtuale() {
    std::cout << "----- begin virtuale() -----\n";
    baza_v b1;
    derivata_v d1;
    baza_v* b2 = new baza_v;
    delete b2;
    std::cout << "----- delete 1 -----\n";
    derivata_v* d2 = new derivata_v;
    delete d2;
    std::cout << "----- delete 2 -----\n";
    baza_v* b3 = new derivata_v;
    delete b3;
    std::cout << "----- delete 3 -----\n";
    //derivata_v* d3 = new baza_v;
    //delete d3;
    std::cout << "----- end virtuale() -----\n";
}

int main() {
    non_virtuale();
    std::cout << "----- main 1 -----\n";
    virtuale();
    std::cout << "----- main 2 -----\n";
}
```

Singura diferență dintre clasele `baza_nv` și `baza_v` este cuvântul cheie `virtual`. Observăm că apar
probleme la apelarea destructorilor atunci când folosim `delete` dacă ne referim la un obiect derivat
prin pointer către bază:
- dacă destructorul din bază nu este virtual, obiectul vede doar implementarea destructorului din bază
- dacă destructorul din bază este virtual, `delete` vede implementarea cea mai derivată a destructorului
  - întrucât toate clasele primesc din partea compilatorului un destructor, orice derivată are destructor propriu
  - se va apela în mod corect cel mai derivat destructor, iar abia apoi destructorii claselor de bază

**Pointerii și referințele către bază văd doar funcțiile din bază!** Dacă aceste funcții sunt virtuale,
se apelează la momentul execuției funcția cea mai derivată a tipului efectiv al obiectului.

Dacă avem o funcție virtuală, am plătit deja costul virtualizării, deci este gratuit să facem și
destructorul virtual.

Dacă uităm să facem destructorul virtual, deși ar fi trebuit, **nu se apelează toți destructorii!**

Acest aspect este deosebit de grav dacă în destructorii din derivate eliberăm resurse.

Are sens să facem destructorii virtuali doar dacă avem și alte funcții virtuale.
Reciproca nu este adevărată!

Putem avea funcții virtuale fără să facem și destructorii virtuali. Totuși, nu văd utilitatea acestei abordări,
deoarece nu pot fi reținute decât adresele unor variabile locale și apare foarte ușor riscul de
referințe/pointeri agățate/agățați (dangling reference/pointer). Poate avea sens atunci când avem
legături între clase în ambele direcții, dar tot mi se pare forțat.
Dacă găsiți un exemplu _cu sens_, vă rog să îmi spuneți și mie.

**Destructor protected și non-virtual**

Pentru situațiile în care doar vrem să grupăm atribute și funcționalități comune, însă nu avem nevoie de
funcții virtuale și am folosi doar clase derivate, avem posibilitatea să nu plătim prețul virtualizării.

Din moment ce nu avem funcții virtuale, nici destructorul nu este nevoie să fie virtual.

Totuși, întrucât nu vrem să construim decât obiecte din clase derivate, destructorul nu trebuie să fie public:
dacă destructorul unei clase nu este public, nu avem voie să construim obiecte din acea clasă, deoarece
resursele asociate unui astfel de obiect nu ar putea fi eliberate.

Destructorul nu poate fi privat, deoarece trebuie apelat de clasele derivate. Prin urmare, destructorul trebuie
să fie protected. Dacă suntem paranoici, putem face protected și constructorii din bază.
```c++
#include <iostream>
#include <vector>

class student {
    std::vector<int> note;
protected:
    ~student() { std::cout << "destr student\n"; }
    //~student() = default;
public:
    double medie() {
        double medie_ = 0;
        for(auto nota : note)
            medie_ += nota;
        return medie_ / note.size();
    }
};

class student_licenta : public student {
    long long motivatie;
public:
    ~student_licenta() { std::cout << "destr student_licenta\n"; }
};

class student_master : public student {
    short motivatie;
public:
    ~student_master() { std::cout << "destr student_master\n"; }
};

int main() {
    //student st;
    student_licenta sl1;
    student_master sm1;
}
```

Folosim abordarea descrisă mai devreme dacă vrem să forțăm doar crearea de obiecte derivate și nu avem nevoie de
funcții virtuale.

**Exercițiu:** afișați sizeof-urile claselor de mai sus. Comparați aceste sizeof-uri dacă ați face
destructorul virtual (dar tot protected). Opțional, completați codul cu ce mai doriți:
constructori, funcții ajutătoare etc.

**Nu apelăm funcții virtuale în constructori și destructori!**

Această regulă este specifică limbajului C++. Dacă apelăm funcții virtuale în constructori/destructori, avem
comportament nedefinit, deci 💥️

Detalii [aici](https://en.cppreference.com/w/cpp/language/virtual#During_construction_and_destruction) și
[aici](https://isocpp.org/wiki/faq/strange-inheritance#calling-virtuals-from-ctors).

În limbaje interpretate se pot apela fără probleme funcții virtuale în constructori.

#### Funcții virtuale pure

Funcțiile virtuale ne oferă posibilitatea de a schimba implementarea din bază atunci când definim o clasă derivată.
Astfel, extindem codul clasei de bază fără să fie necesare modificări în clasa de bază sau în alte clase
care folosesc doar pointeri sau referințe la clasa de bază.

În situațiile în care este imposibil să furnizăm un comportament implicit sau nu are sens să creăm obiecte
din clasa de bază, declarăm în clasa de bază funcții virtuale pure:
```c++
class baza {
public:
    virtual void f() = 0;
};

int main() {
    // baza b;
}
```

O clasă cu cel puțin o funcție virtuală pură se numește clasă abstractă. Nu avem voie să creăm obiecte
din clase abstracte.

```c++
class baza {
public:
    virtual void f() = 0;
    virtual void g() const = 0;
};

class derivata1 : public baza {};

class derivata2 : public derivata1 {
public:
    void f() override { std::cout << "f d2\n"; }
};

class derivata3 : public derivata2 {
public:
    void g() const override { std::cout << "g d3\n"; }
};

class derivata4 : public baza {
public:
    void f() override { std::cout << "f d4\n"; }
    void g() const override { std::cout << "g d4\n"; }
};
```

Dacă nu suprascriem toate funcțiile virtuale pure într-o clasă derivată, derivata este la rândul său clasă abstractă.
În exemplul anterior, clasele `baza`, `derivata1` și `derivata2` sunt clase abstracte.

Exemplu concret:
```c++
#include <string>
#include <algorithm> // std::max

class curs {
    std::string nume;
public:
    virtual double nota_finala() const = 0;
};

class curs_obligatoriu : public curs {
    double laborator;
    double examen;
    bool seminar;
public:
    double nota_finala() const override {
        return laborator * 0.4 + seminar * 0.1 + examen * 0.5;
    }
};

class curs_optional : public curs {
    int nr_raspunsuri;
    double nota_prezentare;
public:
    double nota_finala() const override {
        return std::max(nr_raspunsuri, 10) * 0.1 + nota_prezentare;
    }
};
```

În acest exemplu, fiecare clasă derivată trebuie să își definească formula pentru calculul notei finale.
Probabil am putea crea o formulă generală, însă dacă formula devine prea complicată, acesta este un indiciu
că ne-ar ajuta mai mult niște funcții virtuale.

În plus, trebuie să ne gândim și cât de ușor este să extindem codul existent prin adăugarea de noi clase derivate.
Dacă ar trebui să rescriem formula generală, riscăm să stricăm și ce mergea deja. Cu funcțiile virtuale separăm
implementările claselor derivate și este mult mai ușor să facem modificări în mod independent, iar impactul unor
posibile defecte este mult mai mic.

Pentru simplitate, am omis constructorii, destructorul virtual în bază, funcția main și afișările.

---

Există și situații când o parte din implementare se repetă în toate derivatele, dar tot vrem să forțăm
derivatele să suprascrie funcția, deci trebuie să fie funcție virtuală pură.
În acest caz, este util să avem în clasa de bază o implementare implicită, chiar dacă o suprascriem:
```c++
class curs {
    int teme;
    double test;
public:
    virtual double nota_laborator() const = 0;
};

double curs::nota_laborator { return teme * 0.5 + test * 0.5; }

class curs_greu : public curs {
public:
    double nota_laborator() const override {
        double nota_finala = curs::nota_laborator();

        if(nota_finala < 5)
            return 0;
        return nota_finala;
    }
};
```

Totuși, abordarea de mai sus nu este recomandată dacă ajungem să avem multe derivate în care doar apelăm
implementarea din bază:
```c++
// AȘA NU!!!!!

class curs_mediu : public curs {
public:
    double nota_laborator() const override { return curs::nota_laborator(); }
};

class curs_simplu : public curs {
public:
    double nota_laborator() const override { return curs::nota_laborator(); }
};
```

Există mai multe alternative pentru a evita această repetiție și pentru a avea în continuare o clasă de bază
abstractă:
- folosim funcții virtuale pure doar pentru partea din formulă care variază
  - ar trebui ca această parte să varieze în majoritatea derivatelor, altfel ne întoarcem de unde am plecat
- facem toți constructorii protected
  - din moment ce avem funcții virtuale, destructorul trebuie să fie public și virtual
  - există riscul ca atunci când adăugăm un nou constructor să uităm să îl facem protected
- facem destructorul din bază public și virtual pur

Destructorul virtual pur este cea mai la îndemână soluție când nu avem ce altă funcție să facem virtuală pură.

Cea mai frecventă eroare este următoarea:
```c++
class baza {
public:
    virtual ~baza() = 0;
};

class derivata : public baza {};

int main() {
    derivata d;
}
```

Vom primi următorul mesaj de eroare:
```
/usr/bin/ld: /tmp/ccGUb9jL.o: in function `derivata::~derivata()':
main.cpp:(.text._ZN8derivataD2Ev[_ZN8derivataD5Ev]+0x26): undefined reference to `baza::~baza()'
collect2: error: ld returned 1 exit status
```

Sau
```
/usr/bin/ld: /tmp/s13-589071.o: in function `derivata::~derivata()':
main.cpp:(.text._ZN8derivataD2Ev[_ZN8derivataD2Ev]+0x11): undefined reference to `baza::~baza()'
clang: error: linker command failed with exit code 1 (use -v to see invocation)
```

Sau alt mesaj similar. Ce se întâmplă?

Codul compilează, dar crapă la etapa de linking, deoarece nu este găsită definiția destructorului
din clasa de bază.

Soluția este să definim destructorul în clasa de bază:
```c++
class baza {
public:
    virtual ~baza() = 0;
};

baza::~baza() = default;

class derivata : public baza {};

int main() {
    derivata d;
}
```

În clasele derivate, destructorul este definit de compilator în mod implicit. **Nu** este nevoie să îl suprascriem.

**Concluzie**

Funcțiile virtuale (pure) ne ajută să extindem codul existent într-un mod ușor, fără să facem schimbări
în clasele de bază sau în alte clase care depind de clasa de bază.

#### Interfață non-virtuală

[//]: # (mai multă flexibilitate în clasele de bază _fără_ modificarea derivatelor)

Funcțiile virtuale publice au dezavantajul că derivatele pot schimba în mod complet interfața clasei de bază.
Avem flexibilitatea să schimbăm în derivate comportamentul din baze, însă nu putem să modificăm în mod uniform
comportamentul derivatelor fără să facem modificări în toate derivatele.

Interfața non-virtuală este o rețetă prin care:
- derivatele nu pot modifica structura interfeței la nivel înalt și
- obținem posibilitatea de a modifica în mod uniform toate derivatele fără să schimbăm în mod
  explicit codul din derivate.

[//]: # (de găsit exemplu concret)

[//]: # (http://www.gotw.ca/publications/mill18.htm)

#### Constructori virtuali

Exemplul următor este doar cu scop ilustrativ pentru a scrie mai puțin.
```c++
#include <iostream>

class curs {
public:
    virtual void prezentare() const = 0;
    virtual ~curs() = default;
};

class curs_obligatoriu : public curs {
    int nr_prezentare = 0;
public:
    void prezentare() const override {
        std::cout << "prezentare obligatorie " << ++nr_prezentare << "\n";
    }
};

class curs_optional : public curs {
    bool interactiv;
public:
    void prezentare() const override {
        std::cout << "prezentare opțională" << (interactiv ? " interactivă" : "") << "\n";
    }
};

class student {
    curs* curs_;
public:
};
```

[//]: # (nu apelăm funcții virtuale în constructori și destructori!!! comportament nedefinit)

[//]: # (clone public, cc/op= protected, la fel pt cele de mutare)

[//]: # (https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-copy)

#### Funcție de afișare

#### Alte funcții virtuale


[//]: # (cu qualified name lookup putem apela prin pointer la bază implementarea unei funcții virtuale pure)

[//]: # (totuși e cam inutil pt că funcțiile virtuale nu ar trebui să fie publice)

[//]: # (https://stackoverflow.com/questions/15853031/call-base-class-method-from-derived-class-object)


[//]: # (https://en.wikipedia.org/wiki/Call_super)

[//]: # (https://stackoverflow.com/a/30885842)

[//]: # (dilema cu cercul și elipsa)

[//]: # (de găsit pe undeva de scris: se recomandă overload cu friend din cauza ADL https://en.cppreference.com/w/cpp/language/adl)

#### Smart pointers

##### shared_ptr
##### unique_ptr

#### Dynamic cast

[//]: # (referințe, pointeri)

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

---

#### Exemplu

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
- implementarea a două funcționalități noi specifice temei; pentru minim o funcționalitate **trebuie**
  folosite funcții virtuale
- **după** rezolvarea discuțiilor, de făcut un commit cu adăugarea unei noi derivate și suprascrierea unei
  funcții virtuale specifice temei; ar trebui modificat codul doar în funcția main și în fișierul cu noua derivată

#### Termen limită
- săptămâna 7 (20 noiembrie/2 aprilie): progres parțial
- **săptămâna 8 (27 noiembrie/9 aprilie): tema 2 gata**
- săptămâna 9 (4 decembrie/16 aprilie): (eventuale) modificări în urma feedback-ului
