#ifndef SEABATTLE_PARSER_H
#define SEABATTLE_PARSER_H
#include "optionparser.h"
#include <iostream>

class Parser {
public:static int parserCmd(int argc, char** argv);
    enum class OptionIndex {
        HELP,
        COUNT,
        FIRST,
        SECOND
    };
};
#endif //SEABATTLE_PARSER_H
