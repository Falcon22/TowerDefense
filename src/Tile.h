//
// Created by Falcon on 21.04.2018.
//

#ifndef TOWERDEFENSE_TILE_H
#define TOWERDEFENSE_TILE_H

#include <SFML/Graphics.hpp>

class Tile : public sf::Drawable, public sf::Transformable
{
public:
    enum class Type
    {
        None = 0,
        Invalid,
        Valid
    };

    Tile();

    //void setState(Type state);
    void setTexture(const sf::Texture &texture, sf::IntRect rect);
    void setTileNumber(int number);

    //const Type getState() const;
    const int getTileNumber() const;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    int tileNumber;
    Type state;
    sf::Sprite sprite;
    sf::Vector2i position;
};

#endif //TOWERDEFENSE_TILE_H
