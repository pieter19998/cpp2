#pragma once

#include <string>
#include <vector>
#include <memory>

class State{
public:
    virtual ~State() = default;
    [[nodiscard]] virtual const std::vector<std::string>& Moves() const = 0;
    [[nodiscard]] virtual const std::string& GetState() const = 0 ;
    [[nodiscard]] virtual std::unique_ptr<State> Move(int) = 0;
};