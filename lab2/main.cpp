#include "workflow.h"
#include "ParserFile.h"

using namespace std;
int main(int argc, char** argv) {
    try {
        if (argc < 2) {
            Validator("Few arguments in command line. Please, try again.");
        } else if (argc > 2) {
            Validator("Too many arguments in command line. Please, try again.");
        }
    }
    catch (const std::exception & ex) {
        std::cout <<  ex.what() << std::endl;
        return 0;
    }
    try {
       ParserFile::parseFile(argv[1]);
    }

    catch (const std::exception & ex) {
        std::cout <<  ex.what() << std::endl;
    }
    return 0;
}
