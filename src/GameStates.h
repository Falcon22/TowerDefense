#ifndef TOWERDEFENSE_GAMESTATES_H
#define TOWERDEFENSE_GAMESTATES_H

namespace States {
    enum class ID {
        None = 0,
        Game,
        MultiplayerGame,
        ConnectGame,
        Menu,
        Pause,
        GameOverState,
        WinState
    };
}

#endif //TOWERDEFENSE_GAMESTATES_H
