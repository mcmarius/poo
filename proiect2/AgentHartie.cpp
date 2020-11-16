//
// Created by marius on 15/04/2016.
//

#include "AgentHartie.h"

AgentHartie::AgentHartie(int x, int y) : Agent({x, y}) {
    tip = '$';
}

void AgentHartie::avanseaza() {
    int y = rand() % 113 + 1;
    pozitie.y += y;
    int x = rand() % 127 + 1;
    pozitie.x += x;
}

int AgentHartie::confrunta(int i) const {
    return i == '@';
}

AgentHartie::~AgentHartie() = default;
