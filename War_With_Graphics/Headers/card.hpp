//
//  card.hpp
//  War
//
//  Created by Sean Weiss on 5/22/17.
//  Copyright © 2017 Sean Weiss. All rights reserved.
//

#ifndef card_hpp
#define card_hpp

#include <stdio.h>
#include <string>

using namespace std;

class card
{
public:
    
    card();
    
    /* initializes a card object with a value, color, suit and a cardIcon */
    card(int, string, string, string, int);
    
    
    friend ostream& operator<<(ostream& out, const card& cardObj);
    bool operator <(const card &player) const;
    bool operator >(const card &player) const;
    bool operator ==(const card &player) const;
    
    int getSpriteLocation();
    
private:
    
    int value;
    string color;
    string suit;
    string cardIcon;
    int spriteLocation;
};

#endif /* card_hpp */
