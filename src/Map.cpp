#include "Map.h"
#include <fstream>


Map::Map(sf::RenderWindow &window) : window(window) {
    std::ifstream fin("Resources/map.csv");
    texture.loadFromFile("Resources/map1.png");

    fin >> height >> width;
    map.resize(height, std::vector<Tile>(width));
    int tileNumber;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fin >> tileNumber;
            map[i][j].setTileNumber(tileNumber);
            if (tileNumber == 13 || tileNumber == 14) {
                map[i][j].setTileNumber(tileNumber);
                tileNumber = 16;
            }
            sf::IntRect rect{ TILE_SIZE * (tileNumber % 15), TILE_SIZE * (tileNumber / 15), TILE_SIZE, TILE_SIZE };
            map[i][j].setTexture(texture, rect);
            map[i][j].setPosition(static_cast<float>(j * TILE_SIZE), static_cast<float>(i * TILE_SIZE));
        }
    }
    fin >> start.second >> start.first;
}


void Map::analyze(std::vector<sf::Vector2f>& towers1, std::vector<sf::Vector2f>& towers2) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j].getTileNumber() == 13 || map[i][j].getTileNumber() == 14) {
                sf::Vector2f tmp((j + 0.5) * TILE_SIZE, (i + 0.5) * TILE_SIZE);
                if (map[i][j].getTileNumber() == 13) {
                    towers1.push_back(tmp);
                } else {
                    towers2.push_back(tmp);
                }
            }
        }
    }

    std::cout << width << " " << height << " " << start.first << " " << start.second << std::endl;
    int move = 0; // 1 - down, 2 - up, 3 - right, 4 - left, 0 - default

    if (start.first == 0) {
        move = 3;
    } else if (start.first == (width - 1)) {
        move = 4;
    } else if (start.second == 0) {
        move = 1;
    } else if (start.second == (height - 1)) {
        move = 2;
    }

    std::cout << move << std::endl;

    std::pair<int, int> this1, this2;
    this1.first = start.second;
    this1.second = start.first;
    this2.first = start.second;
    this2.second = start.first;

    std::pair<sf::FloatRect, Direction> rect;
    rect.first.height = 0;
    rect.first.width = 0;


    std::cout << start.first <<  " " << start.second << " " << move << std::endl;
    if (move == 1 || move == 2) {
        this2.first = start.second + 1;
        rect.first.width = TILE_SIZE;
        sf::Vector2f s((start.first + 1) * TILE_SIZE, (start.second) * TILE_SIZE);
        roadRect.start = s;
    } else if (move == 3 || move == 4) {
        this2.first = start.second + 1;
        rect.first.height = TILE_SIZE;
        sf::Vector2f s((start.first - 5) * TILE_SIZE, (start.second - 5) * TILE_SIZE);
        roadRect.start = s;
    }

    std::pair<long, long> point;
//    sf::Vector2f s((start.first + 1) * TILE_SIZE, (start.second) * TILE_SIZE);
//            roadRect.start = s;
    while ((this1.first == start.second || (this1.first != height && this1.first != 0)) &&
           (this1.second == start.first || (this1.second != width && this1.second != 0))) {
        std::cout << "(" << this1.first + 1<< ";" << this1.second + 1<< ") "<< " (" << this2.first + 1<< ";" << this2.second + 1<< ")" << std::endl;
        switch (move) {
            case 1:
                if (map[this1.first][this1.second].getTileNumber() == 18) {
                    rect.second = DOWN;
                    roadRect.road.push_back(rect);
                    rect.first.top = (this1.first - 0.5) * TILE_SIZE;
                    rect.first.left = (this1.second + 0.5) * TILE_SIZE;
                    this1.first--;
                    this1.second++;
                    move = 3;
                    rect.first.width = 0.5 * TILE_SIZE;
                    rect.first.height = TILE_SIZE;
                } else
                if (map[this2.first][this2.second].getTileNumber() == 19) {
                    rect.second = DOWN;
                    roadRect.road.push_back(rect);
                    this1.first--;
                    this2.second--;
                    move = 4;
                    rect.first.width = 0.5 * TILE_SIZE;
                    rect.first.height = TILE_SIZE;
                } else {
                    rect.first.height += TILE_SIZE;
                    this1.first++;
                    this2.first++;
                }
                break;
            case 2:
                if (map[this1.first][this1.second].getTileNumber() == 3) {
                    rect.second = UP;
                    rect.first.top = (this1.first + 1) * TILE_SIZE;
                    rect.first.left = (this1.second + 0.5) * TILE_SIZE;
                    roadRect.road.push_back(rect);
                    rect.first.top = (this1.first + 0.5) * TILE_SIZE;
                    rect.first.left = (this1.second + 0.5) * TILE_SIZE;
                    this2.first++;
                    this1.second++;
                    move = 3;
                    rect.first.width = 0.5 * TILE_SIZE;
                    rect.first.height = TILE_SIZE;
                } else
                if (map[this2.first][this2.second].getTileNumber() == 4) {
                    rect.second = UP;
                    rect.first.top = (this1.first + 1) * TILE_SIZE;
                    rect.first.left = (this1.second + 0.5) * TILE_SIZE;
                    roadRect.road.push_back(rect);
                    this2.first++;
                    this2.second--;
                    move = 4;
                    rect.first.width = 0.5 * TILE_SIZE;
                    rect.first.height = TILE_SIZE;
                } else {
                    rect.first.height += TILE_SIZE;
                    this1.first--;
                    this2.first--;
                }
                break;

            case 3:
                if (map[this1.first][this1.second].getTileNumber() == 4) {
                    rect.second = RIGHT;
                    roadRect.road.push_back(rect);
                    this1.first++;
                    this1.second--;
                    rect.first.left = (this1.second + 0.5) * TILE_SIZE;
                    rect.first.top = (this1.first - 0.5) * TILE_SIZE;
                    move = 1;
                    rect.first.width = TILE_SIZE;
                    rect.first.height = 0.5 * TILE_SIZE;
                } else if (map[this2.first][this2.second].getTileNumber() == 19) {
                    rect.second = RIGHT;
                    roadRect.road.push_back(rect);
                    this1.second--;
                    this2.first--;
                    move = 2;
                    rect.first.width = TILE_SIZE;
                    rect.first.height = 0.5 * TILE_SIZE;
                } else {
                    rect.first.width += TILE_SIZE;
                    this1.second++;
                    this2.second++;
                }
                break;
            case 4:
                if (map[this1.first][this1.second].getTileNumber() == 3) {
                    rect.first.top = (this1.first + 0.5) * TILE_SIZE;
                    rect.first.left = (this1.second + 1) * TILE_SIZE;
                    rect.second = LEFT;
                    roadRect.road.push_back(rect);
                    rect.first.top = (this1.first + 0.5) * TILE_SIZE;
                    rect.first.left = (this1.second + 0.5) * TILE_SIZE;
                    this1.first++;
                    this2.second++;
                    move = 1;
                    rect.first.width = TILE_SIZE;
                    rect.first.height = 0.5 * TILE_SIZE;
                } else if (map[this2.first][this2.second].getTileNumber() == 18) {
                    rect.first.top = (this1.first + 0.5) * TILE_SIZE;
                    rect.first.left = (this1.second + 1) * TILE_SIZE;
                    rect.second = LEFT;
                    roadRect.road.push_back(rect);
                    this2.second++;
                    this2.first--;
                    move = 2;
                    rect.first.width = TILE_SIZE;
                    rect.first.height = 0.5 * TILE_SIZE;
                } else {
                    rect.first.width += TILE_SIZE;
                    this1.second--;
                    this2.second--;
                }
                break;
            default:
                break;
        }
    }

    if (move == 1 || move == 3) {
        if (move == 1) {
            rect.second = DOWN;
        } else if (move == 3) {
            rect.second = RIGHT;
        }
        roadRect.finish.top = (this1.first + 0.5) * TILE_SIZE;
        roadRect.finish.left = (this1.second - 2) * TILE_SIZE;
        roadRect.finish.height = TILE_SIZE;
        roadRect.finish.width = TILE_SIZE;
        roadRect.road.push_back(rect);
    } else if (move == 2) {
        rect.first.top = (this1.first + 1) * TILE_SIZE;
        rect.first.left = (this1.second + 0.5) * TILE_SIZE;
        roadRect.road.push_back(rect);
    } else if (move == 4) {
        rect.first.top = (this1.first + 0.5) * TILE_SIZE;
        rect.first.left = (this1.second + 0.5) * TILE_SIZE;
        roadRect.road.push_back(rect);
    }
   std::cout << roadRect.start.x << " !! " << roadRect.start.y;

}

void Map::draw() {
    for (auto row : map) {
        for(auto tile : row) {
            window.draw(tile);
        }
    }

    for (int i = 1; i >= 0; i--) {
                sf::RectangleShape r(sf::Vector2f(roadRect.road[i].first.width, roadRect.road[i].first.height));
                r.setPosition(roadRect.road[i].first.left, roadRect.road[i].first.top);
                r.setOutlineColor(sf::Color::Black);
                r.setOutlineThickness(0.5);
                if (roadRect.road[i].second == UP) {
                        r.setFillColor(sf::Color::Red);
                    } else if (roadRect.road[i].second == DOWN) {
                        r.setFillColor(sf::Color::Green);
                    } else if (roadRect.road[i].second == LEFT) {
                        r.setFillColor(sf::Color::Blue);
                    } else if (roadRect.road[i].second == RIGHT) {
                        r.setFillColor(sf::Color::White);
                    }

                            //sf::Rect r(i.left, i.top, i.width, i.height);
                                window.draw(r);
            }
        sf::RectangleShape f(sf::Vector2f(roadRect.finish.width, roadRect.finish.height));
        f.setPosition(roadRect.finish.left, roadRect.finish.top);
        f.setFillColor(sf::Color::Black);
        window.draw(f);
}

const Map::LogicMap &Map::getRoadRect() const {
    return roadRect;
}
