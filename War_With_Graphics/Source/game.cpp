
//
//  main.cpp
//  War
//
//  Created by Sean Weiss on 5/22/17.
//  Copyright © 2017 Sean Weiss. All rights reserved.
//

#include <iostream>
#include "cardDeck.hpp"
#include "War.hpp"
#include <ctime>        // std::time
#include <cstdlib>



int main( int argc, char* args[] )
{
    
    srand(unsigned(time(NULL)));
    
    War war;
    
    war.gameLoop();
    
    
    return 0;
}


