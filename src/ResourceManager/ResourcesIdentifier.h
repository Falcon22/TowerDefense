#ifndef TOWERDEFENSE_RESOURCESIDENTIFIER_H
#define TOWERDEFENSE_RESOURCESIDENTIFIER_H

namespace sf {
    class Texture;
    class Font;
}

namespace Textures {
    enum id {
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
