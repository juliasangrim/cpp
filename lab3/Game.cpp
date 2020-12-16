#include "Game.h"

void playGame(std::shared_ptr<IGamer::IGamer> &player1, std::shared_ptr<IGamer::IGamer> &player2, int &rounds) {
    int score1 = 0;
    int score2 = 0;
    for (int i = 1; i <= rounds; i++){
        IGameView::ConsoleView::printRounds(i);
        system("cls");
        std::cout << "Fill your field, player 1" << std::endl;
        player1->placeShip();
        char **field1 = player1->getField();
        std::map<char, IGamer::ship> ships1 = player1->getShips();
        Sleep(1000);

        std::cout << "Fill your field, player 2" << std::endl;
        player2->placeShip();
        char **field2 = player2->getField();
        std::map<char, IGamer::ship> ships2 = player2->getShips();
        Sleep(1000);

        bool win = false;
        while (true) {
            std::cout << "The 1st player is shooting." << std::endl;
            win = player1->shoot(field2, ships2);

            if (win) {
                score1++;
                system("cls");
                std::cout << "1st player WIN " << i << " round" << std::endl;
                break;
            }

            std::cout << "The 2st player is shooting." << std::endl;
            win = player2->shoot(field1, ships1);

            if (win) {
                score2++;
                system("cls");
                std::cout << "2nd player WIN " << i << " round" << std::endl;
                break;
            }
        }
        Sleep(3000);
        system("cls");

        std::cout << "      THE SCORE\n"
                     "---------------------\n"
                     "PLAYER 1     PLAYER 2\n"
                     "    "<< score1 << "             "<< score2<<std::endl;
        Sleep(3000);
        system("cls");
        //free fields
        if (i != rounds) {
            player1->makeFree();
            player2->makeFree();
        }

    }
    if (score1 > score2) {
        std::cout << "THE FIRST PLAYER WIN IN THE GAME!\n";
    } else {
        if (score1 == score2) {
            std::cout << "DRAW!\n";
        } else {
            std::cout << "THE SECOND PLAYER WIN IN THE GAME!\n";
        }
    }
}