#ifndef TOWERDEFENSE_GRAPHICSUNIT_H
#define TOWERDEFENSE_GRAPHICSUNIT_H


#include <SFML/Graphics/Sprite.hpp>
#include "../../ResourceManager/ResourcesIdentifier.h"
#include "../../GameContext.h"
#include "../Warrior/Warrior.h"

class GraphicsUnit {
public:
    GraphicsUnit(sf::RenderWindow &window, Type type, const TextureHolder& textureHolder);
    void update(Warrior& unit, const sf::Time& dTime);
    void draw() {
        window_.draw(sprite_);
    }
private:
    sf::Sprite sprite_;
    int width_;
    int height_;
    float currentFrame_;
    const unsigned int kAnimationSpeed_ = 5;
    const unsigned int kFrames_ = 4;
    sf::RenderWindow& window_;
};


#endif //TOWERDEFENSE_GRAPHICSUNIT_H
