#ifndef TOWERDEFENSE_CONNECTGAMESTATE_H
#define TOWERDEFENSE_CONNECTGAMESTATE_H

#include "Graphics/Gui.h"
#include "State.h"

class ConnectGameState: public State {
public:
    explicit ConnectGameState(StateManager& stack, States::Context context);

    bool handleEvent(const sf::Event& event) override ;
    bool update(sf::Time dt) override;
    void draw() override;

    void initButtons();

private:
    gui::Gui container;
};


#endif //TOWERDEFENSE_CONNECTGAMESTATE_H
