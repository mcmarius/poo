### Tema 3

Templates, design patterns. Urmează să adaug detalii.

Scopul acestei teme este utilizarea unor concepte mai avansate de OOP (design patterns) și a programării generice, dacă este posibil.

Exemple de design patterns care s-ar putea potrivi și care nu sunt foarte complicate:
- singleton
- builder
- factory
- proxy
- object pool



Moșteniri multiple și virtuale

C++ permite moșteniri multiple:
```c++
class plantă {};
class eco {}; // clasa abstracta
class plantă_eco : public plantă, public eco {};
```

Un comportament care poate nu este de dorit apare atunci când clasele pe care le moștenim au o clasă de bază comună.

Atributele din clasa de bază vor apărea de mai multe ori în clasa derivată:
```c++
class ecran {};
class dispozitiv {
    ecran e;
};

class tabletă : public dispozitiv {
    // moștenește ecranul
};

class laptop : public {
    // moștenește ecranul
};

class two_in_one : public tabletă, public laptop {
    // moștenește două ecrane!
    // acestea sunt tabletă::ecran și laptop::ecran
};
```

Soluția este să folosim moștenire virtuală:
```c++
class ecran {};
class dispozitiv {
    ecran e;
};

class tabletă : virtual public dispozitiv {
    // moștenește ecranul
};

class laptop : virtual public {
    // moștenește ecranul
};

class two_in_one : public tabletă, public laptop {
    // moștenește un singur ecran!
};
```

Putem face moștenirea virtuală și "la sfârșit" (în clasa `two_in_one`), însă nu e recomandat (de adăugat de ce).



Templates
- funcții template
- clase template
- supraîncărcare operatori friend în clase template
