//
//  SDL_Functions.cpp
//  WarWithGraphics
//
//  Created by Sean Weiss on 5/29/17.
//  Copyright © 2017 Sean Weiss. All rights reserved.
//

#include <iostream>
#include "cardDeck.hpp"
#include "War.hpp"
#include <ctime>        // std::time
#include <cstdlib>
#include <math.h>


//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "SDL_Functions.hpp"


#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int CARD_WIDTH = 208;
const int CARD_HEIGHT = 303;

extern const double PLAYER_1_LOCATION_SCALE_HEIGHT = 0.66;
extern const double PLAYER_2_LOCATION_SCALE_HEIGHT = 0.20;
extern const double PLAYER_LOCATION_SCALE_WIDTH = 0.66;

extern const int ANIMATION_RATE = 15;

// The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

// The image we will load and show on the screen
SDL_Texture* gGameBackground = NULL;



// Loads individual image
SDL_Texture* loadTexture( std::string path );

// The images that correspond to a keyPress
SDL_Texture* gCurrentSurface = NULL;

// The deck sprite sheet that holds the card images
SDL_Texture* gDeckSpriteSheet = NULL;

//The images that correspond to a keypress
SDL_Texture* gDeckCardImages[ 52 ];

// stores the locations of each card in the sprite sheets
SDL_Rect gSpriteClips[ 54 ];


//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;


//The music that will be played
Mix_Music *gMusic = NULL;

//The sound effects that will be used
Mix_Chunk *gWin = NULL;
Mix_Chunk *gLose = NULL;
Mix_Chunk *gShuffle = NULL;
Mix_Chunk *gWar = NULL;


// Globally used font
TTF_Font *gFont = NULL;


// Rendered text texture
SDL_Texture* gText_Texture = NULL;

// text texture for the number in deck
SDL_Texture* gNumText_Texture;

// Rect for the location of the text for player 1 deck count
SDL_Rect textLocation = { 20, SCREEN_HEIGHT - 50, NULL, 50 };
// location where deck size will be updated. **120 should be changed
SDL_Rect deckNumTextLocation = { 120, SCREEN_HEIGHT - 50, NULL, 50};


/* ********************  init   ******************** */


bool init()
{
    // Initialization flag
    bool success = true;
    
    // Initiailize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Create window
        gWindow = SDL_CreateWindow("WAR", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
                else
                {
                    //Initialize SDL_mixer
                    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                    {
                        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                        success = false;
                    }
                    else
                    {
                        //Initialize SDL_ttf
                        if( TTF_Init() == -1 )
                        {
                            printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                            success = false;
                        }
                        else
                        {
                            // Get window surface
                            gScreenSurface = SDL_GetWindowSurface( gWindow );
                        }
                    }
                }
            }
            
        }
    }
        return success;
}

/* ********************  loadMedia   ******************** */


bool loadMedia()
{
    // Loading success flag
    bool success = true;
    
    // Load default background
    gGameBackground = loadTexture( "ImageFiles/Table.jpg" );
    if ( gGameBackground == NULL )
    {
        printf( "Failed to load default image!\n" );
        success = false;
    }
    
    // Load in each sprite sheet and then each individual image
    // 6 is the number of sprite sheets we have

        gDeckSpriteSheet = loadTexture( "ImageFiles/PlayingDeckSpriteSheet-0.png" );
        if ( gDeckSpriteSheet == NULL )
        {
            printf( "Failed to load default image!\n" );
            success = false;
        }
        else
        {
            for ( int i = 0; i < 6; i++ )
            {
                for ( int j = 0; j < 9; j++ )
                {
                    gSpriteClips[ j + ( i * 9 ) ].x =  CARD_WIDTH * j ;
                    gSpriteClips[ j + ( i * 9 ) ].y = CARD_HEIGHT * i;
                    gSpriteClips[ j + ( i * 9 ) ].w = CARD_WIDTH;
                    gSpriteClips[ j + ( i * 9 ) ].h = CARD_HEIGHT;
                }
            }
        
    }
    
    // Load music
    gMusic = Mix_LoadMUS( "SoundFiles/Castlevania.wav" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    //Load sound effects
    gWin = Mix_LoadWAV( "SoundFiles/CardSounds/Passturn2.wav" );
    if( gWin == NULL )
    {
        printf( "Failed to load Win sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    //Load sound effects
    gLose = Mix_LoadWAV( "SoundFiles/CardSounds/error2.wav" );
    if( gLose == NULL )
    {
        printf( "Failed to load Lose sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    //Load sound effects
    gShuffle = Mix_LoadWAV( "SoundFiles/CardSounds/shuffle.wav" );
    if( gShuffle == NULL )
    {
        printf( "Failed to load Shuffle sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    //Load sound effects
    gWar = Mix_LoadWAV( "SoundFiles/CardSounds/WAR.wav" );
    if( gWar == NULL )
    {
        printf( "Failed to load WAR sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    //Open the font
    gFont = TTF_OpenFont( "ImageFiles/FontFiles/Top Secret Stamp.ttf", 28 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        // **This text will remain the same the whole game
        //Render text
        SDL_Color textColor = { 0, 0, 0 };
        
        gText_Texture = loadFromRenderedText("Player 1 Deck:  ", textColor ) ;
        if( !gText_Texture)
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
    }
    
    return success;
}

/* ********************  close   ******************** */

void close()
{
    
    //Free loaded images
 //   gDeckSpriteSheet.free();
    
    TTF_CloseFont( gFont );
    
    //Free the sound effects
    Mix_FreeChunk( gWin );
    Mix_FreeChunk( gLose );
    Mix_FreeChunk( gShuffle );
    gWin = NULL;
    gLose = NULL;
    gShuffle = NULL;
    
    //Free the music
    Mix_FreeMusic( gMusic );
    gMusic = NULL;
    
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    
    //Quit SDL subsystems
    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
}

/* ********************  loadSurface   ******************** */

SDL_Texture* loadTexture( std::string path )
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
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    
    return newTexture;
}

void render( int x, int y, SDL_Rect* clip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, static_cast<int>(CARD_WIDTH / 2.5), static_cast<int>(CARD_HEIGHT / 2.5) };

    //Render to screen
    /* 1. gRenderer is a global renderer object
         2. gDeckSpriteSheet is our entire sprite sheet as a texture pointer object
         3. "clip" is the specific box in the sprite sheet where the image we want exists.
         4. renderQuad is holds the x and y values for where to place the image on the display,
         as well as the size of the image to display */
    SDL_RenderCopy( gRenderer, gDeckSpriteSheet, clip, &renderQuad );
}

SDL_Texture* loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    //Get rid of preexisting texture
    SDL_DestroyTexture( gText_Texture );
    gText_Texture = NULL;
    
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        gText_Texture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( gText_Texture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        
        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    
    //Return success
    return gText_Texture;
}

/* Similar to loadFromRenderedText but takes in a paramter of an SDL texture */
SDL_Texture* loadTextFromRenderedText( std::string textureText, SDL_Color textColor, SDL_Texture* textTexture )
{
    //Get rid of preexisting texture
    SDL_DestroyTexture( textTexture );
    textTexture = NULL;
    
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        textTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( textTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        
        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    
    //Return success
    return textTexture;
}

// ******************** Playing with bezier curves **********************



void getCubicBezierCurve( Points p0, Points p1, Points p2, float t, int numPointsOnCurve, vector<Points> &array )
{
    float tTemp = t;
    for ( int i = 0; i < numPointsOnCurve; i++ )
    {
        
        Points temp(0, 0);
        
        temp.x = ( ( pow(1-tTemp, 2) * p0.x ) + ( 2 * (1-tTemp) * tTemp * p1.x ) + ( pow( tTemp, 2 ) * p2.x ) );
        temp.y = ( pow(1-tTemp, 2) * p0.y ) + ( 2 * (1-tTemp) * tTemp * p1.y ) + ( pow( tTemp, 2 ) * p2.y );
        
        temp.x = int(temp.x);
        temp.y = int(temp.y);
        
        array.push_back(temp);
        
        tTemp += t;
        
    }
    
}
