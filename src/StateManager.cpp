#include "StateManager.h"

#include <assert.h>

StateManager::StateManager(States::Context context)
        : context(context)
{}

void StateManager::pushState(States::ID state) {
    actionQueue.push_back(std::make_pair(Action::Push, state));
}

void StateManager::popState() {
    actionQueue.push_back(std::make_pair(Action::Pop, States::ID::None));
}

void StateManager::clearStates() {
    actionQueue.push_back(std::make_pair(Action::Clear, States::ID::None));
}

void StateManager::processEvents(const sf::Event &event) {
    for (auto it = stateStack.rbegin(); it != stateStack.rend(); ++it) {
        if (!(*it)->handleEvent(event)) {
            break;
        }
    }
    applyChanges();
}

void StateManager::update(sf::Time dt) {
    for (auto it = stateStack.rbegin(); it != stateStack.rend(); ++it) {
        if (!(*it)->update(dt)) {
            break;
        }
    }
    applyChanges();
}

void StateManager::draw() {
    for (State::Ptr &state : stateStack) {
        state->draw();
    }
}

bool StateManager::isEmpty() const {
    return stateStack.empty();
}

State::Ptr StateManager::createState(States::ID state) {
    auto found = factories.find(state);
    assert(found != factories.end());

    return found->second();
}

void StateManager::applyChanges() {
    for (const auto &change : actionQueue) {
        switch (change.first) {
            case Action::Push:
                stateStack.push_back(createState(change.second));
                break;
            case Action::Pop:
                stateStack.pop_back();
                break;
            case Action::Clear:
                stateStack.clear();
                break;
            default:
                break;
        }
    }
    actionQueue.clear();
}