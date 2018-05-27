//
// Created by silvman on 16.05.18.
//

#ifndef SERVER_PLAYERMANAGER_H
#define SERVER_PLAYERMANAGER_H

#include "Manager.h"
#include "../Entities/Player.h"

namespace mp {
    class player_manager: public manager<player> {
    private:
        int next_id;

    public:
        player_manager();
        ~player_manager();

        player& get_by_id(int id) override;
        // void add(player &&entity) override;
        player& create();
        void remove(int id) override;
    };

    template<typename T>
    std::list<T>& mp::manager<T>::getEntities() {
        return entities;
    }

}


#endif //SERVER_PLAYERMANAGER_H
