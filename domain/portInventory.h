#pragma once
#include <memory>
#include <vector>
#include "wares.h"

class portInventory {
private:
    std::vector<std::unique_ptr<Wares>> wares_;

public:
    portInventory();
    [[nodiscard]] const std::vector<std::unique_ptr<Wares>>& GetWares() const;
};
