#include "player.h"

Player::Player(int gold, std::unique_ptr<Ship>& ship) : gold_(gold), ship_(std::move(ship)), playing_(true){}

int Player::GetFunds() const {
    return gold_;
}

void Player::Earn(int gold) {
    gold_ += gold;
}

Ship& Player::GetShip() const {
    return *ship_;
}

void Player::SetPlaying(bool playing) {
    playing_ = playing;
}

bool Player::GetPlaying() const {
    return playing_;
}

void Player::Spend(int price) {
    gold_ -= price;
}

void Player::PrintGold() {
    std::cout << "wallet: " << gold_ << std::endl;
}

bool Player::CheckFunds(int price) const {
    if (gold_ - price < 0){
        std::cout << "Not enough gold." << std::endl;
        return false;
    }
    return true;
}

void Player::SetShip(std::unique_ptr<Ship>& ship) {
    ship_ = std::move(ship);
}
