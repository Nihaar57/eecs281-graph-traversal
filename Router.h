// Project Identifier: B99292359FFD910ED13A7E6C7F9705B874262D79
#ifndef ROUTER_H
#define ROUTER_H

#include <vector>
#include <cstdint>
#include "Castle.h"

struct PathNode {
    int room;
    int row;
    int col;
    char moveTaken;
};

class Router {
public:
    Router(Castle& c, bool searchModeInput);

    bool findPath();
    void reconstructPath();
    std::vector<PathNode> getPathVector() const;
    int getTilesDiscovered() const;

private:
    Castle& castle;
    bool searchMode;
    int tilesDiscovered;
    uint16_t currentSearchID;

    void discoverTile(int room, int row, int col, int prevRoom, int prevRow, int prevCol);
};

#endif // ROUTER_H