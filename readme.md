# Graph Traversal — C++

A graph pathfinding solver implemented in C++, created as part of EECS 281 (Data Structures & Algorithms) at the University of Michigan. 

## Overview

Given a multi-room castle map, finds a valid path from the start (S) to the Countess (C) while navigating walls, hazards, and warp tiles between rooms.

The castle is represented as a 3D grid (room, row, column) and supports both depth-first and breadth-first search depending on the selected mode.

Warp tiles (0–9) allow transitions between rooms while preserving position.

## Modes

| Flag             | Mode        | Description                           |
| ---------------- | ----------- | ------------------------------------- |
| `--stack` / `-s` | DFS         | Depth-first traversal using a stack   |
| `--queue` / `-q` | BFS         | Breadth-first traversal using a queue |
| `--output M`     | Map Output  | Prints castle with path overlay       |
| `--output L`     | List Output | Prints path as coordinate list        |

## Usage

```
./superMarco [--stack|--queue] [--output M|L]
```

Input is read from stdin in either:

Map mode (M): grid-based room layouts
List mode (L): coordinate-based tile definitions

## Files

| File         | Description                               |
| ------------ | ----------------------------------------- |
| `main.cpp`   | Argument parsing and program entry        |
| `Runner.cpp` | Input handling and output formatting      |
| `Router.cpp` | BFS/DFS traversal and path reconstruction |
| `Castle.cpp` | Castle grid representation                |
| `Tile.cpp`   | Tile metadata and path tracking           |

## Tools

- **Language:** C++17
- **Build:** Makefile
- **IDE:** VS Code