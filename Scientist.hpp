#pragma once
#include "Board.hpp"
#include "Player.hpp"
#include "City.hpp"

namespace pandemic
{
    class Scientist : public Player
    {
    private:
        int num;

    public:
        Scientist(Board&, City, int);
    };
}