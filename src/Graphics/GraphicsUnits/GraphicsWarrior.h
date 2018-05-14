#ifndef SERVER_GRAPHICSWARRIOR_H
#define SERVER_GRAPHICSWARRIOR_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include "../../GameContext.h"
#include "../../Units/Warrior/Warrior.h"

class GraphicsWarrior {
public:
    explicit GraphicsWarrior(std::shared_ptr<Warrior>& warrior, States::Context& context);
    void update(const sf::Time& dTime);
    void draw(const States::Context& context);

    bool isFinished() const;
    bool isDied() const;

private:
    void lifeAnimation(const sf::Time& dTime);
    void deathAnimation(const sf::Time& dTime);

    std::shared_ptr<Warrior> warrior_;
    sf::Sprite sprite_;
    std::pair<int, int> warriorSpriteRect_;//<width, height>
    sf::Sprite deadSprite_;

    const char kFrames_ = 4;
    sf::Int32 deathDuration;
    float currentFrame_;
    bool died_;
    bool finished_;
};

#endif //SERVER_GRAPHICSWARRIOR_H
