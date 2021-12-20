#include "ship.h"
#include "../logger/logger.h"

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
    Logger::get().PrintAndLog("Ship inventory: ");
    for (auto &cargo: wares_) {
        std::cout << cargo->GetWare() << " amount: " << cargo->GetWareAmount() << std::endl;
    }
}

void Ship::PrintCannons() {
    Logger::get().PrintAndLog("Cannon inventory: ");
    Logger::get().PrintAndLog("1) Light Cannon amount: " + std::to_string(cannon_->GetCannonAmount(LIGHTCANNON)) + "Price: 25 pp");
    Logger::get().PrintAndLog("2) Medium Cannon amount: " + std::to_string(cannon_->GetCannonAmount(MEDIUMCANNON)) + "Price: 100 pp");
    Logger::get().PrintAndLog("3) Heavy Cannon amount: " + std::to_string(cannon_->GetCannonAmount(HEAVYCANNON)) + "Price: 500 pp");
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
    Logger::get().PrintAndLog("Available cargo space: " + std::to_string(amount) + "/" + std::to_string(cargoSize_));
}

void Ship::AddCargo(std::unique_ptr<Wares> &ware) {
    if (wares_.size() <= cargoSize_) {
        wares_.push_back(std::move(ware));
    } else {
        Logger::get().PrintAndLog("No available space inside the cargo hold, sell some wares or buy a bigger ship.");
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
        Logger::get().PrintAndLog("No available space inside the cargo hold, sell some wares or buy a bigger ship.");
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
        Logger::get().PrintAndLog("A Small ship can't have heavy cannons");
        return false;
    }
    //check space
    if (cannon_->TotalCannonAmount() + amount == maxCannons_) {
        Logger::get().PrintAndLog("No available space");
        return false;
    }
    return true;
}

const std::string& Ship::GetType() const {
    return type_;
}

void Ship::PrintStats() {
    Logger::get().PrintAndLog("Id: " + std::to_string(id_));
    Logger::get().PrintAndLog("Type: " + type_);
    Logger::get().PrintAndLog("Price: " + std::to_string(price_));
    Logger::get().PrintAndLog("Particularity: " + std::to_string(particularity_));
    Logger::get().PrintAndLog("MaxHealth: " + std::to_string(GetMaxHealth()));
    Logger::get().PrintAndLog("MaxCannons: " + std::to_string(GetMaxCannons()));
    Logger::get().PrintAndLog("MaxCargo: " + std::to_string(GetCargoSize()));
}
