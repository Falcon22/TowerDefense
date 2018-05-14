#include "State.h"
#include "StateManager.h"

State::State(StateManager& stack, States::Context context)
    : stack(stack),
    context(context)
{}

void State::pushState(States::ID state) {
    stack.pushState(state);
}

void State::popState() {
    stack.popState();
}

void State::clearStates() {
    stack.clearStates();
}

States::Context& State::getContext() {
    return context;
}