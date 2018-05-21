#ifndef TOWERDEFENSE_GAME_H
#define TOWERDEFENSE_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "StateManager.h"
#include "GameContext.h"
#include "ResourceManager/ResourcesHolder.h"
#include "ResourceManager/ResourcesIdentifier.h"
#include "Multiplayer/Entities/Player.h"

//std::vector<mp::Events>& incoming_events;
//std::vector<mp::Events>& outcoming_events;

class Game {
public:
    Game();
    Game(mp::player &first, mp::player &second);

    void run();
    void server_run(bool use_validation);

private:
    void input();
    void update(sf::Time frameTime);
    void draw();

    void registerStates();
    void loadAllResources();

    TextureHolder textureHolder;
    FontHolder fontHolder;
    sf::Font font;
    sf::Sprite cursor;
    sf::RenderWindow window;
    States::Context context;
    StateManager stateManager;
};


#endif //TOWERDEFENSE_GAME_H