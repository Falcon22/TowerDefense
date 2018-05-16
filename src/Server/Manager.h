//
// Created by silvman on 08.04.18.
//

#ifndef TOWERDEFENSE_MANAGER_HPP
#define TOWERDEFENSE_MANAGER_HPP

#include "Entities.h"
#include <list>

namespace mp {
    template<typename T>
    class manager {
    protected:
        std::list<T> entities;

    public:
        virtual std::list<T>& getEntities();

        virtual T& get_by_id(int id) = 0;
//        virtual void add(T&& entity) = 0;
        virtual void remove(int id) = 0;
    };


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


//    class game_manager: public manager<game> {
//    private:
//        int next_id;
//
//    public:
//        game_manager();
//
//        game &get_by_id(int id) override;
////        void add(game &&entity) override;
//        void remove(int id) override;
//    };

}

#endif //TOWERDEFENSE_MANAGER_HPP