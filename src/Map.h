//
// Created by Falcon on 20.04.2018.
//

#ifndef TOWERDEFENSE_MAP_H
#define TOWERDEFENSE_MAP_H

#include <SFML/Graphics/Rect.hpp>

#include <iostream>
#include <vector>

#include "Constants.h"
#include "Tile.h"

class Map {
public:
    Map(sf::RenderWindow &window);
    void draw();
    void analyze();


    enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    struct LogicMap {
        std::vector<std::pair<sf::FloatRect, Direction>> road;
        sf::FloatRect finish;
        sf::Vector2f start;
    };

private:

    LogicMap roadRect;
public:
    const LogicMap &getRoadRect() const;

private:
    sf::RenderWindow &window;
    sf::Texture texture;
    std::vector<std::vector<Tile>> map;
    int width;
    int height;
    std::pair<int, int> start;
};


#endif //TOWERDEFENSE_MAP_H
