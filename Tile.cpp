// Project Identifier: B99292359FFD910ED13A7E6C7F9705B874262D79
#include "Tile.h"

Tile::Tile()
    : type('.'), discoveryID(0),
      prevRoom(-1), prevRow(-1), prevCol(-1), moveTaken(' ')
{}

Tile::Tile(char t)
    : type(t), discoveryID(0),
      prevRoom(-1), prevRow(-1), prevCol(-1), moveTaken(' ')
{}