#ifndef TOWERDEFENSE_GAMECONTEXT_H
#define TOWERDEFENSE_GAMECONTEXT_H

#include "ResourceManager/ResourcesIdentifier.h"
#include "ResourceManager/ResourcesHolder.h"
#include "Server/Entities.h"

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
                , sf::Sprite &cursor
                , int id
                , std::vector<mp::Event>& ie
                , std::vector<mp::Event>& oe)

                : window(&window)
                , font(&font)
                , textureHolder(&textureHolder)
                , fontHolder(&fontHolder)
                , cursor(&cursor)
                , id(id)
        , incoming_events(ie)
                , outcoming_events(oe)


        {};

        sf::RenderWindow *window;
        sf::Font *font;
        TextureHolder *textureHolder;
        FontHolder *fontHolder;
        SoundManager *soundManager;
        sf::Sprite *cursor;

        std::vector<mp::Event> &incoming_events;
        std::vector<mp::Event> &outcoming_events;

        int id;
    };
}

#endif //TOWERDEFENSE_GAMECONTEXT_H
