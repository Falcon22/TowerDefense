#ifndef SERVER_LOGICUNITSMANAGER_H
#define SERVER_LOGICUNITSMANAGER_H

#include <memory>
#include <vector>
#include <SFML/System/Time.hpp>

class Castle;
class Bullet;

class LogicUnitsManager {
public:
    explicit LogicUnitsManager();

    void update(const sf::Time& dTime);

    std::shared_ptr<Castle>& getPlayer1();
    std::shared_ptr<Castle>& getPlayer2();
    std::vector<std::shared_ptr<Bullet>>& getBullets();

private:
    void updateBullets(const sf::Time& dTime);

    std::shared_ptr<Castle> player1_;
    std::shared_ptr<Castle> player2_;
    std::vector<std::shared_ptr<Bullet>> bullets_;
};


#endif //SERVER_LOGICUNITSMANAGER_H
