#pragma once
#include <memory>
class Dice {
private:
    Dice() = default;
    static Dice _singleton;

public:
    Dice(Dice &other) = delete;
    void operator=(const Dice &) = delete;
    static Dice& get();
    [[nodiscard]] int generateNumber(int,int) const;
};