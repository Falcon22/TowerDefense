#include "Castle.h"
#include "../Units/Warrior/WarriorLvlOne.h"
#include "../Units/Warrior/WarriorLvlTwo.h"
#include "../Units/Tower/TowerLvlZero.h"

Castle::Castle()
    : enemy_(nullptr),
      gold_(kInitGold_),
      health_(kInitHealth_),
      towers_(),
      warriors_(),
      numRealWarriors(0),
      warriorsBuffer_(10, nullptr),
      farm_(),
      barracks_(),
      weapons_(),
      makingWave_(false),
      waveDuration_(0) {
    std::cout << "Castle" << std::endl;
}

Castle::~Castle() {
    for (auto tower: towers_) {
        delete tower;
    }
    for (auto warrior: warriors_) {
        delete warrior;
    }
    for (auto warrior: warriorsBuffer_) {
        delete warrior;
    }
}

int Castle::getGold() const {
    return gold_;
}

int Castle::getHealth() const {
    return health_;
}

const std::vector<Tower*>& Castle::getTowers() const {
    return towers_;
}

std::list<Warrior*>& Castle::getWarriors() {
    return warriors_;
}

const std::vector<Warrior*>& Castle::getWarriorsBuffer() const {
    return warriorsBuffer_;
}

Type Castle::getFarmLvl() const {
    return farm_.getLvl();
}

Type Castle::getBarracksLvl() const {
    return barracks_.getLvl();
}

Type Castle::getWeaponsLvl() const {
    return weapons_.getLvl();
}

void Castle::upgradeTower(int index) {
    Tower::upgrade(towers_[index]);
}

void Castle::upgradeBuilding(char type) {
    switch (type) {
        case 'f':
            farm_.upgrade();
            break;
        case 'b':
            barracks_.upgrade();
            break;
        case 'w':
            weapons_.upgrade();
            break;
    }
}

void Castle::addWarrior(Type type, const Map::LogicMap& logicMap) {
    switch (type) {
        case Type::lvlOne:
            warriorsBuffer_.at(numRealWarriors) = new WarriorLvlOne(logicMap.start, logicMap);
            break;
        case Type::lvlTwo:
            warriorsBuffer_.at(numRealWarriors) = new WarriorLvlTwo(logicMap.start, logicMap);
            break;
    }
    gold_ -= warriorsBuffer_[numRealWarriors]->getCost();
    ++numRealWarriors;
}

void Castle::updateCastle(const sf::Time& dTime) {
    gold_ += farm_.getBenefits(dTime);
    for (auto warrior = warriors_.begin(); warrior != warriors_.end();) {
        (*warrior)->update(dTime);
        if (!(*warrior)->isAlive() || (*warrior)->isFinished()) {
            if ((*warrior)->isFinished()) {
                enemy_->takeDamage((*warrior)->getHp());
            }
            delete *warrior;
            warrior = warriors_.erase(warrior);
        }
        else
            ++warrior;
    }
    for (auto tower : towers_) {
        tower->update(dTime);
    }
    if (makingWave_) {
        makeWave(dTime);
    }
}

void Castle::takeDamage(int damage) {
    health_ -= damage;
}

void Castle::setEnemy(Castle* castle) {
    enemy_ = castle;
}

void Castle::addTower(const sf::Vector2f& position, std::list<Warrior*>& warriors, std::vector<Bullet*>& bullets) {
    towers_.push_back(new TowerLvlZero(position, warriors, bullets));
}

void Castle::makeWave(const sf::Time& dTime) {
    waveDuration_ -= dTime.asMilliseconds();
    if (waveDuration_ <= 0) {
        waveDuration_ = kWaveDuration_;
        if (numRealWarriors > 0) {
            --numRealWarriors;
            warriors_.push_back(warriorsBuffer_[numRealWarriors]);
            warriorsBuffer_[numRealWarriors] = nullptr;
        } else {
            makingWave_ = false;
        }
    }
}

void Castle::letsMakingWave() {
    makingWave_ = true;
}

std::string Castle::generateWaveString(const Castle& player) {
    std::string value;
    for (auto warrior: player.getWarriorsBuffer()) {
        if (warrior != nullptr) {
            switch (warrior->getType()) {
                case Type::lvlOne:
                    value.push_back('1');
                    break;
                case Type::lvlTwo:
                    value.push_back('2');
                    break;
            }
        }
    }
    return value;
}

size_t Castle::getWarriorsInBuffer() const {
    return numRealWarriors;
}
