### Greșeli în subiecte de examen

Exemple de UB (undefined behavior - comportament nedefinit):
- ordinea apelării parametrilor unei funcții
  - mai nou posibil să fie doar comportament nespecificat, dar tot nu ar trebui dat
    ca subiect de examen
  - subiectele care cer afișarea ordinii constructorilor/destructorilor
- `++i = i++`; de găsit subiectul din 2016??
- sequence points și `op<<`; de căutat ce garanții oferă noile standarde de C++
- dereferențierea unei adrese aiurea nu afișează neapărat o valoare aiurea;
  poate cauza și segmentation fault; este tot UB
- TBA

Altele:
- unele versiuni de compilator (GCC < 7) au bug-uri la (`=default` și) moșteniri multiple
  unde baza se apelează de mai multe ori
- TBA