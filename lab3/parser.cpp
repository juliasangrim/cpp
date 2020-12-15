#include "parser.h"
#include "Game.h"

struct Arg: public option::Arg
{
    static void printError(const char* msg1, const option::Option& opt, const char* msg2)
    {
        fprintf(stderr, "ERROR: %s", msg1);
        std::cerr << "Error:" << msg1 <<  opt.name << msg2;
    }
    static option::ArgStatus NonEmpty(const option::Option& option, bool msg)
    {
        if (option.arg != 0 && option.arg[0] != 0)
            return option::ARG_OK;
        if (msg) printError("Option '", option, "' requires a non-empty argument\n");
        return option::ARG_ILLEGAL;
    }
    static option::ArgStatus Numeric(const option::Option& option, bool msg)
    {
        char* endptr = 0;
        if (option.arg != 0){
            strtol(option.arg, &endptr, 10);
        }
        if (endptr != option.arg && *endptr == 0)
            return option::ARG_OK;
        if (msg) printError("Option '", option, "' requires a numeric argument\n");
        return option::ARG_ILLEGAL;
    }
};

const option::Descriptor usage[] = {
        {static_cast<int>(Parser::OptionIndex::HELP), 0, "h" ,"help", option::Arg::None,"-h --help - \n     print information about parameters"},
        {static_cast<int> (Parser::OptionIndex::COUNT), 0, "c", "count", Arg::Numeric, "-c --count - \n     Default: 1, amount of rounds"},
        {static_cast<int> (Parser::OptionIndex::FIRST), 0, "f", "first", Arg::NonEmpty, "-f --first - \n     Default: random, type of the first player"},
        {static_cast<int> (Parser::OptionIndex::SECOND), 0, "s", "second", Arg::NonEmpty, "-s --second - \n     Default: random, type of the second player\n"
                                                                                          "Type of players: random, optimal and console\n"
                                                                                          "random - random play\n"
                                                                                          "console - player is you\n"
                                                                                          "optimal - player is computer\n"},
        {0,0,0,0,0,0}
};

int Parser::parserCmd(int argc, char **argv) {
    argc-=(argc > 0); argv+=(argc > 0);
    option::Stats stats(usage, argc, argv);
    option::Option options[stats.options_max], buffer[stats.options_max];
    option::Parser parse(usage, argc, argv, options, buffer);
    if (parse.error())
        return 1;
    if (options[static_cast<int>(Parser::OptionIndex::HELP)]) {
        option::printUsage(std::cout, usage);
        return 0;
    }
    ///////CHECKING THE KEY//////////////////////////////////////////////////////////////////
    if (options[static_cast<int> (Parser::OptionIndex::FIRST)].count() > 1) {
        std:: cout << "FIRST:Please, write only one key."<<std::endl;
        return 1;
    }
    if (options[static_cast<int> (Parser::OptionIndex::SECOND)].count() > 1) {
        std:: cout << "SECOND:Please, write only one key."<<std::endl;
        return 1;
    }
    if (options[static_cast<int> (Parser::OptionIndex::COUNT)].count() > 1) {
        std:: cout << "COUNT:Please, write only one key."<<std::endl;
        return 1;
    }
    ////////COUNT/////////////////////////////////////////////////////////////////////////////////
    int countRounds = 1;
    if (options[static_cast<int> (Parser::OptionIndex::COUNT)]) {
        countRounds = std::stoi(options[static_cast<int> (Parser::OptionIndex::COUNT)].arg);
    }
    //////////FIRST///////////////////////////////////////////////////////////////////////////////
    std::shared_ptr<IGamer::IGamer> player1;
    if (options[static_cast<int> (Parser::OptionIndex::FIRST)]) {
        std::string first(options[static_cast<int> (Parser::OptionIndex::FIRST)].arg);
        if (first == "random") {
            player1 = std::make_shared<IGamer::RandomGamer>();
        } else if (first == "optimal") {
            player1 = std::make_shared<IGamer::OptimalGamer>();
        } else if (first == "console") {
            player1 = std::make_shared<IGamer::ConsoleGamer>();
        } else {
            std::cout << "There's no this type of players" << std::endl;
        }
    } else {
        player1 = std::make_shared<IGamer::RandomGamer>();
    }
    //////////SECOND////////////////////////////////////////////////////////////////////////////////
    std::shared_ptr<IGamer::IGamer> player2;
    if (options[static_cast<int> (Parser::OptionIndex::SECOND)]) {
        std::string second(options[static_cast<int> (Parser::OptionIndex::SECOND)].arg);
        if (second == "random") {
            player2 = std::make_shared<IGamer::RandomGamer>();
        } else if (second == "optimal") {
            player2 = std::make_shared<IGamer::OptimalGamer>();
        } else if (second == "console") {
            player2 = std::make_shared<IGamer::ConsoleGamer>();
        } else {
            std::cout << "There's no this type of players" << std::endl;
        }
    } else {
        player2 = std::make_shared<IGamer::RandomGamer>();
    }
    playGame(player1, player2, countRounds);
    return 0;
}

