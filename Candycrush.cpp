#include "Candycrush.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>


using namespace std;
const int width = 1000, height = 600;
class Candy{
    public:
    SDL_Rect srcrect;
    string type;
    //static bool flag;
    //static int count;
    Candy(){

    }
     /*
     void crush(SDL_Renderer* renderer, SDL_Texture* texture, int row, int col){
        int xbox = width/col;
        int ybox = height/row;
        SDL_Rect mov = { xbox*col, ybox*row, xbox - 10, ybox - 10};
        SDL_RenderClear(renderer);
        for(int i=0;i<10;i++){
            if(i==0){
                srcrect={67,23,86,90};
                SDL_RenderCopy(renderer, texture, &srcrect, &mov);
                SDL_RenderPresent(renderer); //displays the updated render
                 SDL_Delay(5);
            }else if(i==1){
                srcrect={319,16,89,97};
                SDL_RenderCopy(renderer, texture, &srcrect, &mov);
                SDL_RenderPresent(renderer); //displays the updated renderer
                 SDL_Delay(5);
            }else if(i==2){
                srcrect={574,16,92,104};
                SDL_RenderCopy(renderer, texture, &srcrect, &mov);
                SDL_RenderPresent(renderer); //displays the updated renderer
                 SDL_Delay(5);
            }else if(i==3){
                srcrect={827,15,98,110};
                SDL_RenderCopy(renderer, texture, &srcrect, &mov);
                SDL_RenderPresent(renderer); //displays the updated renderer
                 SDL_Delay(5);
            }else if(i==4){
                srcrect={1079,12,107,114};
                SDL_RenderCopy(renderer, texture, &srcrect, &mov);
                SDL_RenderPresent(renderer); //displays the updated renderer
                 SDL_Delay(5);
            }else if(i==5){
                srcrect={41,257,133,133};
                SDL_RenderCopy(renderer, texture, &srcrect, &mov);
                SDL_RenderPresent(renderer); //displays the updated renderer
                 SDL_Delay(5);
            }else if(i==6){
                srcrect={294,255,139,137};
                SDL_RenderCopy(renderer, texture, &srcrect, &mov);
                SDL_RenderPresent(renderer); //displays the updated renderer
                 SDL_Delay(5);
            }else if(i==7){
                srcrect={547,254,145,142};
                SDL_RenderCopy(renderer, texture, &srcrect, &mov);
                SDL_RenderPresent(renderer); //displays the updated renderer
                 SDL_Delay(5);
            }else if(i==8){
                srcrect={799,252,152,147};
                SDL_RenderCopy(renderer, texture, &srcrect, &mov);
                SDL_RenderPresent(renderer); //displays the updated rendere
                 SDL_Delay(5);
            }else if(i==9){
                srcrect={1052,249,157,152};
                SDL_RenderCopy(renderer, texture, &srcrect, &mov);
                SDL_RenderPresent(renderer); //displays the updated renderer
                 SDL_Delay(5);
            }
        }
        */
        virtual void crush(){
           srcrect={401,189,128,128};
    }
    
};

class blue:public Candy{
public:
    blue(){  //constructor
        srcrect={-1,-1,128,128};
        type="blue";
    }
    
    void crush(){
        srcrect={428,1,74,128};
    }
    
};

class Pink:public Candy{
    public:
    Pink(){
        srcrect={201,189,128,128};
        type="pink";
    }
    
    void crush(){
        srcrect={1,189,128,128};
    }
    
};
class Fish:public Candy{
    public:
    Fish(){
        srcrect={401,377,128,128};
        type="fish";
    }
    
    void crush(){
        srcrect={220,377,90,128};
    }
    
};

class egg:public Candy{
    public:
    egg(){
        srcrect={201,1,128,128};
        type="egg";
    }
    
    void crush(){
        srcrect={1,377,128,128};
    }
    
};

// Currently rows and columns are set to 8, however your game implementation should work for any other number
const int rows = 10, cols = 10;

// grid will store characters matrix of rows*cols size, you have to allocate memory to it in initialize function below
Candy** grid = NULL;

//int Candy :: count = 0;
//bool Candy :: flag = false;
// *****************************************************************************************************
// No change zone: Don't change anything until the next stars line
// *****************************************************************************************************

// Don't Change it: Screen width and height values

int box_width = width/cols;
int box_height = height/rows;

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



void pos :: set_pos(int X,int Y){
        x=X/box_width;
        y=Y/box_height;
}

int pos :: get_x(){
        return x;
}
int pos :: get_y(){
        return y;
}

void swap(int x, int y, int t, int z){
    //Candy* temp = grid[1*cols+0];
    //grid[1*cols+0] = grid[0*cols+0];
    //grid[0*cols+0] = temp;
    int pointx = x/box_width; 
    int pointy = y/box_height;
    if (abs(t-pointx)<=1 && abs(z-pointy)<=1){
        Candy* temp = grid[pointy*cols+pointx];
        grid[pointy*cols+pointx] = grid[z*cols+t];
        grid[z*cols+t] = temp;
    }
}



// *****************************************************************************************************
// No change zone ends here
// *****************************************************************************************************



// To Do zone: 

bool ended = false;

void initialize(){
    //Randomly initializes candies all over the grid
    int size = rows*cols;
    grid = new Candy*[size];// implement array creation
    for(int i = 0 ; i<size; i++){
        int p = rand()%3;
        if (p==1){
            grid[i] = new blue();
        }else if(p==2){
            grid[i] = new Pink();
        }else{
            grid[i] = new Fish();
        }
    }
    

    /*
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            int p = rand()%3;
        }
    }
    */

    // generate two random numbers and store in ghostRow and ghostCol variables


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
                grid[i*cols + j] = createrandom();
                grid[(i+1)*cols + j] = createrandom();
                grid[(i+2)*cols + j] = createrandom();
                if(flag==true){
                    ++(*count);
                }
               }else if(grid[i*cols+j]->type == grid[i*cols+(j+1)]->type && grid[i*cols+j]->type == grid[i*cols+(j+2)]->type){
                grid[i*cols + j] = createrandom();
                grid[i*cols + (j+1)] = createrandom();
                grid[i*cols + (j+2)] = createrandom();
                if(flag==true){
                    ++(*count);
                }
               }
            }else if(i==0 && j==cols-1){
                if(grid[i*cols+j]->type == grid[(i+1)*cols+j]->type && grid[i*cols+j]->type == grid[(i+2)*cols+j]->type){
                grid[i*cols + j] = createrandom();
                grid[(i+1)*cols + j] = createrandom();
                grid[(i+2)*cols + j] = createrandom();
                if(flag==true){
                    ++(*count);
                }
               }else if(grid[i*cols+j]->type == grid[i*cols+(j-1)]->type && grid[i*cols+j]->type == grid[i*cols+(j-2)]->type){
                grid[i*cols + j] = createrandom();
                grid[i*cols + (j-1)] = createrandom();
                grid[i*cols + (j-2)] = createrandom();
                if(flag==true){
                    ++(*count);
                }
               }
            }else if(i==rows-1 && j==0){
                if(grid[i*cols+j]->type == grid[i*cols+(j+1)]->type && grid[i*cols+j]->type == grid[i*cols+(j+2)]->type){
                grid[i*cols + j] = createrandom();
                grid[i*cols + (j+1)] = createrandom();
                grid[i*cols + (j+2)] = createrandom();
                if(flag==true){
                   ++(*count);
                }
               }else if(grid[i*cols+j]->type == grid[(i-1)*cols+j]->type && grid[i*cols+j]->type == grid[(i-2)*cols+j]->type){
                grid[i*cols + j] = createrandom();
                grid[(i-1)*cols + j] = createrandom();
                grid[(i-2)*cols + j] = createrandom();
                if(flag==true){
                    ++(*count);
                }
               }
            }else if(i==rows-1 && j==cols-1){
                if(grid[i*cols+j]->type == grid[i*cols+(j-1)]->type && grid[i*cols+j]->type == grid[i*cols+(j-2)]->type){
                grid[i*cols + j] = createrandom();
                grid[i*cols + (j-1)] = createrandom();
                grid[i*cols + (j-2)] = createrandom();
                if(flag==true){
                    ++(*count);
                }
               }else if(grid[i*cols+j]->type == grid[(i-1)*cols+j]->type && grid[i*cols+j]->type == grid[(i-2)*cols+j]->type){
                grid[i*cols + j] = createrandom();
                grid[(i-1)*cols + j] = createrandom();
                grid[(i-2)*cols + j] = createrandom();
                if(flag==true){
                    ++(*count);
                }
               }
            }else if(i==0){
                if(grid[i*cols+j]->type == grid[(i+1)*cols+j]->type && grid[i*cols+j]->type == grid[(i+2)*cols+j]->type){
                grid[i*cols + j] = createrandom();
                grid[(i+1)*cols + j] = createrandom();
                grid[(i+2)*cols + j] = createrandom();
                if(flag==true){
                   ++(*count);
                }
                }else if(grid[i*cols+j]->type == grid[i*cols+(j+1)]->type && grid[i*cols+j]->type == grid[i*cols+(j-1)]->type){
                grid[i*cols + j] = createrandom();
                grid[i*cols + (j+1)] = createrandom();
                grid[i*cols + (j-1)] = createrandom();
                if(flag==true){
                    ++(*count);
                }
                }
            }else if(i==rows-1){
                if(grid[i*cols+j]->type == grid[(i-1)*cols+j]->type && grid[i*cols+j]->type == grid[(i-2)*cols+j]->type){
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