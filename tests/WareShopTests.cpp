#include <gtest/gtest.h>
#include "../states/docked/waresShop.h"

TEST(WareShop, sellwares) {
    //Arrange
    std::string name{"Pinnace"};
    std::string portName{"Portname"};
    std::string wareName{"hout"};
    auto ship{std::make_unique<Ship>(name, 1, 1000, 200, 8, 100, LOG)};
    auto ships {std::vector<std::unique_ptr<Ship>>()};
    auto player{std::make_unique<Player>(25000, ship)};
    auto cannons{std::make_unique<Cannon>(1,1,1)};
    auto wares{std::vector<std::unique_ptr<Wares>>()};
    auto port{std::make_unique<Port>(1, portName, wares, cannons, ships)};
    auto state{std::make_unique<WaresShop>(*player, *port)};
    auto ShipWares {std::make_unique<Wares>(wareName,1,10,100)};
    //Act
    player->GetShip().AddCargo(ShipWares);
    state->Move(2);
    //Assert

}