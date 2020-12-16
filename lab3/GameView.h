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
    public:
        static void printPlayingField(char** field1, char** field2);
        static void printRounds(int rounds);
    };
}
#endif //SEABATTLE_GAMEVIEW_H
