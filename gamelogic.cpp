#include "gamelogic.hpp"


void gamelogic :: operator++(){
    score = score + 3;
}

void gamelogic :: operator--(){
    moves = moves - 1;
}

int gamelogic :: getmove(){
    return moves;
}

int gamelogic :: getscore(){
    return score;
}