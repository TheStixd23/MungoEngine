#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>


inline const std::vector<sf::Vector2f>& getCircuitWaypoints() {
    static const std::vector<sf::Vector2f> kCircuit = {
    {1134,432}, {1134,310}, {910,305}, {910,130}, {500,130},
    {500,500}, {680,500}, {890,435}, {890,820}, {700,820},
    {560,860}, {500,800}, {625,670}, {1132,670}, {1132,400}


    };
    return kCircuit;
}