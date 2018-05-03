#pragma once

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Widget.h"
namespace gui {
    class Textbox : public Widget {
    public:
        Textbox(sf::Font &font);

        void setDimensons(double newX, double newY, double newWidth, double newHeight);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void update(sf::Time dt) override ;
        void setString(std::string newString);

        std::string getString();

        void handleEvent(const sf::Event& event) override ;

        void setFocus(bool focus);

        void setReturnEvent(void (*newFunctionToCall)());

    private:
        bool isFocused;
        double x;
        double y;
        double width;
        double height;
        std::string string = "";
        sf::Font &font;
        sf::RectangleShape background;
        sf::Text text;

        bool enterText(sf::Uint32 unicode);
    };
}