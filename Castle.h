// Project Identifier: B99292359FFD910ED13A7E6C7F9705B874262D79
#ifndef CASTLE_H
#define CASTLE_H

#include <vector>
#include "Tile.h"

class Castle {
public:
    Castle();
    Castle(int numRoomsInput, int roomSizeInput);

    Tile& getTile(int room, int row, int col);
    bool isValidTile(int room, int row, int col) const;
    static bool isWarpTile(const Tile& t);

    void setStartTile(int room, int row, int col);
    void setCountessTile(int room, int row, int col);
    void setTileType(int room, int row, int col, char type);

    inline int getStartRoom() const { return startRoom; }
    inline int getStartRow() const { return startRow; }
    inline int getStartCol() const { return startCol; }
    inline int getCountessRoom() const { return countessRoom; }
    inline int getCountessRow() const { return countessRow; }
    inline int getCountessCol() const { return countessCol; }
    inline int getNumRooms() const { return numRooms; }
    inline int getRoomSize() const { return roomSize; }

private:
    int numRooms;
    int roomSize;

    int startRoom;
    int startRow;
    int startCol;

    int countessRoom;
    int countessRow;
    int countessCol;

    std::vector<std::vector<std::vector<Tile>>> cells;
};

#endif // CASTLE_H