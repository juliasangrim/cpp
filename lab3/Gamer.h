//
// Created by julia on 12/4/2020.
//

#ifndef SEABATTLE_GAMER_H
#define SEABATTLE_GAMER_H
#include <iostream>
#include <string>
#include <memory>
#include <windows.h>
#include <map>
#include <ctime>
#include "GameView.h"
#define sizeField 10

namespace IGamer {
    typedef struct ship{
        int size, x_begin, y_begin, direction;
    } ship;
    class IGamer {
    public:
        ~IGamer() = default;
        virtual void setShip(int &shipCount, int &shipSize, int &shipIndex) = 0;
        virtual char** getField() = 0;
        virtual std::map<char, ship>getShips() = 0;
        virtual void placeShip() = 0;
        virtual bool shoot(char** &player2, std::map<char, ship> &enemyShips) = 0;
        virtual void makeFree() = 0;
    };

    class ConsoleGamer : public IGamer {
    private:
        char **m_field;
        std::map<char, ship> ships;
    public:
        ConsoleGamer();
        void placeShip() override;
        void setShip(int &shipCount, int &shipSize, int &shipIndex)override;
        bool shoot(char** &enemy, std::map<char, ship> &enemyShips) override;
        char** getField() override;
        void makeFree() override;
        std::map<char, ship>getShips()override;
        ~ConsoleGamer();
    };

    class RandomGamer : public IGamer {
    private:
        char **m_field;
        std::map<char, ship> ships;
    public:
        RandomGamer();
        void placeShip() override;
        void setShip(int &shipCount, int &shipSize, int &shipIndex) override;
        bool shoot(char** &enemy, std::map<char, ship> &enemyShips) override;
        char** getField() override;
        void makeFree() override;
        std::map<char, ship>getShips()override;
        ~RandomGamer();
    };

    class OptimalGamer : public IGamer {
    private:
        char **m_field;
        std::map<char, ship> ships;
        int xCurr, yCurr, dirCurr;
        bool isCoordFind;
        void changeDirection(int &dir, int &x, int &y);
    public:
        OptimalGamer();
        void placeShip() override;
        void setShip(int &shipCount, int &shipSize, int &shipIndex)override;
        bool shoot(char** &enemy, std::map<char, ship> &enemyShips) override;
        char** getField() override;
        void makeFree() override;
        std::map<char, ship>getShips()override;
        ~OptimalGamer();
    };
    void checkAreaShip (bool &setting_is_possible, int &shipSize, int x, int y, char** field);
    void addHit(char** &enemy, char &index, std::map<char, ship> &ships);
    bool inBounds(int &x, int &y);
    void direction(int &dir, int &x, int &y);
}
#endif //SEABATTLE_GAMER_H
