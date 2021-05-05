#pragma once
#include "Board.hpp"
#include "Player.hpp"
#include "City.hpp"

namespace pandemic
{
    class Dispatcher : public Player
    {
    public:
        Dispatcher(Board&, City);
    };
}