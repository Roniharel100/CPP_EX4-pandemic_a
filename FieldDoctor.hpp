#pragma once
#include "Board.hpp"
#include "Player.hpp"
#include "City.hpp"

namespace pandemic
{
    class FieldDoctor : public Player
    {
    public:
        FieldDoctor(Board&, City);
    };
}