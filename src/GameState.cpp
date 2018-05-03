#include "GameState.h"
#include "Game.h"
#include "Units/Bullet/Bullet.h"
#include "Units/Warrior/WarriorLvlTwo.h"
#include "Units/Tower/TowerLvlOne.h"
#include "Castle/Castle.h"

//TODO: что-то не то с lvl*
GameState::GameState(StateManager &stack, States::Context context) :
        player1(new Castle),
        player2(new Castle),
        State(stack, context),
        gameData(),
        map(*context.window),
        clock(sf::Time::Zero),
        waveTimer(kWaveTimer) {
    map.analyze();
    player1->setEnemy(player2);
    player2->setEnemy(player1);

    player1->addTower({100, 100}, player2->getWarriors(), bullets);
    player1->addTower({100, 300}, player2->getWarriors(), bullets);
    player1->addTower({100, 500}, player2->getWarriors(), bullets);
    player2->addTower({100, 200}, player1->getWarriors(), bullets);
    player2->addTower({100, 400}, player1->getWarriors(), bullets);
    player2->addTower({100, 600}, player1->getWarriors(), bullets);
    bulletSprite.setTexture((*context.textureHolder).get(Textures::bulletTwo));
    bulletSprite.setOrigin(bulletSprite.getTextureRect().width / 2, bulletSprite.getTextureRect().height / 2);
    towerSprite.setTexture((*context.textureHolder).get(Textures::towerTopLvlOne));
    towerSprite.setOrigin(towerSprite.getTextureRect().width / 2, towerSprite.getTextureRect().height / 2);
    towerSprite2.setTexture((*context.textureHolder).get(Textures::towerTopLvlTwo));
    towerSprite2.setOrigin(towerSprite2.getTextureRect().width / 2, towerSprite2.getTextureRect().height / 2);
    warriorSprite1.setTexture((*context.textureHolder).get(Textures::star));
    warriorSprite1.setOrigin(warriorSprite1.getTextureRect().width / 2, warriorSprite1.getTextureRect().height / 2);
    warriorSprite2.setTexture((*context.textureHolder).get(Textures::gold));
    warriorSprite2.setOrigin(warriorSprite2.getTextureRect().width / 2, warriorSprite2.getTextureRect().height / 2);
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

    if (event.type == sf::Event::KeyReleased
        && event.key.code == sf::Keyboard::B) {
        events.emplace_back(1, 'c', "f", clock + sf::milliseconds(2000));
        std::cout << "pressed B" << std::endl;
    }
        if (event.type == sf::Event::KeyReleased
        && event.key.code == sf::Keyboard::U)
    {
        events.emplace_back(1, 't', "0", clock + sf::milliseconds(2000));
        std::cout << "pressed U" << std::endl;
    }
    if (event.type == sf::Event::KeyReleased
        && event.key.code == sf::Keyboard::F)
    {
        events.emplace_back(2, 't', "0", clock + sf::milliseconds(2000));
        std::cout << "pressed F" << std::endl;
    }
    if (event.type == sf::Event::KeyReleased
        && event.key.code == sf::Keyboard::G)
    {
        events.emplace_back(2, 't', "1", clock + sf::milliseconds(2000));
        std::cout << "pressed G" << std::endl;
    }
    if (event.type == sf::Event::KeyReleased
        && event.key.code == sf::Keyboard::O)
    {
        player1->addWarrior(Type::lvlOne, map.getRoadRect());
        std::cout << "pressed O " << player1->getWarriorsInBuffer() << std::endl;
    }
    if (event.type == sf::Event::KeyReleased
        && event.key.code == sf::Keyboard::P)
    {
        player1->addWarrior(Type::lvlTwo, map.getRoadRect());
        std::cout << "pressed P " << player1->getWarriorsInBuffer() << std::endl;
    }


}

bool GameState::update(sf::Time dt) {
    clock += dt;

    if (waveTimer <= clock.asSeconds()) {
        waveTimer += kWaveTimer;
        events.emplace_back(1, 'w', Castle::generateWaveString(*player1), clock + sf::milliseconds(2000));
    }

    manageEvents();

    player1->updateCastle(dt);
    player2->updateCastle(dt);

    for (auto bullet = bullets.begin(); bullet != bullets.end();) {
        if ((*bullet)->isExploded() || (*bullet)->isDisappeared()) {
            delete *bullet;
            bullet = bullets.erase(bullet);
        }
        else {
            ++bullet;
        }
        (*bullet)->update(dt);
    }
}

void GameState::draw() {
    map.draw();
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
    for (auto bullet: bullets) {
        bulletSprite.setRotation(bullet->getAngle());
        bulletSprite.setPosition(bullet->getPosition());
        getContext().window->draw(bulletSprite);
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
                if (player->getWarriorsBuffer().empty()) {
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




