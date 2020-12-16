#include "GameView.h"

void IGameView::ConsoleView::printPlayingField(char** field1, char** field2) {
    std::cout<<"         1  2  3  4  5  6  7  8  9  10                   1  2  3  4  5  6  7  8  9  10"<<std::endl;
    std::cout << "\n";

    //field 1
    for (int i = 0; i < sizeField; i++) {
        std::cout<< i + 1 << "\t";
        for (int j = 0; j < sizeField; j++) {
            if ((field1[i][j] >= '0') && (field1[i][j] <= '9')) {
            std::cout << "|" << '#' << "|";
            } else {
                if (field1[i][j] == '.') {

                    std::cout << "|" << ' ' << "|";
                } else {
                    std::cout << "|" << field1[i][j] << "|";
                }
            }
        }

        //field 2
        std::cout<<"\t\t"<< i + 1 << "\t";
        for (int j = 0; j < sizeField; j++) {
            if ((field2[i][j] >= '0') && (field2[i][j] <= '9')) {
                std::cout<<"|" << ' ' << "|";
            } else {
                std::cout << "|" << field2[i][j] << "|";
            }
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void IGameView::ConsoleView::printRounds(int rounds) {
    std::cout << "ROUND " << rounds << std::endl;
    Sleep(1000);
    std::cout << "READY" << std::endl;
    Sleep(1000);
    std::cout << "..." << std::endl;
    Sleep(1000);
    std::cout << "ALMOST HERE" << std::endl;
    Sleep(1000);
    std::cout << "..." << std::endl;
    Sleep(1000);
    std::cout << "99%" << std::endl;
    Sleep(1000);
    std::cout << "..." << std::endl;
    Sleep(1000);
    std::cout << "99,1%" << std::endl;
    Sleep(1000);
    std::cout << "..." << std::endl;
    Sleep(1000);
    std::cout << "FIGHT" << std::endl;
    Sleep(1000);
}




