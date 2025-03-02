# Tema 1

### ⚠ Puneți cât mai multe întrebări! Nu există întrebări greșite.
#### Semnalați orice fel de greșeli găsiți!

Înainte de a parcurge aceste materiale, ar trebui să aveți configurat
[mediul de lucru](/env).

Pentru proiect, voi presupune că ați făcut un repository nou pe baza repository-ului template corespunzător grupei
voastre și că v-ați clonat local
repository-ul vostru.

### Template proiect

| Laborant  | Link template                                |
|-----------|----------------------------------------------|
| Dragoș B  | https://github.com/Ionnier/oop-template      |
| Tiberiu M | https://github.com/MaximTiberiu/oop-template |
| Marius MC | https://github.com/mcmarius/oop-template     |

Dacă nu doriți să folosiți template-ul, trebuie să ajungeți la o configurație
echivalentă:

- gitignore, gitattributes
- CMakelists.txt (sau un fișier pentru alt sistem de build portabil)
- flags pentru warnings (de asemenea trebuie să fie portabile)
- eventualele configurații pentru biblioteci externe de asemenea trebuie să fie portabile
- serviciu de integrare continuă (pe scurt CI = continuous integration)
- distribuire fișiere binare (executabile) cu toate fișierele auxiliare necesare
- fișier README cu o scurtă descriere

Pentru diverse exerciții, este suficient să vă configurați afișarea de warnings. Desigur, trebuie să
și țineți cont de warnings și să le eliminați pentru că **nu sunt degeaba**.

**Pentru introducere/recapitulare a noțiunilor de bază din limbajele C și C++,
citiți de [aici](intro_recap_c_cpp.md).**

## Noțiuni de bază de OOP în C++

### Clase și obiecte

O clasă este o descriere generală pentru noțiuni din realitate pe care vrem să le
modelăm într-un program.
O clasă reprezintă un tipar după care construim obiecte.
Un obiect este o instanță a unei clase, adică un element concret, cu proprietăți specifice.

Aveți grijă să nu folosiți definiții circulare!

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
Din această cauză, limbajul C++ are o gramatică ambiguă.

Sintaxa cu acolade încearcă să remedieze situația. Întotdeauna se construiesc obiecte
atunci când folosim sintaxa cu acolade.

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

În curs, compunerea se mai numește și agregare, dar înseamnă același lucru.

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
folosi setters (aproape) deloc, deoarece am vrea să ne definim operații cu un nivel mai ridicat
de abstractizare.

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
    Student() { std::cout << "Constructor Student fără params;\n"; }
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

### Constructori expliciți

Cu excepția constructorilor de copiere (vezi secțiunea următoare), toți constructorii cu un singur parametru
ar trebui să îi declarăm cu specificatorul "explicit". Dacă nu facem asta, sunt posibile conversii implicite
între diverse tipuri de date, iar asta ne va face să pierdem timp încercând să depanăm erori subtile.

```c++
#include <string>
#include <iostream>

class Student {
private:
    std::string nume;
public:
    Student(const std::string& nume_) : nume{nume_} {
        std::cout << "Constr de inițializare Student\n";
    }
    const std::string& getNume() const { return nume; }
};

void f(std::string& st) {
    std::cout << "f cu string: " << st << "\n";
}

void f(Student st) {
    std::cout << "f cu student: " << st.getNume() << "\n";
}

int main() {
    using namespace std::string_literals;
    f("Nume"s);
}
```

Comportamentul din exemplul de mai sus poate părea surprinzător: apelăm funcția `f` cu un argument de tip
`std::string`, însă se apelează funcția care primește ca parametru un `Student`.

Pentru a evita astfel de conversii nedorite, este recomandat (în cazul nostru obligatoriu - vezi tema 1)
să folosim constructori expliciți:

```c++
#include <string>
#include <iostream>

class Student {
private:
    std::string nume;
public:
    explicit Student(const std::string& nume_) : nume{nume_} {
        std::cout << "Constr de inițializare Student\n";
    }
    const std::string& getNume() const { return nume; }
};

void f(std::string& st) {
    std::cout << "f cu string: " << st << "\n";
}

void f(Student st) {
    std::cout << "f cu student: " << st.getNume() << "\n";
}

int main() {
    using namespace std::string_literals;
    f(Student{"Nume"s});
}
```

Din C++20, există o sintaxă care ne permite să zicem că vrem în mod intenționat ca anumiți constructori să
permită conversii implicite:
```c++
class Student {
private:
    std::string nume;
public:
    explicit(false) Student(const std::string& nume_) : nume{nume_} {
        std::cout << "Constr de inițializare Student\n";
    }
};
```

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


**Observație!** Dacă redefinim cc, trebuie să fim atenți când adăugăm noi atribute în clasă, deoarece acestea
nu vor fi copiate dacă nu cerem asta în mod explicit. **Verificați!**

Putem folosi `= default` și `= delete` și pentru a forța generarea/ștergerea constructorilor de copiere
generați de compilator.

#### Detalii shallow copy vs deep copy

În alte limbaje orientate obiect, fie nu avem definite implicit operații de copiere, fie se face implicit
shallow copy (din motive de performanță și pt că e mai simplu de implementat). Pentru anumite situații,
avem nevoie de obiecte complet independente pentru prelucrări ulterioare și trebuie să facem "deep copy".

C++ nu are nativ funcționalități de deep copy. Pentru clase uzuale, suprascriem constructorul de copiere,
operator= și destructor (detalii mai jos).
În cazul ierarhiilor de clase,
o [convenție uzuală](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-copy) este să definim
o funcție numită `clone` și să dezactivăm constructorul de copiere.
Vom face și noi deep copy cu `clone` la tema 2 pentru că nu avem de ales.

Deși unele limbaje oferă mecanisme de deep copy, este responsabilitatea noastră să le folosim sau să
implementăm acest comportament dacă decidem că este necesar. Abordările din C++ nu diferă cu mult
față de alte limbaje, ideile de bază sunt aceleași.

Câteva exemple din alte limbaje (ordine alfabetică):
- în C#, există o interfață `ICloneable` și o funcție
  [`MemberwiseClone`](https://learn.microsoft.com/en-us/dotnet/api/system.object.memberwiseclone) cu probleme
  similare cu cele din Java; alternativele sunt asemănătoare cu cele din Java - vezi mai jos
- în Java, există o interfață `Cloneable` fără o funcție `clone` și _separat_ o funcție `clone` (din `Object`),
  însă pare să aibă greșeli istorice; implicit,
  [clone](https://docs.oracle.com/en/java/javase/21/docs/api/java.base/java/lang/Object.html#clone()) face
  shallow copy; pentru deep copy, se poate folosi tot clone (fiind conștienți de
  [dezavantaje](https://stackoverflow.com/questions/1106102/)), constructor de copiere (ca în C++),
  serializare (sunt (mici) similarități cu `operator<<` - vezi mai jos)/deserializare (lent),
  reflexie (momentan fără echivalent nativ în C++) sau biblioteci specializate (probabil tot prin reflexie)
- în JavaScript, implicit se face [shallow copy](https://developer.mozilla.org/en-US/docs/Glossary/Shallow_copy);
  pentru deep copy, pare să existe [structuredClone](https://developer.mozilla.org/en-US/docs/Web/API/structuredClone);
  alternativ, cu serializare/deserializare; în particular, în JavaScript pot exista mai adesea multe structuri recursive sau
  alte cazuri particulare, deci nu se poate face de fapt deep copy pentru orice obiect arbitrar
- în Python, există modulul copy cu funcția [deepcopy](https://docs.python.org/3/library/copy.html#copy.deepcopy)
- în Swift, nu pare să putem face [ușor](https://stackoverflow.com/a/66105234) deep copy deoarece limbajul încearcă
  să facă numeroase optimizări tocmai pentru a nu copia obiecte


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

La rândurile `nume = nume_;` și `stud = stud_;` se apelează funcțiile `operator=` de copiere (op= pe scurt)
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

Este analog constructorului de mutare. De obicei, când folosim cc, folosim op= de copiere. Când folosim cm,
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
să putem accesa în mod direct atributele private (într-un cadru restrâns). Noțiunea de funcție friend
nu există și în alte limbaje. O noțiune similară ar fi accesul la nivel de pachet/modul/namespace.

În biblioteca standard, avem ca funcție ajutătoare `std::to_string`. Totuși, nu avem definit `operator<<`
pentru toate tipurile de date, deoarece există prea multe posibilități de a face asta (care pot afecta
performanța), iar C++ încearcă să fie un limbaj general și să acopere cât mai multe cazuri.
De aceea, nu sunt furnizate decât implementări care să meargă pe multe cazuri (uneori, prea multe).

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

### Operatori de conversie

[Operatorii de conversie](https://en.cppreference.com/w/cpp/language/cast_operator) sunt specifici C++,
nu prea au treabă cu OOP-ul și nu sunt foarte utili (dacă nu sunt expliciți) pentru că fac codul mai greu de urmărit
(vezi de exemplu [aici](https://stackoverflow.com/questions/18547449/) și [aici](https://stackoverflow.com/questions/1384007/)).
Sunt incluși aici pentru că sunt în curs/examen.

Sintaxa este asemănătoare cu cea de la constructori:
```c++
#include <string>

class Submarin {
    std::string nume;
    int nr_locuri;
public:
    Submarin(std::string nume_, int nr_locuri_) : nume(nume_), nr_locuri(nr_locuri_) {}
};
class Mașină {
    std::string nume;
    int nr_locuri;
public:
    Mașină(std::string nume_, int nr_locuri_) : nume(nume_), nr_locuri(nr_locuri_) {}
    operator Submarin() { return Submarin(nume + " de baltă", nr_locuri / 2); }
};

int main() {
    Mașină masina{"Logan", 5};
    Submarin submarin = masina;
}
```

Alternativa ar fi constructorii de conversie, dezavantajul fiind nevoia de getteri (sau clasă friend):
```c++
#include <string>

class Mașină {
    std::string nume;
    int nr_locuri;
public:
    Mașină(std::string nume_, int nr_locuri_) : nume(nume_), nr_locuri(nr_locuri_) {}
    const std::string get_nume() const { return nume; }
    int get_nr_locuri() const { return nr_locuri; }
};

class Submarin {
    std::string nume;
    int nr_locuri;
public:
    // Submarin(std::string nume_, int nr_locuri_) : nume(nume_), nr_locuri(nr_locuri_) {}
    Submarin(const Mașină& masina) :
        nume(masina.get_nume() + " de baltă"),
        nr_locuri(masina.get_nr_locuri() / 2) {}
};

int main() {
    Mașină masina{"Logan", 5};
    Submarin submarin = masina;
}
```

Un exemplu de situație în care poate fi util acest operator este să scriem mai succint design pattern-ul "Builder" (vezi tema 3). Exercițiu.

Alt exemplu ar fi să nu mai creăm obiecte în plus: vezi [aici](https://stackoverflow.com/a/6095954).

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

Dacă avem funcții membru "read-only", atunci cel mai bine este să le marcăm cu `const`,
deoarece `const`-urile au efect de domino și se propagă. Astfel, primim eroare la
compilare dacă încercăm să modificăm ceva ce nu ar trebui.

```c++
class Student {
    std::vector<int> note;
public:
    int medie() const {
        int rezultat = 0;
        for(int nota : note)
            rezultat += nota;

        return rezultat;
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

### Referințe circulare

Detalii [aici](intro_recap_c_cpp.md#fișiere-de-tip-header-și-clase). Pe scurt, este imposibil ca următorul cod să compileze:
```c++
// facultate.h
#pragma once
#include "Student.h"

class Facultate {
    Student student;
};


// student.h
#pragma once
#include "Facultate.h"

class Student {
    Facultate facultate;
};
```

Soluția este să avem doar pointer (sau referință) într-o direcție pentru a nu avea recurențe infinite la construirea obiectelor.

Oul și găina: pentru a construi un obiect de tip facultate trebuie construit un obiect de tip student, iar pentru a construi un
obiect de tip student trebuie construit întâi un obiect de tip facultate.

Acolo unde avem pointer (sau referință) nu mai este nevoie de `include` întrucât nu este nevoie de definiția clasei (toți pointerii au același sizeof):
```c++
// facultate.h
#pragma once
#include "Student.h"

class Facultate {
    Student student;
};


// student.h
#pragma once

class Student {
    Facultate* facultate;
    // trebuie suprascrise cc, op= și destr
};
```

### Numere aleatoare

Detalii [aici](https://github.com/effolkronium/random) și pe repo-ul template (vezi pe branch-ul common-libs).

## Cerințe tema 1

Scopul primei teme este familiarizarea cu limbajul C++ și cu unele noțiuni OOP de bază. La sfârșitul
săptămânii 4 ar trebui să aveți implementate minim 3 funcționalități **netriviale** pe care le considerați esențiale.

**Nu vă apucați de implementat până nu ați primit OK-ul! Aș vrea să discut cu fiecare în parte pentru
a stabili interfața.**

Pentru lista completă a cerințelor, vezi [template-ul de proiect](#template-proiect).

Cerințe comune pe scurt:

- compunere
- constructori (expliciți) de inițializare pentru fiecare clasă
- regula celor trei pentru o clasă: constructor de copiere, `operator=` de copiere și destructor
- `operator<<` pentru **toate** clasele cu compunere
- minim 3 funcții membru publice **netriviale**
- scenariu de utilizare cu sens: apelarea/testarea *tuturor* funcțiilor publice în `main`; dacă nu le apelăm, la ce
  le-am mai definit?

Cerințe comune (organizatorice):
- codul trebuie să fie pe un repository de `git` la care să am acces (nu e obligatoriu să fie github dpmdv)
- obligatoriu `.gitignore`
- **NU faceți commit prin upload la fișiere din browser** deoarece nu se ia în considerare fișierul `.gitignore`;
nu fiți leneși!
- un tag de git pe un commit cu cod stabil și toate bifele
- obligatoriu un serviciu de integrare continuă (CI) cu minim 2 sisteme de operare diferite și
minim 2 compilatoare diferite
  - recomand să folosiți GitHub Actions deoarece e inclus în repository-ul template
  - fără warnings din partea compilatoarelor
  - fără warnings din partea instrumentelor de analiză statică
  - fără erori de memorie

#### Termen limită
- săptămâna 3 (23 octombrie/12 martie): stabilirea claselor și implementarea parțială a acestora
- **săptămâna 4 (30 octombrie/19 martie): tema 1 gata**
- săptămâna 5 (6 noiembrie/26 martie): (eventuale) modificări în urma feedback-ului


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

**Încercați să veniți cu propriile idei. Dacă nu aveți inspirație, uitați-vă pe
[proiectele din anii trecuți](/HoF.md), dar vă rog nu alegeți [proiecte care s-au tot făcut](/repetitiv.md).**

**Nu vă apucați de implementat până nu ați primit OK-ul! Aș vrea să discut cu fiecare în parte.**

## Resurse
- [cppreference.com](https://en.cppreference.com/w/cpp)
- [ISO C++ FAQ](https://isocpp.org/faq/)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- [Diverse standarde (draft) ale limbajului](https://en.cppreference.com/w/cpp/links) sau ca
[HTML (neoficial)](https://github.com/timsong-cpp/cppwp) (sau
[aici](https://stackoverflow.com/questions/81656/where-do-i-find-the-current-c-or-c-standard-documents#4653479))
  - faptul că nu (mai) găsim draft-uri disponibile pentru standardele C++98/C++03 ar trebui să ne transmită ceva 😉
  - mai ales în contextul în care toate compilatoarele cunoscute au implementat complet C++11, C++14 și C++17 (și
    aproape complet C++20)
  - le-am adăugat mai mult ca să știți că există, nu e nevoie să vă uitați peste ele
