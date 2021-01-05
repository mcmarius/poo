Câteva sfaturi pentru colocviu
- cel mai important este să trimiteți un cod care compilează
- dacă faceți cu citire de la tastatură, salvați-vă undeva într-un notepad/comentariu datele de intrare, pentru ca apoi să faceți doar "paste"
  (ca să câștigați timp să nu scrieți aceleași date de fiecare dată când testați programul)
  - verificați dacă merge acest truc înainte de colocviu, nu atunci pe loc; nici mie nu îmi merge din prima
- pe ce ar trebui să luați multe puncte ușor:
  - constructori de inițializare
  - moșteniri (virtuale multiple), funcții virtuale
  - excepții (cu moștenire din `std::exception`)
  - `operator<<`, `static_cast`
- folosiți `std::string` în loc de `char*`, folosiți `std::vector` în loc de `A *vec = new A[nr]` (și `delete[]`)

Shortcuts:
- <kbd>Shift</kbd>+<kbd>F6</kbd> redenumiri
- <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>V</kbd> extrage variabilă
- <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>M</kbd> extrage funcție
- <kbd>Alt</kbd>+<kbd>Insert</kbd> în interiorul clasei generează cod: constructor, destructor, getter/setter, `op<<`, `op==`, `op!=`, `op<`
- <kbd>Ctrl</kbd>+<kbd>O</kbd> override, suprascrie funcție virtuală
- <kbd>Ctrl</kbd>+<kbd>B</kbd> mergi la declarație
- <kbd>Ctl</kbd>+<kbd>D</kbd> duplică linia sau selecția
- <kbd>Ctrl</kbd>+<kbd>Space</kbd> auto-complete
- <kbd>Alt</kbd>+<kbd>Enter</kbd> auto-fix (nu oferă întotdeauna cea mai bună soluție!)
