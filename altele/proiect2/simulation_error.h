//
// Created by marius on 2020-11-16.
//

#ifndef SURVIVAL_GAME_SIMULATION_ERROR_H
#define SURVIVAL_GAME_SIMULATION_ERROR_H

#include <stdexcept>

class simulation_error : public std::runtime_error {
public:
    simulation_error(std::string& msg) : std::runtime_error(msg) {}
};

#endif //SURVIVAL_GAME_SIMULATION_ERROR_H
