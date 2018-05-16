#pragma once

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Widget.h"
namespace gui {
    class Textbox : public Widget {
    public:
        using Callback = std::function<void(int ind)>;

        explicit Textbox(sf::Font &font);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void update(sf::Time dt) override ;
        void handleEvent(const sf::Event& event) override ;

        void setDimensons(float newX, float newY, float newWidth, float newHeight);
        void setString(const std::string &newString);
        void setInd(int i);
        void setCallback(Callback callback);

        const std::string & getString();

    private:
        bool is_focused;

        float x;
        float y;
        float width;
        float height;
        std::string string;
        sf::Font &font;
        sf::RectangleShape background;
        sf::Text text;

        int ind;
        Callback callback;

        bool enterText(sf::Uint32 unicode);
    };
}