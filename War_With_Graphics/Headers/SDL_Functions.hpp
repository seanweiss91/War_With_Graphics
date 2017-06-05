//
//  SDL_Functions.hpp
//  WarWithGraphics
//
//  Created by Sean Weiss on 5/29/17.
//  Copyright © 2017 Sean Weiss. All rights reserved.
//

#ifndef SDL_Functions_h
#define SDL_Functions_h

#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>



//Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const int CARD_WIDTH;
extern const int CARD_HEIGHT;

// Provides the scale multiplied by the entire screen height to provide card location for player 1
extern const double PLAYER_1_LOCATION_SCALE_HEIGHT;
// Provides the scale multiplied by the entire screen height to provide card location for player 2
extern const double PLAYER_2_LOCATION_SCALE_HEIGHT;
// Provides the scale multiplied by the entire screen width to provide card location for player 1 and 2
extern const double PLAYER_LOCATION_SCALE_WIDTH;

// Determines how quick the animations will occur
extern const int ANIMATION_RATE;


// The window we'll be rendering to
extern SDL_Window* gWindow;

// The surface contained by the window
extern SDL_Surface* gScreenSurface;

// The image we will load and show on the screen
extern SDL_Texture* gGameBackground;



// Loads individual image
extern SDL_Texture* loadTexture( std::string path );

// The images that correspond to a keyPress
extern SDL_Texture* gCurrentSurface;

// The deck sprite sheet that holds the card images
extern SDL_Texture* gDeckSpriteSheet;

//The images that correspond to a keypress
extern SDL_Texture* gDeckCardImages[ 52 ];


//The window renderer
extern SDL_Renderer* gRenderer;

//Current displayed texture
extern SDL_Texture* gTexture;

// stores the locations of each card in the sprite sheets
extern SDL_Rect gSpriteClips[ 54 ];




//The music that will be played
extern Mix_Music *gMusic;

//The sound effects that will be used
extern Mix_Chunk *gLose;
extern Mix_Chunk *gWin;
extern Mix_Chunk *gShuffle;
extern Mix_Chunk *gWar;


extern TTF_Font *gFont;

extern SDL_Texture* gText_Texture;
extern SDL_Texture* gNumText_Texture;

extern SDL_Rect textLocation;
extern SDL_Rect deckNumTextLocation;

// Starts up SDL and creates twindow
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

/* First parameter determines 'x' location on screen to display image.
     Second parameter determines 'y' location on screen to display image.
     Third passes a "clip", or the box of the sprite sheet where the image exists. */
void render( int x, int y, SDL_Rect* clip );

SDL_Texture* loadFromRenderedText( std::string textureText, SDL_Color textColor );

SDL_Texture* loadTextFromRenderedText( std::string textureText, SDL_Color textColor, SDL_Texture* textTexture );

struct Points
{
    Points(float x, float y) : x(x), y(y) {}
    float x;
    float y;
};

extern void getCubicBezierCurve( Points p0, Points p1, Points p2, float t, int numPointsOnCurve, std::vector<Points> &array );


#endif /* SDL_Functions_h */
