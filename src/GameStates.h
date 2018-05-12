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
        GameOver,
        Win
    };
}

#endif //TOWERDEFENSE_GAMESTATES_H
