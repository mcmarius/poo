# Configurarea mediului de lucru

### ⚠ Puneți cât mai multe întrebări! Nu există întrebări greșite.
#### Semnalați orice fel de greșeli găsiți!

Avem de configurat următoarele programe:
- un compilator
- un editor/IDE
- Git ca sistem de versionare a codului

Compilatorul și editorul sunt în majoritatea situațiilor programe **complet independente**.
Editorul este folosit ca să scriem cod, compilatorul este folosit ca să transforme codul
într-un fișier binar (executabil sau bibliotecă).

Exemple de compilatoare: GCC (GNU Compiler Collection), LLVM Clang, Apple Clang,
MSVC (Microsoft Visual C++), Intel C++ Compiler, NVCC (Nvidia CUDA Compiler) etc.

Exemple de editoare/IDE: Code::Blocks, CLion, VSCode, vim, emacs, nano, gedit, XCode,
Visual Studio, Notepad etc.

---

**Atenție!**

Code::Blocks **nu** este compilator.
MinGW **nu** este compilator.
MinGW-w64 **nu** este compilator.
CLion **nu** este compilator.
VSCode **nu** este compilator.
Visual Studio **nu** este compilator.
XCode **nu** este compilator.
C++ **nu** este compilator (C++ este un limbaj).
C++14 **nu** este compilator (C++14 este o versiune a limbajului C++).

---

Am văzut confuzia asta de prea multe ori și recunosc că este și greșeala mea că nu am ilustrat
mai clar diferența și nu am fost prea insistent. Poate cu explicațiile de aici se va remedia confuzia.
Sau măcar să vă amintiți imaginea de mai jos când aveți dileme
([sursa](https://www.ranzey.com/generators/bart/index.html)).

![](img/ce_nu_este_compilator.png)

**Ce este MinGW?**

MinGW este o colecție de pachete software din Linux portate pe Windows pentru a folosi apelurile native
ale sistemului de operare (Windows API). Printre pachetele software incluse se regăsește și o portare
a colecției de compilatoare GCC.

**Ce este MinGW-w64?**

MinGW-w64 este o continuare a proiectului MinGW pentru a funcționa pe variante de Windows pe 64 de biți
și pentru a aduce tot felul de îmbunătățiri. MinGW pare un proiect abandonat.

**De ce nu e corect să spunem că MinGW/MinGW-w64 este un compilator?**

Dacă vrem să specificăm versiunea compilatorului, versiunea de MinGW este irelevantă pentru că putem
avea versiuni de compilator diferite cu aceeași versiune de MinGW: puteți vedea pe WinLibs că avem
5 versiuni majore de GCC (de la 8 la 12) care folosesc aceeași versiune de MinGW-w64 (9.0.0).


## Configurarea compilatorului

Indiferent de sistemul de operare, vă recomand să folosiți versiuni cât mai noi de compilator, ideal
GCC minim versiunea 10 sau LLVM Clang minim versiunea 12.

#### Windows

Pe Windows, vă recomand să folosiți GCC/Clang furnizate de [WinLibs](https://winlibs.com). Nu recomand
compilatorul celor de la Microsoft dacă nu îl aveți deja instalat pentru că ocupă foarte mult spațiu
pe disc. Celelalte variante cu MSYS2 și/sau Cygwin mi se par prea complicate pentru ce avem nevoie
la acest laborator.

Ar fi de preferat să dezarhivați arhiva într-un loc unde calea absolută nu conține spații.

Întrucât compilatorul de pe WinLibs este doar un simplu folder (nu se instalează), ar fi bine să
adăugăm compilatorul în variabila de mediu numită `%PATH%`.

🚧

#### Linux

Dacă aveți deja instalată o versiune relativ recentă de compilator, puteți sări momentan peste acest pas.

Pe Ubuntu (sau alte derivate din Debian), ar trebui să fie suficiente următoarele instrucțiuni
(pentru GCC 11):
```
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install gcc-11 g++-11
```

Ar trebui să găsiți instrucțiuni asemănătoare pentru alte distribuții de Linux.

Compilatorul ar trebui să fie deja adăugat în cale (variabila `$PATH`).

#### macOS

Pe macOS ar trebui să aveți deja instalat Apple Clang. Dacă aveți nevoie de versiuni mai noi,
cred că cel mai ușor ar fi cu [`brew`](https://brew.sh).

Compilatorul ar trebui să fie deja adăugat în cale (cred că variabila se numește tot `$PATH`).

### Verificarea versiunii compilatorului

Indiferent de sistemul de operare, deschideți un terminal și introduceți comanda
`g++ --version` sau `clang++ --version` sau `g++-11 --version` etc. (după caz).

Exemple de terminal: Command Prompt/Powershell/Windows Terminal/Terminal/sh/bash/zsh.

Ar trebui să vă apară ceva de felul următor:

🚧

Dacă nu vă apare versiunea corespunzătoare, încercați să schimbați ordinea căilor către
compilatoare în `PATH`. Pentru a vedea unde se află compilatorul vechi, folosiți comanda
`where` sau `whereis`. Exemplu pe Windows:

🚧

## Configurarea editorului

Alegerea editorului/IDE-ului este complet subiectivă. La laborator nu le putem încerca pe toate.
Eu vă recomand [CLion](https://www.jetbrains.com/clion/download/) pentru că așa m-am obișnuit.
Pentru a primi licență gratuită, completați
[acest formular](https://www.jetbrains.com/shop/eform/students/) cu adresa instituțională
(`@s.unibuc.ro`).

Pasul următor este să vă configurați editorul pentru a folosi compilatorul configurat mai sus.

## Configurarea și utilizarea programului Git

### Instalare

Pentru Windows, cel mai simplu este să folosiți [Git for Windows](https://gitforwindows.org).
NU vă recomand să vă setați ca editor implicit `vim`. După pasul cu editorul puteți da next/next
până la sfârșit.

Pe Linux probabil e suficient cu `sudo apt install git` sau ceva asemănător.

Pe macOS, Git ar trebui să fie deja instalat.

La fel ca mai sus, verificați dintr-un terminal că programul este instalat corect cu `git --version`:

🚧

### Crearea unui repository remote

Dacă nu aveți deja cont, va trebui să vă creați unul. Cel mai la îndemână serviciu ar fi GitHub, însă
puteți folosi și alte servicii care lucrează cu repository-uri de git.

Pentru proiectul de POO, vă recomand să folosiți sau să vă inspirați din
[acest repository template](https://github.com/mcmarius/oop-template) (chiar dacă nu folosiți GitHub).
Apăsați pe butonul "Use this template". Dacă alegeți această variantă, puteți trece la pasul următor.

TODO: de adăugat vim, emacs, ninja, gcov la gitignore && de ordonat alfabetic

Pentru a crea un repository pe GitHub, folosim butonul ➕ din dreapta sus, apoi "New repository".
Pentru a putea folosi proiectul și local, ar fi bine să bifăm măcar una dintre opțiuni
(de exemplu cea de "Add a README file") pentru ca repository-ul nostru să aibă cel puțin un commit.
Dacă un avem măcar un commit, putem întâmpina diverse erori.

### Configurare inițială

La user puneți numele userului de GitHub. La email puteți pune
"your_github_username@users.noreply.github.com" dacă nu doriți ca adresa de email să fie publică.

```
git config --global user.name "Your Name"
git config --global user.email "your_email@example.com"
```

Setările globale sunt salvate în fișierul `.gitconfig` din
[folderul Home](https://en.wikipedia.org/wiki/Home_directory) al userului.
Setările la nivel de repository sunt în fișierul `config` din folderul `.git`. 

### Clonarea unui repository

Din browser, de pe pagina principală a repository-ului, apăsați pe butonul "Code", iar apoi copiați
URL-ul din tab-ul HTTPS:

🚧

```
git clone https://github.com/mcmarius/oop-template.git
```

Comanda `clone` face mai multe lucuri: inițializează un repository local, face legătura dintre
repository-ul local și cel remote (de pe GitHub) și aduce local conținutul de pe remote. Dacă
nu specificăm și alte opțiuni, vom prelua local tot istoricul modificărilor.

După aceasta, veți avea un folder cu numele repository-ului - `oop-template` pe exemplul de aici.
Dacă vă uitați la fișierele ascunse din acest folder, veți observa un folder `.git`. Aici își ține
programul Git toate fișierele de care are nevoie.

Așadar, un repository este un folder normal, dar care conține acest folder special `.git`.

### gitignore

Repository-ul template ar trebui să fie deja configurat cu un fișier `.gitignore`. Dacă ați pus bifa de
.gitignore când ați creat repository-ul, atunci aveți deja creat acest fișier.

Altfel, va trebui să creați fișierul cu ajutorul editorului sau din linia de comandă. Pe Windows, din
File Explorer trebuie creat ca `.gitignore.` deoarece trebuie păcălit să creadă că fișierul are și
nume, și extensie.

Vă recomand să vă uitați pe repo-ul template sau să folosiți
[gitignore.io](https://gitignore.io) pentru a completa fișierul `.gitignore`.

Ce rol are acest fișier?

Ne ajută să **nu** punem pe repository fișiere executabile, fișiere obiect, fișiere locale de
configurare ale editorului și alte fișiere care nu sunt de interes pentru altcineva care ar dori
să folosească repository-ul respectiv. De exemplu, executabilele nu sunt de interes deoarece se
schimbă la fiecare recompilare și sunt specifice unui anumit sistem de operare.

## Comenzi uzuale de Git

De cele mai multe ori, vom folosi `git` dintr-o interfață grafică. Totuși, este bine să avem o vagă
idee despre modul de utilizare din linia de comandă, deoarece interfețele grafice mai dau rateuri
și atunci tot din linia de comandă va trebui să remediem situația.

### **`git clone`**

Pentru explicații, vedeți mai sus. Exemple: 
- `git clone https://github.com/mcmarius/oop-template.git` clonează în folderul `oop-template`
- `git clone git@github.com:mcmarius/oop-template.git` clonează folosind SSH
- `git clone https://github.com/mcmarius/oop-template.git folder` clonează în folderul `folder`
- `git clone --depth 2 https://github.com/mcmarius/oop-template.git` ia doar ultimele 2 commit-uri

### **`git status`**

Una dintre cele mai utile comenzi. Arată informații despre starea curentă a repository-ului și ne
indică ce comenzi uzuale putem da.

Ce putem vedea?
- ce fișiere propunem să fie adăugate pentru următorul commit
- ce comandă putem da pentru a scoate fișiere din a fi adăugate la următorul commit
- ce fișiere urmărite de Git au fost modificate de la ultimul commit
- pe ce branch suntem
- dacă avem conflicte între fișiere
- dacă avem conflicte între commit-uri (local vs remote)
- dacă avem commit-uri locale și nu le-am transmis la repository-ul remote
- și nu numai

### **`git diff`**



### **`git add`**

### **`git diff --cached`** (sau `--staged`)

### **`git pull`**

### **`git commit`**

### **`git pull`**

### **`git push`**

### **`git fetch`**

### **`git tag`**

## Alte comenzi de interes

### **`git log`, `git show`**

### **`git stash`**

### **`git branch`, `git checkout`**

### gitconfig din nou

### Utilizarea SSH (opțional)

### `git remote`

### Git LFS (opțional)

### Din interfața grafică


