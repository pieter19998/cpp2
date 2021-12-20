#pragma once
#include <string>

class Wares {
    std::string ware_;
    int id_,  wareAmount_, price_;

public:
    Wares(std::string&, int,int,int);
    [[nodiscard]] const std::string& GetWare() const;
    [[nodiscard]] int GetId() const;
    [[nodiscard]] int GetWareAmount() const;
    [[nodiscard]] int GetPrice() const;
    [[nodiscard]] std::string GetWareCopy() const;
    void SetAmount(int amount);
};