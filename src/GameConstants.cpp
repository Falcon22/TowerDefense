#include <fstream>
#include <iostream>
#include "GameConstants.h"

bool GameConstants::initialized_ = false;

GameConstants &GameConstants::instance() {

    static GameConstants gameConstants;
    if (initialized_) {
        return gameConstants;
    }
    initialized_ = true;

    std::ifstream fin("../src/game_config.cfg");
    if (!fin.is_open()) {
        throw std::runtime_error(std::string("Config file doesn't open."));
    }

    std::string name;
    while (fin >> name) {
        if (name == "BARRACKS_1_COST") {
            fin >> gameConstants.BARRACKS_1_COST;
        } else if (name == "BARRACKS_2_COST") {
            fin >> gameConstants.BARRACKS_2_COST;
        } else if (name == "BARRACKS_3_COST") {
            fin >> gameConstants.BARRACKS_3_COST;
        } else if (name == "FARM_COST") {
            fin >> gameConstants.FARM_COST;
        } else if (name == "FARM_INC_COST_BASE") {
            fin >> gameConstants.FARM_INC_COST_BASE;
        } else if (name == "FARM_LVL_BENEFITS") {
            fin >> gameConstants.FARM_LVL_BENEFITS;
        } else if (name == "FARM_TIME_CYCLE") {
            fin >> gameConstants.FARM_TIME_CYCLE;
        } else if (name == "WEAPONS_1_COST") {
            fin >> gameConstants.WEAPONS_1_COST;
        } else if (name == "WEAPONS_2_COST") {
            fin >> gameConstants.WEAPONS_2_COST;
        } else if (name == "WEAPONS_3_COST") {
            fin >> gameConstants.WEAPONS_3_COST;
        } else if (name == "CASTLE_HP") {
            fin >> gameConstants.CASTLE_HP;
        } else if (name == "CASTLE_INIT_GOLD") {
            fin >> gameConstants.CASTLE_INIT_GOLD;
        } else if (name == "CASTLE_WAVE_DURATION") {
            fin >> gameConstants.CASTLE_WAVE_DURATION;
        } else if (name == "WARRIORS_BUFFER_SIZE") {/*____________________________________*/
            fin >> gameConstants.WARRIORS_BUFFER_SIZE;
        } else if (name == "BULLET_1_DAMAGE") {
            fin >> gameConstants.BULLET_1_DAMAGE;
        } else if (name == "BULLET_1_VELOCITY") {
            fin >> gameConstants.BULLET_1_VELOCITY;
        } else if (name == "BULLET_2_DAMAGE") {
            fin >> gameConstants.BULLET_2_DAMAGE;
        } else if (name == "BULLET_2_VELOCITY") {
            fin >> gameConstants.BULLET_2_VELOCITY;
        } else if (name == "BULLET_3_DAMAGE") {
            fin >> gameConstants.BULLET_3_DAMAGE;
        } else if (name == "BULLET_3_VELOCITY") {
            fin >> gameConstants.BULLET_3_VELOCITY;
        } else if (name == "BULLET_3_AOE") {
            fin >> gameConstants.BULLET_3_AOE;/*___________________________________*/
        } else if (name == "TOWER_0_UP_COST") {
            fin >> gameConstants.TOWER_0_UP_COST;
        } else if (name == "TOWER_1_UP_COST") {
            fin >> gameConstants.TOWER_1_UP_COST;
        } else if (name == "TOWER_1_RANGE") {
            fin >> gameConstants.TOWER_1_RANGE;
        } else if (name == "TOWER_1_COOLDOWN") {
            fin >> gameConstants.TOWER_1_COOLDOWN;
        } else if (name == "TOWER_2_UP_COST") {
            fin >> gameConstants.TOWER_2_UP_COST;
        } else if (name == "TOWER_2_RANGE") {
            fin >> gameConstants.TOWER_2_RANGE;
        } else if (name == "TOWER_2_COOLDOWN") {
            fin >> gameConstants.TOWER_2_COOLDOWN;
        } else if (name == "TOWER_3_RANGE") {
            fin >> gameConstants.TOWER_3_RANGE;
        } else if (name == "TOWER_3_COOLDOWN") {
            fin >> gameConstants.TOWER_3_COOLDOWN;
        } else if (name == "WARRIOR_1_COST") {
            fin >> gameConstants.WARRIOR_1_COST;
        } else if (name == "WARRIOR_1_VELOCITY") {
            fin >> gameConstants.WARRIOR_1_VELOCITY;
        } else if (name == "WARRIOR_1_HP") {
            fin >> gameConstants.WARRIOR_1_HP;
        } else if (name == "WARRIOR_2_COST") {
            fin >> gameConstants.WARRIOR_2_COST;
        } else if (name == "WARRIOR_2_VELOCITY") {
            fin >> gameConstants.WARRIOR_2_VELOCITY;
        } else if (name == "WARRIOR_2_HP") {
            fin >> gameConstants.WARRIOR_2_HP;
        } else if (name == "WAVE_TIMER") {
            fin >> gameConstants.WAVE_TIMER;
        } else if (name == "SELECTOR_WAIT_TIME") {
            fin >> gameConstants.SELECTOR_WAIT_TIME;
        } else if (name == "DEBUG_MODE") {
            fin >> gameConstants.DEBUG_MODE;
        } else if (name == "CONNECTION_PORT") {
            fin >> gameConstants.CONNECTION_PORT;
        } else if (name == "IP_ADDR_SERVER") {
            fin >> gameConstants.IP_ADDR_SERVER;
        } else {
            throw std::runtime_error(std::string("Unknown config parameter"));
        }

    }
    fin.close();

    return gameConstants;
}

int GameConstants::cBARRACKS_1_COST() const {
    return BARRACKS_1_COST;
}

int GameConstants::cBARRACKS_2_COST() const {
    return BARRACKS_2_COST;
}

int GameConstants::cBARRACKS_3_COST() const {
    return BARRACKS_3_COST;
}

int GameConstants::cFARM_COST() const {
    return FARM_COST;
}

int GameConstants::cFARM_INC_COST_BASE() const {
    return FARM_INC_COST_BASE;
}

int GameConstants::cFARM_LVL_BENEFITS() const {
    return FARM_LVL_BENEFITS;
}

int GameConstants::cFARM_TIME_CYCLE() const {
    return FARM_TIME_CYCLE;
}

int GameConstants::cWEAPONS_1_COST() const {
    return WEAPONS_1_COST;
}

int GameConstants::cWEAPONS_2_COST() const {
    return WEAPONS_2_COST;
}

int GameConstants::cWEAPONS_3_COST() const {
    return WEAPONS_3_COST;
}

int GameConstants::cCASTLE_HP() const {
    return CASTLE_HP;
}

int GameConstants::cCASTLE_INIT_GOLD() const {
    return CASTLE_INIT_GOLD;
}

int GameConstants::cCASTLE_WAVE_DURATION() const {
    return CASTLE_WAVE_DURATION;
}

int GameConstants::cWARRIORS_BUFFER_SIZE() const {
    return WARRIORS_BUFFER_SIZE;
}

int GameConstants::cBULLET_1_DAMAGE() const {
    return BULLET_1_DAMAGE;
}

int GameConstants::cBULLET_1_VELOCITY() const {
    return BULLET_1_VELOCITY;
}

int GameConstants::cBULLET_2_DAMAGE() const {
    return BULLET_2_DAMAGE;
}

int GameConstants::cBULLET_2_VELOCITY() const {
    return BULLET_2_VELOCITY;
}

int GameConstants::cBULLET_3_DAMAGE() const {
    return BULLET_3_DAMAGE;
}

int GameConstants::cBULLET_3_VELOCITY() const {
    return BULLET_3_VELOCITY;
}

int GameConstants::cBULLET_3_AOE() const {
    return BULLET_3_AOE;
}

int GameConstants::cTOWER_0_UP_COST() const {
    return TOWER_0_UP_COST;
}

int GameConstants::cTOWER_1_UP_COST() const {
    return TOWER_1_UP_COST;
}

int GameConstants::cTOWER_1_RANGE() const {
    return TOWER_1_RANGE;
}

int GameConstants::cTOWER_1_COOLDOWN() const {
    return TOWER_1_COOLDOWN;
}

int GameConstants::cTOWER_2_UP_COST() const {
    return TOWER_2_UP_COST;
}

int GameConstants::cTOWER_2_RANGE() const {
    return TOWER_2_RANGE;
}

int GameConstants::cTOWER_2_COOLDOWN() const {
    return TOWER_2_COOLDOWN;
}

int GameConstants::cTOWER_3_RANGE() const {
    return TOWER_3_RANGE;
}

int GameConstants::cTOWER_3_COOLDOWN() const {
    return TOWER_3_COOLDOWN;
}

int GameConstants::cWARRIOR_1_COST() const {
    return WARRIOR_1_COST;
}

int GameConstants::cWARRIOR_1_VELOCITY() const {
    return WARRIOR_1_VELOCITY;
}

int GameConstants::cWARRIOR_1_HP() const {
    return WARRIOR_1_HP;
}

int GameConstants::cWARRIOR_2_COST() const {
    return WARRIOR_2_COST;
}

int GameConstants::cWARRIOR_2_VELOCITY() const {
    return WARRIOR_2_VELOCITY;
}

int GameConstants::cWARRIOR_2_HP() const {
    return WARRIOR_2_HP;
}

int GameConstants::cWAVE_TIMER() const {
    return WAVE_TIMER;
}

int GameConstants::cSELECTOR_WAIT_TIME() const {
    return SELECTOR_WAIT_TIME;
}

int GameConstants::cDEBUG_MODE() const {
    return DEBUG_MODE;
}

int GameConstants::cCONNECTION_PORT() const {
    return CONNECTION_PORT;
}

const std::string &GameConstants::cIP_ADDR_SERVER() const {
    return IP_ADDR_SERVER;
}
