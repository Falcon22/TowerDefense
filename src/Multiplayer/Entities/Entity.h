//
// Created by silvman on 16.05.18.
//

#ifndef SERVER_ENTITY_H
#define SERVER_ENTITY_H

namespace mp {
    class entity {
    protected:
        int id;

    public:
        explicit entity(int id = 0);
        virtual ~entity() = default;

        int getId() const;
        void setId(int id);
    };

}


#endif //SERVER_ENTITY_H
