//
// Created by marius on 15/04/2016.
//

#include "AgentPiatra.h"

AgentPiatra::AgentPiatra(int x, int y) : Agent({x, y}) {
    tip = '@';
}

void AgentPiatra::avanseaza() {
    Agent::avanseaza();
    int y = rand() % 97 + 1;
    pozitie.y += y;
}

int AgentPiatra::confrunta(int i) const {
    return i == '#';
}

AgentPiatra::~AgentPiatra() = default;
