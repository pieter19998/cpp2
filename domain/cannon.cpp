#include "cannon.h"

Cannon::Cannon(int light, int medium, int heavy) {
    cannons_.insert( {{LIGHTCANNON,light},{MEDIUMCANNON,medium},{HEAVYCANNON, heavy} } );
}

void Cannon::AddCannon(CannonType type, int amount) {
    cannons_.find(type)->second = cannons_.find(type)->second + amount;
}

void Cannon::RemoveCannons(CannonType type, int amount) {
    cannons_.find(type)->second = cannons_.find(type)->second - amount;
}

int Cannon::GetCannonAmount(CannonType type) const {
    return  cannons_.find(type)->second;
}

int Cannon::TotalCannonAmount() const {
    return cannons_.find(LIGHTCANNON)->second + cannons_.find(MEDIUMCANNON)->second +
           cannons_.find(HEAVYCANNON)->second;
}

std::unordered_map<CannonType, int> &Cannon::GetCannons(){
    return cannons_;
}