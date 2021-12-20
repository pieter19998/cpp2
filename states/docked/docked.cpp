#include "docked.h"
#include "waresShop.h"
#include "repair.h"
#include "canonShop.h"
#include "shipShop.h"
#include "setSail.h"

Docked::Docked(Player &player, Port &port) : state_("Inside the harbor"),
moves_(std::vector<std::string>{"1) Ware shop","2) Cannon shop", "3) Ship shop","4) Set sail","5) repair ship","6) Quit"}),
player_(player), port_(port) {}

//return list of available moves
const std::vector<std::string> &Docked::Moves() const {
    return moves_;
}

const std::string &Docked::GetState() const {
    return state_;
}

std::unique_ptr<State> Docked::Move(int action) {
    switch (action) {
        case 1: return std::make_unique<WaresShop>(player_,port_);
        case 2: return std::make_unique<CanonShop>(player_,port_);
        case 3: return std::make_unique<ShipShop>(player_,port_);
        case 4: return std::make_unique<SetSail>(player_,port_);
        case 5: return std::make_unique<Repair>(player_, port_);
        case 6: Quit(); return nullptr;
        default: return std::make_unique<Docked>(player_,port_);
    }
}

void Docked::Quit() {
    player_.SetPlaying(false);
}

