
#### Rețin adresele unor variabile locale și "la mine merge". De ce ar trebui să îmi pese?

Situația întâlnită în multe teme este echivalentă cu codul de mai jos, doar că ați avut noroc să nu crape deoarece sunt adăugate adresele unor variabile din funcția main care se distrug la sfârșitul programului.

Ce încerc să zic este că dacă folosiți clasele definite de voi și în alte părți decât funcția main, o să crape foarte urât.

Vă rog să confirmați că vă crapă și vouă codul de mai jos.

```c++
#include <iostream>
#include <vector>

class C1 {
public:
  virtual ~C1() = default;
  virtual void afis(std::ostream& os) const { os << "c1"; }
  friend std::ostream& operator<<(std::ostream& os, const C1& c) {
    c.afis(os);
    return os;
  }
};

class C2 : public C1 {
public:
  void afis(std::ostream& os) const override { os << "c2"; }
};
class C3 : public C1 {
public:
  void afis(std::ostream& os) const override { os << "c3"; }
};

class D {
  std::vector<C1*> elem;
public:
  void adauga(C1* c) { elem.push_back(c); }
  friend std::ostream& operator<<(std::ostream& os, const D& d) {
    for(const C1* c : d.elem) {
      os << *c << "\n";
    }
    return os;
  }
};

void adauga1(D& d) {
  C1 c;
  d.adauga(&c);
}

void adauga2(D& d) {
  C2 c;
  d.adauga(&c);
}

int main() {
  D d;
  std::cout << d;
  adauga1(d);
  std::cout << d;
  adauga2(d);
  std::cout << d;
  adauga1(d);
  std::cout << d;
}
```

Compilat cu `g++ var_locale.cpp -o vars -Wall -Wextra -pedantic -g -fsanitize=address`.
<details>
  <summary>Output de la sanitizer</summary>
<pre>
./vars                                                                                                                                                                                          !10012
=================================================================
==31314==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x602000000028 at pc 0x55a9ae10ea02 bp 0x7fffaba700a0 sp 0x7fffaba70090
READ of size 8 at 0x602000000028 thread T0
    #0 0x55a9ae10ea01 in operator<<(std::ostream&, C1 const&) poo/var_locale.cpp:9
    #1 0x55a9ae10ecd6 in operator<<(std::ostream&, D const&) poo/var_locale.cpp:29
    #2 0x55a9ae10e7c6 in main poo/var_locale.cpp:49
    #3 0x7f3f5a604082 in __libc_start_main ../csu/libc-start.c:308
    #4 0x55a9ae10e38d in _start (poo/vars+0x238d)

0x602000000028 is located 16 bytes to the right of 8-byte region [0x602000000010,0x602000000018)
allocated by thread T0 here:
    #0 0x7f3f5ac65587 in operator new(unsigned long) ../../../../src/libsanitizer/asan/asan_new_delete.cc:104
    #1 0x55a9ae110d28 in __gnu_cxx::new_allocator<C1*>::allocate(unsigned long, void const*) /usr/include/c++/9/ext/new_allocator.h:114
    #2 0x55a9ae11081b in std::allocator_traits<std::allocator<C1*> >::allocate(std::allocator<C1*>&, unsigned long) /usr/include/c++/9/bits/alloc_traits.h:443
    #3 0x55a9ae1104bd in std::_Vector_base<C1*, std::allocator<C1*> >::_M_allocate(unsigned long) /usr/include/c++/9/bits/stl_vector.h:343
    #4 0x55a9ae10f94b in void std::vector<C1*, std::allocator<C1*> >::_M_realloc_insert<C1* const&>(__gnu_cxx::__normal_iterator<C1**, std::vector<C1*, std::allocator<C1*> > >, C1* const&) /usr/include/c++/9/bits/vector.tcc:440
    #5 0x55a9ae10ef6c in std::vector<C1*, std::allocator<C1*> >::push_back(C1* const&) /usr/include/c++/9/bits/stl_vector.h:1195
    #6 0x55a9ae10eaf9 in D::adauga(C1*) poo/var_locale.cpp:26
    #7 0x55a9ae10e518 in adauga1(D&) poo/var_locale.cpp:37
    #8 0x55a9ae10e7b2 in main poo/var_locale.cpp:48
    #9 0x7f3f5a604082 in __libc_start_main ../csu/libc-start.c:308

SUMMARY: AddressSanitizer: heap-buffer-overflow poo/var_locale.cpp:9 in operator<<(std::ostream&, C1 const&)
Shadow bytes around the buggy address:
  0x0c047fff7fb0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c047fff7fc0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c047fff7fd0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c047fff7fe0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c047fff7ff0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x0c047fff8000: fa fa 00 fa fa[fa]fa fa fa fa fa fa fa fa fa fa
  0x0c047fff8010: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff8020: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff8030: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff8040: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff8050: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc
==31314==ABORTING  </pre>
</details>

<details>
  <summary>Output de la valgrind (desigur, compilat fără sanitizer)</summary>
<pre>
valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./vars
==31391== Memcheck, a memory error detector
==31391== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==31391== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==31391== Command: ./vars
==31391== 
==31391== Invalid read of size 8
==31391==    at 0x10959F: operator<<(std::ostream&, C1 const&) (var_locale.cpp:9)
==31391==    by 0x109693: operator<<(std::ostream&, D const&) (var_locale.cpp:29)
==31391==    by 0x10944E: main (var_locale.cpp:49)
==31391==  Address 0x4dfac98 is 16 bytes after a block of size 8 alloc'd
==31391==    at 0x483CFE3: operator new(unsigned long) (vg_replace_malloc.c:422)
==31391==    by 0x10A51D: __gnu_cxx::new_allocator<C1*>::allocate(unsigned long, void const*) (new_allocator.h:114)
==31391==    by 0x10A355: std::allocator_traits<std::allocator<C1*> >::allocate(std::allocator<C1*>&, unsigned long) (alloc_traits.h:443)
==31391==    by 0x10A14B: std::_Vector_base<C1*, std::allocator<C1*> >::_M_allocate(unsigned long) (stl_vector.h:343)
==31391==    by 0x109BB2: void std::vector<C1*, std::allocator<C1*> >::_M_realloc_insert<C1* const&>(__gnu_cxx::__normal_iterator<C1**, std::vector<C1*, std::allocator<C1*> > >, C1* const&) (vector.tcc:440)
==31391==    by 0x109835: std::vector<C1*, std::allocator<C1*> >::push_back(C1* const&) (stl_vector.h:1195)
==31391==    by 0x109608: D::adauga(C1*) (var_locale.cpp:26)
==31391==    by 0x109326: adauga1(D&) (var_locale.cpp:37)
==31391==    by 0x10943B: main (var_locale.cpp:48)
==31391== 
==31391== Jump to the invalid address stated on the next line
==31391==    at 0x0: ???
==31391==    by 0x109693: operator<<(std::ostream&, D const&) (var_locale.cpp:29)
==31391==    by 0x10944E: main (var_locale.cpp:49)
==31391==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==31391== 
==31391== 
==31391== Process terminating with default action of signal 11 (SIGSEGV)
==31391==  Bad permissions for mapped region at address 0x0
==31391==    at 0x0: ???
==31391==    by 0x109693: operator<<(std::ostream&, D const&) (var_locale.cpp:29)
==31391==    by 0x10944E: main (var_locale.cpp:49)
==31391== 
==31391== HEAP SUMMARY:
==31391==     in use at exit: 72,712 bytes in 2 blocks
==31391==   total heap usage: 2 allocs, 0 frees, 72,712 bytes allocated
==31391== 
==31391== 8 bytes in 1 blocks are still reachable in loss record 1 of 2
==31391==    at 0x483CFE3: operator new(unsigned long) (vg_replace_malloc.c:422)
==31391==    by 0x10A51D: __gnu_cxx::new_allocator<C1*>::allocate(unsigned long, void const*) (new_allocator.h:114)
==31391==    by 0x10A355: std::allocator_traits<std::allocator<C1*> >::allocate(std::allocator<C1*>&, unsigned long) (alloc_traits.h:443)
==31391==    by 0x10A14B: std::_Vector_base<C1*, std::allocator<C1*> >::_M_allocate(unsigned long) (stl_vector.h:343)
==31391==    by 0x109BB2: void std::vector<C1*, std::allocator<C1*> >::_M_realloc_insert<C1* const&>(__gnu_cxx::__normal_iterator<C1**, std::vector<C1*, std::allocator<C1*> > >, C1* const&) (vector.tcc:440)
==31391==    by 0x109835: std::vector<C1*, std::allocator<C1*> >::push_back(C1* const&) (stl_vector.h:1195)
==31391==    by 0x109608: D::adauga(C1*) (var_locale.cpp:26)
==31391==    by 0x109326: adauga1(D&) (var_locale.cpp:37)
==31391==    by 0x10943B: main (var_locale.cpp:48)
==31391== 
==31391== 72,704 bytes in 1 blocks are still reachable in loss record 2 of 2
==31391==    at 0x483C855: malloc (vg_replace_malloc.c:381)
==31391==    by 0x4917C69: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.29)
==31391==    by 0x4011B99: call_init.part.0 (dl-init.c:72)
==31391==    by 0x4011CA0: call_init (dl-init.c:30)
==31391==    by 0x4011CA0: _dl_init (dl-init.c:119)
==31391==    by 0x4001139: ??? (in /lib/x86_64-linux-gnu/ld-2.31.so)
==31391== 
==31391== LEAK SUMMARY:
==31391==    definitely lost: 0 bytes in 0 blocks
==31391==    indirectly lost: 0 bytes in 0 blocks
==31391==      possibly lost: 0 bytes in 0 blocks
==31391==    still reachable: 72,712 bytes in 2 blocks
==31391==         suppressed: 0 bytes in 0 blocks
==31391== 
==31391== For lists of detected and suppressed errors, rerun with: -s
==31391== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
[1]    31391 segmentation fault (core dumped)  valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./vars </pre>
</details>

**Soluții posibile**
- alocări dinamice cu `new`; trebuie șters la un moment dat cu `delete` tot ce am alocat cu `new`
- trecere la smart pointers; alocare cu `std::make_shared` sau `std::make_unique`

Indiferent de tipul de pointeri, trebuie suprascriși (sau șterși) cc/op= în clasele unde avem atribute pointeri pentru ca funcțiile membru speciale să funcționeze corect.

#### Am o funcție virtuală, iar compilatorul meu (nu) face automat și destructorul virtual.

**De ce pe alt compilator/alt sistem de operare (nu) îmi crapă programul?**

Limbajul C++ nu obligă compilatoarele să genereze destructorul ca fiind virtual. De aceea, cel mai bine
este să declarăm noi în mod explicit că destructorul este virtual dacă avem cel puțin încă o funcție
virtuală.

De ce nu se face asta în mod automat _prin definiție_? Am găsit că și
[altcineva](https://stackoverflow.com/questions/1117481#comment110485430_1117484) s-a mai întrebat asta.
Răspunsul este doar o bănuială de-a mea.

Nu se face automat destructorul virtual deoarece există situații când am vrea ca destructorul să fie
protected și nevirtual (pentru că nu ar fi nevoie să fie virtual) pentru a nu da voie crearea obiectelor
prin pointer la baza respectivă (întrucât destructorul nu e accesibil/public). Mai multe detalii
[aici](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-dtor-virtual).

Totuși, în acele situații nu am folosi polimorfism, deci tot nu avem un răspuns complet la întrebare.

#### Am redenumit proiectul și nu mai merg bifele, primesc erori ciudate

Soluție: șterge cache-urile din browser. Pe tab-ul Actions în stânga la Management - Caches. Trebuie șterse unul
câte unul. Accept pull requests pentru a simplifica acest proces.

Cu `gh` CLI se poate: https://cli.github.com/manual/gh_cache_delete

#### Folosesc fișiere externe (imagini, sunete etc.) și nu sunt găsite local sau pe acțiuni

Vezi cu funcția `copy_files` la sfârșit în CMakeLists.txt. Sunt exemple de apeluri în comentarii.

Dacă ai multe fișiere, este mai simplu să ai grupate fișierele în foldere deoarece așa adaugi în
apelul de `copy_files` doar folder-ul, nu fiecare fișier individual.

#### Codul rulează la nesfârșit pe bife/acțiuni

Verifică datele din fișierul `tastatura.txt`. De asemenea, vezi să nu confunzi citirile simple (`std::cin`)
cu citiri la nivel de rând (`std::getline`).

#### Pe Windows nu găsește definiție pentru `min`/`max`/`abs` etc

Problema este din cauză că `Windows.h` definește `min`/`max` etc sub formă de macros, deci nu mai poți scăpa de ele.

Soluție: schimbă ordinea include-urilor astfel încât `Windows.h` să fie inclus la urmă.

Alternativ, definește constanta `NOMINMAX` înainte de a include `Windows.h`. Vezi și `WIN32_LEAN_AND_MEAN`.
Vezi și cum am făcut pe branch-ul common-libs cu rlutil pentru a restaura valorile vechi ale macro-urilor.

De asemenea, ai grijă să faci asta doar pentru Windows, altfel va crăpa pe celelalte medii.

#### Nu am schimbat nimic și brusc sunt erori ciudate pe bife/acțiuni

Erorile sunt din vina mea (mcmarius) sau din vina altora 🙂

Pentru erorile din vina mea, vedeți dacă nu au apărut commit-uri noi pe repository-ul template.

Pentru erorile din vina altora, vedeți în issues pe acțiunea care crapă, pe [GitHub Status](https://githubstatus.com)
sau pe repo-ul de [runners](https://github.com/actions/runner-images/issues).
