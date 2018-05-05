#include "TextBox.h"

#include <utility>

using namespace gui;

Textbox::Textbox(sf::Font &font): font(font), is_focused(false) {
    text = sf::Text("", font);
    background.setFillColor(sf::Color::White);
    text.setColor(sf::Color::Black);
}

void Textbox::update(sf::Time dt) { }

void Textbox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background, states);
    target.draw(text, states);
}

void Textbox::setDimensons(float newX, float newY, float newWidth, float newHeight) {
    x = newX;
    y = newY;
    width = newWidth;
    height = newHeight;
    text.setPosition(x, y-height/5);
    text.setCharacterSize(height);
    background.setPosition(x, y);
    background.setSize(sf::Vector2f(width, height));
}

void Textbox::setString(const std::string &newString) {
    string = newString;
    text.setString(string);
}

const std::string & Textbox::getString() {
    return string;
}

void Textbox::handleEvent(const sf::Event &event) {
    sf::FloatRect rect;
    rect.left   = x;
    rect.top    = y;
    rect.width  = width;
    rect.height = height;

    if (event.type == sf::Event::MouseButtonPressed)
        is_focused = rect.contains(event.mouseButton.x, event.mouseButton.y);

    if (is_focused && !string.empty() && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
        is_focused = false;
        // todo прочекать строку, чтобы не было пробелов и прочих гадостей
        callback(ind);
        string.clear();
    }

    if (is_focused && event.type == sf::Event::TextEntered) {
        enterText(event.text.unicode);
    }


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

void Textbox::setCallback(Textbox::Callback callback) {
    this->callback = std::move(callback);
}

void Textbox::setInd(const int i) {
    ind = i;
}
