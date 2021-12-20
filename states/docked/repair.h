#pragma once
#include "../state.h"
#include "../../domain/player.h"
#include "../../domain/port.h"
#include "docked.h"


class Repair : public State {
private:
    const std::string state_;
    const std::vector<std::string> moves_;
    Player& player_;
    Port& port_;
public:
    explicit Repair(Player &player, Port &port);
    [[nodiscard]] const std::vector<std::string> &Moves() const override;
    [[nodiscard]] const std::string &GetState() const override;
    std::unique_ptr<State> Move(int) override;
    void RepairShip();
};
