#include<SDL.h>
#include <stdio.h>
#include <string>
#include <SDL_image.h>
#include<SDL_mixer.h>
#include "gamelogic.hpp"
#include "pos.hpp"
#include "sound.hpp"
#pragma once


class Candy{
    public:
    SDL_Rect srcrect;
    string type;
    Candy(){

    }
        virtual void crush(){
           srcrect={401,189,128,128};
    }
    ~Candy(){

    }
    
};


void initialize();

void drawBlocks(SDL_Renderer*, SDL_Texture*);


void swap(int x, int y, int t, int z);

void drawOneBlock(SDL_Renderer* renderer, SDL_Texture*, int row, int col, char sym);

void quitgrid();

void match(bool& flag, gamelogic* count, SDL_Renderer* gRenderer, SDL_Texture* assets);

//int count=0;





