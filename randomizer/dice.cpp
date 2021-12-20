#include "dice.h"

#include <random>

Dice Dice::_singleton;

int Dice::generateNumber(int from, int to) const {
    std::random_device dev;
    std::default_random_engine dre {dev()};
    std::uniform_int_distribution<int> dist {from, to};
    return dist(dre);
}

Dice &Dice::get() {
    return _singleton;
}
