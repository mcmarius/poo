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

[//]: # (https://stackoverflow.com/questions/367633/what-are-all-the-common-undefined-behaviours-that-a-c-programmer-should-know-a)

[//]: # (https://stackoverflow.com/a/4183735)

```

    i = i++ * ++i;  // Undefined Behaviour
    i = ++i + i++;  // Undefined Behaviour
    i = ++i + ++i;  // Undefined Behaviour
    i = v[i++];     // Undefined Behaviour
    i = v[++i]:     // Well-defined Behavior
    i = i++ + 1;    // Undefined Behaviour
    i = ++i + 1;    // Well-defined Behaviour
    ++++i;          // Well-defined Behaviour
    f(i = -1, i = -1); // Undefined Behaviour (see below)

```

[//]: # (https://en.cppreference.com/w/cpp/language/ub)

[//]: # (http://www.pvv.org/~oma/UnspecifiedAndUndefined_ACCU_Apr2013.pdf)

[//]: # (https://blog.llvm.org/2011/05/what-every-c-programmer-should-know.html)

Altele:
- unele versiuni de compilator (GCC < 7) au bug-uri la (inițializarea cu acolade și) moșteniri multiple
  unde baza se apelează de mai multe ori
- TBA