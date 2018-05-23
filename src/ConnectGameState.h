#ifndef TOWERDEFENSE_CONNECTGAMESTATE_H
#define TOWERDEFENSE_CONNECTGAMESTATE_H

#include "Graphics/Gui.h"
#include "State.h"
#include "Tile.h"

class ConnectGameState: public State {
public:
    explicit ConnectGameState(StateManager& stack, States::Context context);

    bool handleEvent(const sf::Event& event) override ;
    bool update(sf::Time dt) override;
    void draw() override;

    void initButtons();

private:
    sf::Texture texture;
    Tile mapSprite;

    std::string gameID;
    gui::Gui container;
    sf::Text textNew;
    sf::Text textJoin;
};


#endif //TOWERDEFENSE_CONNECTGAMESTATE_H