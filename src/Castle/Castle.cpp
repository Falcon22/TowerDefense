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
      numWarriorsToWave_(0),
      numWarriorsInBuffer_(0),
      warriorsBuffer_(),
      farm_(),
      barracks_(),
      weapons_(),
      makingWave_(false),
      waveDuration_(0) {
    std::cout << "Castle" << std::endl;
}

int Castle::getGold() const {
    return gold_;
}

int Castle::getHealth() const {
    return health_;
}

const std::vector<std::shared_ptr<Tower>>& Castle::getTowers() const {
    return towers_;
}

std::list<std::shared_ptr<Warrior>>& Castle::getWarriors() {
    return warriors_;
}

const std::list<std::shared_ptr<Warrior>>& Castle::getWarriorsBuffer() const {
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
    if (numWarriorsInBuffer_ >= kBufferSize_) {
        return;
    }
    switch (type) {
        case Type::lvlOne:
            warriorsBuffer_.push_back(std::make_shared<WarriorLvlOne>(logicMap.start, logicMap));
            break;
        case Type::lvlTwo:
            warriorsBuffer_.push_back(std::make_shared<WarriorLvlTwo>(logicMap.start, logicMap));
            break;
    }
    gold_ -= warriorsBuffer_.back()->getCost();
    ++numWarriorsInBuffer_;
}

void Castle::updateCastle(const sf::Time& dTime) {
    gold_ += farm_.getBenefits(dTime);

    for (auto warrior = warriors_.begin(); warrior != warriors_.end();) {
        (*warrior)->update(dTime);
        if (!(*warrior)->isAlive() || (*warrior)->isFinished()) {
            if ((*warrior)->isFinished()) {
                enemy_->takeDamage((*warrior)->getHp());
            }
            warrior = warriors_.erase(warrior);
        }
        else {
            ++warrior;
        }
    }

    for (const auto &tower : towers_) {
        tower->update(dTime);
    }
    if (makingWave_) {
        makeWave(dTime);
    }
}

void Castle::takeDamage(int damage) {
    health_ -= damage;
}

void Castle::setEnemy(const std::shared_ptr<Castle>& castle) {
    enemy_ = castle;
}

void Castle::addTower(const sf::Vector2f& position, std::list<std::shared_ptr<Warrior>>& warriors, std::vector<std::shared_ptr<Bullet>>& bullets) {
    towers_.push_back(std::make_shared<TowerLvlZero>(position, warriors, bullets));
}

void Castle::makeWave(const sf::Time& dTime) {
    waveDuration_ -= dTime.asMilliseconds();
    if (waveDuration_ <= 0) {
        waveDuration_ = kWaveDuration_;
        if (numWarriorsToWave_ > 0) {
            --numWarriorsToWave_;
            warriors_.push_back(warriorsBuffer_.front());
            warriorsBuffer_.pop_front();
        } else {
            makingWave_ = false;
        }
    }
}

void Castle::letsMakingWave() {
    numWarriorsToWave_ += numWarriorsInBuffer_;
    numWarriorsInBuffer_ = 0;
    makingWave_ = true;
}

std::string Castle::generateWaveString(const Castle& player) {
    std::string value;

    for (const auto& warrior: player.getWarriorsBuffer()) {
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
    return numWarriorsInBuffer_;
}
