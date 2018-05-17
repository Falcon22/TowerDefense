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
        lComponent.getPlayer1()->addTower(towers1[i], lComponent.getPlayer1()->getWarriors(), lComponent.getBullets());
        //if (getContext().id == 1) {
            auto bt = std::make_shared<gui::Button>();
            bt->setTexture(b);
            bt->setTextureRect(rect);
            p = towers1[i];
            p.x -= TILE_SIZE / 2;
            p.y -= TILE_SIZE / 2;
            bt->setPosition(p);
            bt->setInd(i);
            bt->setCallback([this](int ind) {
                if (lComponent.getPlayer1()->getGold() > lComponent.getPlayer1()->getTowers().at(ind)->getPrice()) {
                    getContext().outcoming_events.emplace_back(1, 't', std::to_string(ind), clock + sf::milliseconds(2000));
                }
            });
            container.addWidget(bt);
        //}
    }

    for (int i = 0; i < towers2.size(); i++) {
        lComponent.getPlayer2()->addTower(towers2[i], lComponent.getPlayer2()->getWarriors(), lComponent.getBullets());
        auto bt = std::make_shared<gui::Button>();
        if (getContext().id == 2) {
            bt->setTexture(b);
            bt->setTextureRect(rect);
            p = towers2[i];
            p.x -= TILE_SIZE / 2;
            p.y -= TILE_SIZE / 2;
            bt->setPosition(p);
            bt->setInd(i);
            bt->setCallback([this](int ind) {
                if (lComponent.getPlayer2()->getGold() > lComponent.getPlayer2()->getTowers().at(ind)->getPrice()) {
                    getContext().outcoming_events.emplace_back(2, 't', std::to_string(ind),
                                                               clock + sf::milliseconds(2000));
                }
            });
            container.addWidget(bt);
        }
    }
}

void GameState::initHUD() {
    hud.init();
    sf::IntRect rect{0, 0, TILE_SIZE, TILE_SIZE};
    auto addLvlOne = std::make_shared<gui::Button>();
    auto addLvlTwo = std::make_shared<gui::Button>();

    std::cout << "1" << std::endl;

    addLvlOne->setCallback([this](int ind) {
        if (getContext().id == 2) {
            lComponent.getPlayer1()->addWarrior(Type::lvlOne, roadRect[1]);
        } else {
            lComponent.getPlayer2()->addWarrior(Type::lvlOne, roadRect[0]);
        }
    });

    std::cout << "2" << std::endl;

    addLvlOne->setTexture(getContext().textureHolder->get(Textures::addWarriorOne));
    addLvlOne->setTextureRect(rect);
    addLvlOne->setPosition(860.f, 705.f);
    addLvlTwo->setCallback([this](int ind) {
        if (getContext().id == 2) {
            lComponent.getPlayer1()->addWarrior(Type::lvlTwo, roadRect[1]);
        } else {
            lComponent.getPlayer2()->addWarrior(Type::lvlTwo, roadRect[0]);
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
        if (getContext().id == 1) {
            lComponent.getPlayer1()->upgradeBuilding('f');
        } else {
            lComponent.getPlayer2()->upgradeBuilding('f');
        }
    });

    std::cout << "10" << std::endl;

    addBarraks->setCallback([this](int ind) {
        std::cout << "barraks" << std::endl;
        if (getContext().id == 1) {
            lComponent.getPlayer1()->upgradeBuilding('b');
        } else {
            lComponent.getPlayer2()->upgradeBuilding('b');
        }
    });

    std::cout << "11" << std::endl;

    addWeapons->setCallback([this](int ind) {
        std::cout << "weapons" << std::endl;
        if (getContext().id == 1) {
            lComponent.getPlayer1()->upgradeBuilding('w');
        } else {
            lComponent.getPlayer2()->upgradeBuilding('w');
        }
    });

    std::cout << "12" << std::endl;

    buttons.addWidget(addFarm);
    buttons.addWidget(addBarraks);
    buttons.addWidget(addWeapons);
    std::cout << "end init hud" << std::endl;
}

bool GameState::handleEvent(const sf::Event& event) {http://shador.ru/metr/
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
        getContext().outcoming_events.emplace_back(2, 'c', "f", clock + sf::milliseconds(1000));
        std::cout << "pressed F " << std::endl;
    }
    if (event.type == sf::Event::KeyReleased
        && event.key.code == sf::Keyboard::B)
    {
        getContext().outcoming_events.emplace_back(2, 'c', "b", clock + sf::milliseconds(1000));
        std::cout << "pressed B " << std::endl;
    }
    if (event.type == sf::Event::KeyReleased
        && event.key.code == sf::Keyboard::C)
    {
        getContext().outcoming_events.emplace_back(2, 'c', "w", clock + sf::milliseconds(1000));
        getContext().outcoming_events.emplace_back(1, 'c', "w", clock + sf::milliseconds(1000));
        std::cout << "pressed C " << std::endl;
    }
    if (event.type == sf::Event::KeyReleased
        && event.key.code == sf::Keyboard::L)
    {

        getContext().outcoming_events.emplace_back(2, 't', "0", clock + sf::milliseconds(2000));
        std::cout << "pressed L " << std::endl;
    }
}

bool GameState::update(sf::Time dt) {
    //std::cout << "update" << std::endl;
    //std::cout << gameConst.cWAVE_TIMER() << std::endl;
//    std::cout << clock.asMilliseconds() << std::endl;

//    std::cout << getContext().incoming_events.size() << std::endl;
    //std::cout << getContext().outcoming_events.size() << std::endl;
    //std::cout << "warriors:  " << player1->getWarriors().size() << std::endl;
    //std::cout << "in buffer: " << player1->getWarriorsInBuffer() << std::endl;
    //std::cout << bullets.size() << std::endl;
    for (auto &&event : getContext().incoming_events) {
        events.emplace_back(event.id, event.type, event.value, event.time);
    }

    if (waveTimer <= clock.asSeconds()) {
        waveTimer += gameConst.cWAVE_TIMER();
        getContext().outcoming_events.emplace_back(/*getContext().id*/1, 'w', Castle::generateWaveString(*lComponent.getPlayer1()), clock + sf::milliseconds(2000));
        getContext().outcoming_events.emplace_back(/*getContext().id*/2, 'w', Castle::generateWaveString(*lComponent.getPlayer2()), clock + sf::milliseconds(2000));
    }

    for (auto &&event : getContext().outcoming_events) {
        events.emplace_back(event.id, event.type, event.value, event.time);
    }
    getContext().outcoming_events.clear();

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
    Castle* player = nullptr;
    for(auto event = events.begin(); event != events.end();) {
        if (event->time > clock) {
            ++event;
            break;
        }
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
                if (event->id == 2) {
                    for (auto type : event->value) {
                        switch (type) {
                            case '1':
                                if (player->getGold() > gameConst.cWARRIOR_1_COST() && player->getBarracks().getLvl() >= 1) {
                                    player->addWarrior(Type::lvlOne, roadRect[0]);
                                }
                                break;
                            case '2':
                                if (player->getGold() > gameConst.cWARRIOR_2_COST() && player->getBarracks().getLvl() >= 2) {
                                    player->addWarrior(Type::lvlTwo, roadRect[1]);
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