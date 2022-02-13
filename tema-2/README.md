# Tema 2

### ⚠ Puneți cât mai multe întrebări! Nu există întrebări greșite.
#### Semnalați orice fel de greșeli găsiți!

### Moșteniri

### Funcții virtuale
#### Destructor
#### Constructori virtuali
#### Smart pointers
#### Dynamic cast

### Copy and swap

### Excepții
#### Motivație
#### Excepții predefinite
#### Ierarhie proprie

### Funcții și atribute statice

## Cerințe tema 2

Continuăm familiarizarea cu limbajul C++ (din nou) și învățăm alte concepte OOP de bază: moșteniri și excepții.

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
- implementarea a două funcționalități noi specifice temei; pot fi folosite funcții virtuale în acest scop

#### Termen limită
- săptămâna 7 (20 noiembrie/2 aprilie): progres parțial
- **săptămâna 8 (27 noiembrie/9 aprilie): tema 2 gata**
- săptămâna 9 (4 decembrie/16 aprilie): (eventuale) modificări în urma feedback-ului
