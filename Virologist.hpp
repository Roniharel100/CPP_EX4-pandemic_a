#pragma once
#include "Board.hpp"
#include "Player.hpp"
#include "City.hpp"

namespace pandemic
{
    class Virologist : public Player
    {
    public:
        Virologist(Board&, City);
    };
}