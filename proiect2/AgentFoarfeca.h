//
// Created by marius on 15/04/2016.
//

#ifndef SURVIVAL_GAME_AGENTFOARFECA_H
#define SURVIVAL_GAME_AGENTFOARFECA_H

#include "Agent.h"

class AgentFoarfeca : public Agent {
public:
    AgentFoarfeca(int, int);
    void avanseaza() override;
    int confrunta(int) const override;
    ~AgentFoarfeca() override;
};

#endif //SURVIVAL_GAME_AGENTFOARFECA_H
