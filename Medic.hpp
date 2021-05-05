#pragma once
#include "Board.hpp"
#include "Player.hpp"
#include "City.hpp"

namespace pandemic
{
    class Medic : public Player
    {
    public:
        Medic(Board&, City);
    };
}