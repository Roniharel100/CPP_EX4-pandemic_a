#include <string>
#include "Board.hpp"
using namespace std;
using namespace pandemic;

double &Board::operator[](City c)
{
  return worldMap[c];
}

ostream &pandemic::operator<<(ostream &os, const Board &b)
{
  os << "input" << endl;
  return os;
}

bool Board::is_clean()
{
  return worldMap.empty();
}

void Board::remove_cures() {}
