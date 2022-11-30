#include "gamelogic.hpp"

// operator overloading done
void gamelogic :: operator++(){
    score = score + 3;
}

void gamelogic :: operator--(){
    moves = moves - 1;
}

// getter
int gamelogic :: getmove(){
    return moves;
}

// getter for score
int gamelogic :: getscore(){
    return score;
}