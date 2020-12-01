#include "Validator.h"

Validator::Validator(const std::string& errorMessage) {
    throw std::runtime_error(errorMessage);
}

