#include<SDL.h>

//singleton design pattern implemented here
class gamelogic{
      private:
         int score;
         int moves;
         static gamelogic* instance;
         gamelogic(){
            score=0;
            moves=10;
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


void initialize();

void drawBlocks(SDL_Renderer*, SDL_Texture*);


void swap(int x, int y, int t, int z);

void drawOneBlock(SDL_Renderer* renderer, SDL_Texture*, int row, int col, char sym);

void quitgrid();

void match(bool& flag, gamelogic* count, SDL_Renderer* gRenderer, SDL_Texture* assets);

//int count=0;

class pos{
    public:
       int x;
       int y;
    pos(){
       x=0;
       y=0;
    };
    void set_pos(int X,int Y);

    int get_x();

    int get_y();

};

/*
class flag{
   private:
      bool value;
   public:
      flag(){};
      void set_bool(bool x){
         value = x;
      }
      bool get_value(){
         return value;
      }
};
*/

