#ifndef TOWERDEFENSE_MENUSTATE_H
#define TOWERDEFENSE_MENUSTATE_H

#include "Graphics/Gui.h"
#include "State.h"
#include "Tile.h"

class MenuState : public State {
public:
    explicit MenuState(StateManager& stack, States::Context context);

    bool handleEvent(const sf::Event& event) override ;
    bool update(sf::Time dt) override;
    void draw() override;

    void initButtons();
private:
    sf::Texture texture;
    Tile mapSprite;

    gui::Gui container;
    sf::Text name;
    sf::Sprite logo;
};


#endif //TOWERDEFENSE_MENUSTATE_H
