#include "setSail.h"
#include "../sea/sailing.h"
#include <algorithm>

SetSail::SetSail(Player &player, Port &port) :
        state_("Set Sail"),
        moves_(std::vector<std::string>{"1) Choose Destination", "2) Back to Port"}),
        player_(player), port_(port) {}

const std::vector<std::string> &SetSail::Moves() const {
    return moves_;
}

const std::string &SetSail::GetState() const {
    return state_;
}

std::unique_ptr<State> SetSail::Move(int action) {
    switch (action) {
        case 1:
            return Sail();
        case 2:
            return std::make_unique<Docked>(player_, port_);
        default:
            return std::make_unique<SetSail>(player_, port_);
    }
}

std::unique_ptr<State> SetSail::Sail() const  {
    //print all ports and distances
    std::cout << "Current Port: " << port_.GetName() << std::endl;
    auto sql{std::make_unique<Sql>()};
    auto availablePorts {std::vector<int>()};
    for (int i{1}; i < 24; ++i) {
        int distance{sql->GetDistance(port_.GetId(), i)};
        auto port{sql->GetPort(i)};
        if (distance > 0){
            std::cout << port->GetId() << ") " << port->GetName() << " distance: " << distance << std::endl;
            availablePorts.emplace_back(port->GetId());
        }
    }
//user input
    std::string destination;
    std::cout << "Type number of port to sail to." << std::endl;
    std::cin >> destination;
//set sail
    try{
        //check if port exists
        int id {std::stoi(destination)};
        if(std::find(availablePorts.begin(), availablePorts.end(), id) == availablePorts.end()){
            std::cout << "This Port is not available" << std::endl;
            return std::make_unique<SetSail>(player_, port_);
        }
        auto finalDestination {sql->GetPort(id)};
        return std::make_unique<Sailing>(player_,finalDestination, sql->GetDistance(port_.GetId(), id));
    } catch (...) {
        std::cout << "Invalid input" << std::endl;
    }
    return std::make_unique<SetSail>(player_, port_);
}