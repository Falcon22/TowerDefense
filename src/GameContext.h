#ifndef TOWERDEFENSE_GAMECONTEXT_H
#define TOWERDEFENSE_GAMECONTEXT_H

#include "ResourceManager/ResourcesIdentifier.h"
#include "ResourceManager/ResourcesHolder.h"

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
        explicit Context(sf::RenderWindow &window
                , sf::Font &font
                , TextureHolder &textureHolder
                , FontHolder &fontHolder
                , sf::Sprite &cursor)

                : window(&window)
                , font(&font)
                , textureHolder(&textureHolder)
                , fontHolder(&fontHolder)
                , cursor(&cursor)

        {};

        sf::RenderWindow *window;
        sf::Font *font;
        TextureHolder *textureHolder;
        FontHolder *fontHolder;
        SoundManager *soundManager;
        sf::Sprite *cursor;
    };
}

#endif //TOWERDEFENSE_GAMECONTEXT_H
