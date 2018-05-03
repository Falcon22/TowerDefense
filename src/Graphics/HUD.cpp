//#pragma once
//
//#include "Widget.h"
//#include "Button.h"
//#include "Icon.h"
//#include "Gui.h"
//#include "../GameContext.h"
////#include "Tower.h"
//#include "Label.h"
//
//namespace gui
//{
//    class HUD : public Widget
//    {
//    public:
//        enum class Action
//        {
//            None,
//            Audio,
//            Music,
//            Pause,
//            Forward,
//            Upgrade,
//            Sell,
//            Exit
//        };
//
//        HUD(States::Context context, Player:: &gameData);
//
//        void init();
//
//        void handleEvent(const sf::Event &event) override;
//        void update(sf::Time dt) override;
//
//        void setAction(Action action);
//        const Action getAction() const;
//
//    private:
//        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
//
//        Action action;
//
//        Gui container;
//        States::Context context;
//        Player::
//
//        sf::Texture texture;
//        sf::Font font;
//
//
//        Label gold;
//        Label live;
//        Label fight;
//        Label star;
//
//        sf::Text totalGold;
//        sf::Text totalLives;
//        sf::Text currentLevel;
//        sf::Text score;
//
//        sf::RectangleShape background;
//    };
//}
//
