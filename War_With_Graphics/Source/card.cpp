//
//  card.cpp
//  War
//
//  Created by Sean Weiss on 5/22/17.
//  Copyright © 2017 Sean Weiss. All rights reserved.
//

#include <stdio.h>
#include "card.hpp"
#include <iostream>

#include <string>

using namespace std;

/*
ostream& operator<<(ostream& out, const card& cardObj)
{
    
    if (cardObj.value < 11)
        out << cardObj.value;
    else if ( cardObj.value == 11 )
        out << "Jack";
    else if ( cardObj.value == 12 )
        out << "Queen";
    else if ( cardObj.value == 13 )
        out << "King";
    else if ( cardObj.value == 14 )
        out << "Ace";
    
    out << " of " << cardObj.suit;
        
        return out;
}
 */

// /*
ostream& operator<<(ostream& out, const card& cardObj)
{
    
    out << cardObj.cardIcon << " " << cardObj.value;
    
    return out;
}
//*/

bool card::operator <(const card &player) const {
    return this->value < player.value;
}

bool card::operator >(const card &player) const {
    return this->value > player.value;
}
 


card::card(int value, string color, string suit, string cardIcon, int spriteLocation)
{
    this->value = value;
    this->color = color;
    this->suit = suit;
    this->cardIcon = cardIcon;
    this->spriteLocation = spriteLocation;
}

int card::getSpriteLocation()
{
    return spriteLocation;
}
