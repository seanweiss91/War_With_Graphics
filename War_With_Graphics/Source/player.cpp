//
//  player.cpp
//  War
//
//  Created by Sean Weiss on 5/22/17.
//  Copyright © 2017 Sean Weiss. All rights reserved.
//

#include "player.hpp"
#include <iostream>

void player::addAllCardsToDiscardPile (cardDeck &tableDeck)
{
    for (int i = 0; i < tableDeck.sizeOfDeck(); i++) {
        discardPile.cards.push_back(tableDeck[i]);
    }
    
    tableDeck.clear();
    
}

player::player(int numCards) {
    this->numCards = numCards;
    
}

void player::insertCards(card &card) {
    cardsInHand.cards.push_back(card);
}

card& player::getTopOfPlayerHand()
{
    return cardsInHand.cards.front();
}

bool player::empty() {
    return this->cardsInHand.cards.empty();
}

void player::removeTopCard() {
    cardsInHand.cards.erase(cardsInHand.getBegin());
}

bool player::outOfCards() {
    return ( cardsInHand.cards.empty() && discardPile.cards.empty() );
}

void player::fillHandFromDiscardPile()
{
    
    // Code should only run if there is at least one element in discardPile
    if ( !discardPile.isEmpty() )
    {
        discardPile.shuffleDeck();
        
        for ( int i = 0; i < discardPile.sizeOfDeck(); i++ ) {
            cardsInHand.addCard(discardPile[i]);
        }
        
        discardPile.clear();
    }
    
}

void player::displayCardsInHand() {
    cardsInHand.displayDeck();
}

cardDeck player::getCardsInHandDeck() {
    return cardsInHand;
}


