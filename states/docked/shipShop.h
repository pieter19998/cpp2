#pragma once
#include "../state.h"
#include "../../domain/player.h"
#include "../../domain/port.h"
#include "docked.h"

class ShipShop : public State {
private:
    const std::string state_;
    const std::vector<std::string> moves_;
    Player& player_;
    Port& port_;
    void SellAndBuyShip();

public:
    ShipShop(Player &player, Port &port);
    [[nodiscard]] const std::vector<std::string>& Moves() const override;
    [[nodiscard]] const std::string &GetState() const override;
    [[nodiscard]] std::unique_ptr<State> Move(int) override;
};
