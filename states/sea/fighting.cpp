#include "fighting.h"
#include "../../randomizer/dice.h"
#include "../docked/docked.h"

Fighting::Fighting(Player &player, Port &port, std::unique_ptr<Ship>& enemy) :
        state_("Fighting"),
        moves_(std::vector<std::string>{"1) Fire", "2) Escape", "3) Surrender"}),
        player_(player), port_(port), fighting_(true), enemy_(std::move(enemy)) {}

const std::vector<std::string> &Fighting::Moves() const {
    return moves_;
}

const std::string &Fighting::GetState() const {
    return state_;
}

std::unique_ptr<State> Fighting::Move(int action) {
    switch (action) {
        case 1:
            Fire(player_.GetShip(), enemy_.operator*());
        case 2:
            Escape();
        case 3:
            Surrender();
        default:
            break;
    }
    if (!fighting_) return std::make_unique<Docked>(player_, port_);
    return std::make_unique<Fighting>(player_, port_, enemy_);
}

void Fighting::Escape() {
    std::unordered_map<Particularities,std::unordered_map<Particularities, int>> map;
    map[LIGHT][LIGHT] = 50;
    map[LIGHT][NONE] = 60;
    map[LIGHT][LOG] = 75;
    map[NONE][LIGHT] = 30;
    map[NONE][NONE] = 40;
    map[NONE][LOG] = 55;
    map[LOG][LIGHT] = 5;
    map[LOG][NONE] = 15;
    map[LOG][LOG] = 30;
    auto playerShip {player_.GetShip().GetParticularity()};
    auto enemyShip {enemy_->GetParticularity()};
    int percent {map.find(playerShip)->second.find(enemyShip)->second};
    auto number {Dice::get().generateNumber(0, 100)};
    if( percent <= number){
        fighting_ = false;
        std::cout << "escape succeeded"<< std::endl;
    }
    std::cout << "escape failed" << std::endl;
}

void Fighting::Fire(Ship &attacker, Ship &receiver) {
    auto allCannons{attacker.GetCannons()->GetCannons()};
    for (int i = 0; i < allCannons.find(LIGHTCANNON)->second; ++i) {
        receiver.Damage(Dice::get().generateNumber(0, 2));
    }
    for (int i = 0; i < allCannons.find(MEDIUMCANNON)->second; ++i) {
        receiver.Damage(Dice::get().generateNumber(0, 4));
    }
    for (int i = 0; i < allCannons.find(HEAVYCANNON)->second; ++i) {
        receiver.Damage(Dice::get().generateNumber(0, 6));
    }
}

void Fighting::Surrender() {
    std::cout << "You surrendered and lost all cargo." << std::endl;
    player_.GetShip().RemoveAllCargo();
    fighting_ = false;
}