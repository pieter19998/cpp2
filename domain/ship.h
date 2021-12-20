#pragma once

#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include "enum/Particularities.h"
#include "wares.h"
#include "cannon.h"

class Ship {
private:
    std::string type_;
    int id_, price_, cargoSize_, maxCannons_, health_, maxHealth_;
    Particularities particularity_;
    std::vector<std::unique_ptr<Wares>> wares_;
    std::unique_ptr<Cannon> cannon_;

public:
    explicit Ship(std::string &, int, int, int, int, int, Particularities);

    [[nodiscard]]int GetHealth() const;

    [[nodiscard]]int GetMaxHealth() const;

    [[nodiscard]]int GetMaxCannons() const;

    [[nodiscard]]int GetCargoSize() const;

    [[nodiscard]]int GetShipValue() const;

    [[nodiscard]]const std::string &GetType() const;

    [[nodiscard]]std::unique_ptr<Cannon> &GetCannons();

    [[nodiscard]]bool CheckIfCargoFids(int) const;

    [[nodiscard]]std::vector<std::unique_ptr<Wares>> &GetCargo();

    [[nodiscard]] int GetCurrentCargoSize() const;

    [[nodiscard]] Particularities GetParticularity() const;

    [[nodiscard]] bool CheckIfCannonFids(int) const;

    std::unique_ptr<Wares> &GetWareByName(const std::string &);

    void Damage(int);

    void Repair(int points);

    void PrintCargo();

    void PrintCargoSize();

    void PrintStats();

    void PrintCannons();

    void AddCargo(std::unique_ptr<Wares> &);

    void RemoveCargo(const std::string &, int);
    void RemoveAllCargo();
};
