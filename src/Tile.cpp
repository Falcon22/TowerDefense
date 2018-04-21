//
// Created by Falcon on 21.04.2018.
//

#include "Tile.h"

Tile::Tile()
        : state(Tile::Type::None)
{}


void Tile::setTexture(const sf::Texture &texture, sf::IntRect rect)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
}

void Tile::setTileNumber(int number)
{
    tileNumber = number;
}

const int Tile::getTileNumber() const
{
    return tileNumber;
}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
}