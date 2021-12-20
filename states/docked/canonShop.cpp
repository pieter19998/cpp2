#include "canonShop.h"

CanonShop::CanonShop(Player &player, Port &port) :
        state_("Canon shop"),
        moves_(std::vector<std::string>{"1) Sell Canons", "2) Buy Canons", "3) Back"}),
        player_(player), port_(port) {}

const std::vector<std::string> &CanonShop::Moves() const {
    return moves_;
}

const std::string &CanonShop::GetState() const {
    return state_;
}

std::unique_ptr<State> CanonShop::Move(int action) {
    switch (action) {
        case 1:
            SellCannon();
            return std::make_unique<CanonShop>(player_, port_);
        case 2:
            BuyCannon();
            return std::make_unique<CanonShop>(player_, port_);
        case 3:
            return std::make_unique<Docked>(player_, port_);
        default:
            return std::make_unique<CanonShop>(player_, port_);
    }
}

void CanonShop::SellCannon() {
    //print available cannons
    player_.GetShip().PrintCannons();
    //input to sell cannon
    std::string item, amount;
    std::cout << "Enter number of cannon type to sell. Or exit to go back" << std::endl;
    std::cin >> item;
    if (item == "exit" || item == "Exit") return;
    std::cout << "Enter amount." << std::endl;
    std::cin >> amount;
    //sell
    try {
        int i{std::stoi(item)};
        int a{std::stoi(amount)};
        //check stock
        if (player_.GetShip().GetCannons()->TotalCannonAmount() - a < 0) {
            std::cout << "You do not have enough cannons" << std::endl;
            return;
        }

        switch (i) {
            case 1:
                player_.GetShip().GetCannons()->RemoveCannons(LIGHTCANNON, a);
                player_.Earn(a * 25);
                break;
            case 2:
                player_.GetShip().GetCannons()->RemoveCannons(MEDIUMCANNON, a);
                player_.Earn(a * 100);
                break;
            case 3:
                player_.GetShip().GetCannons()->RemoveCannons(HEAVYCANNON, a);
                player_.Earn(a * 500);
                break;
            default:
                std::cout << "invalid Cannon Number" << std::endl;
        }
    } catch (...) {
        std::cout << "Invalid input" << std::endl;
    }
}

void CanonShop::BuyCannon() {
    //print available cannons
    port_.PrintCanons();
    //input to buy cannon
    std::string item, amount;
    std::cout << "Enter number of cannon type to buy. Or exit to go back" << std::endl;
    std::cin >> item;
    if (item == "exit" || item == "Exit") return;
    std::cout << "Enter amount." << std::endl;
    std::cin >> amount;
    //buy
    try {
        int i{std::stoi(item)};
        int a{std::stoi(amount)};
        //check if cargo fids
        if (!player_.GetShip().CheckIfCannonFids(a)) return;
        //check if amount is valid
        if (port_.GetCannon()->TotalCannonAmount() + a > player_.GetShip().GetMaxCannons()) {
            std::cout << "You do not have enough cannons" << std::endl;
            return;
        }
        //check funds lambda
        auto checkFunds = [](int wallet, int price, int amount) {
            return wallet - amount * price < 0;
        };
        switch (i) {
            case 1:
                if (checkFunds(player_.GetFunds(), 50, a)) {
                    std::cout << "Not enough gold" << std::endl;
                }
                player_.GetShip().GetCannons()->AddCannon(LIGHTCANNON, a);
                port_.RemoveCannonFromStock(LIGHTCANNON, a);
                player_.Spend(a * 50);
                break;
            case 2:
                if (checkFunds(player_.GetFunds(), 200, a)) {
                    std::cout << "Not enough gold" << std::endl;
                }
                player_.GetShip().GetCannons()->AddCannon(MEDIUMCANNON, a);
                port_.RemoveCannonFromStock(MEDIUMCANNON, a);
                player_.Spend(a * 200);
                break;
            case 3:
                if (checkFunds(player_.GetFunds(), 1000, a)) {
                    std::cout << "Not enough gold" << std::endl;
                }
                player_.GetShip().GetCannons()->AddCannon(HEAVYCANNON, a);
                port_.RemoveCannonFromStock(HEAVYCANNON, a);
                player_.Spend(a * 1000);
                break;
            default:
                std::cout << "invalid Cannon Number" << std::endl;
        }
        std::cout << "transaction succeeded" << std::endl;
    }
    catch (...) {
        std::cout << "transaction failed" << std::endl;
        std::cout << "Invalid input" << std::endl;
    }
}
