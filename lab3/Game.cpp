#include "Game.h"

bool checkAmountShip(std::map<char, IGamer::ship> ships) {
    bool isThereShip = true;
    int shipCount = 0;
    for (char i = '0'; i <= '9'; i++) {
        if (ships[i].size == 0) {
            shipCount++;
        }
    }
    if (shipCount == 10) {
        isThereShip = false;
    }
    return isThereShip;
}

void playGame(std::shared_ptr<IGamer::IGamer> &player1, std::shared_ptr<IGamer::IGamer> &player2, int & rounds) {
    char** field1 = player1->getField();
    char** field2 = player2->getField();
    std::cout << "Fill your field, player 1"<<std::endl;
    player1->shipLoop();
    std::map<char, IGamer::ship> ships1 = player1->getShips();
    Sleep(1000);
    std::cout << "Fill your field, player 2"<<std::endl;
    player2->shipLoop();
    std::map<char, IGamer::ship> ships2 = player2->getShips();
    Sleep(1000);
    std::cout << "See your field, player 1"<<std::endl;
    IGameView::ConsoleView:: consoleView(field1, field2);
    Sleep(1000);
    std::cout << "See your field, player 2"<<std::endl;
    IGameView::ConsoleView:: consoleView(field2, field1);
    Sleep(1000);
    bool win = true;
    while (true) {
        std::cout << "The 1st player is shooting." << std::endl;
        player1->shoot(field2, ships2);
        win = checkAmountShip(ships2);
        if (!win) {
            std::cout << "1st player WIN" << std::endl;
            break;
        }
        std::cout << "The 2st player is shooting." << std::endl;
        player2->shoot(field1, ships1);
        win = checkAmountShip(ships1);
        if (!win) {
            std::cout << "2nd player WIN" << std::endl;
            break;
        }
    }
}