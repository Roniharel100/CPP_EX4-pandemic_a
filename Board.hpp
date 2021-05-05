#pragma once
#include <string>
#include <map>
#include <iostream>
#include "City.hpp"

namespace pandemic
{
    class Board
    {
    private:
        std::map<City, double> worldMap;

    public:
        double &operator[](City c);
        friend std::ostream &operator<<(std::ostream &os, const Board &b);
        bool is_clean();
        void remove_cures();
    };
}