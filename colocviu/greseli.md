# Greșeli frecvente în colocvii

Majoritatea colocviilor din ultimii ~12 ani sunt pe stil "muncitoresc". În contextul în care multe aspecte
repetitive ale programării pot fi automatizate din ce în ce mai ușor, și evaluarea studenților ar trebui
să tindă spre evaluarea unor competențe de nivel mai înalt.

În ultimii ani, câțiva dintre noi am încercat să ne mobilizăm și să schimbăm stilul de până acum,
eliminând punctarea codului de tip "boilerplate" care poate fi generat de IDE-uri.

Cu toate acestea, demersul este îngreunat de studenții din ani mai mari și de pe la tutoriate
care publică pe diverse repository-uri soluții de la colocviile din anii anteriori. Soluțiile respective
oferă o "rețetă" de "succes" ca să "treci la sigur", însă promovează fix boilerplate-ul amintit mai sus,
sub o formă sau alta. Sper ca pe viitor să depunctăm în mod activ astfel de soluții, deoarece este în
detrimentul tuturor și nu se evaluează modul de gândire, ci adaptarea unui tipar de "papagal".

## Listă de greșeli

### Singleton care nu e singleton

#### Problema

Un singleton nu trebuie să poată fi copiat. Dacă există constructor de copiere și operator= de copiere,
înseamnă că nu putem garanta că nu se pot crea mai multe obiecte.

Exemplu greșit 1:

```c++
class App {
    App() = default;
public:
    static App& getInstance {
        static App app;
        return app;
    }
};
```

Exemplu greșit 2:

```c++
class App {
    App() = default;
    App(const App& app) = default;
    App& operator=(const App& app) = default;
public:
    static App& getInstance {
        static App app;
        return app;
    }
};
```

Singurul caz când ar merge cu `=default` este când acesta implică `=delete` (dacă sunt atribute
`std::unique_ptr` direct sau indirect).

#### Soluția

Ștergem constructorul de copiere și operator= de copiere (vizibilitatea nu contează).
Nu este suficient să le facem private, pentru că încă pot fi create copii din interiorul clasei.

Exemplu corect:

```c++
class App {
    App() = default;
    App(const App& app) = delete;
    App& operator=(const App& app) = delete;
public:
    static App& getInstance {
        static App app;
        return app;
    }
};
```

### Excepții

#### Problema

- Cod care aruncă `std::runtime_error` sau alte excepții predefinite
- Clase proprii de excepții care moștenesc direct din `std::runtime_error` sau altă clasă predefinită

De ce? Pentru că

- nu putem trata mai multe excepții diferite cu același catch
- dacă totuși încercăm asta, putem realiza acest lucru doar prinzând clasa de bază, deci excepția
  predefinită, deci nu putem face distincție între codul nostru și alt cod care aruncă tot acea
  excepție predefinită sau ceva derivat din ea

Exemplu greșit 1:

```c++
void f() {
    throw std::runtime_error("eroare din cod propriu");
}
```

Exemplu greșit 2:

```c++
class EroareFisier : public std::runtime_error {};
class EroareCalcul : public std::runtime_error {};
```

#### Soluția

Ierarhie de excepții **cu bază proprie**. La rândul său, baza proprie este recomandat să fie derivată
dintr-o excepție predefinită.

Nu uitați - **orice problemă de software engineering se poate rezolva cu un nou strat de
abstractizare/indirectare**.

Exemplu corect:

```c++
class EroareBaza   : public std::runtime_error {};
class EroareFisier : public EroareBaza {};
class EroareCalcul : public Baza {};
```

### Atribute în loc de funcții

Valorile dinamice care se schimbă foarte des și care sunt eficient de calculat de la zero nu ar
trebui reținute ca atribute în clasă. Iar dacă totuși le reținem ca atribute, ar trebui să avem
și getters; altfel, dacă nu le folosim la nimic, degeaba le-am definit/calculat.

Desigur, depinde de la caz la caz, dar foarte mulți studenți pun aiurea atribute în clase.

Exemplu greșit:

```c++
class Exemplu {
    int formula;
    int ceva;
public:
    Exemplu(int val1, int val2, int ceva_) : formula(val1 + val2*2), ceva(ceva_) {}
    void update_ceva(int ceva_) { ceva = ceva_; f(); }
    void f() { formula += ceva; }
    // fără getter pentru "formula"!!!
};
```

Exemplu mai corect:

```c++
class Exemplu {
    int val1;
    int val2;
    int ceva;
public:
    Exemplu(int val1_, int val2_, int ceva_) : val1(val1_), val2(val2_), ceva(ceva_) {}
    int update_ceva(int ceva_) { ceva = ceva_; }
    int formula() { return val1 + 2*val2 + ceva; }
};
```

### Afișări direct cu `std::cout`

CLion vă oferă funcționalitatea de a suprascrie (aproape) automat `operator<<` pentru orice fel de
`std::ostream`, nu doar pentru `std::cout`. Codul trebuie să fie cât mai generic.

### Apeluri de tip "super" în fiecare derivată

Codul comun ar trebui mutat în clasa de bază, nu copiat în fiecare derivată.

Exemplu greșit:

```c++
class Baza {
    int x;
public:
    virtual void afis(std::ostream& os) const {
        os	<< "x " << b.x << "\n";
    }
	friend std::ostream& operator<< (std::ostream& os, const Baza& b) {
	    b.afis(os);
		return os;
	}
};

class D1 : public Baza {
    int y;
public:
    void afis(std::ostream& os) const override {
        Baza::afis(os); // sau std::cout << *this; dacă nu e apelul virtual în op<<
		os	<< "y " << y.x << "\n";
	}
};
    
};
```

Dacă ierarhiile sunt mai adânci, atunci aceasta poate rămâne o soluție acceptabilă dacă
apelurile de tip "super" sunt mici/puține.

Exemplu corect (mai ales pentru ierarhii pe un nivel):

```c++
class B {
    int x;
public:
    virtual void afis(std::ostream& os) const {}
	friend std::ostream& operator<< (std::ostream& os, const B& b) {
        os	<< "x " << b.x << "\n";
	    b.afis(os);
		return os;
	}
};

class D1 : public B {
    int y;
public:
    void afis(std::ostream& os) const override {
        os	<< "y " << y << "\n";
	}
};

```

Citiți explicațiile din tema 2, aveți și acolo contraexemple.

### Factory-uri care nu sunt factory-uri

Un factory trebuie să îți dea un obiect "de-a gata", ușor de construit, fără prea mulți parametri.

Dacă trebuie să îi dai mai mult de 1-3 parametri, nu prea mai e factory. Și mai rău este când în
funcția de factory aveți citiri de la tastatură.

Exemple greșite:

```c++
class FactoryExemplu {
public:
    static std::shared_ptr<Exemplu> createExemplu(const std::string& nume, float ceva, int altceva);
    static std::shared_ptr<Exemplu> createExemplu2() {
        std::string nume;
        std::cin >> nume;
        // etc.
    }
};
```

Exemple mai corecte:

```c++
class FactoryExemplu {
public:
    static std::shared_ptr<Exemplu> createExemplu(TipExemplu tip, const std::string& nume);
    static std::shared_ptr<Exemplu> createExemplu2() {
        return std::make_shared<Exemplu>("val fixa1", 2.3, 4); // sau cu std::rand
    }
};
```

Nu înseamnă să nu aveți funcții ajutătoare prin cod de acest fel, dar nu le spuneți factory-uri.

De asemenea, nu faceți confuzie cu pattern-ul "Abstract Factory". Acela este pentru familii de obiecte
și implică moșteniri. Aveți o variație în rezolvarea de colocviu din ianuarie 2026.

### Citiri, afișări, meniu când nu se cer în enunț

**NU ne interesează povești**. Nu ne interesează să arătați nu știu câte citiri de la tastatură.

Pentru crearea obiectelor există constructori. Nu demonstrați că știți POO dacă duplicați rolul
constructorilor prin inițializarea obiectelor cu `operator>>`, mai ales când nu se cere asta explicit
în cerință.

**NU ne interesează mesaje de afișare kilometrice**. Pentru asta există temele de laborator.
Nu arătați că știți POO prin zeci de afișări de mesaje.

### Excepții folosite aiurea

Citiți explicațiile din tema 2, aveți și acolo contra-exemple.

Un exemplu (desigur, greșit):

```c++
try {
    switch (optiune) {
        case 1:
            // ...
            break;
        case 2:
            // ...
            break;
        default:
            throw EroareOptiune();
    }
} catch (EroareOptiune& err) { std::cout << err.what() << "\n"; }
```

Este fix degeaba să aruncăm o excepție pe care o prindem imediat. Nu demonstrează absolut nimic.
Dimpotrivă, arată că **nu ați înțeles** excepțiile. Nu evaluăm că știți sintaxa. Este irelevant
să pui o sintaxă în ideea că poate bifezi o cerință. Pe viitor probabil vom scădea puncte pe astfel
de bazaconii.

### Clase finale

**NU folosiți clase finale**. Situațiile când chiar se justifică sunt foarte rare. Rolul ar fi să
documentezi codul, însă nu poți prevedea toate modurile în care s-ar putea extinde aplicația.

În momentul în care ajungi să ai de adăugat/suprascris funcționalități, va trebui să facem copy-paste
la clasa finală cu totul doar pentru a schimba/adăuga câteva rânduri.

### Fără cod de umplutură

Probabil vom scădea pe viitor în mod activ pentru asta. Nu arătați că știți POO dacă generați
cc/op=/getters/setters când nu este nevoie. Dimpotrivă.

### TBA
