#pragma once
#include "../state.h"
#include "../../domain/player.h"
#include "../../domain/port.h"

class Fighting : public State  {
private:
    const std::string state_;
    const std::vector<std::string> moves_;
    Player& player_;
    Port& port_;
    std::unique_ptr<Ship> enemy_;
    bool fighting_;
    void Fire(Ship& ,Ship&);
    void Escape();
    void Surrender();
public:
    explicit Fighting(Player &player, Port &port, std::unique_ptr<Ship>&);
    [[nodiscard]] const std::vector<std::string>& Moves() const override;
    [[nodiscard]] const std::string &GetState() const override;
    [[nodiscard]] std::unique_ptr<State> Move(int) override;
    ~Fighting() override = default;
};
