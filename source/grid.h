/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */

#if !defined(__GRID_H__)
#define __GRID_H__

#include "gem.h"
#include "Iw2DSceneGraph.h"
#include <list>

#define MAX_GEM_TYPES   5

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

/**
 * @class Grid
 *
 * @brief The game grid.
 *
 * The game grid is a class that is used to create and manage the game grid. This includes:
 * - Generating the initial grid and populating it each round
 * - Fixing up the game grid; removing any 3+ matches from the initial grid
 * - Checking for matching 3+ gems in rows or columns
 * - Removing matched gems and moving others into the spare spaces
 */
class Grid
{
protected:
    Gem**               Gems;               // Grid cells
    int                 Width, Height;      // Grid width and height
    int                 GemSize;            // Actual isply size of gem
    int                 GridOriginX;        // Grids y-axis origin
    int                 GridOriginY;        // Grids y-axis origin
    std::list<Gem*>     MatchedGems;        // Matched gems list
public:
    Gem*        getGem(int x, int y);
    int         getWidth() const        { return Width; }
    int         getHeight() const       { return Height; }
    int         getGridOriginX() const  { return GridOriginX; }
    int         getGridOriginY() const  { return GridOriginY; }
    int         getGemSize() const      { return GemSize; }
public:
    Grid(CNode* scene, int num_columns, int num_rows, int offset_x, int offset_y, int grid_width);
    ~Grid();

    Gem*        getGemScreen(int screen_x, int screen_y);
    void        screenToGrid(int x, int y, int& out_x, int &out_y);

    void        regenerate();
    void        fix();
    void        addGemToMatches(Gem* gem);
    bool        checkMatches();
    void        swapGems(int* grid_x, int* grid_y);
    void        removeGem(Gem* gem);
    void        gemsFalling(float dt);
};

#endif  // __GRID_H__

