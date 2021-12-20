#pragma once

#include <memory>
#include <iostream>
#include "ship.h"

class Player {
private:
    int gold_;
    std::unique_ptr<Ship> ship_;
    bool playing_;

public:
    Player(int, std::unique_ptr<Ship>&);
    void Earn(int);
    void Spend(int);
    void SetPlaying(bool);
    void SetShip(std::unique_ptr<Ship>&);
    void PrintGold();
    [[nodiscard]]bool CheckFunds(int) const;
    [[nodiscard]] int GetFunds() const;
    [[nodiscard]] Ship& GetShip() const;
    [[nodiscard]] bool GetPlaying() const;
};
