// Project Identifier: B99292359FFD910ED13A7E6C7F9705B874262D79
#include "Runner.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

static bool isValidMapChar(char c)
{
    return c == '.' || c == '#' || c == '!' || c == 'S' 
        || c == 'C' || (c >= '0' && c <= '9');
}

Runner::Runner(bool useStackMode, char outputModeChar)
    : useStack(useStackMode), outputMode(outputModeChar), ourCastle()
{}

Castle& Runner::readCastle(istream& input)
{
    char inputMode;
    int numRooms, roomSize;
    input >> inputMode >> numRooms >> roomSize;

    if (numRooms <= 0 || roomSize <= 0)
    {
        cerr << "Error: Invalid castle dimensions\n";
        exit(1);
    }

    if (inputMode != 'M' && inputMode != 'L')
    {
        cerr << "Error: Invalid input mode\n";
        exit(1);
    }

    string line;
    getline(input, line);

    ourCastle = Castle(numRooms, roomSize);

    if (inputMode == 'M')
    {
        for (int room = 0; room < numRooms; ++room)
        {
            int rowsRead = 0;
            while (rowsRead < roomSize && getline(input, line))
            {
                size_t pos = 0;
                while (pos < line.size() && isspace(static_cast<unsigned char>(line[pos])))
                    ++pos;

                if (pos >= line.size())
                    continue;

                if (line[pos] == '/' && pos + 1 < line.size() && line[pos + 1] == '/')
                    continue;

                for (int col = 0; col < roomSize; ++col)
                {
                    char c = (col + pos < line.length()) ? line[col + pos] : '.';

                    if (!isValidMapChar(c))
                    {
                        cerr << "Error: Invalid map character\n";
                        exit(1);
                    }

                    ourCastle.setTileType(room, rowsRead, col, c);

                    if (c == 'S')
                    {
                        ourCastle.setStartTile(room, rowsRead, col);
                    }
                    else if (c == 'C')
                    {
                        ourCastle.setCountessTile(room, rowsRead, col);
                    }
                }
                ++rowsRead;
            }
        }
    }
    else // L mode
    {
        while (getline(input, line))
        {
            size_t pos = 0;
            while (pos < line.size() && isspace(static_cast<unsigned char>(line[pos])))
                ++pos;

            if (pos >= line.size())
                continue;

            if (line[pos] == '/' && pos + 1 < line.size() && line[pos + 1] == '/')
                continue;

            int room, row, col;
            char c;

            if (sscanf(line.c_str() + pos, "(%d,%d,%d,%c)", &room, &row, &col, &c) == 4)
            {
                if (room < 0 || room >= numRooms || 
                    row < 0 || row >= roomSize || 
                    col < 0 || col >= roomSize)
                {
                    cerr << "Error: Invalid coordinates\n";
                    exit(1);
                }

                if (!isValidMapChar(c))
                {
                    cerr << "Error: Invalid map character\n";
                    exit(1);
                }

                ourCastle.setTileType(room, row, col, c);

                if (c == 'S')
                {
                    ourCastle.setStartTile(room, row, col);
                }
                else if (c == 'C')
                {
                    ourCastle.setCountessTile(room, row, col);
                }
            }
        }
    }
    return ourCastle;
}

void Runner::printMapOutput(ostream& output, Castle& castle)
{
    int startRoom = castle.getStartRoom();
    int startRow = castle.getStartRow();
    int startCol = castle.getStartCol();

    output << "Start in room " << startRoom << ", row " << startRow << ", column " << startCol << "\n";

    int numRooms = castle.getNumRooms();
    int roomSize = castle.getRoomSize();

    for (int room = 0; room < numRooms; ++room)
    {
        output << "//castle room " << room << "\n";

        for (int row = 0; row < roomSize; ++row)
        {
            for (int col = 0; col < roomSize; ++col)
            {
                Tile& tile = castle.getTile(room, row, col);

                if (tile.type == 'C')
                {
                    output << 'C';
                }
                else if (tile.moveTaken != ' ')
                {
                    output << tile.moveTaken;
                }
                else
                {
                    output << tile.type;
                }
            }
            output << '\n';
        }
    }
}

void Runner::printListOutput(ostream& output, const vector<PathNode>& path)
{
    output << "Path taken:\n";

    if (path.empty())
    {
        return;
    }

    for (size_t i = 0; i < path.size() - 1; ++i)
    {
        const PathNode& n = path[i];
        output << "(" << n.room << "," << n.row << "," << n.col << "," << n.moveTaken << ")\n";
    }
}

void Runner::run(istream& input, ostream& output, ostream&)
{
    ourCastle = readCastle(input);

    Router router(ourCastle, useStack);

    if (!router.findPath())
    {
        output << "No solution, " << router.getTilesDiscovered() << " tiles discovered.\n";
        return;
    }

    router.reconstructPath();

    vector<PathNode> path = router.getPathVector();

    if (outputMode == 'M')
    {
        printMapOutput(output, ourCastle);
    }
    else
    {
        printListOutput(output, path);
    }
}