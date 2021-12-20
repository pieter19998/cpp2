#pragma once
#include "../state.h"
#include "../../domain/player.h"
#include "../../domain/port.h"
#include "../docked/docked.h"
#include "../../sql/sql.h"

class Sailing : public State{
private:
    const std::string state_;
    const std::vector<std::string> moves_;
    Player& player_;
    std::unique_ptr<Port> port_;
    int turns_, distance_;
    void Nothing();
    void Breeze();
    void Weak();
    void Normal();
    void Strong();
    void Storm();
public:
    explicit Sailing(Player &player, std::unique_ptr<Port>&, int);
    [[nodiscard]] const std::vector<std::string> &Moves() const override;
    [[nodiscard]] const std::string &GetState() const override;
    std::unique_ptr<State> Move(int) override;
};