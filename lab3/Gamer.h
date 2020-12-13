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
#include "GameView.h"
#define sizeField 10

namespace IGamer {
    class IGamer {
    public:
        ~IGamer() = default;
        virtual void setShip(int &shipCount, int &shipSize, int &shipIndex) = 0;
        virtual char** getField() = 0;
        virtual std::map<char, int>getShips() = 0;
        virtual void shipLoop() = 0;
        virtual void shoot(char** &player2) = 0;
    };

    class ConsoleGamer : public IGamer {
    private:
        char **m_field;
        std::map<char, int> ships;
    public:
        ConsoleGamer();
        void shipLoop() override;
        void setShip(int &shipCount, int &shipSize, int &shipIndex)override;
        void shoot(char** &enemy) override;
        char** getField() override;
        std::map<char, int>getShips()override;
        //TODO destructor
    };

    class RandomGamer : public IGamer {
    private:
        char **m_field;
        std::map<char, int> ships;
    public:
        RandomGamer();
        void shipLoop() override;
        void setShip(int &shipCount, int &shipSize, int &shipIndex) override;
        void shoot(char** &enemy) override;
        char** getField() override;
        std::map<char, int>getShips()override;
    };

    class OptimalGamer : public IGamer {
    private:
        char **m_field;
        std::map<char, int> ships;
    public:
        OptimalGamer();
        void shipLoop() override;
        void setShip(int &shipCount, int &shipSize, int &shipIndex)override;
        void shoot(char** &enemy) override;
        char** getField() override;
        std::map<char, int>getShips()override;
    };
}
bool inBound(int &x, int &y);
#endif //SEABATTLE_GAMER_H
