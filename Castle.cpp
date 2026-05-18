// Project Identifier: B99292359FFD910ED13A7E6C7F9705B874262D79
#include "Castle.h"
#include <iostream>

using namespace std;

Castle::Castle()
    : numRooms(0), roomSize(0), startRoom(-1), startRow(-1), startCol(-1),
      countessRoom(-1), countessRow(-1), countessCol(-1)
{}

Castle::Castle(int numRoomsInput, int roomSizeInput)
    : numRooms(numRoomsInput), roomSize(roomSizeInput),
      startRoom(-1), startRow(-1), startCol(-1),
      countessRoom(-1), countessRow(-1), countessCol(-1)
{
    cells.resize(numRooms);
    for (int i = 0; i < numRooms; ++i)
    {
        cells[i].resize(roomSize);
        for (int j = 0; j < roomSize; ++j)
        {
            cells[i][j].resize(roomSize);
        }
    }
}

Tile& Castle::getTile(int room, int row, int col)
{
    return cells[room][row][col];
}

bool Castle::isValidTile(int room, int row, int col) const
{
    if (room < 0 || room >= numRooms || row < 0 || row >= roomSize || col < 0 || col >= roomSize)
        return false;
        
    const Tile& t = cells[room][row][col];
    return t.type != '#' && t.type != '!';
}

bool Castle::isWarpTile(const Tile& t)
{
    return t.type >= '0' && t.type <= '9';
}

void Castle::setStartTile(int room, int row, int col)
{
    startRoom = room;
    startRow = row;
    startCol = col;
}

void Castle::setCountessTile(int room, int row, int col)
{
    countessRoom = room;
    countessRow = row;
    countessCol = col;
}

void Castle::setTileType(int room, int row, int col, char type)
{
    cells[room][row][col] = Tile(type);
}