#include "game.h"
#include "../logger/logger.h"

Game::Game() : player_(nullptr), port_(nullptr), state_(nullptr) {}

void Game::StartGame() {
    try { SetupGame(); }
    catch (...) {
        std::cout << "Error setting up game" << std::endl;
        return;
    }
    while (player_->GetPlaying()) {
        //print options
        Print();
        std::string input;
        std::cin >> input;
        Logger::get().log(input);
        state_ = state_->Move(std::stoi(input));
        //check game status
        if (GameOver()) {
            std::cout << "Game over." << std::endl;
            break;
        }
        if (Victory()) {
            std::cout << "Victory." << std::endl;
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
}

void Game::Print() {
    for (auto &move: state_->Moves()) {
        Logger::get().log(move);
        std::cout << move << std::endl;
    }
}
