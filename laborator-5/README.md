### Tema 3

Scopul acestei teme este utilizarea unor concepte mai avansate de OOP (design patterns) și a programării generice.

Cerințe:
- minim o funcție șablon și o clasă șablon (template)
    - modificați o clasă existentă care este ceva mai izolată de celelalte (să nu aveți foarte mult de modificat) și transformați-o în clasă template
    - adăugați (minim) un atribut de tip `T` sau care depinde de `T`
    - adăugați (minim) o funcție membru care să depindă de `T` (sau de alt parametru template); idee: [expresii de tip fold](#expresii-de-tip-fold-c17)
    - adăugați (minim) o funcție normală/liberă template; poate să fie `friend`
- minim 2 design patterns (3 dacă aveți singleton sau ceva la fel de simplu și proiectul e simplu); **utilizarea acestor design patterns ar trebui să aibă sens**

Observații:
- desigur, pt nota 10 trebuie să nu fie warnings sau erori de memorie
- nu ar trebui să vă ia mai mult de câteva ore (cel mult 8-9 aș zice)
- puteți folosi și alte design patterns pe lângă cele prezentate aici
- aceste patterns se pot combina între ele și au numeroase variațiuni

**Deadline feature freeze** (dar prelungim atât cât se poate pt mici modificări); după această dată, cel mult reparat bug-uri
  - sem 1: **29 decembrie** (inclusiv)
  - sem 2: **3 iunie** (inclusiv)

Orice funcționalitate în plus e luată în considerare pentru puncte bonus, inclusiv la temele din urmă. Nota maximă este 12.

Dacă doriți să folosiți conceptele din C++20, am actualizat pipeline-ul de GitHub Actions. [Puteți vedea modificările aici](https://github.com/mcmarius/demo-poo/pull/19/files#diff-cdd48abbd3eb8d1c54077449fc74a8de1f29805d2be5d8e5232b7aab76ea7a6fL17) (vedeți și [următorul commit](https://github.com/mcmarius/demo-poo/commit/ab2b37c1d999ce9f7030464ece1e0be802309421) pe repo).

-----

## Design patterns

În continuare, prezint câteva exemple de design patterns care s-ar putea potrivi și care nu sunt foarte complicate.

### Singleton

Context: avem nevoie de un singur obiect dintr-o anumită clasă, deoarece nu are rost să avem mai multe obiecte de acest fel.

Exemplu: un obiect care gestionează o aplicație/un joc
```c++
class application {
private:
    application() = default;
    static application* app;
public:
    application(const application&) = delete;
    application& operator=(const application&) = delete;
    static application* get_app() {
        if(app == nullptr) { app = new application; }
        return app;
    }
};

application* application::app = nullptr;

// mod de utilizare
auto x = application::get_app();
```
Putem folosi smart pointers, însă nu este necesar, având în vedere că dorim ca variabila statică să trăiască pe toată durata programului în cazul singleton.

### Object pool

Context: avem un număr limitat de obiecte care trebuie refolosite. De obicei este folosit pentru refolosirea conexiunilor la un server. Poate fi considerat un fel de generalizare a singleton-ului: un connection_pool cu o singură conexiune poate fi privit ca un singleton.

Exemplu cu conexiuni; `connection_pool` poate la rândul său să utilizeze `singleton`; după ce o conexiune nu mai e folosită, se apelează `close`:
```c++
class connection {
private:
    bool opened = false;
public:
    void open() { opened = true; }
    bool free() const { return !opened; }
    void close() { opened = false; }
    ~connection() { close(); }
};

class connection_pool {
private:
    static const int max_conns = 5;
    std::vector<connection> conns{max_conns};
public:
    connection& get_conn() {
        for(auto& conn : conns)
            if(conn.free()) {
                conn.open();
                return conn;
            }
        throw std::runtime_error("too many open connections!");
    }
};

// mod de folosire
connection_pool pool;
try {
    connection& c = pool.get_conn();
    auto data = fetch_data(c); // presupunem că am definit funcția aceasta
    std::cout << data;
} catch(std::runtime_error& err) { std::cout << err.what() << "\n"; }
```

**Builder**

Context: limitare a limbajului C++. Funcțiile au doar argumente poziționale, nu și argumente de tip dicționar (sau cheie-valoare). Dacă nu vrem să inițializăm toate atributele, nu putem folosi argumente implicite dacă ne interesează doar argumentele "de la sfârșit".

Exemplu:
```c++
class dulap {
    int nr_rafturi;
    int nr_sertare;
    std::string tip_maner;
    std::string tip_balama;
friend class dulap_builder;
public:
    dulap() = default;
};

class dulap_builder {
private:
    dulap d;
public:
    dulap_builder() = default;
    dulap_builder& nr_rafturi(int nr) {
        d.nr_rafturi = nr;
        return *this;
    }
    dulap_builder& nr_sertare(int nr) {
        d.nr_sertare = nr;
        return *this;
    }
    dulap_builder& tip_maner(const std::string& tip) {
        d.tip_maner = tip;
        return *this;
    }
    dulap_builder& tip_balama(const std::string& tip) {
        d.tip_balama = tip;
        return *this;
    }
    dulap build() {
        return d;
    }
};

// mod de folosire
dulap_builder b;
dulap d = b.nr_rafturi(5).tip_balama("clasic").build();
```

Observații:
- în funcția `build` putem arunca o excepție dacă obiectul este invalid (de exemplu, lipsește ușa)
- putem introduce o funcție sau o clasă suplimentară pentru a reseta obiectul intern (sau putem face asta în funcția `build`) ca să putem folosi același `builder` pentru a construi mai multe obiecte

Context general (nu depinde de limbaj): evaluare leneșă.

Exemplu: construirea unor cereri (SQL) în mod dinamic. Adăugăm pe parcurs mai multe clauze (`where`, `join` etc.), însă nu ar fi eficient să facem câte o cerere la baza de date la fiecare pas. Astfel, acumulăm condițiile într-o variabilă internă și efectuăm cererea efectivă cu toate condițiile acumulate de-abia "la sfârșit", în momentul în care avem nevoie de rezultate.


### Factory

Context: obiectul are foarte multe atribute (să zicem 5+, foarte comun în aplicații medii/mari) și nu ne interesează să le setăm pe fiecare în parte. Se folosește de obicei la testarea automată: dorim să obținem o instanță a obiectului "repede", fără să ne preocupe foarte tare ce "conține".

Exemplu:
```c++
class scaun {
    int nr_picioare;
    bool spatar;
    std::string material;
public:
    scaun(int nrPicioare, bool spatar, std::string material)
    : nr_picioare(nrPicioare), spatar(spatar), material(std::move(material)) {}};

class scaun_factory {
public:
    static scaun taburet() { return scaun(4, false, "lemn"); }
    static scaun taburet_simplu() { return scaun(3, false, "lemn"); }
    static scaun scaun_de_lemn() { return scaun(4, true, "lemn"); }
    static scaun scaun_de_metal() { return scaun(4, true, "metal"); }
    static scaun scaun_modern() { return scaun(2, true, "metal"); }
};

// mod de folosire
scaun s = scaun_factory::taburet();
```

Observații:
- putem modifica să întoarcem smart pointers
- putem combina pattern-ul cu un builder
- putem folosi factories abstracte pentru a crea familii de obiecte legate între ele:
  - avem
    - `class A {}; class A1 : public A {}; class A2 : public A {};`
    - `class B {}; class B1 : public B {}; class B2 : public B {};`
  - `Factory` este o interfață care întoarce pointeri la `A` și `B` (factory abstract)
  - `Factory1 : public Factory` construiește `A1`, `B1`
  - `Factory2 : public Factory` construiește `A2`, `B2`
  - în `main` inițializăm un factory concret, apoi putem lucra cu referință/pointer la `Factory` și astfel ascundem tipurile concrete (`A1` și `B1` de exemplu)
  - exemplu cu baze de date:
    - `A` și `B` ar putea fi adaptor (pt conexiuni), statement_generator
    - `A1` și `B1` (`A2` cu `B2` etc.) sunt clase concrete pentru o bază de date anume (exemple: MySQL, Oracle, PostgreSQL, SQLite, SQL Server)
    - restul codului va interacționa doar cu pointeri la `A` și `B` pe care îi putem obține cu ajutorul unui factory abstract

### Proxy

Context: avem nevoie de o interfață pentru alte obiecte. Exemple: abstractizarea codului din alte limbaje/module, restricționarea accesului, testarea automată.

Exemplu:
```c++
class postare {
public:
    void citeste() {}
    void scrie() {}
    void modifica() {}
    void ascunde() {}
    void sterge() {}
};

class user {};
class auth {
    user u;
public:
    auth(const user& u) : u(u) {}
};

class postare_proxy {
private:
    postare p;
    auth a;
public:
    postare_proxy(const postare& p, const auth& a) : p(p), a(a) {}
    void citeste() {
        if(a.are_voie())
            p.citeste();
    }
    // restul funcțiilor publice din postare (cele de interes) sunt adăugate și în proxy
};
```

Observații:
- de ce nu am făcut verificarea direct în clasa `postare`? deoarece fiecare clasă ar trebui să facă un singur lucru (iar pe acela să îl facă bine)

### Alte design patterns de adăugat/completat

#### Decorator

Scop simplificat: reprezentăm un obiect într-un mod diferit.

Din ce am văzut în (prea) multe locuri, pare destul de standard să păstrezi interfața obiectului pe care îl decorezi. Cu toate acestea, eu nu am avut de folosit în practică decoratorii în acest fel 🙃

Pe scurt:
```c++
class abc {
    // atribute
};

class abc_decorator {  // : public abc dacă vrem să păstrăm interfața obiectului inițial
    abc ob;  // sau pointer la abc/pointer la bază
public:
    // adăugăm noi funcționalități
    std::string& to_csv() { /* ... */ }
    std::string& to_json() { /* ... */ }
}
```

Patterns asemănătoare: adapter, facade.

#### Strategy

TL;DR interfață comună pentru diverși algoritmi/variante ale aceluiași algoritm.

#### Null object

Un eventual alt mod de a "trata" erori. În loc să folosim `nullptr` sau coduri de retur, continuăm să folosim obiectul într-un lanț de apeluri, iar apelurile respective nu vor face nimic în caz de erori. E un fel de proxy care ignoră apelurile invalide. Dacă vreți, poate să semene un pic și cu înlănțuirea din builder.

```c++
obiect ob;
obiect_wrapper ow(ob);

ow.f();
ow.g();  // <--- acest apel "crapă", dar putem continua execuția normal
ow.h();

// alternativ
ow.f().g().h();  // ob.g() crapă
```

Clase ajutătoare în C++: [`std::optional`](https://en.cppreference.com/w/cpp/utility/optional), [`std::variant`](https://en.cppreference.com/w/cpp/utility/variant).

----

### Moșteniri multiple și virtuale

C++ permite moșteniri multiple:
```c++
class planta {};
class eco {}; // clasa abstracta
class planta_eco : public planta, public eco {};
```

Un comportament care poate nu este de dorit apare atunci când clasele pe care le moștenim au o clasă de bază comună.

Atributele și funcțiile din clasa de bază vor apărea de mai multe ori în "ultima" clasă derivată:
```c++
class ecran {};
class dispozitiv {
    ecran e;
};

class tableta : public dispozitiv {
    // moștenește ecranul
};

class laptop : public dispozitiv {
    // moștenește ecranul
};

class two_in_one : public tableta, public laptop {
    // moștenește două ecrane!
    // acestea sunt tabletă::ecran și laptop::ecran
};
```

Soluția este să folosim moștenire virtuală:
```c++
class ecran {};
class dispozitiv {
    ecran e;
};

class tableta : public virtual dispozitiv {
    // moștenește ecranul
};

class laptop : public virtual dispozitiv {
    // moștenește ecranul
};

class two_in_one : public tableta, public laptop {
    // moștenește un singur ecran!
};
```
Dacă facem moștenirea virtuală "la sfârșit" (în clasa `two_in_one`), vom avea în continuare două `ecrane`.

Side note: dacă pun `virtual public` e același lucru, dar nu mai merge syntax highlight pe github.

---

## Templates
Pentru motivație etc, citiți cursul. Această secțiune conține câteva exemple care mi s-au părut relevante/utile și arată modul în care putem folosi fișiere separate pentru templates.

Dezavantajul atunci când folosim fișiere separate este acela că trebuie să declarăm în mod explicit funcțiile/clasele toate tipurile de date pentru care avem nevoie de templates. De aceea, pentru biblioteci poate să fie de preferat varianta header-only.

Avantajul pentru împărțirea în fișiere este acela că dacă modificăm implementarea, nu trebuie să recompilăm toate clasele care includ header-ul.

Pentru situațiile întâlnite aici, putem folosi fie `<class T>`, fie `<typename T>`, este același lucru. Există situații când merge doar cu `typename` sau doar cu `class`, însă nu ne vom întâlni cu ele (sper). Important este să le folosim pe cât posibil în mod consistent, peste tot la fel.

### Funcții template

```c++
// sursa.h
#ifndef SURSA_H
#define SURSA_H

template <typename T>
void f(T x);

#endif

/////////////////////////

// sursa.cpp
#include "sursa.h"
#include <iostream>

template <typename T>
void f(T x) {
    std::cout << x;
}

/////////////////////////

// sursa_impl.cpp
#include "sursa.cpp"

template
void f<int>(int x);

/////////////////////////

// main.cpp
#include "sursa.h"

int main() {
    f<int>(5);
}
```

Observații:
- în `sursa_impl.cpp` trebuie să adăugăm declarații pentru **toate** tipurile pe care le folosim peste tot unde includem `sursa.h`
- poate fi suficient să adăugăm `sursa_impl.cpp` în sistemul de build, nu și `sursa.cpp`

O variantă un pic mai organizată, dar tot header-only:
```c++
// sursa.h
#ifndef SURSA_H
#define SURSA_H

template <typename T>
void f(T x);

#include "sursa.cpp"
#endif

/////////////////////////

// sursa.cpp
#include <iostream>

template <typename T>
void f(T x) {
    std::cout << x;
}
```

#### Funcție de afișat colecții din STL

Întrucât există mai multe (prea multe?) moduri de a afișa o colecție, afișarea nu este implementată.

**Atenție!** Din cauza ODR (one definition rule), problema cu a ne defini noi `operator<<` ca funcție de sine stătătoare este aceea că altcineva nu va mai putea rescrie afișarea în alt mod.

De aceea, e de preferat să ne punem datele într-o clasă wrapper și să facem `operator<<` pe această clasă wrapper.

Totuși, clasa wrapper e mai complicat de făcut ca să meargă și pentru colecții de colecții. Așadar, în exemplul următor ne vom limita la o funcție de sine stătătoare.

```c++
#include <iostream>
#include <vector>

template <typename T>
std::enable_if_t<!std::is_convertible_v<T, std::string>, std::ostream&>
operator<<(std::ostream& os, const T& obj) {
    os << "[";
    for(auto iter = obj.begin(); iter != obj.end(); ++iter) {
        os << *iter;
        if(iter == obj.end())
            break;
        os << ", ";
    }
    os << "]";
    return os;
}


class abc {
public:
    friend std::ostream& operator<<(std::ostream& os, const abc&) { os << "abc"; return os; }
};

int main() {
    auto vec = std::vector<std::vector<int>>{{1, 2, 3, 4, 5, 6, 7}, {3, 4, 5, 6, 7, 8}};
    auto v2 = std::vector<abc>{{}, {}};
    std::cout << vec << "\n" << v2 << "\n";
}
```

Observații:
- dacă nu adăugăm rândul cu `std::enable_if`, atunci avem ambiguitate cu `operator<<` definit pentru `std::string`, deoarece `std::string` este iterabil (are `begin` și `end`)
- [`std::is_convertible<From, To>`](https://en.cppreference.com/w/cpp/types/is_convertible) este un template pentru verificare la momentul compilării dacă From poate fi convertit la To
- `std::is_convertible<From, To>::value` va întoarce `true` dacă această conversie este posibilă
- `std::is_convertible_v<From, To>` este o scurtătură pentru `std::is_convertible<From, To>::value` (C++17)
- [`std::enable_if<bool, T>`](https://en.cppreference.com/w/cpp/types/enable_if) este un template care elimină generarea unor definiții de funcții/clase dacă valoarea primului parametru este `false`
- în situația în care condiția este adevărată, `std::enable_if<bool, T>::type` va întoarce `T`
- `std::enable_if_t<bool, T>` este o scurtătură pentru `std::enable_if<bool, T>::type` (C++14)
- în cazul nostru, va întoarce tipul de retur pentru `operator<<`, adică `std::ostream&`
- în acest mod, nu mai generăm definiția și pentru `std::string`, deci nu mai apar ambiguități
- am pus o condiție în plus pentru a nu mai afișa ultima virgulă; acesta este motivul pentru care nu am folosit `for(const auto& elem : obj)`
  - am fi putut lua ultimul element și să comparăm cu acela, însă asta ar necesita ca elementele să fie comparabile

În cazul în care avem foarte multe elemente, am dori să optimizăm afișarea pentru a limita consumul de resurse:
```c++
#include <iostream>
#include <vector>

template <typename T>
std::enable_if_t<!std::is_convertible_v<T, std::string>, std::ostream&>
operator<<(std::ostream& os, const T& obj) {
    os << "[";
    int nr = 0;
    for(auto iter = obj.begin(); iter != obj.end(); ++iter) {
        os << *iter;
        ++nr;
        if(iter == obj.end())
            break;
        os << ", ";
        if(nr >= 5) {
            os << "...";
            break;
        }
    }
         
    os << "]";
    return os;
}

int main() {
    auto vec = std::vector<std::vector<int>>{{1, 2, 3, 4, 5, 6, 7}, {3, 4, 5, 6, 7, 8}};
    std::cout << vec << "\n";
}
```

În C++20 putem să scriem într-un mod un pic mai elegant constrângerea pentru tipuri. Headerele și funcția main rămân la fel:
```c++
template <typename T> requires (!std::convertible_to<T, std::string>)
std::ostream& operator<<(std::ostream& os, const T& obj) {
    os << "[";
    for(const auto& elem : obj)
        os << elem << " ";
    os << "]\n";
    return os;
}
```

Dacă dorim să marcăm în mod explicit constrângerea pentru colecție, putem proceda în felul următor:
```c++
template <typename T>
concept Container = requires(T v) {
    std::begin(v);
    std::end(v);
};

template <Container T> requires (!std::convertible_to<T, std::string>)
std::ostream& operator<<(std::ostream& os, const T& obj) {
    os << "[";
    for(const auto& elem : obj)
        os << elem << " ";
    os << "]\n";
    return os;
}
```

#### Funcții cu număr variabil de argumente

```c++
#include <string>
#include <iostream>

class elem {};

class abc {
    abc() = default;
    abc(int) { std::cout << "constr int\n"; }
    abc(std::string, int) { std::cout << "constr string int\n"; }
    abc(elem) { std::cout << "constr elem\n"; }
public:
    template <typename... Args>
    static abc create(Args&&... args) {
        return abc(std::forward<Args>(args)...);
    }
};

int main() {
    abc::create(1);
    abc::create(elem{});
}
```

Observații:
- poate fi util când avem mulți constructori, însă vrem să restricționăm crearea de obiecte (exemplu: object pool de mai sus)
- smart pointerii funcționează similar pentru a putea apela constructorii
- nu putem folosi fișiere separate deoarece nu este rezonabil să instanțiem în avans toate combinațiile de apeluri
- dacă vreți totuși să lucrați cu fișiere separate, fie scrieți funcția cu nr variabil de argumente în header, fie includeți cpp-ul în header (vezi la începutul secțiunii cu funcții template)

#### [Expresii de tip fold](https://en.cppreference.com/w/cpp/language/fold) (C++17)

```c++
#include <iostream>

template <typename T>
void print(std::ostream& os, const T& elem) { os << elem << " "; }

template <typename... Args>
void afis(Args... args) {
    (std::cout << ... << args) << "\n";
    // (std::cout.operator<<(args), ...) << "\n"; // (1)
    // (..., std::cout.operator<<(args)) << "\n"; // (2)
    (print(std::cout, args), ...);
    std::cout << "\n";
    (..., print(std::cout, args));
    std::cout << "\n";
}

int main() {
  afis(1, 2, 3, 4);
  afis("a", 3);
}
```

Observații:
- pentru `std::cout << ... << args` "expansiunea" se face astfel:
  - `(std::cout << ... ) << args`, adicaă
  - `(std::cout << ... ) << 4`, adică
  - `((std::cout << ... ) << 3) << 4`, adică
  - `(((std::cout << ... ) << 2) << 3) << 4`, adică
  - `((((std::cout <<   1 ) << 2) << 3) << 4`
  - întâi se evaluează `std::cout << 1` care întoarce noul stream, care va deveni argument pentru `std::cout << 2` etc.
- dacă punem pe dos, ce se întâmplă?
  - `std::cout << args << ...`, adică
  - `std::cout << (args << ...), adică
  - `std::cout << (1  << (2 << ...))`, adică
  - `std::cout << (1  << (2 << ( 3 << ...)))`, adică
  - `std::cout << (1  << (2 << ( 3 << 4  )))`, adică... facem shiftare pe biți și o să vedem doar un număr foarte mare
- dacă ne definim o clasă proprie pentru care definim `operator<<` și încercăm afișarea, rândurile cu (1) și (2) nu vor mai merge deoarece compilatorul se va uita doar la definițiile din interiorul clasei `std::ostream`, nu și la funcțiile friend
- din cauza modului în care se realizează expansiunea argumentelor, nu putem adăuga spații în mod direct
- acesta este motivul pentru care am definit separat funcția `print`, iar apelurile se vor realiza în felul următor:
  - `(print(std::cout, args), ...)`, adică
  - `(print(std::cout, 1), ...)`, adică
  - `(print(std::cout, 1), (print(std::cout, 2), ...))`, adică...
  - și, cu toate acestea, se va afișa `1 2 3 4`
  - de ce? parantezele ar zice pe dos; așa funcționează [operatorul virgulă](https://en.cppreference.com/w/cpp/language/operator_other#Built-in_comma_operator): întâi se evaluează expresia din stânga, abia apoi expresia din dreapta
- detalii în documentație, link-ul este pe titlul secțiunii

**La ce vă puteți folosi de acest lucru la temele voastre?**

Vă puteți defini o funcție de adăugare a mai multor elemente simultan. Găsiți un exemplu și în documentație.

Alternativ, puteți folosi [liste explicite de inițializare](https://en.cppreference.com/w/cpp/utility/initializer_list) dacă argumentele au același tip (de exemplu pointeri la bază); cf [recomandărilor](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#t103-dont-use-variadic-templates-for-homogeneous-argument-lists), variadic templates ar fi overkill.

Bonus: dacă vrem să restricționăm funcția de afișare doar pentru derivate ale anumitei clase, putem folosi din nou concepte (C++20):
```c++
#include <iostream>

class Base {
public:
    friend std::ostream& operator<<(std::ostream& os, const Base&);// { return os; }
};

std::ostream& operator<<(std::ostream& os, const Base&) { os << "."; return os; }

//template <typename T>
//concept Derived = std::is_base_of_v<Base, T>;
template <typename T>
concept Derived = std::derived_from<T, Base>;

template <Derived... Args>
//template <typename... Args> requires(Derived<Args>, ...)
void afis2(const Args... args) {
    (std::cout << ... << args) << "\n";
    //(std::cout.operator<<(args), ...) << "\n";  // err
    //(..., std::cout.operator<<(args)) << "\n";  // err
    (print(std::cout, args), ...);
    std::cout << "\n";
    (..., print(std::cout, args));
    std::cout << "\n";
}

class Der1 : public Base {};
class Der2 : public Base {};

int main() {
  afis2(Base{});
  // afis2(1); // err
  afis2(Base{}, Der1{}, Der2{}, Base{});
}
```

Observații:
- nu am reușit să exprim cu `std::enable_if` această constrângere (probabil se poate, dar e mai urât); cu concepte e destul de natural
- `template <Derived... Args>` este scurtătură pentru `template <typename... Args> requires(Derived<Args>, ...)`
- diferența esențială dintre `std::derived_from` și `std::is_base_of` este aceea că prima permite doar moșteniri publice

### Clase template

```c++
// sursa.h
#ifndef SURSA_H
#define SURSA_H


template <typename T>
class cls {
public:
    void f(T x);
};

#endif

/////////////////////////

// sursa.cpp
#include "sursa.h"
#include <iostream>

template <typename T>
void cls<T>::f(T x) {
    std::cout << x;
}

/////////////////////////

// sursa_impl.cpp
#include "sursa.cpp"

template
class cls<int>;

/////////////////////////

// main.cpp
#include "sursa.h"

int main() {
    cls<int> c;
    c.f(5);
}
```

Observații:
- toate funcțiile unei clase template sunt la rândul lor funcții template
- clasele template sunt de obicei utile dacă vrem să ne definim diverse structuri de date (de exemplu arbori)

#### Tipuri de date dependente

```c++
#include <string>
#include <memory>
#include <array>

class ob {};
template <int nr>
class scaun {
    std::array<ob, nr> picioare;
public:
};

int main() {
  scaun<4> c;
  scaun<3> d;
  // c = d; // eroare
}
```

Tipurile de date de mai sus sunt utile de exemplu la înmulțiri de matrice: vrem să impunem ca nr de linii al primei matrice să fie egal cu nr de coloane al celei de-a doua matrice. Astfel, codificăm o valoare în tipul de date. `scaun<3>` și `scaun<4>` sunt două tipuri de date distincte!

### Supraîncărcare operatori friend în clase template

```c++
// sursa.h
#ifndef SURSA_H
#define SURSA_H

#include <iostream>

template <typename T>
class cls;

template <typename T>
std::ostream& operator<<(std::ostream& o, const cls<T>& c);

template <typename T>
class cls {
    T info;
public:
    cls(const T& x);
    friend std::ostream& operator<< <>(std::ostream&, const cls<T>&);
};

#endif

/////////////////////////

// sursa.cpp
#include "sursa.h"

template <typename T>
cls<T>::cls(const T& x) : info(x) {}

template <typename T>
std::ostream& operator<<(std::ostream& o, const cls<T>& c) {
    o << c.info;
    return o;
}

/////////////////////////

// sursa_impl.cpp
#include "sursa.cpp"

template class
cls<int>;

template
std::ostream& operator<< <>(std::ostream& o, const cls<int>& x);

/////////////////////////

// main.cpp
#include "sursa.h"

int main() {
    cls<int> c(5);
    std::cout << c;
}
```
