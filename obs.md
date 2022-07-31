# Diverse observații

Până când materialele de curs/seminar/laborator sunt refăcute, consider necesar
să semnalez (și) aici numeroase erori pentru a nu mai pierde timpul să explic de
fiecare dată de ce nu e bine să `(vezi fiecare secțiune)` și ce alternative avem.

## Despre reimplementarea `std::vector` și `std::string`

În curs, seminar și în unele materiale de laborator este posibil să vedeți
numeroase exemple în care sunt reimplementate de la zero câteva
funcționalități ale claselor `std::vector` și `std::string` din
biblioteca standard de C++, sub pretextul folosirii alocărilor dinamice explicite.

Rolul acestei secțiuni este să demonstreze defectele implementărilor respective
și să arate că demersul este motivat greșit. Câteva rezultate ale acestor implementări:
- nu sunt rezolvate limitări ale claselor inițiale
- sunt introduse defecte suplimentare
- codul nu este testat în mod corespunzător; de fapt, nici nu se pune problema că
  ar trebui testat ceva; în schimb, este esențial să ne pierdem timpul cu meniuri
  interactive și citiri de la tastatură
- nu sunt verificate eventuale erori de memorie

Întâi de toate, plecăm de la o premisă greșită, și anume că am avea nevoie să
reimplementăm clase deja definite. Autorul limbajului recomandă în mod explicit
să folosim [`std::vector` în loc de vectori stil C][cg-rsl-arrays]
și [`std::string` în loc de `char*`][cg-rstr-string],
dar noi știm mai bine.

#### Ce motive serioase am avea să rescriem aceste clase?

Am vrea să rescriem clasa `std::vector` pentru a putea face atribuiri în siguranță
în cazul în care sunt aruncate excepții.

Am vrea să rescriem clasa `std::string` ca să putem face prelucrări pe text
codificat ca UTF-8 în mod portabil, fără să fim nevoiți să folosim biblioteci
imense ca [ICU](https://icu.unicode.org/).

În curs/seminar/alte materiale de laborator nu apar deloc justificările de mai sus.
Mai mult, nu se spune nimic despre Unicode/UTF-8 în niciun curs din facultate de
licență sau master (doar într-un curs de licență și unul de master se menționează
în treacăt, dar sunt greșeli în ambele locuri).

Eu unul nu știu ce alte motive am avea să reinventăm roata.
Dacă știți alte motive, vă rog să îmi spuneți și mie.

#### Cum verificăm dacă avem erori de memorie?

Cu [Valgrind](https://valgrind.org/) și
[sanitizers](https://github.com/google/sanitizers) (Google).
Valgrind nu merge pe Windows, iar pe macOS nu merg sanitizers pentru memory leaks
(evident că nu merg nici pe Windows).
Am decis să folosim GitHub Actions ca să nu fie nevoie să vă configurați nimic local.

Pe Windows există într-adevăr [DrMemory](https://drmemory.org) (făcut de Google),
însă nu am reușit să îl fac să detecteze ceva util. Dacă reușiți, să îmi spuneți și mie.

Nu știu să existe alte astfel de instrumente care să fie gratuite și să mai și meargă.

În curs/seminar/alte materiale de laborator veți găsi amenințări că aveți memory leaks
dacă nu eliberați memoria, însă nu apar deloc pași concreți prin care
să vedem dacă avem respectivele memory leaks (și locul în care apar).

#### Cum testăm dacă am implementat corect cc și op=?

Întâi ar trebui să ne implementăm `operator==` ca să putem compara două obiecte.
Eventual trebuie implementat și `operator!=` dacă nu folosim C++20: recomandat este
să îl implementăm în funcție de `operator==`.

Vom presupune că această implementare este corectă. CLion poate să genereze definiții
pentru toți operatorii relaționali. De obicei, definițiile respective sunt corecte.

După aceea, pașii sunt următorii:
- facem un obiect `ob1`
- facem un obiect `ob2` ca o copie după `ob1` (prin apelarea cc)
- verificăm că `ob1 == ob2` este `true`
- modificăm unul dintre obiecte
- dacă cc face ce trebuie, obiectele nu ar mai trebui să fie egale: `ob1 != ob2`
ar trebui să fie `true` (`o1 == ob2` să fie `false`)
- facem o atribuire pentru apelarea op=
- verificăm că atribuirea s-a făcut corect și că obiectele sunt egale
- din nou, modificăm unul dintre obiecte
- dacă op= face ce trebuie, obiectele nu ar mai trebui să fie egale

Ar trebui să facem o modificare asupra obiectului astfel încât să fie afectate câmpurile obiectului
care sunt mai speciale (de exemplu cele de tip pointer).

În curs/seminar/alte materiale de laborator nu am văzut astfel de teste/verificări.

### Reimplementare `std::vector`

Nu ne vom complica să folosim templates, însă vom face vectori
pentru o clasă definită de noi:
```c++
class Student {
    std::string nume;
    int grupa;
public:
    Student(std::string nume_, int grupa_) : nume{std::move(nume_)}, grupa{grupa_} {}
};
```

Într-o primă variantă, nici nu putem să construim clasa pentru vector:
```c++
class vector_st {
    Student* v;
    int nr;
public:
    vector_st(Student* v_, int nr_) : v{new Student[nr_]}, nr{nr_} { /*...*/ }
    //                                           ^-- aici face 💥
    ~vector_st() { delete[] v; }
};
```

#### Ce trebuie să facem ca să meargă?

Trebuie să adăugăm în clasa `Student` un constructor fără parametri. Acest constructor
poate fi necesar și dacă vrem să construim un `std::vector` de o anumită dimensiune
fără să specificăm valorile elementelor.

Dacă putem da valori valide tuturor câmpurilor clasei, atunci este în regulă. Dacă
avem valori valide, înseamnă că am putea apela orice funcție membru (detalii
[aici][cg-complete]).

În schimb, dacă nu putem avea valori valide, cu sens, atunci probabil nu ar trebui
să avem constructor fără parametri pentru acea clasă.

Părerea mea este că nu are sens un constructor fără parametri pentru clasa `Student`:
chiar dacă am putea avea nume necunoscut sau incomplet, tot trebuie o grupă și nu
există o grupă "implicită".

Totuși, pentru a continua implementarea, vom adăuga un constructor fără parametri
și vom inițializa atributele direct (detalii
[aici](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-default)):
```c++
class Student {
    std::string nume = "N/A";
    int grupa = 100;
public:
    Student(std::string nume_, int grupa_) : nume{std::move(nume_)}, grupa{grupa_} {}
    Student() = default;
};
```

Ne-am definit destructor, deci ar trebui să redefinim cc și op= (regula celor trei):
```c++
class vector_st {
    Student* v;
    int nr;
public:
    vector_st(Student* v_, int nr_) : v{new Student[nr_]}, nr{nr_} {
        for(int i = 0; i < nr; ++i)
            v[i] = v_[i];
    }

    ~vector_st() { delete[] v; }

    vector_st(const vector_st &other) : v{new Student[other.nr]}, nr{other.nr} {
        for(int i = 0; i < nr; ++i)
            v[i] = other.v[i];
    }

    vector_st& operator=(const vector_st& other) {
        delete[] v;
        v = new Student[other.nr];
        nr = other.nr;
        for(int i = 0; i < nr; ++i)
            v[i] = other.v[i];

        return *this;
    }
};
```

Chiar și la implementarea de mai sus am văzut greșeli prin alte locuri. Ce să mai
vorbim de erori mai subtile...

#### Este nevoie să facem `delete[]` de fiecare dată în op=?

Observăm că nu este nevoie să facem realocări dacă nu avem nevoie de mai mult spațiu.
Vom avea nevoie de un atribut suplimentar pentru a face această optimizare. Nu voi
implementa toate operațiile deoarece nu urmăresc să reimplementez tot, ci să subliniez
greșeli pe care le consider grave. Presupunem că `nr` și `nr_max` sunt sincronizate
corespunzător.

```c++
class vector_st {
    Student* v;
    int nr;
    int nr_max;
public:
    vector_st(Student* v_, int nr_) : v{new Student[nr_]}, nr{nr_}, nr_max{nr} {
        for(int i = 0; i < nr; ++i)
            v[i] = v_[i];
    }

    ~vector_st() { delete[] v; }

    vector_st(const vector_st &other) : v{new Student[other.nr_max]}, nr{other.nr}, nr_max{other.nr_max} {
        for(int i = 0; i < nr; ++i)
            v[i] = other.v[i];
    }

    vector_st& operator=(const vector_st& other) {
        if(nr_max < other.nr_max) {
            delete[] v;
            v = new Student[other.nr_max];
            nr_max = other.nr_max;
        }
        nr = other.nr;
        for(int i = 0; i < nr; ++i)
            v[i] = other.v[i];

        return *this;
    }
};
```

Vestea bună este că am văzut și în alte materiale această idee de optimizare. Vestea
rea este că nu am prea văzut să fie implementată corect. Degeaba facem optimizări
cu alocări exponențiale dacă nu verificăm că avem spațiu destul pentru elementele pe
care le copiem.

Apropo, optimizarea este făcută și de bibliotecile standard, deci reimplementarea până
în acest punct nu aduce nimic în plus. În afară de niște defecte și pierdere de timp.

#### De ce nu este ok să eliminăm duplicarea codului din cc/op= prin apelarea op= din cc?

Să scriem definiția și ne vom da seama:
```c++
class vector_st {
    Student* v;
    int nr;
    int nr_max;
public:
    vector_st(const vector_st &other) : v{???}, nr{???}, nr_max{???} {
        *this = other;
    }
```

Așadar, pentru câmpurile care nu sunt tipuri de date primitive se va apela constructorul,
se va arunca la gunoi rezultatul și se va inițializa din nou în operator=. De asemenea,
ce ne facem dacă nu avem pentru toate atributele constructori fără parametri?

[//]: # (Ne facem că plouă.)

Dacă vrem să eliminăm din duplicarea codului din cc/op=, trebuie să mergem în sens invers
și să apelăm cc din op= printr-un procedeu numit copy and swap. Detalii în tema 2.

#### Ce se întâmplă dacă sunt aruncate excepții în cc/op= din Student?

[//]: # (Imposibil, în curs nu scrie despre asta.)

Dacă am înțeles bine, operațiile de adăugare și de redimensionare pentru structurile de date
din stdlib oferă anumite garanții atunci când pot fi aruncate excepții în constructori.
Astfel, obținem niște **tranzacții**: operația fie reușește complet, fie nu reușește deloc
și suntem în starea de dinaintea începerii operației.

Cu toate acestea, pe implementarea de stdlib pe care m-am uitat nu părea să fie siguranță
la excepții pentru operatorul de atribuire (operator=).

Următoarea idee nu este specifică C++ sau OOP, ci este o tehnică general valabilă.

Pentru implementarea unei tranzacții, pașii la modul general sunt următorii:
- încercăm să facem modificările într-un spațiu temporar
- **după** ce am făcut modificările cu succes:
  - facem curat dacă este cazul
  - mutăm ce avem în spațiul temporar la locul potrivit
- în caz de eșec, ștergem ce avem în spațiul temporar dacă este cazul

În acest fel, **nu stricăm** ce avem deja dacă operația nu reușește.

Această tehnică/strategie este **general valabilă!** Câteva exemple: tranzacții (baze de date,
sisteme bancare etc), update-uri (sisteme de operare), descărcări de fișiere, instalare de
pachete (cu un package manager decent).

Pașii în C++ ar fi:
- alocăm noile resurse într-un spațiu temporar
- copiem ce avem nevoie în noul spațiu alocat
- dacă primii doi pași au reușit, ștergem resursele anterioare și apoi doar interschimbăm niște pointeri
- dacă a crăpat ceva, probabil este suficient să eliberăm resursele alocate la primul pas

Să vedem concret și pentru clasa vector_st:
```c++
class vector_st {
    Student* v;
    int nr;
    int nr_max;
public:
    vector_st(Student* v_, int nr_) : v{new Student[nr_]}, nr{nr_}, nr_max{nr} {
        for(int i = 0; i < nr; ++i)
            v[i] = v_[i];
    }

    ~vector_st() { delete[] v; }

    vector_st(const vector_st &other) : v{new Student[other.nr_max]}, nr{other.nr}, nr_max{other.nr_max} {
        for(int i = 0; i < nr; ++i)
            v[i] = other.v[i];
    }

    vector_st& operator=(const vector_st& other) {
        Student *tmp;
        if(nr_max < other.nr_max) {
            tmp = new Student[other.nr_max];
            nr_max = other.nr_max;
        }
        else {
            tmp = new Student[nr_max];
        }

        for(int i = 0; i < other.nr; ++i)
            tmp[i] = other.v[i];

        nr = other.nr;
        delete[] v;
        v = tmp;

        return *this;
    }
};
```

Prețul plătit pentru această siguranță este un consum dublu de memorie. De asemenea,
nu mai putem face (ușor) optimizarea prin care nu facem alocări de fiecare dată.

Totuși, este suficient de corect codul de mai sus? Ce se întâmplă dacă se aruncă
excepții în op= din Student?
```c++
class Student {
    std::string nume = "N/A";
    int grupa = 100;
public:
    Student(std::string nume_, int grupa_) : nume{std::move(nume_)}, grupa{grupa_} {}
    Student() = default;
    Student& operator=(const Student& other) {
        if(grupa % 100 == 0)
            throw std::runtime_error("Grupă invalidă");
        nume = other.nume;
        grupa = other.grupa;

        return *this;
    }
};
```

Vom avea memory leak în operator= din vector și vom avea bușit nr_max. Ce am putea face?
```c++
    vector_st& operator=(const vector_st& other) {
        Student *tmp = nullptr;
        if(nr_max < other.nr_max) {
            tmp = new Student[other.nr_max];
        }
        else {
            tmp = new Student[nr_max];
        }

        try {
            for (int i = 0; i < other.nr; ++i)
            tmp[i] = other.v[i];
        } catch(std::exception& err) {
            // log error
            delete[] tmp;
            throw;
        }

        nr = other.nr;
        delete[] v;
        v = tmp;
        if(nr_max < other.nr_max) {
            nr_max = other.nr_max;
        }

        return *this;
    }
```

Concluzia este că nu a fost deloc trivial să ne definim operator= astfel încât să nu
stricăm obiectul inițial dacă sunt aruncate excepții în procesul de copiere (fie la
alocarea dinamică, fie la copierea propriu-zisă). Mai mult, nu am reușit să avem un
consum redus de memorie.

Din cauza constructorilor și a destructorilor, în C++ nu avem funcționalitate de
`realloc`. Nu lucrez profesional cu C++, nu știu dacă există vreo soluție mai bună
care să fie și simplu de înțeles. Probabil se poate folosind custom allocators,
doar că nu este simplu și allocators nu prea au legătură cu acest curs. Dacă aflați,
vă rog să îmi spuneți și modific.

În situația în care întâi facem `delete[]` și apoi `new[]` există posibilitatea să
nu avem suficientă memorie pentru a face acel `new[]` deoarece memoria eliberată de
`delete[]` poate fi acaparată între timp de alt proces/fir de execuție. Rezultatul
este că nu reușim copierea și pierdem datele pe care le aveam deja.

Din punctul meu de vedere, este mult mai important să nu pierdem date existente decât
să optimizăm pentru situațiile în care avem `< 2*n` memorie disponibilă. Dacă suntem
cam la limită cu memoria disponibilă, riscul de a nu mai putea aloca spațiu pentru
noile elemente nu este neglijabil.

Dacă avem de făcut astfel de copieri masive de date, consider că ar trebui să ne întrebăm
dacă nu le putem evita cu totul. Ca fapt divers, pe sisteme embedded nu ar trebui să ne
intereseze problema aceasta deoarece probabil nu am folosi alocare dinamică.

Putem simplifica operator= și să nu avem probleme cu excepțiile?

Da, cu copy and swap. Vezi tema 2.

#### Ce se întâmplă dacă facem auto-atribuiri?

În cazurile în care facem întâi `delete[]` și apoi `new[]` poate să sară în aer foarte ușor
(nu zic numai eu asta, vezi
[aici](https://isocpp.org/wiki/faq/assignment-operators#self-assignment-why)).
Din nefericire, este mai greu de demonstrat întrucât avem nevoie de niște alocări
între `delete[]` și `new[]` care să dea peste cap allocator-ul și să nu mai aloce vectorul
nou în aceeași zonă de memorie cu cel vechi.

Dacă folosim un spațiu suplimentar temporar, acest caz particular este rezolvat de la sine
și evităm o comparație în plus. Ne interesează să fie tratat și acest caz pentru a avea
clase cu un comportament intuitiv. Detalii
[aici](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-copy-self).

#### Observație despre operații de mutare

Operațiile de mutare ar trebui să presupună doar interschimbare de pointeri și eventual
eliberarea resurselor. Întrucât niciuna dintre aceste operații nu trebuie să arunce
excepții, nu este o problemă să facem întâi `delete[]` și apoi să interschimbăm pointerii.

De menționat că pentru operator= de mutare ar trebui avut grijă și mai mult la auto-atribuiri.

### Despre `std::string`

Multe dintre observațiile anterioare se aplică și aici. În ceea ce privește excepțiile,
lucrurile sunt un pic mai simple: singura excepție care poate fi aruncată este
`std::bad_alloc` dacă nu avem destulă memorie.

Referitor la optimizări, nu am văzut exemple cu `realloc`.

Totuși, pentru a implementa diverse operații pentru codificarea UTF-8 pe `std::string`
putem refolosi chiar `std::string` deoarece nu prea are rost să ne complicăm cu
gestionarea manuală a memoriei. Iar dacă vrem asta... surpriză! Clasa `std::string`
poate primi ca argument un allocator.

La acest curs nu vorbim despre allocators deoarece sunt utili. În loc să aflăm
despre lucruri care chiar ne pot ajuta cu ceva, este mai bine să reinventăm roata
și să propovăduim `new`/`delete` din moși strămoși.

[//]: # (din prof.dr. în drd. proful nu e prof destul...)
[//]: # (Nu trebuie să avem spirit critic și să ne întrebăm dacă ce învățăm ne ajută.)
[//]: # (După cum bine știm, programarea se bazează pe misticism.)

#### În ce situații ne-ar ajuta allocators la șiruri de caractere?

În multe aplicații se creează multe obiecte mici, dintre care multe sunt șiruri de
caractere. Întrucât nu știm dimensiunile a priori, trebuie alocate dinamic.
Rezultatul este fragmentarea memoriei și irosirea spațiului. Această problemă
nu este specifică C++.

În acest context, ne-ar ajuta un allocator specializat pentru a aloca doar obiecte
de mici dimensiuni pentru a reduce fragmentarea. O optimizare pentru șiruri de
caractere de foarte mici dimensiuni este implementată de bibliotecile standard
prin utilizarea (cu sens!) a uniunilor:
[small string optimization](https://tc-imba.github.io/posts/cpp-sso). O generalizare
a acestei optimizări este folosită în mașinile virtuale pentru diverse limbaje
pentru stocarea obiectelor de mici dimensiuni.

## Despre supraîncărcarea `new` și `delete`

Limbajul C++ ne permite să supraîncărcăm operatorii `new` și `delete` pentru a
facilita utilizarea unor alți algoritmi de alocare dinamică (nu știu cum aș putea
să traduc custom allocators).

Situațiile în care avem nevoie de custom allocators nu sunt neapărat atât de speciale
pe cât se spune în curs. Mai mult, exemplele din curs sunt fix degeaba. Pentru a
nu fi degeaba, ar trebui măcar să punem niște afișări în acei operatori ca să
vedem că într‑adevăr se apelează operatorii definiți de noi.

[//]: # (‑)
[//]: # (non-breaking hyphen)
[//]: # (https://meta.stackexchange.com/questions/363879)

Exemple de custom allocators:
[mimalloc](https://github.com/microsoft/mimalloc) (Microsoft),
[jemalloc](https://github.com/jemalloc/jemalloc) (Facebook),
[tcmalloc](https://github.com/google/tcmalloc) (Google).

Mimalloc mi se pare cel mai bine documentat și conține benchmarks. Pe ce am avut eu
nevoie, nu era o diferență semnificativă între mimalloc și jemalloc. **Nu vă luați
după "reclame"! Întotdeauna faceți măsurători și vedeți concret ce merge mai bine!**

[Aici](https://github.com/mtrebi/memory-allocators) este un repository cu niște allocators
simpli și niște desene.

🚧 de adăugat cum funcționează, setup și în ce situații am folosi așa ceva

[cg-rsl-arrays]: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rsl-arrays
[cg-rstr-string]: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rstr-string
[cg-complete]: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-complete