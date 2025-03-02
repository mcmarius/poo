# Tema 2

### ⚠ Puneți cât mai multe întrebări! Nu există întrebări greșite.
#### Semnalați orice fel de greșeli găsiți!

[//]: # (TODO de adăugat la sfârșit sintaxa în alte limbaje ~~populare~~ studiate în facultate)

[//]: # ([ordonate aproximativ după popularitate])

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

**Moștenirea** este un concept de POO prin care dorim să modelăm legături de tipul "B **este un fel de** A".

Sintaxa pentru moștenire folosește `:`. Exemplu:
```c++
class A {};

class B : A {};
```
Cel mai adesea vom folosi termenii de **clasă de bază** și **clasă derivată**.

O clasă de bază (sau superclasă) reprezintă un concept general sau abstract care acoperă cât mai multe situații.

O clasă derivată (sau subclasă) reprezintă o particularizare a unei clase de bază pentru tratarea unor cazuri speciale
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
    Baza b{1};
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
    `protected`/`public` fără să modificăm și derivatele.
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
- este de preferat să folosim compuneri în loc de moșteniri private/protected deoarece prin compuneri
  clasele depind mai puțin una de alta (vezi mai jos S-ul din SOLID)
- moștenirile `private` și `protected` nu există în alte limbaje și se folosesc în situații rare; detalii
  [aici](https://isocpp.org/wiki/faq/private-inheritance)
  - moștenirea privată este o moștenire de implementare, **nu de interfață**; faptul că folosim moștenire
    este doar un detaliu de implementare
  - dacă derivata moștenește privat baza, putem spune că derivata "reneagă" baza/interfața bazei

**Observații**

1. Specificatorii de acces din C++ sunt la nivel de clasă: putem accesa atributele private ale unui alt obiect
   al aceleiași clase. Nu putem accesa atributele private sau protected ale unui obiect de tip bază _din clasa
   derivată_, deoarece este vorba de altă clasă. Modificați exemplul următor:
```c++
class Baza {
protected:
    int x;
};

class Derivata : public Baza {
public:
    void f(Baza b) {
        x;
        b.x;
    }
};

int main() {
    Baza b;
    Derivata d;
    d.f(b);
}
```

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

Asemănător cu multe alte elemente de sintaxă din C++, și sintaxa de mai sus ar putea fi utilă în situații rare,
dar nu știu care sunt acelea în acest caz.
Un exemplu ar fi la funcțiile virtuale pure (detalii în [secțiunea respectivă](#funcții-virtuale)), însă nici acolo
nu prea are sens să facem acest apel al unei funcții din bază din afara clasei cu sintaxa de nume complet `obiect.Baza::functie()`.
[S-a mai întrebat și altcineva](https://stackoverflow.com/questions/14288594/), dar tot nu am găsit utilitatea.
Dacă aflați exemple de situații cu sens, vă rog să îmi spuneți și mie.

[//]: # (Iar dacă tot am zis de situații rare, să vorbim despre moștenirea multiplă.)

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
#include <utility>

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
#include <utility>

class student {
public:
    ~student() {}
};

int main() {
    student s1; // compilează
    student s2{s1}; // constr de copiere; compilează, dar este deprecated
    student s3{std::move(s2)}; // nu se apelează constr de mutare, ci constr de copiere
    s1 = s2; // op= de copiere; compilează, dar este deprecated
    s2 = std::move(s3); // nu se apelează op= de mutare, ci op= de copiere
    // destructor
}
```

Pentru a ne convinge că nu se mai generează operațiile de mutare, trebuie să ne uităm în codul de asamblare generat.

Codul folosit:
```c++
#include <utility>

class student {
public:
    //~student() {} // singura diferență este decomentarea acestui rând
};

int main() {
    student s1;
    student s2{std::move(s1)};
}

```

<details>
  <summary><code>g++ main_fara_destr.cpp -S -O0 -o -</code> (47 de linii de ASM)</summary>
  <pre lang='asm'>
	.file	"main_fara_destr.cpp"
	.text
	.globl	main
	.type	main, @function
main:
.LFB90:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L3
	call	__stack_chk_fail@PLT
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE90:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.1.0-1ubuntu1~20.04) 11.1.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:  </pre>
</details>

<details>
  <summary><code>g++ main_cu_destr.cpp -S -O0 -o -</code> (100 de linii de ASM)</summary>
  <pre lang='asm'>
	.file	"main_cu_destr.cpp"
	.text
	.section	.text._ZN7studentD2Ev,"axG",@progbits,_ZN7studentD5Ev,comdat
	.align 2
	.weak	_ZN7studentD2Ev
	.type	_ZN7studentD2Ev, @function
_ZN7studentD2Ev:
.LFB91:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE91:
	.size	_ZN7studentD2Ev, .-_ZN7studentD2Ev
	.weak	_ZN7studentD1Ev
	.set	_ZN7studentD1Ev,_ZN7studentD2Ev
	.text
	.globl	main
	.type	main, @function
main:
.LFB93:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-10(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt4moveIR7studentEONSt16remove_referenceIT_E4typeEOS3_
	leaq	-9(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7studentD1Ev
	leaq	-10(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7studentD1Ev
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L4
	call	__stack_chk_fail@PLT
.L4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE93:
	.size	main, .-main
	.section	.text._ZSt4moveIR7studentEONSt16remove_referenceIT_E4typeEOS3_,"axG",@progbits,_ZSt4moveIR7studentEONSt16remove_referenceIT_E4typeEOS3_,comdat
	.weak	_ZSt4moveIR7studentEONSt16remove_referenceIT_E4typeEOS3_
	.type	_ZSt4moveIR7studentEONSt16remove_referenceIT_E4typeEOS3_, @function
_ZSt4moveIR7studentEONSt16remove_referenceIT_E4typeEOS3_:
.LFB94:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE94:
	.size	_ZSt4moveIR7studentEONSt16remove_referenceIT_E4typeEOS3_, .-_ZSt4moveIR7studentEONSt16remove_referenceIT_E4typeEOS3_
	.ident	"GCC: (Ubuntu 11.1.0-1ubuntu1~20.04) 11.1.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4: </pre>
</details>

Nu am rulat cu optimizări deoarece s-ar face diverse... optimizări și nu s-ar vedea vreo diferență;
de exemplu, se elimină din variabile și din codul care nu face de fapt nimic, se face inlining la cod.
În programe mai mari, este posibil ca nu toate aceste optimizări să aibă loc deoarece compilarea
ar dura foarte mult.

Corect ar trebui să definim toate cele trei funcții dacă ne definim una dintre ele explicit:
```c++
class student {
public:
    ~student() {}
    student(const student& other) = default;
    student& operator=(const student& other) = default;
};
```

Dacă ne definim doar constructor de copiere sau operator= de copiere, nu mai avem cm și op= de mutare.

Dacă ne definim doar constructor de mutare sau operator= de mutare, nu mai avem cc și op= de copiere.

Dacă vrem să fim riguroși, avem nevoie de toate 5 atunci când avem nevoie să definim explicit destructorul
(vezi mai jos la destructor virtual).
În acest caz, nu avem de ales și trebuie să le specificăm pe toate (probabil cu `=default`),
de unde și regula celor 5.

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

Detalii și sursa de inspirație [aici](https://howardhinnant.github.io/bloomberg_2016.pdf)/[aici](https://www.accu.org/conf-docs/PDFs_2014/Howard_Hinnant_Accu_2014.pdf).

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
    curs_obligatoriu(const curs_obligatoriu& other) : st(other.st), curs(other) {
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

#### Refolosirea constructorilor din bază

Dacă creăm o derivată și nu adăugăm atribute, am vrea să moștenim constructorii din bază:
```c++
#include <iostream>
#include <string>

class curs {
    std::string prof;
    int nr = 10;
public:
    curs(const std::string& prof_) : prof(prof_) { std::cout << "constructor curs: " << prof << "\n"; }
    curs(const std::string& prof_, int nr_) : prof(prof_), nr(nr_) { std::cout << "constructor curs: " << prof << "\n"; }
    curs(int nr_, const std::string& prof_) : prof(prof_), nr(nr_) { std::cout << "constructor curs: " << prof << "\n"; }
    friend std::ostream& operator<<(std::ostream& os, const curs& c) { os << "curs: " << c.prof << "\n"; return os; }
};

class curs_obligatoriu : public curs {};

int main() {
    using namespace std::string_literals;
    curs_obligatoriu c1{"prof1"s};    // eroare C++ < C++20
                                      // eroare în C++ >= C++20 dacă avem atribute private în derivată 
    curs_obligatoriu c2{"prof2"s, 3}; // eroare
    curs_obligatoriu c3{5, "prof3"s}; // eroare
}
```

**Dacă nu avem nevoie să adăugăm atribute în derivată**, este firesc să vrem să refolosim constructorii din bază.
Pentru C++ dinainte de C++11, acest lucru nu este posibil și trebuie scriși de mână constructori care să dea mai
departe parametrii la clasa de bază. Din fericire, IDE-urile ar trebui să știe să genereze acești constructori.

Începând cu C++11, clauza
[`using baza::baza;`](https://en.cppreference.com/w/cpp/language/using_declaration#Inheriting_constructors)
face disponibili în derivată toți constructorii din bază. Codul din `main`
va compila dacă modificăm clasa derivată de mai sus astfel:
```c++
class curs_obligatoriu : public curs {
    // nu contează specificatorul de acces la aceste clauze baza::baza;
    using curs::curs;
};
```

Toate celelalte atribute se inițializează cu inițializarea din definiția clasei sau prin constructorul
fără parametri:
```c++
class curs_obligatoriu : public curs {
    using curs::curs;

    int x = 5;        // inițializare în definiția clasei
    std::string nume; // se apelează constructorul std::string()
    student stud_;    // se apelează constructorul student()
};
```

**Exercițiu:** verificați ce constructori se apelează.

Dacă avem nevoie să adăugăm atribute în derivată pe care să le și inițializăm diferit, nu ne ajută prea mult să
preluăm constructorii clasei de bază, deoarece oricum trebuie să avem constructori și pentru acest atribut
specific derivatei.

**TODO:** următorul cod poate ar trebui mutat la tema 3, dar îl las momentan aici să vedeți că nu este mult
de scris. Dacă folosim șabloane (templates) de funcții, există un mod succint de a inițializa atributele
într-o derivată, apelând toți constructorii din bază:
```c++
class curs_obligatoriu : public curs {
    std::string nume;
public:
    template <typename... Args> curs_obligatoriu(std::string nume_, Args... args) :
        curs(args...), nume(nume_) {}
};
```

Inițializările din C++ sunt [foarte complicate](https://randomcat.org/cpp_initialization/initialization.svg)
și nu ne interesează să acoperim subiectul. Ca fapt divers (mai mult să îmi răspund la o întrebare),
las [acest link](https://stackoverflow.com/questions/68470625/).

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
- funcții membre nestatice virtuale într-o clasă
- moșteniri virtuale pentru clase de bază în cazul moștenirilor multiple

În această secțiune vorbim doar despre funcții virtuale.
Funcțiile virtuale trebuie să aibă **același antet** și în bază, și în derivate.
Există o singură excepție de la regulă pe care o discutăm mai târziu.

Există câteva funcții într-o clasă care nu pot fi funcții virtuale:
- constructorii
- [funcțiile statice](#funcții-și-atribute-statice): doar funcțiile membre nestatice pot fi virtuale
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
Detalii [aici](https://isocpp.org/wiki/faq/classes-and-objects#sizeof-empty).

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
unde `n` reprezintă multiplul la care să se facă alinierea. Pentru exemplul de mai sus, dacă folosim directiva
`#pragma pack(2)`, `sizeof`-ul claselor `cls2` și `cls3` va fi 22, iar clasa `cls1` va avea `sizeof` 24.

Dacă mai aveam un câmp `char` în clasă, am avea `sizeof` 24 la `cls2` și `cls3`, deoarece mai trebuie un byte de
padding ca să fie multiplu de 2 (parametrul din directiva `#pragma pack`). Dacă folosim `#pragma pack(1)`,
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

Limbajul ne permite să avem funcții virtuale fără să facem și destructorii virtuali. Totuși, nu văd
utilitatea acestei abordări, deoarece nu pot fi reținute decât adresele unor variabile locale și apare
foarte ușor riscul de referințe/pointeri agățate/agățați (dangling reference/pointer). Poate avea sens
atunci când avem legături între clase în ambele direcții, dar tot mi se pare forțat.
Dacă găsiți un exemplu _cu sens_, vă rog să îmi spuneți și mie.

**Destructor protected și non-virtual**

Pentru situațiile în care doar vrem să grupăm atribute și funcționalități comune, însă nu avem nevoie de
funcții virtuale și am folosi doar clase derivate, avem posibilitatea să nu plătim prețul virtualizării.

Din moment ce nu avem funcții virtuale, nici destructorul din bază nu este nevoie să fie virtual.

Totuși, întrucât nu vrem să construim decât obiecte din clase derivate, destructorul bazei nu trebuie să fie public:
dacă destructorul unei clase nu este public, nu avem voie să construim obiecte din acea clasă, deoarece
resursele asociate unui astfel de obiect nu ar putea fi eliberate.

Destructorul clasei de bază nu poate fi privat, deoarece trebuie apelat de clasele derivate.
Prin urmare, destructorul din bază trebuie să fie protected.
Dacă suntem paranoici, putem face protected și constructorii din bază.
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

Destructorii din derivate sunt automat publici, nu trebuie redefiniți. I-am redefinit doar ca să
arătăm că se apelează.

Folosim abordarea descrisă mai devreme dacă vrem să forțăm doar crearea de obiecte derivate și nu avem nevoie de
funcții virtuale.

**Exercițiu:** afișați sizeof-urile claselor de mai sus. Comparați aceste sizeof-uri dacă ați face
destructorul virtual (dar tot protected). Opțional, completați codul cu ce mai doriți:
constructori, funcții ajutătoare etc.

**Nu apelăm funcții virtuale în constructori și destructori!**

Dacă funcțiile respective nu sunt virtuale pure, nu este o problemă dpdv al limbajului, dar poate fi sursă de confuzie.
Această regulă este specifică limbajului C++. Dacă apelăm funcții virtuale pure în constructori/destructori, avem
comportament nedefinit, deci 💥️

Detalii [aici](https://en.cppreference.com/w/cpp/language/virtual#During_construction_and_destruction) și
[aici](https://isocpp.org/wiki/faq/strange-inheritance#calling-virtuals-from-ctors).

În limbaje interpretate (dinamice) se pot apela fără probleme funcții virtuale în constructori.

Dacă totuși dorim să apelăm implementarea respectivă, folosim sintaxa explicită de apel non-virtual:
```c++
class Baza {
public:
    virtual void f() {}
    Baza() { Baza::f(); }
};

class Derivata : public Baza {
public:
    void f() override {}
    Derivata() { Derivata::f(); }
};
```

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

Codul compilează (transformarea codului sursă în cod obiect), dar crapă la etapa de linking,
deoarece nu este găsită definiția destructorului din clasa de bază.

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

Opțional, de citit un pic și de [aici](https://en.wikipedia.org/wiki/Call_super).

#### Interfață non-virtuală

Funcțiile virtuale publice au dezavantajul că derivatele pot schimba în mod complet interfața clasei de bază.
Avem flexibilitatea să schimbăm în derivate comportamentul din baze, însă nu putem să modificăm în mod uniform
comportamentul derivatelor fără să facem modificări în toate derivatele.

Interfața non-virtuală (**NVI** - non-virtual interface) este o rețetă prin care:
- derivatele nu pot modifica structura interfeței din bază la nivel înalt și
- obținem posibilitatea de a modifica în mod uniform toate derivatele fără să schimbăm în mod
  explicit codul din derivate.

Astfel, separăm interfața de detaliile de implementare. Această tehnică nu este o particularitate de C++.

```c++
class curs {
public:
    void evalueaza() {
        std::cout << "evaluarea a început\n";
        examineaza();
        corecteaza();
        noteaza();
        std::cout << "evaluarea s-a încheiat\n";
    }
private:
    virtual void examineaza() = 0;
    virtual void corecteaza() = 0;
    virtual void noteaza() = 0;
};

class curs_obligatoriu : public curs {
private:
    void examineaza() override { /* codul din curs_obligatoriu::examineaza() */ }
    void corecteaza() override { /* codul din curs_obligatoriu::corecteaza() */ }
    void noteaza() override { /* codul din curs_obligatoriu::noteaza() */ }
};

class curs_optional : public curs {
private:
    void examineaza() override { /* codul din curs_optional::examineaza() */ }
    void corecteaza() override { /* codul din curs_optional::corecteaza() */ }
    void noteaza() override { /* codul din curs_optional::noteaza() */ }
};
```

Dacă dorim să modificăm comportamentul funcției `evalueaza` în toate derivatele în același fel, este simplu:
```c++
#include <iostream>
#include <chrono>

class curs {
public:
    void evalueaza() {
        using namespace std::chrono_literals;
        std::cout << "evaluarea a început\n";
        examineaza();
        ia_pauza(35min);
        corecteaza();
        ia_pauza(3h);
        noteaza();
        std::cout << "evaluarea s-a încheiat\n";
    }
private:
    virtual void examineaza() = 0;
    virtual void corecteaza() = 0;
    virtual void noteaza() = 0;
    void ia_pauza(auto durata) {
        std::cout << "o bine meritată pauză de "
                  << std::chrono::seconds(durata).count() << " (de) secunde\n";
    }
};
```

**Codul din derivate este neschimbat!**

Iar acum să vedem varianta în care nu ne complicăm cu atâtea funcții și folosim funcții virtuale publice:
```c++
#include <iostream>
#include <chrono>

class curs {
public:
    virtual void evalueaza() = 0;
};

class curs_obligatoriu : public curs {
public:
    void evalueaza() override {
        // codul din curs_obligatoriu::examineaza()
        // codul din curs_obligatoriu::corecteaza()
        // codul din curs_obligatoriu::noteaza()
    }
};

class curs_optional : public curs {
public:
    void evalueaza() override {
        // codul din curs_optional::examineaza()
        // codul din curs_optional::corecteaza()
        // codul din curs_optional::noteaza()
    }
};
```

Într-adevăr, pentru programe mici, codul este mai simplu și în aparență nu se justifică să ne complicăm cu
funcții separate.

Încercăm să aplicăm modificările de mai devreme pe codul de acum:
```c++
#include <iostream>
#include <chrono>

class curs {
public:
    virtual void evalueaza() = 0;
protected:
    void ia_pauza(auto durata) {
        std::cout << "o bine meritată pauză de "
                  << std::chrono::seconds(durata).count() << " (de) secunde\n";
    }
};

class curs_obligatoriu : public curs {
public:
    void evalueaza() override {
        using namespace std::chrono_literals;
        std::cout << "evaluarea a început\n";
        // codul din curs_obligatoriu::examineaza()
        ia_pauza(35min);
        // codul din curs_obligatoriu::corecteaza()
        ia_pauza(3h);
        // codul din curs_obligatoriu::noteaza()
        std::cout << "evaluarea s-a încheiat\n";
    }
};

class curs_optional : public curs {
public:
    void evalueaza() override {
        using namespace std::chrono_literals;
        std::cout << "evaluarea a început\n";
        // codul din curs_optional::examineaza()
        ia_pauza(35min);
        // codul din curs_optional::corecteaza()
        ia_pauza(3h);
        // codul din curs_optional::noteaza()
        std::cout << "evaluarea s-a încheiat\n";
    }
};
```

Acest cod este mai ușor de scris (un simplu copy-paste), dar mult mai greu de întreținut pe termen mediu-lung.

Pe măsură ce adăugăm noi derivate, continuăm să duplicăm codul din ce în ce mai mult. Este foarte ușor să
uităm să preluăm toate modificările în noile derivate. Mai grav, dacă vrem să mai modificăm comportamentul
comun din derivate, avem de înlocuit de fiecare dată în n locuri, n fiind numărul de derivate.

Bonus, funcția `evalueaza` este publică virtuală, deci nu avem un mecanism să impunem o structură comună
pentru o nouă derivată. Derivata poate suprascrie complet toate funcțiile virtuale.

Dacă folosim o interfață non-virtuală, de fiecare dată avem de modificat într-un singur loc! De asemenea,
derivatele nu pot suprascrie decât partea de detaliu a interfeței, nu interfața cu totul.

Interfața non-virtuală presupune următoarele convenții:
- clasa de bază definește interfața prin funcții publice non-virtuale
- clasa de bază declară detaliile de implementare prin funcții virtuale private (sau virtuale protected)
  - nu este obligatoriu ca toate funcțiile virtuale să fie virtuale pure
- clasele derivate suprascriu doar funcțiile virtuale private (sau protected)

Este de preferat ca majoritatea funcțiilor din bază să fie private, nu protected. Facem protected doar
funcțiile care trebuie apelate explicit din derivate.

Exemple de comportamente care pot fi impuse de o clasă de bază pentru toate derivatele:
- logging și/sau monitorizare
- caching
- debugging
- pre-condiții (de exemplu setup/verificări comune) și post-condiții (de exemplu cleanup comun)

Caz particular:
```c++
class curs {
public:
    void evalueaza() {
        evalueaza_();
        // sau
        evalueaza_impl();
        //sau
        do_evalueaza();
    }
private:
    virtual void evalueaza_() = 0;
    virtual void evalueaza_impl() = 0;
    virtual void do_evalueaza() = 0;
};
```

Interfața non-virtuală este de obicei utilă și dacă nu avem mai multe etape în funcția publică. Nu există
o convenție standard pentru denumirea funcției virtuale private. Singura restricție ar fi
[să nu înceapă cu `_`.](https://stackoverflow.com/questions/228783/)

Având în vedere că nu putem prezice viitorul și ce modificări va trebui să facem, costul de a adăuga câteva rânduri
în plus în clasa de bază este neglijabil în comparație cu rescrierea ulterioară a codului în mai multe derivate.
Pe de altă parte, dacă unele funcții nu sunt foarte strâns legate de clasă, o idee mai bună este să folosim
compunerea și să extragem acele funcții în una sau mai multe clase noi.

Sursa de inspirație și detalii [aici](http://www.gotw.ca/publications/mill18.htm).

Sunt și situații în care nu este nevoie să ne complicăm cu NVI, deoarece funcția este prea simplă.
Singura situație pe care o știu este definirea de constructori virtuali.

**Exerciții:** adăugați constructori, atribute, afișări, implementări pentru funcțiile virtuale
și ce mai lipsește în exemplele din această secțiune.

#### Constructori virtuali

Denumirea de constructor virtual este o tehnică de programare. Din punct de vedere al sintaxei, nu există
constructori virtuali.

Facem o scurtă pauză de clase abstracte. Dacă avem o ierarhie și folosim pointeri sau referințe către clasa
de bază, este foarte ușor să feliem accidental obiectele (object slicing) cu transmitere prin valoare:
```c++
#include <iostream>

class baza {
public:
    virtual void f() const {
        std::cout << "f bază\n";
    }
};

class derivata : public baza {
public:
    void f() const override {
        std::cout << "f derivată\n";
    }
};

void g1(baza b) {
    std::cout << "g1\n";
    b.f();
}

baza g2(baza& b) {
    std::cout << "g2\n";
    return b;
}

int main() {
    derivata d;
    g1(d);
    baza b1 = g2(d);
    b1.f();
    const baza& b2 = g2(d);
    b2.f();
}
```

Dacă nu avem nevoie de un nou obiect, înlocuim transmiterea/întoarcerea prin valoare cu referințe.
Dar dacă avem nevoie să copiem obiecte și avem doar pointer sau referință către bază?

Vom afla răspunsul după un exemplu mai stufos. Revenim la clase abstracte.

Exemplul următor este doar cu scop ilustrativ pentru a scrie mai puțin. Nu îl folosiți ca model pentru teme.
```c++
#include <iostream>

class curs {
public:
    virtual void prezentare() = 0;
    virtual ~curs() = default;
};

class curs_obligatoriu : public curs {
    int nr_prezentare = 0;
public:
    void prezentare() override {
        std::cout << "prezentare obligatorie " << ++nr_prezentare << "\n";
    }
};

class curs_optional : public curs {
    bool interactiv = false;
public:
    void prezentare() override {
        std::cout << "prezentare opțională" << (interactiv ? " interactivă" : "") << "\n";
    }
};

class student {
    curs* m_curs;
public:
    student(curs* curs_) : m_curs(curs_) {}
    ~student() { delete m_curs; }
    void prezinta() { m_curs->prezentare(); }
    void schimba_curs(curs* curs_) { m_curs = curs_; }
};

int main() {
    curs* c1 = new curs_obligatoriu;
    curs* c2 = new curs_optional;
    student st1{c1};
    std::cout << "st1 prezintă\n";
    st1.prezinta();
    std::cout << "st1 schimbă cursul\n";
    st1.schimba_curs(c2);
    std::cout << "st1 prezintă\n";
    st1.prezinta();
}
```

Codul de mai sus funcționează fără probleme în aparență. Cine ar trebui să facă `new` și `delete`? Ar trebui
făcut `new` în constructorul de la student? Ar trebui făcut `delete` în funcția main?

Avem un memory leak deoarece c1 rămâne alocat. Ar trebui făcut `delete` în `schimba_curs`?
```
./main
st1 prezintă
prezentare obligatorie 1
st1 schimbă cursul
st1 prezintă
prezentare opțională

=================================================================
==15278==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x7fe1bce055a7 in operator new(unsigned long) ../../../../src/libsanitizer/asan/asan_new_delete.cpp:99
    #1 0x558266acf47c in main main.cpp:46
    #2 0x7fe1bc7fd082 in __libc_start_main ../csu/libc-start.c:308

SUMMARY: AddressSanitizer: 16 byte(s) leaked in 1 allocation(s).
```

Să modificăm funcția main astfel încât să mai adăugăm un student:
```c++

int main() {
    curs* c1 = new curs_obligatoriu;
    student st1{c1};
    std::cout << "st1 prezintă\n";
    st1.prezinta();
    student st2{st1};
    std::cout << "st1 prezintă\n";
    st1.prezinta();
    std::cout << "st2 prezintă\n";
    st2.prezinta();
}
```

Acum codul ar trebui să crape:
```
./main
st1 prezintă
prezentare obligatorie 1
st1 prezintă
prezentare obligatorie 2
st2 prezintă
prezentare obligatorie 3
=================================================================
==14997==ERROR: AddressSanitizer: heap-use-after-free on address 0x602000000010 at pc 0x563662293901 bp 0x7ffc37a26a40 sp 0x7ffc37a26a30
READ of size 8 at 0x602000000010 thread T0
    #0 0x563662293900 in student::~student() main.cpp:29
    #1 0x5636622935ac in main main.cpp:51
```

Să mai vedem un exemplu. Înlocuim funcția main cu:
```c++
int main() {
    curs* c1 = new curs_obligatoriu;
    curs* c2 = new curs_optional;
    student st1{c1};
    std::cout << "st1 prezintă\n";
    st1.prezinta();
    student st2{c2};
    std::cout << "st1 prezintă\n";
    st1.prezinta();
    std::cout << "st2 prezintă\n";
    st2.prezinta();
    std::cout << "st2 = st1;\n";
    st2 = st1;
    std::cout << "st1 prezintă\n";
    st1.prezinta();
    std::cout << "st2 prezintă\n";
    st2.prezinta();
}
```

Crapă similar:
```
./main
st1 prezintă
prezentare obligatorie 1
st1 prezintă
prezentare obligatorie 2
st2 prezintă
prezentare opțională
st2 = st1;
st1 prezintă
prezentare obligatorie 3
st2 prezintă
prezentare obligatorie 4
=================================================================
==15762==ERROR: AddressSanitizer: heap-use-after-free on address 0x602000000010 at pc 0x556b72b7e977 bp 0x7ffc0a62c1a0 sp 0x7ffc0a62c190
READ of size 8 at 0x602000000010 thread T0
    #0 0x556b72b7e976 in student::~student() main.cpp:29
    #1 0x556b72b7e61f in main main.cpp:51
```

**De ce crapă?**

Dacă avem atribute de tip pointer, constructorul de copiere, operator= și destructorul generate implicit de compilator
cel mai probabil nu fac ce trebuie.

Pe exemplul de aici, constructorul de copiere și operator= copiază pointeri. Un pointer reține o adresă de memorie.
Chiar dacă fiecare student are un câmp separat cu câte un pointer, valoarea reținută de acești pointeri este
aceeași după ce folosim cc sau op=.

Înainte ca programul să crape, observăm că ambii studenți incrementează același contor din `curs_obligatoriu`.

**De ce vrem să folosim pointeri?**

Deoarece vrem să apelăm funcții virtuale prin pointeri de bază. Nu trebuie să modificăm nimic în clasa `student`
ca să funcționeze în continuare, oricâte clase derivate am crea din `curs`.

Pentru ce facem la acest laborator, în orice alte situații nu prea are sens să folosim pointeri, deoarece ne-am
complica inutil.

**Ce ar trebui să scriem în constructorul de copiere și operator=?**

Răspunsul corect este în secțiunea următoare.

Să încercăm să scriem constructorul de copiere. Cursul din obiectul nou construit ar trebui să fie un pointer
către un nou curs, deci trebuie să folosim `new`:
```c++
class student {
    curs* m_curs;
public:
    student(const student& other) {
        m_curs = new ???(other.m_curs);
    }
};
```

Trebuie să facem `new curs_obligatoriu` sau `new curs_optional`?

Cele două soluții aparent simple și la îndemână sunt următoarele:
- modificăm clasa `curs` și includem un câmp pentru a reține tipul subclasei și eventual un enum cu toate tipurile
- folosim dynamic_cast/typeid și încercăm cu if/else if cast-uri la fiecare subclasă

Clasa `curs` se transformă astfel:
```c++
class curs {
public:
    virtual void prezentare() = 0;
    virtual ~curs() = default;
    enum tip { Obligatoriu, Optional };
    tip get_tip() const { return m_tip };
private:
    tip m_tip;
};
```

În clasele derivate trebuie să inițializăm în toți constructorii noul câmp:
```c++
class curs_obligatoriu : public curs {
    // restul
public:
    // restul
    curs_obligatoriu() : curs(curs::Obligatoriu) {}
};
```

Procedăm asemănător pentru toate clasele derivate.

Nu este nevoie să suprascriem și constructorul de copiere, deoarece acesta funcționează corect
și în clasa de bază, și în derivate.

Acum avem tot ce ne trebuie pentru a defini constructorul de copiere din clasa `student`:
```c++
class student {
    curs* m_curs;
public:
    // restul
    student(const student& other) {
        switch(other.m_curs->get_tip()) {
            case curs::Obligatoriu:
                m_curs = new curs_obligatoriu(*static_cast<curs_obligatoriu*>(other.m_curs));
                break;
            case curs::Optional:
                m_curs = new curs_optional(*static_cast<curs_optional*>(other.m_curs));
                break;
            default:
                // eroare, caz lipsă!!!
                m_curs = nullptr;
                break;
        }
    }
};
```

Presupunând că inițializăm întotdeauna corect câmpul `m_tip` din clasa `curs`, este în regulă să facem
`static_cast`, deoarece câmpul `m_tip` este modificat doar la crearea unui obiect. Fiecare instrucțiune
`new` va apela constructorul de copiere al subclasei adecvate.

`static_cast<curs_obligatoriu*>(other.m_curs)` convertește cursul din `other` de la `curs*` la `curs_obligatoriu*`.
În mod normal, această conversie nu este corectă, întrucât `curs*` poate să arate către orice subclasă.
Aici ne bazăm pe faptul că am inițializat corect câmpul pentru tip.

Mai departe, constructorul de copiere apelat de `new` are nevoie de o referință la `curs_obligatoriu`, dar noi
avem un pointer. De aceea, ultimul pas este să dereferențiem rezultatul cast-ului.

Dezavantajul major al acestei abordări este că trebuie să modificăm codul în multe locuri atunci când avem
nevoie să adăugăm o nouă derivată. Switch-ul respectiv se va repeta peste tot pe unde avem nevoie să creăm o
copie a unui curs, nu doar în clasa `student`.

Un alt dezavantaj este că avem nevoie de un câmp suplimentar în clasa de bază și creștem consumul de memorie
pentru toate obiectele derivate, _pe lângă_ costul indus de funcțiile virtuale.

Pentru dynamic cast/typeid, codul este similar și dezavantajele sunt aceleași, cu mici variații.
Vedeți [secțiunea respectivă](#dynamic-cast) pentru detalii.

Dacă nu folosim clase abstracte, apare și pericolul de object slicing.

**Dacă avem instrucțiuni `if`/`else` pe tipuri de date, cel mai adesea este greșit!**

Soluția este să folosim funcții virtuale. În loc să verificăm noi manual tipul unui obiect polimorfic, vom
delega responsabilitatea creării unei copii chiar obiectului pe care vrem să îl copiem.

Pentru a preveni object slicing, vom ascunde cc și op=, deci nu mai trebuie să fie publice. Totuși,
dacă vrem să copiem obiecte, este nevoie să facem cc și op= protected ca să poată fi apelate de clasele derivate:
```c++
class curs {
public:
    virtual void prezentare() = 0;
    virtual ~curs() = default;
protected:
    curs(const curs& other) = default;
    curs& operator=(const curs& other) = default;
};
```

**Atenție!** Dacă schimbăm comportamentul implicit al unui constructor, nu se mai generează
constructorul fără parametri nici pentru derivate:
```c++
class curs_obligatoriu : public curs {
public:
    void prezentare() override {}
};

int main() {
    curs_o c1;   // eroare!!!
    curs c2{c1}; // ok dacă l-am putea construi pe c1
}
```

Pentru a remedia situația, trebuie să definim constructorul fără parametri în bază. Chiar dacă ne definim
constructori cu parametri în derivate, baza tot trebuie inițializată, iar compilatorul apelează implicit
constructorul fără parametri din bază, constructor care este inexistent.

**Exerciții:**
- de ce nu putem defini constructorul fără parametri doar în derivate?
- de ce nu ar fi în regulă să apelăm din derivată constructorul de copiere al bazei cu `this`?
  - `curs_obligatoriu() : curs(*this) {}`

[//]: # (clone public, cc/op= protected, la fel pt cele de mutare)

[//]: # (https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-copy)

**Constructorii virtuali** sunt prin convenție niște funcții virtuale numite `clone`. Folosim constructori
virtuali pentru a copia în mod corect obiecte prin pointeri sau referințe către bază.
```c++
#include <iostream>

class curs {
public:
    virtual void prezentare() = 0;
    virtual curs* clone() const = 0;
    virtual ~curs() = default;
    curs() = default;
protected:
    curs(const curs& other) = default;
    curs& operator=(const curs& other) = default;
};

class curs_obligatoriu : public curs {
    int nr_prezentare = 0;
public:
    void prezentare() override {
        std::cout << "prezentare obligatorie " << ++nr_prezentare << "\n";
    }

    curs* clone() const override { return new curs_obligatoriu(*this); }
};

class curs_optional : public curs {
    bool interactiv = false;
public:
    void prezentare() override {
        std::cout << "prezentare opțională" << (interactiv ? " interactivă" : "") << "\n";
    }

    curs* clone() const override { return new curs_optional(*this); }
};

void f1(curs* c) {
    std::cout << "begin f1\n";
    curs* d = c->clone();
    c->prezentare();
    d->prezentare();
    delete d;
    std::cout << "end f1\n";
}

void f2(curs& c) {
    std::cout << "begin f2\n";
    curs* d = c.clone();
    c.prezentare();
    d->prezentare();
    delete d;
    std::cout << "end f2\n";
}

int main() {
    curs* oop = new curs_obligatoriu;
    f1(oop);
    f2(*oop);
    delete oop; // 🙂️
}
```

Deși funcția `clone` ar putea avea implementare dacă nu am avea alte funcții virtuale pure, am vrea să forțăm
toate derivatele să implementeze `clone` pentru că altfel nu se apelează și constructorul de copiere din derivate.
De aceea, vom prefera să facem întotdeauna funcția `clone` să fie virtuală pură.

Observăm că funcțiile `f1` și `f2` nu se folosesc decât de referințe și pointeri la clasa de bază `curs`. Avem
posibilitatea să adăugăm oricâte subclase, iar funcțiile `f1` și `f2` vor funcționa corect în continuare, fără
să fie nevoie de modificări.

Ca fapt divers, antetul unei funcții virtuale poate diferi în derivate prin tipul de retur dacă avem tipuri de date
covariante. Cu alte cuvinte, în derivate avem voie să scriem așa:
```c++
class curs_obligatoriu : public curs {
    // restul
public:
    // restul
    curs_obligatoriu* clone() const override { return new curs_obligatoriu(*this); }
};
```

Avem aceeași posibilitate și dacă trebuie să întoarcem referințe: putem întoarce `baza&` într-o funcție virtuală
din bază și `derivata&`.

Acest aspect al limbajului ne ajută să scăpăm de cast-uri atunci când știm că avem tipul de date derivat și
trebuie să apelăm funcții din derivată care nu sunt și în bază. Totuși, nu este ceva esențial.

O posibilă greșeală când implementăm constructori virtuali este următoarea:
```c++
class curs_obligatoriu : public curs {
    // restul
public:
    // restul
    curs* clone() const override { return new curs_obligatoriu(); }
};
```

Nu se mai apelează constructorul de copiere, ci constructorul fără parametri. Chiar dacă primim un obiect nou,
acesta nu conține datele pe care voiam să le copiem.

Avantajul esențial al constructorilor virtuali este că nu ne umplem programul de `if`/`else`-uri pe tipuri de date.
Atunci când creăm o nouă derivată, doar implementăm `clone` și creăm un obiect de acest subtip în main.
**Restul codului nu se modifică și funcționează cu noua derivată!**

Pentru ce facem noi, este ok să lăsăm funcția `clone` virtuală și publică, întrucât nu vom avea nevoie să îi
modificăm în vreun fel comportamentul.

În alte limbaje, clonarea se mai numește "deep copy". Unele limbaje fac "shallow copy" cu funcția `clone` și
folosesc constructori de copiere pentru "deep copy". Ideea în sine de a avea nevoie de obiecte
complet independente o veți regăsi și în viitor sub o formă sau alta.

**Reamintim** că nu apelăm funcții virtuale în constructori și destructori în C++ deoarece este
comportament nedefinit 💥

#### Copy and swap și RAII

Am văzut în secțiunea precedentă modul prin care copiem obiecte prin pointeri sau referințe către clasa de bază.

În clasa `student` avem ca atribut un pointer la un curs și apăreau probleme din cauza cc și op= generate de
compilator. Nu suntem mulțumiți cu abordarea prezentată mai devreme pentru că avem multe modificări de făcut
în momentul în care definim o nouă clasă derivată. Acest inconvenient apărea din cauză că nu aveam un mecanism
de clonat obiecte prin pointeri de bază.

Vom considera ierarhia claselor pentru cursuri ca fiind cea din secțiunea anterioară. Să reluăm definiția
clasei `student`:
```c++
class student {
    curs* m_curs;
public:
    student(curs* curs_) : m_curs(curs_) {}
    ~student() { delete m_curs; }
    void prezinta() { m_curs->prezentare(); }
    void schimba_curs(curs* curs_) { m_curs = curs_; }
};
```

Pentru a elimina dilema cu cine ar trebui să facă `new` și `delete`, vom face `new` în constructori (și funcțiile
similare) și `delete` în destructor:
```c++
class student {
    curs* m_curs;
public:
    student(const curs& curs_) : m_curs(curs_.clone()) {}
    ~student() { delete m_curs; }
    void prezinta() { m_curs->prezentare(); }
    void schimba_curs(const curs& curs_) { delete m_curs; m_curs = curs_.clone(); }
};
```

Această abordare nu este neapărat eficientă din punctul de vedere al memoriei, însă este mai sigură.

În funcția `main` vom avea câte un `delete` pentru fiecare `new`. Este important să nu folosim `new`
direct în lista de parametri a unui apel, deoarece s-ar crea un obiect temporar pe care nu l-am mai
putea elibera.

Filozofia C++ în privința gestionării resurselor este [RAII](https://en.cppreference.com/w/cpp/language/raii)
(resource acquisition is initialization):
- resursele se alocă în constructori
- resursele se eliberează în destructori

Dacă am scris destructorii corect, aceștia se vor apela automat în momentul potrivit și nu există risc de
resource leaks. Pentru ca această strategie să funcționeze, este important să **nu folosim `new`
decât în constructori!**

Consecința este că ar trebui să apelăm `clone` doar în constructori sau în funcții care se comportă
ca niște constructori.

În alte limbaje, un bloc `finally` (sau similar) este folosit pentru eliberarea manuală a resurselor.

Am suprascris destructorul. Regula celor trei ne spune că ar trebui să suprascriem și cc, și op=:
```c++
class student {
    curs* m_curs;
public:
    student(const curs& curs_) : m_curs(curs_.clone()) {}
    student(const student& other) : m_curs(other.m_curs->clone()) {}

    student& operator=(const student& other) {
        if(this != &other) {
            delete m_curs;
            m_curs = other.m_curs->clone();
        }
        return *this;
    }

    ~student() { delete m_curs; }
    void prezinta() { m_curs->prezentare(); }
    void schimba_curs(const curs& curs_) { delete m_curs; m_curs = curs_.clone(); }
};
```

Mai multe detalii despre auto-atribuiri [aici](/obs.md#ce-se-întâmplă-dacă-facem-auto-atribuiri).

Exemplul nu este tocmai realist: un student poate să aibă mai multe cursuri. Vom folosi `std::vector`
pentru că nu are rost să reinventăm roata:
```c++
#include <vector>

class student {
    std::vector<curs*> cursuri;
public:
    student() = default;

    student(const std::vector<curs*> cursuri_) {
        for(const auto& curs : cursuri_)
            cursuri.emplace_back(curs->clone());
    }

    student(const student& other) {
        for(const auto& curs : other.cursuri)
            cursuri.emplace_back(curs->clone());
    }

    student& operator=(const student& other) {
        if(this != &other) {
            for(auto& curs : cursuri)
                delete curs;
            cursuri.clear();
            for(const auto& curs : other.cursuri)
                cursuri.emplace_back(curs->clone());
        }
        return *this;
    }

    ~student() {
        for(auto& curs : cursuri)
            delete curs;
    }

    void prezinta() {
        for(auto& curs : cursuri)
            curs->prezentare();
    }
};
```

Logica din operatorul de atribuire (op=) nu este deloc trivială și este ușor să facem greșeli la gestionarea
resurselor. De asemenea, implementarea prezintă câteva posibile defecte întrucât întâi ștergem resursele existente
și abia apoi încercăm să alocăm alte resurse.

Ca regulă generală, în multe cazuri este mai bine să alocăm întâi noile resurse într-o zonă temporară și să
eliberăm resursele vechi de-abia după ce noile resurse au fost alocate cu succes. După acești pași, ce ne rămâne
de făcut sunt interschimbări de pointeri, operații care nu ar trebui să eșueze.

O discuție mai amănunțită a acestui subiect găsiți [aici](/obs.md#reimplementare-stdvector).

Remarcăm faptul că repetăm logica din constructorul de copiere și din destructor. Ne vom folosi de cc pentru
alocarea noilor resurse într-o variabilă temporară și apoi de destructor pentru eliberarea vechilor resurse.
Pentru a elibera resursele vechi, acestea trebuie să ajungă în obiectul temporar. Cum facem asta? Cu o simplă
interschimbare de pointeri!

```c++
#include <utility> // std::swap

class student {
    // restul
public:
    // restul
    student& operator=(const student& other) {
        if(this != &other) {
            auto tmp_student{other};
            std::swap(cursuri, tmp_student.cursuri);
        }
        return *this;
    }
};
```

Mult mai puțin cod, mult mai puține șanse să greșim ceva! De menționat că optimizăm crearea unei copieri
în caz de auto-atribuire, dar ar trebui să definim separat op= de mutare.

Codul se poate simplifica un pic mai mult și obținem simultan op= de copiere și op= de mutare:

```c++
#include <utility> // std::swap

class student {
    // restul
public:
    // restul
    student& operator=(student other) {
        std::swap(cursuri, other.cursuri);
        return *this;
    }
};
```

Acum este prea simplu, îl complicăm la loc. Convenția este să folosim o funcție friend pentru a face partea de
swap. Dacă avem mai multe atribute, este nevoie de swap pentru fiecare atribut în parte:
```c++
#include <vector>
#include <string>
#include <utility> // std::swap

class student {
    std::vector<curs*> cursuri;
    std::string nume;
public:
    // restul; trebuie actualizat cc să copieze și numele
    student& operator=(student other) {
        swap(*this, other);
        return *this;
    }

    friend void swap(student& st1, student& st2) {
        std::swap(st1.cursuri, st2.cursuri);
        std::swap(st1.nume, st2.nume);
    }
};
```

De ce facem swap-ul funcție friend?

Pentru situația de mai sus nu este nevoie. Este util ca să simplificăm funcțiile de swap mai complexe din cauza
regulilor limbajului. Funcțiile friend sunt găsite de
[ADL (argument-dependent lookup)](https://en.cppreference.com/w/cpp/language/adl).

Ca să înțelegem mai bine, mai complicăm un pic exemplul:
```c++
#include <iostream>
#include <vector>
#include <string>
#include <utility> // std::swap

class facultate {
    std::string nume;
public:
    friend void swap(facultate& f1, facultate& f2) {
        std::cout << "swap custom facultate\n";
        std::swap(f1.nume, f2.nume);
    }
};

class student {
    std::vector<curs*> cursuri;
    std::string nume;
    facultate facultate_;
public:
    // restul
    student& operator=(student other) {
        swap(*this, other);
        return *this;
    }

    friend void swap(student& st1, student& st2) {
        std::swap(st1.cursuri, st2.cursuri);
        std::swap(st1.nume, st2.nume);
        swap(st1.facultate_, st2.facultate_);
    }
};
```

La fel cum clasa `student` are nevoie de o funcție specială (custom) de swap, este posibil ca și alte clase să
aibă nevoie de astfel de funcții speciale de swap. Am adăugat o astfel de funcție în clasa `facultate` cu scop
demonstrativ. Confirmați că vă apare mesajul din funcția swap din clasa `facultate`.

Funcțiile din spații de nume (de exemplu `std::`) nu sunt căutate de ADL, fiindcă ADL caută doar
funcții fără prefix de spațiu de nume.

Pentru a avea codul uniform, este comun să folosim `using std::swap;` pentru a activa ADL și pentru funcția
swap predefinită:
```c++
#include <iostream>
#include <vector>
#include <string>
#include <utility> // std::swap

class facultate {
    std::string nume;
public:
    friend void swap(facultate& f1, facultate& f2) {
        using std::swap;
        std::cout << "swap custom facultate\n";
        swap(f1.nume, f2.nume);
    }
};

class student {
    std::vector<curs*> cursuri;
    std::string nume;
    facultate facultate_;
public:
    // restul
    student& operator=(student other) {
        swap(*this, other);
        return *this;
    }

    friend void swap(student& st1, student& st2) {
        using std::swap;
        swap(st1.cursuri, st2.cursuri);
        swap(st1.nume, st2.nume);
        swap(st1.facultate_, st2.facultate_);
    }
};
```

**Bonus:** de ce nu putem folosi `std::swap` în felul următor?

```c++
class student {
    // restul
public:
    // restul
    student& operator=(student other) {
        if(this != &other) {
            std::swap(*this, other);
        }
        return *this;
    }
};
```

**Exercițiu:** rulați ca să vă convingeți: `std::swap` apelează operatorul de atribuire și avem recursie infinită.

#### Smart pointers

**Important!** Indiferent de ce fel de pointeri folosim, trebuie să ne asigurăm că nu dereferențiem pointeri nuli
sau neinițializați. Este redundant să mai facem verificări doar dacă avem garanția că un pointer se inițializează
corect în toate cazurile și nu există riscul să folosim pointerul după ce obiectul către care arată a fost
eliberat (dangling pointer).

Pe măsură ce programul crește în complexitate, vom avea din ce în ce mai multe alocări dinamice. Chiar și în codul
de până acum nu respectăm în totalitate RAII pentru că nu facem `new` doar în constructori. Trebuie să ne asigurăm
că fiecare `new` are un `delete` asociat, dar nu înseamnă că doar numărăm câte instrucțiuni `new` și câte `delete`
avem. Există situații când multe new-uri sunt eliberate de un singur delete din destructor. Datorită RAII este mai
rar în C++ să avem mai multe delete-uri decât new-uri, dar în C este destul de frecvent.

Acest curs nu este de algoritmică, nu consider esențial să pierdem timp cu gestionarea explicită a memoriei.
Recomandarea mea este să folosiți smart pointers: astfel, nu ne mai interesează când trebuie făcut `delete`.

Nu este obligatoriu să folosiți smart pointers, dar este obligatoriu să verificați că nu aveți erori de memorie,
indiferent dacă folosiți smart pointers sau nu. Este posibil să avem erori de memorie, inclusiv memory leaks, și
dacă folosim smart pointers.

Biblioteca standard de C++ are 3 tipuri de smart pointers: `shared_ptr`, `weak_ptr` și `unique_ptr`.

Un dezavantaj este că nu avem tipuri de date covariante în cazul smart pointers (cel puțin nu ușor), însă este
irelevant pentru acest laborator.

`std::shared_ptr` pot fi ineficienți în situații reale. Câteva dezavantaje sunt contorul intern care trebuie
sincronizat între firele de execuție și crearea multor copii ale pointerului. Probabil sunt și alte motive,
dar nu am mai căutat pentru că nu este relevant. Ca exemplu, `std::shared_ptr` sunt
[interziși](https://chromium.googlesource.com/chromium/src/+/main/styleguide/c++/c++-features.md#Shared-Pointers-banned)
în proiectul Chromium. În schimb, acolo există smart pointers specializați; exemplu:
[MiraclePtr](https://docs.google.com/document/d/1pnnOAIz_DMWDI4oIOFoMAqLnf_MZ2GsrJNb_dbQ3ZBg/edit).

##### shared_ptr

Cel mai simplu de folosit la acest laborator este `shared_ptr`:
- înlocuim pointerii simpli `T* variabila;` cu `std::shared_ptr<T> variabila;`
- înlocuim `new T(arg1, arg2, ...)` cu `std::make_shared<T>(arg1, arg2, ...)`
- nu mai avem `delete`

Concret, în destructor nu mai avem nimic, iar singurele locuri cu alocări explicite au fost funcțiile `clone`:
```c++
// înainte
curs* curs_obligatoriu::clone() const override {
    return new curs_obligatoriu(*this);
}

// destructor cu delete în clasa student

// după
std::shared_ptr<curs> curs_obligatoriu::clone() const override {
    return std::make_shared<curs_obligatoriu>(*this);
}

student::~student() = default; // nu mai este nevoie de delete
```

Restul codului rămâne la fel.

Pentru ce facem noi la acest laborator, este suficient `std::shared_ptr`.
[Recomandările din domeniu](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-unique_ptr)
sunt de obicei cu `std::unique_ptr` (secțiunea următoare), dar este mult mai simplu cu `std::shared_ptr`
din punct de vedere didactic.

---

Acest tip de pointeri numără referințele către obiectul alocat și distruge obiectul atunci când numărul de
referințe ajunge la zero. Consecința este că avem memory leak dacă numărul de referințe nu ajunge niciodată
la zero.
```c++
#include <memory>

class B;
class A {
    std::shared_ptr<B> b;
public:
    void set(std::shared_ptr<B> b_) { b = b_; }
};

class B {
    std::shared_ptr<A> a;
public:
    void set(std::shared_ptr<A> a_) { a = a_; }
};

int main() {
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();
    a.set(b);
    b.set(a);
}
```

Sanitizers nu detectează acest caz. Valgrind ne semnalează următoarele:
```
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./main
==15891== Memcheck, a memory error detector
==15891== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==15891== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==15891== Command: ./main
==15891==
==15891==
==15891== HEAP SUMMARY:
==15891==     in use at exit: 64 bytes in 2 blocks
==15891==   total heap usage: 3 allocs, 1 frees, 72,768 bytes allocated
==15891==
==15891== 32 bytes in 1 blocks are indirectly lost in loss record 1 of 2
==15891==    at 0x483CFE3: operator new(unsigned long) (vg_replace_malloc.c:422)
==15891==    by 0x10AA8F: __gnu_cxx::new_allocator<std::_Sp_counted_ptr_inplace<B, std::allocator<B>, (__gnu_cxx::_Lock_policy)2> >::allocate(unsigned long, void const*) (new_allocator.h:121)
==15891==    by 0x10A69C: allocate (allocator.h:173)
==15891==    by 0x10A69C: std::allocator_traits<std::allocator<std::_Sp_counted_ptr_inplace<B, std::allocator<B>, (__gnu_cxx::_Lock_policy)2> > >::allocate(std::allocator<std::_Sp_counted_ptr_inplace<B, std::allocator<B>, (__gnu_cxx::_Lock_policy)2> >&, unsigned long) (alloc_traits.h:460)
==15891==    by 0x10A22B: std::__allocated_ptr<std::allocator<std::_Sp_counted_ptr_inplace<B, std::allocator<B>, (__gnu_cxx::_Lock_policy)2> > > std::__allocate_guarded<std::allocator<std::_Sp_counted_ptr_inplace<B, std::allocator<B>, (__gnu_cxx::_Lock_policy)2> > >(std::allocator<std::_Sp_counted_ptr_inplace<B, std::allocator<B>, (__gnu_cxx::_Lock_policy)2> >&) (allocated_ptr.h:97)
==15891==    by 0x109ED9: std::__shared_count<(__gnu_cxx::_Lock_policy)2>::__shared_count<B, std::allocator<B>>(B*&, std::_Sp_alloc_shared_tag<std::allocator<B> >) (shared_ptr_base.h:648)
==15891==    by 0x109CE7: std::__shared_ptr<B, (__gnu_cxx::_Lock_policy)2>::__shared_ptr<std::allocator<B>>(std::_Sp_alloc_shared_tag<std::allocator<B> >) (shared_ptr_base.h:1337)
==15891==    by 0x109BDC: std::shared_ptr<B>::shared_ptr<std::allocator<B>>(std::_Sp_alloc_shared_tag<std::allocator<B> >) (shared_ptr.h:409)
==15891==    by 0x109AF7: std::shared_ptr<B> std::allocate_shared<B, std::allocator<B>>(std::allocator<B> const&) (shared_ptr.h:861)
==15891==    by 0x1097DE: std::shared_ptr<B> std::make_shared<B>() (shared_ptr.h:877)
==15891==    by 0x10927B: main (main.cpp:18)
==15891==
==15891== 64 (32 direct, 32 indirect) bytes in 1 blocks are definitely lost in loss record 2 of 2
==15891==    at 0x483CFE3: operator new(unsigned long) (vg_replace_malloc.c:422)
==15891==    by 0x10A9C3: __gnu_cxx::new_allocator<std::_Sp_counted_ptr_inplace<A, std::allocator<A>, (__gnu_cxx::_Lock_policy)2> >::allocate(unsigned long, void const*) (new_allocator.h:121)
==15891==    by 0x10A45C: allocate (allocator.h:173)
==15891==    by 0x10A45C: std::allocator_traits<std::allocator<std::_Sp_counted_ptr_inplace<A, std::allocator<A>, (__gnu_cxx::_Lock_policy)2> > >::allocate(std::allocator<std::_Sp_counted_ptr_inplace<A, std::allocator<A>, (__gnu_cxx::_Lock_policy)2> >&, unsigned long) (alloc_traits.h:460)
==15891==    by 0x10A00D: std::__allocated_ptr<std::allocator<std::_Sp_counted_ptr_inplace<A, std::allocator<A>, (__gnu_cxx::_Lock_policy)2> > > std::__allocate_guarded<std::allocator<std::_Sp_counted_ptr_inplace<A, std::allocator<A>, (__gnu_cxx::_Lock_policy)2> > >(std::allocator<std::_Sp_counted_ptr_inplace<A, std::allocator<A>, (__gnu_cxx::_Lock_policy)2> >&) (allocated_ptr.h:97)
==15891==    by 0x109D75: std::__shared_count<(__gnu_cxx::_Lock_policy)2>::__shared_count<A, std::allocator<A>>(A*&, std::_Sp_alloc_shared_tag<std::allocator<A> >) (shared_ptr_base.h:648)
==15891==    by 0x109C93: std::__shared_ptr<A, (__gnu_cxx::_Lock_policy)2>::__shared_ptr<std::allocator<A>>(std::_Sp_alloc_shared_tag<std::allocator<A> >) (shared_ptr_base.h:1337)
==15891==    by 0x109BA2: std::shared_ptr<A>::shared_ptr<std::allocator<A>>(std::_Sp_alloc_shared_tag<std::allocator<A> >) (shared_ptr.h:409)
==15891==    by 0x109A9B: std::shared_ptr<A> std::allocate_shared<A, std::allocator<A>>(std::allocator<A> const&) (shared_ptr.h:861)
==15891==    by 0x109725: std::shared_ptr<A> std::make_shared<A>() (shared_ptr.h:877)
==15891==    by 0x10926F: main (main.cpp:17)
==15891==
==15891== LEAK SUMMARY:
==15891==    definitely lost: 32 bytes in 1 blocks
==15891==    indirectly lost: 32 bytes in 1 blocks
==15891==      possibly lost: 0 bytes in 0 blocks
==15891==    still reachable: 0 bytes in 0 blocks
==15891==         suppressed: 0 bytes in 0 blocks
==15891==
==15891== For lists of detected and suppressed errors, rerun with: -s
==15891== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

Dacă avem nevoie de pointeri în ambele direcții și vrem să folosim `std::shared_ptr`, trebuie să decidem
în ce direcție acest pointer este opțional pentru a elimina referințele circulare. Marcăm legătura mai slabă
cu `std::weak_ptr`.
```c++
#include <memory>

class B;
class A {
    std::shared_ptr<B> b;
public:
    void set(std::shared_ptr<B> b_) { b = b_; }
};

class B {
    std::weak_ptr<A> a;
public:
    void set(std::weak_ptr<A> a_) { a = a_; }
};

int main() {
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();
    a.set(b);
    b.set(a);
}
```

Legătura mai slabă o folosim de obicei pentru a simplifica logica programului.

Exemplu:
```c++
#include <memory>

class Calator;
class Bilet {
    std::weak_ptr<Calator> calator;
};

class Calator {
    std::shared_ptr<Bilet> bilet;
};
```

Călătorul gestionează existența obiectului bilet. Obiectul de tip călător nu trebuie să dispară dacă eliminăm un
bilet. În sens invers, atunci când un obiect de tip călător nu mai există, biletul dispare automat.

Noțiuni asemănătoare cu pointerii shared există și în Rust și Swift.

[//]: # (make_shared_from_this, dynamic_pointer_cast)

##### unique_ptr

Pointerii unici sunt eficienți pentru că nu au nevoie de sincronizări și de obicei nu creăm noi pointeri, ci
mutăm pointerul, adică transferăm resursa unui alt obiect.

Pentru a folosi acești pointeri, pașii ar fi următorii:
- pointerii se declară cu `std::unique_ptr<T> variabila;`
- inițializarea se face su `std::make_unique<T>(arg1, arg2, ...);`
- dacă vrem să plimbăm pointerii dintr-o funcție în alta **trebuie să folosim `std::move`** din `<utility>`
- nu mai avem `delete`
- orice clasă care conține un câmp de tip `unique_ptr` are implicit constructorul de copiere și
  operator= de copiere dezactivate, deoarece pointerii unici nu pot fi copiați
  - dacă vrem să copiem obiecte ale acestei clase, trebuie să ne definim cc și op= de copiere
  - alternativ, folosim `std::move` pentru obiectele acestei clase

Folosirea operațiilor de mutare în loc de operații de copiere oferă performanță, dar are efect de domino.
Din motive didactice, am preferat să evit promovarea `std::unique_ptr`. Ne interesează mai mult concepte
de OOP decât să umplem programul cu `std::move` și alt [**cod de umplutură**](https://stackoverflow.com/a/30885842)
necesar ca operațiile de mutare să funcționeze corect.

#### Funcție de afișare

Am văzut mai devreme un mod de a face afișarea pentru obiecte din clase derivate:
```c++
#include <string>
#include <iostream>

class curs {
public:
    friend std::ostream& operator<<(std::ostream& os, const curs& curs_) {
        os << "Curs: " << curs_.nume << "\n";
        return os;
    }

private:
    std::string nume = "OOP";
};

class curs_obligatoriu : public curs {
public:
    friend std::ostream& operator<<(std::ostream& os, const curs_obligatoriu& curs_) {
        os << static_cast<const curs&>(curs_)
           << "\t" << curs_.nr_prezentari << " prezentări\n";
        return os;
    }

private:
    int nr_prezentari = 2;
};

int main() {
    curs_obligatoriu c1;
    std::cout << c1;
    curs& c2 = c1;
    std::cout << c2;
    curs* c3 = &c1;
    std::cout << *c3;
}
```

Afișarea prin `operator<<` se uită la tipul de date declarat, așadar funcționează corect pentru obiecte derivate.
Nu funcționează pentru referințe și pointeri de bază, tipul de date declarat fiind clasa de bază.

Pentru a rezolva problema, vom folosi o funcție protected virtuală constantă `afisare`:
```c++
#include <string>
#include <iostream>

class curs {
public:
    virtual ~curs() = default;

    friend std::ostream& operator<<(std::ostream& os, const curs& curs_) {
        curs_.afisare(os);
        return os;
    }
protected:
    virtual void afisare(std::ostream& os) const {
        os << "Curs: " << nume << "\n";
    }
private:
    std::string nume = "OOP";
};

class curs_obligatoriu : public curs {
protected:
    void afisare(std::ostream& os) const override {
        curs::afisare(os);
        os << "\t" << nr_prezentari << " prezentări\n";
    }
private:
    int nr_prezentari = 2;
};

int main() {
    curs_obligatoriu c1;
    std::cout << c1;
    curs& c2 = c1;
    std::cout << c2;
    curs* c3 = &c1;
    std::cout << *c3;
}
```

Nu există o convenție consacrată pentru denumirea acestei funcții: `afis`, `afisare`, `print`, `show`, `display`
etc. Nu contează ce nume alegem, dar este bine să păstrăm aceeași denumire dacă avem nevoie de afișări
polimorfice în mai multe clase în același program.

Vrem să facem funcția de afișare protected fiindcă este un detaliu de implementare. Respectăm (parțial) ideea de
[interfață non-virtuală](#interfață-non-virtuală), unde interfața (funcția publică) este `operator<<`.

Totuși, dacă _toate_ derivatele ar trebui să apeleze afișarea din bază, mai bine regândim operatorul de afișare
pentru a evita cod repetitiv [din vina noastră](https://en.wikipedia.org/wiki/Call_super).

Poate nu toate derivatele adaugă atribute pe care să le afișeze, motiv pentru care nu facem funcția de afișare
virtuală pură. Acum nu mai facem nimic în funcția de afișare din bază, deci nu avem motiv să o apelăm din
derivate, așa că o putem face private. Rezultatul este următorul:
```c++
class curs {
public:
    virtual ~curs() = default;

    friend std::ostream& operator<<(std::ostream& os, const curs& curs_) {
        os << "Curs: " << curs_.nume;
        curs_.afisare(os);
        os << "\n";
        return os;
    }
private:
    virtual void afisare(std::ostream& os) const {}

    std::string nume = "OOP";
};

class curs_obligatoriu : public curs {
private:
    void afisare(std::ostream& os) const override {
        os << "\t" << nr_prezentari << " prezentări";
    }

    int nr_prezentari = 2;
};
```

#### Diverse (funcții virtuale)

[//]: # (Alte funcții virtuale)

Dacă avem nevoie să apelăm din main implementarea unei funcții virtuale pure publice dintr-o clasă de bază,
există o sintaxă specială de C++ care ignoră virtualizarea (qualified name lookup):
```c++
#include <iostream>

class baza {
public:
    virtual void f() const = 0;
};

void baza::f() const { std::cout << "f bază\n"; }

class derivata : public baza {
public:
    void f() const override { std::cout << "f derivată\n"; }
};

int main() {
    derivata d;
    std::cout << "d.f(): ";
    d.f();
    std::cout << "d.baza::f(): ";
    d.baza::f();
    baza& b1 = d;
    std::cout << "b1.f(): ";
    b1.f();
    std::cout << "b1.baza::f(): ";
    b1.baza::f();
    baza* b2 = &d;
    std::cout << "b2->f(): ";
    b2->f();
    std::cout << "b2->baza::f(): ";
    b2->baza::f();
}
```

Din câte știu, sintaxa nu există în alte limbaje. De asemenea, este cam inutil să avem nevoie de așa ceva
pentru că funcțiile virtuale nu ar trebui să fie publice ca să respecte rețeta de interfață non-virtuală.

Nu este ceva extrem de ezoteric, s-au mai întrebat și [alții](https://stackoverflow.com/questions/15853031).
Este un hack. Dacă ajungeți în situația de a crede că aveți nevoie de asta, gândiți-vă foarte bine dacă nu
v-ar ajuta mai mult o variantă de interfață non-virtuală.

---

#### Exemplu complet funcții virtuale

Exemplul următor pune cap la cap toate conceptele prezentate în această secțiune referitoare la funcții virtuale.
Poate fi folosit ca sursă de inspirație pentru partea de funcții virtuale din tema 2, însă nu este suficient,
fiind doar un exemplu minimalist cu scop demonstrativ.

Codul este lăsat în interiorul claselor pentru a ocupa mai puțin spațiu pe ecran. În funcția main trebuie să
aveți (mult) mai multe exemple. Testarea op= din student este făcută să vedem că merge, dar în proiecte mai
mari este foarte posibil să avem nevoie de atribuiri, deci trebuie să funcționeze corect.

```c++
#include <iostream>
#include <algorithm> // std::max
#include <memory>
#include <string>
#include <utility> // std::move, std::swap
#include <vector>

class curs {
public:
    virtual ~curs() = default;
    virtual std::shared_ptr<curs> clone() const = 0;
    double nota_finala() const { return nota_finala_(); }

    friend std::ostream &operator<<(std::ostream &os, const curs &curs_) {
        os << "Curs: " << curs_.nume;
        curs_.afisare(os);
        os << "\n";
        return os;
    }

    explicit curs(std::string nume_) : nume(std::move(nume_)) {}

    // dacă folosim unique_ptr probabil trebuie activate operațiile de mutare
    curs(curs &&other) = default;
    curs &operator=(curs &&other) = default;
protected:
    curs(const curs &other) = default;
    curs &operator=(const curs &other) = default;

private:
    virtual double nota_finala_() const = 0;
    virtual void afisare(std::ostream &) const {}

    std::string nume;
};

class curs_obligatoriu : public curs {
public:
    explicit curs_obligatoriu(
            const std::string &nume, double laborator = 11, double examen = 9.5, bool seminar = false,
            int nrPrezentari = 1) : curs(nume), laborator(laborator), examen(examen), seminar(seminar),
                                    nr_prezentari(nrPrezentari) {}

    std::shared_ptr<curs> clone() const override { return std::make_shared<curs_obligatoriu>(*this); }

private:
    double nota_finala_() const override { return laborator * 0.4 + seminar * 0.1 + examen * 0.5; }

    void afisare(std::ostream &os) const override {
        os << "\tlaborator: " << laborator << "\n"
           << "\texamen: " << examen << "\n"
           << "\tseminar: " << (seminar ? "da" : "nu") << "\n"
           << "\t" << nr_prezentari << " prezentări";
    }

    double laborator = 0;
    double examen = 0;
    bool seminar = false;
    int nr_prezentari = 0;
};

class curs_optional : public curs {
public:
    curs_optional(const std::string &nume, int nrRaspunsuri, double notaPrezentare) : curs(nume),
                                                                                      nr_raspunsuri(nrRaspunsuri),
                                                                                      nota_prezentare(notaPrezentare) {}

    std::shared_ptr<curs> clone() const override { return std::make_shared<curs_optional>(*this); }

private:
    double nota_finala_() const override { return std::max(nr_raspunsuri, 10) * 0.1 + nota_prezentare; }

    void afisare(std::ostream &os) const override {
        os << "\tprezentare: " << nota_prezentare << "\n"
           << "\t" << nr_raspunsuri << " răspunsuri";
    }

    int nr_raspunsuri = 0;
    double nota_prezentare = 0;
};

class student {
    std::string nume;
    std::vector<std::shared_ptr<curs>> cursuri;
public:
    double medie_finala() const {
        double total = 0;
        for (auto &curs: cursuri)
            total += curs->nota_finala();

        return total / cursuri.size();
    }

    // student(std::string nume, const std::vector<std::shared_ptr<curs>> &cursuri_) : nume(std::move(nume)) {
    //     for (const auto &curs: cursuri_)
    //         cursuri.emplace_back(curs->clone());
    // }
    student(std::string nume, std::vector<std::shared_ptr<curs>> cursuri) : nume(std::move(nume)),
                                                                            cursuri(std::move(cursuri)) {}

    student(const student &other) : nume(other.nume) {
        for (const auto &curs: other.cursuri)
            cursuri.emplace_back(curs->clone());
    }

    student &operator=(student other) {
        swap(*this, other);
        return *this;
    }

    friend void swap(student &st1, student &st2) {
        std::swap(st1.cursuri, st2.cursuri);
        std::swap(st1.nume, st2.nume);
    }

    friend std::ostream &operator<<(std::ostream &os, const student &student) {
        os << "nume student: " << student.nume << "\ncursuri:\n";
        for (const auto &curs: student.cursuri)
            os << *curs;
        os << "\n";
        return os;
    }
};

class facultate {
    std::string nume;
    std::vector<student> studenti;
public:
    explicit facultate(std::string nume) : nume(std::move(nume)) {}
    void adauga(const student &st) { studenti.emplace_back(st); }

    friend std::ostream &operator<<(std::ostream &os, const facultate &facultate) {
        os << "nume facultate: " << facultate.nume << "\nstudenti:\n";
        for (const auto &student: facultate.studenti)
            os << student;
        // os << "\n";
        return os;
    }
};

int main() {
    student st1{"m", {
            curs_obligatoriu{"POO", 12, 9.8}.clone(),
            curs_obligatoriu{"BD", 10, 9, false, 0}.clone(),
            curs_obligatoriu{"TW", 9, 8, true, 0}.clone(),
            curs_optional{"NLP", 5, 10}.clone()
    }};
    student st2{"c", {
            curs_obligatoriu{"POO", 12}.clone(),
            curs_obligatoriu{"BD", 9.5, 10, true, 5}.clone(),
            curs_obligatoriu{"TW", 9, 9, true, 0}.clone(),
            curs_optional{"CV", 3, 10}.clone()
    }};
    student st3{"z", {
            curs_obligatoriu{"POO", 9, 8}.clone(),
            curs_obligatoriu{"BD", 9, 9, true, 3}.clone(),
            curs_obligatoriu{"TW", 10, 9, false, 0}.clone(),
            curs_optional{"SP", 6, 9.9}.clone()
    }};

    std::cout << st1.medie_finala() << "\n";
    std::cout << st2.medie_finala() << "\n";
    std::cout << st3.medie_finala() << "\n";
    facultate fac1{"FMI"};
    fac1.adauga(st1);
    fac1.adauga(st2);
    std::cout << fac1;
    st1 = st2;
    std::cout << "---\ndupa op=: " << st1 << "---\n";

    facultate fac2 = facultate{"poli"};
    fac2.adauga(st3);
    std::cout << fac2;
}
```

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

#### Ce să NU faceți cu funcții virtuale

Dată fiind următoarea ierarhie:

```c++
class Baza {
public:
  virtual void f() = 0; 
  virtual ~Baza() = default;
};

class D1 : public Baza {
public: void f() override() { /* ... */ }
};

class D2 : public Baza {
public: void f() override() { /* ... */ }
};
```

1. Apel prin obiecte derivate

```c++
class Aplicatie {
  D1 d1;
  D2 d2;
public:
  void g() { d1.f(); d2.f(); }
};
```

De ce e greșit? Sunt apeluri normale de funcții, nu folosim cu nimic virtualizarea.

2. Apel prin obiecte separate explicite

```c++
class Aplicatie {
  Baza* d1;  // arată către un D1
  Baza* d2;  // arată către un D2
public:
  void g() { d1->f(); d2->f(); }
};
```

De ce e greșit? Avem nevoie de câte un obiect separat pentru fiecare nouă derivată.

Asta înseamnă că avem de modificat în foarte multe locuri dacă vrem să extindem sau să schimbăm codul.
În plus, pierdem în mod inutil informație despre tip dacă ne interesează doar anumite derivate concrete.

Soluția ar fi să ținem obiectele într-o colecție (de exemplu un vector).

3. Poluarea interfețelor

```c++
class Aplicatie {
public:
  void f1() {
    // folosește f() din D1
  }
  void f2() {
    // folosește f() din D2
  }
};
```

De ce e greșit? Nu ar trebui să schimbăm interfața _altei_ clase atunci când adăugăm/schimbăm derivate.

Tocmai asta ar fi ideea, să **nu** modificăm deloc codul în `Aplicatie` sau ce clasă se folosește de
interfața definită de noi.

Variație a acestei greșeli: adăugăm câte o nouă funcție în clasa de bază.

Altă variație: necesitatea adăugării unor "else if"-uri în `Aplicatie` sau în clasa de bază atunci când adăugăm o nouă
derivată.

4. Dynamic casts pentru fiecare derivată

De ce e greșit? Dacă trebuie să tratăm în mod diferit fiecare derivată, înseamnă că de fapt acele clase
nu prea au nimic în comun, deci ar putea fi clase independente una de alta.

Pe de altă parte, este posibil să ne fi definit interfața clasei de bază greșit și de fapt să putem veni
cu o abstractizare uniformă pentru majoritatea derivatelor.

Care e problema? În timp, sigur vom uita să adăugăm pe undeva o ramură de "else if" cu o nouă derivată
și nu vom sesiza greșeala decât după mult timp, iar apoi pierdem timp să depanăm în loc să fi folosit în
mod corespunzător funcții virtuale și problema să nu existe deloc.

### Excepții

Excepțiile sunt un mecanism de tratare a erorilor. Cel mai simplu exemplu de eroare este să știm dacă execuția
unui program s-a încheiat cu succes. Un program este reprezentat de unul sau mai multe procese gestionate de
sistemul de operare. Sistemul de operare primește de la program (proces) un număr care ne spune dacă au fost
sau nu erori. Întoarcem acest număr prin funcția `main`:
```c++
int main() {
    return 1;
}
```

O convenție uzuală este să folosim 0 pentru succes și un număr întreg (sau natural) nenul pentru eșec. Dacă
vrem portabilitate pe sisteme de operare mai ezoterice, există constantele `EXIT_SUCCESS` și `EXIT_FAILURE`
din `<cstdlib>`/`<stdlib.h>`.

Din terminal de bash, codul de eroare al ultimului proces este reținut în variabila `$?`. Dacă
rulăm programul de mai sus, ar trebui să afișeze codul de eroare pe care îl punem în cod:
```bash
$ g++ main.cpp -o main
$ ./main
$ echo $?
1
```

Din terminal de cmd, variabila se numește `%errorlevel%`. Există comenzi similare și în powershell.
```
> g++ main.cpp -o main.exe
> main.exe
> echo %errorlevel%
1
```

Excepțiile reprezintă un alt mod de a semnala erori. Pentru a înțelege excepțiile, de ce vrem să le folosim
și în ce situații este bine/nu este bine să le folosim, este mai ușor să vedem întâi ce alternative avem.

#### Alternative

Alternativele la excepții sunt următoarele:
- coduri de eroare
- tipuri de date rezultat (result types)

Vezi și [aici](https://github.com/SFML/SFML/issues/2139#issue-1279145220).

Tratarea erorilor folosind coduri de eroare este cel mai simplu mecanism de a indica reușita sau eșecul în urma
unui apel de funcție:
```c++
#include <vector>

int calcul_medie(std::vector<int> note, int& rezultat) {
    rezultat = 0;
    if(note.size() < 3)
        return 1; // note prea puține
    for(int nota : note) {
        rezultat += nota;
        if(nota < 5) {
            rezultat = 4;
            return 2; // note prea mici
        }
    }
    rezultat /= note.size();
    return 0;
}
```

Funcția de mai sus întoarce un anumit cod pentru a face distincția între diverse categorii de erori, iar
rezultatul îl găsim în parametrul `rezultat` transmis prin referință. Pentru cazuri simple, am putea întoarce
rezultatul direct în `return`, fără parametri auxiliari, cu condiția ca valorile să nu se suprapună cu codurile
de eroare.

Dacă avem de întors mai multe valori, grupăm atributele într-o structură sau clasă. Dacă trebuie să întoarcem
și un cod de eroare, ar trebui să revenim la varianta cu transmiterea rezultatului ca referință.

O variantă simplă ar fi să întoarcem un obiect cu atribute invalide/nule/setate pe zero. Aceasta nu este deloc
o idee bună în cele mai multe situații, întrucât nu exprimăm într-un mod clar faptul că avem erori.

Odată ce programul crește în dimensiuni, este anevoios să depanăm sau să extindem codul când avem foarte multe
coduri de eroare. Aceste coduri de eroare ar trebui documentate. Un mod de a realiza această documentare este
să utilizăm niște enumerări:
```c++
#include <vector>

enum class rezultat_calcul { ok, note_prea_putine, note_prea_mici };

rezultat_calcul calcul_medie(std::vector<int> note, int& rezultat) {
    rezultat = 0;
    if(note.size() < 3)
        return rezultat_calcul::note_prea_putine;
    for(int nota : note) {
        rezultat += nota;
        if(nota < 5) {
            rezultat = 4;
            return rezultat_calcul::note_prea_mici;
        }
    }
    rezultat /= note.size();
    return rezultat_calcul::ok;
}
```

Chiar dacă acum este mai mult cod, codul este mai ușor de înțeles când avem sute sau mii de tipuri de erori și
este mai rapid să căutăm după nume decât după numere. Desigur, pentru programe mici nu se justifică să ne complicăm.

Observăm că abordarea de mai sus poate necesita câte un `enum` pentru fiecare funcție/clasă/modul. O abordare
generală folosește tipuri de date rezultat sau [result types](https://en.wikipedia.org/wiki/Result_type)
inspirate din programarea funcțională. Unele limbaje pot beneficia de cod simplificat dacă folosesc pattern matching.

Pe scurt, avem un nou nivel de abstractizare: folosim o uniune pentru a reprezenta fie rezultatul funcției noastre,
fie codul de eroare. O bază în C++17 pentru acest stil de tratare a erorilor este clasa șablon
[`std::variant`](https://en.cppreference.com/w/cpp/utility/variant), urmând să fie completată în C++23 de
[`std::expected`](https://en.cppreference.com/w/cpp/header/expected). Există deja această funcționalitate
sub formă de [bibliotecă externă](https://github.com/TartanLlama/expected) cu funcții ajutătoare în plus.

Un exemplu foarte schițat arată în felul următor:
```c++
#include <variant>

class calcul {};
class eroare {};

std::variant<calcul, eroare> f(int nota) {
    if(nota < 5) {
        return eroare{nota, "prea mică"};
    }
    return calcul{nota + 1};
}

void g() {
    auto rezultat = f(5);
    if(calcul *x = std::get_if<calcul>(&rezultat)) {
        // folosește x
    }
    else {
        // eroarea este în std::get_if<eroare>(&rezultat) sau std::get<eroare>(rezultat)
    }
}
```

Dacă vă interesează subiectul, discutăm la tema 3 (dacă avem timp). Abordările nu se exclud: există
[biblioteci](https://www.boost.org/doc/libs/develop/libs/system/doc/html/system.html)
care combină tipuri de date rezultat cu excepții. Ca fapt divers, a existat o
[tentativă](https://stackoverflow.com/questions/28746372/system-error-categories-and-standard-system-error-codes)
mai low-level și la nivel de limbaj, dar pare o varză, nu recomand.

Nu există o definiție complet obiectivă pentru ce ar trebui considerat eroare. Este responsabilitatea noastră
să alegem nivelul de detaliu.

#### Aserțiuni

Aserțiunile (instrucțiunile `assert`) sunt folosite doar în etapa de dezvoltare pentru condiții care trebuie
să fie adevărate întotdeauna și care pot fi false doar din neatenția noastră. **Nu folosim aserțiuni pentru
validarea datelor de intrare!** Sunt două motive pentru care aserțiunile nu ne ajută:
- aserțiunile se dezactivează atunci când compilăm cu optimizări
- dacă nu dezactivăm aserțiunile, programul crapă brusc la momentul execuției, fără vreo posibilitate de a
  remedia situația

Prin date de intrare înțelegem orice parametri ai unei funcții. Dacă vrem să ne asigurăm că primim date valide,
trebuie să facem verificări explicite cu if-uri și să întrerupem execuția normală a codului dacă avem date
invalide: fie întoarcem un cod de eroare, fie folosim excepții.

#### Motivație

Sub o formă sau alta, (aproape) toate formele de tratare a erorilor care nu folosesc excepții se rezumă la coduri
de eroare sau tipuri de date rezultat. Dacă nu avem posibilitatea să folosim excepții, este de preferat să alegem
tipuri de date rezultat (nu coduri de eroare) pentru că ne oferă flexibilitate și un cod mult mai ușor de întreținut.

Codurile de eroare ne ajută cel mai mult doar în situații simple. **Exemplu:** input interactiv.

Indiferent de ce am alege, ambele tehnici prezintă dezavantajul dificultății propagării erorilor prin multe
apeluri de funcții. Exemplul următor folosește coduri de eroare, însă avem dificultăți asemănătoare cu tipurile
de date rezultat dacă nu folosim biblioteci specializate.

```c++
#include <iostream>
#include <vector>

int calcul_medie(std::vector<int> note, int& medie) {
    if(note.size() < 3)
        return 1;
    // ...
    return 0;
}

int f1(/*...*/) {
    // ...
    int err = calcul_medie(/*...*/);
    if(err != 0)
        return err;
    // ...
    return 0;
}

int f2(/*...*/) {
    // ...
    int err = f1(/*...*/);
    if(err != 0)
        return err;
    // ...
    return 0;
}

// f3, f4, ..., f7, f8

int f9(/*...*/) {
    // ...
    int err = f8(/*...*/);
    if(err != 0)
        return err;
    // ...
    return 0;
}

void f10(/*...*/) {
    // ...
    int err = f9(/*...*/);
    if(err != 0) {
        std::cout << "eroare calcul: " << err < "; se încearcă repararea erorii\n";
        // repară
        return;
    }
    // ...
}
```

Funcția `f10` apelează funcția `f9`, `f9` apelează funcția `f8`, ..., `f2` apelează funcția `f1`, iar `f1`
apelează funcția `calcul_medie`. Funcția `calcul_medie` întoarce un cod de eroare pe care avem nevoie să
îl transmitem înapoi la funcția `f10`. Presupunem că nu avem posibilitatea să remediem situația sau să salvăm
ceva în funcțiile `f1`, ..., `f9` și că trebuie să transmitem codul de eroare înapoi la `f10`.

Acest scenariu este frecvent întâlnit în aplicații mai mari: eroarea apare într-o funcție internă dintr-o
componentă sau bibliotecă externă, dar eroarea poate fi tratată doar într-o altă componentă sau altă parte
de cod la multe apeluri de funcție distanță de locul unde a apărut eroarea. De aceea, avem nevoie să propagăm
erorile de-a lungul mai multor apeluri de funcții.

Vom rescrie codul de mai sus folosind excepții. Important nu este să înțelegeți ce face codul (momentan), ci să
remarcați cât se simplifică logica programului, mai ales dacă scriam explicit toate funcțiile de la `f1` la `f10`.
```c++
#include <iostream>
#include <vector>

void calcul_medie(std::vector<int> note, int& medie) {
    if(note.size() < 3)
        throw eroare_calcul("prea puține note");
    // ...
}

void f1(/*...*/) {
    // ...
    calcul_medie(/*...*/);
    // ...
}

void f2(/*...*/) {
    // ...
    f1(/*...*/);
    // ...
}

// f3, f4, ..., f7, f8

void f9(/*...*/) {
    // ...
    f8(/*...*/);
    // ...
}

void f10(/*...*/) {
    // ...
    try {
        f9(/*...*/);
        // ...
    } catch(eroare_calcul& err) {
        std::cout << "eroare calcul: " << err.what() << "; se încearcă repararea erorii\n";
        // repară
        return;
    }
}
```

Diferența esențială la exemplul cu excepții față de exemplul cu coduri de eroare este că funcțiile `f1`-`f9`
nu conțin instrucțiuni pentru a propaga erorile, iar codul este mai ușor de urmărit.

De asemenea, dacă avem nevoie să adăugăm funcții intermediare, la varianta cu excepții, funcțiile intermediare
nu au nevoie de cod suplimentar: erorile se propagă automat. Pe de altă parte, numărul de coduri de eroare
crește și este din ce în ce mai dificil să determinăm ce erori trebuie propagate mai departe. 

#### Sintaxă partea 1: introducere

Pentru a arunca o excepție, folosim `throw`. Codul de după `throw` nu se mai execută:
```c++
#include <iostream>
#include <exception>

int main() {
    std::cout << "înainte de throw\n";
    throw std::exception{};
    std::cout << "după throw\n";
}
```

Dacă aruncăm o excepție și nu o prindem, programul crapă instant:
```
$ ./main
înainte de throw
terminate called after throwing an instance of 'std::exception'
  what():  std::exception
Aborted (core dumped)  ./main
```

Destructorii nu se mai apelează:
```c++
#include <iostream>
#include <exception>

class Test {
public:
    Test() { std::cout << "constr test\n"; }
    ~Test() { std::cout << "destr test\n"; }
};

int main() {
    Test t;
    std::cout << "înainte de throw\n";
    throw std::exception{};
    std::cout << "după throw\n";
}
```

Se va afișa:
```
$ ./main
constr test
înainte de throw
terminate called after throwing an instance of 'std::exception'
  what():  std::exception
Aborted (core dumped)
```

Pentru a prinde o excepție, folosim un bloc `try`/`catch`:
```c++
#include <iostream>
#include <exception>

class Test {
public:
    Test(int nr) { std::cout << "constr test" << nr << "\n"; }
    ~Test() { std::cout << "destr test\n"; }
};

int main() {
    Test t1{1};
    std::cout << "înainte de try\n";
    try {
        Test t2{2};
        std::cout << "înainte de throw\n";
        throw std::exception{};
        Test t3{3};
        std::cout << "după throw\n";
    } catch(std::exception& err) {
        Test t4{4};
        std::cout << ">>> " << err.what() << " <<<\n";
    }
    Test t5{5};
    std::cout << "după try\n";
}
```

**Exercițiu:** în ce ordine se apelează destructorii în codul de mai sus?

#### Excepții predefinite

C++ definește clasa de bază pentru excepții [`std::exception`](https://en.cppreference.com/w/cpp/error/exception)
din `<exception>`. Principalele clase derivate
sunt [`std::runtime_error`](https://en.cppreference.com/w/cpp/error/runtime_error) și
[`std::logic_error`](https://en.cppreference.com/w/cpp/error/logic_error) din `<stdexcept>`. Din aceste 3 clase
sunt derivate excepții mai specifice. Nu ar trebui să le rețineți pe dinafară, citiți în documentație pentru a
afla ce clasă de bază are o anumită excepție specifică și ce excepții aruncă o anumită funcție.

De exemplu, funcția [`std::stoi`](https://en.cppreference.com/w/cpp/string/basic_string/stol) poate arunca
`std::invalid_argument` sau `std::out_of_range` (ambele derivate din `std::logic_error`):
```c++
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

int main() {
    int x = 0;
    std::string text;
    //std::istringstream st{"1doi 3"};
    // std::istringstream st{"1111111111111 doi 3"}; // std::out_of_range
    std::istringstream st{"1 doi 3"};
    try {
        std::cout << "înainte de stoi\n";
        st >> text;
        x = std::stoi(text);
        std::cout << "x:" << x << "\n";
        st >> text;
        x = std::stoi(text);
        std::cout << "x:" << x << "\n";
    } catch(std::invalid_argument& err) {
        std::cout << "err: " << err.what() << "\n";
    }
}
```

Chiar dacă nu scriem noi un `throw` explicit, trebuie să prindem excepțiile care ar putea fi aruncate
de o funcție. Altfel, programul crapă. Citiți în documentație ce excepții pot fi aruncate pentru a ști
ce trebuie să prindeți.

#### Sintaxă partea 2: moșteniri

Putem avea mai multe clauze `catch`:
```c++
#include <iostream>
#include <string>

int main() {
    std::string input;
    std::cout << "x = ";
    std::cin >> input;
    try {
        int x = std::stoi(input);
        if(x % 11 == 0)
            std::cout << "a\n";
        else if(x % 7 == 0)
            std::cout << "b\n";
        else
            std::cout << "c\n";
    } catch(std::invalid_argument& err) {
        std::cout << "nu este număr: " << err.what() << "\n";
    } catch(std::out_of_range& err) {
        std::cout << "număr prea mare/prea mic: " << err.what() << "\n";
    }
}
```

Execuția codului sare de la `throw` la **primul bloc `catch` care se potrivește**.
Așadar, nu are rost să avem două catch-uri cu tip de date identic asociate unui același bloc `try`.

Dacă avem blocuri try/catch imbricate, poate fi în regulă să repetăm din catch-uri pentru că se pot
arunca excepții în mai multe locuri. Cu toate acestea, trebuie să avem în vedere că vrem să folosim
excepții doar atunci când ne-am simplifica modul de tratare a erorilor, deci nu ar trebui să ne
umplem codul în mod excesiv de blocuri try/catch.

Să ne reamintim că un obiect de tip de date derivat _este un fel de_ obiect de tip de date de bază.
Putem prinde excepții derivate cu referințe la o clasă excepție de bază:
```c++
#include <iostream>
#include <string>

int main() {
    std::string input;
    std::cout << "x = ";
    std::cin >> input;
    try {
        int x = std::stoi(input);
        if(x % 11 == 0)
            std::cout << "a\n";
        else if(x % 7 == 0)
            std::cout << "b\n";
        else
            std::cout << "c\n";
    } catch(std::logic_error& err) {
        std::cout << "eroare conversie număr: [" << input << "] " << err.what() << "\n";
    }
}
```

Acum prindem cu un singur `catch` fie `std::invalid_argument`, fie `std::out_of_range`, deoarece
`std::logic_error` este clasa lor de bază. Dacă ne interesează să tratăm o eroare mai specifică vom
prinde eroarea specifică. Dacă vrem să tratăm în mod unitar mai multe categorii de erori, vom prinde
o eroare generală printr-o clasă de bază comună.

Am fi putut folosi în exemplul anterior și `std::exception` în loc de `std::logic_error`, dar trebuie
să ținem cont că așa vom prinde și ce nu ne-am aștepta. Dacă folosim în catch o excepție prea generală,
pierdem din detaliile erorilor și nu mai putem repara prea multe din două motive:
- pierdem mare parte din contextul inițial al erorii
- eroarea poate preveni din prea multe locuri

Desigur, sunt situații când vrem să prindem tot, dar aceste situații nu sunt întâlnite foarte des. Un
exemplu este un server care procesează cereri de la clienți: o cerere poate cauza tot felul de erori
și un catch general este util în astfel de situații.

La polul opus, poate fi de preferat să lăsăm programul să crape decât să prindem excepția. Ne ajută
mai mult să vedem ce și unde a crăpat decât să prindem erori despre care nu avem habar, iar procesarea
unor date să continue, deși nu ar trebui, întrucât niște prelucrări anterioare nu au reușit. Vom vedea
o combinație a acestor abordări într-o [secțiune următoare](#sintaxă-partea-3-rearuncarea-excepțiilor).

Dacă avem două blocuri `catch`, ordinea acestor blocuri contează atunci când vrem să prindem și excepții
specifice, și generale:
```c++
#include <iostream>
#include <string>

int main() {
    std::string input{"oops"};
    try {
        int x = std::stoi(input);
        if(x % 11 == 0)
            std::cout << "a\n";
        else if(x % 7 == 0)
            std::cout << "b\n";
        else
            std::cout << "c\n";
    } catch(std::logic_error& err) {
        std::cout << "catch std::logic_error: " << err.what() << "\n";
    } catch(std::invalid_argument& err) {
        std::cout << "catch std::invalid_argument: " << err.what() << "\n";
    }
}
```

Chiar dacă excepția `std::invalid_argument` este mai specifică decât `std::logic_error`, primul
`catch` care se potrivește este cel cu `std::logic_error`!

Funcția `std::stoi` aruncă `std::invalid_argument`, dar se va afișa:
```
catch std::logic_error: stoi
```

Primim și warning. Repet, warning-urile nu sunt degeaba, nu le ignorați!
```
main.cpp: In function ‘int main()’:
main.cpp:16:7: warning: exception of type ‘std::invalid_argument’ will be caught by earlier handler [-Wexceptions]
   16 |     } catch(std::invalid_argument& err) {
      |       ^~~~~
main.cpp:14:7: note: for type ‘std::logic_error’
   14 |     } catch(std::logic_error& err) {
      |       ^~~~~
```

Corect este să **punem întotdeauna blocurile `catch` specifice înaintea celor generale!**
```c++
#include <iostream>
#include <string>

int main() {
    std::string input{"oops"};
    try {
        int x = std::stoi(input);
        if (x % 11 == 0)
            std::cout << "a\n";
        else if (x % 7 == 0)
            std::cout << "b\n";
        else
            std::cout << "c\n";
    } catch(std::invalid_argument& err) {
        std::cout << "catch std::invalid_argument: " << err.what() << "\n";
    } catch(std::logic_error& err) {
        std::cout << "catch std::logic_error: " << err.what() << "\n";
    }
}
```

Excepțiile se propagă prin oricâte blocuri sau apeluri de funcții este necesar. Execuția codului sare de la `throw`
la primul `catch` care se potrivește: ori un tip de date exact, ori un tip de date de bază al excepției aruncate.

Exemplul următor este doar ca să înțelegem sintaxa (nu are sens să aruncăm argument invalid când nu avem argumente):
```c++
#include <iostream>
#include <stdexcept>

void f1() {
    std::cout << "f1: înainte de throw\n";
    {
        throw std::invalid_argument{"argumentul invalid este..."};
    } // linia 8
    std::cout << "f1: după throw\n";
} // linia 10

void f2() {
    std::cout << "f2: înainte de throw\n";
    throw std::out_of_range{"trebuie între... și..."};
    std::cout << "f2: după throw\n";
} // linia 16

void f3() {
    std::cout << "f3: înainte de try\n";
    try {
        std::cout << "f3: înainte de f1\n";
        f1(); // linia 22
        std::cout << "f3: înainte de f2\n";
        f2();
        std::cout << "f3: după f2\n";
    } catch(std::out_of_range& err) { // linia 26
        std::cout << "f3: catch std::out_of_range " << err.what() << "\n";
    }
    std::cout << "f3: final\n";
} // linia 30

void f4() {
    std::cout << "f4: înainte de try\n";
    try {
        std::cout << "f4: înainte de f3\n";
        f3(); // linia 36
        std::cout << "f4: după f3\n";
    } catch(std::runtime_error& err) { // linia 38
        std::cout << "f4: catch std::runtime_error " << err.what() << "\n";
    }
} // linia 41

int main() {
    std::cout << "main: înainte de try\n";
    try {
        std::cout << "main: înainte de f4\n";
        f4(); // linia 47
        std::cout << "după f4\n";
    } catch(std::logic_error& err) { // linia 49
        std::cout << "main: catch std::logic_error " << err.what() << "\n";
    }
}
```

Până la instrucțiunea `throw` din funcția `f1`, totul decurge normal, după cum ne-am aștepta. De la acest `throw`
se sare direct la acolada de la linia 8 și se apelează toți destructorii din acest bloc (dacă există). Blocul
acesta nu este un bloc `try`/`catch`, deci se sare la următorul bloc. Următorul bloc este la linia 10 și este
scopul funcției `f1`. Se apelează acum și toți destructorii variabilelor locale din funcția `f1`.

Mai departe, funcția `f1` a fost apelată din blocul `try`/`catch` al funcției `f3`, la linia 22. Excepția nu a
fost încă prinsă, așa că execuția sare la următoarea acoladă închisă, adică la linia 26, moment în care se
apelează destructorii variabilelor locale din acest bloc de `try`. Din restricții de sintaxă, blocul `try`
are obligatoriu și minim un bloc `catch`, însă nu avem clauze `catch` care să știe să prindă excepția
aruncată (`std::invalid_argument`). Excepția nu a putut fi tratată, deci execuția codului sare din nou la
următoarea acoladă închisă, adică la linia 30. Se apelează iar destructorii.

În continuare, am revenit din apelul funcției `f3` de la linia 36. Se sare iarăși la următoarea acoladă
închisă, adică la linia 38 (și se apelează destructorii). Nici aici nu se potrivește `catch`-ul. Se sare la
linia 41, destructorii din funcția `f4`...

Și am ajuns la linia 47 de unde a fost apelată funcția `f4`. Se sare la linia 49, se apelează destructorii
din blocul `try`/`catch` din funcția `main` și apoi găsim în sfârșit un bloc `catch` care să știe să trateze
excepția aruncată.

Se va afișa:
```
main: înainte de try
main: înainte de f4
f4: înainte de try
f4: înainte de f3
f3: înainte de try
f3: înainte de f1
f1: înainte de throw
main: catch std::logic_error argumentul invalid este...
```

**Exercițiu:** adăugați clasa `Test` de mai devreme și creați niște obiecte pentru a vedea când se apelează
destructorii. Adăugați orice alte afișări suplimentare de care credeți că aveți nevoie pentru a înțelege
mai bine ce se întâmplă.

Tot acest proces de distrugere a obiectelor și de revenire din apeluri se numește stack unwinding.
Detalii [aici](https://en.cppreference.com/w/cpp/language/throw#Stack_unwinding).

Încă un exemplu:
```c++
#include <iostream>
#include <stdexcept>

void f1() {
    std::cout << "f1: înainte de throw\n";
    throw std::invalid_argument{"argumentul invalid este..."};
    std::cout << "f1: după throw\n";
}

void f2() {
    std::cout << "f2: înainte de throw\n";
    throw std::out_of_range{"trebuie între... și..."};
    std::cout << "f2: după throw\n";
}

void f3() {
    std::cout << "f3: înainte de try\n";
    try {
        std::cout << "f3: înainte de f1\n";
        f1();
        std::cout << "f3: înainte de f2\n";
        f2();
        std::cout << "f3: după f2\n";
    } catch(std::runtime_error& err) {
        std::cout << "f3: catch std::runtime_error " << err.what() << "\n";
    }
    std::cout << "f3: final\n";
}

void f4() {
    std::cout << "f4: înainte de try\n";
    try {
        std::cout << "f4: înainte de f3\n";
        f3();
        std::cout << "f4: după f3\n";
    } catch(std::logic_error& err) {
        std::cout << "f4: catch std::logic_error " << err.what() << "\n";
    }
}

int main() {
    std::cout << "main: înainte de try\n";
    try {
        std::cout << "main: înainte de f4\n";
        f4();
        std::cout << "după f4\n";
    } catch(std::invalid_argument& err) {
        std::cout << "main: catch std::invalid_argument " << err.what() << "\n";
    }
}
```

**Exercițiu:** ce se afișează?

#### Ierarhie proprie

Până acum am folosit doar tipuri de excepții predefinite de biblioteca standard (stdlib), excepția cea mai de
bază fiind `std::exception` (din `<exception>`). Vom întâlni clase asemănătoare și în alte limbaje. Totuși,
în alte limbaje, sintaxa de `throw`/`catch` nu ne permite să aruncăm/prindem decât excepții derivate direct
sau indirect din clasa de bază de excepții a limbajului respectiv.

Chiar dacă C++ ne permite să aruncăm orice tip de date, această flexibilitate este utilă doar ca să avem voie
să ne definim ierarhii proprii de excepții care să nu fie derivate din `std::exception`. Ne interesează să
ne creăm ierarhii proprii de excepții de la zero doar dacă folosim biblioteci specializate și în cazuri rare.
Nu avem nevoie de așa ceva la acest curs.

Prin urmare, nu ne definim o ierarhie de excepții complet de la zero. Vom vedea în curând de ce.

Să presupunem că nu ne definim deloc excepții proprii și continuăm să folosim clasele de excepții din
biblioteca standard. Pentru programe mici nu contează, însă este o problemă atunci când integrăm în
program biblioteci externe sau când ne definim noi o bibliotecă și aruncăm excepții din stdlib:
```c++
#include <iostream>
#include <string>
#include <stdexcept>

#include <orar.hpp> // bibliotecă externă fictivă

void învață(std::string nume_curs) {
    if(nume_curs == "oop")
        throw std::runtime_error("vreau pauză");
    std::cout << "am chef de " << nume_curs << "!\n";
}

int main() {
    try {
        învață("sport");
        învață("engleză");
        orar::caută_sala(217);
        învață("robotică");
        orar::caută_sala(100);    // aruncă std::runtime_error("sala nu există")
        orar::rezervă_sala(303);
        învață("oop");
    } catch(std::runtime_error& err) {
        std::cout << err.what() << "\n";
        // eroare din funcția învață? din caută_sala? din rezervă_sala?
    }
}
```

Dacă funcțiile din biblioteca `orar` aruncă tot `std::runtime_error` sau o excepție din stdlib pe care
o aruncăm și noi, este imposibil să avem blocuri `catch` separate pentru a face distincția între erori
aruncate de biblioteca externă și erori aruncate de noi. Mai mult, chiar dacă în prezent aruncăm
excepții diferite față de acea bibliotecă, nu avem garanția că o versiune ulterioară a bibliotecii nu
ar arunca excepții pe care le aruncăm și noi. Reciproc, suntem restricționați să nu aruncăm excepțiile
aruncate de bibliotecile externe.

La extrema cealaltă, dacă fiecare bibliotecă externă și fiecare componentă a programului nostru și-ar
defini o ierarhie proprie de la zero, ne-ar trebui extrem de multe blocuri `catch` și nu am simplifica
prea mult tratarea erorilor. Atunci când am adăuga o nouă bibliotecă, ar trebui să completăm programul
în multe locuri cu alte clauze `catch`.

Din aceste considerente, nu vrem să aruncăm excepții predefinite de biblioteca standard a limbajului.
Acest lucru este valabil și în alte limbaje. Alte detalii
[aici](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Re-exception-types). Specific C++,
nu vrem nici să ne definim (de cele mai multe ori) o ierarhie de la zero, deoarece am forța
utilizatorii claselor definite de noi să prindă neapărat aceste excepții particulare.

Pentru a combina beneficiile celor două abordări, rețeta la care ajungem este următoarea: ne creăm o
ierarhie proprie, iar clasa cea mai de bază a acestei ierarhii trebuie să fie derivată direct sau
indirect din `std::exception`. Vom deriva din `std::runtime_error`, deoarece are constructor cu mesaj.

##### Exemplu ierarhie proprie
```c++
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <orar.hpp> // aceeași bibliotecă externă fictivă de mai devreme

class eroare_aplicație : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class eroare_student : public eroare_aplicație {
public:
    explicit eroare_student(std::string mesaj) :
        eroare_aplicație("eroare student: " + mesaj) {}
};

class medie_invalidă : public eroare_aplicație {
public:
    explicit medie_invalidă(double medie) :
        eroare_aplicație("media trebuie să fie >= 5, dar este " + std::to_string(medie)) {}
};

void învață(std::string nume_curs) {
    if(nume_curs == "oop")
        throw eroare_student("vreau pauză");
    std::cout << "am chef de " << nume_curs << "!\n";
}

void calcul_medie(std::vector<int> note, int& medie) {
    double medie_tmp = 0;
    for(auto nota : note)
        medie_tmp += nota;
    medie_tmp /= note.size();
    if(medie_tmp < 5)
        throw medie_invalidă(medie_tmp);
    medie = medie_tmp;
}

int main() {
    try {
        învață("sport");
        învață("engleză");
        orar::caută_sala(217);
        învață("robotică");
        orar::caută_sala(100);    // aruncă orar::sală_invalidă
        orar::rezervă_sala(303);  // poate arunca orar::eroare_rezervare
        int medie;
        calcul_medie({2, 3, 4}, medie);
        învață("oop");
    } catch(eroare_student& err) {
        std::cout << "eroare student: " << err.what() << "\n";
    } catch(eroare_aplicatie& err) {
        std::cout << "eroare de la noi: " << err.what() << "\n";
    } catch(orar::eroare_rezervare& err) {
        std::cout << "eroare rezervare din orar: " << err.what() << "\n";
    } catch(orar::eroare_orar& err) {
        std::cout << "eroare din orar: " << err.what() << "\n";
    } catch(std::exception& err) {
        std::cout << "altceva: " << err.what() << "\n";
    }
}
```

**Atenție:** `std::exception` nu are constructor cu mesaj în biblioteca standard. Un astfel de
constructor este oferit de MSVC ca extensie de compilator, dar nu este portabil, deci nu îl vom folosi.

La început de tot vrem să prindem erorile cele mai specifice care ne interesează. Dacă vrem să prindem erorile
unor componente sau ale unor biblioteci externe, fără să ne preocupe alte detalii, prindem clasa de bază a
erorilor pentru acea componentă/bibliotecă. Dacă nu ne interesează detalii deloc, ci doar vrem să știm că
nu crapă, prindem `std::exception`.

Presupunând că și alte biblioteci respectă această convenție, nu trebuie să modificăm nimic atunci când
integrăm o nouă bibliotecă dacă doar vrem să prindem erori, deoarece se vor duce pe catch-ul cu
`std::exception`. Dacă vrem să prindem erori mai specifice, avem o ierarhie de erori proprie pentru fiecare
componentă/bibliotecă, iar aceste ierarhii nu intră în conflict una cu cealaltă.

Clasele de excepții pot avea mai mulți parametri în constructori, dar în exemplul de mai sus nu am avut
inspirație.

Nu este neapărat nevoie de toate acele blocuri `catch` în exemplul de mai sus, dar le-am inclus pentru a
ilustra mai sugestiv separarea codului care merge de codul care tratează erori:
- codul din blocul `try` arată secvența de instrucțiuni executată dacă totul merge fără probleme
- blocurile `catch` se ocupă doar de tratarea erorilor

Codul este mult mai ușor de urmărit decât dacă am fi tratat erorile cu coduri de eroare, deoarece, atunci
când folosim excepții, nu amestecăm codul obișnuit cu tratarea erorilor.

Mai multe discuții [aici](https://isocpp.org/wiki/faq/exceptions#exceptions-separate-good-and-bad-path)
și [aici](https://docs.microsoft.com/en-us/cpp/cpp/errors-and-exception-handling-modern-cpp).

#### Sintaxă partea 3: rearuncarea excepțiilor

Există situații când nu avem posibilitatea să remediem complet o eroare, însă vrem să prindem excepția
ca să reparăm ce se poate repara sau doar ca să scriem un mesaj de eroare (în logs, de exemplu) pentru
o depanare mai ușoară. Instrucțiunea `throw;` rearuncă excepția curentă:
```c++
#include <iostream>
#include <stdexcept>

void f1() {
    std::cout << "f1 înainte de throw\n";
    throw std::runtime_error{"hopa..."};
    std::cout << "f1 după throw\n";
}

void f2() {
    try {
        std::cout << "f2 înainte de apel f1\n";
        f1();
        std::cout << "f2 după apel f1\n";
    } catch(std::runtime_error& err) {
        std::cout << "f2 în catch 1: " << err.what() << "\n";
        throw;
        std::cout << "f2 în catch 1 după throw\n";
    } catch(std::exception& err) {
        std::cout << "f2 în catch 2: " << err.what() << "\n";
    }
}

int main() {
    try {
        std::cout << "main înainte de apel f2\n";
        f2();
        std::cout << "main după apel f2\n";
    } catch(std::exception& err) {
        std::cout << "main în catch: " << err.what() << "\n";
    }
}
```

**Atenție!** Atunci când rearuncăm o excepție, se sare la următorul bloc `try`/`catch`! Nu se sare la un
alt catch corespunzător aceluiași bloc `try`/`catch`!

Pentru a demonstra că avem nevoie de sintaxa specială `throw;` și că nu este echivalentă cu a scrie
`throw err;`, ne vom defini excepții proprii și vom suprascrie toate funcțiile speciale.
Sintaxa `throw err;` creează întotdeauna un nou obiect:
```c++
#include <iostream>
#include <stdexcept>
#include <utility>

class eroare_aplicație : public std::runtime_error {
public:
    eroare_aplicație(const std::string& mesaj) : std::runtime_error(mesaj) {
        std::cout << "constr init eroare_aplicație: " << mesaj << "\n";
    }
    eroare_aplicație(const eroare_aplicație& other) : std::runtime_error(other) {
        std::cout << "cc eroare_aplicație\n";
    }
    eroare_aplicație(eroare_aplicație&& other) : std::runtime_error(other) {
        std::cout << "cm eroare_aplicație\n";
    }
    eroare_aplicație& operator=(const eroare_aplicație& other) {
        std::runtime_error::operator=(other);
        std::cout << "op= copiere eroare_aplicație\n";
        return *this;
    }
    eroare_aplicație& operator=(eroare_aplicație&& other) {
        std::runtime_error::operator=(other);
        std::cout << "op= mutare eroare_aplicație\n";
        return *this;
    }
    ~eroare_aplicație() {
        std::cout << "destr eroare_aplicație\n";
    }
};

class eroare_calcul : public eroare_aplicație {
public:
    eroare_calcul(const std::string& mesaj) : eroare_aplicație(mesaj) {
        std::cout << "constr init eroare_calcul: " << mesaj << "\n";
    }
    eroare_calcul(const eroare_calcul& other) : eroare_aplicație(other) {
        std::cout << "cc eroare_calcul\n";
    }
    eroare_calcul(eroare_calcul&& other) : eroare_aplicație(other) {
        std::cout << "cm eroare_calcul\n";
    }
    eroare_calcul& operator=(const eroare_calcul& other) {
        std::runtime_error::operator=(other);
        std::cout << "op= copiere eroare_calcul\n";
        return *this;
    }
    eroare_calcul& operator=(eroare_calcul&& other) {
        std::runtime_error::operator=(other);
        std::cout << "op= mutare eroare_calcul\n";
        return *this;
    }
    ~eroare_calcul() {
        std::cout << "destr eroare_calcul\n";
    }
};

void f1() {
    std::cout << "f1 înainte de throw\n";
    throw eroare_calcul{"hopa..."};
    std::cout << "f1 după throw\n";
}

void f2() {
    try {
        std::cout << "f2 înainte de apel f1\n";
        f1();
        std::cout << "f2 după apel f1\n";
    } catch(eroare_aplicație& err) {
        std::cout << "f2 în catch: " << err.what() << "\n";
        throw err;                                  // linia 70
        // throw eroare_aplicație(err);             // linia 71
        // throw eroare_aplicație(std::move(err));  // linia 72
        // throw;                                   // linia 73
        std::cout << "f2 în catch după throw\n";
    }
}

int main() {
    try {
        std::cout << "main înainte de apel f2\n";
        f2();
        std::cout << "main după apel f2\n";
    } catch(std::exception& err) {
        std::cout << "main în catch: " << err.what() << "\n";
    }
}
```

Executați codul și salvați undeva ce se afișează. Comentați linia 70 și decomentați pe rând liniile
71-73 pentru a vedea ce constructori se apelează. Când se apelează destructorii excepțiilor și de ce?

Dacă rearuncăm un nou obiect de un tip de bază, facem object slicing (liniile 70-72). De aceea avem nevoie
de sintaxa `throw;`. Conform [documentației](https://en.cppreference.com/w/cpp/language/throw), compilatorul
are voie să elimine operația de copiere/mutare și dacă facem `throw err;` și nu este object slicing.
Momentan (2022), compilatoarele pe care am testat nu par să facă această optimizare întotdeauna.

Înlocuiți excepția prinsă din `f2` cu `eroare_calcul`. Ce observați?

Nu vrem niciodată să prindem o excepție prin valoare deoarece s-ar face automat object slicing. Dacă nu avem
nevoie să modificăm obiectul de excepție, este recomandat să prindem excepția prin referință **constantă**:
```c++
int main() {
    try {
        std::cout << "main înainte de apel f2\n";
        f2();
        std::cout << "main după apel f2\n";
    } catch(const std::exception& err) {  // <------------------ referință const!!!
        std::cout << "main în catch: " << err.what() << "\n";
    }
}
```

**În ce situații am vrea să rearuncăm o excepție?**

Există cel puțin patru situații când ne-ar interesa așa ceva:
- afișăm un mesaj de eroare (facem logging), apoi rearuncăm același obiect
- prindem o excepție dintr-o bibliotecă externă sau alt modul și aruncăm o excepție internă, "de-a noastră"
  - poate să ne ajute dacă erorile primite sunt prea criptice sau irelevante pentru noi; este util dacă
    modulul extern respectiv este izolat și nu prea îl folosim în alte locuri
  - mai bine aruncăm o excepție internă și tratăm în mod uniform excepțiile interne decât să prindem o
    excepție foarte specifică în cu totul altă parte din cod
    - cu alte cuvinte, în "try/catch-ul mare din main" nu ne ajută prea mult să prindem excepții foarte
      specifice pentru că am umple main-ul cu prea multe catch-uri de cazuri particulare
  - poate să ne încurce și să facă depanarea mai dificilă pentru că pierdem contextul erorii inițiale
- adunăm informații pentru depanare în obiectul prins, apoi rearuncăm același obiect
  - modificăm atribute ale obiectului în mod direct sau prin apelarea unor funcții (simple sau virtuale)
- prindem o excepție, creăm o nouă excepție cu atribut către vechea excepție, apoi aruncăm această nouă excepție
  - tehnica se numește [exception chaining](https://en.wikipedia.org/wiki/Exception_chaining)
  - C++11 oferă [std::nested_exception](https://en.cppreference.com/w/cpp/error/nested_exception)

Ultimele două tehnici au efectul unui bulgăre de zăpadă aruncat la vale care se tot mărește.

Recurgem la aceste tehnici doar dacă ne simplifică modul de lucru. Decât să ne umplem codul de
`try`/`catch`-uri, poate fi mai util să lăsăm diverse componente să crape cu totul și doar să analizăm
loguri.

Multe limbaje fac abuz de excepții, deși sunt destule situații care nu sunt excepționale, neașteptate sau
rare. Nu există un răspuns definitiv, trebuie să decidem care este cea mai bună variantă pentru fiecare
caz în parte.

Alte limbaje se folosesc mai mult de stacktrace pentru depanare. C++ nu are implementată funcționalitatea
la nivel de limbaj în mod portabil fără biblioteci externe
([exemplu](https://github.com/bombela/backward-cpp), nu am testat). Așteptăm să fie
[implementată](https://en.cppreference.com/w/cpp/utility/basic_stacktrace) în C++23.

#### Throw în constructor

Excepțiile sunt singurul mecanism din limbaj prin care putem opri construirea unui obiect. De ce am vrea
să facem asta? Fiindcă în acest fel garantăm că obiectul este într-o stare validă imediat după ce a fost
construit.

Dacă nu avem la dispoziție mecanismul de excepții, ar trebui să avem un atribut de tip `bool` pe care să
îl verificăm la începutul fiecărei funcții membru:
```c++
#include <iostream>
#include <string>

class curs {
    std::string nume;
    bool valid = true;
    // ...
public:
    curs(std::string nume_) : nume(nume_) {
        if(nume.empty())
            valid = false;
        // if(...)
        //    valid = false;
    }
    int calcul_medie(double& medie) {
        if(!valid)
            return 1;
        // medie = ...
        // if(eroare_calcul)
        //     return 2;
        return 0;
    }
    void prezintă(int nr) {
        if(!valid) {
            std::cout << "curs invalid\n";
            return;
        }
        // std::cout << ...
    }
    int caută(std::string text, std::string& rezultat) {
        if(!valid)
            return 1;
        // ...
        return 0;
    }
};
```

O variantă și mai neinspirată este să punem utilizatorii clasei să fie responsabili să apeleze o funcție
de validare înainte de fiecare funcție:
```c++
int main() {
    curs c1{""};
    if(c1.valid())
        c1.prezintă(2);
    if(c1.valid()) {
        double medie;
        int err;
        err = c1.calcul_medie(medie);
        if(!err)
            std::cout << medie;
    }
    if(c1.valid()) {
        std::string rez;
        int err = c1.caută("throw", rez);

    }
}
```

Ambele variante necesită un efort suplimentar pentru a garanta corectitudinea, iar dacă uităm să verificăm
că obiectul este valid înainte de un apel, programul va continua execuția normală și vom pierde mult timp
să identificăm cauza reală a erorilor. Ideea nu este că nu putem scrie codul în această manieră sau că nu
reușim să rezolvăm bug-urile. Dacă suntem motivați, ne descurcăm și reparăm până la urmă bug-urile. Problema
esențială este că **pierdem mai mult timp cu depanarea** decât dacă am alege varianta cu excepții.

Codul de mai sus rescris cu excepții este următorul:

##### Exemplu throw în constructor și funcție non-void
```c++
#include <iostream>
#include <stdexcept>
#include <string>

class eroare_aplicație : public std::runtime_error { using std::runtime_error::runtime_error; };
class eroare_curs : public eroare_aplicație { using eroare_aplicație::eroare_aplicație; };
class eroare_calcul : public eroare_aplicație { using eroare_aplicație::eroare_aplicație; };

class curs {
    std::string nume;
    // ...
public:
    curs(std::string nume_) : nume(nume_) {
        if(nume.empty())
            throw eroare_curs("nume gol");
        // if(...)
        //    throw eroare_curs...
    }
    double calcul_medie() {
        double medie = 0;
        // medie = ...
        // if(eroare)
        //     throw eroare_calcul{};
        return medie;
    }
    void prezintă(int nr) {
        // std::cout << ...
    }
    std::string caută(std::string text) {
        std::string rezultat;
        // rezultat = ...
        return rezultat;
    }
};

int main() {
    try {
        curs c1{""};
        c1.prezintă(2);
        std::cout << c1.calcul_medie();
        std::cout << c1.caută("cod de eroare");
    } catch(const eroare_aplicație& err) {
        std::cout << err.what() << "\n";
    }
}
```

Funcțiile din clasă nu mai au de verificat de fiecare dată dacă obiectul este valid înainte de a efectua
alte operațiuni, iar codul din main separă foarte clar partea de funcționalitate de partea care tratează
erorile.

Dacă obiectul nu se poate construi, **aruncăm excepție în constructor** și astfel nu avem cum să obținem
un obiect invalid, deoarece obiectul nu s-a construit deloc. Este aceeași idee ca la bazele de date cu
realizarea unei tranzacții: operația de construire fie reușește complet, fie nu reușește deloc.

Mergând cu ideea mai departe, este imposibil să construim parțial un obiect dacă un atribut este invalid:
dacă se aruncă excepție într-un atribut, obiectul mare nu se va mai construi.
```c++
#include <iostream>
#include <stdexcept>

class A {
    int nr;
public:
    A(int nr_) : nr(nr_) {
        std::cout << "constr A " << nr << " înainte de throw\n";
        if(nr % 2)
            throw std::invalid_argument("A: nr trebuie să fie par");
        std::cout << "constr A după throw\n";
    }
    ~A() {
        std::cout << "destr A " << nr << "\n";
    }
};

class B {
    A a1;
    A a2;
public:
    B(int nr1, int nr2) : a1(nr1), a2(nr2) {
        std::cout << "constr B\n";
    }
    void f() {
        std::cout << "B f\n";
    }
    ~B() {
        std::cout << "destr B\n";
    }
};

int main() {
    try {
        B b{4, 3};
        b.f();
    } catch(std::logic_error& err) {
        std::cout << err.what() << "\n";
    }
}
```

Pentru un obiect care nu este construit nu se apelează destructorul: nu ar avea ce să distrugă!
Dacă un obiect a fost deja construit ca membru al unui obiect mai mare, iar obiectul mai mare nu s-a
construit complet, toate sub-obiectele obiectului mare construite complet până în acel punct se vor
distruge automat. Resursele alocate în constructori în afara unor obiecte **nu se eliberează automat!**

Această tehnică este utilă și atunci când suntem într-o funcție care trebuie să întoarcă un obiect,
dar nu putem actualiza codul din clasa obiectului sau nu putem întoarce un cod de eroare/o valoare
invalidă. Dacă aruncăm excepții într-o funcție care întoarce un rezultat prin tipul de retur, execuția
codului nu mai ajunge la vreo instrucțiune `return`, ci sare de la `throw` la primul bloc `catch` care
se potrivește.

**ATENȚIE! Nu facem catch în constructor!** Dacă facem catch în constructor, degeaba mai aruncăm excepții:
obiectul va fi construit și va fi într-o stare invalidă.

#### Contraexemple

[//]: # (Majoritatea exemplelor din curs.)

Până acum am văzut când este bine să utilizăm excepțiile ca mecanism de tratare a erorilor. Cu toate acestea,
există multe moduri de a ne complica logica programului în mod excesiv dacă recurgem la excepții atunci când
alternativele (codurile de eroare și tipurile de date rezultat) ne-ar ajuta mai mult.

Excepțiile se justifică de obicei pentru a propaga erori prin mai multe apeluri de funcții și
pentru a preveni construirea de obiecte invalide.

Datele de intrare primite în mod interactiv nu trebuie validate cu excepții: avem posibilitatea să cerem din
nou introducerea datelor în același loc din cod, deci nu ar trebui propagată vreo eroare. Să scriem întâi o
variantă cu excepții:
```c++
#include <iostream>
#include <stdexcept>

int main() {
    do {
        int x = 0;
        std::cout << "x: ";
        std::cin >> x;
        try {
            if(x < 100)
                throw std::invalid_argument{"trebuie >= 100"};
            break;
        } catch(const std::invalid_argument& err) {
            std::cout << err.what() << "\n";
        }
    } while(true);
}
```

Iar acum varianta fără excepții:
```c++
#include <iostream>

int main() {
    do {
        int x = 0;
        std::cout << "x: ";
        std::cin >> x;
        if(x >= 100)
            break;
        std::cout << "trebuie >= 100\n";
    } while(true);
}
```

În general, de cele mai multe ori nu are sens să facem `throw` tot acolo unde facem și `catch`, deoarece
este echivalent cu un `if`/`else`, doar că scriem mai mult cod. Este valabil mai ales când blocul de try
nu este prea mare:
```c++
int main() {
    // cu excepții
    try {
        if(conditie)
            throw err;
        // codul de după if
    } catch(const err&) {
        // codul din catch
    }

    // cu if/else
    if(conditie) {
        // codul din catch
    }
    else {
        // codul de după if
    }
}
```

Este important să înțelegem că vrem să alegem mecanismul de tratare a erorilor care să fie cel mai simplu
pentru contextul respectiv.

**NU FOLOSIȚI INSTRUCȚIUNI `goto` LA ACEST CURS!** Totuși, trebuie să menționez că utilizarea `goto` este un
mecanism des folosit pentru tratarea erorilor pentru a simula excepții, întrucât sunt cazuri când excepțiile
sunt dezactivate (sisteme critice, de exemplu aviație).

Alt exemplu când excepțiile sunt folosite în mod eronat:
```c++
int main() {
    try {
        if(conditie1)
            throw err1;
        // ...
    } catch(const err1&) {
        // ...
    }
    try {
        if(conditie2)
            throw err2;
        // ...
    } catch(const err2&) {
        // ...
    }
    try {
        if(conditie3)
            throw err1;
        // ...
    } catch(const err1&) {
        // ...
    }
}
```

Avem cel puțin 3 alternative:
- alegem varianta de mai jos
- regândim ierarhia de excepții
- trecem înapoi la coduri de eroare

Alte discuții [aici](https://isocpp.org/wiki/faq/exceptions#too-many-trycatch-blocks).
```c++
int main() {
    try {
        if(conditie1)
            throw err1;
        // ...
        if(conditie2)
            throw err2;
        // ...
        if(conditie3)
            throw err1;
        // ...
    }
    } catch(const err1&) {
        // ...
    }
    } catch(const err2&) {
        // ...
    }
}
```

Dacă tot suntem la subiectul "prea multe try/catch-uri", un alt mod de a complica inutil lucrurile este acesta:
```c++
#include <stdexcept>

void f1(int x) {
    if(x % 2)
        throw std::invalid_argument{"nu este par"};
}

void f2(int y, int z) {
    try {
        // ...
        f1(y + z);
        // ...
    } catch(std::invalid_argument& err) {
        throw;
    }
}
```

Dacă _doar_ rearuncăm excepția în catch, _fără să facem altceva_, nu diferă cu nimic de a nu prinde excepția
deloc. Dacă nu avem ce să facem ca să remediem situația sau dacă nu ne ajută să afișăm un mesaj de eroare
intermediar, mai bine nu avem deloc `try`/`catch` pentru că _excepțiile se propagă automat_.

C++ este printre puținele limbaje care ne dă voie să aruncăm tipuri de date primitive și obiecte care
nu sunt derivate din excepțiile predefinite de limbaj (mai corect spus definite de stdlib). Asta înseamnă că
avem voie să facem asta:
```c++
int main() {
    try {
        throw 1;
    } catch(int err) {
        std::cout << err << "\n";
    }
}
```

De ce este o idee extrem de... neinspirată să facem asta? Pentru că nu avem posibilitatea să facem distincția
între tipuri diferite de erori, așa că ajungem la următoarea absurditate:
```c++
int main() {
    try {
        if(conditie1)
            throw 1;
        if(conditie2)
            throw 2;
    } catch(int err) {
        if(err == 1) {
            std::cout << "eroarea 1\n";
        }
        else if(err == 2) {
            std::cout << "eroarea 2\n";
        }
    }
}
```

Astfel, am reușit să folosim excepții sub formă de coduri de eroare, combinând dezavantajele ambelor abordări.
Felicitări!

Mai departe, dacă trebuie să interacționăm cu biblioteci/module scrise de cineva care s-a inspirat din
exemplul anterior, însă nu a documentat ce tipuri de date sunt aruncate (sau avem ceva critic și trebuie
să prindem orice), există o sintaxă specială de catch care știe să prindă acest "orice":
```c++
#include <iostream>
// #include <exception>

int main() {
    // std::exception_ptr eptr;
    try {
        throw 1;
    } catch(double err) {
        std::cout << "catch double\n";
    } catch(...) {
        std::cout << "eroare necunoscută...\n";
        // eptr = std::current_exception();
    }
    // depanare ulterioară a lui eptr
    // if(eptr)
    //     ...
}
```

Nu este nevoie de `std::exception_ptr` și `std::current_exception` dacă nu vrem să facem mai departe nimic
cu excepția sau dacă tratăm eroarea direct în blocul `catch(...)`.

`catch(...)` este recomandat atunci când încercăm să garantăm că nu aruncăm mai departe alte excepții, de
exemplu în destructori.

##### Exemplu handler erori comune

Următorul exemplu **nu este un contraexemplu!** Sintaxa cu `catch(...)` ne mai poate ajuta să eliminăm
duplicarea de cod dacă avem de tratat în mai multe locuri un grup de aceleași erori în același mod:
```c++
void handle_errors() {
    try {
        throw;
    } catch(eroare_calcul& err) {
        std::cout << "err calcul\n";
    } catch(curs_invalid& err) {
        std::cout << "err curs\n";
    } catch(orar::eroare_planificare& err) {
        std::cout << "err planificare orar\n";
    }
}

void f1() {
    try {
        // ...
    } catch(eroare_foarte_specifică1) {
        // ...
    } catch(...) {
        handle_errors();
    }
}
void f2() {
    try {
        // ...
    } catch(eroare_foarte_specifică2) {
        // ...
    } catch(...) {
        handle_errors();
    }
}
```

Am ales să vorbesc despre `catch(...)` în secțiunea de contraexemple, deoarece nu este bine să prindem
excepții _prea_ generale, fiind foarte ușor să ascundem erori neașteptate în mod neintenționat
(sau mai grav, intenționat din lene). Alt exemplu similar este să prindem în prea multe locuri direct
`std::exception` sau altă clasă de bază foarte comună (procedeu numit uneori Pokémon exception handling).

Reciproc, nu este bine nici să avem prea multe catch-uri specifice pentru că așa nu simplificăm deloc
tratarea erorilor. C++ este un limbaj (prea) special, iar excepțiile complică lucrurile în multe locuri din
limbaj. Este bine să știm că avem la dispoziție acest mecanism, dar este și mai bine să nu aruncăm excepții
doar pentru a emula `goto`. La urma urmei, excepțiile ar trebui folosite doar în situații excepționale.

Ca o încheiere a acestei secțiuni, printre cele mai dezastruoase lucruri pe care le puteți face cu excepțiile
în C++ este să aruncați excepții în destructori. Pe scurt, șansele sunt foarte mari ca programul să sară în
aer 💥

Nu ne mai ajută nici `catch(...)`: dacă se aruncă o excepție în procesul de stack unwinding (vezi mai sus),
se apelează `std::terminate` și programul crapă.

Discuții mai avansate despre excepții specifice C++ [aici](http://www.gotw.ca/gotw/065.htm).

[//]: # (#### Sintaxă aproape inutilă: https://en.cppreference.com/w/cpp/language/function-try-block)

[//]: # (http://www.gotw.ca/gotw/066.htm)

#### Exemplu complet excepții

Puneți cap la cap exemplele anterioare:

- vă definiți o [ierarhie proprie de excepții](#exemplu-ierarhie-proprie) cu bază derivată indirect (sau direct)
  din `std::exception`, de exemplu din `std::runtime_error`
- aruncați excepții **cu sens** în [constructori](#exemplu-throw-în-constructor-și-funcție-non-void)
  sau în funcții care întorc obiecte/valori și să le și prindeți (tot cu sens - minimal în funcția main)
- opțional, vă definiți o [funcție de tratat erori comune](#exemplu-handler-erori-comune)

### Diverse
#### Dynamic cast

Am văzut la moșteniri și funcții virtuale că un obiect de tip derivată poate fi convertit automat la
pointer sau referință de bază:
```c++
class curs {};
class curs_obligatoriu : public curs {};

void f1(curs& curs_) {}
void f2(curs* curs_) {}

int main() {
    curs_obligatoriu c1;
    f1(c1);
    f2(&c1);
}
```

De cele mai multe ori, ar trebui să ne descurcăm cu ajutorul funcțiilor virtuale (ideal prin interfață
non-virtuală). Uneori, în cazuri izolate, interfața din clasa de bază ne limitează și ne trebuie o metodă să
apelăm funcții publice dintr-o clasă derivată care nu sunt definite în clasa de bază.

Dacă avem deja obiectul de tip clasă derivată, problema este rezolvată de la sine. Dacă avem un pointer sau
o referință la clasa de bază, trebuie să folosim `dynamic_cast` pentru a transforma acest pointer/această
referință la pointer/referință către clasa derivată dorită.

Trebuie să activăm virtualizarea: cast-ul dinamic are nevoie de informații despre tipul de date la momentul
execuției. Pentru a nu devia de la subiect, în exemplul următor nu sunt incluse toate funcțiile necesare
atunci când folosim `virtual` (clone, cc/op= protected în bază șamd).

Acest proces este riscant fiindcă nu știm dacă pointerul/referința arată către derivata de care avem nevoie
sau către o altă derivată. Dacă facem cast la pointeri, primim un pointer nul în caz de eșec. Dacă facem cast
la referințe, se aruncă excepția `std::bad_cast` (din `<typeinfo>`) la eșec.
```c++
#include <iostream>
#include <typeinfo>

class curs { public: virtual ~curs() = default; };
class curs_obligatoriu : public curs {
public:
    void f() { std::cout << "f curs obligatoriu\n"; }
};
class curs_facultativ : public curs {
public:
    void g() { std::cout << "g curs facultativ\n"; }
};

void test1(curs* curs_) {
    if(auto* co = dynamic_cast<curs_obligatoriu*>(curs_)) {
        std::cout << "test1 cast pointer reușit\n";
        co->f();
    }
    else
        std::cout << "test1 cast pointer nereușit\n";

    try {
        auto& co = dynamic_cast<curs_obligatoriu&>(*curs_);
        std::cout << "test1 cast referință reușit\n";
        co.f();
    } catch(std::bad_cast& err) {
        std::cout << "test1 cast referință nereușit: " << err.what() << "\n";
    }
}

void test2(curs& curs_) {
    if(auto* co = dynamic_cast<curs_facultativ*>(&curs_)) {
        std::cout << "test2 cast pointer reușit\n";
        co->g();
    }
    else
        std::cout << "test2 cast pointer nereușit\n";

    try {
        auto& co = dynamic_cast<curs_facultativ&>(curs_);
        std::cout << "test2 cast referință reușit\n";
        co.g();
    } catch(std::bad_cast& err) {
        std::cout << "test2 cast referință nereușit: " << err.what() << "\n";
    }
}

int main() {
    curs_obligatoriu c1;
    curs_facultativ c2;
    std::cout << "main: apel test1 cu param curs_obligatoriu\n";
    test1(&c1);
    std::cout << "main: apel test1 cu param curs_facultativ\n";
    test1(&c2);
    std::cout << "main: apel test2 cu param curs_obligatoriu\n";
    test2(c1);
    std::cout << "main: apel test2 cu param curs_facultativ\n";
    test2(c2);
}
```

Conversia de mai sus la `curs_obligatoriu`/`curs_facultativ` va merge și dacă transmitem derivate din
`curs_obligatoriu` sau `curs_facultativ`. Prețul plătit este un timp de execuție ceva mai lent, deoarece
trebuie parcursă toată ierarhia în cel mai rău caz (depinde și de compilator), nu doar până la tipul de
date la care facem cast.

Un alt mod de a identifica tipul de date actual în momentul rulării este cu operatorul `typeid` (header-ul
`<typeinfo>` este obligatoriu). Diferența față de `dynamic_cast` este că merge un pic mai repede, însă
nu va funcționa decât pentru `curs_obligatoriu`/`curs_facultativ`, nu și pentru alte derivate din aceste
clase.

De asemenea, dacă folosim pointer, acesta trebuie dereferențiat. Dacă dereferențiem pointer polimorfic nul,
`typeid` aruncă [`std::bad_typeid`](https://en.cppreference.com/w/cpp/types/bad_typeid).
```c++
#include <iostream>
#include <typeinfo>

class curs { public: virtual ~curs() = default; };
class curs_obligatoriu : public curs {
public:
    void f() { std::cout << "f curs obligatoriu\n"; }
};
class curs_facultativ : public curs {
public:
    void g() { std::cout << "g curs facultativ\n"; }
};

void test1(curs* curs_) {
    if(curs_ == nullptr)
        return;
    if(typeid(curs_) == typeid(curs_obligatoriu*)) {
        std::cout << "test1 typeid(curs_) == typeid(curs_obligatoriu*)\n";
        static_cast<curs_obligatoriu*>(curs_)->f();
        static_cast<curs_obligatoriu&>(*curs_).f();
    }
    if(typeid(curs_) == typeid(curs_obligatoriu)) {
        std::cout << "test1 typeid(curs_) == typeid(curs_obligatoriu)\n";
        static_cast<curs_obligatoriu*>(curs_)->f();
        static_cast<curs_obligatoriu&>(*curs_).f();
    }
    if(typeid(curs_) == typeid(curs_obligatoriu&)) {
        std::cout << "test1 typeid(curs_) == typeid(curs_obligatoriu&)\n";
        static_cast<curs_obligatoriu*>(curs_)->f();
        static_cast<curs_obligatoriu&>(*curs_).f();
    }
    if(typeid(*curs_) == typeid(curs_obligatoriu)) {
        std::cout << "test1 typeid(*curs_) == typeid(curs_obligatoriu)\n";
        static_cast<curs_obligatoriu*>(curs_)->f();
        static_cast<curs_obligatoriu&>(*curs_).f();
    }
    if(typeid(*curs_) == typeid(curs_obligatoriu*)) {
        std::cout << "test1 typeid(*curs_) == typeid(curs_obligatoriu*)\n";
        static_cast<curs_obligatoriu*>(curs_)->f();
        static_cast<curs_obligatoriu&>(*curs_).f();
    }
    if(typeid(*curs_) == typeid(curs_obligatoriu&)) {
        std::cout << "test1 typeid(*curs_) == typeid(curs_obligatoriu&)\n";
        static_cast<curs_obligatoriu*>(curs_)->f();
        static_cast<curs_obligatoriu&>(*curs_).f();
    }
}

void test2(curs& curs_) {
    if(typeid(curs_) == typeid(curs_obligatoriu*)) {
        std::cout << "test2 typeid(curs_) == typeid(curs_obligatoriu*)\n";
        static_cast<curs_obligatoriu*>(&curs_)->f();
        static_cast<curs_obligatoriu&>(curs_).f();
    }
    if(typeid(curs_) == typeid(curs_obligatoriu)) {
        std::cout << "test2 typeid(curs_) == typeid(curs_obligatoriu)\n";
        static_cast<curs_obligatoriu*>(&curs_)->f();
        static_cast<curs_obligatoriu&>(curs_).f();
    }
    if(typeid(curs_) == typeid(curs_obligatoriu&)) {
        std::cout << "test2 typeid(curs_) == typeid(curs_obligatoriu&)\n";
        static_cast<curs_obligatoriu*>(&curs_)->f();
        static_cast<curs_obligatoriu&>(curs_).f();
    }
    if(typeid(&curs_) == typeid(curs_obligatoriu*)) {
        std::cout << "test2 typeid(&curs_) == typeid(curs_obligatoriu*)\n";
        static_cast<curs_obligatoriu*>(&curs_)->f();
        static_cast<curs_obligatoriu&>(curs_).f();
    }
    if(typeid(&curs_) == typeid(curs_obligatoriu)) {
        std::cout << "test2 typeid(&curs_) == typeid(curs_obligatoriu)\n";
        static_cast<curs_obligatoriu*>(&curs_)->f();
        static_cast<curs_obligatoriu&>(curs_).f();
    }
    if(typeid(&curs_) == typeid(curs_obligatoriu&)) {
        std::cout << "test2 typeid(&curs_) == typeid(curs_obligatoriu&)\n";
        static_cast<curs_obligatoriu*>(&curs_)->f();
        static_cast<curs_obligatoriu&>(curs_).f();
    }
}

int main() {
    curs_obligatoriu c1;
    curs_facultativ c2;
    test1(&c1);
    test1(&c2);
    test2(c1);
    test2(c2);
}
```

Rulați exemplul ca să vedeți ce se afișează!

Varianta cu `typeid` merge doar dacă avem potrivire exactă de tip. Chiar dacă ar merge mai repede, este
mult mai urât de extins și mai fragil. Fără verificare de `typeid`, `static_cast` de mai sus
**nu este corect!**

[//]: # (https://stackoverflow.com/questions/12588264/static-cast-and-rtti-vs-dynamic-cast)

**Exercițiu:** comparați `dynamic_cast` cu `typeid`! Adăugați o subclasă pentru `curs_obligatoriu`,
creați un obiect și apelați funcțiile de test.

Dacă folosim smart pointers:
- în cazul std::shared_ptr putem folosi `std::dynamic_pointer_cast` pentru a obține
un std::shared_ptr de clasă derivată
- în cazul std::unique_ptr nu putem face cast la pointer pentru că s-ar încerca crearea unei copii a pointerului
- în ambele cazuri putem face cast către o referință la obiectul dereferențiat
```c++
#include <iostream>
#include <memory>

class curs { public: virtual ~curs() = default; };
class curs_obligatoriu : public curs {
public:
    void f() { std::cout << "f curs obligatoriu\n"; }
};
class curs_facultativ : public curs {
public:
    void g() { std::cout << "g curs facultativ\n"; }
};

int main() {
    std::shared_ptr<curs> ptr1;
    ptr1 = std::make_shared<curs_obligatoriu>();

    // cast la shared ptr
    if(auto ptr_curs_obl = std::dynamic_pointer_cast<curs_obligatoriu>(ptr1)) {
        ptr_curs_obl->f();
    }

    // cast la referință
    try {
        auto curs_obl = dynamic_cast<curs_obligatoriu&>(*ptr1);
        curs_obl.f();
    } catch(std::bad_cast& err) {
        std::cout << "err: " << err.what() << "\n";
    }

    std::unique_ptr<curs> ptr2;
    ptr2 = std::make_unique<curs_obligatoriu>();

    // nu putem face cast la unique ptr deoarece nu putem crea un nou pointer
    // în plus, pot apărea probleme dacă acel cast nu reușește
    // (dacă am vrea de exemplu cu std::move către noul pointer)
    // vezi și https://stackoverflow.com/questions/11002641

    // cast la referință merge, nu obținem un nou pointer
    try {
        auto curs_obl = dynamic_cast<curs_obligatoriu&>(*ptr2);
        curs_obl.f();
    } catch(std::bad_cast& err) {
        std::cout << "err: " << err.what() << "\n";
    }
}
```

Dacă observăm că avem nevoie de multe cast-uri de la bază către derivată, este un semn că nu ne-am definit
corect clasele și/sau funcțiile virtuale. Nevoia de hard-codare a unui tip de date derivat/dynamic_cast/typeid
este un **anti-pattern**: un asemenea cod devine din ce în ce mai greu de extins și de întreținut.

[//]: # (https://stackoverflow.com/questions/12582040/understanding-double-dispatch-c)
[//]: # (https://en.wikipedia.org/wiki/Double_dispatch)
[//]: # (http://www.vishalchovatiya.com/double-dispatch-in-cpp/)
[//]: # (https://en.cppreference.com/w/cpp/utility/variant/visit)

Evitați pe cât posibil downcast-urile, dar este bine să știți că există și această funcționalitate și că este
cea mai bună variantă în unele situații. C++ nu are ([încă?](https://stackoverflow.com/a/13217106)) reflection,
dar se predă RTTI pentru că în alte limbaje uzuale sunt biblioteci care se bazează destul de mult pe reflection.
[Programarea cu "reflexie"](https://en.wikipedia.org/wiki/Reflective_programming) este un fel de meta-programare.
C++ folosește în mod tradițional șabloane pentru meta-programare.

<sub>Fun fact: dacă ne luăm după comentarii de pe net, unele jocuri dezactivează RTTI pentru a îngreuna
crearea de cheats.</sub>

#### Funcții și atribute statice

Funcțiile membru dintr-o clasă de până acum sunt nestatice și le apelăm doar prin intermediul unui obiect.

Funcțiile membru statice sunt la nivel de clasă și le apelăm cu numele clasei. Sintaxa ne permite să
apelăm funcții statice și via un obiect, doar că în felul acesta nu mai este evident dacă funcția este
statică sau nu, deci nu este recomandat.
```c++
#include <iostream>

class curs {
public:
    void f() const {
        std::cout << "funcție membru nestatică\n";
    }
    static void g() {
        std::cout << "funcție membru statică\n";
    }
    // virtual static void h1_1() {}
    // static virtual void h1_2() {}
    // static void h2() const {}
    // static void h3() volatile {}
};

int main() {
    // curs::f(); // eroare
    std::cout << "curs::g()\n";
    curs::g();
    curs c1;
    std::cout << "c1.f()\n";
    c1.f();
    std::cout << "c1.g()\n";
    c1.g(); // valid, dar nerecomandat
    curs* c2 = &c1;
    std::cout << "c2->g()\n";
    c2->g(); // valid, dar nerecomandat
}
```

Funcțiile membru statice sunt la nivel de clasă, deci nu avem nevoie să creăm un obiect pentru a efectua
apeluri. Consecința este că nu avem `*this`, ceea ce înseamnă că funcțiile statice nu pot fi nici virtuale
sau declarate cu `const` (sau `volatile`).

Funcțiile membru statice nu au acces la `*this`, dar au acces la atributele membru statice.

Atributele membru din secțiunile anterioare dintr-o clasă sunt nestatice și sunt la nivel de obiect.
Atributele statice dintr-o clasă nu sunt la nivel de obiect, ci la nivel de clasă. Nu avem nevoie să
creăm un obiect pentru a avea acces și a modifica atribute statice.

Este un pic greșit în curs. Chiar dacă putem folosi atributele statice pe post de variabile globale la nivel
de clasă, atributele statice nu aparțin tuturor obiectelor clasei, din simplul motiv că nu trebuie să avem
vreun obiect din clasa respectivă. Atributele statice sunt pe clasă.

**Atributele membru statice trebuie inițializate în afara clasei, într-un singur fișier `.cpp`!**

Este nevoie să facem inițializarea **doar într-un `.cpp`**, deoarece fișierele `.h` pot fi incluse de mai
multe ori, iar inițializarea s-ar realiza de mai multe ori, ceea ce este interzis de limbaj. Fișierele
`.cpp` sunt compilate o singură dată și nu sunt incluse de alte fișiere.
```c++
#include <iostream>

class curs {
    static int prez_medie;
public:
    static int get_prez_medie() {
        return prez_medie;
    }
    static void up_prez_medie() {
        ++prez_medie;
    }
    static void down_prez_medie() {
        --prez_medie;
    }
};

int curs::prez_medie = 20; // inițializare!!! doar într-un singur fișier .cpp!!!

int main() {
    std::cout << curs::get_prez_medie() << "\n";
    curs::down_prez_medie();
    curs::down_prez_medie();
    std::cout << curs::get_prez_medie() << "\n";
    curs::up_prez_medie();
    curs::up_prez_medie();
    curs::up_prez_medie();
    curs::up_prez_medie();
    std::cout << curs::get_prez_medie() << "\n";
    curs::down_prez_medie();
    std::cout << curs::get_prez_medie() << "\n";
}
```

Nu avem acces din funcții membru statice la atribute membru nestatice, dar avem acces la atribute membru
statice din funcții membru nestatice. O posibilă idee este să generăm id-uri unice:
```c++
#include <iostream>
#include <string>

class curs {
    static int id_max;
    const int id;
    std::string nume;
public:
    explicit curs(std::string nume_) : id(id_max), nume(nume_) { ++id_max; }
    int get_id() const { return id; }
};

int curs::id_max = 1;

int main() {
    curs c1{"oop"}, c2{"mate1"}, c3{"mate2"};
    std::cout << c3.get_id() << "\n";
    std::cout << c2.get_id() << "\n";
    // c1 = c2; // eroare
    curs c4{c1};
    std::cout << c4.get_id() << "\n";
}
```

Observație: soluția nu merge dacă folosim mai multe fire de execuție.

**Atenție!** Atunci când avem atribute constante, compilatorul generează cc, dar nu mai generează și op=
pentru că nu știe să copieze tot, dar fără atributele constante. Constructorul de copiere generat copiază
același id. Dacă ne convine, nu este nevoie să îl suprascriem. Trebuie să ținem cont și că se pot crea
multe obiecte temporare, deci id-ul ar fi mai mare decât numărul de obiecte create explicit de noi.
```c++
#include <iostream>
#include <string>

class curs {
    static int id_max;
    const int id;
    std::string nume;
public:
    explicit curs(std::string nume_) : id(id_max), nume(nume_) { ++id_max; }
    curs(const curs& other) : id(id_max), nume(other.nume) { ++id_max; }
    curs& operator=(const curs& other) { nume = other.nume; return *this; }
    int get_id() const { return id; }
    const std::string& get_nume() const { return nume; }
};

int curs::id_max = 1;

int main() {
    curs c1{"oop"}, c2{"mate1"}, c3{"mate2"};
    std::cout << c3.get_id() << "\n";
    std::cout << c2.get_id() << "\n";
    std::cout << c1.get_nume() << "\n";
    c1 = c2; // eroare
    std::cout << c1.get_nume() << "\n";
    curs c4{c1};
    std::cout << c4.get_id() << "\n";
}
```

Atributele statice constante pot fi inițializate în interiorul clasei doar dacă sunt
de tip întreg/char, constexpr pt tipuri simple non-integral (float, double) sau `inline`:
```c++
class test {
    static const int attr1 = 1;
    static constexpr float attr2 = 2;
    inline static const std::string attr3{"test 3"};
    static const std::string attr4;
};

const std::string test::attr4{"test 4"};  // nu este inline, deci nu merge inițializare direct în clasă
// dacă nu facem inițializarea în afara clasei, primim undefined reference atunci când încercăm să folosim atributul
// tipurile care nu sunt literali nu pot fi declarate (în prezent) cu constexpr
```

Funcțiile și atributele statice sunt aproape identice în restul limbajelor. Ca o încheiere specifică C++,
avem și variabile statice locale. Acestea sunt tot la nivel de clasă, dar sunt vizibile doar în funcția `f`:
```c++
#include <iostream>

class curs {
public:
    void f() const {
        static int nr = 1;
        std::cout << nr << "\n";
        ++nr;
    }
    void g() {
        // std::cout << nr << "\n"; // eroare!
    }
};

int main() {
    curs c1, c2, c3;
    c1.f();
    c2.f();
    c3.f();
    c1.f();
}
```

Din nou, nu faceți abuz de atribute membru `static`, acestea fiind tot un fel de variabile globale, doar
că localizate la nivel de clasă.

#### Moștenire multiplă și virtuală

Exemplele anterioare au ilustrat doar moștenirea simplă, dintr-o singură clasă de bază. Pentru a nu crea un număr
mare de clase intermediare, este util să avem posibilitatea să moștenim pe un singur nivel din mai multe baze.
Moștenirea multiplă poate fi împărțită în două categorii:
- clase de bază fără atribute
- clase de bază cu atribute

De regulă, clasele de bază fără atribute au rolul de interfețe: aceste clase doar declară niște funcții
virtuale pure și nu oferă o implementare. Clasele derivate sunt forțate să aibă definiții pentru funcțiile
din clasa de bază dacă vor să arate că implementează acea interfață.

Moștenirea de interfețe este cel mai frecvent întâlnit tip de moștenire multiplă și este oferit de majoritatea
limbajelor OOP. Vom relua ideea la tema 3 din altă perspectivă.

Exemplul este inspirat de [aici](https://docs.github.com/en/graphql/reference/interfaces).
```c++
class identifiable {
    const int id;
public:
    virtual ~identifiable() = default;
    identifiable() : id(generate_id()) {}
    int get_id() const { return id; }
};

class deletable {
    virtual ~deletable() = default;
    virtual bool can_be_deleted() const = 0;
};

class loggable {
    virtual ~loggable() = default;
    virtual void log(std::string message) const { /* ... */ }
};

class pinned_post : public identifiable, public deletable, public loggable {
    user user_;
public:
    bool can_be_deleted() const override {
        return user_.is_author(*this) || user_.is_admin();
    }

    // void log(std::string message) const override { /* custom logging logic */ }
};
```

Exemplul este minimal pentru a înțelege ideea. Nu sunt definite toate clasele/funcțiile ca să compileze.
Toate interfețele au destructorii virtuali în cazul în care ne-am referi prin pointeri de bază.

Unele interfețe nu pot defini un comportament implicit și atunci obligă clasele care le implementează să
ofere definiții pentru funcțiile virtuale pure. Alte interfețe au funcționalități suficient de bune și
putem păstra logica inițială, însă avem posibilitatea să o suprascriem.

Exemplul nu este grozav pentru că avem un atribut în clasa `identifiable`. Identificatorul ar putea fi
mutat în clasa care implementează interfața.

Multe interfețe comune din alte limbaje sunt implementate sub formă de operatori în C++:

|     C++      | Alte limbaje |
|:------------:|:------------:|
| `operator<`  | `Comparable` |
| `operator==` | `Equatable`  |
| `operator++` |  `Iterable`  |
| `operator<<` | `Printable`  |
| `operator()` |  `Callable`  |

---

Moștenirea multiplă în care clasele de bază au atribute este implementată la nivel de limbaj în C++,
[Python](https://docs.python.org/3/tutorial/classes.html#multiple-inheritance),
[MATLAB](https://www.mathworks.com/help/matlab/matlab_oop/subclassing-multiple-classes.html),
[Perl](https://perldoc.perl.org/perlobj#Multiple-Inheritance),
[Raku](https://docs.raku.org/language/classtut#Multiple_inheritance) și încă unele mai puțin cunoscute.
O parte dintre acestea folosesc un [algoritm de liniarizare](https://en.wikipedia.org/wiki/C3_linearization)
pentru a transforma moștenirea multiplă în mai multe moșteniri simple. Algoritmul a apărut la 7-10 ani după
ce [moștenirea multiplă a apărut în C++](https://en.cppreference.com/w/cpp/language/history).

Dacă ne uităm pe documentațiile respective, vedem că acest fel de moștenire nu este tocmai simplu de realizat
corect și nu este recomandat în majoritatea situațiilor, în favoarea moștenirilor din interfețe
([exemplu](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-mi-interface)).
Și dacă tot vorbim de istorie, probabil nu este întâmplător că majoritatea limbajelor apărute mai târziu
nu oferă moștenire multiplă pentru clase de bază cu atribute, iar această decizie este una intenționată.

Înainte de a arăta dezavantajele moștenirii multiple, să prezentăm sintaxa printr-un exemplu:
```c++
class căști {
    int volum_min;
    int volum_max;
    int volum;
};

class microfon {
    double senzitivitate;
    bool suprimare_ecou;
};

class căști_cu_microfon : public căști, public microfon {};
```

Căștile cu microfon sunt _un fel de_ căști, dar se comportă și ca _un fel de_ microfon. Dacă nu am fi
dorit să expunem partea de "microfon", o variantă era să folosim compunere în loc de moștenire. Totuși,
în acest caz, căștile cu microfon nu ar fi putut fi transmise unei funcții/unui obiect care necesită un
microfon.

Toate atributele din cele două baze sunt preluate de clasa derivată. Desigur, atributele trebuie declarate
`protected` dacă vrem să le accesăm direct în derivată. De asemenea, în situații și mai rare, una sau mai
multe moșteniri pot fi `private` sau `protected` în loc de `public`.

**Atenție!** O eroare frecventă este să scriem moștenirea fără să scriem explicit specificatorii de acces
la fiecare moștenire în parte. Implicit este `private`!
```c++
class căști_cu_microfon : public căști, microfon {};
```

Denumirea clasei derivate nu este tocmai una fericită, însă nu am găsit alt exemplu mai bun (momentan).
Dacă un nume de atribut sau de funcție cu același antet apare în mai multe baze, avem ambiguitate în
derivată și trebuie să ne referim la atribut/funcție cu prefixul bazei: `baza1::f()` sau `baza2::f()`.

Atunci când clasele de bază provin din ierarhii complet independente, moștenirea multiplă este cel mai natural
mod de a modela problema, iar eventualele ambiguități sunt ușor de rezolvat. Nu ne întâlnim foarte des cu așa
ceva, dar în puținele situații relevante ne ajută mai mult decât improvizațiile și trucurile din limbajele
fără moștenire multiplă.

Modificăm exemplul de mai sus: adăugăm o bază comună și punem mesaje de afișare în constructori și destructori.
```c++
#include <iostream>

class periferic {
public:
    enum tip_conector { Con3_5, USB, USB_C, Bluetooth };

    periferic(tip_conector conector_ = USB) : conector(conector_) {
        std::cout << "constr periferic " << conector << "\n";
    }

    ~periferic() {
        std::cout << "destr periferic " << conector << "\n";
    }

    virtual void conectează() const {
        std::cout << "periferic conectat pe " << conector << "\n";
    }

    friend std::ostream& operator<<(std::ostream& os, tip_conector con) {
        switch(con) {
        case Con3_5:
            os << "3.5mm";
            break;
        case USB:
            os << "USB";
            break;
        case USB_C:
            os << "USB-C";
            break;
        case Bluetooth:
            os << "bluetooth";
            break;
        default:
            os << "necunoscut";
        }
        return os;
    }
private:
    tip_conector conector;
};

class căști : public periferic {
public:
    căști() : periferic(Con3_5) {
        std::cout << "constr căști\n";
    }

    ~căști() {
        std::cout << "destr căști\n";
    }

    void conectează() const override {
        std::cout << "căști conectate\n";
    }
private:
    int volum_min = 0;
    int volum_max = 10;
    int volum = 4;
};

class microfon : public periferic {
public:
    microfon() : periferic(USB_C) {
        std::cout << "constr microfon\n";
    }

    ~microfon() {
        std::cout << "destr microfon\n";
    }
    void conectează() const override {
        std::cout << "microfon conectat\n";
    }
private:
    double senzitivitate = 4.2;
    bool suprimare_ecou = true;
};

class căști_cu_microfon : public căști, public microfon { // linia 78
public:
    căști_cu_microfon() {
        std::cout << "constr căști cu microfon\n";
    }

    ~căști_cu_microfon() {
        std::cout << "destr căști cu microfon\n";
    }
};

int main() {
    căști_cu_microfon cm1;
    // cm1.conectează(); // eroare! care funcție conectează?
    cm1.căști::conectează();
}
```

Observăm că se construiește câte un obiect din clasa de bază `periferic` pentru fiecare bază în parte, fiindcă
bazele sunt considerate complet independente. Constructorii sunt apelați în ordinea din definiția clasei,
adică linia 78! Dacă nu apelăm bazele explicit, se apelează fiecare bază cu constructorul fără parametri.
Dacă într-o bază nu avem constructor fără parametri, primim eroare. Constructorul din ultima derivată este
echivalent cu următorul:
```c++
    căști_cu_microfon() : căști(), microfon() {
        std::cout << "constr căști cu microfon\n";
    }
```

**Exercițiu!** Verificați acest lucru: schimbați una dintre baze (`căști` sau `microfon`) pentru a avea doar
constructor cu parametri.

Când vine vorba de funcționalități, lucrurile sunt un pic mai complicate. Dacă ambele baze suprascriu o
funcție virtuală din baza comună, derivata are ambiguitate dacă încercăm să facem apeluri de funcții. Nu
primim eroare de compilare dacă nu apelăm nicăieri funcția, chiar dacă avem ambiguitate!

Specific C++ (nu am săpat în alte limbaje), avem sintaxa oarecum inutilă de care ziceam
[mai devreme](#diverse-funcții-virtuale) prin care apelăm direct funcția din baza care ne interesează. Totuși,
este mai mult un hack.

Mai departe, dacă avem o funcționalitate comună în baza inițială (`periferic`), am vrea să folosim interfața
non-virtuală ca să nu fie apelată această funcționalitate de două ori în derivată (`căști_cu_microfon`).
Codul inițial ar fi următorul:
```c++
class periferic {
public:
    virtual void conectează() const {
        std::cout << "periferic conectat pe " << conector << "\n";
    }
};

class căști : public periferic {
public:
    void conectează() const override {
        periferic::conectează();
        std::cout << "căști conectate\n";
    }
};

class microfon : public periferic {
public:
    void conectează() const override {
        periferic::conectează();
        std::cout << "microfon conectate\n";
    }
};

class căști_cu_microfon : public căști, public microfon {
public:
    void conectează() const override {
        căști::conectează();
        microfon::conectează();
        std::cout << "căști cu microfon conectate\n";
    }
};

int main() {
    căști_cu_microfon cm1;
    cm1.conectează(); // compilează, dar nu face chiar ce trebuie
}
```

Se va afișa:
```
constr periferic 3.5mm
constr căști
constr periferic USB-C
constr microfon
constr căști cu microfon
periferic conectat pe 3.5mm
căști conectate
periferic conectat pe USB-C
microfon conectat
căști cu microfon conectate
destr căști cu microfon
destr microfon
destr periferic USB-C
destr căști
destr periferic 3.5mm
```

Se apelează de două ori implementarea din clasa `periferic`! Cel mai probabil nu vrem asta, mai ales dacă
este vorba de fapt despre un singur conector.

**Exercițiu!** Am omis părți din cod pentru că exemplul ar fi ocupat prea multe rânduri și nu mai era clar
ce încercam să arăt. Adaptați codul inițial cu această implementare.

**Exercițiu!** Rescrieți codul pentru a folosi o interfață non-virtuală. Indiciu:
```c++
class periferic {
public:
    void conectează() const {
        std::cout << "periferic conectat pe " << conector << "\n";
        // apel de funcție virtuală privată
    }
};
```

Dacă doar unele clase din ierarhie au nevoie de codul comun din bază, funcția respectivă ar trebui să fie
protected și eventual non-virtuală.

Pentru acest exemplu, este discutabil dacă are sens să avem conectori diferiți pentru căști și microfon dacă
este vorba despre un singur periferic. Obiectele de tip `cășți_cu_microfon` au două atribute: `căști::conector`
și `microfon::conector`. Dacă mai aveam o bază derivată din `periferic`, mai apărea încă un `conector`.

Pentru a elimina atributele care apar de mai multe ori în derivata care moștenește clase cu bază comună,
C++ ne pune la dispoziție moștenirea virtuală. Moștenirea virtuală trebuie activată pe primul nivel din
ierarhie!

Codul de mai sus rămâne aproape identic. Nu reiau tot exemplul, menționez doar modificările necesare:
```c++
class căști : public virtual periferic { /* restul este identic */ };
class microfon : public virtual periferic { /* restul este identic */ };
```

Ce se va afișa acum?
```
constr periferic USB
constr căști
constr microfon
constr căști cu microfon
periferic conectat pe USB
căști conectate
periferic conectat pe USB
microfon conectat
căști cu microfon conectate
destr căști cu microfon
destr microfon
destr căști
destr periferic USB
```

Constructorul clasei `periferic` s-a apelat acum o singură dată. Totuși...

De ce `USB`??? Conectorul de la căști este implicit `3.5mm` și nu avem alt constructor, iar conectorul de la
microfon este implicit `USB-C` și nu avem alt constructor. Ce se întâmplă???

La moștenirea virtuală, compilatorul trebuie să garanteze că baza comună se construiește **o singură dată**,
înaintea tuturor derivatelor care urmează. Derivatele `căști` și `microfon` nu mai apelează constructorul
clasei de bază `periferic` în acest context, deoarece acesta a fost deja apelat! Așadar, constructorul generat
de compilator din clasa `căști_cu_microfon` este echivalent cu următorul constructor:
```c++
    căști_cu_microfon() : periferic(), căști(), microfon() {
        std::cout << "constr căști cu microfon\n";
    }
```

Prin urmare, dacă vrem să setăm atributul respectiv, am scrie constructorul astfel:
```c++
    căști_cu_microfon(tip_conector con) : periferic(con), căști(), microfon() {
        std::cout << "constr căști cu microfon\n";
    }
```

**Observație!** Dacă avem constructor cu parametri în baza comună și nu îl apelăm explicit din derivată,
primim eroare la compilare. Presupunem că revenim la versiunea anterioară a codului, iar în bază nu mai
avem valoare implicită (restul rămâne la fel, cu moșteniri virtuale):
```c++
class periferic {
public:
    periferic(tip_conector conector_) : conector(conector_) {
        std::cout << "constr periferic " << conector << "\n";
    }
};

class căști_cu_microfon : public căști, public microfon {
public:
    căști_cu_microfon() : căști(), microfon() {
        std::cout << "constr căști cu microfon\n";
    }
};
```

Avem moștenire virtuală, deci implicit avem în constructorul din derivată este echivalent cu a avea:
```c++
căști_cu_microfon() : periferic(), căști(), microfon() {}
```

Primim următoarea eroare:
```
main.cpp: In constructor ‘căști_cu_microfon::căști_cu_microfon()’:
main.cpp:82:45: error: no matching function for call to ‘periferic::periferic()’
   82 |     căști_cu_microfon() : căști(), microfon() {
      |                                             ^
main.cpp:7:5: note: candidate: ‘periferic::periferic(periferic::tip_conector)’
    7 |     periferic(tip_conector conector_) : conector(conector_) {
      |     ^~~~~~~~~
main.cpp:7:5: note:   candidate expects 1 argument, 0 provided
main.cpp:3:7: note: candidate: ‘constexpr periferic::periferic(const periferic&)’
    3 | class periferic {
      |       ^~~~~~~~~
main.cpp:3:7: note:   candidate expects 1 argument, 0 provided
```

Clang ne oferă un mesaj ceva mai clar:
```
main.cpp:82:5: error: constructor for 'căști_cu_microfon' must explicitly initialize the base class 'periferic' which does not have a default constructor
    căști_cu_microfon() : căști(), microfon() {
    ^
main.cpp:3:7: note: 'periferic' declared here
class periferic {
      ^
```

Totuși, dacă includem apelul explicit al bazei, se presupune că știm ce facem și primim acest mesaj de la clang.
Săgeata este mai bine poziționată decât la g++, unde mesajul este identic:
```
main.cpp:82:29: error: no matching constructor for initialization of 'periferic'
    căști_cu_microfon() : periferic(), căști(), microfon() {
                          ^
main.cpp:7:5: note: candidate constructor not viable: requires single argument 'conector_', but no arguments were provided
    periferic(tip_conector conector_) : conector(conector_) {
    ^
main.cpp:3:7: note: candidate constructor (the implicit copy constructor) not viable: requires 1 argument, but 0 were provided
class periferic {
      ^
```

Atât moștenirea multiplă, cât și inițializarea sunt funcționalități foarte complicate în C++ dacă intrăm în
(prea multe) detalii. Este posibil să dați de diverse bug-uri pe compilatoare mai vechi (g++ < 8)
dacă folosiți moștenire multiplă și inițializare cu acolade.

Ca fapt divers, `virtual public` este același lucru, dar nu mai merge syntax highlight pe github
(oricum nu prea merge dacă avem diacritice).

**Observație! Nu punem moștenirea virtuală atunci când "unim" clasele, ci pe primul nivel unde facem derivate!**

Pentru a ne convinge, modificăm clasele anterioare astfel:
```c++
class periferic { /* restul este identic */ };
class căști : public periferic { /* restul este identic */ };
class microfon : public periferic { /* restul este identic */ };
class căști_cu_microfon : public virtual căști, public virtual microfon { /* restul este identic */ };
```

Se va afișa:
```
constr periferic 3.5mm
constr căști
constr periferic USB-C
constr microfon
constr căști cu microfon
periferic conectat pe 3.5mm
căști conectate
periferic conectat pe USB-C
microfon conectat
căști cu microfon conectate
destr căști cu microfon
destr microfon
destr periferic USB-C
destr căști
destr periferic 3.5mm
```

Dacă punem `virtual` acolo, **nu are niciun efect!** Moștenirea virtuală se activează de-abia după aceea.
Acele `virtual`-uri ar avea efect doar dacă facem derivate din `class_căști_cu_microfon` și eventual cu
alte baze virtuale, dar s-ar elimina din atributele comune doar în aceste derivate ulterioare **după ce**
a fost activată moștenirea virtuală.

Să mai vedem ceva. Ce afișează programul de mai jos?
```c++
#include <iostream>

class bază {};
class der1 : public bază {};
class der2 : public bază {};
class der3 : public bază {};
class der4 : public der1, public der2, public der3 {};
class bază2 {};
class der5 : public bază, public bază2 {};

int main() {
    std::cout << "sizeof(bază): " << sizeof(bază) << "\n";
    std::cout << "sizeof(der1): " << sizeof(der1) << "\n";
    std::cout << "sizeof(der4): " << sizeof(der4) << "\n";
    std::cout << "sizeof(der5): " << sizeof(der5) << "\n";
}
```

Se va afișa:
```
sizeof(bază): 1
sizeof(der1): 1
sizeof(der4): 3
sizeof(der5): 1
```

Dar pe msvc:
```
sizeof(bază): 1
sizeof(der1): 1
sizeof(der4): 2
sizeof(der5): 1
```

Așadar, moștenirea multiplă cu bază comună nu este tocmai gratuită, dar nu avem costuri dacă bazele sunt
complet independente. Dar moștenirea virtuală? Să ne limităm momentan la două clase derivate:
```c++
#include <iostream>

class bază {};
class der1 : public virtual bază {};
class der2 : public virtual bază {};
class der4 : public der1, public der2 {};

int main() {
    std::cout << "sizeof(bază): " << sizeof(bază) << "\n";
    std::cout << "sizeof(der1): " << sizeof(der1) << "\n";
    std::cout << "sizeof(der4): " << sizeof(der4) << "\n";
}
```

Se va afișa (pe g++, clang, msvc):
```
sizeof(bază): 1
sizeof(der1): 8
sizeof(der4): 16
```

Nici moștenirea virtuală nu este gratuită, dar plătim costul doar pentru pointerii de la moștenirea virtuală.

Pentru 3 moșteniri, vom avea (pe g++, clang, msvc):
```
sizeof(bază): 1
sizeof(der1): 8
sizeof(der4): 24
```

Dar dacă avem și funcții virtuale?
```c++
#include <iostream>

class bază {
public:
    virtual ~bază() = default;
};

class der1 : public virtual bază {};
class der2 : public virtual bază {};
class der4 : public der1, public der2 {};

int main() {
    std::cout << "sizeof(bază): " << sizeof(bază) << "\n";
    std::cout << "sizeof(der1): " << sizeof(der1) << "\n";
    std::cout << "sizeof(der4): " << sizeof(der4) << "\n";
}
```

Se va afișa:
```
sizeof(bază): 8
sizeof(der1): 8
sizeof(der4): 16
```

Iar dacă avem 3 derivate:
```
sizeof(bază): 8
sizeof(der1): 8
sizeof(der4): 24
```

Așadar, fiecare moștenire virtuală pare să adauge un nou pointer, însă nu mai crește `sizeof`-ul și când
adăugăm funcții virtuale. Sau nu chiar! **Depinde de compilator!**

Pe msvc cu 3 derivate se va afișa:
```
sizeof(bază): 8
sizeof(der1): 16
sizeof(der4): 24
```

Cu acest bagaj de cunoștințe, poate fi mai ușor să analizăm un alt exemplu de eroare. De câte ori avem `x`
în clasa `der4`?
```c++
class bază { int x; };
class der1 : public virtual bază {};
class der2 : public virtual bază {};
class der3 : public bază {};
class der4 : public der1, public der2, public der3 {};

int main() {
    std::cout << "sizeof(bază): " << sizeof(bază) << "\n";
    std::cout << "sizeof(der1): " << sizeof(der1) << "\n";
    std::cout << "sizeof(der3): " << sizeof(der3) << "\n";
    std::cout << "sizeof(der4): " << sizeof(der4) << "\n";
}
```

Întâi de toate, primim acest warning pe gcc (nu și pe clang):
```
main.cpp:110:7: warning: virtual base ‘bază’ inaccessible in ‘der4’ due to ambiguity [-Winaccessible-base]
  110 | class der4 : public der1, public der2, public der3 {};
      |       ^~~~
```

Se va afișa:
```
sizeof(bază): 4
sizeof(der1): 16
sizeof(der3): 4
sizeof(der4): 24
```

Iar pe msvc:
```
sizeof(bază): 4
sizeof(der1): 16
sizeof(der3): 4
sizeof(der4): 32
```

Presupunem că `sizeof(int) == 4`. Pe g++/clang avem în `der4`:
- 4 bytes dintr-un `x` de la `der1` și `der2`
- 4 bytes dintr-un `x` de la `der3`
- 8 bytes din `virtual` de la der1
- 8 bytes din `virtual` de la der2

Total: 24.

Pe msvc, bănuiala mea este că ocupă mai mult din cauza unor bytes de padding. Cu directiva `#pragma pack(1)`
obținem și pe msvc 24 pentru `der4`. Pentru `der1` am obține 12, deci și acolo pare să fie padding.

##### Sidecast/crosscast

La moștenirile multiple, putem face conversii cu dynamic_cast și lateral, nu doar downcasting.

Dintr-un pointer de tip Der1 care arată de fapt către un obiect de tip DerM, putem obține un pointer de tip Der2 (frați/surori/siblings):
```c++
#include <iostream>

class Baza {
public:
    virtual ~Baza() = default;
};
class Der1 : public virtual Baza {};
class Der2 : public virtual Baza {};
class DerM : public Der1, public Der2 {};

int main() {
    Baza *b = new DerM;
    if(auto ptr1 = dynamic_cast<Der1*>(b)) {
        std::cout << "downcast\n";
        // ptr1 este de tip Der1*
        if(auto ptr2 = dynamic_cast<Der2*>(ptr1)) {
            std::cout << "sidecast\n";
        }
    }
    delete b;
}
```

##### Concluzii

Moștenirea multiplă și virtuală complică multe alte aspecte ale limbajului (de exemplu, excepțiile și RTTI).
Am omis acest lucru în secțiunile precedente. Ca să nu discredităm complet aceste facilități, menționez că
ele sunt utile atunci când alternativele îngreunează și mai mult întreținerea și extinderea codului.
Detalii, explicații și exemple [aici](https://isocpp.org/wiki/faq/multiple-inheritance) și
[aici](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-kind).


[//]: # (### Fișiere header și fișiere sursă)

## Cerințe tema 2

Continuăm familiarizarea cu limbajul C++ (din nou) și învățăm alte noțiuni OOP de bază: moșteniri și excepții.

Pentru lista completă a cerințelor, vezi [template-ul de proiect](../tema-1/README#template-proiect).

Cerințe comune:
- separarea codului din clase în fișiere header (`.h`/`.hpp` etc.) și surse (`.cpp` etc.)
  - clasele mici și legate între ele se pot afla în aceeași pereche de fișiere header-sursă
  - FĂRĂ `using namespace std` în fișiere `.h`/`.hpp` la nivel global
    - pot fi declarații locale în cpp-uri
- moșteniri
  - funcții virtuale (pure), constructori virtuali (clone)
    - funcțiile virtuale vor fi apelate prin pointeri la clasa de bază
    - pointerii la clasa de bază vor fi atribute ale altei clase, nu doar niște pointeri/referințe în main
  - `dynamic_cast`
  - suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
- excepții
  - ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`
  - utilizare cu sens: de exemplu, `throw` în constructor, `try`/`catch` în `main`
- funcții și atribute statice

#### Termen limită
- săptămâna 7 (20 noiembrie/9 aprilie): progres parțial
- **săptămâna 8 (27 noiembrie/16 aprilie): tema 2 gata**
- săptămâna 9 (4 decembrie/29 aprilie): (eventuale) modificări în urma feedback-ului
