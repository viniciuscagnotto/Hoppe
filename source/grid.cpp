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

#include "IwGx.h"
#include "IwTween.h"
#include "audio.h"
#include "scene.h"
#include "grid.h"
#include "game.h"
#include "resources.h"
#include "main.h"

using namespace IwTween;

Grid::Grid(CNode* scene, int num_columns, int num_rows, int offset_x, int offset_y, int grid_width)
{
    Width = num_columns;
    Height = num_rows;
    Gems = new Gem* [num_columns * (num_rows + 1)];

    // Calculate gem display size
    int bm_width = (int)g_pResources->getGemAtlas(0)->GetFrameWidth();
    GemSize = (IwGxGetScreenWidth() * bm_width) / GRAPHIC_DESIGN_WIDTH;

    // Calculate gem scale
    float gem_scale = (float)GemSize / bm_width;

    // Create gems
    int index = 0;
    GridOriginX = offset_x;
    GridOriginY = IwGxGetScreenHeight() - (num_rows * GemSize) - offset_y;
    for (int y = 0; y < num_rows; y++)
    {
        for (int x = 0; x < num_columns; x++)
        {
            // Init gem
            Gems[index] = new Gem();
            Gems[index]->init((float)x * GemSize + GridOriginX, GridOriginY + (float)y * GemSize, g_pResources->getGemAtlas(0));
            Gems[index]->m_ScaleX = gem_scale;
            Gems[index]->m_ScaleY = gem_scale;
            // Add to scene
            scene->AddChild(Gems[index]);
            index++;
        }
    }
    // We fill extra row with 1 to give lowest line of blocks something solid to rest on
    for (int x = 0; x < num_columns; x++)
        Gems[index++] = (Gem*)1;

    regenerate();
}

Grid::~Grid()
{
    if (Gems != 0)
        delete [] Gems;
}

void Grid::screenToGrid(int x, int y, int& out_x, int &out_y)
{
    out_x = (x - GridOriginX) / GemSize;
    out_y = (y - GridOriginY) / GemSize;
}

Gem* Grid::getGem(int x, int y)
{
    if (Gems == 0)
        return 0;
    return Gems[y * Width + x];
}

Gem* Grid::getGemScreen(int screen_x, int screen_y)
{
    if (screen_y < GridOriginY)
        return 0;

    return Gems[((screen_y - GridOriginY) / GemSize * Width) + (screen_x - GridOriginX) / GemSize];
}

// Add gem to matches table
void Grid::addGemToMatches(Gem* gem)
{
    // Check to make sure that the gem is not already present
    for (std::list<Gem*>::iterator it = MatchedGems.begin(); it != MatchedGems.end(); ++it)
    {
        if (*it == gem)
            return;
    }

    // Add to matched gems table
    MatchedGems.push_back(gem);
}

// Check for any 3+ matches and builds a table of gems that need to be removed
bool Grid::checkMatches()
{
    bool match = false;
    // Clear matched gem list
    MatchedGems.clear();

    // Check columns for a match
    for (int x = 0; x < Width; x++)
    {
        int count = 0;
        int focus;
        int ox, oy;
        for (int y = 0; y < Height; y++)
        {
            Gem* gem = Gems[y * Width + x];
            int current = gem->getType();
            if (count == 0)
            {
                focus = current;
                count = 1;
                ox = x;
                oy = y;
            }
            else
            if (current == focus)
                count++;

            // We reached the end of a sequence or the end of the column so check for min matches
            if (current != focus || y == Height - 1)
            {
                // Remove matches in column
                if (count >= 3)
                {
                    match = true;
                    for (int i = 0; i < count; i++)
                    {
                        addGemToMatches(Gems[oy * Width + ox]);
                        oy++;
                    }
                }
                focus = current;
                ox = x;
                oy = y;
                count = 1;
            }
        }
    }

    // Check rows for a match
    for (int y = 0; y < Height; y++)
    {
        int count = 0;
        int focus;
        int ox, oy;
        for (int x = 0; x < Width; x++)
        {
            Gem* gem = Gems[y * Width + x];
            int current = gem->getType();
            if (count == 0)
            {
                focus = current;
                count = 1;
                ox = x;
                oy = y;
            }
            else
            if (current == focus)
                count++;

            // We reached the end of a sequence or the end of the row so check for min matches
            if (current != focus || x == Width - 1)
            {
                // Remove matches in row
                if (count >= 3)
                {
                    match = true;
                    for (int i = 0; i < count; i++)
                    {
                        addGemToMatches(Gems[oy * Width + ox]);
                        ox++;
                    }
                }
                focus = current;
                ox = x;
                oy = y;
                count = 1;
            }
        }
    }

    // Destroy any matched gems
    if (MatchedGems.size() > 0)
    {
        g_pAudio->PlaySound("audio/gem_destroyed.wav");
    }
    for (std::list<Gem*>::iterator it = MatchedGems.begin(); it != MatchedGems.end(); ++it)
        (*it)->explode();

    return match;
}

// Fix grid - removes initial 3+ matches
void Grid::fix()
{
    // We check the grids columns and rows for any 3 matches if found then we change one or more gems to the next colour gem
    // to remove the match. We keep re-checking the grid until no matches are found
    bool redo = true;
    while (redo)
    {
        redo = false;
        // Check columns for a match
        for (int x = 0; x < Width; x++)
        {
            int count = 0;
            int focus;
            int ox, oy;
            for (int y = 0; y < Height; y++)
            {
                int current = Gems[y * Width + x]->getType();
                if (count == 0)
                {
                    focus = current;
                    count = 1;
                    ox = x;
                    oy = y;
                }
                else
                if (current == focus)
                    count++;

                // We reached the end of a sequence or the end of the column so check for min matches
                if (current != focus || y == Height - 1)
                {
                    // Remove matches in column
                    if (count >= 3)
                    {
                        oy++;   // Skip to next gem (prevents removing 2 gems in a 4 match)
                        for (int i = 0; i < (count - 1) / 2; i++)
                        {
                            int type = Gems[oy * Width + ox]->getType();
                            Gems[oy * Width + ox]->setType((type + 1) % MAX_GEM_TYPES); // Change to next gem in sequence
                            oy += 2;
                        }
                        redo = true;
                    }
                    focus = current;
                    ox = x;
                    oy = y;
                    count = 1;
                }
            }
        }
        // Check rows for a match
        for (int y = 0; y < Height; y++)
        {
            int count = 0;
            int focus;
            int ox, oy;
            for (int x = 0; x < Width; x++)
            {
                int current = Gems[y * Width + x]->getType();
                if (count == 0)
                {
                    focus = current;
                    count = 1;
                    ox = x;
                    oy = y;
                }
                else
                if (current == focus)
                    count++;

                // We reached the end of a sequence or the end of the row so check for min matches
                if (current != focus || x == Width - 1)
                {
                    // Remove matches in row
                    if (count >= 3)
                    {
                        ox++;   // Skip to next gem (prevents removing 2 gems in a 4 match)
                        for (int i = 0; i < (count - 1) / 2; i++)
                        {
                            int type = Gems[oy * Width + ox]->getType();
                            Gems[oy * Width + ox]->setType((type + 1) % MAX_GEM_TYPES); // Change to next gem in sequence
                            ox += 2;
                        }
                        redo = true;
                    }
                    focus = current;
                    ox = x;
                    oy = y;
                    count = 1;
                }
            }
        }
    }
}

// Regenerate a random grid of gems
void Grid::regenerate()
{
    // Generate a random grid
    int index = 0;
    std::list<Gem*>::iterator it = MatchedGems.begin();
    srand((int)(s3eTimerGetMs() & 0x7fffffff));
    for (int y = 0; y < Height; y++)
    {
        for (int x = 0; x < Width; x++)
        {
            // if an empty grid cell is found then put the gem back into the cell from the gem matches list
            if (Gems[index] == 0)
            {
                Gems[y * Width + x] = *it;
                it++;
            }

            // Reset the gems attributes
            int type = rand() % MAX_GEM_TYPES;
            Gems[index]->setType(type);
            Gems[index]->m_X = GridOriginX + (float)x * GemSize;
            Gems[index]->m_Y = GridOriginY + (float)y * GemSize;
            Gems[index]->m_Alpha = 1.0f;
            index++;
        }
    }

    // Clear matchedg gems list
    MatchedGems.clear();

    // Fix any matches
    fix();
}

// Swap gems
void Grid::swapGems(int* grid_x, int* grid_y)
{
    Gem* gem1 = Gems[grid_y[0] * Width + grid_x[0]];
    Gem* gem2 = Gems[grid_y[1] * Width + grid_x[1]];
    Game* game = (Game*)g_pSceneManager->Find("game");

    // Start gem swap animation
    if (grid_x[0] == grid_x[1])
    {
        game->GetTweener().Tween(0.5f,
                            FLOAT, &gem1->m_Y, gem2->m_Y,
                            FLOAT, &gem2->m_Y, gem1->m_Y,
                            EASING, Ease::sineInOut,
                            END);
    }
    else
    if (grid_y[0] == grid_y[1])
    {
        game->GetTweener().Tween(0.5f,
                            FLOAT, &gem1->m_X, gem2->m_X,
                            FLOAT, &gem2->m_X, gem1->m_X,
                            EASING, Ease::sineInOut,
                            END);
    }

    // Swap gems in the grid
    Gems[grid_y[0] * Width + grid_x[0]] = gem2;
    Gems[grid_y[1] * Width + grid_x[1]] = gem1;
}

// Remove gem from grid
void Grid::removeGem(Gem* gem)
{
    int grid_x, grid_y;
    screenToGrid((int)gem->m_X, (int)gem->m_Y, grid_x, grid_y);
    Gems[grid_y * Width + grid_x] = 0;
}

// Handle falling gems
void Grid::gemsFalling(float dt)
{
    bool falling = false;
    for (int x = 0; x < Width; x++)
    {
        for (int y = Height - 1; y >= 0; y--)
        {
            Gem* g = Gems[y * Width + x];
            Gem* gem_below = Gems[(y + 1) * Width + x];
            if (g != 0 && gem_below == 0)
            {
                int old_x, old_y;
                screenToGrid((int)g->m_X, (int)g->m_Y, old_x, old_y);
                float dy = Gem::gemFallSpeed * g->m_ScaleY * dt;         // Scale fall speed to match different height displays
                if (dy > g->m_H - 1)
                    dy = g->m_H - 1;
                g->m_Y += dy;

                int new_x, new_y;
                screenToGrid((int)g->m_X, (int)g->m_Y, new_x, new_y);
                if (new_y == y)
                {
                    // Still in same block
                    falling = true;
                }
                else
                {
                    // Moved into new block below
                    if (Gems[new_y * Width + new_x] == 0)
                    {
                        // Remove from previous grid cell and insert into new empty cell below
                        Gems[old_y * Width + old_x] = 0;
                        Gems[new_y * Width + new_x] = g;
                        falling = true;
                        if (Gems[(new_y + 1) * Width + new_x] != 0)
                        {
                            // Position sprite because it may have gone over boundary
                            g->m_Y = (float)new_y * GemSize + GridOriginY;
                        }
                    }
                }
            }
        }
    }

    // Traverse removed gems and drop them back into the grid
    std::list<Gem*> removals;
    bool new_gem = false;
    if (falling == false)
    {
        if (MatchedGems.size() > 0)
        {
            Game* game = (Game*)g_pSceneManager->Find("game");
            falling = true;
            for (std::list<Gem*>::iterator it = MatchedGems.begin(); it != MatchedGems.end(); ++it)
            {
                Gem* g = *it;
                int x, y;
                screenToGrid((int)g->m_X, (int)g->m_Y, x, y);
                if (Gems[x] == 0)
                {
                    // Add new gem
                    Gems[x] = g;
                    int type = rand() % MAX_GEM_TYPES;
                    g->setType(type);
                    g->m_Y = (float)GridOriginY;

                    game->GetTweener().Tween(0.5f,
                                                FLOAT, &g->m_Alpha, 1.0f,
                                                EASING, Ease::sineOut,
                                                END);
                    removals.push_back(*it);
                    new_gem = true;
                }
            }
        }
    }
    // Cleanup removed gems in mathed gems list
    for (std::list<Gem*>::iterator it = removals.begin(); it != removals.end(); ++it)
        MatchedGems.remove(*it);

    if (new_gem == true)
    {
        g_pAudio->PlaySound("audio/gem_land.wav");
    }

    if (falling == false)
    {
        if (!checkMatches())
        {
            // Switch back to waiting for gem selection state
            Game* game = (Game*)g_pSceneManager->Find("game");
            game->changeGameState(waitingFirstGem);
        }
    }
}
