#include"display.h"

void display::OnLoop(){
    game->generateObs();
    game->move();
}