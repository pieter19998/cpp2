#include "waresShop.h"
#include "docked.h"

WaresShop::WaresShop(Player &player, Port &port) :
        state_("Inside WareShop"),
        moves_(std::vector<std::string>{"1) Sell Wares", "2) Buy Wares", "3) Back"}),
        player_(player), port_(port) {}

const std::vector<std::string> &WaresShop::Moves() const {
    return moves_;
}

const std::string &WaresShop::GetState() const {
    return state_;
}

std::unique_ptr<State> WaresShop::Move(int action) {
    switch (action) {
        case 1:
            SellWares();
            return std::make_unique<WaresShop>(player_, port_);
        case 2:
            BuyWares();
            return std::make_unique<WaresShop>(player_, port_);
        case 3:
            return std::make_unique<Docked>(player_, port_);
        default:
            return std::make_unique<WaresShop>(player_, port_);
    }
}

void WaresShop::SellWares() {
    player_.GetShip().PrintCargoSize();
    for (size_t i{0}; i < player_.GetShip().GetCargo().size(); ++i) {
        std::cout << player_.GetShip().GetCargo().at(i)->GetWare() << " price per piece: "
                  << player_.GetShip().GetCargo().at(i)->GetPrice()
                  << " amount: " << player_.GetShip().GetCargo().at(i)->GetWareAmount() << std::endl;
    }
    if (player_.GetShip().GetCargo().empty()) {
        std::cout << "Cargo hold is empty." << std::endl;
        return;
    }
    //input
    std::string item, amount;
    std::cout << "Enter name of item to sell. Or exit to go back" << std::endl;
    std::cin >> item;
    if (item == "exit" || item == "Exit") return;
    std::cout << "Enter amount." << std::endl;
    std::cin >> amount;
    try {
        if (std::stoi(amount) <= player_.GetShip().GetCurrentCargoSize()) {
            auto &ware{player_.GetShip().GetWareByName(item)};
            player_.GetShip().RemoveCargo(ware->GetWare(), std::stoi(amount));
            player_.Earn(ware->GetPrice() * std::stoi(amount));
            player_.PrintGold();
        } else {
            std::cout << "Invalid amount" << std::endl;
        }
    } catch (...) {
        std::cout << "Invalid input" << std::endl;
    }
}

void WaresShop::BuyWares() {
    std::cout << "Shop inventory:" << std::endl;
    for (size_t i{0}; i < port_.GetWares().size(); ++i) {
        std::cout << port_.GetWares().at(i)->GetWare() << " price per piece: " << port_.GetWares().at(i)->GetPrice()
                  << " amount: " << port_.GetWares().at(i)->GetWareAmount() << std::endl;
    }
    player_.PrintGold();
    player_.GetShip().PrintCargoSize();
    std::cout << "Enter name of item to buy. Or exit to go back" << std::endl;
    //input
    std::string item, amount;
    std::cin >> item;
    if (item == "exit" || item == "Exit") return;
    std::cout << "Enter amount." << std::endl;
    std::cin >> amount;
    //process data
    try {
        auto &ware{port_.GetWareByName(item)};
        //make sure wares are available and player has enough gold
        if (player_.GetShip().CheckIfCargoFids(std::stoi(amount)) &&
            player_.CheckFunds(ware->GetPrice() * std::stoi(amount)) &&
            ware->GetWareAmount() - std::stoi(amount) >= 0) {
            player_.Spend(ware->GetPrice() * std::stoi(amount));
            port_.RemoveWareFromStock(item, std::stoi(amount));
            auto copy{ware->GetWareCopy()}; //make lvalue cause constructor expects a lvalue reference
            auto newCargo{std::make_unique<Wares>(copy, ware->GetId(), std::stoi(amount), ware->GetPrice())};
            player_.GetShip().AddCargo(newCargo);
            std::cout << "transaction succeeded" << std::endl;
        } else {
            std::cout << "transaction failed" << std::endl;
        }
    }
    catch (...) {
        std::cout << "Invalid input" << std::endl;
    }
}
