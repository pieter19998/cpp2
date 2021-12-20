#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include "wares.h"
#include "../domain/cannon.h"
#include "ship.h"

class Port {
private:
    int id_;
    std::string name_;
    std::vector<std::unique_ptr<Wares>> wares_;
    std::vector<std::unique_ptr<Ship>> ships_;
    std::unique_ptr<Cannon> cannon_;

public:
    explicit Port(int, std::string, std::vector<std::unique_ptr<Wares>> &, std::unique_ptr<Cannon>&,std::vector<std::unique_ptr<Ship>>&);
    void PrintWares();
    void PrintCanons();
    void PrintShips();

    [[nodiscard]] std::vector<std::unique_ptr<Wares>>& GetWares();
    [[nodiscard]] std::unique_ptr<Cannon>& GetCannon();
    [[nodiscard]] std::unique_ptr<Wares>& GetWareByName(const std::string&);
    [[nodiscard]] const std::string& GetName() const;
    [[nodiscard]] int GetId() const;

    void RemoveWareFromStock(const std::string &item, int amount);
    void RemoveCannonFromStock(CannonType, int);
};
