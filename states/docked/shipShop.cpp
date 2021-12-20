#include "shipShop.h"
#include "../../sql/sql.h"

ShipShop::ShipShop(Player &player, Port &port) :
        state_("Ship shop"),
        moves_(std::vector<std::string>{"1) Sell and buy new Ship", "2) Back"}),
        player_(player), port_(port) {}

const std::vector<std::string> &ShipShop::Moves() const {
    return moves_;
}

const std::string &ShipShop::GetState() const {
    return state_;
}

std::unique_ptr<State> ShipShop::Move(int action) {
    switch (action) {
        case 1:
            SellAndBuyShip();
            return std::make_unique<ShipShop>(player_, port_);
        case 2:
            return std::make_unique<Docked>(player_, port_);
        default:
            return std::make_unique<ShipShop>(player_, port_);
    }
}

void ShipShop::SellAndBuyShip() {
    //print all available ships in shop
    port_.PrintShips();
    //print price for current ship
    std::cout << "Current Ship Stats" << std::endl;
    player_.GetShip().PrintStats();
    //user input
    std::string sell, shipId;
    std::cout << "Sell current ship ? yes/no" << std::endl;
    std::cin >> sell;
    if (sell == "No" || sell == "no") return;
    std::cout << "Enter Id of ship you want to buy" << std::endl;
    std::cin >> shipId;
    try {
        auto sql{std::make_unique<Sql>()};
        auto newShip{sql->GetShip(std::stoi(shipId))};
        //check if cargo and cannons fit.
        if (player_.GetShip().GetCurrentCargoSize() > newShip->GetCargoSize()) {
            std::cout << "Cargo does not fit inside new ship." << std::endl;
            return;
        }
        if (player_.GetShip().GetCannons()->TotalCannonAmount() > newShip->GetMaxCannons()) {
            std::cout << "cannons do not fit inside new ship." << std::endl;
            return;
        }
        //check funds
        int earn{player_.GetShip().GetShipValue() / 2};
        int newShipValue{player_.GetShip().GetShipValue()};
        if (player_.GetFunds() + earn < newShipValue) {
            std::cout << "Not enough gold" << std::endl;
            return;
        }
        //sell ship
        player_.Earn(earn);
        //buy ship
        player_.SetShip(newShip);
        player_.Spend(newShipValue);
    } catch (...) {
        std::cout << "Invalid input" << std::endl;
    }
}
