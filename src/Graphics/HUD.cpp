#include "HUD.h"
#include "../StateManager.h"
#include "../ResourceManager/ResourcesHolder.h"
#include "../ResourceManager/ResourcesIdentifier.h"

using namespace gui;

HUD::HUD(States::Context context, std::shared_ptr<Castle>& player1, std::shared_ptr<Castle>& player2)
        : context(context),
          gold(context.textureHolder->get(Textures::gold), context.fontHolder->get(Fonts::font1)),
          livePlayer(context.textureHolder->get(Textures::lives), context.fontHolder->get(Fonts::font1)),
          liveFoe(context.textureHolder->get(Textures::lives), context.fontHolder->get(Fonts::font1)),
          player(player1),
          foe(player2) {
//    if (*context.p_id == 1) {
//        player = player1;
//        foe = player2;
//    } else {
//        player = player2;
//        foe = player1;
//    }

//
//    auto audio = std::make_shared<gui::Icon>();
//    audio->setTexture(context.textureHolder->get(Textures::audioOn), context.textureHolder->get(Textures::audioOff));
//    audio->setPosition({770.f, 10.f});
//
//
//    auto music = std::make_shared<gui::Icon>();
//
//    music->setTexture(context.textureHolder->get(Textures::musicOn), context.textureHolder->get(Textures::musicOff));
//    music->setPosition({820.f, 10.f});
//
//    auto pause = std::make_shared<gui::Icon>();
//
//    pause->setTexture(context.textureHolder->get(Textures::pauseOff), context.textureHolder->get(Textures::pauseOff));
//    pause->setPosition({670.f, 10.f});
//    pause->setCallback([this]
//                       {
//                           action = Action::Pause;
//
//
//                       });
//
//    auto forward = std::make_shared<gui::Icon>();
//
//    forward->setTexture(context.textureHolder->get(Textures::forwardOff), context.textureHolder->get(Textures::forwardOn));
//    forward->setPosition({600.f, 10.f});
//    forward->setCallback([this]
//                         {
//                             action = Action::Forward;
//                         });


    auto exit = std::make_shared<gui::Icon>();

    exit->setTexture(context.textureHolder->get(Textures::exit), context.textureHolder->get(Textures::exit));
    exit->setPosition({1120.f, 5.f});
    exit->setCallback([this]
                      {
                          action = Action::Exit;

                      });

//    auto upgrade = std::make_shared<gui::Button>(*context.soundManager);
//    upgrade->setTexture(context.textureHolder->get(Textures::button));
//    upgrade->setPosition({600.f, 485.f});
//    upgrade->setFont(*context.font);
//    upgrade->setText("Upgrade");
//    upgrade->setCallback([this]()
//                         {
//                             action = Action::Upgrade;
//                         });

//    auto sell = std::make_shared<gui::Button>(*context.soundManager);
//    sell->setTexture(context.textureHolder->get(Textures::button));
//    sell->setPosition({ 600.f, 550.f});
//    sell->setFont(*context.font);
//    sell->setText("Sell");
////    sell->setCallback([this]()
//                      {
//
//                          action = Action::Sell;
//                      });

//    container.addWidget(audio);
//    container.addWidget(music);
//    container.addWidget(pause);
    container.addWidget(exit);
//
//    //container.addWidget(upgrade);
//    //container.addWidget(sell);
//
//    action = Action::None;
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

//
//    star.setTexture(context.textureHolder->get(Textures::star));
//    star.setPosition(250.f, 5.f);
//
//    live.setTexture(context.textureHolder->get(Textures::lives));
//    live.setScale({1.f / 3.f, 1.f / 3.f});
//    live.setPosition(150.f, 5.f);
//
//
//    fight.setTexture(context.textureHolder->get(Textures::fight));
//    fight.setPosition(430.f, 5.f);
//
//    singleTurret.setTexture(context.textureHolder->get(Textures::towerOneBase));
//    singleTurret.setPosition(268.f, 500.f);
//
//    singleTurret.setTexture(context.textureHolder->get(Textures::towerOneBase));
//    splashTurret.setPosition(368.f, 500.f);

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
//    sf::Vector2i mousePos = sf::Mouse::getPosition(*context.window);
//    if (event.type == sf::Event::MouseButtonPressed
//        && event.key.code == sf::Mouse::Left)
//    {
//    }
//    else if (event.type == sf::Event::MouseButtonPressed
//             && event.key.code == sf::Mouse::Right)
//    {
//        action = Action::None;
//    }
//
    container.handleWidgetsEvent(event);
}

void HUD::update(sf::Time dt)
{
    totalGold.setString(std::to_string(player->getGold()));

    totalPlayerLives.setString(std::to_string(player->getHealth()));
    totalFoeLives.setString(std::to_string(foe->getHealth()));

//    currentLevel.setString(std::to_string(gameData->currentLevel + 1));
//    score.setString(std::to_string(gameData->score));
//
//    container.updateWidgets(dt);
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
//    target.draw(star);
    target.draw(totalGold);
    target.draw(totalPlayerLives);
    target.draw(totalFoeLives);
//    target.draw(currentLevel);
//    target.draw(score);
    target.draw(container);
    for (auto i : buffer) {
        target.draw(i);
    }

    auto p = 0.f;
    for (auto warrior : player->getWarriorsBuffer()) {
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