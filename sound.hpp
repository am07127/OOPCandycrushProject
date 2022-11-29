#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#pragma once

using namespace std;

class sound{
     Mix_Chunk*gMusic = NULL;
     Mix_Chunk*tmusic = NULL;
     Mix_Chunk*pmusic = NULL;
     Mix_Chunk*lmusic = NULL;
     Mix_Music*losemus = NULL;
     Mix_Music*winmus = NULL;
    public:
      bool success;
      sound(){
        if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 ){
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
        }
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
        bool success = true;
        gMusic = Mix_LoadWAV( "mixkit-air-zoom-vacuum-2608.wav" );
        tmusic = Mix_LoadWAV("candysound2.wav");
        pmusic = Mix_LoadWAV("candysound3.wav");
        lmusic = Mix_LoadWAV("candysound4.wav");
        losemus = Mix_LoadMUS("losesound.wav");
        winmus = Mix_LoadMUS("winsound.wav");
    if( gMusic == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    }
    void playsound1(){
        Mix_PlayChannel(-1,gMusic,0);
    }
    void playsound2(){
        Mix_PlayChannel(-1,tmusic,0);
    }
    void playsound3(){
        Mix_PlayChannel(-1,pmusic,0);
    }
    void playsound4(){
        Mix_PlayChannel(-1,lmusic,0);
    }
    void losesound(){
        Mix_PlayMusic(losemus,-1);
    }
    void winsound(){
        Mix_PlayMusic(winmus,-1);
    }
};
