//
//  LTexture.cpp
//  WarWithGraphics
//
//  Created by Sean Weiss on 5/29/17.
//  Copyright © 2017 Sean Weiss. All rights reserved.
//

#include <stdio.h>
#include "LTexture.hpp"

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <SDL2_image/SDL_image.h>

#include "SDL_Functions.hpp"

void LTexture::render( int x, int y, SDL_Rect* clip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    
    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    
    //Render to screen
    SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}
