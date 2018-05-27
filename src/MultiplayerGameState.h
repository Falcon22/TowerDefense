#include <SFML/System/Time.hpp>

#include "ResourceManager/ResourcesHolder.h"
#include "ResourceManager/ResourcesIdentifier.h"

#include "State.h"
#include "Graphics/Gui.h"
#include "Map.h"
#include "Units/Warrior/Warrior.h"
#include "Units/UnitsGraphics/GraphicsUnit.h"

class Tower;
class Bullet;

class GameState : public State {
public:
    explicit GameState(StateManager& stack, States::Context context);
    ~GameState() = default;

    bool handleEvent(const sf::Event &event) override;
    bool update(sf::Time dt) override;
    void draw() override;

private:
    Player::GameData player1;
    Player::GameData player2;
    gui::Gui containter;
    Map map;
    std::vector<sf::IntRect> roadRect;
    std::vector<Warrior*> warriors;
    GraphicsUnit graphicsUnit;
    Tower* tower;
    std::vector<Bullet*> bullets;
    sf::Sprite towerSprite;
    sf::Sprite bulletSprite;
};