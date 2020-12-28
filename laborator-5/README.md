### Tema 3

Scopul acestei teme este utilizarea unor concepte mai avansate de OOP (design patterns) și a programării generice, dacă este posibil.

Cerințe:
- minim o funcție/o clasă șablon (template); dacă nu se poate, renunțăm la această cerință ☹
- minim un design pattern (sau 2 dacă aveți singleton sau ceva la fel de simplu și proiectul e simplu); **utilizarea acestor design patterns ar trebui să aibă sens**

Observații:
- desigur, pt nota 10 trebuie să nu fie warnings sau erori de memorie
- nu ar trebui să vă ia mai mult de câteva ore (cel mult 4-5 aș zice)
- puteți folosi și alte design patterns pe lângă cele prezentate aici
- aceste patterns se pot combina între ele și au numeroase variațiuni

În continuare, prezint câteva exemple de design patterns care s-ar putea potrivi și care nu sunt foarte complicate.

**Singleton**

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
Desigur, putem folosi smart pointers. Dacă folosim `std::unique_ptr`, atunci constructorul de copiere și op= vor fi implicit șterse.

**Object pool**

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
    connection c = pool.get_conn();
} catch(std::runtime_error&) {}
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
    dulap_builder& tip_maner(std::string& tip) {
        d.tip_maner = tip;
        return *this;
    }
    dulap_builder& tip_balama(std::string& tip) {
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

**Factory**

Context: obiectul are foarte multe atribute (să zicem 5+, foarte comun în aplicații medii/mari) și nu ne interesează să le setăm pe fiecare în parte. Se folosește de obicei la testarea automată: dorim să obținem o instanță a obiectului "repede", fără să ne preocupe ce "conține".

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

**Proxy**

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

#### Moșteniri multiple și virtuale

C++ permite moșteniri multiple:
```c++
class plantă {};
class eco {}; // clasa abstracta
class plantă_eco : public plantă, public eco {};
```

Un comportament care poate nu este de dorit apare atunci când clasele pe care le moștenim au o clasă de bază comună.

Atributele și funcțiile din clasa de bază vor apărea de mai multe ori în "ultima" clasă derivată:
```c++
class ecran {};
class dispozitiv {
    ecran e;
};

class tabletă : public dispozitiv {
    // moștenește ecranul
};

class laptop : public dispozitiv {
    // moștenește ecranul
};

class two_in_one : public tabletă, public laptop {
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

class tabletă : public virtual dispozitiv {
    // moștenește ecranul
};

class laptop : public virtual dispozitiv {
    // moștenește ecranul
};

class two_in_one : public tabletă, public laptop {
    // moștenește un singur ecran!
};
```
Dacă facem moștenirea virtuală "la sfârșit" (în clasa `two_in_one`), vom avea în continuare două `ecrane`.


#### Templates
Pentru exemple, motivație etc, citiți cursul. Această secțiune arată modul în care putem folosi fișiere separate pentru templates.

Singurul dezavantaj atunci când folosim fișiere separate este acela că trebuie să declarăm în mod explicit funcțiile/clasele toate tipurile de date pentru care avem nevoie de templates.

Pentru situațiile întâlnite aici, putem folosi fie `<class T>`, fie `<typename T>`, este același lucru. Există situații când merge doar cu `typename` sau doar cu `class`, însă nu ne vom întâlni cu ele (sper). Important este să le folosim în mod consistent, peste tot la fel.

**Funcții template**

```c++
// sursa.h
#ifndef SURSA_H
#define SURSA_H

template <class T>
void f(T x);

#endif

/////////////////////////

// sursa.cpp
#include "sursa.h"
#include <iostream>

template <class T>
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
- în `sursa_impl.cpp` trebuie să adăugăm declarații pentru toate tipurile pe care le folosim peste tot unde includem `sursa.h`

**Clase template**

```c++
// sursa.h
#ifndef SURSA_H
#define SURSA_H


template <class T>
class cls {
public:
    void f(T x);
};

#endif

/////////////////////////

// sursa.cpp
#include "sursa.h"
#include <iostream>

template <class T>
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

**Supraîncărcare operatori friend în clase template**

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
