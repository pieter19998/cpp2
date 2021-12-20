cmake_minimum_required(VERSION 3.16)
project(HandelsSchepen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")
add_executable(HandelsSchepen main.cpp sql/sql.cpp sql/sql.h domain/ship.cpp domain/ship.h domain/player.cpp domain/player.h domain/port.cpp domain/port.h randomizer/dice.cpp randomizer/dice.h game/game.cpp game/game.h domain/enum/Particularities.h domain/wares.cpp domain/wares.h domain/portInventory.cpp domain/portInventory.h states/state.h states/docked/docked.cpp states/docked/docked.h states/docked/waresShop.cpp states/docked/waresShop.h states/docked/repair.cpp states/docked/repair.h states/docked/setSail.cpp states/docked/setSail.h states/docked/canonShop.cpp states/docked/canonShop.h states/sea/sailing.cpp states/sea/sailing.h logger/logging.h domain/enum/cannonType.h domain/cannon.cpp domain/cannon.h states/docked/shipShop.cpp states/docked/shipShop.h states/sea/fighting.cpp states/sea/fighting.h tests/WareShopTests.cpp tests/GameTest.cpp logger/logger.cpp logger/logger.h)

target_link_libraries(HandelsSchepen LINK_PUBLIC sqlite3 gtest)