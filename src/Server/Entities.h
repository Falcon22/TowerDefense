//
// Created by silvman on 08.04.18.
//

#ifndef TOWERDEFENSE_PLAYER_HPP
#define TOWERDEFENSE_PLAYER_HPP

#include <SFML/Network.hpp>

namespace mp {

    struct Event {
        int         id;
        char        type;
        std::string value;
        sf::Time    time;

        Event(int id, char type, const std::string &value, sf::Time time);
        Event(const std::string &sId, const std::string &sType, const std::string &value, const std::string &sTime);
    };

    void parseEventString(const std::string& sEvents, std::vector<mp::Event>& vEvents);
    void encodeEventsToString(std::string& sEvents, std::vector<mp::Event>& vEvents);

    class entity {
    protected:
        int id;

    public:
        explicit entity(int id = 0);
        virtual ~entity() = default;

        int getId() const;
        void setId(int id);
    };



    class player : public entity {
    public:
        enum connection_state {
            notConnected = 0,
            connected,
            notAvailable
        };

        explicit player(int id = 0);
        ~player();

        sf::TcpSocket& getSocket();


        void getEvents();
        void sendEvents();
//        void resendEvents(player& to_who);

        // вызывается у первого игрока для уведомления о начале игры
        bool hasNewData(sf::SocketSelector &selector);

        void disconnect();

        void connect(sf::TcpListener &listener, sf::SocketSelector &selector);

        void startGame();

        bool isAvailable() const;
        bool isConnected() const;

        bool isInGame() const;
        void setInGame();


        std::vector<mp::Event> from_client;
        std::vector<mp::Event> to_send;


    private:
        struct msg {
            static constexpr const char *get_events = "[player:success] get events from ";
            static constexpr const char *not_get_events = "[player:error] can't recieve events";
            static constexpr const char *send_id = "[player:success] send id to ";
            static constexpr const char *not_send_id = "[player:error] send id to";
            static constexpr const char *connect_player = "[success] connected player " ;
            static constexpr const char *not_connect_player = "[fail] didn't connect player" ;
            static constexpr const char *send_events = "[success] send events to " ;
            static constexpr const char *not_send_events = "[error] can't send events to " ;
        };

        sf::TcpSocket       socket_;
        connection_state    state_;
        bool                in_game_;
    };



    class game : public entity {
    private:
        struct msg {
            static constexpr const char *game_running = "[error] game already running" ;
        };

        std::string     name_;
        int             player_id_first_;
        int             player_id_second_;

        bool            first_connected_;
        bool            second_connected_;

        bool            is_started_;

    public:
        explicit game(const std::string& name);

        bool isReady() const;
        void join(int player_id);
        const std::string& getName() const;

        int getFirstId() const;

        int getSecondId() const;


        bool isStarted() const;
        void start();
    };
}

#endif //TOWERDEFENSE_PLAYER_HPP
