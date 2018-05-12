#include "GameState.h"
#include "Game.h"
#include "Units/Bullet/Bullet.h"
#include "Units/Warrior/WarriorLvlTwo.h"
#include "Units/Tower/TowerLvlOne.h"
#include "Castle/Castle.h"
#include "Graphics/Gui.h"
#include "Graphics/Button.h"
#include "Graphics/GraphicsUnits/GraphicsCastle.h"
#include "Graphics/GraphicsUnits/GraphicsBullet.h"


GameState::GameState(StateManager &stack, States::Context context) :
        player1(new Castle),
        player2(new Castle),
        State(stack, context),
        gameData(),
        map(*context.window),
        clock(sf::Time::Zero),
        waveTimer(kWaveTimer),
        gComponent(context, *player1, *player2) {
    player1->setEnemy(player2);
    player2->setEnemy(player1);
    map.analyze(towers1, towers2);
    initTower();
}

void GameState::initTower() {
    sf::Texture b = getContext().textureHolder->get(Textures::target);
    sf::IntRect rect{ TILE_SIZE, TILE_SIZE, TILE_SIZE, TILE_SIZE};
    sf::Vector2f p;
    for (int i = 0; i < towers1.size(); i++) {
        player1->addTower(towers1[i], player2->getWarriors(), bullets);
        if (getContext().id == 1) {
            auto bt = std::make_shared<gui::Button>();
            bt->setTexture(b);
            bt->setTextureRect(rect);
            p = towers1[i];
            p.x -= TILE_SIZE / 2;
            p.y -= TILE_SIZE / 2;
            bt->setPosition(p);
            bt->setInd(i);
            bt->setCallback([this](int ind) {
                if (player1->getGold() > player1->getTowers().at(ind)->getPrice() &&
                    player1->getWeaponsLvl() != Type::lvlThree) {
                    getContext().outcoming_events.emplace_back(1, 't', std::to_string(ind), clock + sf::milliseconds(2000));
                    std::cout << ind << std::endl;
                }
            });
            container.addWidget(bt);
        }
    }

    for (int i = 0; i < towers2.size(); i++) {
        player2->addTower(towers2[i], player1->getWarriors(), bullets);
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
                if (player2->getGold() > player2->getTowers().at(ind)->getPrice() &&
                    (player2->getWeaponsLvl() != Type::lvlThree)) {
                    getContext().outcoming_events.emplace_back(2, 't', std::to_string(ind),
                                                               clock + sf::milliseconds(2000));
                    std::cout << ind << std::endl;
                }
            });
            container.addWidget(bt);
        }
    }
}

GameState::~GameState() {
    for (auto bullet: bullets) {
        delete bullet;
    }
    delete player1;
    delete player2;
}

bool GameState::handleEvent(const sf::Event& event) {
    container.handleWidgetsEvent(event);

    if (event.type == sf::Event::KeyReleased
        && event.key.code == sf::Keyboard::P)
    {
        player1->addWarrior(Type::lvlTwo, map.getRoadRect());
        std::cout << "pressed P " << player1->getWarriorsInBuffer() << std::endl;
    }
    if (event.type == sf::Event::KeyReleased
        && event.key.code == sf::Keyboard::U)
    {
        player1->addWarrior(Type::lvlOne, map.getRoadRect());
        std::cout << "pressed U " << player1->getWarriorsInBuffer() << std::endl;
    }
    if (event.type == sf::Event::KeyReleased
        && event.key.code == sf::Keyboard::F)
    {
        getContext().outcoming_events.emplace_back(1, 'c', "f", clock + sf::milliseconds(1000));
        std::cout << "pressed F " << std::endl;
    }
    if (event.type == sf::Event::KeyReleased
        && event.key.code == sf::Keyboard::B)
    {
        getContext().outcoming_events.emplace_back(1, 'c', "b", clock + sf::milliseconds(1000));
        std::cout << "pressed B " << std::endl;
    }
    if (event.type == sf::Event::KeyReleased
        && event.key.code == sf::Keyboard::C)
    {
        getContext().outcoming_events.emplace_back(1, 'c', "w", clock + sf::milliseconds(1000));
        std::cout << "pressed C " << std::endl;
    }
}

bool GameState::update(sf::Time dt) {
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
        waveTimer += kWaveTimer;
        getContext().outcoming_events.emplace_back(
                    /*getContext().id*/1, 'w', Castle::generateWaveString(*player1), clock + sf::milliseconds(2000));//Что здесь дожно происходить? ЧТо такое ID?
        std::cout << "Wave go!" << std::endl;
    }

    for (auto &&event : getContext().outcoming_events) {
        events.emplace_back(event.id, event.type, event.value, event.time);
    }
    getContext().outcoming_events.clear();

    clock += dt;
    manageEvents();

    player1->updateCastle(dt);
    player2->updateCastle(dt);

    updateBullets(dt);
    gComponent.update(dt, getContext(), bullets);
}

void GameState::draw() {
    map.draw();
    gComponent.draw(getContext());
}

void GameState::manageEvents() {
    Castle* player = nullptr;
    //std::cout << events.size() << std::endl;
    for(auto event = events.begin(); event != events.end();) {
        if (event->time > clock) {
            ++event;
            break;
        }
        if (event->id == 1) {
            player = player1;
        } else {
            player = player2;
        }
        switch (event->type) {
            case 't':
                player->upgradeTower(stoi(event->value));
                break;
            case 'w':
                if (player->getWarriorsInBuffer() == 0) {
                    for (auto type : event->value) {
                        switch (type) {
                            case '1':
                                player->addWarrior(Type::lvlOne, map.getRoadRect());
                                break;
                            case '2':
                                player->addWarrior(Type::lvlTwo, map.getRoadRect());
                                break;
                        }
                    }
                }
                player->letsMakingWave();
                break;
            case 'c':
                player->upgradeBuilding(event->value[0]);
                break;
        }
        event = events.erase(event);
    }
}

void GameState::updateBullets(const sf::Time& dTime) {
    for (auto bullet = bullets.begin(); bullet != bullets.end();) { // use smart ptrs!
        if ((*bullet)->isExploded() || (*bullet)->isDisappeared()) {
            delete *bullet;
            bullet = bullets.erase(bullet);
        } else {
            (*bullet)->update(dTime);
            ++bullet;
        }
    }
}
