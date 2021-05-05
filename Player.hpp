#pragma once
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"

using namespace std;

namespace pandemic
{
    class Player
    {
    private:
        Board board;
        City city;

    public:
        Player(Board b, City c)
        {
            board = b;
            city = c;
        }
        virtual Player &drive(City c);
        virtual Player &fly_direct(City c);
        virtual Player &fly_charter(City c);
        virtual Player &fly_shuttle(City c);
        virtual Player &build();
        virtual Player &discover_cure(Color c);
        virtual Player &treat(City c);
        virtual string role();
        virtual Player &take_card(City c);
    };
}