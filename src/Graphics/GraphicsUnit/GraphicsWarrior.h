#ifndef TOWERDEFENSE_GRAPHICSWARRIOR_H
#define TOWERDEFENSE_GRAPHICSWARRIOR_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include "../../GameContext.h"
#include "../../Units/Warrior/Warrior.h"

class GraphicsWarrior {
public:
    explicit GraphicsWarrior(const Warrior* warrior, States::Context& context);
    void update(const sf::Time& dTime);
    void draw(const States::Context& context);

    bool isFinished() const;

private:
    const Warrior* warrior_;
    sf::Sprite sprite_;
    std::pair<int, int> warriorSpriteRect_;//<width, height>
    float currentFrame_;
    bool finished_;
};


#endif //TOWERDEFENSE_GRAPHICSWARRIOR_H
