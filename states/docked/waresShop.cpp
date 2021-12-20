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
        Logger::get().PrintAndLog(player_.GetShip().GetCargo().at(i)->GetWare() + " price per piece: "
                                  + std::to_string(player_.GetShip().GetCargo().at(i)->GetPrice())
                                  + " amount: " + std::to_string(player_.GetShip().GetCargo().at(i)->GetWareAmount()));
    }
    if (player_.GetShip().GetCargo().empty()) {
        Logger::get().PrintAndLog("Cargo hold is empty.");
        return;
    }
    //input
    std::string item, amount;
    Logger::get().PrintAndLog("Enter name of item to sell. Or exit to go back");
    std::cin >> item;
    Logger::get().Log(item);
    if (item == "exit" || item == "Exit") return;
    Logger::get().PrintAndLog("Enter amount.");
    std::cin >> amount;
    Logger::get().Log(amount);
    try {
        if (std::stoi(amount) <= player_.GetShip().GetCurrentCargoSize()) {
            auto &ware{player_.GetShip().GetWareByName(item)};
            player_.GetShip().RemoveCargo(ware->GetWare(), std::stoi(amount));
            player_.Earn(ware->GetPrice() * std::stoi(amount));
            player_.PrintGold();
        } else {
            Logger::get().PrintAndLog("Invalid amount");
        }
    } catch (...) {
        Logger::get().PrintAndLog("Invalid input");
    }
}

void WaresShop::BuyWares() {
    std::cout << "Shop inventory:" << std::endl;
    for (size_t i{0}; i < port_.GetWares().size(); ++i) {
        Logger::get().PrintAndLog(port_.GetWares().at(i)->GetWare() + " price per piece: " +
                                  std::to_string(port_.GetWares().at(i)->GetPrice()) +
                                  " amount: " + std::to_string(port_.GetWares().at(i)->GetWareAmount()));
    }
    player_.PrintGold();
    player_.GetShip().PrintCargoSize();
    Logger::get().PrintAndLog("Enter name of item to buy. Or exit to go back");
    //input
    std::string item, amount;
    std::cin >> item;
    if (item == "exit" || item == "Exit") return;
    Logger::get().PrintAndLog("Enter amount.");
    std::cin >> amount;
    Logger::get().Log(amount);
    Logger::get().Log(item);
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
            Logger::get().PrintAndLog("transaction succeeded");
        } else {
            Logger::get().PrintAndLog("transaction failed");
        }
    }
    catch (...) {
        Logger::get().PrintAndLog("Invalid input");
    }
}
