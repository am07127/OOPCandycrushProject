#include "Candycrush.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>



using namespace std;
const int width = 1000, height = 600;
const int rows = 10, cols = 10;
int box_width = width/cols;
int box_height = height/rows;



class blue:public Candy{
sound* z = new sound();
public:
    blue(){  //constructor
        srcrect={-1,-1,128,128};
        type="blue";
    }
    
    void crush(){
        srcrect={428,1,74,128};
        z->playsound1();
    }
    ~blue(){
        delete z;
    }
    
};

class Pink:public Candy{
    sound* z = new sound();
    public:
    Pink(){
        srcrect={201,189,128,128};
        type="pink";
    }
    
    void crush(){
        srcrect={1,189,128,128};
        z->playsound2();
    }
    ~Pink(){
        delete z;
    }
    
};
class Fish:public Candy{
    sound* z = new sound();
    public:
    Fish(){
        srcrect={401,377,128,128};
        type="fish";
    }
    
    void crush(){
        srcrect={220,377,90,128};
        z->playsound3();
    }
    ~Fish(){
        delete z;
    }
    
};

class egg:public Candy{
    sound* z = new sound();
    public:
    egg(){
        srcrect={201,1,128,128};
        type="egg";
    }
    
    void crush(){
        srcrect={1,377,128,128};
        z->playsound4();
    }
    ~egg(){
        delete z;
    }
};

// Currently rows and columns are set to 8, however your game implementation should work for any other number

// grid will store characters matrix of rows*cols size, you have to allocate memory to it in initialize function below
Candy** grid = NULL;

// Don't Change: This function is dealing with SDL and currently it's complete. Don't change anything here
void drawOneBlock(SDL_Renderer* renderer, SDL_Texture* texture, int row, int col, Candy* sym){
    int xbox = width/cols;
    int ybox = height/rows;
    SDL_Rect src;
    src=sym->srcrect;
    SDL_Rect mov = { xbox*col, ybox*row, xbox - 10, ybox - 10};
    SDL_RenderCopy(renderer, texture, &src, &mov);
}

void drawBlocks(SDL_Renderer* renderer, SDL_Texture* texture){
    // Call drawOneBlock for all of the blocks of grid
    // for example to draw a snake over block (3, 5) you call it this way:
    // drawOneBlock(renderer, texture, 3, 5, 'S');
    if(grid == NULL) return;
    for(int i=0;i<rows; i++){
        for(int j=0;j<cols; j++){
            drawOneBlock(renderer, texture, i, j, grid[i*cols+j]);
        }   
    }
}


void swap(int x, int y, int t, int z){
    int pointx = x/box_width; 
    int pointy = y/box_height;
    if (abs(t-pointx)<=1 && abs(z-pointy)<=1){
        Candy* temp = grid[pointy*cols+pointx];
        grid[pointy*cols+pointx] = grid[z*cols+t];
        grid[z*cols+t] = temp;
    }
}



bool ended = false;

void initialize(){
    //Randomly initializes candies all over the grid
    int size = rows*cols;
    grid = new Candy*[size];// implement array creation
    for(int i = 0 ; i<size; i++){
        int p = rand()%4;
        if (p==1){
            grid[i] = new blue();
        }else if(p==2){
            grid[i] = new Pink();
        }else if(p==4){
            grid[i] = new egg();
        }else{
            grid[i] = new Fish();
        }
    }
}





Candy* createrandom(){
    int p = rand()%4;
        if (p==1){
            Candy* Blue = new blue();
            return Blue;
        }else if(p==2){
            Candy* Egg = new egg();
            return Egg;
        }else if(p==3){
            Candy* fish = new Fish();
            return fish;
        }else{
            Candy* pink = new Pink();
            return pink;
        }
}

void match(bool& flag, gamelogic* count, SDL_Renderer* gRenderer, SDL_Texture* assets){
    for(int i=0;i<rows; i++){
        for(int j=0;j<cols; j++){
            if (i==0 && j==0){
                if(grid[i*cols+j]->type == grid[(i+1)*cols+j]->type && grid[i*cols+j]->type == grid[(i+2)*cols+j]->type){
                grid[i*cols + j]->crush();
                grid[(i+1)*cols + j]->crush();
                grid[(i+2)*cols + j]->crush();
                SDL_RenderClear(gRenderer);
                drawBlocks(gRenderer, assets);
                SDL_RenderPresent(gRenderer);
                SDL_Delay(200);
                grid[i*cols + j] = createrandom();
                grid[(i+1)*cols + j] = createrandom();
                grid[(i+2)*cols + j] = createrandom();
                if(flag==true){
                    ++(*count);
                }
               }else if(grid[i*cols+j]->type == grid[i*cols+(j+1)]->type && grid[i*cols+j]->type == grid[i*cols+(j+2)]->type){
                grid[i*cols + j]->crush();
                grid[i*cols + (j+1)]->crush();
                grid[i*cols + (j+2)]->crush();
                SDL_RenderClear(gRenderer);
                drawBlocks(gRenderer, assets);
                SDL_RenderPresent(gRenderer);
                SDL_Delay(200);
                grid[i*cols + j] = createrandom();
                grid[i*cols + (j+1)] = createrandom();
                grid[i*cols + (j+2)] = createrandom();
                if(flag==true){
                    ++(*count);
                }
               }
            }else if(i==0 && j==cols-1){
                if(grid[i*cols+j]->type == grid[(i+1)*cols+j]->type && grid[i*cols+j]->type == grid[(i+2)*cols+j]->type){
                grid[i*cols + j]->crush();
                grid[(i+1)*cols + j]->crush();
                grid[(i+2)*cols + j]->crush();
                SDL_RenderClear(gRenderer);
                drawBlocks(gRenderer, assets);
                SDL_RenderPresent(gRenderer);
                SDL_Delay(200);
                grid[i*cols + j] = createrandom();
                grid[(i+1)*cols + j] = createrandom();
                grid[(i+2)*cols + j] = createrandom();
                if(flag==true){
                    ++(*count);
                }
               }else if(grid[i*cols+j]->type == grid[i*cols+(j-1)]->type && grid[i*cols+j]->type == grid[i*cols+(j-2)]->type){
                grid[i*cols + j]->crush();
                grid[i*cols + (j-1)]->crush();
                grid[i*cols + (j-2)]->crush();
                SDL_RenderClear(gRenderer);
                drawBlocks(gRenderer, assets);
                SDL_RenderPresent(gRenderer);
                SDL_Delay(200);
                grid[i*cols + j] = createrandom();
                grid[i*cols + (j-1)] = createrandom();
                grid[i*cols + (j-2)] = createrandom();
                if(flag==true){
                    ++(*count);
                }
               }
            }else if(i==rows-1 && j==0){
                if(grid[i*cols+j]->type == grid[i*cols+(j+1)]->type && grid[i*cols+j]->type == grid[i*cols+(j+2)]->type){
                grid[i*cols + j]->crush();
                grid[i*cols + (j+1)]->crush();
                grid[i*cols + (j+2)]->crush();
                SDL_RenderClear(gRenderer);
                drawBlocks(gRenderer, assets);
                SDL_RenderPresent(gRenderer);
                SDL_Delay(200);
                grid[i*cols + j] = createrandom();
                grid[i*cols + (j+1)] = createrandom();
                grid[i*cols + (j+2)] = createrandom();
                if(flag==true){
                   ++(*count);
                }
               }else if(grid[i*cols+j]->type == grid[(i-1)*cols+j]->type && grid[i*cols+j]->type == grid[(i-2)*cols+j]->type){
                grid[i*cols + j]->crush();
                grid[(i-1)*cols + j]->crush();
                grid[(i-2)*cols + j]->crush();
                SDL_RenderClear(gRenderer);
                drawBlocks(gRenderer, assets);
                SDL_RenderPresent(gRenderer);
                SDL_Delay(200);
                grid[i*cols + j] = createrandom();
                grid[(i-1)*cols + j] = createrandom();
                grid[(i-2)*cols + j] = createrandom();
                if(flag==true){
                    ++(*count);
                }
               }
            }else if(i==rows-1 && j==cols-1){
                if(grid[i*cols+j]->type == grid[i*cols+(j-1)]->type && grid[i*cols+j]->type == grid[i*cols+(j-2)]->type){
                grid[i*cols + j]->crush();
                grid[i*cols + (j-1)]->crush();
                grid[i*cols + (j-2)]->crush();
                SDL_RenderClear(gRenderer);
                drawBlocks(gRenderer, assets);
                SDL_RenderPresent(gRenderer);
                SDL_Delay(200);
                grid[i*cols + j] = createrandom();
                grid[i*cols + (j-1)] = createrandom();
                grid[i*cols + (j-2)] = createrandom();
                if(flag==true){
                    ++(*count);
                }
               }else if(grid[i*cols+j]->type == grid[(i-1)*cols+j]->type && grid[i*cols+j]->type == grid[(i-2)*cols+j]->type){
                grid[i*cols + j]->crush();
                grid[(i-1)*cols + j]->crush();
                grid[(i-2)*cols + j]->crush();
                SDL_RenderClear(gRenderer);
                drawBlocks(gRenderer, assets);
                SDL_RenderPresent(gRenderer);
                SDL_Delay(200);
                grid[i*cols + j] = createrandom();
                grid[(i-1)*cols + j] = createrandom();
                grid[(i-2)*cols + j] = createrandom();
                if(flag==true){
                    ++(*count);
                }
               }
            }else if(i==0){
                if(grid[i*cols+j]->type == grid[(i+1)*cols+j]->type && grid[i*cols+j]->type == grid[(i+2)*cols+j]->type){
                grid[i*cols + j]->crush();
                grid[(i+1)*cols + j]->crush();
                grid[(i+2)*cols + j]->crush();
                SDL_RenderClear(gRenderer);
                drawBlocks(gRenderer, assets);
                SDL_RenderPresent(gRenderer);
                SDL_Delay(200);
                grid[i*cols + j] = createrandom();
                grid[(i+1)*cols + j] = createrandom();
                grid[(i+2)*cols + j] = createrandom();
                if(flag==true){
                   ++(*count);
                }
                }else if(grid[i*cols+j]->type == grid[i*cols+(j+1)]->type && grid[i*cols+j]->type == grid[i*cols+(j-1)]->type){
                grid[i*cols + j]->crush();
                grid[i*cols + (j+1)]->crush();
                grid[i*cols + (j-1)]->crush();
                SDL_RenderClear(gRenderer);
                drawBlocks(gRenderer, assets);
                SDL_RenderPresent(gRenderer);
                SDL_Delay(200);
                grid[i*cols + j] = createrandom();
                grid[i*cols + (j+1)] = createrandom();
                grid[i*cols + (j-1)] = createrandom();
                if(flag==true){
                    ++(*count);
                }
                }
            }else if(i==rows-1){
                if(grid[i*cols+j]->type == grid[(i-1)*cols+j]->type && grid[i*cols+j]->type == grid[(i-2)*cols+j]->type){
                grid[i*cols + j]->crush();
                grid[(i-1)*cols + j]->crush();
                grid[(i-2)*cols + j]->crush();
                SDL_RenderClear(gRenderer);
                drawBlocks(gRenderer, assets);
                SDL_RenderPresent(gRenderer);
                SDL_Delay(200);
                grid[i*cols + j] = createrandom();
                grid[(i-1)*cols + j] = createrandom();
                grid[(i-2)*cols + j] = createrandom();
                if(flag==true){
                    ++(*count);
                }
               }else if(grid[i*cols+j]->type == grid[i*cols+(j+1)]->type && grid[i*cols+j]->type == grid[i*cols+(j-1)]->type){
                grid[i*cols + j]->crush();
                grid[i*cols + (j+1)]->crush();
                grid[i*cols + (j-1)]->crush();
                SDL_RenderClear(gRenderer);
                drawBlocks(gRenderer, assets);
                SDL_RenderPresent(gRenderer);
                SDL_Delay(200);
                grid[i*cols + j] = createrandom();
                grid[i*cols + (j+1)] = createrandom();
                grid[i*cols + (j-1)] = createrandom();
                if(flag==true){
                    ++(*count);
                }
                }
            }else if(j==0){
                if(grid[i*cols+j]->type == grid[i*cols+(j+1)]->type && grid[i*cols+j]->type == grid[i*cols+(j+2)]->type){
                grid[i*cols + j]->crush();
                grid[i*cols + (j+1)]->crush();
                grid[i*cols + (j+2)]->crush();
                SDL_RenderClear(gRenderer);
                drawBlocks(gRenderer, assets);
                SDL_RenderPresent(gRenderer);
                SDL_Delay(200);
                grid[i*cols + j] = createrandom();
                grid[i*cols + (j+1)] = createrandom();
                grid[i*cols + (j+2)] = createrandom();
                if(flag==true){
                    ++(*count);
                }
                }else if(grid[i*cols+j]->type == grid[(i-1)*cols+j]->type && grid[i*cols+j]->type == grid[(i+1)*cols+j]->type){
                grid[i*cols + j]->crush();
                grid[(i-1)*cols + j]->crush();
                grid[(i+1)*cols + j]->crush();
                SDL_RenderClear(gRenderer);
                drawBlocks(gRenderer, assets);
                SDL_RenderPresent(gRenderer);
                SDL_Delay(200);
                grid[i*cols + j] = createrandom();
                grid[(i-1)*cols + j] = createrandom();
                grid[(i+1)*cols + j] = createrandom();
                if(flag==true){
                    ++(*count);
                }
                }
            }else if(j==cols-1){
                if(grid[i*cols+j]->type == grid[(i-1)*cols+j]->type && grid[i*cols+j]->type == grid[(i+1)*cols+j]->type){
                grid[i*cols + j]->crush();
                grid[(i-1)*cols + j]->crush();
                grid[(i+1)*cols + j]->crush();
                SDL_RenderClear(gRenderer);
                drawBlocks(gRenderer, assets);
                SDL_RenderPresent(gRenderer);
                SDL_Delay(200);
                grid[i*cols + j] = createrandom();
                grid[(i-1)*cols + j] = createrandom();
                grid[(i+1)*cols + j] = createrandom();
                if(flag==true){
                    ++(*count);
                }
                }else if(grid[i*cols+j]->type == grid[i*cols+(j-1)]->type && grid[i*cols+j]->type == grid[i*cols+(j-2)]->type){
                grid[i*cols + j]->crush();
                grid[i*cols + (j-1)]->crush();
                grid[i*cols + (j-2)]->crush();
                SDL_RenderClear(gRenderer);
                drawBlocks(gRenderer, assets);
                SDL_RenderPresent(gRenderer);
                SDL_Delay(200);
                grid[i*cols + j] = createrandom();
                grid[i*cols + (j-1)] = createrandom();
                grid[i*cols + (j-2)] = createrandom();
                if(flag==true){
                    ++(*count);
                }
                }
            }else{
                if(grid[i*cols+j]->type == grid[(i-1)*cols+j]->type && grid[i*cols+j]->type == grid[(i+1)*cols+j]->type){
                grid[i*cols + j]->crush();
                grid[(i-1)*cols + j]->crush();
                grid[(i+1)*cols + j]->crush();
                SDL_RenderClear(gRenderer);
                drawBlocks(gRenderer, assets);
                SDL_RenderPresent(gRenderer);
                SDL_Delay(200);
                grid[i*cols + j] = createrandom();
                grid[(i-1)*cols + j] = createrandom();
                grid[(i+1)*cols + j] = createrandom();
                if(flag==true){
                   ++(*count);
                }
                }else if(grid[i*cols+j]->type == grid[i*cols+(j+1)]->type && grid[i*cols+j]->type == grid[i*cols+(j-1)]->type){
                grid[i*cols + j]->crush();
                grid[i*cols + (j+1)]->crush();
                grid[i*cols + (j-1)]->crush();
                SDL_RenderClear(gRenderer);
                drawBlocks(gRenderer, assets);
                SDL_RenderPresent(gRenderer);
                SDL_Delay(200);
                grid[i*cols + j] = createrandom();
                grid[i*cols + (j+1)] = createrandom();
                grid[i*cols + (j-1)] = createrandom();
                if(flag==true){
                    ++(*count);
                }
                }
            }
        }   
    }
}



void quitgrid(){
    for(int i=0;i<rows; i++){
        for(int j=0;j<cols; j++){
            delete grid[i*cols+j];
        }   
    }
    delete [] grid;

}