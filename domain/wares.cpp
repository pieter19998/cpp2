#include "wares.h"

Wares::Wares(std::string & ware, int id, int wareAmount, int price) : ware_(std::move(ware)), id_(id), wareAmount_(wareAmount), price_(price){}

const std::string& Wares::GetWare() const {
    return ware_;
}

std::string Wares::GetWareCopy() const {
    return ware_;
}

int Wares::GetId() const {
    return id_;
}

int Wares::GetWareAmount() const {
    return wareAmount_;
}

int Wares::GetPrice() const {
    return price_;
}

void Wares::SetAmount(int amount) {
    wareAmount_ = amount;
}
