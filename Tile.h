// Project Identifier: B99292359FFD910ED13A7E6C7F9705B874262D79
#ifndef TILE_H
#define TILE_H

#include <cstdint>

struct Tile {
    char type;
    uint16_t discoveryID;
    int16_t prevRoom;
    int16_t prevRow;
    int16_t prevCol;
    char moveTaken;

    Tile();
    Tile(char t);
};

#endif // TILE_H