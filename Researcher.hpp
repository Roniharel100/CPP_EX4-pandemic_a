#pragma once
#include "Board.hpp"
#include "Player.hpp"
#include "City.hpp"

namespace pandemic
{
    class Researcher : public Player
    {
    public:
        Researcher(Board&, City);
    };
}