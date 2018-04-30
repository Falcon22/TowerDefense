#include <cmath>
#include "GameState.h"
#include "Game.h"
#include "Units/Bullet/Bullet.h"
#include "Units/Warrior/WarriorLvlTwo.h"
#include "Units/Tower/TowerLvlOne.h"


GameState::GameState(StateManager &stack, States::Context context) :
        State(stack, context),
        gameData(),
        map(*context.window)
{
    map.analyze();

    warriors.push_back(new WarriorLvlTwo(sf::Vector2f(500, 700), map.getRoadRect()));
    warriors.push_back(new WarriorLvlTwo(sf::Vector2f(500, 1000), map.getRoadRect()));

    gUnits.push_back(new GraphicsUnit(*context.window, Type::lvlTwo, *context.textureHolder));
    gUnits.push_back(new GraphicsUnit(*context.window, Type::lvlTwo, *context.textureHolder));

    tower = new TowerLvlOne(sf::Vector2f(160, 500), warriors, bullets);

    towerSprite.setTexture((*context.textureHolder).get(Textures::towerOneTop));
    towerSprite.setOrigin(towerSprite.getTextureRect().width / 2, towerSprite.getTextureRect().height / 2);

    bulletSprite.setTexture((*context.textureHolder).get(Textures::bulletTwo));
    bulletSprite.setOrigin(bulletSprite.getTextureRect().width / 2, bulletSprite.getTextureRect().height / 2);

    Tower::upgrade(tower);
    if (tower->getType() == Type::lvlTwo)
        std::cout << "Correct" << std::endl;
}

bool GameState::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
//        (event.key.code == sf::Keyboard::Escape)
    }

    return false;
}

bool GameState::update(sf::Time dt) {
    for(auto bullet: bullets) {
        if (!bullet->isExploded())
            bullet->update(dt);
    }

    tower->update(dt);

    for (int i = 0; i < warriors.size(); ++i) {
        warriors[i]->update(dt);
        gUnits[i]->update(*warriors[i], dt);
    }

    //std::cout << "0: " << warriors[0]->getPosition().x << "|" << warriors[0]->getPosition().y << std::endl;
    //std::cout << "1: " << warriors[1]->getPosition().x << "|" << warriors[1]->getPosition().y << std::endl;
}

void GameState::draw() {
    map.draw();
    towerSprite.setRotation(tower->getAngle());
    towerSprite.setPosition(tower->getPosition());
    getContext().window->draw(towerSprite);
    for(auto bullet: bullets) {
        if (!bullet->isExploded()) {
            //std::cout << bullet->getAngle() << std::endl;
            bulletSprite.setRotation(static_cast<float>(-bullet->getAngle() * 180 / M_PI + 180));
            bulletSprite.setPosition(bullet->getPosition());
            getContext().window->draw(bulletSprite);
        }
    }

    for (auto &&item : gUnits) {
        item->draw();
    }

}
