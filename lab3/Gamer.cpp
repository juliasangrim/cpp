#include "Gamer.h"

IGamer::ConsoleGamer::ConsoleGamer() {
    m_field = new char* [sizeField];
    for (char ch = '0'; ch <= '3'; ch++) {
        ships[ch] = 1;
    }
    for (char ch = '4'; ch <= '6'; ch++) {
        ships[ch] = 2;
    }
    for (char ch = '7'; ch <= '8'; ch++) {
        ships[ch] = 3;
    }
    ships['9'] = 4;
    for (int i = 0; i < sizeField; i++) {
        m_field[i] = new char [sizeField];
    }
    for (int i = 0; i < sizeField; i++) {
        for (int j = 0; j < sizeField; j++) {
            m_field[i][j] = ' ';
        }
    }
}

IGamer::RandomGamer::RandomGamer() {
    m_field = new char* [sizeField];
    for (char ch = '0'; ch <= '3'; ch++) {
        ships[ch] = 1;
    }
    for (char ch = '4'; ch <= '6'; ch++) {
        ships[ch] = 2;
    }
    for (char ch = '7'; ch <= '8'; ch++) {
        ships[ch] = 3;
    }
    ships['9'] = 4;
    for (int i = 0; i < sizeField; i++) {
        m_field[i] = new char [sizeField];
    }
    for (int i = 0; i < sizeField; i++) {
        for (int j = 0; j < sizeField; j++) {
            m_field[i][j] = ' ';
        }
    }
}

IGamer::OptimalGamer::OptimalGamer() {
    m_field = new char* [sizeField];
    for (char ch = '0'; ch <= '3'; ch++) {
        ships[ch] = 1;
    }
    for (char ch = '4'; ch <= '6'; ch++) {
        ships[ch] = 2;
    }
    for (char ch = '7'; ch <= '8'; ch++) {
        ships[ch] = 3;
    }
    ships['9'] = 4;
    for (int i = 0; i < sizeField; i++) {
        m_field[i] = new char [sizeField];
    }
    for (int i = 0; i < sizeField; i++) {
        for (int j = 0; j < sizeField; j++) {
            m_field[i][j] = ' ';
        }
    }
}

bool inBounds(int &x, int &y) {
    if (x < 0 || y < 0 || x >= sizeField || y >= sizeField) return false;
    return true;
}

void IGamer::ConsoleGamer::shipLoop() {
    int shipCount = 4;
    int shipSize = 1;
    int shipIndex = 0;
    std::cout << "\nYou have:\nfour torpedo boats\nthree destroyers\ntwo cruises\none battle ship\n"<<std::endl;
    std::cout << "Placed your torpedo boats...\n"<<std::endl;
    this->setShip(shipCount, shipSize, shipIndex);
    shipCount--;
    shipSize++;
    std::cout << "You have:\nthree destroyers\ntwo cruises\none battle ship\n"<<std::endl;
    std::cout << "Placed your destroyers...\n"<<std::endl;
    this->setShip(shipCount, shipSize,shipIndex);
    shipCount--;
    shipSize++;
    std::cout << "You have:\ntwo cruises\none battle ship\n"<<std::endl;
    std::cout << "Placed your cruises...\n"<<std::endl;
    this->setShip(shipCount, shipSize, shipIndex);
    shipCount--;
    shipSize++;
    std::cout << "You have:\none battle ship\n"<<std::endl;
    std::cout << "Placed your battle ship...\n"<<std::endl;
    this->setShip(shipCount, shipSize, shipIndex);
}

void IGamer::ConsoleGamer::setShip(int &shipCount, int &shipSize, int &shipIndex) { //TODO coordinate check
    bool setting_is_possible = true;
    int x, y;
    int dir = 0;
    int temp_x;
    int temp_y;
    int count_ship = 0;
    while (count_ship < shipCount) {
        do {
            std::cout<<"Please, write the first coordinate.(number)"<<std::endl;
            std::cin >> x;
            std::cout<<"Please, write the second coordinate.(number)"<<std::endl;
            std::cin>>y;
            x--;
            y--;
            temp_x = x;
            temp_y = y;
            std::cout<<"Please, write the coordinate direction.\n"
                       "There is four directions:\n"
                       "0 - down\n"
                       "1 - right\n"
                       "2 - up\n"
                       "3 - left"<<std::endl;
            std::cin>>dir;
//            if (dir > 3) {
//                std::cout<<"Ooops...There is no such a direction. Please, write the correct direction.\n"<<std::endl;
//                setting_is_possible = false;
//                continue;
//            }
            setting_is_possible = true;
            for (int i = 0; i < shipSize; ++i) {
                if (!inBounds(x, y)) {
                    setting_is_possible = false;
                    std::cout<<"The coordinates is not in the field. Please, write the correct coordinates.\n"<<std::endl;
//                    Sleep(5000);
//                    system("cls");
                    break;
                }
                for (int x1 = x - 1; x1 <= x + 1; x1++) {
                    for (int y1 = y - 1; y1 <= y + 1; y1++) {
                        if (!inBounds(x1, y1)) {
                            continue;
                        }
                        if ((m_field[x1][y1] >= '0') && (m_field[x1][y1] <= '9'))  {
                            setting_is_possible = false;
                            std::cout<<"Ooops...Ship is staying here or near already. Please, write the correct coordinates.\n"<<std::endl;
                            break;
                        }
                        if (!setting_is_possible) break;
                    }
                }
                if (setting_is_possible) {
                    switch (dir) {
                        case 0:
                            x++;
                            break;
                        case 1:
                            y++;
                            break;
                        case 2:
                            x--;
                            break;
                        case 3:
                            y--;
                            break;
                        default:
                            break;
                    }
                } else break;
            }
        } while (!setting_is_possible);

        if (setting_is_possible) {
            x = temp_x;
            y = temp_y;
            for (int i = 0; i < shipSize; ++i) {
                m_field[x][y] = static_cast<char>(static_cast<int>('0') + shipIndex);
                switch (dir) {
                    case 0:
                        x++;
                        break;
                    case 1:
                        y++;
                        break;
                    case 2:
                        x--;
                        break;
                    case 3:
                        y--;
                        break;
                    default:
                        break;

                }
            }
        }
        shipIndex++;
        count_ship++;
        IGameView::ConsoleView::consoleView(m_field, m_field);
//        Sleep(5000);
//        system("cls");
    }


}

char **IGamer::ConsoleGamer::getField() {
    return m_field;
}

void IGamer::ConsoleGamer::shoot(char** &enemy) {

}

std::map<char, int> IGamer::ConsoleGamer::getShips() {
    return ships;
}

void IGamer::RandomGamer::shipLoop() {
    int shipCount = 4;
    int shipSize = 1;
    int shipIndex = 0;
    this->setShip(shipCount, shipSize, shipIndex);
    shipCount--;
    shipSize++;
    this->setShip(shipCount, shipSize, shipIndex);
    shipCount--;
    shipSize++;
    this->setShip(shipCount, shipSize, shipIndex);
    shipCount--;
    shipSize++;
    this->setShip(shipCount, shipSize, shipIndex);
}

void IGamer::RandomGamer::setShip(int &shipCount, int &shipSize, int &shipIndex) {
    bool setting_is_possible = true;
    int x, y;
    int dir = 0;
    int temp_x;
    int temp_y;
    int count_ship = 0;
    while (count_ship < shipCount) {
        do {
            x = rand() % sizeField;
            y = rand() % sizeField;

            temp_x = x;
            temp_y = y;

            dir = rand() % 4;

            setting_is_possible = true;
            for (int i = 0; i < shipSize; ++i) {
                if (!inBounds(x, y)) {
                    setting_is_possible = false;
                    break;
                }
              for (int x1 = x - 1; x1 <= x + 1; x1++) {
                  for (int y1 = y - 1; y1 <= y + 1; y1++) {
                      if (!inBounds(x1, y1)) {
                          continue;
                      }
                      if ((m_field[x1][y1] >= '0') && (m_field[x1][y1] <= '9')) {
                          setting_is_possible = false;
                          break;
                      }
                  }
              }

                switch (dir) {
                    case 0:
                        x++;
                        break;
                    case 1:
                        y++;
                        break;
                    case 2:
                        x--;
                        break;
                    case 3:
                        y--;
                        break;
                    default:
                        break;
                }
            }
        } while (!setting_is_possible);

        if (setting_is_possible) {
            x = temp_x;
            y = temp_y;
            for (int i = 0; i < shipSize; ++i) {
               m_field[x][y] = static_cast<char>(static_cast<int>('0') + shipIndex);
                switch (dir) {
                    case 0:
                        x++;
                        break;
                    case 1:
                        y++;
                        break;
                    case 2:
                        x--;
                        break;
                    case 3:
                        y--;
                        break;
                    default:
                        break;

                }
            }
        }
        shipIndex++;
        count_ship++;
    }
}

char **IGamer::RandomGamer::getField() {
    return m_field;
}

void IGamer::RandomGamer::shoot(char** &enemy) {
//    bool isThereShip = true;
//    int x, y;
//    while (isThereShip) {
//        x = rand() % sizeField;
//        y = rand() % sizeField;
//        if (enemy[x][y] == '#') {
//            for (int x1 = x - 1; x1 <= x + 1; x1++) {
//                for (int y1 = y - 1; y1 <= y + 1; y1++) {
//                    if (!inBounds(x1, y1)) {
//                        continue;
//                    }
//                    if (m_field[x1][y1] == '#') {
//                        setting_is_possible = false;
//                        break;
//                    }
//                }
//            }
//
//        }
//    }
}

std::map<char, int> IGamer::RandomGamer::getShips() {
    return ships;
}

void IGamer::OptimalGamer::shipLoop() {
    int shipCount = 4;
    int shipSize = 1;
    int shipIndex = 0;
    this->setShip(shipCount, shipSize, shipIndex);
    shipCount--;
    shipSize++;
    this->setShip(shipCount, shipSize, shipIndex);
    shipCount--;
    shipSize++;
    this->setShip(shipCount, shipSize, shipIndex);
    shipCount--;
    shipSize++;
    this->setShip(shipCount, shipSize, shipIndex);
}


void IGamer::OptimalGamer::setShip(int &shipCount, int &shipSize, int &shipIndex) {
    bool setting_is_possible = true;
    int x, y;
    int dir = 0;
    int temp_x;
    int temp_y;
    int count_ship = 0;
    while (count_ship < shipCount) {
        do {
            x = rand() % sizeField;
            y = rand() % sizeField;

            temp_x = x;
            temp_y = y;

            dir = rand() % 4;

            setting_is_possible = true;
            for (int i = 0; i < shipSize; ++i) {
                if (!inBounds(x, y)) {
                    setting_is_possible = false;
                    break;
                }
                for (int x1 = x - 1; x1 <= x + 1; x1++) {
                    for (int y1 = y - 1; y1 <= y + 1; y1++) {
                        if (!inBounds(x1, y1)) {
                            continue;
                        }
                        if ((m_field[x1][y1] >= '0') && (m_field[x1][y1] <= '9')) {
                            setting_is_possible = false;
                            break;
                        }
                    }
                }

                switch (dir) {
                    case 0:
                        x++;
                        break;
                    case 1:
                        y++;
                        break;
                    case 2:
                        x--;
                        break;
                    case 3:
                        y--;
                        break;
                    default:
                        break;
                }
            }
        } while (!setting_is_possible);

        if (setting_is_possible) {
            x = temp_x;
            y = temp_y;
            for (int i = 0; i < shipSize; ++i) {
                m_field[x][y] = static_cast<char>(static_cast<int>('0') + shipIndex);
                switch (dir) {
                    case 0:
                        x++;
                        break;
                    case 1:
                        y++;
                        break;
                    case 2:
                        x--;
                        break;
                    case 3:
                        y--;
                        break;
                    default:
                        break;

                }
            }
        }
        shipIndex++;
        count_ship++;
    }
}

char **IGamer::OptimalGamer::getField() {
    return m_field;
}

void IGamer::OptimalGamer::shoot(char** &enemy) {

}

std::map<char, int> IGamer::OptimalGamer::getShips() {
    return ships;
}
