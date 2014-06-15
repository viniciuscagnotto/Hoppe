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

#include "explosion.h"
#include "resources.h"
#include "game.h"

#define EXPLOSION_ANIM_DURATION     1.0f

ExplosionManager*   g_pExplosionManager = 0;

Explosion::Explosion() : InUse(false)
{
    SetAtlas(g_pResources->getExplosionAtlas());
    SetAnimDuration(EXPLOSION_ANIM_DURATION);
    SetAnimRepeat(1);
    m_AnchorX = 0.5;
    m_AnchorY = 0.5;
}

void Explosion::Update(float deltaTime, float alphaMul)
{
    int repeat = m_AnimRepeat;
    CSprite::Update(deltaTime, alphaMul);

    // If animation has finished then disable explosion and return it back to pool
    if (repeat == 1 && m_AnimRepeat == 0)
    {
        InUse = false;
        m_IsVisible = false;
    }
}

ExplosionManager::~ExplosionManager()
{
}

Explosion* ExplosionManager::Create(float x, float y)
{
    // Search for a spare explosion slot
    for (std::list<Explosion*>::iterator it = Explosions.begin(); it != Explosions.end(); ++it)
    {
        // Found a free explosion so re-use it
        if (!(*it)->isInUse())
        {
            (*it)->m_X = x;
            (*it)->m_Y = y;
            (*it)->m_IsVisible = true;
            (*it)->setUsed(true);
            (*it)->SetAnimDuration(EXPLOSION_ANIM_DURATION);
            (*it)->SetAnimRepeat(1);
            return *it;
        }
    }

    // No explosion found so allocate a new one
    Game* game = (Game*)g_pSceneManager->Find("game");
    Explosion* exp = new Explosion();
    game->AddChild(exp);
    exp->m_X = x;
    exp->m_Y = y;
    exp->m_ScaleX = game->getGraphicsScale();
    exp->m_ScaleY = game->getGraphicsScale();
    exp->m_IsVisible = true;
    exp->setUsed(true);
    exp->SetAnimDuration(EXPLOSION_ANIM_DURATION);
    exp->SetAnimRepeat(1);

    return exp;
}

void ExplosionManager::ReleaseAll()
{
    // Release all explosions
    for (std::list<Explosion*>::iterator it = Explosions.begin(); it != Explosions.end(); ++it)
    {
        (*it)->setUsed(false);
        (*it)->m_IsVisible = false;
    }
}
