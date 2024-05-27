//
// Hobby Project
// "The Edge"
// For my DnD campaign 
//
// PiaPsyker - 2024
//

//---------------------------------------------------------//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <thread>
#include <chrono>

#include "LTexture.h"

//---------------------------------------------------------//

using namespace std::this_thread;
using namespace std::chrono_literals;

//---------------------------------------------------------//

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int pdir = 0;
int px = 0;
int py = 0;

//---------------------------------------------------------//

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

//---------------------------------------------------------//



//---------------------------------------------------------//

SDL_Rect gSpriteClip[12];
LTexture gPlayerTexture;
LTexture gBGTexture;

//---------------------------------------------------------//

bool init(){

    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {

        printf("SDL could not initalize");
        success = false;

    }
    else {

        gWindow = SDL_CreateWindow( "-=-The Edge-=-", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if( gWindow == NULL) {

            printf("Window  messed up");
            success = false;

        }
        else{

            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(gRenderer == NULL){

                printf("Renderer messed up");
                success = false;

            }
            else{

                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags)){

                    printf("Image messed up");
                    success = false;

                }
                else{

                    gPlayerTexture.setRender(gRenderer);
                    gBGTexture.setRender(gRenderer);

                }
            }
        }

    return success;

    }
}

//---------------------------------------------------------//

bool loadMedia(){

    bool success = true;

    if(!gPlayerTexture.loadFromFile("sheet.png")){

        printf("File Loading messed up");
        success = false;

    }

    else{

        //DOWN-----------------------------------------------------//

        gSpriteClip[0].x = 48; // First Frame
        gSpriteClip[0].y = 0;
        gSpriteClip[0].w = 48;
        gSpriteClip[0].h = 48;

        gSpriteClip[1].x = 0; // Second Frame
        gSpriteClip[1].y = 0;
        gSpriteClip[1].w = 48;
        gSpriteClip[1].h = 48;

        gSpriteClip[2].x = 96; // Third Frame
        gSpriteClip[2].y = 0;
        gSpriteClip[2].w = 48;
        gSpriteClip[2].h = 48;

        //LEFT-----------------------------------------------------//

        gSpriteClip[3].x = 48;
        gSpriteClip[3].y = 48;
        gSpriteClip[3].w = 48;
        gSpriteClip[3].h = 48;

        gSpriteClip[4].x = 0;
        gSpriteClip[4].y = 48;
        gSpriteClip[4].w = 48;
        gSpriteClip[4].h = 48;

        gSpriteClip[5].x = 96;
        gSpriteClip[5].y = 48;
        gSpriteClip[5].w = 48;
        gSpriteClip[5].h = 48;

        //RIGHT----------------------------------------------------//

        gSpriteClip[6].x = 48;
        gSpriteClip[6].y = 96;
        gSpriteClip[6].w = 48;
        gSpriteClip[6].h = 48;

        gSpriteClip[7].x = 0;
        gSpriteClip[7].y = 96;
        gSpriteClip[7].w = 48;
        gSpriteClip[7].h = 48;

        gSpriteClip[8].x = 96;
        gSpriteClip[8].y = 96;
        gSpriteClip[8].w = 48;
        gSpriteClip[8].h = 48;

        //UP-------------------------------------------------------//

        gSpriteClip[9].x = 48;
        gSpriteClip[9].y = 144;
        gSpriteClip[9].w = 48;
        gSpriteClip[9].h = 48;

        gSpriteClip[10].x = 0;
        gSpriteClip[10].y = 144;
        gSpriteClip[10].w = 48;
        gSpriteClip[10].h = 48;

        gSpriteClip[11].x = 96;
        gSpriteClip[11].y = 144;
        gSpriteClip[11].w = 48;
        gSpriteClip[11].h = 48;

    }

    if(!gBGTexture.loadFromFile("bg_universe.png")){

        printf("Loading Image messed up");
        success = false;

    }

    return success;
}
//---------------------------------------------------------//

void close(){

    gPlayerTexture.free();
    gBGTexture.free();

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();

}

//---------------------------------------------------------//
//---------------------------------------------------------//

int main( int argc, char* args[] ) {

    if( !init() ){

        printf("Init messed up");

    }
    else{

        if(!loadMedia()){

            printf("Media messed up");

        }
        else{

            bool quit = false;

            SDL_Event e;

            int frame = 0;
            int anim = -1;

            while(!quit){

                while(SDL_PollEvent(&e) != 0){

                    if(e.type == SDL_QUIT){

                        quit = true;

                    }
                    else if(e.type == SDL_KEYDOWN && anim == -1){
                        switch(e.key.keysym.sym){
                        case SDLK_UP:
                            py -= 48;
                            pdir = 3;
                            anim = 0;
                            break;
                        case SDLK_DOWN:
                            py += 48;
                            pdir = 0;
                            anim = 0;
                            break;
                        case SDLK_LEFT:
                            px -= 48;
                            pdir = 1;
                            anim = 0;
                            break;
                        case SDLK_RIGHT:
                            px += 48;
                            pdir = 2;
                            anim = 0;
                            break;
                        }
                    }                   
                }

                SDL_RenderClear(gRenderer);

                gBGTexture.render(0,0);

                SDL_Rect* currentClip = &gSpriteClip[(pdir*3) + frame];

                gPlayerTexture.render(px,py, currentClip);

                SDL_RenderPresent(gRenderer);

                // TODO proper animation timing

                if(anim > -1){
                    frame++;
                    anim++;

                    if(frame == 2){
                        frame = 0;
                    }
                    if(anim == 2){
                        anim = -1;
                    }
                    
                }

                sleep_for(200ms);

            }
        }
    }

    close();

    return 0;

}

//---------------------------------------------------------//