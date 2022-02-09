
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

Totuși, în acele situații, nu am folosi polimorfism, deci tot nu avem un răspuns complet la întrebare.
