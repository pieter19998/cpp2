#pragma once
#include "../state.h"
#include "../../domain/player.h"
#include "../../domain/port.h"
#include "../../sql/sql.h"
#include "docked.h"
class SetSail : public State{
private:
    const std::string state_;
    const std::vector<std::string> moves_;
    Player& player_;
    Port& port_;
    [[nodiscard]] std::unique_ptr<State> Sail() const ;
public:
    explicit SetSail(Player &player, Port &port);
    [[nodiscard]] const std::vector<std::string> &Moves() const override;
    [[nodiscard]] const std::string &GetState() const override;
    std::unique_ptr<State> Move(int) override;
};