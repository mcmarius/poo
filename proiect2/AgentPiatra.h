//
// Created by marius on 15/04/2016.
//

#ifndef SURVIVAL_GAME_AGENTPIATRA_H
#define SURVIVAL_GAME_AGENTPIATRA_H

#include "Agent.h"

class AgentPiatra : public Agent {
public:
    AgentPiatra(int, int);
    void avanseaza() override;
    int confrunta(int) const override;
    ~AgentPiatra() override;
};

#endif //SURVIVAL_GAME_AGENTPIATRA_H
