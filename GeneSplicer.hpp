#pragma once
#include "Board.hpp"
#include "Player.hpp"
#include "City.hpp"

namespace pandemic
{
    class GeneSplicer : public Player
    {
    public:
        GeneSplicer(Board&, City);
    };
}
