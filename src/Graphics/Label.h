#ifndef TOWERDEFENSE_LABEL_H
#define TOWERDEFENSE_LABEL_H

#include "Widget.h"

namespace gui {
    class Label : public Widget {
    public:
        Label(sf::Texture texture, sf::Font &font);
        void handleEvent(const sf::Event& event) override;
        void update(sf::Time dt) override ;

        void setTexture(const sf::Texture& texture);
        void setText(const std::string& text);
        void setFont(const sf::Font &font);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void centerText();

        sf::Sprite sprite;
        sf::Text text;
    };
}

#endif //TOWERDEFENSE_LABEL_H