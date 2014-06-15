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

#if !defined(__EXPLOSION_H__)
#define __EXPLOSION_H__

#include <list>
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

/**
 * @class Explosion
 *
 * @brief A explosion.
 *
 * An explosion game object. Each explosion has its an InUse flag and sprite node associated with it
 */
class Explosion : public CSprite
{
protected:
    bool        InUse;
public:
    bool        isInUse() const         { return InUse; }
    void        setUsed(bool used)      { InUse = used; }
public:
    Explosion();
    ~Explosion()        {}

    void        Update(float deltaTime, float alphaMul);

};

/**
 * @class ExplosionManager
 *
 * @brief Manages a collection of re-usable explosions.
 */
class ExplosionManager
{
protected:
    std::list<Explosion*>       Explosions; // Explosions list

public:
    Explosion*      Create(float x, float y);
    void            ReleaseAll();

    ~ExplosionManager();

};

extern ExplosionManager*    g_pExplosionManager;

#endif  // __EXPLOSION_H__

