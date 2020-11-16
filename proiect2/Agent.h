//
// Created by marius on 15/04/2016.
//

#ifndef SURVIVAL_GAME_AGENT_H
#define SURVIVAL_GAME_AGENT_H

#include <ctime>
#include <cstdlib>

struct Pozitie {
    int x, y;
};

class Agent {
protected:
    Pozitie pozitie;
    unsigned char tip;
public:
    const Pozitie &getPozitie() const { return pozitie; }
    unsigned char getTip() const { return tip; }
    void setPozitie(int x, int y) { pozitie.x = x; pozitie.y = y; }
    virtual void avanseaza() = 0;
    virtual int confrunta(int) = 0;
    virtual ~Agent() { }
};

#endif //SURVIVAL_GAME_AGENT_H
