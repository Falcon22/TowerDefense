#include "HUD.h"
#include "../StateManager.h"
#include "../ResourceManager/ResourcesHolder.h"
#include "../ResourceManager/ResourcesIdentifier.h"

using namespace gui;

HUD::HUD(States::Context context, std::shared_ptr<Castle> player1, std::shared_ptr<Castle> player2)
        : context(context),
          gold(context.textureHolder->get(Textures::gold), context.fontHolder->get(Fonts::font1)),
          livePlayer(context.textureHolder->get(Textures::lives), context.fontHolder->get(Fonts::font1)),
          liveFoe(context.textureHolder->get(Textures::lives), context.fontHolder->get(Fonts::font1)) {

    if (*context.p_id == 1) {
        player = player1;
        foe = player2;
    } else {
        player = player2;
        foe = player1;
    }

    auto exit = std::make_shared<gui::Icon>();

    exit->setTexture(context.textureHolder->get(Textures::exit), context.textureHolder->get(Textures::exit));
    exit->setPosition({1120.f, 5.f});
    exit->setCallback([this]
                      {
                          action = Action::Exit;

                      });

    container.addWidget(exit);
}

void HUD::init()
{
    std::cout << "HUD::init()" << std::endl;

    sf::IntRect rect{ TILE_SIZE * (15), TILE_SIZE * (0), TILE_SIZE, TILE_SIZE };
    for (int i = 0; i < 10; i++) {
        sf::RectangleShape tmp;
        tmp.setPosition(350.f + i * 50.f, 710.f);
        tmp.setSize(sf::Vector2f(50, 50));
        tmp.setTexture(&context.textureHolder->get(Textures::map));
        tmp.setTextureRect(rect);
        buffer.push_back(tmp);
    }

    gold.setTexture(context.textureHolder->get(Textures::gold));
    gold.setPosition(535.f, 0.f);

    if (*context.p_id == 1) {
        livePlayer.setPosition(0.f, 5.f);
        liveFoe.setPosition(970.f, 5.f);
    } else {
        liveFoe.setPosition(0.f, 5.f);
        livePlayer.setPosition(970.f, 5.f);
    }

    livePlayer.setTexture(context.textureHolder->get(Textures::lives));
    livePlayer.setScale({1.f / 3.f, 1.f / 3.f});
    liveFoe.setTexture(context.textureHolder->get(Textures::lives));
    liveFoe.setScale({1.f / 3.f, 1.f / 3.f});

    totalGold.setFont(context.fontHolder->get(Fonts::font1));
    totalGold.setString(std::to_string(player->getGold()));
    totalGold.setPosition(585.f, 10.f);
//
    totalPlayerLives.setFont(context.fontHolder->get(Fonts::font1));
    totalFoeLives.setFont(context.fontHolder->get(Fonts::font1));
    totalPlayerLives.setString(std::to_string(player->getHealth()));
    totalFoeLives.setString(std::to_string(foe->getHealth()));

    if (*context.p_id == 1) {
        totalFoeLives.setPosition(50.f, 10.f);
        totalPlayerLives.setPosition(1020.f, 10.f);
    } else {
        totalPlayerLives.setPosition(50.f, 10.f);
        totalFoeLives.setPosition(1020.f, 10.f);
    }
}

void HUD::handleEvent(const sf::Event &event)
{
    container.handleWidgetsEvent(event);
}

void HUD::update(sf::Time dt)
{
    totalGold.setString(std::to_string(player->getGold()));

    totalPlayerLives.setString(std::to_string(player->getHealth()));
    totalFoeLives.setString(std::to_string(foe->getHealth()));

}




void gui::HUD::setAction(Action action)
{
    this->action = action;
}

const HUD::Action HUD::getAction() const
{
    return action;
}

void HUD::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(gold);
    target.draw(livePlayer);
    target.draw(liveFoe);
    target.draw(totalGold);
    target.draw(totalPlayerLives);
    target.draw(totalFoeLives);
    target.draw(container);
    for (auto i : buffer) {
        target.draw(i);
    }

    auto p = 0.f;

    size_t i = 0;
    for (auto warrior : player->getWarriorsBuffer()) {
        if (i++ < player->getWarriorsToWave()) {
            continue;
        }
        sf::Sprite tmp;
        sf::IntRect rect{ 0, 0, TILE_SIZE, TILE_SIZE };
        tmp.setTextureRect(rect);
        if (warrior->getType() == Type::lvlOne) {
            tmp.setTexture(context.textureHolder->get(Textures::warriorIconOne));
        } else {
            tmp.setTexture(context.textureHolder->get(Textures::warriorIconTwo));
        }
        tmp.setPosition(355.f + p, 715.f);

        tmp.setScale(1.f / 2.f, 1.f / 2.f);
        p += 50.f;
        target.draw(tmp);
    }
}