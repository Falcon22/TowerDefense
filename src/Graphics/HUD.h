#pragma once

#include "Widget.h"
#include "Button.h"
#include "Icon.h"
#include "Gui.h"
#include "../GameContext.h"
//#include "Tower.h"
#include "../Castle/Castle.h"
#include "Label.h"

namespace gui
{
    class HUD : public Widget
    {
    public:
        enum class Action
        {
            None,
            Audio,
            Music,
            Pause,
            Forward,
            Upgrade,
            Sell,
            Exit
        };

        HUD(States::Context context, std::shared_ptr<Castle> player1, std::shared_ptr<Castle> player2);

        void init();

        void handleEvent(const sf::Event &event) override;
        void update(sf::Time dt) override;

        void setAction(Action action);
        const Action getAction() const;

    private:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        Action action;

        Gui container;
        States::Context context;
        //Player::GameData *gameData;
        std::shared_ptr<Castle> player;
        std::shared_ptr<Castle> foe;
        sf::Texture texture;
        sf::Font font;


        Label gold;
        Label livePlayer;
        Label liveFoe;
//        Label star;

        sf::Text totalGold;
        sf::Text totalPlayerLives;
        sf::Text totalFoeLives;
        sf::Text currentLevel;
        sf::Text score;
        std::vector<sf::RectangleShape> buffer;
        sf::RectangleShape background;
    };
}

