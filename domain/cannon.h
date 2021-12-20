#pragma once
#include <unordered_map>
#include "enum/cannonType.h"

class Cannon {
private:
    std::unordered_map<CannonType, int> cannons_;

public:
    Cannon(int,int,int);

    [[nodiscard]] int GetCannonAmount(CannonType) const;
    [[nodiscard]] int TotalCannonAmount() const;
    [[nodiscard]] std::unordered_map<CannonType, int>& GetCannons();

    void AddCannon(CannonType, int);

    void RemoveCannons(CannonType, int);
};