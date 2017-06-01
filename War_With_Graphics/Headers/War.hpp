//
//  War.hpp
//  War
//
//  Created by Sean Weiss on 5/22/17.
//  Copyright © 2017 Sean Weiss. All rights reserved.
//

#ifndef War_h
#define War_h

#include <vector>
#include "card.hpp"
#include "game.hpp"
#include "player.hpp"

class War: public game
{
    
public:
    
    
    // initiates the start of the game. Creates a deck of cards and distributes the cards to the
    // players. Then runs 'playWar' function. 'playWar' will continue to loop until one player is out
    // of cards
    int gameLoop();
    
    // takes a filled and shuffled deck of cards and gives a card to each player, alternating players
    void distributeCardsToPlayers( cardDeck &deck, player &player1, player &player2 );
    
    // Looks at the top of card each players deck (In this instance [0]) and compares the cards' values
    // If player1 is larger return 0, else return 1. If equal return 2.
    int compareTopCardForPlayers( player &player1, player &player2 );
    
    /* Takes the winner of the card comparison and fills their discard pile with what is in the table deck */
    void collectCardsFromTable( player &winner );
    
    // adds the top card in each player deck into the tableDeck, then removes each card from each player
    void addToTableDeck( player &player1 , player &player2 );
    
    /* Checks which top card is higher, displays the top cards to output, and adds the top card of each player to the table deck. A switch case is used based on which top card is higher. The player with the higher card takes the table deck and puts it into their discard pile. If a tie, both players put an extra card into the table deck and then 'playWar' is recursively called until there is a winner. 'checkIfPlayerHandIsEmpty' is called each time before placing more cards into table deck from the player's cardsInHand deck.  */
    void playWar( player &player1, player &player2 );
    
    /* Displays the card icon and value of the top cards to show who won the round */
    void displayAttack(player &player1, player &player2);
    
    //returns false if player still has cards. Returns true if one player is completely out of cards.
    bool checkIfPlayerHandIsEmpty(player &player1, player &player2);
    
    /* Whoever still has cards in their deck is the winner. 'playWar' will continue to loop until one player is out of cards */
    void checkWinner(player &player1, player &player2);
    
    /* Renders the top card of the player decks to display them in the window at the appropriate place */
    void renderCardsToScreen( player &player1, player &player2 );
    
    void animateTableCardsToPlayer1( player &player1, player &player2 );
    
    void animateTableCardsToPlayer2( player &player1, player &player2 );
    
    void updateNumText(player &player);
    
    void renderCardsInHandLabel ( );
    
private:
    
    /* A card deck that stores the cards that are currently "on the table" */
    cardDeck tableDeck;
    
};
#endif /* War_h */
