#ifndef TOWERDEFENSE_BUTTON_H
#define TOWERDEFENSE_BUTTON_H

#include <functional>

#include "Widget.h"

namespace gui {
    class Button : public Widget {
    public:
        using Callback = std::function<void(int ind)>;

        enum Type {
            Normal = 0,
            Selected,
            Pressed
        };

        explicit Button();

        void setSprite(sf::Sprite newSprite);
        void setCallback(Callback callback);
        void setTexture(const sf::Texture& texture);
        void setTextureRect(sf::IntRect rect);
        void setText(const std::string& text);
        void setFont(const sf::Font& font);
        void setInd(const int i);
        void handleEvent(const sf::Event& event) override ;
        void update(sf::Time dt) override ;
        void setCostCallback(Callback callback);
        void setCost(bool cost);
        void setPrintCost(bool print);
        void setCostText(sf::Text cost);

    private:
        void select();
        void deselect();
        void activate();
        void deactivate();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void changeTexture(Type type);
        void centerText();

        Callback callback;
        Callback cost;
        sf::Sprite sprite;
        sf::Text text;
        sf::Text costText;

        bool printCost;
        bool isCost;
        bool selected;
        bool toggle;
        int ind;
    };
}


#endif //TOWERDEFENSE_BUTTON_H