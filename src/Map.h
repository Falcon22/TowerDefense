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
    void analyze(std::vector<sf::Vector2f>& towers1, std::vector<sf::Vector2f>& towers2);


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

    std::vector<LogicMap> roadRect;
public:
     void getRoadRect(std::vector<LogicMap>&) const;

private:
    sf::RenderWindow &window;
    sf::Texture texture;
    std::vector<std::vector<Tile>> map;
    int count;
    int width;
    int height;
    std::vector<std::pair<int, int>> start;
    std::vector<sf::Vector2f> t1;
    std::vector<sf::Vector2f> t2;

};


#endif //TOWERDEFENSE_MAP_H
