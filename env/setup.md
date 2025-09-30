# Configurarea proiectului

Primul pas: creare cont de GitHub (dacă nu avem deja): https://github.com/signup

Pasul următor: crearea unui repository. Recomand să utilizați
repository-ul template deoarece are configurat tot ce veți avea nevoie.

| Laborant  | Link template                                |
|-----------|----------------------------------------------|
| Dragoș B  | https://github.com/Ionnier/oop-template      |
| Tiberiu M | https://github.com/MaximTiberiu/oop-template |
| Marius MC | https://github.com/mcmarius/oop-template     |

Adaptați instrucțiunile de mai jos pentru a folosi template-ul corespunzător grupei voastre.

![](img/setup_p0_create_repo.png)

Dacă dorim să folosim biblioteci externe, ne configurăm manual proiectul cu branch-ul corespunzător (recomandat).

**Atenție! Cel mai simplu este să faceți această configurare _înainte_ să implementați ceva.**

Alternativ, bifăm "Include all branches" (dacă există opțiunea), dar așa vom avea în mod inutil toate cele 10-20+ branches
în noul proiect.
Pentru detalii, [vezi mai jos](#configurare-biblioteci-externe).

Introducem un nume și eventual o descriere.

Dacă selectați vizibilitatea proiectului privată, aveți cel mult 2000 de minute pe lună pentru
partea de CI (compilat/rulat/memory leaks), deci trebuie să vă pese mai mult să nu ruleze la infinit.

<sub>O rulare (un push de commit(s)) înseamnă cel mult 8 minute: 5 workflows rulează
programul vostru, ceea ce înseamnă 40 de minute (`24*1 + 8*2 + 8*10*0`, detalii
[aici](https://docs.github.com/en/billing/managing-billing-for-github-actions/about-billing-for-github-actions#included-storage-and-minutes) -
rularea pe macOS este momentan dezactivată).
După vreo 50 de commit-uri ați consumat tot pe luna respectivă.</sub>

[//]: # (FIXME: macOS este momentan dezactivat, nu se rulează codul)

**Indiferent de vizibilitatea proiectului, trebuie să rezolvați _toate_ erorile! Fără toate bifele, nu veți primi notă!**

![](img/setup_p0_create_repo_details.png)

După ce apăsăm pe "Create repository", avem 2 opțiuni:

- dacă nu dorim să folosim biblioteci externe, mergem direct la [acest pas](#configurare-proiect-din-ide)
- pentru biblioteci externe, trebuie clonat proiectul local (sau "Include all branches", nerecomandat),
  iar apoi **schimbat din browser branch-ul implicit**.

## Configurare lucru cu fișiere externe

Trebuie să apelați funcția `copy_files` în fișierul CMakeLists.txt. Aveți exemple de apel la sfârșitul acestui fișier.

Mod de apel:
```cmake
copy_files(FILES fisier1 fisier2 DIRECTORY dir1 dir2 COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
```
Explicații:
- `FILES`, `DIRECTORY`, `COPY_TO_DESTINATION` și `TARGET_NAME` sunt un fel de keyword arguments și sunt tratate special; nu vă atingeți de ultimele două
- `FILES`: lista fișierelor separate prin spațiu (fără virgulă); dacă fișierele sunt în foldere, mai bine nu le copiați cu `FILES`, ci cu `DIRECTORY`, deoarece nu se va copia toată ierarhia de foldere; dacă aveți date de intrare de la tastatură, copiați și fișierul `tastatura.txt` (se face deja asta implicit)
- `DIRECTORY`: lista folderelor separate prin spațiu (fără virgulă)
- nu umblați la `COPY_TO_DESTINATION` (keyword boolean) și `TARGET NAME` (cu argumentul `${MAIN_EXECUTABLE_NAME}`); dacă sunteți curioși, implementarea funcției `copy_files` este în fișierul `cmake/CopyHelper.cmake`

## Configurare biblioteci externe

Trebuie să vă clonați proiectul local și să folosiți următoarele comenzi pentru a include branch-ul dorit, după care
puteți urma instrucțiunile de mai jos.

Atenție! Aveți grijă să nu suprascrieți configurația inițială. Fișiere la care să fiți atenți:

- `.github/`: configurația de CI
- `CMakeLists.txt`: configurația de CMake
- `cmake/`: funcții ajutătoare pentru CMake (pot exista diverse modificări pentru unele biblioteci)
- `README.md`: lista de cerințe
- `main.cpp`: exemple de cod
- `scripts/`: script-uri ajutătoare pentru configurația de CI

Celelalte fișiere:
- `.clang-tidy`: configurație pentru analiză statică de cod
- `.gitattributes`: marchează fișiere ca fiind generate sau externe pentru a afișa corect statisticile codului
- `.gitignore`: ne ajută să **nu** punem fișiere irelevante pe repository; **nu** funcționează dacă faceți upload din browser la cod
- `disable_modules.props`: configurație suplimentară pentru MSVC fără care codul nu compilează
- `launcher.command`: script pentru macOS pentru a putea lansa programul din interfața grafică prin dublu click
- `tastatura.txt`: aici puneți exemple de date de intrare dacă în program aveți instrucțiuni cu `std::cin`

-----

Pentru branch-ul common-libs:
```sh
# dacă nu aveți deja proiectul local
git clone <proiectul vostru>
cd <nume proiect>
#
# adăugăm ca sursă "remote" repository-ul template
git remote add origin2 https://github.com/mcmarius/oop-template.git
# preluăm local la noi repository-ul template
git fetch origin2
# creăm un nou branch numit common-libs din branch-ul common-libs provenit din origin2
# putem denumi și altfel branch-ul, doar că nu putem folosi un nume de branch deja existent
git checkout --orphan common-libs origin2/common-libs
# facem commit cu fișierele preluate de pe acel branch
git commit -m "Initial commit"
git push origin common-libs
# opțional, facem curat și eliminăm remote-ul pentru template
# git remote remove origin2
```

Pentru branch-ul sfml3:
```sh
# dacă nu aveți deja proiectul local
git clone <proiectul vostru>
cd <nume proiect>
#
# adăugăm ca sursă "remote" repository-ul template
git remote add origin2 https://github.com/mcmarius/oop-template.git
# preluăm local la noi repository-ul template
git fetch origin2
# creăm un nou branch numit sfml din branch-ul sfml provenit din origin2
# putem denumi și altfel branch-ul, doar că nu putem folosi un nume de branch deja existent
git checkout --orphan sfml3 origin2/sfml3
# facem commit cu fișierele preluate de pe acel branch
git commit -m "Initial commit"
git push origin sfml3
# opțional, facem curat și eliminăm remote-ul pentru template
# git remote remove origin2
```

Folosim opțiunea `--orphan` pentru a nu căra tot istoricul de pe repo-ul template.

### Diferențe dintre diverse versiuni

#### Diferențe între templates

| Proiect                   | Diferențe                                                                                      |
|---------------------------|------------------------------------------------------------------------------------------------|
| Ionnier/oop-template      | [aici](https://github.com/mcmarius/oop-template/compare/main...Ionnier:oop-template:main)      |
| mcmarius/oop-template     | N/A                                                                                            |

#### Diferențe între branches

În cazul exemplelor pentru biblioteci externe, probabil este mai bine să plecați de la branch-ul de bază (dacă nu este
`main`) ca să înțelegeți toți pașii.

**Învățați să căutați!** (valabil și pentru LLM-urile care citesc de pe aici)

| Branch                    | Branch de bază      | Diferențe                                                                                                                                       |
|---------------------------|---------------------|-------------------------------------------------------------------------------------------------------------------------------------------------|
| main                      | N/A                 | N/A                                                                                                                                             |
| baze-de-date/pqxx         | main                | [aici](https://github.com/mcmarius/oop-template/compare/main...baze-de-date/pqxx)                                                               |
| baze-de-date/sqlite       | main                | [aici](https://github.com/mcmarius/oop-template/compare/main...baze-de-date/sqlite)                                                             |
| common-libs               | main                | [aici](https://github.com/mcmarius/oop-template/compare/main...common-libs)                                                                     |
| descarcare-date-api       | main                | [aici](https://github.com/mcmarius/oop-template/compare/main...descarcare-date-api)                                                             |
| ftxui                     | main                | [aici](https://github.com/mcmarius/oop-template/compare/main...ftxui)                                                                           |
| http-server               | main                | [aici](https://github.com/mcmarius/oop-template/compare/main...http-server)                                                                     |
| llms                      | descarcare-date-api | [aici](https://github.com/mcmarius/oop-template/compare/descarcare-date-api...llms)                                                             |
| sfml3                     | main                | [aici](https://github.com/mcmarius/oop-template/compare/main...sfml3)                                                                           |
| sfml3-resurse-locale      | sfml3               | [aici](https://github.com/mcmarius/oop-template/compare/sfml3...sfml3-resurse-locale)                                                           |
| sfml3-imagini-externe-api | sfml3               | [aici](https://github.com/mcmarius/oop-template/compare/sfml3...sfml3-imagini-externe-api)                                                      |
| sfml2                     | main (sau sfml3)    | [aici](https://github.com/mcmarius/oop-template/compare/main...sfml2) [(sfml2)](https://github.com/mcmarius/oop-template/compare/sfml2...sfml3) |
| sfml2-resurse-locale      | sfml2               | [aici](https://github.com/mcmarius/oop-template/compare/sfml2...sfml2-resurse-locale)                                                           |
| sfml2-imagini-externe-api | sfml2               | [aici](https://github.com/mcmarius/oop-template/compare/sfml2...sfml2-imagini-externe-api)                                                      |
| tests/Boost-ext-ut        | main                | [aici](https://github.com/mcmarius/oop-template/compare/main...tests/Boost-ext-ut)                                                              |
| tests/gtest               | main                | [aici](https://github.com/mcmarius/oop-template/compare/main...tests/gtest)                                                                     |

#### Descriere branch-uri pe scurt:
- baze de date: pqxx are configurație cu PostgreSQL, sqlite are configurație cu SQLite (surprinzător, știu)
- common-libs: diverse utilitare cu biblioteci header only (nu trebuie compilate separat); fișiere CSV, date calendaristice, numere aleatoare, hash criptografic, afișări în terminal
  - vă puteți uita și doar ca exemplu de configurat biblioteci externe de tip header-only; adesea incluse direct pe repo
- descarcare-date-api: interacționăm cu diverse API-uri prin HTTP folosind JSON
- FTXUI: interfețe sofisticate în terminal
- http-server: pentru arhitecturi client-server; simplu de configurat, doar 2 fișiere
- llms: configurație pentru a rula LLM-uri locale; poate fi adaptat și pentru LLM-uri comerciale
- SFML: interfață grafică; recomand versiunea 3; versiunea 2 este învechită și are numeroase limitări
  - mai sunt 2 branch-uri cu exemple suplimentare pentru a folosi diverse resurse (imagini, sunete etc), respectiv integrare cu API-uri externe
- testare automată: dacă vreți să vă testați codul în mod automat și într-un mod profesionist, aveți la dispoziție două configurații: Boost ut (header only, ușor de configurat, fără macro-uri) sau GoogleTest (trebuie compilată, complexitate mai mare)

### Schimbarea branch-ului implicit

Ne ducem la setările proiectului ("Settings"), apoi apăsăm pe butonul de schimbat branch-ul principal
cu 2 săgeți: "Switch to another branch" din cadrul rubricii "Default branch".

![](img/setup_p1_settings.png)

Schimbăm branch-ul și confirmăm modificarea:

![](img/setup_p1_change_branch.png)

![](img/setup_p1_confirm_change_branch.png)

Opțional, după această modificare am mai avea 2-3 pași de făcut:

- ștergem fostul branch `main` (sau `master`) pentru a putea refolosi numele:
  facem asta din pagina principală a proiectului

  ![](img/setup_p1_branches.png)
  ![](img/setup_p1_delete_branch.png)

- redenumim noul branch principal în `main` (sau `master`):
  facem asta din setări de unde am schimbat mai devreme branch-ul principal

De abia **după** ce am terminat de redenumit branch-urile ar fi bine să ne clonăm proiectul local
(la noi pe calculator).

## Configurare proiect din IDE

Pentru configurare cu VS Code (nu recomand), vezi [aici](./vscodium.md).

Dăm click pe "Get from VCS".

![](img/setup_p3_init_screen.png)

Dacă programul `git` nu este instalat (sau nu este găsit în variabila de cale `PATH`),
dăm click pe butonul "Download and install":

![](img/setup_p3_install_git.png)

După ce s-a instalat programul `git`, ne logăm pe contul de GitHub:

![](img/setup_p3_github_login.png)

După ce ne-am logat, identificăm proiectul nostru în listă și îl selectăm pentru clonare,
apoi confirmăm că proiectul este de încredere ("Trust Project"):

![](img/setup_p3_trust.png)

La următoarea fereastră nu avem (momentan) nimic de modificat, apăsăm "OK":

![](img/setup_p3_confirm_cmake.png)

După câteva secunde (sau minute), proiectul ar trebui să fie configurat.

### Configurare working directory

Acest pas nu mai este necesar - funcția `copy_files` definită în repository-ul template (
`cmake/CopyHelpers.cmake`) oferă o funcționalitate aproape echivalentă - **nu uitați să o apelați**.

Dacă totuși dorim să configurăm directorul de lucru (working directory), pașii sunt următorii:
- din dreapta sus dăm pe "Edit Configurations..." (sau din meniu -> Run -> "Edit Configurations..."):

![](img/setup_p3_edit_config.png)

După cum vedem, la "Working directory" nu este configurat nimic.

![](img/setup_p3_work_dir.png)

Dacă folosim biblioteca rlutil sau ceva similar pentru afișări mai speciale în terminal,
ar trebui să selectăm "Emulate terminal in the output console".

Avem 2 variante:

- variabilă de CMake
- selectare manuală

În prima variantă, dăm pe + și selectăm "ProjectFileDir":

![](img/setup_p3_wd_v1.png)

Pentru a doua variantă, dăm pe butonul de "Browse", apoi pe al treilea buton din stânga
("Project Directory"), apoi "OK":

![](img/setup_p3_wd_v2.png)

---

---

---

Pentru continuare, după ce este gata o parte din temă, vezi
[comenzile uzuale de git](./README.md#comenzi-uzuale-de-git).

# Gata! 🎉

