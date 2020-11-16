//
// Created by marius on 2020-11-16.
//

#ifndef SURVIVAL_GAME_TIMEOUT_ERROR_H
#define SURVIVAL_GAME_TIMEOUT_ERROR_H

#include "simulation_error.h"

class timeout_error : public simulation_error {
public:
    timeout_error(std::string& msg) : simulation_error(msg) {}
};

#endif //SURVIVAL_GAME_TIMEOUT_ERROR_H
