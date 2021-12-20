#include "port.h"

Port::Port(int id, std::string name, std::vector<std::unique_ptr<Wares>>& wares, std::unique_ptr<Cannon>& cannon, std::vector<std::unique_ptr<Ship>>& ships)
: id_(id), name_(std::move(name)) ,wares_(std::move(wares)),ships_(std::move(ships)),cannon_(std::move(cannon)) {}

void Port::PrintWares() {
    for (auto& ware : wares_) {
        std::cout << ware->GetWare() << std::endl;
    }
}

std::vector<std::unique_ptr<Wares>> &Port::GetWares() {
    return wares_;
}

int Port::GetId() const {
    return id_;
}

void Port::RemoveWareFromStock(const std::string& item, int amount) {
    for (auto& ware : wares_) {
        if (ware->GetWare() == item && ware->GetWareAmount() - amount > 0){
            ware->SetAmount(ware->GetWareAmount() - amount);
        }
    }
}

std::unique_ptr<Wares>& Port::GetWareByName(const std::string& name) {
    for (auto& ware : wares_) {
        if (ware->GetWare() == name){
            return ware;
        }
    }
}

void Port::RemoveCannonFromStock(CannonType type, int amount) {
    cannon_->RemoveCannons(type, amount);
}

std::unique_ptr<Cannon> &Port::GetCannon() {
    return cannon_;
}

void Port::PrintCanons() {
    std::cout << "Cannon inventory: " << std::endl;
    std::cout << "1) Light Cannon amount: " << cannon_->GetCannonAmount(LIGHTCANNON) << "Price: 50 pp" << std::endl;
    std::cout << "2) Medium Cannon amount: " << cannon_->GetCannonAmount(MEDIUMCANNON) << "Price: 200 pp"<< std::endl;
    std::cout << "3) Heavy Cannon amount: " << cannon_->GetCannonAmount(HEAVYCANNON) << "Price: 1000 pp"<< std::endl;
}

void Port::PrintShips() {
    for (auto& ship : ships_) {
        std::cout << "Ship stats: " << std::endl;
        ship->PrintStats();
        std::cout << "-----------------------------------" << std::endl;
    }
}

const std::string &Port::GetName() const {
    return name_;
}
