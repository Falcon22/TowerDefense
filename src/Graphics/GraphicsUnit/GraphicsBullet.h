#ifndef TOWERDEFENSE_GRAPHICSBULLET_H
#define TOWERDEFENSE_GRAPHICSBULLET_H


#include "../../GameContext.h"
#include "../../Units/Bullet/Bullet.h"

class GraphicsBullet {
public:
    GraphicsBullet(const Bullet* bullet, States::Context& context);
    void update(const sf::Time& dTime);
    void draw(States::Context& context);

    bool isFinished() const;

private:
    const Bullet* bullet_;
    sf::Sprite sprite_;
    sf::Sprite explosion_;
    sf::Int32 explosionTime_;
    bool finished_;
};


#endif //TOWERDEFENSE_GRAPHICSBULLET_H
