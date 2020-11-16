//
// Created by marius on 15/04/2016.
//

#include "AgentFoarfeca.h"

AgentFoarfeca::AgentFoarfeca(int x, int y) : Agent({x, y}) {
    tip = '#';
}

void AgentFoarfeca::avanseaza() {
    int x = rand() % 101 + 1;
    pozitie.x += x;
}

int AgentFoarfeca::confrunta(int i) const {
    return i == '$';
}

AgentFoarfeca::~AgentFoarfeca() = default;
