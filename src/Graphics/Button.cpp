#include "Button.h"

using namespace gui;

Button::Button() : callback(),
                   toggle(false),
                   selected(false)
{}

void Button::setCallback(Callback callback) {
    this->callback = std::move(callback);
}

void Button::setTexture(const sf::Texture& texture) {
    sprite.setTexture(texture);
    changeTexture(Type::Normal);
    centerText();
}

void Button::setTextureRect(sf::IntRect rect) {
    sprite.setTextureRect(rect);
}

void Button::setText(const std::string& text) {
    this->text.setString(text);
    centerText();
}

void Button::setFont(const sf::Font& font) {
    text.setFont(font);
    centerText();
}

void Button::setInd(const int i) {
    ind = i;
}

void Button::handleEvent(const sf::Event& event) {
    sf::FloatRect rect;
    rect.left = getPosition().x;
    rect.top = getPosition().y;
    rect.width = sprite.getLocalBounds().width * sprite.getScale().x;
    rect.height = sprite.getLocalBounds().height * sprite.getScale().y;

    switch (event.type) {
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
            if (rect.contains(static_cast<float>(event.mouseButton.x),
                              static_cast<float>(event.mouseButton.y))) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    activate();
                } else {
                    deactivate();
                }
            }
            break;
//        case sf::Event::MouseMoved:
//            if (rect.contains(static_cast<float>(event.mouseMove.x),
//                              static_cast<float>(event.mouseMove.y))) {
//                if (!selected) {
//                            select();
//                    }
//            } else {
//                if (selected) {
//                    deselect();
//                }
//            }
//            break;
    }
}

void Button::update(sf::Time dt) {}

void Button::select() {
    changeTexture(Type::Normal);
    selected = true;
}

void Button::deselect() {
    changeTexture(Type::Normal);
    selected = false;
}

void Button::activate() {
    if (callback) {
        callback(ind);
    }

    deactivate();
}

void Button::deactivate() {
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(sprite, states);
    target.draw(text, states);
}

void Button::changeTexture(Type type) {
    sf::IntRect textureRect(190 * type, 0, 190, 49);
    sprite.setTextureRect(textureRect);
}

void Button::centerText() {
    sf::FloatRect rect = text.getGlobalBounds();
    text.setOrigin(rect.left, rect.top);
    text.setPosition({sprite.getLocalBounds().width + 160,
                      sprite.getLocalBounds().height + rect.height / 2});

}