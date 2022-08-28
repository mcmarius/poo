//
// Created by marius on 2020-11-16.
//

#include "map_full_error.h"

const char *map_full_error::what() const noexcept {
    return runtime_error::what();
}
