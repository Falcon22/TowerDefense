#ifndef TOWERDEFENSE_GAMECONTEXT_H
#define TOWERDEFENSE_GAMECONTEXT_H

#include "ResourceManager/ResourcesIdentifier.h"
#include "ResourceManager/ResourcesHolder.h"
#include "Multiplayer/MultiplayerFacade/AbstractMultiplayerFacade.h"

enum class Type {
    lvlZero,
    lvlOne,
    lvlTwo,
    lvlThree,
};

namespace sf {
    class RenderWindow;

    class Font;

    class Sprite;
}

class SoundManager;

namespace Player {
    struct GameData {
        int lives;
        int gold;
        int currentLevel;
        int score;
    };
}

namespace States {
    struct Context {
        explicit Context(
                sf::RenderWindow &window,
                sf::Font &font,
                TextureHolder &textureHolder,
                FontHolder &fontHolder,
                sf::Sprite &cursor,
                mp::AbstractMultiplayerFacade *p_mult
        )

                : window(&window),
                  font(&font),
                  textureHolder(&textureHolder),
                  fontHolder(&fontHolder),
                  cursor(&cursor),
                  p_id(new int(2)),
                  multiplayer(p_mult)

        {};

        sf::RenderWindow *window;
        sf::Font *font;
        TextureHolder *textureHolder;
        FontHolder *fontHolder;
        SoundManager *soundManager;
        sf::Sprite *cursor;

        std::shared_ptr<int> p_id;
        std::shared_ptr<mp::AbstractMultiplayerFacade> multiplayer;
    };
}

#endif //TOWERDEFENSE_GAMECONTEXT_H