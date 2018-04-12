#ifndef TOWERDEFENSE_WIDGET_H
#define TOWERDEFENSE_WIDGET_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "../GameContext.h"

namespace gui {
    class Widget : public sf::Drawable, public sf::Transformable, private sf::NonCopyable {
    public:
        using Ptr = std::shared_ptr<Widget>;

        Widget() = default;
        virtual ~Widget() = default;

        virtual void handleEvent(const sf::Event &event) = 0;
        virtual void update(sf::Time dt) = 0;
    };
}
#endif //TOWERDEFENSE_WIDGET_H
