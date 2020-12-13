

#ifndef SEABATTLE_GAMEVIEW_H
#define SEABATTLE_GAMEVIEW_H
#include <iostream>
#include <string>
#include <windows.h>

#define sizeField 10
namespace IGameView {

    class IGameView {
    public:
        ~IGameView() = default;
    };

    class ConsoleView : IGameView {
    private:
        static void printPlayingField(char** &field1, char** &field2);
        static void printRounds(int rounds);
    public:
//        explicit ConsoleView(char** array1, char** array2); //TODO constructor for matrix
        static void consoleView(char** &field1, char** &field2);
    };
}
#endif //SEABATTLE_GAMEVIEW_H
