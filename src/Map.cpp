#include "Map.h"
#include <fstream>


Map::Map(sf::RenderWindow &window) : window(window) {
    std::ifstream fin("Resources/map.csv");
    texture.loadFromFile("Resources/map1.png");
    fin >> count;
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

    for (int i = 0; i < count; i++) {
        std::pair<int, int> tmp;
        fin >> tmp.second >> tmp.first;
        start.push_back(tmp);
    }
    fin.close();
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

    //std::cout << width << " " << height << " " << start.first << " " << start.second << std::endl;
    int move = 0; // 1 - down, 2 - up, 3 - right, 4 - left, 0 - default

    for (auto s: start) {
        std::cout << "start.x "<< s.first << " start.y " << s.second << ";" << std::endl;
        LogicMap tmpRoadRect;
        if (s.first == 0) {
            move = 3;
        } else if (s.first == (width - 1)) {
            move = 4;
        } else if (s.second == 0) {
            move = 1;
        } else if (s.second == (height - 1)) {
            move = 2;
        }
        if ((s.first == 0) && (s.second == 3)) {
            move = 2;
        }

        if ((s.first == 17) && (s.second == 8)) {
            move = 1;
        }

        std::cout << move << std::endl;

        std::pair<int, int> this1, this2;
        this1.first = s.second;
        this1.second = s.first;
        this2.first = s.second;
        this2.second = s.first;

        std::pair<sf::FloatRect, Direction> rect;
        rect.first.height = 0;
        rect.first.width = 0;


        std::cout << s.first << " " << s.second << " " << move << std::endl;
        if (move == 1 || move == 2) {
            this2.second = this1.second + 1;
            rect.first.width = TILE_SIZE;
            sf::Vector2f st((s.first + 1) * TILE_SIZE, (s.second) * TILE_SIZE);
            if (move == 1) {
                rect.first.top = (s.second) * TILE_SIZE;
                rect.first.left = (s.first + 0.5) * TILE_SIZE;
                rect.first.width = TILE_SIZE;
                rect.second = DOWN;
            }
            tmpRoadRect.start = st;
        } else if (move == 3 || move == 4) {
            if (move == 3) {
                rect.first.top = (s.second + 0.5) * TILE_SIZE;
                rect.first.left = (s.first - 0.5) * TILE_SIZE;
                rect.first.width = 0.5 * TILE_SIZE;
            }
            this2.first = s.second + 1;
            rect.first.height = TILE_SIZE;
            sf::Vector2f st((s.first) * TILE_SIZE, (s.second + 1) * TILE_SIZE);
            tmpRoadRect.start = st;
        }

        std::pair<long, long> point;
//    sf::Vector2f s((start.first + 1) * TILE_SIZE, (start.second) * TILE_SIZE);
//            roadRect.start = s;
        while ((this1.first == s.second || (this1.first != height && this1.first != -1)) &&
               (this1.second == s.first || (this1.second != width && this1.second != -1)) &&
               (map[this1.first][this1.second].getTileNumber() != 16 || map[this2.first][this2.second].getTileNumber() != 16)) {
            //std::cout << "(" << this1.first + 1 << ";" << this1.second + 1 << ") " << " (" << this2.first + 1 << ";"
            //          << this2.second + 1 << ")" << std::endl;
            switch (move) {
                case 1:
                    if (map[this1.first][this1.second].getTileNumber() == 18) {
                        std::cout << "!1!" << std::endl;
                        rect.second = DOWN;
                        tmpRoadRect.road.push_back(rect);
                        rect.first.top = (this1.first - 0.5) * TILE_SIZE;
                        rect.first.left = (this1.second + 0.5) * TILE_SIZE;
                        this1.first--;
                        this1.second++;
                        move = 3;
                        rect.first.width = 0.5 * TILE_SIZE;
                        rect.first.height = TILE_SIZE;
                    } else if (map[this2.first][this2.second].getTileNumber() == 19) {
                        std::cout << "!2!" << std::endl;
                        rect.second = DOWN;
                        tmpRoadRect.road.push_back(rect);
                        this1.first--;
                        this2.second--;
                        move = 4;
                        rect.first.width = 0.5 * TILE_SIZE;
                        rect.first.height = TILE_SIZE;
                    } else {
                        std::cout << "!3!" << std::endl;
                        rect.first.height += TILE_SIZE;
                        this1.first++;
                        this2.first++;
                    }
                    break;
                case 2:
                    if (map[this1.first][this1.second].getTileNumber() == 3) {
                        std::cout << "!4!" << std::endl;
                        rect.second = UP;
                        rect.first.top = (this1.first + 1) * TILE_SIZE;
                        rect.first.left = (this1.second + 0.5) * TILE_SIZE;
                        tmpRoadRect.road.push_back(rect);
                        rect.first.top = (this1.first + 0.5) * TILE_SIZE;
                        rect.first.left = (this1.second + 0.5) * TILE_SIZE;
                        this2.first++;
                        this1.second++;
                        move = 3;
                        rect.first.width = 0.5 * TILE_SIZE;
                        rect.first.height = TILE_SIZE;
                    } else if (map[this2.first][this2.second].getTileNumber() == 4) {
                        std::cout << "!5!" << std::endl;
                        rect.second = UP;
                        rect.first.top = (this1.first + 1) * TILE_SIZE;
                        rect.first.left = (this1.second + 0.5) * TILE_SIZE;
                        tmpRoadRect.road.push_back(rect);
                        this2.first++;
                        this2.second--;
                        move = 4;
                        rect.first.width = 0.5 * TILE_SIZE;
                        rect.first.height = TILE_SIZE;
                    } else {
                        std::cout << "!6!" << std::endl;
                        rect.first.height += TILE_SIZE;
                        this1.first--;
                        this2.first--;
                    }
                    break;

                case 3:
                    if (map[this1.first][this1.second].getTileNumber() == 4) {
                        std::cout << "!7!" << std::endl;
                        rect.second = RIGHT;
                        tmpRoadRect.road.push_back(rect);
                        this1.first++;
                        this1.second--;
                        rect.first.left = (this1.second + 0.5) * TILE_SIZE;
                        rect.first.top = (this1.first - 0.5) * TILE_SIZE;
                        move = 1;
                        rect.first.width = TILE_SIZE;
                        rect.first.height = 0.5 * TILE_SIZE;
                    } else if (map[this2.first][this2.second].getTileNumber() == 19) {
                        std::cout << "!8!" << std::endl;
                        rect.second = RIGHT;
                        tmpRoadRect.road.push_back(rect);
                        this1.second--;
                        this2.first--;
                        move = 2;
                        rect.first.width = TILE_SIZE;
                        rect.first.height = 0.5 * TILE_SIZE;
                    } else {
                        std::cout << "!9!" << std::endl;
                        rect.first.width += TILE_SIZE;
                        this1.second++;
                        this2.second++;
                    }
                    break;
                case 4:
                    if (map[this1.first][this1.second].getTileNumber() == 3) {
                        std::cout << "!10!" << std::endl;
                        rect.first.top = (this1.first + 0.5) * TILE_SIZE;
                        rect.first.left = (this1.second + 1) * TILE_SIZE;
                        rect.second = LEFT;
                        tmpRoadRect.road.push_back(rect);
                        rect.first.top = (this1.first + 0.5) * TILE_SIZE;
                        rect.first.left = (this1.second + 0.5) * TILE_SIZE;
                        this1.first++;
                        this2.second++;
                        move = 1;
                        rect.first.width = TILE_SIZE;
                        rect.first.height = 0.5 * TILE_SIZE;
                    } else if (map[this2.first][this2.second].getTileNumber() == 18) {
                        std::cout << "!11!" << std::endl;
                        rect.first.top = (this1.first + 0.5) * TILE_SIZE;
                        rect.first.left = (this1.second + 1) * TILE_SIZE;
                        rect.second = LEFT;
                        tmpRoadRect.road.push_back(rect);
                        this2.second++;
                        this2.first--;
                        move = 2;
                        rect.first.width = TILE_SIZE;
                        rect.first.height = 0.5 * TILE_SIZE;
                    } else {
                        std::cout << "!12!" << std::endl;
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
            tmpRoadRect.finish.top = (this1.first) * TILE_SIZE;
            tmpRoadRect.finish.left = (this1.second + 0.5) * TILE_SIZE;
            tmpRoadRect.finish.height = TILE_SIZE;
            tmpRoadRect.finish.width = TILE_SIZE;
            tmpRoadRect.road.push_back(rect);
        } else if (move == 2) {
            tmpRoadRect.finish.top = (this1.first) * TILE_SIZE;
            tmpRoadRect.finish.left = (this1.second + 0.5) * TILE_SIZE;
            tmpRoadRect.finish.height = TILE_SIZE;
            tmpRoadRect.finish.width = TILE_SIZE;
            rect.second = UP;
            rect.first.top = (this1.first + 1) * TILE_SIZE;
            rect.first.left = (this1.second + 0.5) * TILE_SIZE;
            tmpRoadRect.road.push_back(rect);
        } else if (move == 4) {
            rect.second = LEFT;
            tmpRoadRect.finish.top = (this1.first + 0.5) * TILE_SIZE;
            tmpRoadRect.finish.left = (this1.second) * TILE_SIZE;
            tmpRoadRect.finish.height = TILE_SIZE;
            tmpRoadRect.finish.width = TILE_SIZE;
            rect.first.top = (this1.first + 0.5) * TILE_SIZE;
            rect.first.left = (this1.second + 0.5) * TILE_SIZE;
            tmpRoadRect.road.push_back(rect);
        }
        std::cout << tmpRoadRect.start.x << " !! " << tmpRoadRect.start.y;
        roadRect.push_back(tmpRoadRect);
    }
}

void Map::draw() {
    for (auto row : map) {
        for(auto tile : row) {
            window.draw(tile);
        }
    }

//    for (auto roadRects : roadRect) {
//        for (auto roads : roadRects.road) {
//            sf::RectangleShape r(sf::Vector2f(roads.first.width, roads.first.height));
//            r.setPosition(roads.first.left, roads.first.top);
//            r.setOutlineColor(sf::Color::Black);
//            r.setOutlineThickness(0.5);
//            if (roads.second == UP) {
//                r.setFillColor(sf::Color::Red);
//            } else if (roads.second == DOWN) {
//                r.setFillColor(sf::Color::Green);
//            } else if (roads.second == LEFT) {
//                r.setFillColor(sf::Color::Blue);
//            } else if (roads.second == RIGHT) {
//                r.setFillColor(sf::Color::White);
//            }
//
//            //sf::Rect r(i.left, i.top, i.width, i.height);
//            window.draw(r);
//        }
//        sf::RectangleShape f(sf::Vector2f(roadRects.finish.width, roadRects.finish.height));
//        f.setPosition(roadRects.finish.left, roadRects.finish.top);
//        f.setFillColor(sf::Color::Black);
//        window.draw(f);
//    }

}

void Map::getRoadRect(std::vector<LogicMap>& road) const {
    road = roadRect;
}