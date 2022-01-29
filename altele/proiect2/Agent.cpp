//
// Created by marius on 15/04/2016.
//

#include <iostream>
#include "Agent.h"

Agent::Agent(const Pozitie &pozitie) : pozitie(pozitie) {}

Agent::Agent(const Agent &a) : pozitie(a.pozitie), tip(a.tip) {}

Agent &Agent::operator=(const Agent &a) {
    if(&a != this) {  // self assignment
        pozitie = a.pozitie;
        tip = a.tip;
    }

    return *this;
}

std::ostream &operator<<(std::ostream &os, const Agent &agent) {
    os << "pozitie: " << agent.pozitie << " tip: " << agent.tip;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Pozitie &pozitie) {
    os << "x: " << pozitie.x << " y: " << pozitie.y;
    return os;
}

void Agent::avanseaza() {
    std::cout << "baza\n";
}