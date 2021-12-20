#pragma once

#include <memory>
#include <iostream>

#include "../domain/player.h"
#include "../domain/port.h"
#include "../states/state.h"
#include "../states/Docked/docked.h"
#include "../sql/sql.h"
#include "../randomizer/dice.h"

class Game {
private:
    std::unique_ptr<Port> port_;
    std::unique_ptr<Player> player_;
    std::unique_ptr<State> state_;

    [[nodiscard]] bool GameOver() const;
    [[nodiscard]] bool Victory() const;
    void SetupGame();
    void Print();
public:
    Game();
    void StartGame();
};
