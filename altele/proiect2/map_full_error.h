//
// Created by marius on 2020-11-16.
//

#ifndef SURVIVAL_GAME_MAP_FULL_ERROR_H
#define SURVIVAL_GAME_MAP_FULL_ERROR_H

#include "simulation_error.h"

class map_full_error : public simulation_error {
public:
    map_full_error(std::string& msg) : simulation_error(msg) {}
    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

#endif //SURVIVAL_GAME_MAP_FULL_ERROR_H
