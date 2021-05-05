#include "Scientist.hpp"
using namespace std;

namespace pandemic
{
    Scientist::Scientist(Board &b, City c, int num) : Player(b, c)
    {
        this->num = num;
    }
}