#include <iostream>
#include "CSVParser.h"

int main() {
    try {
    std::ifstream input;
    input.open("input2.csv");
    if (!input.is_open()) {
        throw std::runtime_error("Cannot open the file!");
    }

        Parser::CSVParser<int, std::string, std::string, std::string, double> parser(input, 0);
        for (std::tuple<int, std::string, std::string, std::string, double> rs : parser) {
            std::cout << rs << std::endl;
        }
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}