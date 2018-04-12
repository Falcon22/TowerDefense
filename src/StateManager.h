#ifndef TOWERDEFENSE_STATEMANAGER_H
#define TOWERDEFENSE_STATEMANAGER_H

#include <functional>

#include "State.h"

class StateManager : private sf::NonCopyable {
public:
    explicit StateManager(States::Context context);

    template <typename T>
    void registerState(States::ID stateID);

    void pushState(States::ID state);
    void popState();
    void clearStates();

    void processEvents(const sf::Event &event);
    void update(sf::Time dt);
    void draw();

    bool isEmpty() const;

private:
    State::Ptr createState(States::ID state);
    void       applyChanges();

private:
    enum class Action {
        Push,
        Pop,
        Clear
    };

    std::vector<std::pair<Action, States::ID>> actionQueue;
    std::vector<State::Ptr> stateStack;

    State::Ptr      state;
    States::Context context;

    std::map<States::ID, std::function<State::Ptr()>> factories;
};

template <typename T>
void StateManager::registerState(States::ID stateID) {
    factories[stateID] = [this]() {
        return State::Ptr(std::make_unique<T>(*this, context));
    };
}


#endif //TOWERDEFENSE_STATEMANAGER_H
