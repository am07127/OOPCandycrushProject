#include<SDL.h>
#include <stdio.h>
#include <string>
#include <SDL_image.h>
#include<SDL_mixer.h>
#pragma once

//singleton design pattern implemented here
class gamelogic{
      private:
         int score;
         int moves;
         static gamelogic* instance;
         gamelogic(){
            score=0;
            moves=20;
         };
      public:
         static gamelogic* getinstance(){
            if(!instance){
               instance = new gamelogic();
               return instance;
            }
         }

         void operator++();

         void operator--();

         int getscore();

         int getmove();

         ~gamelogic(){
            
         }
};