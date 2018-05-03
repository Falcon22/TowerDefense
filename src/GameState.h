#ifndef TOWERDEFENSE_GAMESTATE_H
#define TOWERDEFENSE_GAMESTATE_H

#include <SFML/System/Time.hpp>
#include <utility>
#include "ResourceManager/ResourcesHolder.h"
#include "ResourceManager/ResourcesIdentifier.h"

#include "State.h"
#include "Graphics/Gui.h"
#include "Map.h"
#include "Units/Warrior/Warrior.h"
#include "Units/UnitsGraphics/GraphicsUnit.h"
#include "Castle/Castle.h"
#include <list>

class Tower;
class Bullet;


class GameState : public State {
public:
    explicit GameState(StateManager& stack, States::Context context);
    ~GameState();

    bool handleEvent(const sf::Event &event) override;
    bool update(sf::Time dt) override;
    void draw() override;

    void manageEvents();
    void initTower();
    void initWarrior(sf::RenderWindow &window, const TextureHolder& textureHolder);

private:
    std::vector<sf::Vector2f> towers1;
    std::vector<sf::Vector2f> towers2;

    struct Event {
        Event(int id_, char type_, std::string value_, const sf::Time time_) :
                id(id_),
                type(type_),
                value(std::move(value_)),
                time(time_) {}
        int id;
        char type;
        std::string value;
        sf::Time time;
    };
    std::vector<Event> events;
    sf::Time clock;
    Castle* player1;
    Castle* player2;
    float waveTimer;
    const float kWaveTimer = 10;//second

    Player::GameData gameData;
    gui::Gui containter;
    Map map;
    std::vector<sf::IntRect> roadRect;

    std::list<Warrior*> warriors;
    std::list<GraphicsUnit> graphicsUnits;
    std::vector<Tower*> towers;
    std::list<Bullet*> bullets;

    sf::Sprite towerSprite;
    sf::Sprite towerSprite2;
    sf::Sprite warriorSprite1;
    sf::Sprite warriorSprite2;
    sf::Sprite bulletSprite;
    std::vector<sf::Vector2f> towerArea;
};


#endif //TOWERDEFENSE_GAMESTATE_H
