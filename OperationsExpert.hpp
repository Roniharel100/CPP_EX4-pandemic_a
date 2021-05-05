#pragma once
#include "Board.hpp"
#include "Player.hpp"
#include "City.hpp"

namespace pandemic
{
    class OperationsExpert : public Player
    {
    public:
        OperationsExpert(Board&, City);
    };
}
