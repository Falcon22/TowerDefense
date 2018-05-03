#include "Label.h"

using namespace gui;

Label::Label(sf::Texture texture, std::string& textIn, sf::Font &font)  {
    sprite.setTexture(texture);
    text.setString(textIn);
    text.setFont(font);
}

void Label::handleEvent(const sf::Event &event) {
    sf::FloatRect rect = sprite.getGlobalBounds();
}

void Label::update(sf::Time dt) {}

void Label::setTexture(const sf::Texture &texture) {
    sprite.setTexture(texture);
}

void Label::setText(const std::string &text) {
    this->text.setString(text);
}

void Label::setFont(const sf::Font &font) {
    text.setFont(font);
}

void Label::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    if (sprite.getTexture()) {
        target.draw(sprite, states);
    } else {
        target.draw(text, states);
    }
}

void Label::centerText() {
    sf::FloatRect rect = text.getGlobalBounds();
    text.setOrigin(rect.left, rect.top);
    text.setPosition({sprite.getLocalBounds().width / 2 - rect.width,
                     sprite.getLocalBounds().height / 2 - rect.height / 2});
}