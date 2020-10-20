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
