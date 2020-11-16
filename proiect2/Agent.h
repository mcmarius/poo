//
// Created by marius on 15/04/2016.
//

#ifndef SURVIVAL_GAME_AGENT_H
#define SURVIVAL_GAME_AGENT_H

#include <ostream>

struct Pozitie {
    int x, y;
    friend std::ostream &operator<<(std::ostream &os, const Pozitie &pozitie);
};

class Agent {
protected:
    Pozitie pozitie;
    unsigned char tip = '\0';
public:
    explicit Agent(const Pozitie &pozitie);
    Agent(const Agent& a);
    Agent& operator=(const Agent& a);

    const Pozitie &getPozitie() const { return pozitie; }
    unsigned char getTip() const { return tip; }
    void setPozitie(int x, int y) { pozitie.x = x; pozitie.y = y; }
    virtual void avanseaza() = 0;
    virtual int confrunta(int) const = 0;
    virtual ~Agent() = default;
    friend std::ostream &operator<<(std::ostream &os, const Agent &agent);

};

#endif //SURVIVAL_GAME_AGENT_H
