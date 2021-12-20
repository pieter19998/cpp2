#include <iostream>
#include <memory>
#include "game/game.h"
#include <gtest/gtest.h>

int main(int argc, char **argv){

//    testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
    try {
        std::make_unique<Game>()->StartGame();
    }catch (...){
        std::cout << "something went wrong"  << std::endl;
    }
}
