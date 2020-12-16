#include "Gamer.h"

/////////CONSTRUCTORS////////////////////////////////////////////////////////////
IGamer::ConsoleGamer::ConsoleGamer() {
    m_field = new char* [sizeField];
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
    xCurr = 0;
    yCurr = 0;
    dirCurr = 0;
    isCoordFind = false;
    for (int i = 0; i < sizeField; i++) {
        m_field[i] = new char [sizeField];
    }
    for (int i = 0; i < sizeField; i++) {
        for (int j = 0; j < sizeField; j++) {
            m_field[i][j] = ' ';
        }
    }
}

//////////DESTRUCTORS////////////////////////////////////////////////////////////////////
IGamer::ConsoleGamer::~ConsoleGamer() {
    for (int i = 0; i < sizeField; i++) {
        delete[] m_field[i];
    }
    delete[] m_field;
}

IGamer::RandomGamer::~RandomGamer() {
    for (int i = 0; i < sizeField; i++) {
        delete[] m_field[i];
    }
    delete[] m_field;
}

IGamer::OptimalGamer::~OptimalGamer() {
    for (int i = 0; i < sizeField; i++) {
        delete[] m_field[i];
    }
    delete[] m_field;
}

/////////CHECKS//////////////////////////////////////////////////////////////////////////
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

bool IGamer::inBounds(int &x, int &y) {
    if (x < 0 || y < 0 || x >= sizeField || y >= sizeField) return false;
    return true;
}

///////////OTHER FUNCTIONS////////////////////////////////////////////////////////////////////
void IGamer::direction(int &dir, int &x, int &y) {
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

void IGamer::addHit(char** enemy, char &index, std::map<char, ship> &ships){
    int x_begin = ships[index].x_begin;
    int y_begin = ships[index].y_begin;
    while (inBounds(x_begin, y_begin) && (enemy[x_begin][y_begin] == 'X')) {
        for (int x1 = x_begin - 1; x1 <= x_begin + 1; x1++) {
            for (int y1 = y_begin - 1; y1 <= y_begin + 1; y1++) {
                if (!inBounds(x1, y1)) {
                    continue;
                }
                if (enemy[x1][y1] == ' ')  {
                    enemy[x1][y1] = '.';
                }
            }
        }
        switch (ships[index].direction) {
            case 0:
                x_begin++;
                break;
            case 1:
                y_begin++;
                break;
            case 2:
                x_begin--;
                break;
            case 3:
                y_begin--;
                break;
            default:
                break;
        }
    }
}
////////////Console gamer/////////////////////////////////////////////////////////////////////
void IGamer::ConsoleGamer::placeShip() {
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

void IGamer::ConsoleGamer::setShip(int &shipCount, int &shipSize, int &shipIndex) {
    bool setting_is_possible = true;
    int x, y;
    int dir = 0;
    int temp_x;
    int temp_y;
    int count_ship = 0;
    ///check the area of future ship
    while (count_ship < shipCount) {
        do {
            IGameView::ConsoleView::printPlayingField(m_field, m_field);
            std::cout<<"Please, write the first coordinate.(vertical)"<<std::endl;
            std::cin >> x;
            std::cout<<"Please, write the second coordinate.(horizontal)"<<std::endl;
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
            if (dir > 3) {
                std::cout<<"Ooops...There is no such a direction. Please, write the correct direction.\n"<<std::endl;
                Sleep(5000);
                system("cls");
                setting_is_possible = false;
                }
            setting_is_possible = true;
            for (int i = 0; i < shipSize; ++i) {
                if (!inBounds(x, y)) {
                    setting_is_possible = false;
                    std::cout<<"The coordinates is not in the field. Please, write the correct coordinates.\n"<<std::endl;
                    Sleep(5000);
                    system("cls");
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
                            Sleep(5000);
                            system("cls");
                            break;
                        }
                        if (!setting_is_possible) break;
                    }
                }
                if (setting_is_possible) {
                    direction(dir, x,y);
                } else break;
            }
        } while (!setting_is_possible);

        if (setting_is_possible) {
            x = temp_x;
            y = temp_y;
            char index = static_cast<char>(static_cast<int>('0') + shipIndex);
            ships[index].size = shipSize;
            ships[index].x_begin = x;
            ships[index].y_begin = y;
            ships[index].direction = dir;
            for (int i = 0; i < shipSize; ++i) {
                m_field[x][y] = index;
                direction(dir, x, y);
            }
        }
        shipIndex++;
        count_ship++;
        system("cls");
    }
}

char **IGamer::ConsoleGamer::getField() {
    return m_field;
}

std::map<char, IGamer::ship> IGamer::ConsoleGamer::getShips() {
    return ships;
}

bool IGamer::ConsoleGamer::shoot(char** enemy, std::map<char, ship> &enemyShips) {
    bool hit = true;
    int x, y;
    IGameView::ConsoleView::printPlayingField(m_field,enemy);
    while (hit) {
        std::cout << "Please, write the first coordinate:\n";
        std::cin >> x;
        std::cout << "Please, write the second coordinate:\n";
        std::cin >> y;
        x--;
        y--;
        if (!inBounds(x, y)) {
            std::cout << "Please, write correct coordinates:\n";
            continue;
        }
        char index = enemy[x][y];
        if ((index >= '0') && ((index <= '9'))) {
            enemyShips[index].size--;
            std::cout << "HIT!!!" << std::endl;
            enemy[x][y] = 'X';
            if (enemyShips[index].size == 0) {
                std::cout << "YOU HIT THE ENEMY SHEEP!" << std::endl;
                addHit(enemy, index, enemyShips);
                if (!checkAmountShip(enemyShips)) {
                    return true;
                }
            }
        } else {
            if (index == 'X') {
                std::cout << "You have already hit here" << std::endl;
                hit = false;
                continue;
            }
            std::cout << "\nYou missed!\n" ;
            enemy[x][y] = '.';
            hit = false;
        }
        IGameView::ConsoleView::printPlayingField(m_field, enemy);
    }
    Sleep(5000);
    system("cls");
    return false;
}


void IGamer::ConsoleGamer::makeFree() {
    for (int i = 0; i < sizeField; i++) {
        for (int j = 0; j < sizeField; j++) {
            m_field[i][j] = ' ';
        }
    }
}

///////Random gamer////////////////////////////////////////////////////////////////////
void IGamer::RandomGamer::placeShip() {
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

                direction(dir, x, y);
            }
        } while (!setting_is_possible);

        if (setting_is_possible) {
            x = temp_x;
            y = temp_y;
            char index = static_cast<char>(static_cast<int>('0') + shipIndex);
            ships[index].size = shipSize;
            ships[index].x_begin = x;
            ships[index].y_begin = y;
            ships[index].direction = dir;
            for (int i = 0; i < shipSize; ++i) {
                m_field[x][y] = index;
               direction(dir, x, y);
            }
        }
        shipIndex++;
        count_ship++;
    }
}

char **IGamer::RandomGamer::getField() {
    return m_field;
}


bool IGamer::RandomGamer::shoot(char** enemy, std::map<char, ship> &enemyShips) {
    bool hit = true;
    int x, y;
    while (hit) {
        x = rand() % sizeField;
        y = rand() % sizeField;
        char index = enemy[x][y];
        if ((index >= '0') && ((index <= '9'))) {
            enemyShips[index].size--;
            std::cout << "HIT!!!" << std::endl;
            enemy[x][y] = 'X';
            if (enemyShips[index].size == 0) {
                std:: cout << "YOU HIT THE ENEMY SHEEP!" << std::endl;
                if (!checkAmountShip(enemyShips) ) {
                    return true;
                }

            }
        } else {
            if ((index == 'X') || (index == '.')) {
                std::cout << "You have already hit here" << std::endl;
                continue;
            }
            enemy[x][y] = '.';
            hit = false;
        }
        IGameView::ConsoleView:: printPlayingField(m_field, enemy);
    }
    Sleep(100);
    system("cls");
    return false;
}

std::map<char, IGamer::ship> IGamer::RandomGamer::getShips() {
    return ships;
}

void IGamer::RandomGamer::makeFree() {
    for (int i = 0; i < sizeField; i++) {
        for (int j = 0; j < sizeField; j++) {
            m_field[i][j] = ' ';
        }
    }
}

/////////Optimal gamer////////////////////////////////////////////////////
void IGamer::OptimalGamer::placeShip() {
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
                direction(dir, x, y);
            }
        } while (!setting_is_possible);

        if (setting_is_possible) {
            x = temp_x;
            y = temp_y;
            x = temp_x;
            y = temp_y;
            char index = static_cast<char>(static_cast<int>('0') + shipIndex);
            ships[index].size = shipSize;
            ships[index].x_begin = x;
            ships[index].y_begin = y;
            ships[index].direction = dir;
            for (int i = 0; i < shipSize; ++i) {
                m_field[x][y] = index;
                direction(dir, x, y);
            }
        }
        shipIndex++;
        count_ship++;
    }
}

char **IGamer::OptimalGamer::getField() {
    return m_field;
}

void IGamer::OptimalGamer::changeDirection(int &dir, int &x, int &y) {
    switch (dir) {
        case 0:
            x--;
            break;
        case 1:
            y--;
            break;
        case 2:
            x++;
            break;
        case 3:
            y++;
            break;
    }
    dir++;
}

bool IGamer::OptimalGamer::shoot(char** enemy, std::map<char, ship> &enemyShips) {
    bool hit = true;
    while (hit) {
        if (!isCoordFind) {
            xCurr  = rand() % 10;
            yCurr = rand() % 10;
        } else {
            dirCurr = dirCurr % 4;
            switch (dirCurr) {
                case 0:
                    if (xCurr < sizeField - 1) {
                        xCurr++;
                    } else {
                        dirCurr++;
                        continue;
                    }
                    break;
                case 1:
                    if (yCurr < sizeField - 1) {
                        yCurr++;
                    } else {
                        dirCurr++;
                        continue;
                    }
                    break;
                case 2:
                    if (xCurr > 0) {
                        xCurr--;
                    } else {
                        dirCurr++;
                        continue;
                    }
                    break;
                case 3:
                    if (yCurr > 0) {
                        yCurr--;
                    }else {
                        dirCurr++;
                        continue;
                    }
                    break;
            }
        }
        char index = enemy[xCurr][yCurr];
        if ((index >= '0') && ((index <= '9'))) {
            isCoordFind = true;
            enemyShips[index].size--;
            std::cout << "HIT!!!" << std::endl;
            enemy[xCurr][yCurr] = 'X';
            if (enemyShips[index].size == 0) {
                std:: cout << "YOU HIT THE ENEMY SHEEP!" << std::endl;
                addHit(enemy, index, enemyShips);
                dirCurr = 0;
                isCoordFind = false;
                if (!checkAmountShip(enemyShips) ) {
                    return true;
                }

            }
        } else {
            if (index == 'X')  {
                continue;
            }
            if  (index == '.') {
                changeDirection(dirCurr, xCurr, yCurr);
                continue;
            }
            enemy[xCurr][yCurr] = '.';
            if (isCoordFind) {
                changeDirection(dirCurr, xCurr, yCurr);
            }
            hit = false;
        }

        IGameView::ConsoleView::printPlayingField(m_field, enemy);
    }
    Sleep(100);
    system("cls");
    return false;
}

std::map<char, IGamer::ship> IGamer::OptimalGamer::getShips() {
    return ships;
}

void IGamer::OptimalGamer::makeFree() {
    for (int i = 0; i < sizeField; i++) {
        for (int j = 0; j < sizeField; j++) {
            m_field[i][j] = ' ';
        }
    }
}

