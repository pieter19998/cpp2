#pragma once

#include <memory>
#include <iostream>
#include <vector>
#include "../domain/ship.h"
#include "../domain/enum/Particularities.h"
#include "../domain/wares.h"
#include "../randomizer/dice.h"
#include "sqlite3.h"
#include "../domain/port.h"

class Sql {
private:
    std::vector<std::string> queryData_;
public:
    [[nodiscard]] std::unique_ptr<Ship>GetShip(int) const;
    [[nodiscard]] int GetDistance(int, int) const;
    [[nodiscard]] Particularities StringToParticularity(const std::string &particularity) const;
    [[nodiscard]] std::unique_ptr<Port> GetPort(int) const;
    [[nodiscard]] std::vector<std::unique_ptr<Wares>> GetWares(int portId) const;
};
