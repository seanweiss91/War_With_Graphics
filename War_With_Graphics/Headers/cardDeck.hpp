//
//  cardDeck.hpp
//  War
//
//  Created by Sean Weiss on 5/22/17.
//  Copyright © 2017 Sean Weiss. All rights reserved.
//

#ifndef cardDeck_hpp
#define cardDeck_hpp

#include <stdio.h>
#include "card.hpp"
#include <queue>
#include <string>

using namespace std;

class cardDeck
{
public:
    
    cardDeck();
    cardDeck(int deckSize);
    
    /* Fills a deck object with one of every card in a 52 card deck */
    void fillDeck();
    
    /* displays every card in a given deck */
    void displayDeck();
    
    /* Uses the random_shuffle function to randomize the order of the vector of the deck object */
    void shuffleDeck();
    
    /* returns the number of elements in the vector of any given deck object */
    unsigned long sizeOfDeck();
    
    /* returns the card object at a given subscript location in the deck object vector */
    card& operator []( const int &x ) ;
    
    /* Places a card object into the "bottom" of the deck, or the back of the deck vector */
    void addCard( card &card );
    
    /* Clears the entire deck object vector, destroying ecery object */
    void clear();
    
    /* Provides an iterator that points to the beginning of the deck vector */
    vector<card>::iterator getBegin();
    
    /* Provides an iterator that points to the last element of the deck vector */
    vector<card>::iterator getEnd();
    
    /* Returns true of the deck is empty */
    bool isEmpty();
    
    /* An array of strings that holds the cardIcons used to output card pictures */
    string cardIcons[52];
    
    /* declaring that 'player' class has access to private data members in 'cardDeck' class */
    friend class player;
    
private:
    vector<card> cards;
    int numCards;
};

#endif /* cardDeck_hpp */
