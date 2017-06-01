//
//  War.cpp
//  War
//
//  Created by Sean Weiss on 5/22/17.
//  Copyright © 2017 Sean Weiss. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "War.hpp"

#include <vector>
#include "card.hpp"
#include "player.hpp"

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>

#include "SDL_Functions.hpp"


using namespace std;

int War::gameLoop()
{
    
    // Start up SDL and create a window
    if ( !init() )
        printf( "Failed to initialize!\n" );
    else
    {
        // Load media
        if ( !loadMedia() )
            printf ( "Failed to load media\n" );
        else
        {
            
            cout << "erase this later" << endl;
            
            // Main loop flag
            bool quit = false;
            
            // Event handler
            SDL_Event e;
            
            // Render game background to screen
            SDL_RenderCopy( gRenderer, gGameBackground, NULL, NULL );
            
            int w;
            SDL_QueryTexture(gText_Texture, NULL, NULL, &w, NULL);
            textLocation.w = w;
            SDL_RenderCopy(gRenderer, gText_Texture, NULL, &textLocation);
            
            // Update screen
            SDL_RenderPresent( gRenderer );
            
            
            
            // Preparing cards for players and game
            player player1(52);
            player player2(52);
            
            cardDeck deck(52);
            deck.fillDeck();
            deck.shuffleDeck();
            
            distributeCardsToPlayers(deck, player1, player2);
            
            SDL_Delay(1000); // Wait one second after background loads
           Mix_PlayChannel( -1, gShuffle, 2 );
            
            SDL_Delay(2000); // Wait two second after Shuffle noise
            // Start Music!
            Mix_PlayMusic( gMusic, -1 );
            
            // While application is running and players are not out of cards
            while ( !quit && ( !player1.outOfCards()  && !player2.outOfCards() )  )
            {
                
                while( SDL_PollEvent( &e ) != 0 )
                {
                    // User requests quit
                    if( e.type == SDL_QUIT )
                        quit = true;
                    else if ( e.type == SDL_KEYDOWN )
                    {
                        
                        if ( !checkIfPlayerHandIsEmpty(player1, player2) )
                            playWar(player1, player2);
                        
                        
    
                    } // End of key check else if statement
                } // End of Poll Event while loop
            } // End of Game Loop
            
            // GameLoop can only end if a player has no cards. Therefore we check for who still has cards
            checkWinner(player1, player2);
            
        } // End of else statement after loadMedia()
    } // End of else statement after init()
   
    //Free resources and close SDL
    close();
    
    return 0;
}

void War::playWar( player &player1, player &player2 )
{
    
    int condition = compareTopCardForPlayers( player1, player2 );
    
    displayAttack(player1, player2);
    
    addToTableDeck( player1, player2 );

    switch(condition){
        case 0 : collectCardsFromTable(player1);
            cout << ". Player1 wins this round " << endl;
            break;
        case 1 : collectCardsFromTable(player2);
            cout << ". Player2 wins this round " << endl;
            break;
        case 2 :
            if ( !checkIfPlayerHandIsEmpty(player1, player2))
            addToTableDeck( player1, player2 );
            cout << ". War has been declared" << endl;
            Mix_PlayChannel( -1, gWar, 0 );
            if ( !checkIfPlayerHandIsEmpty(player1, player2) )
                playWar(player1, player2);
    }
    
}

void War::distributeCardsToPlayers( cardDeck &deck, player &player1, player &player2 )
{
    
    for (int i = 0; i < deck.sizeOfDeck(); i++)
    {
        if ( i % 2 == 0 )
            player1.insertCards(deck[i]);
        else
            player2.insertCards(deck[i]);
    }
    
}

// Take the cards that are currently on the table and insert them to the back of the winners discard pile
void War::collectCardsFromTable( player &winner )
{
    winner.addAllCardsToDiscardPile(tableDeck);
}


int War::compareTopCardForPlayers( player &player1, player &player2 ) {
    
    int condition;
    if ( player1.getTopOfPlayerHand() > player2.getTopOfPlayerHand() )
        condition = 0;
    else if ( player1.getTopOfPlayerHand() < player2.getTopOfPlayerHand() )
        condition = 1;
    else condition = 2;
    
    renderCardsToScreen( player1, player2 );
    
    /* Leave cards on table for 1 second before the winner takes them */
    SDL_Delay(1000);
    
    if ( condition == 0 )
    {
        Mix_PlayChannel( -1, gWin, 2 );
        animateTableCardsToPlayer1( player1, player2 );
    }
    
    if ( condition == 1 )
    {
        Mix_PlayChannel( -1, gLose, 2 );
        animateTableCardsToPlayer2( player1, player2 );
    }
    
    return condition;
}

void War::addToTableDeck( player &player1, player &player2 )
{
    
    tableDeck.addCard(player1.getTopOfPlayerHand());
    tableDeck.addCard(player2.getTopOfPlayerHand());
    
    player1.removeTopCard();
    player2.removeTopCard();
    
}

void War::displayAttack(player &player1, player &player2) {
    cout << player1.getTopOfPlayerHand() << " Versus " << player2.getTopOfPlayerHand();
}

bool War::checkIfPlayerHandIsEmpty(player &player1, player &player2)
{
    if ( player1.empty() ) {
        player1.fillHandFromDiscardPile();
    }
    
    if ( player2.empty() ) {
        player2.fillHandFromDiscardPile();
    }
    
    return ( player1.outOfCards() || player2.outOfCards() );
}

void War::checkWinner(player &player1, player &player2)
{
    
    if ( player1.empty() )
        cout << "*** Player 2 is the winner!! ***" << endl;
    else
        cout <<  "*** Player 1 is the winner!! ***" << endl;
}

void War::renderCardsToScreen( player &player1, player &player2 )
{
    
    // Clear Screen
    SDL_RenderClear( gRenderer );
    
    // Render game background to screen
    SDL_RenderCopy( gRenderer, gGameBackground, NULL, NULL );
    
    renderCardsInHandLabel();
    
    updateNumText( player1 );
    
    // First parameter: Where on x axis card will be displayed
    // Second parameter: Where on y axis card will be displayed
    // 3rd Parameter: A SDL_Rect object with location of appropriate card sprite
    render(SCREEN_WIDTH * PLAYER_LOCATION_SCALE_WIDTH, SCREEN_HEIGHT * PLAYER_1_LOCATION_SCALE_HEIGHT, &gSpriteClips[player1.getTopOfPlayerHand().getSpriteLocation()]);
    
    render(SCREEN_WIDTH * PLAYER_LOCATION_SCALE_WIDTH, SCREEN_HEIGHT * PLAYER_2_LOCATION_SCALE_HEIGHT, &gSpriteClips[player2.getTopOfPlayerHand().getSpriteLocation()]);
    
    SDL_RenderPresent( gRenderer );
    
}

void War::animateTableCardsToPlayer1( player &player1, player &player2 )
{
    int pixelsToMove = 6;
    
    /* The furthest card is the card of the loser. It has more distance to travel to go off screen as it moves to the winners side. */
    double furthestCardStartingLocationHeight = SCREEN_HEIGHT * PLAYER_2_LOCATION_SCALE_HEIGHT;
    
    /* The closest card is the card of the winner. It has less distance to travel to go off screen */
    double closestCardStartingLocationHeight = SCREEN_HEIGHT * PLAYER_1_LOCATION_SCALE_HEIGHT;
    
    /* End of animation is when the farthest card is past the height of the sceen and can't be seen anymore */
    double endOfAnimationLocation = SCREEN_HEIGHT + 30;
    
    
    /* While the furthest card is still on screen */
    while ( furthestCardStartingLocationHeight < endOfAnimationLocation )
    {
        
        int ticks = SDL_GetTicks();
        
        ticks += ANIMATION_RATE;
        
        while ( SDL_GetTicks() < ticks ) {}
        
        // Clear Screen
        SDL_RenderClear( gRenderer );
        
        // Render game background to screen
        SDL_RenderCopy( gRenderer, gGameBackground, NULL, NULL );
        
        render(SCREEN_WIDTH * PLAYER_LOCATION_SCALE_WIDTH, furthestCardStartingLocationHeight, &gSpriteClips[player2.getTopOfPlayerHand().getSpriteLocation()]);
        
        if ( furthestCardStartingLocationHeight < closestCardStartingLocationHeight - 50 )
            render(SCREEN_WIDTH * PLAYER_LOCATION_SCALE_WIDTH, SCREEN_HEIGHT * PLAYER_1_LOCATION_SCALE_HEIGHT, &gSpriteClips[player1.getTopOfPlayerHand().getSpriteLocation()]);
        else
        {
             render(SCREEN_WIDTH * PLAYER_LOCATION_SCALE_WIDTH, closestCardStartingLocationHeight, &gSpriteClips[player1.getTopOfPlayerHand().getSpriteLocation()]);
            closestCardStartingLocationHeight += pixelsToMove;
        }
        
        SDL_RenderPresent( gRenderer );
        
        furthestCardStartingLocationHeight += pixelsToMove;
    }
}

void War::animateTableCardsToPlayer2( player &player1, player &player2 )
{
    int pixelsToMove = 6;
    
    double furthestCardStartingLocationHeight = SCREEN_HEIGHT * PLAYER_1_LOCATION_SCALE_HEIGHT;
    
    double closestCardStartingLocationHeight = SCREEN_HEIGHT * PLAYER_2_LOCATION_SCALE_HEIGHT;
    
    double endOfAnimationLocation = furthestCardStartingLocationHeight - SCREEN_HEIGHT;

    
    while ( furthestCardStartingLocationHeight > endOfAnimationLocation )
    {
        
        
        int ticks = SDL_GetTicks();
        
        ticks += ANIMATION_RATE;
        
        while ( SDL_GetTicks() < ticks ) {}
        // Clear Screen
        SDL_RenderClear( gRenderer );
        
        // Render game background to screen
        SDL_RenderCopy( gRenderer, gGameBackground, NULL, NULL );
        
        if ( furthestCardStartingLocationHeight > closestCardStartingLocationHeight + 50 )
            render(SCREEN_WIDTH * PLAYER_LOCATION_SCALE_WIDTH, closestCardStartingLocationHeight, &gSpriteClips[player2.getTopOfPlayerHand().getSpriteLocation()]);
        else
        {
            render(SCREEN_WIDTH * PLAYER_LOCATION_SCALE_WIDTH, closestCardStartingLocationHeight, &gSpriteClips[player2.getTopOfPlayerHand().getSpriteLocation()]);
            closestCardStartingLocationHeight -= pixelsToMove;
        }
        
        render(SCREEN_WIDTH * PLAYER_LOCATION_SCALE_WIDTH, furthestCardStartingLocationHeight, &gSpriteClips[player1.getTopOfPlayerHand().getSpriteLocation()]);
        
        SDL_RenderPresent( gRenderer );
        
        furthestCardStartingLocationHeight -= pixelsToMove;

    }
}

void War::updateNumText(player &player)
{

    bool success = true;
    
    //Render text
    SDL_Color textColor = { 0, 0, 0 };
    
    /* passes the current size of the cardsInHand deck to be displayed on screen */
    gNumText_Texture = loadFromRenderedText( std::to_string(player.getCardsInHandDeck().sizeOfDeck()), textColor ) ;
    if( !gNumText_Texture)
    {
        printf( "Failed to render text texture!\n" );
        success = false;
    }
    else
    {
        int w;
        SDL_QueryTexture(gNumText_Texture, NULL, NULL, &w, NULL);
        deckNumTextLocation.w = w;
        SDL_RenderCopy(gRenderer, gNumText_Texture, NULL, &deckNumTextLocation);
    }
    
}

void War::renderCardsInHandLabel ( )
{
    int w;
    SDL_QueryTexture(gText_Texture, NULL, NULL, &w, NULL);
    textLocation.w = w;
    SDL_RenderCopy(gRenderer, gText_Texture, NULL, &textLocation);
}



