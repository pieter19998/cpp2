#include "ship.h"

Ship::Ship(std::string &type, int id, int price, int cargoSize, int cannon, int health, Particularities particularity)
        : type_(std::move(type)), id_(id), price_(price), cargoSize_(cargoSize), maxCannons_(cannon),
          health_(health),
          maxHealth_(health),
          particularity_(particularity),
          cannon_(std::make_unique<Cannon>(0,0,0)){}

void Ship::Damage(int damage) {
    health_ -= damage;
}

int Ship::GetHealth() const {
    return health_;
}

void Ship::PrintCargo() {
    std::cout << "Ship inventory: " << std::endl;
    for (auto &cargo: wares_) {
        std::cout << cargo->GetWare() << " amount: " << cargo->GetWareAmount() << std::endl;
    }
}

void Ship::PrintCannons() {
    std::cout << "Cannon inventory: " << std::endl;
    std::cout << "1) Light Cannon amount: " << cannon_->GetCannonAmount(LIGHTCANNON) << "Price: 25 pp" << std::endl;
    std::cout << "2) Medium Cannon amount: " << cannon_->GetCannonAmount(MEDIUMCANNON) << "Price: 100 pp"<< std::endl;
    std::cout << "3) Heavy Cannon amount: " << cannon_->GetCannonAmount(HEAVYCANNON) << "Price: 500 pp"<< std::endl;
}

int Ship::GetCurrentCargoSize() const {
    int amount{0};
    for (auto &item: wares_) {
        amount += item->GetWareAmount();
    }
    return amount;
}

void Ship::PrintCargoSize() {
    int amount{0};
    for (auto &item: wares_) {
        amount += item->GetWareAmount();
    }
    std::cout << "Available cargo space: " << amount << "/" << cargoSize_ << std::endl;
}

void Ship::AddCargo(std::unique_ptr<Wares> &ware) {
    if (wares_.size() <= cargoSize_) {
        wares_.push_back(std::move(ware));
    } else {
        std::cout << "No available space inside the cargo hold, sell some wares or buy a bigger ship." << std::endl;
    }
}

int Ship::GetCargoSize() const {
    return cargoSize_;
}

std::vector<std::unique_ptr<Wares>> &Ship::GetCargo() {
    return wares_;
}

bool Ship::CheckIfCargoFids(int amount) const {
    if (wares_.size() + amount > cargoSize_) {
        std::cout << "No available space inside the cargo hold, sell some wares or buy a bigger ship." << std::endl;
        return false;
    }
    return true;
}

void Ship::Repair(int gold) {
    health_ += gold * 10;
    if (health_ > maxHealth_) health_ = maxHealth_;
}

int Ship::GetMaxHealth() const {
    return maxHealth_;
}

std::unique_ptr<Wares> &Ship::GetWareByName(const std::string &name) {
    for (auto &ware: wares_) {
        if (ware->GetWare() == name) {
            return ware;
        }
    }
}

void Ship::RemoveCargo(const std::string &index, int amount) {
    for (int i{0}; i < wares_.size(); ++i) {
        if (wares_.at(i)->GetWare() == index) {
            wares_.at(i)->SetAmount(wares_.at(i)->GetWareAmount() - amount);
        }
    }
}

void Ship::RemoveAllCargo() {
    wares_.clear();
}

Particularities Ship::GetParticularity() const {
    return particularity_;
}

int Ship::GetMaxCannons() const {
    return maxCannons_;
}

int Ship::GetShipValue() const {
    return price_;
}

std::unique_ptr<Cannon> &Ship::GetCannons() {
    return cannon_;
}

bool Ship::CheckIfCannonFids(int amount) const{
    //check if ship type can have heavy cannons
    if (particularity_ == SMALL) {
        std::cout << "A Small ship can't have heavy cannons" << std::endl;
        return false;
    }
    //check space
    if (cannon_->TotalCannonAmount() + amount == maxCannons_) {
        std::cout << "No available space" << std::endl;
        return false;
    }
    return true;
}

const std::string& Ship::GetType() const {
    return type_;
}

void Ship::PrintStats() {
    std::cout << "Id: " << id_ << std::endl;
    std::cout << "Type: " << type_ << std::endl;
    std::cout << "Price: " << price_ << std::endl;
    std::cout << "particularity: " << particularity_ << std::endl;
    std::cout << "Health: " << GetMaxHealth() << std::endl;
    std::cout << "MaxCannons: " << GetMaxCannons() << std::endl;
    std::cout << "MaxCargo: " << GetCargoSize() << std::endl;
}
