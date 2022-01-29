//
// Created by marius on 15/04/2016.
//

#ifndef SURVIVAL_GAME_AGENTHARTIE_H
#define SURVIVAL_GAME_AGENTHARTIE_H

#include "Agent.h"

class AgentHartie : public Agent {
public:
    AgentHartie(int, int);
    void avanseaza() override;
    int confrunta(int) const override;
    ~AgentHartie() override;
};

#endif //SURVIVAL_GAME_AGENTHARTIE_H
