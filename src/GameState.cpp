#include "GameState.h"
#include "Game.h"
#include "Units/Warrior/WarriorLvlTwo.h"
#include "Units/Tower/TowerLvlOne.h"
#include "Graphics/Gui.h"
#include "Graphics/Button.h"
#include "Graphics/HUD.h"
#include "Graphics/GraphicsUnits/GraphicsCastle.h"
#include "Graphics/GraphicsUnits/GraphicsBullet.h"


GameState::GameState(StateManager &stack, States::Context context) :
        lComponent(),
        State(stack, context),
        gameData(),
        map(*context.window),
        clock(sf::Time::Zero),
        gComponent(context, *lComponent.getPlayer1(), *lComponent.getPlayer2()),
        hud(context, lComponent.getPlayer1(), lComponent.getPlayer2()) {
    std::cout << "start counstructor" << std::endl;

    if (*context.p_id == 1)
        curPlayer = lComponent.getPlayer1();
    else
        curPlayer = lComponent.getPlayer2();

    map.analyze(towers1, towers2);
    std::cout << "Map analyze" << std::endl;
    map.getRoadRect(roadRect);
    std::cout << "Get road rect" << std::endl;
    initTower();
    std::cout << "Init Tower" << std::endl;
    initHUD();
    std::cout << "Init HUD" << std::endl;
}

void GameState::initTower() {
    sf::Texture b = getContext().textureHolder->get(Textures::target);
    sf::IntRect rect{ TILE_SIZE, TILE_SIZE, TILE_SIZE, TILE_SIZE};
    sf::Vector2f p;
    for (int i = 0; i < towers1.size(); i++) {
        lComponent.getPlayer1()->addTower(towers1[i], lComponent.getPlayer2()->getWarriors(), lComponent.getBullets());
        if (*getContext().p_id == 1) {
            auto bt = std::make_shared<gui::Button>();
            bt->setTexture(b);
            bt->setTextureRect(rect);
            p = towers1[i];
            p.x -= TILE_SIZE / 2;
            p.y -= TILE_SIZE / 2;
            bt->setPosition(p);
            bt->setInd(i);
            bt->setCallback([this](int ind) {
                if ((lComponent.getPlayer1()->getGold() > lComponent.getPlayer1()->getTowers().at(ind)->getPrice()) &&
                    (Castle::checkValidUpgradeTower(lComponent.getPlayer1()->getTowers().at(ind)->getType(), lComponent.getPlayer1()->getWeapons().getLvl()))) {
                    getContext().multiplayer->outcoming.emplace_back(1, 't', std::to_string(ind), clock + sf::milliseconds(500));
                    std::cout << ind << std::endl;
                }
            });
            container.addWidget(bt);
        }
    }

    for (int i = 0; i < towers2.size(); i++) {
        lComponent.getPlayer2()->addTower(towers2[i], lComponent.getPlayer1()->getWarriors(), lComponent.getBullets());
        auto bt = std::make_shared<gui::Button>();
        if (*getContext().p_id == 2) {
            bt->setTexture(b);
            bt->setTextureRect(rect);
            p = towers2[i];
            p.x -= TILE_SIZE / 2;
            p.y -= TILE_SIZE / 2;
            bt->setPosition(p);
            bt->setInd(i);
            bt->setCallback([this](int ind) {
                if ((lComponent.getPlayer2()->getGold() > lComponent.getPlayer2()->getTowers().at(ind)->getPrice()) &&
                        (Castle::checkValidUpgradeTower(lComponent.getPlayer2()->getTowers().at(ind)->getType(), lComponent.getPlayer2()->getWeapons().getLvl()))) {
                    getContext().multiplayer->outcoming.emplace_back(2, 't', std::to_string(ind),
                                                               clock + sf::milliseconds(500));
                    std::cout << ind << std::endl;
                }
            });
            container.addWidget(bt);
        }
    }
}

void GameState::initHUD() {
    std::cout << "start init HUD" << std::endl;
    hud.init();
    sf::IntRect rect{0, 0, TILE_SIZE, TILE_SIZE};
    auto addLvlOne = std::make_shared<gui::Button>();
    auto addLvlTwo = std::make_shared<gui::Button>();

    std::cout << "1" << std::endl;

    addLvlOne->setCallback([this](int ind) {



        if (*getContext().p_id == 1) {
            if (lComponent.getPlayer1()->getBarracks().getLvl() >= 1) {
                std::cout << "button warrior id 1" << std::endl;
                lComponent.getPlayer1()->addWarrior(Type::lvlOne, roadRect[0]);
            }
        } else {
            if (lComponent.getPlayer2()->getBarracks().getLvl() >= 2) {
                std::cout << "button warrior id 2" << std::endl;
                lComponent.getPlayer2()->addWarrior(Type::lvlOne, roadRect[1]);
            }
        }
    });

    std::cout << "2" << std::endl;

    addLvlOne->setTexture(getContext().textureHolder->get(Textures::addWarriorOne));
    addLvlOne->setTextureRect(rect);
    addLvlOne->setPosition(860.f, 705.f);
    addLvlTwo->setCallback([this](int ind) {
        if (*getContext().p_id == 1) {
           if (lComponent.getPlayer1()->getBarracks().getLvl() >= 2) {
               std::cout << "button warrior id 1" << std::endl;
               lComponent.getPlayer1()->addWarrior(Type::lvlTwo, roadRect[0]);
           }
        } else {
            if (lComponent.getPlayer2()->getBarracks().getLvl() >= 2) {
                std::cout << "button warrior id 2" << std::endl;
                lComponent.getPlayer2()->addWarrior(Type::lvlTwo, roadRect[1]);
            }
        }
    });

    std::cout << "3" << std::endl;

    addLvlTwo->setTexture(getContext().textureHolder->get(Textures::addWarriorTwo));
    addLvlTwo->setTextureRect(rect);
    addLvlTwo->setPosition(920.f, 705.f);

    std::cout << "4" << std::endl;

    buttons.addWidget(addLvlOne);
    buttons.addWidget(addLvlTwo);

    std::cout << "5" << std::endl;

    auto addFarm = std::make_shared<gui::Button>();
    auto addBarraks = std::make_shared<gui::Button>();
    auto addWeapons = std::make_shared<gui::Button>();

    std::cout << "6" << std::endl;

    addFarm->setTexture(getContext().textureHolder->get(Textures::addFarm));
    addFarm->setTextureRect(rect);
    addFarm->setPosition(280.f, 705.f);

    std::cout << "7" << std::endl;

    addBarraks->setTexture(getContext().textureHolder->get(Textures::addBarraks));
    addBarraks->setTextureRect(rect);
    addBarraks->setPosition(220.f, 705.f);

    std::cout << "8" << std::endl;

    addWeapons->setTexture(getContext().textureHolder->get(Textures::addWeapons));
    addWeapons->setTextureRect(rect);
    addWeapons->setPosition(160.f, 705.f);

    std::cout << "9" << std::endl;

    addFarm->setCallback([this](int ind) {
        std::cout << "farm" << std::endl;
        getContext().multiplayer->outcoming.emplace_back(*getContext().p_id, 'c', "f", clock + sf::milliseconds(2000));
    });

    std::cout << "10" << std::endl;

    addBarraks->setCallback([this](int ind) {
        std::cout << "barraks" << std::endl;
        getContext().multiplayer->outcoming.emplace_back(*getContext().p_id, 'c', "b", clock + sf::milliseconds(2000));
    });

    std::cout << "11" << std::endl;

    addWeapons->setCallback([this](int ind) {
        std::cout << "weapons" << std::endl;
        getContext().multiplayer->outcoming.emplace_back(*getContext().p_id, 'c', "w", clock + sf::milliseconds(2000));
    });

    std::cout << "12" << std::endl;

    buttons.addWidget(addFarm);
    buttons.addWidget(addBarraks);
    buttons.addWidget(addWeapons);
    std::cout << "end init hud" << std::endl;
}

bool GameState::handleEvent(const sf::Event& event) {
//    std::cout << "handle event" << std::endl;
    container.handleWidgetsEvent(event);
    buttons.handleWidgetsEvent(event);
    hud.handleEvent(event);
    auto action = hud.getAction();

    if (action == gui::HUD::Action::Exit) {
        popState();
        pushState(States::ID::Menu);
        hud.setAction(gui::HUD::Action::None);
    }

    if (event.type == sf::Event::KeyReleased
        && event.key.code == sf::Keyboard::P)
    {
        lComponent.getPlayer2()->addWarrior(Type::lvlTwo, roadRect[0]);
        std::cout << "pressed P " << lComponent.getPlayer1()->getWarriorsInBuffer() << std::endl;
    }
    if (event.type == sf::Event::KeyReleased
        && event.key.code == sf::Keyboard::U)
    {
        lComponent.getPlayer2()->addWarrior(Type::lvlOne, roadRect[0]);
        std::cout << "pressed U " << lComponent.getPlayer2()->getWarriorsInBuffer() << std::endl;
    }
    if (event.type == sf::Event::KeyReleased
        && event.key.code == sf::Keyboard::F)
    {
        getContext().multiplayer->outcoming.emplace_back(2, 'c', "f", clock + sf::milliseconds(1000));
        std::cout << "pressed F " << std::endl;
    }
    if (event.type == sf::Event::KeyReleased
        && event.key.code == sf::Keyboard::B)
    {
        getContext().multiplayer->outcoming.emplace_back(2, 'c', "b", clock + sf::milliseconds(1000));
        std::cout << "pressed B " << std::endl;
    }
    if (event.type == sf::Event::KeyReleased
        && event.key.code == sf::Keyboard::C)
    {
        getContext().multiplayer->outcoming.emplace_back(2, 'c', "w", clock + sf::milliseconds(1000));
        getContext().multiplayer->outcoming.emplace_back(1, 'c', "w", clock + sf::milliseconds(1000));
        std::cout << "pressed C " << std::endl;
    }
    if (event.type == sf::Event::KeyReleased
        && event.key.code == sf::Keyboard::L)
    {

        getContext().multiplayer->outcoming.emplace_back(2, 't', "0", clock + sf::milliseconds(2000));
        std::cout << "pressed L " << std::endl;
    }
}

bool GameState::update(sf::Time dt) {
    //std::cout << "update" << std::endl;
    //std::cout << gameConst.cWAVE_TIMER() << std::endl;
//    std::cout << clock.asMilliseconds() << std::endl;

//    std::cout << getContext().multiplayer->incoming.size() << std::endl;
    //std::cout << getContext().multiplayer->outcoming.size() << std::endl;
    //std::cout << "warriors:  " << player1->getWarriors().size() << std::endl;
    //std::cout << "in buffer: " << player1->getWarriorsInBuffer() << std::endl;
    //std::cout << bullets.size() << std::endl;
    for (auto &&event : getContext().multiplayer->incoming) {
        events.emplace_back(event.id, event.type, event.value, event.time);
    }

    if (waveTimer <= clock.asSeconds()) {
        waveTimer += gameConst.cWAVE_TIMER();

//        if (*getContext().p_id == )

        if (!Castle::generateWaveString(*lComponent.getPlayer1()).empty())
            getContext().multiplayer->outcoming.emplace_back(1, 'w', Castle::generateWaveString(*lComponent.getPlayer1()), clock + sf::milliseconds(2000));

        if (!Castle::generateWaveString(*lComponent.getPlayer2()).empty())
            getContext().multiplayer->outcoming.emplace_back(/**getContext().p_id*/2, 'w', Castle::generateWaveString(*lComponent.getPlayer2()), clock + sf::milliseconds(2000));
    }

    for (auto &&event : getContext().multiplayer->outcoming) {
        events.emplace_back(event.id, event.type, event.value, event.time);
    }

    if (!getContext().multiplayer->isConnected())
        getContext().multiplayer->outcoming.clear();

    clock += dt;
    manageEvents();
    hud.update(dt);
    lComponent.update(dt);
    gComponent.update(dt, getContext(), lComponent.getBullets());

   // std::cout << "Farm: " << (int)lComponent.getPlayer2().get()->getFarm().getLvl() << std::endl;
    //std::cout << "Barracks: " << (int)lComponent.getPlayer2().get()->getBarracks().getLvl() << std::endl;
    //std::cout << "Weapons: " << (int)lComponent.getPlayer2().get()->getWeapons().getLvl() << std::endl;
    //std::cout << bullets.size() << " | " << gComponent.getGBulletsSize() << std::endl;
}

void GameState::draw() {
    //std::cout << "draw" << std::endl;
    map.draw();

    getContext().window->draw(hud);
    getContext().window->draw(buttons);
    gComponent.draw(getContext());
    //std::cout << "end draw" << std::endl;
}

void GameState::manageEvents() {
   // std::cout << "manageEvents" << std::endl;
    Castle* player = nullptr;
    //std::cout << events.size() << std::endl;
    for(auto event = events.begin(); event != events.end();) {
        if (event->time > clock) {
            ++event;
            break;
        }

        std::cout << "pr event " << event->id << " " << event->type << " " << event->value << std::endl;

        if (event->id == 1) {
            player = lComponent.getPlayer1().get();
        } else {
            player = lComponent.getPlayer2().get();
        }
        switch (event->type) {
            case 't': {
                int index = stoi(event->value);
                if (player->getGold() >= player->getTowers().at(index).get()->getPrice()) {
                    if (Castle::checkValidUpgradeTower(player->getTowers().at(index).get()->getType(),
                                                       player->getWeapons().getLvl())) {
                        player->upgradeTower(index);
                    }
                }
                break;
            }
            case 'w':
                std::cout << "Wave go!" << std::endl;
                if (event->id != *getContext().p_id) {
                    for (auto type : event->value) {
                        int rect_num = 0;
                        if (*getContext().p_id == 2) {
                            rect_num = 0;
                        } else {
                            rect_num = 1;
                        }

                        switch (type) {
                            case '1':
                                if (player->getGold() > gameConst.cWARRIOR_1_COST() && player->getBarracks().getLvl() >= 0) {
                                    player->addWarrior(Type::lvlOne, roadRect[rect_num]);
                                }
                                break;

                            case '2':
                                if (player->getGold() > gameConst.cWARRIOR_2_COST() && player->getBarracks().getLvl() >= 2) {
                                    player->addWarrior(Type::lvlTwo, roadRect[rect_num]);
                                }
                                break;
                        }
                    }
                }
                player->letsMakingWave();
                break;
            case 'c':
                int upgradeCost = 0;
                switch (event->value[0]) {
                    case 'f':
                        upgradeCost = player->getFarm().getUpgradeCost();
                        break;
                    case 'b':
                        upgradeCost = player->getBarracks().getUpgradeCost();
                        break;
                    case 'w':
                        upgradeCost = player->getWeapons().getUpgradeCost();
                        break;
                }
                if (upgradeCost != 0 && player->getGold() >= upgradeCost) {
                    player->upgradeBuilding(event->value[0]);
                }
                break;
        }
        event = events.erase(event);
    }
}

