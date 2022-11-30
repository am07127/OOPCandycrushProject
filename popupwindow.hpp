#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <SDL_ttf.h>
#include "sound.hpp"
#pragma once
using namespace std;

class popupwindow {

    sound* z = new sound();
    
    public:
        popupwindow() {         // constructor made   
        }
        
        int makewindow(bool x);
        
        ~popupwindow() {        // destructor made
            delete z;
        }
};