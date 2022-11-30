#include "Candycrush.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>



using namespace std;
const int width = 1000, height = 600;                        // witdth and height for the grid
const int rows = 10, cols = 10;                              // number of rows and columns for candies
int box_width = width/cols;                                  // each candy's width calculated
int box_height = height/rows;                               // each candy's box height calculated



class blue : public Candy{                                  // blue candy inherits publicly from Candy class
    
    sound* z = new sound();                                 // new sound's pointer initialized
    
    public:
    
    blue() {                     //constructor that initializes the type and the srcrect telling which asset to pick
        srcrect = {-1, -1, 128, 128};                        
        type = "blue";
    }
    
    void crush() {                                          // function when the candy is crushed. 
        srcrect = {428 ,1 ,74 ,128};                        // crushed animation candy appeared
        z -> playsound1();                                  // sound played 
    }

    ~blue() {                                               // destructor
        delete z;                                           // frees the data member pointer memory
    }
    
};


class Pink : public Candy {                                 // Pink Candy class publicly inherits from Candy class
    
    sound* z = new sound();                                 // sound pointer kept as a private data member
    
    public:
    
    Pink() {
        srcrect = {201, 189, 128, 128};
        type = "pink";
    }
    
    void crush() {                                          // overloaded function that is partially responsible for crush
        srcrect = {1, 189, 128, 128};                       // crushed animation candy stored in place of the current
        z -> playsound2();                                  // specific sound played during crush
    }
    
    ~Pink() {                                               // destructor made
        delete z;
    }
    
};


class Fish : public Candy {                                 // fish candy inherits publicly from Candy class
    
    sound* z = new sound();                                 // sound data member declared private
    
    public:
    
    Fish() {                       // constructor that initializes the type and the srcrect telling which asset to pick

        srcrect = {401, 377, 128, 128};
        type = "fish";
    }
    
    void crush() {                                         // function when the candy is crushed.        
        srcrect = {220, 377, 90, 128};                     // crushed animation candy appeared
        z -> playsound3();                                 // sound played
    }

    ~Fish() {                                               // destructor
        delete z;                                           // frees the data member pointer
    }
    
};


class egg : public Candy {                                  // egg candy inherits publicly from Candy class
    
    sound* z = new sound();                                 // new sound's pointer data member declared privately
    
    public:
    
    egg() {                   // constructor that initializes the type and the srcrect telling which asset to pick
        srcrect = {201, 1, 128, 128};
        type = "egg";
    }
    
    void crush() {                                          // function when the candy is crushed
        srcrect = {1, 377, 128, 128};                       // animation candy stored
        z -> playsound4();                                  // sound played 
    }

    ~egg() {                                                // destructor
        delete z;                                           // frees the data member pointer
    }

};


// Currently rows and columns are set to 8, however your game implementation should work for any other number

// grid will store characters matrix of rows*cols size, you have to allocate memory to it in initialize function below
Candy** grid = NULL;

// Don't Change: This function is dealing with SDL and currently it's complete. Don't change anything here
// drawOneBlock draws a single candy in a particular block depending on the co-ordinates of rows and columns
void drawOneBlock(SDL_Renderer* renderer, SDL_Texture* texture, int row, int col, Candy* sym){
    int xbox = width / cols;                    // position and number of a single box in terms of x-axis
    int ybox = height / rows;                   // position and number of a single box in terms of y-axis
    SDL_Rect src;
    src = sym->srcrect;                         // candy type's asset stored into that block
    SDL_Rect mov = { xbox * col, ybox * row, xbox - 10, ybox - 10};              // asset drawn into the block
    SDL_RenderCopy(renderer, texture, &src, &mov);                              // rendered
}


void drawBlocks(SDL_Renderer* renderer, SDL_Texture* texture){
    // Call drawOneBlock for all of the blocks of grid
    // for example to draw a snake over block (3, 5) you call it this way:
    // drawOneBlock(renderer, texture, 3, 5, 'S');
    if (grid == NULL) return;
    
    for (int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            drawOneBlock(renderer, texture, i, j, grid[i*cols+j]);
        }   
    }
}


// the swap function makes it possible for the candies to be swapped, both at the front-end and the back-end
void swap(int x, int y, int t, int z){
    int pointx = x / box_width;                         // determines which block is clicked on using the x-y co-ordinates
    int pointy = y / box_height;
    if (abs(t-pointx) <= 1 && abs(z-pointy) <= 1){      // this condition limits the swapping to only the most neighboring candies
        Candy* temp = grid[pointy*cols+pointx];         // temporary storage until swap is done
        grid[pointy*cols+pointx] = grid[z*cols+t];      // data exchanged
        grid[z*cols+t] = temp;
    }
}


bool ended = false;

// this function is responsible for generating the candies at the beginning of the game

void initialize(){
    //Randomly initializes candies all over the grid
    int size = rows * cols;
    grid = new Candy*[size];                           // implement array creation
    
    for (int i = 0 ; i < size; i++) {                  // loop runs till last candy block
        
        int p = rand()%4;                              // an integer randomly generated between 1 and 4
        
        if (p == 1) {                                   // if 1 generated, blue candy made
            grid[i] = new blue();
        }
        else if(p == 2) {
            grid[i] = new Pink();
        }else if(p == 4) {
            grid[i] = new egg();
        }else {
            grid[i] = new Fish();
        }
    }
}




// this function is responsible for generating random candies when candies are crushed
// we will later see why the need was there to create this function
Candy* createrandom() {

    int p = rand()%4;                                       // random integer generated
    
    if (p == 1) {
        Candy* Blue = new blue();
        return Blue;                                        // class returned
    }
    else if(p == 2) {
        Candy* Egg = new egg();
        return Egg;
    }
    else if(p == 3) {
        Candy* fish = new Fish();
        return fish;
    }
    else {
        Candy* pink = new Pink();
        return pink;
    }
}


// the match function makes the matching possible 

void match(bool& flag, gamelogic* count, SDL_Renderer* gRenderer, SDL_Texture* assets) {
    for(int i = 0; i < rows; i++) {                                 // for loop for rows

        for (int j = 0; j < cols; j++) {                                   // for loop for each column of that row
            
            if (i == 0 && j == 0) {                             // condition for the left corner
                // the first IF condition checks for the column-wise 3 matches
                if (grid[i*cols+j] -> type == grid[(i+1)*cols+j]->type && grid[i*cols+j]->type == grid[(i+2)*cols+j]->type){
                    
                    grid[i*cols + j] -> crush();                        // the three candies are crushed
                    grid[(i+1)*cols + j] -> crush();
                    grid[(i+2)*cols + j] -> crush();
                    
                    SDL_RenderClear(gRenderer);                         //SDL functions used to draw the crush candies animation
                    drawBlocks(gRenderer, assets);
                    SDL_RenderPresent(gRenderer);
                    SDL_Delay(200);                                     // Delay for the animation to be visible on the screen
                    
                    grid[i*cols + j] = createrandom();                  // candies randomly created and stored in the column
                    grid[(i+1)*cols + j] = createrandom();
                    grid[(i+2)*cols + j] = createrandom();
                    
                    if (flag == true) {                                 // move counted
                        ++(*count);
                    }
               }
               else if (grid[i*cols+j] -> type == grid[i*cols+(j+1)] -> type && grid[i*cols+j] -> type == grid[i*cols+(j+2)] -> type) {
                // this condition checks for row-wise 3 matches
                    
                    grid[i*cols + j] -> crush();                          // the three candies are crushed
                    grid[i*cols + (j+1)] -> crush();
                    grid[i*cols + (j+2)] -> crush();
                    
                    SDL_RenderClear(gRenderer);                   // SDL functions used to draw the crush candies animation              
                    drawBlocks(gRenderer, assets);
                    SDL_RenderPresent(gRenderer);
                    SDL_Delay(200);                                      // Delay for the animation to be visible on the screen     
                    
                    grid[i*cols + j] = createrandom();                  // candies randomly created and stored in the row
                    grid[i*cols + (j+1)] = createrandom();
                    grid[i*cols + (j+2)] = createrandom();
                    
                    if(flag == true) {
                        ++(*count);                                 // move counted
                    }
               }
            }
            else if (i == 0 && j == cols - 1) {             // condition for mid part of screen except right corner

                if (grid[i*cols+j] -> type == grid[(i+1)*cols+j] -> type && grid[i*cols+j] -> type == grid[(i+2)*cols+j] -> type) {
                    // 3 matching candies in a single column
                    
                    grid[i*cols + j]->crush();              // the three candies are crushed
                    grid[(i+1)*cols + j]->crush();
                    grid[(i+2)*cols + j]->crush();
                    
                    SDL_RenderClear(gRenderer);             // SDL functions used to draw the crush candies animation
                    drawBlocks(gRenderer, assets);
                    SDL_RenderPresent(gRenderer);
                    SDL_Delay(200);                         // Delay for the animation to be visible on the screen
                    
                    grid[i*cols + j] = createrandom();      // candies randomly created and stored in the column
                    grid[(i+1)*cols + j] = createrandom();
                    grid[(i+2)*cols + j] = createrandom();
                    
                    if (flag == true) {
                        ++(*count);                         // move counted
                    }
               }
               else if (grid[i*cols+j]->type == grid[i*cols+(j-1)]->type && grid[i*cols+j]->type == grid[i*cols+(j-2)]->type){
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