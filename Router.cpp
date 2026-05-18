// Project Identifier: B99292359FFD910ED13A7E6C7F9705B874262D79
#include "Router.h"
#include <deque>
#include <algorithm>
#include <tuple>

using namespace std;

Router::Router(Castle& c, bool searchModeInput)
    : castle(c), searchMode(searchModeInput), tilesDiscovered(0), currentSearchID(0)
{}

void Router::discoverTile(int room, int row, int col, int prevRoom, int prevRow, int prevCol)
{
    Tile& t = castle.getTile(room, row, col);
    if (t.discoveryID != currentSearchID)
    {
        t.discoveryID = currentSearchID;
        ++tilesDiscovered;
        t.prevRoom = static_cast<int16_t>(prevRoom);
        t.prevRow = static_cast<int16_t>(prevRow);
        t.prevCol = static_cast<int16_t>(prevCol);
    }
}

bool Router::findPath()
{
    ++currentSearchID;
    tilesDiscovered = 0;

    int numRooms = castle.getNumRooms();

    deque<tuple<int, int, int>> container;

    int startR = castle.getStartRoom();
    int startRow = castle.getStartRow();
    int startCol = castle.getStartCol();

    int countessR = castle.getCountessRoom();
    int countessRow = castle.getCountessRow();
    int countessCol = castle.getCountessCol();

    Tile& startTile = castle.getTile(startR, startRow, startCol);
    startTile.discoveryID = currentSearchID;
    startTile.prevRoom = startTile.prevRow = startTile.prevCol = -1;
    startTile.moveTaken = ' ';
    ++tilesDiscovered;

    container.push_back({startR, startRow, startCol});

    while (!container.empty())
    {
        int room, row, col;
        if (searchMode)
        {
            tie(room, row, col) = container.back();
            container.pop_back();
        }
        else
        {
            tie(room, row, col) = container.front();
            container.pop_front();
        }

        if (room == countessR && row == countessRow && col == countessCol)
            return true;

        Tile& current = castle.getTile(room, row, col);

        if (Castle::isWarpTile(current))
        {
            int targetRoom = current.type - '0';
            if (targetRoom >= 0 && targetRoom < numRooms)
            {
                Tile& warpTile = castle.getTile(targetRoom, row, col);
                if (warpTile.discoveryID != currentSearchID && warpTile.type != '#' && warpTile.type != '!')
                {
                    discoverTile(targetRoom, row, col, room, row, col);
                    if (targetRoom == countessR && row == countessRow && col == countessCol)
                        return true;
                    container.push_back({targetRoom, row, col});
                }
            }
            continue;
        }

        static int directionsRow[4] = {-1, 0, 1, 0};
        static int directionsCol[4] = {0, 1, 0, -1};

        for (uint32_t i = 0; i < 4; ++i)
        {
            int newRow = row + directionsRow[i];
            int newCol = col + directionsCol[i];
            int newRoom = room;

            if (castle.isValidTile(newRoom, newRow, newCol))
            {
                Tile& neighbor = castle.getTile(newRoom, newRow, newCol);
                if (neighbor.discoveryID != currentSearchID)
                {
                    discoverTile(newRoom, newRow, newCol, room, row, col);
                    if (newRoom == countessR && newRow == countessRow && newCol == countessCol)
                        return true;
                    container.push_back({newRoom, newRow, newCol});
                }
            }
        }
    }
    return false;
}

void Router::reconstructPath()
{
    int countessR = castle.getCountessRoom();
    int countessRow = castle.getCountessRow();
    int countessCol = castle.getCountessCol();

    int startR = castle.getStartRoom();
    int startRow = castle.getStartRow();
    int startCol = castle.getStartCol();

    int room = countessR;
    int row = countessRow;
    int col = countessCol;

    while (!(room == startR && row == startRow && col == startCol))
    {
        Tile& cur = castle.getTile(room, row, col);

        int prevRoom = cur.prevRoom;
        int prevRow = cur.prevRow;
        int prevCol = cur.prevCol;

        if (prevRoom == -1)
            break;

        Tile& prev = castle.getTile(prevRoom, prevRow, prevCol);

        if (prevRoom != room)
        {
            prev.moveTaken = 'p';
        }
        else
        {
            int rowDiff = row - prevRow;
            int colDiff = col - prevCol;

            if (rowDiff == -1)
                prev.moveTaken = 'n';
            else if (rowDiff == 1)
                prev.moveTaken = 's';
            else if (colDiff == 1)
                prev.moveTaken = 'e';
            else
                prev.moveTaken = 'w';
        }

        room = prevRoom;
        row = prevRow;
        col = prevCol;
    }
}

vector<PathNode> Router::getPathVector() const
{
    vector<PathNode> path;

    int startR = castle.getStartRoom();
    int startRow = castle.getStartRow();
    int startCol = castle.getStartCol();

    int countessR = castle.getCountessRoom();
    int countessRow = castle.getCountessRow();
    int countessCol = castle.getCountessCol();

    int room = countessR;
    int row = countessRow;
    int col = countessCol;

    while (!(room == startR && row == startRow && col == startCol))
    {
        const Tile& cur = castle.getTile(room, row, col);

        PathNode node;
        node.room = room;
        node.row = row;
        node.col = col;
        node.moveTaken = cur.moveTaken;

        path.push_back(node);

        if (cur.prevRoom == -1)
            break;

        room = cur.prevRoom;
        row = cur.prevRow;
        col = cur.prevCol;
    }

    PathNode startNode;
    startNode.room = startR;
    startNode.row = startRow;
    startNode.col = startCol;
    startNode.moveTaken = castle.getTile(startR, startRow, startCol).moveTaken;
    path.push_back(startNode);

    reverse(path.begin(), path.end());
    return path;
}

int Router::getTilesDiscovered() const
{
    return tilesDiscovered;
}