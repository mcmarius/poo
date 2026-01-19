### Variantă de rezolvare colocviu ianuarie 2023

În continuare, prezentăm subiectul din ianuarie 2023 împreună cu variante posibile de rezolvare.

Reiterăm faptul că nu există o singură soluție corectă.

> După 2 ani de online, Facultatea de Matematică și Informatică este în plină activitate și pe timp de iarnă.
> Deși până acum nu prea au fost ninsori, nu știm ce ne rezervă viitorul.
> Dornici să vină la facultate indiferent de condițiile meteorologice, studenții au proiectat în AutoCAD®
> mai multe unelte de deszăpezire.
>
> Studenții s-au grupat pe echipe într-o competiție ca să afle ce combinație de unelte dă zăpada mai bine.
>
> Toate uneltele de deszăpezire au următoarele caracteristici comune: serie (string de lungime minim 3),
> număr de serie (număr natural nenul) și culoare.
>
> • Seria și numărul sunt fixe și identifică în mod unic o unealtă.
> Culoarea se alege dintr-o paletă prestabilită și trebuie validată (de program sau de compilator).
>
> • Fiecare unealtă are un timp de deszăpezire și un consum de energie determinate prin formule specifice.
> Acestea depind de suprafața curățată dată ca parametru.
>
> Există 3 tipuri de unelte: lopeți electrice, drone și unelte prototip.

În acest punct, identificăm cel puțin o clasă de bază `Unealta` cu următoarele caracteristici:

- seria și culoarea trebuie validate: putem folosi enumerări și/sau excepții, iar pentru lista de culori prestabilite
  variabile constante statice
- funcții virtuale pure pentru deszăpezire și consum de energie

Dacă aceasta nu era o ierarhie de clase, tipul putea fi reținut printr-o enumerare.

> Pentru lopețile electrice se cunosc suprafața fărașului și capacitatea bateriei.
>
> • Timp lopată = `suprafața curățată / std::sqrt(suprafață făraș)`
>
> • Consum energie lopată = `std::pow(suprafața curățată, 2) * capacitate baterie`

Prin urmare, aceasta va fi prima clasă derivată. Ce avem de implementat într-o derivată?

- toate funcțiile virtuale pure din bază (altfel nu putem instanția obiectul)
- funcția virtuală `clone` dacă obiectele trebuie copiate prin pointer de bază
- opțional (depinde de subiect), funcție virtuală de afișare, pretext pentru a arăta ideea de interfață non-virtuală

Nu uitați ce implică faptul că aveți cel puțin o funcție virtuală.

> Dronele au o altitudine maximă și un număr de motoare.
> În plus, dronele au o funcționalitate specială de dat jos țurțuri.
> Există o mică probabilitate ca operația să eșueze (folosiți o funcție de numere aleatoare și alegeți o probabilitate).
>
> • Timp dronă = `std::log(suprafața curățată) * std::tanh(altitudine maximă)`
>
> • Consum energie dronă = `suprafața curățată * std::pow(număr motoare, 3)`

Aceasta ar fi cea de-a doua clasă derivată. Spre deosebire de prima derivată, aici trebuie să
implementăm și o funcție care nu se regăsește în clasa de bază, pretext pentru a face un `dynamic_cast`.
Totodată, aici ar fi un alt pretext de a folosi excepții deoarece operația poate să eșueze.

Mai există încă o alegere care ar trebui făcută, deși într-adevăr nu este tocmai clar din enunț.
Pentru partea de dat jos țurțuri, fie operația va fi integrată în calculul timpului și al consumului,
fie acest aspect trebuie rezolvat la nivel de competiție (vezi mai jos).

> Uneltele prototip au 2 atribute numerice. Toate echipele folosesc aceleași formule pentru prototipuri.
> Aveți de implementat aceste formule la liberă alegere.

Această clasă putea fi folosită în cel puțin două moduri (care nu se exclud):

- moștenire (virtuală) multiplă
- utilizare de șabloane (clasă `template`)

Ar trebui implementate toate funcțiile virtuale, inclusiv `clone` și cea de afișare.

> Fiecare echipă are un nume, un motto și mai multe unelte (se pot repeta). Două echipe pot avea aceleași unelte, însă
> pot fi calibrate cu alți parametri.

Se specifică faptul că două echipe pot pleca de la o aceeași configurație, deci avem de implementat constructor de
copiere și implicit operator=.

Din moment ce fiecare echipă va avea o colecție de pointeri de unelte
(pointeri pentru că altfel nu pot fi apelate funcțiile virtuale),
trebuie să redefinim cc/op= definite de compilator pentru ca aceste copieri să funcționeze corect.

- în constructorul de copiere vom apela `clone` pentru unelte
- în operator= facem cu copy&swap

> Echipele se înscriu într-o competiție unică și sunt clasificate pe 2 categorii: timp minim de deszăpezire și consum
> minim de energie.

Competiție unică, deci clasă singleton. Clasa de prototip poate fi de asemenea singleton, iar singleton-ul poate fi
implementat ca CRTP.
Desigur, trebuie să mai și aibă sens ce facem, de exemplu
clasa de unealtă prototip ar trebui parametrizată și prin echipă în acest caz (de exemplu cu numele echipei - template
pe valori).

Sunt două criterii de clasificare deoarece formulele sunt concepute în așa fel încât
să nu existe o singură configurație optimă pentru ambele criterii (sunt complementare).

Întrucât o echipă are `n` unelte, asta înseamnă că o unealtă ar avea de curățat `1/n` din suprafață, nu toată suprafața.

> Implementați clasificările echipelor și propuneți formule pentru uneltele prototip.
> Pentru cele 2 categorii din competiție (timp minim și consum minim),
> se afișează toate informațiile despre fiecare echipă și totalul la nivel de echipă.

Trebuie folosită sortarea predefinită `std::sort` din `<algorithm>`, cel mai simplu cu o
funcție lambda de comparare.

> Pentru punctaj maxim, toate clasele și funcțiile trebuie folosite direct/indirect din `main`.
> Se permit devieri minimale de la subiect dacă se consideră mai natural astfel.

Nu se specifică nicăieri că ar trebui meniu interactiv.

Pentru acest subiect a fost eliminată această cerință în ideea să nu pierdeți timp să
rulați codul și să faceți validări de input de citiri pentru că asta nu evaluează deloc
cunoștințe de programare orientată pe obiecte.

De asemenea, citirea de la tastatură înseamnă că ne puneți pe noi să vă testăm codul
în loc să aveți exemple concrete de apel și de construire a obiectelor în `main`.
