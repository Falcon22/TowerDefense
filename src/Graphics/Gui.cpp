#include "Gui.h"

using namespace gui;

Gui::Gui() {}

void Gui::addWidget(Widget::Ptr widget) {
    widgets.push_back(widget);
}

void Gui::removeWidgets() {
    widgets.clear();
}

void Gui::handleWidgetsEvent(const sf::Event &event) {
    for (const auto& widget : widgets) {
        widget->handleEvent(event);
    }
}

void Gui::updateWidgets(sf::Time dt) {
    for (const auto& widget : widgets) {
        widget->update(dt);
    }
}

void Gui::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const auto& widget : widgets) {
        target.draw(*widget, states);
    }
}