//
// Created by silvman on 16.05.18.
//

#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#include <list>

namespace mp {
    template<typename T>
    class manager {
    protected:
        std::list <T> entities;

    public:
        virtual std::list <T> &getEntities();

        virtual T &get_by_id(int id) = 0;
        virtual void remove(int id) = 0;
    };
}

#endif //SERVER_MANAGER_H
