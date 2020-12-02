//
// Created by julia on 12/2/2020.
//

#ifndef WORKFLOW_VALIDATOR_H
#define WORKFLOW_VALIDATOR_H
#include <iostream>

class IValidator {
public:
    virtual ~IValidator() = default;
};

class Validator : public IValidator {
public:
    explicit Validator(const std::string &message);
};


#endif //WORKFLOW_VALIDATOR_H
