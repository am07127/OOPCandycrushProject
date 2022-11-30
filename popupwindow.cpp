#include "popupwindow.hpp"

SDL_Texture* LoadTexture( std::string path, SDL_Renderer * renderer )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if ( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

int popupwindow :: makewindow(bool x){
    if (x == false) {
        z->losesound();
    }
    else {
        z->winsound();
    }
	
    bool quit = false;
    SDL_Event e;
 
    SDL_Init(SDL_INIT_VIDEO);
    
 
    SDL_Window * window = SDL_CreateWindow("Game Over",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640,
        480, 0);

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture * background = LoadTexture("newbg.jpg",renderer);
    SDL_Texture * pic = LoadTexture("status.png",renderer);
    SDL_Texture * pic2 = LoadTexture("status2.png",renderer);
    SDL_Rect src = {1,1,540,400};
    
    if (x == false) {
        src = {134,195,932,461};
    }
    SDL_Rect mov = {100,100,256,256};
    
 
    while (!quit)
    {
        SDL_WaitEvent(&e);
 
        if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE)
        {
            quit = true;
                
        }

        SDL_RenderClear(renderer); 
		SDL_RenderCopy(renderer, background, NULL, NULL);
        
        if (x == true) { 
            SDL_RenderCopy(renderer,pic,&src,&mov);
        }
        else {
            SDL_RenderCopy(renderer,pic2,&src,&mov);
        }
        
    	SDL_RenderPresent(renderer); //displays the updated renderer

      
    }
    cout<<"Exited the loop"<<endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
