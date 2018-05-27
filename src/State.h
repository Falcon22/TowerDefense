#ifndef TOWERDEFENSE_STATE_H
#define TOWERDEFENSE_STATE_H

#include <SFML/Graphics.hpp>

#include <memory>
#include "GameContext.h"
#include "GameStates.h"

class StateManager;

class State : private sf::NonCopyable {
public:
    using Ptr = std::unique_ptr<State>; // typedef std::unique_ptr<State> Ptr;

    explicit State(StateManager& stack, States::Context context);
    virtual ~State() = default;

    virtual bool handleEvent(const sf::Event& event) = 0;
    virtual bool update(sf::Time dt) = 0;
    virtual void draw() = 0;

protected:
    void pushState(States::ID state);
    void popState();
    void clearStates();

    States::Context& getContext() ;

private:
    StateManager	 &stack;
    States::Context  context;
};

#endif //TOWERDEFENSE_STATE_H
