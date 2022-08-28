# Biblioteci externe

### ⚠ Puneți cât mai multe întrebări! Nu există întrebări greșite.
#### Semnalați orice fel de greșeli găsiți!

Work In Progress (WIP) 🚧


TL;DR:
- bibliotecile header-only le includem direct în repository
  - le punem într-un folder separat ca să putem să ignorăm warnings din dependențe externe
- pentru bibliotecile care trebuie compilate, cel mai simplu mi se pare cu FetchContent: doar trebuie decomentat
apelul din CMakeLists.txt din repository-ul template și apoi decomentat caching-ul dependențelor din cmake.yml
  - `include(FetchContent)`, apoi
  - pentru fiecare astfel de bibliotecă, pașii ar fi în CMakeLists.txt:
    - `FetchContent_Declare(...)`
    - `FetchContent_MakeAvailable(...)`
    - `target_include_directories(...)`
    - `target_link_directories(...)`
    - `target_link_libraries(...)`
    - eventual `install(FILES ...)`

În cazul în care dorim funcționalități mai avansate sau mai specifice față de ce ne oferă bibliotecile standard,
va trebui să folosim biblioteci externe.

[//]: # (TODO ldd pe Linux, otool -L pe macOS &#40;dar nu numai&#41;)

[//]: # (https://stackoverflow.com/questions/55196053/ldd-r-equivalent-on-macos)

[//]: # (https://cpufun.substack.com/p/which-library-did-you-say-will-be)

[//]: # (Pașii sunt următorii:)
[//]: # (- descărcarea bibliotecii)
[//]: # (- dacă nu există fișiere binare &#40;sau acestea nu funcționează&#41;, compilarea codului sursă)
  - **⚠ atenție!** Codul obiect nu este portabil între sisteme de operare/compilatoare diferite!

[//]: # (- adăugarea căii către fișierele header &#40;cu opțiunea `-Inume_folder_cu_headere`&#41;)
[//]: # (- includerea fișierului/fișierelor header în codul nostru sursă)
[//]: # (- adăugarea căii către fișierele de bibliotecă compilate &#40;cu opțiunea `-Lnume_folder_cu_libs`&#41;)
[//]: # (  - extensii posibile: `.a` &#40;archive&#41;, `.lib`, `.so` &#40;shared object&#41;, `.dll` &#40;dynamic
 linked library&#41;)
[//]: # (  - numele pot începe cu `lib`, dar nu este obligatoriu)
[//]: # (- legarea/link-uirea &#40;linking-ul?&#41; efectivă a bibliotecilor statice de care avem nevoie &#40;cu
 opțiunnea `-lnume_biblioteca` - este litera L mic&#41;)
[//]: # (- adăugarea bibliotecilor dinamice: trebuie să existe în directorul curent sau în `PATH`)

Observații:

[//]: # (- unele biblioteci sunt de tip header-only, deci nu sunt necesari decât pașii 1, 3 și 4
 &#40;sau doar 1 și 4 dacă adăugăm sursa în repo&#41;)
- unele biblioteci sunt gândite să fie legate doar static, altele doar dinamic, iar altele în ambele
feluri (adică au o parte cu fișiere statice și alta cu fișiere dinamice)
- de verificat că licențele bibliotecilor pe care le folosim sunt compatibile cu licența proiectului nostru

**Care este diferența dintre bibliotecile legate static și cele legate dinamic?**

Bibliotecile statice sunt necesare atunci când compilăm codul, ceea ce înseamnă că vor crește dimensiunea
executabilului. Bibliotecile dinamice sunt necesare numai atunci când rulăm programul.

### Biblioteci recomandate

În această secțiune, aș vrea să vă recomand doar biblioteci care sunt **portabile**.

- [SFML](https://www.sfml-dev.org/): grafică, sunete (posibil să trebuiască schimbat DLL-ul de OpenAL pe
Windows... sau nu)
- 🚧 secțiune incompletă
- [rlutil](https://github.com/tapio/rlutil) pentru text colorat și jocuri în consolă,
[rang](https://github.com/agauniyal/rang) pt text colorat/subliniat
- am mai reușit să folosesc [libpqxx](https://github.com/jtv/libpqxx),
[GLFW](https://www.glfw.org/download.html),
[SOIL](https://github.com/kbranigan/Simple-OpenGL-Image-Library) (nu sunt sigur dacă asta e),
[SOIL2](https://github.com/SpartanJ/SOIL2), [indicators](https://github.com/p-ranav/indicators) (bară de progres)
- la SIGIL nu mi-a mers sunetul (și are nevoie de un DLL din MSYS2)
- [portable-file-dialogs](https://github.com/samhocevar/portable-file-dialogs): pop-ups, notificări; e nevoie de
mici modificări pt a merge pe windows cu gcc
- [cpr](https://github.com/whoshuu/cpr)
- json parsing:
  - [nlohmann/json](https://github.com/nlohmann/json) (am aflat de la
  [@MihaiVoinea](https://github.com/MihaiVoinea))
  - dacă vreți performanță, recomand [OjC](https://github.com/ohler55/ojc)
- crypto: [digestpp](https://github.com/kerukuro/digestpp) pt hashing parole
- date calendaristice: [date](https://github.com/HowardHinnant/date)

De încercat:
- Boost (??)
- [raylib-cpp](https://github.com/RobLoach/raylib-cpp) (recomandare din partea
[@meemknight](https://github.com/meemknight))
- [magic_enum](https://github.com/Neargye/magic_enum)

De unde mai puteți găsi biblioteci: căutați awesome c++, de exemplu [aici](https://github.com/fffaraz/awesome-cpp)

### Alte sfaturi

Pentru fișiere mari (minim câțiva MB), este recomandat să folosiți [`git-lfs`](https://git-lfs.github.com/).
Astfel, dacă le modificați, pe repository-ul local veți avea o singură copie a acestor fișiere mari, însă
istoricul complet al modificărilor se va afla pe repository-ul remote (desigur, trebuie ca acesta să știe de lfs).

## Resurse recomandate
- [cppreference.com](https://en.cppreference.com/w/cpp)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- [ISO C++ FAQ](https://isocpp.org/faq/)
- [StackOverflow](https://stackoverflow.com/questions/tagged/cpp?tab=Votes)
