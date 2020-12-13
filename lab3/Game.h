#ifndef SEABATTLE_GAME_H
#define SEABATTLE_GAME_H
#include "GameView.h"
#include "Gamer.h"


void playGame(std::shared_ptr<IGamer::IGamer> &player1, std::shared_ptr<IGamer::IGamer> &player2, int &rounds);


#endif //SEABATTLE_GAME_H
