#include "TextBox.h"

using namespace gui;

Textbox::Textbox(sf::Font &font): font(font) {
    text = sf::Text("", font);
    background.setFillColor(sf::Color::White);
    text.setColor(sf::Color::Black);
}

void Textbox::update(sf::Time dt) {}

void Textbox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background, states);
    target.draw(text, states);
}

void Textbox::setDimensons(double newX, double newY, double newWidth, double newHeight) {
    x = newX;
    y = newY;
    width = newWidth;
    height = newHeight;
    text.setPosition(x, y-height/5);
    text.setCharacterSize(height);
    background.setPosition(x, y);
    background.setSize(sf::Vector2f(width, height));
}

void Textbox::setString(std::string newString) {
    string = newString;
    text.setString(string);
}

std::string Textbox:: getString() {
    return string;
}

void Textbox::handleEvent(const sf::Event &event) {
        if(event.type == sf::Event::TextEntered) {
            if (isFocused) {
                enterText(event.text.unicode);
            }
            setFocus(!isFocused);
        }
}

void Textbox::setFocus(bool focus) {
    isFocused = focus;
}

bool Textbox::enterText(sf::Uint32 unicode) {
    if(unicode == 8)
        string = string.substr(0, string.length()-1); // delete key
    else if(unicode == 10)
        return true; // return key
    else
        if (string.size() <= 10) {
            string += (char) unicode;
        }
    text.setString(string);
    return false;
}
