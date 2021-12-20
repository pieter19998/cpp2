#include "game.h"
#include "../logger/logger.h"

Game::Game() : player_(nullptr), port_(nullptr), state_(nullptr) {}

void Game::StartGame() {
    try { SetupGame(); }
    catch (...) {
        Logger::get().PrintAndLog("Error setting up game");
        return;
    }
    while (player_->GetPlaying()) {
        //print options
        PrintMoves();
        std::string input;
        std::cin >> input;
        Logger::get().Log(input);
        state_ = state_->Move(std::stoi(input));
        //check game status
        if (GameOver()) {
            Logger::get().PrintAndLog("Game Over");
            break;
        }
        if (Victory()) {
            Logger::get().PrintAndLog("Victory");
            break;
        }
    }
}

bool Game::GameOver() const {
    return (player_->GetShip().GetHealth() <= 0);
}

bool Game::Victory() const {
    return (player_->GetFunds() >= 1000000);
}

void Game::SetupGame() {
    auto sql = std::make_unique<Sql>();
    auto ship{sql->GetShip(Dice::get().generateNumber(1, 13))};
    player_ = std::make_unique<Player>(Dice::get().generateNumber(100000, 250000), ship);
    port_ = sql->GetPort(Dice::get().generateNumber(1, 24));
    state_ = std::make_unique<Docked>(*player_, *port_);
    Logger::get().ClearFile();
}

void Game::PrintMoves() {
    for (auto &move: state_->Moves()) {
        Logger::get().PrintAndLog(move);
    }
}
