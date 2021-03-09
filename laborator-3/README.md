# Laboratorul 3

### ⚠ Puneți cât mai multe întrebări! Nu există întrebări greșite.
#### Semnalați orice fel de greșeli găsiți!

În acest laborator vom studia un exemplu de situație în care avem nevoie să definim explicit constructori de copiere/operator=. Vom vedea pe parcurs că, dacă nu dorim ceva special, nu va mai fi nevoie de aceștia, însă situațiile în care este nevoie de acest ceva special pot face diferența.

**Plan minimal**
- constructori expliciți
- `virtual`
- moștenire vs compunere
- transmitere prin valoare, transmitere prin referință
- de revenit asupra cc și op=
- `static`?
- RAII

**Punct de plecare**

Puteți ignora secțiunea asta. 🚧

Un ospătar ține evidența mai multor comenzi. Ospătarii pot face schimb de comenzi. Comenzile sunt preluate de bucătari. Pentru simplitate, folosim fișiere.

Situații de discutat:
- se mai poate modifica o comandă după ce a fost trimisă la bucătărie?
  - dacă nu se pot modifica, trebuie să mai avem o clasă pentru nota de plată: obiectele de acest tip vor reține toate comenzile de la aceeași masă
- moșteniri: tipuri de clienți, mod de servire (bacșiș diferit), feluri de mâncare (mod de preparare specific)

Într-un scenariu mai modern, fișierele sunt înlocuite de o bază de date, iar chelnerii folosesc aplicații mobile.
```c++
class comanda {
    int nr_masa;
    FILE *continut;
};

class ospatar {
    // scrie comenzi
};

class bucatar {
    // citeste comenzi;
};
```

## Biblioteci externe

În cazul în care dorim funcționalități mai avansate sau mai specifice față de ce ne oferă bibliotecile standard, va trebui să folosim biblioteci externe.

Pașii sunt următorii:
- descărcarea bibliotecii
- dacă nu există fișiere binare (sau acestea nu funcționează), compilarea codului sursă
  - **⚠ atenție!** Codul obiect nu este portabil între sisteme de operare diferite!
- adăugarea căii către fișierele header (cu opțiunea `-Inume_folder_cu_headere`)
- includerea fișierului/fișierelor header în codul nostru sursă
- adăugarea căii către fișierele de bibliotecă compilate (cu opțiunea `-Lnume_folder_cu_libs`)
  - extensii posibile: `.a` (archive), `.lib`, `.so` (shared object), `.dll` (dynamic linked library)
  - numele pot începe cu `lib`, dar nu este obligatoriu
- legarea/link-uirea (linking-ul?) efectivă a bibliotecilor statice de care avem nevoie (cu opțiunnea `-lnume_biblioteca` - este litera L mic)
- adăugarea bibliotecilor dinamice: trebuie să existe în directorul curent sau în `PATH`

Observații:
- unele biblioteci sunt de tip header-only, deci nu sunt necesari decât pașii 1, 3 și 4 (sau doar 1 și 4 dacă adăugăm sursa în repo)
- unele biblioteci sunt gândite să fie legate doar static, altele doar dinamic, iar altele în ambele feluri (adică au o parte cu fișiere statice și alta cu fișiere dinamice)
- de verificat că licențele bibliotecilor pe care le folosim sunt compatibile cu licența proiectului nostru

**Care este diferența dintre bibliotecile legate static și cele legate dinamic?**

Bibliotecile statice sunt necesare atunci când compilăm codul, ceea ce înseamnă că vor crește dimensiunea executabilului. Bibliotecile dinamice sunt necesare numai atunci când rulăm programul.

### Biblioteci recomandate

În această secțiune, aș vrea să vă recomand doar biblioteci care sunt **portabile**.

- [SFML](https://www.sfml-dev.org/): grafică, sunete (posibil să trebuiască schimbat DLL-ul de OpenAL pe Windows... sau nu)
- 🚧 secțiune incompletă
- [rlutil](https://github.com/tapio/rlutil) pentru text colorat
- am mai reușit să folosesc [libpqxx](https://github.com/jtv/libpqxx), [GLFW](https://www.glfw.org/download.html), [SOIL](https://github.com/kbranigan/Simple-OpenGL-Image-Library) (nu sunt sigur dacă asta e), [SOIL2](https://github.com/SpartanJ/SOIL2), [indicators](https://github.com/p-ranav/indicators) (bară de progres)
- la SIGIL nu mi-a mers sunetul (și are nevoie de un DLL din MSYS2)

De încercat:
- [cpr](https://github.com/whoshuu/cpr)
- json parsing:
  - [nlohmann/json](https://github.com/nlohmann/json) (am aflat de la @MihaiVoinea 👍)
  - dacă vreți performanță, recomand [OjC](https://github.com/ohler55/ojc)
- Boost (??)
- ~ICU~ (nope, e foarte nașpa, nu merită efortul, deși funcționalitatea e ce trebuie) (??)
- [tiny-utf8](https://github.com/DuffsDevice/tiny-utf8) pare mult mai ok, dar încă n-am încercat
- https://github.com/agauniyal/rang

### Alte sfaturi

Pentru fișiere mari (minim câțiva MB), este recomandat să folosiți [`git-lfs`](https://git-lfs.github.com/). Astfel, dacă le modificați, pe repository-ul local veți avea o singură copie a acestor fișiere mari, însă istoricul complet al modificărilor se va afla pe repository-ul remote (desigur, trebuie ca acesta să știe de lfs).

## Resurse recomandate
- [cppreference.com](https://en.cppreference.com/w/cpp)
- [StackOverflow](https://stackoverflow.com/questions/tagged/cpp?tab=Votes)
- [ISO C++ FAQ](https://isocpp.org/faq/)
- [Diverse standarde (draft) ale limbajului](https://en.cppreference.com/w/cpp/links) sau ca [HTML (neoficial)](https://github.com/timsong-cpp/cppwp) (sau [aici](https://stackoverflow.com/questions/81656/where-do-i-find-the-current-c-or-c-standard-documents#4653479))
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
