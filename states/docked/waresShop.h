#pragma once
#include "../state.h"
#include "../../domain/player.h"
#include "../../domain/port.h"

class WaresShop : public State{
private:
    const std::string state_;
    const std::vector<std::string> moves_;
    Player& player_;
    Port& port_;

    void SellWares();
    void BuyWares();
public:
    explicit WaresShop(Player &player, Port &port);
    [[nodiscard]] const std::vector<std::string> &Moves() const override;
    [[nodiscard]] const std::string &GetState() const override;
    std::unique_ptr<State> Move(int) override;
    ~WaresShop() override = default;
};
