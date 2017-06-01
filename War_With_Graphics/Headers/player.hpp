//
//  player.hpp
//  War
//
//  Created by Sean Weiss on 5/22/17.
//  Copyright © 2017 Sean Weiss. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include <queue>

#include "cardDeck.hpp"

using namespace std;

class card;

class player
{
public:
    
    player();
    /* Creates a player object that takes an int and sets it equal to numCards */
    player(int numCards);
    
    /* This function is called when a player has won a round. It takes in the 'tableDeck' as a parameter so it can place every card "on the table" into the winner's discard pile deck */
    void addAllCardsToDiscardPile (cardDeck &tableDeck);
    
    /* used to insert cards into the player's 'cardsInHand' deck */
    void insertCards(card &card);
    
    /* Returns the card at the top ([0]) of the player's 'cardsInHand' deck */
    card& getTopOfPlayerHand();
    
    /* Checks if player's 'cardsInHand' deck is empty */
    bool empty();
    
    /* Removes the top card in the player's 'cardsInHand' deck. Should occur when the player places a card onto the "table" */
    void removeTopCard();
    
    /* Checks both player decks for cards. If both the 'cardsInHand' deck and 'discardPile' deck are empty, it will return true (the players has no cards left). */
    bool outOfCards();
    
    /* Function is called when the player's 'cardsInHand' deck becomes empty. It first check to see if the discard pile is empty as well before moving forward. If discard pile is not empty then the discard pile is shuffled and then inserted into the player's 'cardsInHand' deck */
    void fillHandFromDiscardPile();
    
    /* Used to display the cards currently in the player's 'cardsInHand' deck */
    void displayCardsInHand();
    
    cardDeck getCardsInHandDeck();
    
private:
    
    /* Stores the max number of cards in the player decks */
    int numCards;
    
    /* Stores the cards that are currently in the player's hands */
    cardDeck cardsInHand;
    
    /* Stores the cards gained from winning a battle. */
    cardDeck discardPile;
    
};

#endif /* player_hpp */
