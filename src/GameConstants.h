#ifndef SERVER_GAMECONSTANTS_H
#define SERVER_GAMECONSTANTS_H


class GameConstants {
public:
    static GameConstants& instance();

    int cBARRACKS_1_COST() const;
    int cBARRACKS_2_COST() const;
    int cBARRACKS_3_COST() const;
    int cFARM_COST() const;
    int cFARM_INC_COST_BASE() const;
    int cFARM_LVL_BENEFITS() const;
    int cFARM_TIME_CYCLE() const;
    int cWEAPONS_1_COST() const;
    int cWEAPONS_2_COST() const;
    int cWEAPONS_3_COST() const;
    int cCASTLE_HP() const;
    int cCASTLE_INIT_GOLD() const;
    int cCASTLE_WAVE_DURATION() const;
    int cWARRIORS_BUFFER_SIZE() const;
    int cBULLET_1_DAMAGE() const;
    int cBULLET_1_VELOCITY() const;
    int cBULLET_2_DAMAGE() const;
    int cBULLET_2_VELOCITY() const;
    int cBULLET_3_DAMAGE() const;
    int cBULLET_3_VELOCITY() const;
    int cBULLET_3_AOE() const;
    unsigned int cTOWER_0_UP_COST() const;
    unsigned int cTOWER_1_UP_COST() const;
    int cTOWER_1_RANGE() const;
    int cTOWER_1_COOLDOWN() const;
    unsigned int cTOWER_2_UP_COST() const;
    int cTOWER_2_RANGE() const;
    int cTOWER_2_COOLDOWN() const;
    int cTOWER_3_RANGE() const;
    int cTOWER_3_COOLDOWN() const;
    unsigned int cWARRIOR_1_COST() const;
    int cWARRIOR_1_VELOCITY() const;
    int cWARRIOR_1_HP() const;
    unsigned int cWARRIOR_2_COST() const;
    int cWARRIOR_2_VELOCITY() const;
    int cWARRIOR_2_HP() const;
    int cWAVE_TIMER() const;

    // server

    int cSELECTOR_WAIT_TIME() const;
    int cDEBUG_MODE() const;
    int cCONNECTION_PORT() const;
    const std::string &cIP_ADDR_SERVER() const;

private:
    GameConstants(){};
    GameConstants(const GameConstants&) = delete;
    GameConstants& operator=(const GameConstants&) = delete;

    static bool initialized_;

    int BARRACKS_1_COST;
    int BARRACKS_2_COST;
    int BARRACKS_3_COST;
    int FARM_COST;
    int FARM_INC_COST_BASE;
    int FARM_LVL_BENEFITS;
    int FARM_TIME_CYCLE;
    int WEAPONS_1_COST;
    int WEAPONS_2_COST;
    int WEAPONS_3_COST;
    int CASTLE_HP;
    int CASTLE_INIT_GOLD;
    int CASTLE_WAVE_DURATION;
    int WARRIORS_BUFFER_SIZE;

    int BULLET_1_DAMAGE;
    int BULLET_1_VELOCITY;
    int BULLET_2_DAMAGE;
    int BULLET_2_VELOCITY;
    int BULLET_3_DAMAGE;
    int BULLET_3_VELOCITY;
    int BULLET_3_AOE;

    unsigned int TOWER_0_UP_COST;
    unsigned int TOWER_1_UP_COST;
    int TOWER_1_RANGE;
    int TOWER_1_COOLDOWN;
    unsigned int TOWER_2_UP_COST;
    int TOWER_2_RANGE;
    int TOWER_2_COOLDOWN;
    int TOWER_3_RANGE;
    int TOWER_3_COOLDOWN;

    unsigned int WARRIOR_1_COST;
    int WARRIOR_1_VELOCITY;
    int WARRIOR_1_HP;
    unsigned int WARRIOR_2_COST;
    int WARRIOR_2_VELOCITY;
    int WARRIOR_2_HP;

    int WAVE_TIMER;

    int SELECTOR_WAIT_TIME;
    int DEBUG_MODE;
    int CONNECTION_PORT;
    std::string IP_ADDR_SERVER;
};



#endif //SERVER_GAMECONSTANTS_H
