#include "Castle.h"
#include "../Units/Warrior/WarriorLvlOne.h"
#include "../Units/Warrior/WarriorLvlTwo.h"
#include "../Units/Tower/TowerLvlZero.h"

Castle::Castle()
    : enemy_(nullptr),
      gold_(GameConstants::instance().cCASTLE_INIT_GOLD()),
      health_(GameConstants::instance().cCASTLE_HP()),
      towers_(),
      warriors_(),
      numWarriorsToWave_(0),
      numWarriorsInBuffer_(0),
      forDurationState_(0),
      warriorsBuffer_(),
      farm_(),
      barracks_(),
      weapons_(),
      makingWave_(false),
      waveDuration_(0) {}

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

void Castle::upgradeTower(int index) {
    gold_ -= Tower::upgrade(towers_[index]);
}

void Castle::upgradeBuilding(char type) {
    switch (type) {
        case 'f':
            gold_ -= farm_.upgrade();
            break;
        case 'b':
            gold_ -= barracks_.upgrade();
            break;
        case 'w':
            gold_ -= weapons_.upgrade();
            break;
    }
}

void Castle::addWarrior(Type type, const Map::LogicMap& logicMap) {
    if (numWarriorsInBuffer_ >= GameConstants::instance().cWARRIORS_BUFFER_SIZE()) {
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

    for (const auto& tower : towers_) {
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
        waveDuration_ = GameConstants::instance().cCASTLE_WAVE_DURATION();
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
    numWarriorsToWave_ += forDurationState_;
    forDurationState_ = 0;
    makingWave_ = true;
}

void Castle::dropBuffer() {
    forDurationState_ += numWarriorsInBuffer_;
    numWarriorsInBuffer_ = 0;
}

std::string Castle::generateWaveString(const Castle& player) {
    std::string value;

    auto buffIterator = player.warriorsBuffer_.begin();
    for (size_t i = 0; i < player.numWarriorsToWave_; i++) {
        buffIterator++;
    }

    for (;buffIterator != player.warriorsBuffer_.end(); buffIterator++) {
        if ((*buffIterator) != nullptr) {
            switch ((*buffIterator)->getType()) {
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

bool Castle::checkValidUpgradeTower(const Type& towerLvl, unsigned char weaponsLvl) {
    return  ((weaponsLvl == 3) || (towerLvl == Type::lvlZero && weaponsLvl >= 1) ||
        (towerLvl == Type::lvlOne && weaponsLvl >= 2));
}

const Farm& Castle::getFarm() const {
    return farm_;
}

const Barracks& Castle::getBarracks() const {
    return barracks_;
}
const Weapons& Castle::getWeapons() const {
    return weapons_;
}

size_t Castle::getWarriorsToWave() const {
    return numWarriorsToWave_;
}
