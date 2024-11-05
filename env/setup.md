# Configurarea proiectului

Primul pas: creare cont de GitHub (dacă nu avem deja): https://github.com/signup

Pasul următor: crearea unui repository. Recomand să utilizați
[repository-ul template](https://github.com/mcmarius/oop-template),
deoarece are configurat tot ce veți avea nevoie.

![](img/setup_p0_create_repo.png)

Dacă dorim să folosim biblioteci externe, selectăm "Include all branches".
Pentru detalii, [vezi mai jos](#configurare-biblioteci-externe).

Introducem un nume și eventual o descriere.

Dacă selectați vizibilitatea proiectului privată, aveți cel mult 2000 de minute pe lună pentru
partea de CI (compilat/rulat/memory leaks), deci trebuie să vă pese mai mult să nu ruleze la infinit.

<sub>O rulare (un push de commit(s)) înseamnă cel mult 10 minute: 5 workflows rulează
programul vostru, ceea ce înseamnă 150 de minute (`30*1 + 10*2 + 10*10`, detalii
[aici](https://docs.github.com/en/billing/managing-billing-for-github-actions/about-billing-for-github-actions#included-storage-and-minutes)).
După vreo 13 commit-uri ați consumat tot pe luna respectivă.</sub>

**Indiferent de vizibilitatea proiectului, trebuie să rezolvați _toate_ erorile!**

![](img/setup_p0_create_repo_details.png)

După ce apăsăm pe "Create repository", avem 2 opțiuni:

- dacă nu dorim să folosim biblioteci externe, mergem direct la [acest pas](#configurare-proiect-din-ide)
- pentru biblioteci externe, este mai simplu de configurat din browser: vezi în continuare.

## Configurare biblioteci externe

**UPDATE 13.03.2024!**

Se pare că GitHub face modificări majore fix după începutul fiecărui semestru 🙃

Pentru conturile noi de GitHub, aparent este posibil să nu vă mai apară bifa de "Include all branches" din screenshot-ul de mai sus.
În acest caz, trebuie să vă clonați proiectul local și să folosiți următoarele comenzi pentru a include acel branch, după care
puteți urma instrucțiunile de mai jos în continuare.

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
git checkout --orphan common-libs origin2/common-libs
# facem commit cu fișierele preluate de pe acel branch
git commit -m "Initial commit"
git push origin common-libs
```

Pentru branch-ul sfml:
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
git checkout --orphan sfml origin2/sfml
# facem commit cu fișierele preluate de pe acel branch
git commit -m "Initial commit"
git push origin sfml
```

Folosim opțiunea `--orphan` pentru a nu căra tot istoricul de pe repo-ul template.

End update 13.03.2024 (actualizat 05.11.2024, 07.04.2024).

---

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

Dacă avem fișiere pentru date de intrare, este necesar să configurăm directorul de lucru
(working directory).

Din dreapta sus dăm pe "Edit Configurations..." (sau din meniu -> Run -> "Edit Configurations..."):

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

Pentru continuare, după ce e gata o parte din temă, vezi
[comenzile uzuale de git](./#comenzi-uzuale-de-git).

# Gata! 🎉

