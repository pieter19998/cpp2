#include "repair.h"


Repair::Repair(Player &player, Port &port) :
        state_("Repairing ship"),
        moves_(std::vector<std::string>{"1) Repair", "2) back"}),
        player_(player), port_(port) {}

const std::vector<std::string> &Repair::Moves() const {
    std::cout << "Ship health: " + std::to_string(player_.GetShip().GetHealth())
              << "/" + std::to_string(player_.GetShip().GetMaxHealth()) << std::endl;
    std::cout << "Funds: " + std::to_string(player_.GetFunds()) << std::endl;
    return moves_;
}

const std::string &Repair::GetState() const {
    return state_;
}

std::unique_ptr<State> Repair::Move(int action) {
    switch (action) {
        case 1:
            RepairShip();
            return std::make_unique<Repair>(player_, port_);
        case 2:
            return std::make_unique<Docked>(player_, port_);
        default:
            return std::make_unique<Repair>(player_, port_);
    }
}

void Repair::RepairShip() {
    std::cout << "1 gold per 10 health. Type Exit to cancel" << std::endl;
    std::string gold;
    std::cin >> gold;
    if (gold == "exit" || gold == "Exit") return;
    try {
        if (player_.CheckFunds(std::stoi(gold))) {
            player_.Spend(std::stoi(gold));
            player_.GetShip().Repair(std::stoi(gold));
        }
    } catch (...) {
        std::cout << "invalid number" << std::endl;
    }
}
