#pragma once
#include "../state.h"
#include "../../domain/player.h"
#include "../../domain/port.h"

class Docked : public State  {
private:
    const std::string state_;
    const std::vector<std::string> moves_;
    Player& player_;
    Port& port_;
    void Quit();
public:
    explicit Docked(Player &player, Port &port);
    [[nodiscard]] const std::vector<std::string>& Moves() const override;
    [[nodiscard]] const std::string &GetState() const override;
    [[nodiscard]] std::unique_ptr<State> Move(int) override;
    ~Docked() override = default;
};
