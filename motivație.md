# Document în lucru

-----

# Câteva idei despre predare

Acest document se adresează celor care doresc să predea pe baza acestor materiale: atât profesori, cât și studenți care țin tutoriate.

Înainte de a porni la drum, trebuie să acceptăm următoarele:
- nu deținem adevărul absolut
- este posibil să persistăm în greșeli timp de mai mulți ani fără să ne dăm seama

În particular, sunt conștient că materialele de față prezintă numeroase limitări. De exemplu, nu am lucrat pe C++ în industrie, deci nu pot să afirm că știu care sunt cele mai bune practici din domeniu. Pe baza experienței de predare și a documentării pe cât posibil riguroase, am încercat să compensez aceste lipsuri.

Momentan (2025), nu am primit reclamații referitoare la corectitudinea informațiilor prezentate. Totuși, aceasta nu constituie automat și o garanție că informațiile sunt perfecte, corecte etc. Oricând pot exista greșeli.

Atunci când sunt semnalate anumite probleme, acestea ar mai trebui și remediate.

Documentarea trebuie făcută, pe cât posibil, din **surse primare**. Dacă avem pretenția ca studenții să învețe să fie riguroși și să dezvolte un mod de gândire critic, nu trebuie să ne limităm la primele rezultate ale motorului de căutare. Dacă folosim surse secundare, înseamnă că altcineva a făcut partea de gândire pentru noi.

Particularizare pentru C++, am folosit:
- cppreference - bazat pe standardele ISO cu mențiuni exacte din standarde: atunci când am avut dubii, am putut astfel consulta direct standardul ISO (da, chiar am făcut asta) (de fapt am consultat un draft, dar mai exact nu se poate în mod legal și gratuit)

În mod intenționat **nu** am folosit:
- cplusplus.com: se limitează la C++11 (ultima dată când am verificat, suntem în 2025) și **nu** oferă referințe de unde sunt preluate informațiile

Să nu ne mirăm astfel că studenții tratează superficial partea de documentare atunci când își redactează lucrările de licență/diplomă/disertație.

Pentru partea de OOP, m-am folosit de experiența din industrie (care nu este pe C++). Au fost de ajutor și articolele lui Herb Sutter (un individ care se ocupă de ISO C++ - poate fi considerat sursă primară). Din nefericire, aici este mai dificil să ofer trimiteri și la alte resurse, deoarece tot ce am găsit nu mi s-a părut de încredere.

Un alt aspect de care consider că trebuie ținut cont în mod obligatoriu este să ne intereseze întâi de toate asimilarea unor principii și paradigme general valabile, în detrimentul unor particularități la nivel de limbaj. Astfel, trebuie să rezistăm tentației de a intra în detalii inutile sau de a depinde prea mult de alte discipline (în particular - Structuri de Date).

## Câteva principii de bază

Planul de învățământ trebuie structurat în așa fel încât fiecare noțiune nou introdusă să depindă doar de noțiuni deja introduse:
- noțiunile trebuie ordonate **logic**
- nu trebuie introduse prea multe noțiuni **simultan**

O evaluare a planurilor de învățământ se poate face cu teoria grafurilor și analiza structurală a rețelelor rezultate.

Fiecare noțiune pe care o introducem trebuie făcută ca o demonstrație matematică:
- nu dorim să formăm papagali, ci persoane cu o gândire critică
- nu trebuie să se înțeleagă că ceva este adevărat doar pentru că "așa li s-a zis": absolut totul ar trebui contestat dacă argumentele nu sunt convingătoare (aici apare altă problemă, ce ne facem cu argumentele convingătoare _greșite_?)
- nu trebuie să încurajăm studenții spre misticism (i.e. "facem așa pentru că trebuie")
- nu trebuie încurajată mentalitatea de "mie îmi merge"

## Tema 1

### De ce programare orientată pe obiecte?

Trebuie vorbit un pic de istorie. Paradigma OOP este un mod (nu singurul) de a gestiona complexitatea. Așadar, ce ne interesează? Să învățăm studenții să facă abstractizări de nivel cât mai înalt.

### De ce nu structuri de date?

Dacă alegem calea "ușoară" de a prezenta exemple cu structuri de date, întâmpinăm două obstacole:
- trebuie implementate operații de nivel scăzut
- se pierde timp cu corectitudinea implementării: invers ar avea mai mult sens, adică utilizarea OOP la cursul de SD
  - structurile date ca exemple există deja în limbaj, nu văd rostul să inventăm roata _la acest curs_

### Primul progarm

Trebuie plecat de la minimul posibil: un fișier sursă gol. De multe ori uit să fac acest exemplu.

Următorul exemplu va fi o funcție `main` fără nimic. Astfel, nu avem nevoie de headers. Pare prea simplu? Nu, tot se poate discuta despre valori de retur și coduri de eroare.

### Nu trebuie luat nimic de bun de-a gata

Mai departe, am avea de prezentat "Hello world", ceea ce presupune afișări. Inevitabil vom folosi `<iostream>`.

De ce nu `using namespace std`?

Aceasta este o ocazie perfectă să le demonstrăm studenților de ce nu e bine să iei totul de-a gata și să înveți ca papagalul. În liceu li se spune "folosiți asta ca să scrieți mai puțin", fără să înțeleagă implicațiile.

Prin includerea oarbă a acestei instrucțiuni în aparență inofensive, obținem:
- misticism
- lipsă de gândire critică
- cultivarea de rele practici
