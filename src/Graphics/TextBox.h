#pragma once

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Widget.h"
namespace gui {
    class Textbox : public Widget {
    public:
        Textbox(sf::RenderWindow &window, sf::Font &font);

        void setDimensons(double newX, double newY, double newWidth, double newHeight);

        void draw();

        void setString(std::string newString);

        std::string getString();

        bool pollEvent(sf::Event event);

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
        sf::RenderWindow &window;
        sf::RectangleShape background;
        sf::Text text;

        bool enterText(sf::Uint32 unicode);
    };
}