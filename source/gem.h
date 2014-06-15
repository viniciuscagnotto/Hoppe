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

#if !defined(__GEM_H)
#define __GEM_H

#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

#define MAX_GEM_TYPES           5

/**
 * @class Gem
 *
 * @brief A game gem.
 *
 * The game grid consists of a collection of Gems. Each gem has its own type and sprite node associated with it
 */
class Gem : public CSprite
{
protected:
    int         Type;           // Gem type
public:
    void        setType(int type);
    int         getType() const     { return Type; }
public:
    Gem() : Type(-1) {}
    ~Gem();

    void init(float x, float y, CAtlas* atlas);
    void explode();

    static int gemFallSpeed;                    // Speed at which gems fall into place (pixels per second)
    static int gemDestroyedScore;               // Number of points to award the player for destroying a gem
};

#endif  // __GEM_H
