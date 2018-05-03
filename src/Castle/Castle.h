#ifndef TOWERDEFENSE_CASTLE_H
#define TOWERDEFENSE_CASTLE_H

#include <vector>
#include <list>
#include "../Units/Tower/Tower.h"
#include "../Units/Warrior/Warrior.h"
#include "Building/Farm.h"
#include "Building/Barracks.h"
#include "Building/Weapons.h"


class Castle {
public:
    Castle();
    ~Castle();

    void updateCastle(const sf::Time& dTime);
    void upgradeTower(int index);
    void upgradeBuilding(char type);
    void addWarrior(Type type, const Map::LogicMap& logicMap);
    void addTower(const sf::Vector2f& position, std::list<Warrior*>& warriors, std::vector<Bullet*>& bullets);
    void takeDamage(int damage);
    void setEnemy(Castle* castle);
    void letsMakingWave();
    void makeWave(const sf::Time& dTime);

    static std::string generateWaveString(const Castle& player);

    int getGold() const;
    int getHealth() const;
    const std::vector<Tower*>& getTowers() const;
    std::list<Warrior*>& getWarriors();
    const std::vector<Warrior*>& getWarriorsBuffer() const;
    size_t getWarriorsInBuffer() const;
    Type getFarmLvl() const;
    Type getBarracksLvl() const;
    Type getWeaponsLvl() const;

private:
    static const int kInitGold_ = 1000;
    static const int kInitHealth_ = 1000;
    static const int kWaveDuration_ = 2000;//mseconds

    int gold_;
    int health_;
    Castle* enemy_;
    std::vector<Tower*> towers_;
    std::list<Warrior*> warriors_;
    size_t numRealWarriors;
    std::vector<Warrior*> warriorsBuffer_;

    Farm farm_;
    Barracks barracks_;
    Weapons weapons_;

    bool makingWave_;
    sf::Int32 waveDuration_;


};


#endif //TOWERDEFENSE_CASTLE_H
