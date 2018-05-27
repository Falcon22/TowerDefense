#pragma once

#include <functional>

#include "Widget.h"

namespace gui
{
    class Icon : public Widget
    {
    public:
        using Callback = std::function<void()>;

        enum Type
        {
            Normal = 0,
            Selected,
            Pressed
        };

        explicit Icon();

        void setCallback(Callback callback);
        void setTexture(const sf::Texture &texture1, const sf::Texture &texture2);
        void handleEvent(const sf::Event &event) override;
        void update(sf::Time dt) override;

    private:
        void activate();
        void deactivate();

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        void changeTexture(Type type);


        Callback   callback;
        sf::Sprite sprite;
        sf::Sprite sprite1;
        sf::Sprite sprite2;
        sf::Text   text;

        bool selected;
        bool toggle;
    };
}