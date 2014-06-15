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

#include "gem.h"
#include "game.h"
#include "explosion.h"
#include "resources.h"
#include "main.h"

int Gem::gemFallSpeed = 500;
int Gem::gemDestroyedScore = 10;

Gem::~Gem()
{
}

void Gem::setType(int type)
{
    Type = type;
    SetAtlas(g_pResources->getGemAtlas(type));
    SetAnimRepeat(1);
}

void Gem::init(float x, float y, CAtlas* atlas)
{
    m_X = x;
    m_Y = y;
    SetAtlas(atlas);
    SetAnimDuration(2);
    SetAnimRepeat(1);
}

// Explode gem
void Gem::explode()
{
    // Fade the gem out
    Game* game = (Game*)g_pSceneManager->Find("game");
    game->GetTweener().Tween(0.2f,
                                FLOAT, &m_Alpha, 0.0f,
                                EASING, Ease::sineIn,
                                END);

    // Remove the gem from play
    game->removeGem(this);

    // Update round score
    game->addToRoundScore(gemDestroyedScore, Type);

    // Create an explosion
    g_pExplosionManager->Create(m_X + (m_W / 2) * game->getGraphicsScale(), m_Y + (m_W / 2) * game->getGraphicsScale());
}



