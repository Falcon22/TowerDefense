#ifndef TOWERDEFENSE_MENUSTATE_H
#define TOWERDEFENSE_MENUSTATE_H

#include "Graphics/Gui.h"
#include "State.h"


class MenuState : public State {
public:
    explicit MenuState(StateManager& stack, States::Context context);

    bool handleEvent(const sf::Event& event) override ;
    bool update(sf::Time dt) override;
    void draw() override;

private:
    gui::Gui container;
};


#endif //TOWERDEFENSE_MENUSTATE_H
