//
//  main.cpp
//  Super
//
//  Created by Bruno Motta on 10/12/16.
//  Copyright © 2016 Bruno_Thomas. All rights reserved.
//

#include <iostream>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <stdlib.h>

#include "./Supermercado.hpp"

int main(int argc, const char * argv[]) {
    
    std::srand(time(NULL));
    
    structures::Supermercado* mercado = new structures::Supermercado();
    
    mercado->simular();
    mercado->results();
   
    return 0;
}
