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

//---------------------------------------------------------//

class LTexture{

public:

    LTexture();

    ~LTexture();

    void setRender(SDL_Renderer* ren);

    bool loadFromFile(std::string path);

    void loadFont(TTF_Font* font);

    bool loadFromRendererText(std::string textureText, SDL_Color textColor);

    void free();

    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    void setBlendMode(SDL_BlendMode blending);

    void setAlpha(Uint8 alpha);

    void render( int x, int y, SDL_Rect* clip = NULL);

    int getWidth();
    int getHeight();

private:

    SDL_Texture* mTexture;
    TTF_Font* mFont;

    int mWidth;
    int mHeight;

    SDL_Renderer* mRenderer;

};

//---------------------------------------------------------//

LTexture::LTexture(){

    mTexture = NULL;
    mFont == NULL;
    mWidth = 0;
    mHeight = 0;
    mRenderer = NULL;

}
//---------------------------------------------------------//
LTexture::~LTexture(){

    free();

}
//---------------------------------------------------------//
void LTexture::setRender(SDL_Renderer* ren){

    mRenderer = ren;

}
//---------------------------------------------------------//
bool LTexture::loadFromFile(std::string path){

    free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if(loadedSurface == NULL){

        printf("loadFromFile messed up: %s\n", IMG_GetError());

    }
    else{

        newTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);

        if(newTexture == NULL){

            printf("TextureFromSurface messed up: %s\n", SDL_GetError());

        }
        else{

            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;

        }

        SDL_FreeSurface(loadedSurface);

    }

    mTexture = newTexture;

    return mTexture != NULL;

}
//---------------------------------------------------------//
void LTexture::loadFont(TTF_Font* font){

    mFont = font;

}
//---------------------------------------------------------//
bool LTexture::loadFromRendererText(std::string textureText, SDL_Color textColor){

    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid( mFont, textureText.c_str(), textColor);

    if(textSurface == NULL){

        printf("Text Surface messed up: %s\n", TTF_GetError());

    }
    else{

        mTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);

        if(mTexture == NULL){

            printf("Rendered Text messed up: %s\n", SDL_GetError());

        }
        else{

            mWidth = textSurface->w;
            mHeight = textSurface->h;

        }

        SDL_FreeSurface(textSurface);

    }

    return mTexture != NULL;

}
//---------------------------------------------------------//
void LTexture::free(){

    if(mTexture != NULL){

        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;

    }

}
//---------------------------------------------------------//
void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue){

	SDL_SetTextureColorMod(mTexture, red, green, blue);

}
//---------------------------------------------------------//
void LTexture::setBlendMode(SDL_BlendMode blending){

	SDL_SetTextureBlendMode(mTexture, blending);

}
//---------------------------------------------------------//
void LTexture::setAlpha(Uint8 alpha){

	SDL_SetTextureAlphaMod(mTexture, alpha);

}
//---------------------------------------------------------//
void LTexture::render( int x, int y, SDL_Rect* clip){

    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    if(clip != NULL){

        renderQuad.w = clip->w;
        renderQuad.h = clip->h;

    }

    SDL_RenderCopy(mRenderer, mTexture, clip, &renderQuad);

}
//---------------------------------------------------------//
int LTexture::getWidth(){

    return mWidth;

}
//---------------------------------------------------------//
int LTexture::getHeight(){

    return mHeight;

}
//=====================================================
