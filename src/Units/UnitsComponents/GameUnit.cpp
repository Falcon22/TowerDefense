#include "GameUnit.h"

GameUnit::GameUnit(InputComponent *input, GraphicsComponent *graphics, LogicComponent *logic)
    : input_(input),
      graphics_(graphics),
      logic_(logic) {}

void GameUnit::Update() {
    input_->Update();
    logic_->Update();
    graphics_->Update();
}
