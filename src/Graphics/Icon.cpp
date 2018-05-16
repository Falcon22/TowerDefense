#include "Icon.h"

using namespace gui;

Icon::Icon()
        : callback()
        , toggle(false)
        , selected(false)
{
}

void Icon::setCallback(Callback callback)
{
    this->callback = std::move(callback);
}

void Icon::setTexture(const sf::Texture &texture1, const sf::Texture &texture2)
{
    sprite1.setTexture(texture1);
    sprite2.setTexture(texture2);
    sprite = sprite1;
    changeTexture(Type::Normal);
}


void Icon::handleEvent(const sf::Event &event)
{
    sf::FloatRect rect;
    rect.left = getPosition().x;
    rect.top  = getPosition().y;
    rect.width  = sprite.getLocalBounds().width;
    rect.height = sprite.getLocalBounds().height;

    switch (event.type)
    {
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
            if (rect.contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    activate();
                }
            }
            break;
    }
}

void Icon::update(sf::Time dt)
{
}

void Icon::activate()
{
    if (callback)
        callback();

    if (toggle)
    {
        deactivate();
    } else
    {
        sprite = sprite2;
        toggle = true;
    }
}

void Icon::deactivate()
{
    sprite = sprite1;
    toggle = false;
}

void Icon::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
    target.draw(text, states);
}

void Icon::changeTexture(Type type)
{
    sf::IntRect textureRect(190 * type, 0, 50, 50);
    sprite.setTextureRect(textureRect);
}

