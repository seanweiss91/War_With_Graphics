//
//  cardDeck.cpp
//  War
//
//  Created by Sean Weiss on 5/22/17.
//  Copyright © 2017 Sean Weiss. All rights reserved.
//

#include <stdio.h>
#include <iostream>

#include "cardDeck.hpp"
#include "card.hpp"

#include <string>
#include <queue>



using namespace std;

string cardIcon[] = {"🂲", "🂳", "🂴", "🂵", "🂶", "🂷", "🂸", "🂹", "🂺", "🂻", "🂽", "🂾", "🂱", "🃂", "🃃", "🃄", "🃅", "🃆", "🃇", "🃈", "🃉", "🃊", "🃋", "🃍", "🃎", "🃁", "🃒", "🃓", "🃔", "🃕", "🃖", "🃗", "🃘", "🃙", "🃚", "🃛", "🃝", "🃞", "🃑", "🂢", "🂣", "🂤", "🂥", "🂦", "🂧", "🂨", "🂩", "🂪", "🂫","🂭","🂮","🂡"};

int myrandom (int i) { return std::rand()%i;}

cardDeck::cardDeck() {
    numCards = 52;
}

cardDeck::cardDeck(int deckSize)
{
    numCards = deckSize;
}

void cardDeck::fillDeck()
{
    
    int numCardsPerSuit = 13;
    
    string suits[] = {"♥️", "♦️", "♣️", "♠️"};
    
    
    string red = "red";
    string black = "black";
    
    string suit;
    string color  = red;
    
    int count = -1; // Will correspond to each new suit in the suit array
    
    int locationOfFirstSpriteLocation = 2;
    int spriteSheetLocation = locationOfFirstSpriteLocation;
    
    for (int i = 0; i < numCards; i++)
    {
        
        // For every 13 cards we will change to a new suit and increase count to the next element in the suit array
        if ( (i % numCardsPerSuit) == 0 )
        {
            count++;
            suit = suits[count];
            locationOfFirstSpriteLocation--;
            
            if ( locationOfFirstSpriteLocation < 0 )
                locationOfFirstSpriteLocation = 3;
            
            spriteSheetLocation = locationOfFirstSpriteLocation;
            
        }
        
        
        if ( i == (numCards / 2) )
            color = black;
        
        // initialize a new card with value i modulo 13
        card card( (i % numCardsPerSuit) + 2, color,  suits[count], cardIcon[i], spriteSheetLocation );
        cards.push_back(card);
        
        spriteSheetLocation += 4;
    }
    
}

void cardDeck::displayDeck()
{
    for (int i = 0; i < this->sizeOfDeck(); i++)
        cout << cards[i];
}

void cardDeck::shuffleDeck() {
    random_shuffle( cards.begin(), cards.end(), myrandom );
}

unsigned long cardDeck::sizeOfDeck()
{
    return cards.size();
}

card& cardDeck::operator []( const int &x )  {
    return cards[x];
}

void cardDeck::addCard( card &card ) {
    cards.push_back( card );
}

void cardDeck::clear() {
    cards.clear();
}

vector<card>::iterator cardDeck::getBegin() {
    return cards.begin();
}

vector<card>::iterator cardDeck::getEnd() {
    return cards.end();
}

bool cardDeck::isEmpty() {
    return this->cards.empty();
}

