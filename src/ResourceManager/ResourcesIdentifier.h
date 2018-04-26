#ifndef TOWERDEFENSE_RESOURCESIDENTIFIER_H
#define TOWERDEFENSE_RESOURCESIDENTIFIER_H

namespace sf {
    class Texture;
    class Font;
}

namespace Textures {
    enum id {
        cursor = 0,
        panel,
        button,
        map,
        target,
        towerOneBase,
        towerOneTop,
        towerTwoBase,
        towerTwoTop,
        warriorLvlOne,
        warriorLvlTwo,
        bulletOne,
        bulletTwo,
        explosion,
        gold,
        star,
        lives,
        pauseOn,
        pauseOff,
        forwardOn,
        forwardOff,
        fastForwardOn,
        fastForwardOff,
        fight,
        play,
        audioOff,
        audioOn,
        musicOff,
        musicOn,
        exit,
    };
}

namespace Fonts {
    enum id {
        font1 = 0,
        font2,
        font3,
        font4,
    };
}

template<typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::id> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::id> FontHolder;

#endif //TOWERDEFENSE_RESOURCESIDENTIFIER_H
