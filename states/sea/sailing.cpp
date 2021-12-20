#include "sailing.h"

Sailing::Sailing(Player &player, std::unique_ptr<Port> &port, int distance) :
        state_("Sailing"),
        moves_(std::vector<std::string>{"1) Roll"}),
        player_(player), port_(std::move(port)),
        turns_(0),
        distance_(distance) {}

const std::vector<std::string> &Sailing::Moves() const {
    return moves_;
}

const std::string &Sailing::GetState() const {
    return state_;
}

std::unique_ptr<State> Sailing::Move(int action) {
    //dice roll
    Logger::get().PrintAndLog("Distance to port: " + std::to_string(distance_));
    if (action == 1) {
        int roll{Dice::get().generateNumber(1, 20)};
        Logger::get().PrintAndLog("You rolled:" + std::to_string(roll));
        if (roll == 1 || roll == 2) Nothing();
        if (roll == 3 || roll == 4) Breeze();
        if (roll >= 5 && roll <= 7) Weak();
        if (roll >= 8 && roll <= 17) Normal();
        if (roll == 18 || roll == 19) Strong();
        if (roll == 20) Storm();
    }
    turns_++;
    if (distance_ <= 0 ) return std::make_unique<Docked>(player_,*port_);
    return std::make_unique<Sailing>(player_, port_, distance_);
}

void Sailing::Nothing() {
    Logger::get().PrintAndLog("Nothing happened");
}

void Sailing::Breeze() {
    if (player_.GetShip().GetParticularity() == LIGHT) { Normal(); }
    else {
        Nothing();
    }
}

void Sailing::Weak() {
    if (player_.GetShip().GetParticularity() == LOG) {
        Nothing();
    } else {
        Normal();
    }
}

void Sailing::Normal() {
    distance_--;
    Logger::get().PrintAndLog("Moved Distance of 1");
}

void Sailing::Strong() {
    Logger::get().PrintAndLog("Moved Distance of 2");
    distance_ = distance_ - 2;
}

void Sailing::Storm() {
    Logger::get().PrintAndLog("It has started storming");
    int roll{Dice::get().generateNumber(1, 5)};
    if (roll == 1 || roll == 2) {
        Logger::get().PrintAndLog("Distance increased by 1");
        distance_++;
    }
    if (roll == 3 || roll == 4) Nothing();
    if (roll == 5) Normal();

    //calculate storm damage
    int damage{Dice::get().generateNumber(1, 100)};
    player_.GetShip().Damage(player_.GetShip().GetHealth() / damage);
    Logger::get().PrintAndLog("Ship health after the storm \n health: " + std::to_string(player_.GetShip().GetHealth())
    + "/" + std::to_string(player_.GetShip().GetMaxHealth()));
}
