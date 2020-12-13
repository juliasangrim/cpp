#include "GameView.h"

//IGameView::ConsoleView::ConsoleView (char** array1, char** array2) { //TODO matrix
//    m_field1 = new char* [sizeField];
//    m_field2 = new char* [sizeField];
//    for (int i = 0; i < sizeField; i++) {
//        m_field1[i] = new char [sizeField];
//        m_field2[i] = new char [sizeField];
//    }
//    for (int i = 0; i < sizeField; i++) {
//        for (int j = 0; j < sizeField; j++) {
//            m_field1[i][j] = array1[i][j];
//            m_field2[i][j] = array1[i][j];
//        }
//    }
//}

void IGameView::ConsoleView::printPlayingField(char** &field1, char** &field2) {
    std::cout<<"         1  2  3  4  5  6  7  8  9  10                   1  2  3  4  5  6  7  8  9  10"<<std::endl;
    std::cout << "\n";
    for (int i = 0; i < sizeField; i++) {
        std::cout<< i + 1 << "\t";
        for (int j = 0; j < sizeField; j++) {
            if ((field1[i][j] >= '0') && (field1[i][j] <= '9') && (field1[i][j] == 'X')) {
            std::cout << "|" << '#' << "|";
            } else {
                if (field1[i][j] == '.') {

                    std::cout << "|" << ' ' << "|";
                } else {
                    std::cout << "|" << field1[i][j] << "|";
                }
            }
        }
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

void IGameView::ConsoleView::consoleView( char** &field1, char** &field2) {
    int q = 0;
    printPlayingField(field1, field2);
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
    std::cout << "FIGHT" << std::endl; //TODO 91,1 %
    Sleep(1000);
}




