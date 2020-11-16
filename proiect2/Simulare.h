//
// Created by marius on 15/04/2016.
//

#ifndef SURVIVAL_GAME_SIMULARE_H
#define SURVIVAL_GAME_SIMULARE_H

#include <iostream>
#include <memory>
#include <vector>
#include "AgentPiatra.h"
#include "AgentFoarfeca.h"
#include "AgentHartie.h"

class Simulare {
    Agent **v;
    std::vector<std::vector<std::unique_ptr<Agent>>> v2;
    const unsigned char c;
    int n, ox, oy, nt, n2, t;
    bool seRepeta(Pozitie &p, Pozitie &q) const;
    void makeRandomXY(int i, Pozitie &p, Pozitie &q);
    void bsort();
    bool isSorted() const;
public:
    Simulare(int, int, int);
    void afisare();
    ~Simulare();
    int simuleaza(int = 0);
};

#endif //SURVIVAL_GAME_SIMULARE_H
