#include "parser.h"
#include <ctime>
int main(int argc, char **argv) {
    srand(time(nullptr));
    Parser::parserCmd(argc, argv);
    return 0;
}

