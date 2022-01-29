//
// Created by marius on 15/04/2016.
//
#include "Simulare.h"
#include "map_full_error.h"
#include "timeout_error.h"

Simulare::Simulare(int NrAgenti, int x, int y) : c(' ') {
    while(NrAgenti % 3)
        NrAgenti++;
    nt = n = NrAgenti;      // nt: nr notal de agenti vii; n: dimensiunea vectorului
    t = 0;
    ox = x;
    oy = y;      // t: "killing" time, cand ajunge la 3 se omoara un agent la intamplare
    v = new Agent *[n];
    // generarea pozitiilor initiale ale agentilor
    AgentPiatra *a;
    AgentFoarfeca *b;
    AgentHartie *c;
    Pozitie p, q;
    for(int i = 0; i + 2 < n; i += 3) {
        makeRandomXY(i, p, q);
        a = new AgentPiatra(p.x, p.y);
        v[i] = a;
        makeRandomXY(i, p, q);
        b = new AgentFoarfeca(p.x, p.y);
        v[i + 1] = b;
        makeRandomXY(i, p, q);
        c = new AgentHartie(p.x, p.y);
        v[i + 2] = c;
    }
    while(seRepeta(p, q))   // daca gaseste doi agenti pe aceeasi pozitie, schimba pozitia celui de-al doilea
        for(int i = 0; i < n; ++i) {       // in cazul in care nu s-a reusit la generarea initiala
            p = v[i]->getPozitie();         // teoretic nu intra in acest while
            for(int j = i + 1; j < n; ++j) {
                q = v[j]->getPozitie();
                while(p.x == q.x && p.y == q.y) {
                    p.x = rand() % ox + 1;
                    p.y = rand() % oy + 1;
                }
                v[j]->setPozitie(p.x, p.y);
            }
        }
    afisare();  // afiseaza configuratia initiala
}

void Simulare::makeRandomXY(int i, Pozitie &p, Pozitie &q) {
    p.x = rand() % ox + 1;
    p.y = rand() % oy + 1;
    for(int j = 0; j < i; ++j) {
        q = v[j]->getPozitie();
        while(p.x == q.x && p.y == q.y) {      // daca se repeta, incearca alte coordonate
            p.x = rand() % ox + 1;
            p.y = rand() % oy + 1;
        }
    }
}

int Simulare::simuleaza(int flag) {
    std::cout << '\n';
    if(!nt) {
        std::cout << "Nu mai exista agenti!!!\n";
        return 0;
    }
    n2 = nt;
    t++;   // n2: numarul de agenti inaintea unei etape
    int i, j, k;
    Pozitie p, q, r;
    for(i = 0; i < n; ++i) {
        p = v[i]->getPozitie();
        if(p.x && p.y) {
            do {
                v[i]->avanseaza();
                q = v[i]->getPozitie();
                q.x %= ox;
                //if(!q.x)
                q.x++;
                q.y %= oy;
                //if(!q.y)
                q.y++;
            } while(p.x == q.x && p.y == q.y);     // fiecare agent avanseaza pana cand nu mai e pe pozitia initiala
//            if(v[i]->nu_a_gasit_loc())
//                throw map_full_error((std::string &) "harta plina");
            v[i]->setPozitie(q.x, q.y);
            for(j = 0; j < n; ++j) {
                r = v[j]->getPozitie();
                if(nt && q.x == r.x && q.y == r.y && i != j) {     // daca mai sunt agenti,
                    k = v[i]->confrunta(v[j]->getTip());        // daca sunt pe aceeasi pozitie, se confrunta;
                    if(k) {                            // i!=j pentru ca un agent nu se confrunta cu el insusi
                        v[j]->setPozitie(0, 0);
                        nt--;
                        t = 0;    // al doilea agent pierde
                        if(flag >= 2)               // a avut loc o confruntare, deci t se reseteaza
                            std::cout << '(' << p.x << ", " << p.y << ") il invinge pe ("
                            << r.x << ", " << r.y << ")\n";
                    }
                    else {
                        v[i]->setPozitie(0, 0);
                        nt--;
                        t = 0;    // al doilea agent e mai tare, se apara
                        if(flag >= 3)           // primul agent pierde
                            std::cout << '(' << p.x << ", " << p.y << ") este invins de ("
                            << r.x << ", " << r.y << ")\n";
                    }
                    break;      // fiecare agent sta in alta parte, deci nu are rost sa continue
                }
            }
            if(flag >= 4)
                std::cout << '(' << p.x << ", " << p.y << ") -> ("
                << q.x << ", " << q.y << ")\n";
        }
    }
    if(t % 3 == 0 && nt == n2 && nt) {        // nu a avut loc nicio confruntare 3 runde consecutive
        int rnd;        // si mai sunt agenti, iar numarul final e egal cu cel initial
        do {
            rnd = rand() % n;
            p = v[rnd]->getPozitie();   // se ia un agent care nu a fost deja eliminat
            throw timeout_error((std::string &) "nu s-a intamplat nimic timp de mai multe runde");
        } while(!p.x);      // e suficient ca o coordonata sa (nu) fie 0
        v[rnd]->setPozitie(0, 0);
        nt--;
        std::cout << "Un agent a pierit din motive necunoscute\n";
    }
    if(!nt) {
        std::cout << "Nu mai exista agenti!\n";
        return 0;
    }
    afisare();
    return nt;
}

void Simulare::afisare() {
    while(!isSorted())
        bsort();
    int i, j, k, x, y, o = nt;      // o: agenti care mai trebuie afisati; i: parcurge vectorul de agenti
    for(i = 0; i <= ox; i++)
        std::cout << "_";
    i = 0;
    x = v[i]->getPozitie().x;       // aflu coordonatele primului agent
    y = v[i]->getPozitie().y;
    for(k = oy; k >= 1; --k) {
        std::cout << "\n|";
        for(j = 1; j <= ox; ++j) {
            while(o && !x) {       // sar peste agentii disparuti
                i++;
                if(i < n) {
                    x = v[i]->getPozitie().x;
                    y = v[i]->getPozitie().y;
                }
            }
            if(o && y == k && x == j) {
                std::cout << v[i]->getTip();
                o--;
                i++;
                if(i < n) {
                    x = v[i]->getPozitie().x;
                    y = v[i]->getPozitie().y;
                }
            }
            else
                std::cout << c;
        }
        std::cout << "|";
    }
    if(o)       // nu au fost afisati toti agentii
        std::cout << "A aparut o eroare\n";
    std::cout << '\n';
    for(i = 0; i <= ox; i++)
        std::cout << "_";
    std::cout << '\n';
}

bool Simulare::isSorted() const {
    Pozitie r, s;
    for(int i = 1; i < n; ++i) {
        r = v[i-1]->getPozitie();
        s = v[i]->getPozitie();
        if(r.y < s.y)
            return false;
        else if(r.y == s.y && r.x > s.x)
            return false;
    }
    return true;
}

void Simulare::bsort() {
    Agent *a;
    Pozitie p, q;
    for(int j = 0; j < n; ++j) {
        p = v[j]->getPozitie();
        for(int k = j + 1; k < n; ++k) {
            q = v[k]->getPozitie();
            if(p.x && p.x == q.x && p.y == q.y)    // nu ar trebui sa existe doi agenti in acelasi loc
                std::cout << "err\n";
            if(p.y < q.y) {        // descrescator pe verticala
                a = v[j];
                v[j] = v[k];
                v[k] = a;
            }
            else if(p.y == q.y && q.x < p.x) {      // crescator pe orizontala
                a = v[j];
                v[j] = v[k];
                v[k] = a;
            }
        }
    }
}

bool Simulare::seRepeta(Pozitie &p, Pozitie &q) const {
    for(int j = 0; j < n; ++j) {
        p = v[j]->getPozitie();
        if(p.x && p.y)
            for(int k = j + 1; k < n; ++k) {
                q = v[k]->getPozitie();
                if(p.x == q.x && p.y == q.y && k != j)
                    return true;
            }
    }
    return false;
}

Simulare::~Simulare() {
    for(int i = 0; i < n; ++i)
        delete v[i];
    delete[] v;
}
