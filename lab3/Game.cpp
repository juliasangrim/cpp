#include "Game.h"



void playGame(std::shared_ptr<IGamer::IGamer> &player1, std::shared_ptr<IGamer::IGamer> &player2, int & rounds) {
    char** field1 = player1->getField();
    char** field2 = player2->getField();
    std::map<char, int> ships1 = player1->getShips();
    std::map<char, int> ships2 = player2->getShips();
    std::cout << "Fill your field, player 1"<<std::endl;
    player1->shipLoop();
    Sleep(1000);
    std::cout << "Fill your field, player 2"<<std::endl;
    player2->shipLoop();
    Sleep(1000);
    std::cout << "See your field, player 1"<<std::endl;
    IGameView::ConsoleView:: consoleView(field1, field2);
    Sleep(1000);
    std::cout << "See your field, player 2"<<std::endl;
    IGameView::ConsoleView:: consoleView(field2, field1);
    Sleep(1000);
}