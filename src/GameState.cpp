#include "GameState.h"
#include "Game.h"
#include "Units/Bullet/Bullet.h"
#include "Units/Warrior/WarriorLvlTwo.h"
#include "Units/Tower/TowerLvlOne.h"
#include "Castle/Castle.h"
#include "Graphics/Gui.h"
#include "Graphics/Button.h"

//TODO: что-то не то с lvl*
GameState::GameState(StateManager &stack, States::Context context) :
        player1(new Castle),
        player2(new Castle),
        State(stack, context),
        gameData(),
        map(*context.window),
        clock(sf::Time::Zero),
        waveTimer(kWaveTimer) {
    map.analyze(towers1, towers2);
    player1->setEnemy(player2);
    player2->setEnemy(player1);
    bulletSprite.setTexture((*context.textureHolder).get(Textures::bulletOne));
    bulletSprite.setOrigin(bulletSprite.getTextureRect().width / 2, bulletSprite.getTextureRect().height / 2);
    warriorSprite1.setTexture((*context.textureHolder).get(Textures::star));
    warriorSprite1.setTextureRect(sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
    warriorSprite1.setOrigin(warriorSprite1.getTextureRect().width / 2, warriorSprite1.getTextureRect().height / 2);
    warriorSprite2.setTexture((*context.textureHolder).get(Textures::star));
    //warriorSprite2.setScale({0.5, 0.5});
    warriorSprite2.setTextureRect(sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
    warriorSprite2.setOrigin(warriorSprite2.getTextureRect().width / 2, warriorSprite2.getTextureRect().height / 2);
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
                    player1->getWeaponsLvl() != Type::lvlTwo) {
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
                    (player2->getWeaponsLvl() != Type::lvlTwo)) {
                    getContext().outcoming_events.emplace_back(2, 't', std::to_string(ind), clock + sf::milliseconds(2000));
                    std::cout << ind << std::endl;
                }
            });
            container.addWidget(bt);
        }
    }

    towerSprite.setTexture(getContext().textureHolder->get(Textures::towerOneTop));
    towerSprite.setOrigin(towerSprite.getTextureRect().width / 2, towerSprite.getTextureRect().height / 2);
    towerSprite2.setTexture(getContext().textureHolder->get(Textures::towerTwoTop));
    towerSprite2.setOrigin(towerSprite2.getTextureRect().width / 2, towerSprite2.getTextureRect().height / 2);
}

GameState::~GameState() {
    for (auto bullet: bullets) {
        delete bullet;
    }
    delete player1;
    delete player2;
}
//handleEventу без времени плохо: как деактивировать кнопки на время? как следить за таймером волны?
//нужно точно знать игрока за данным компьютером, иначе от кого генерировать события?
bool GameState::handleEvent(const sf::Event& event) {
    //Эвенты с игры

    //сюда заходит, только если есть эвенты на экране, проблема

    //Серверные эвенты
    //manageEvents();

    container.handleWidgetsEvent(event);

    if (event.type == sf::Event::KeyReleased
        && event.key.code == sf::Keyboard::P)
    {
        player1->addWarrior(Type::lvlTwo, map.getRoadRect());
        std::cout << "pressed P " << player1->getWarriorsInBuffer() << std::endl;
    }
}

bool GameState::update(sf::Time dt) {
//    std::cout << clock.asMilliseconds() << std::endl;

//    std::cout << getContext().incoming_events.size() << std::endl;
//    std::cout << getContext().outcoming_events.size() << std::endl;

    for (auto &&event : getContext().incoming_events) {
        events.emplace_back(event.id, event.type, event.value, event.time);
    }

    if (waveTimer <= clock.asSeconds()) {
        waveTimer += kWaveTimer;
        getContext().outcoming_events.emplace_back(
                    getContext().id, 'w', Castle::generateWaveString(*player1), clock + sf::milliseconds(2000));
    }

    for (auto &&event : getContext().outcoming_events) {
        events.emplace_back(event.id, event.type, event.value, event.time);
    }
//    getContext().outcoming_events.clear();

    //сгенерировать событие отправки волны!!!
    clock += dt;
    //std::cout << clock.asSeconds() << " " << waveTimer << std::endl;
    manageEvents();
    player1->updateCastle(dt);
    player2->updateCastle(dt);
    for (auto bullet = bullets.begin(); bullet != bullets.end();) { // use smart ptrs!
        (*bullet)->update(dt);
        if ((*bullet)->isExploded() || (*bullet)->isDisappeared()) {
            delete *bullet;
            bullet = bullets.erase(bullet);
        }
        else {
            ++bullet;
        }
    }
}

void GameState::draw() {
    map.draw();
    
    for (auto bullet: bullets) {
        bulletSprite.setRotation(bullet->getAngle());
        bulletSprite.setPosition(bullet->getPosition());
        getContext().window->draw(bulletSprite);
    }

    for (auto tower: player1->getTowers()) {
        towerSprite.setRotation(tower->getAngle());
        towerSprite.setPosition(tower->getPosition());
        getContext().window->draw(towerSprite);
    }

    for (auto tower: player2->getTowers()) {
        towerSprite2.setRotation(tower->getAngle());
        towerSprite2.setPosition(tower->getPosition());
        getContext().window->draw(towerSprite2);
    }

    for (auto warrior: player1->getWarriors()) {
        switch (warrior->getType()) {
            case Type::lvlOne:
                warriorSprite1.setRotation(warrior->getDirection());
                warriorSprite1.setPosition(warrior->getPosition());
                getContext().window->draw(warriorSprite1);
                break;
            case Type::lvlTwo:
                warriorSprite2.setRotation(warrior->getDirection());
                warriorSprite2.setPosition(warrior->getPosition());
                getContext().window->draw(warriorSprite2);
                break;
        }
    }

    for (auto warrior: player2->getWarriors()) {
        switch (warrior->getType()) {

            case Type::lvlOne:
                warriorSprite1.setRotation(warrior->getDirection());
                warriorSprite1.setPosition(warrior->getPosition());
                getContext().window->draw(warriorSprite1);
                break;
            case Type::lvlTwo:
                warriorSprite2.setRotation(warrior->getDirection());
                warriorSprite2.setPosition(warrior->getPosition());
                getContext().window->draw(warriorSprite2);
                break;
        }
    }

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





