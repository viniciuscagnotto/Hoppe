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

#include "resources.h"
#include "Iw2D.h"


Resources::Resources()
{
    // Load images
    Gems[0] = Iw2DCreateImage("textures/sparkle_aubergine.png");
    Gems[1] = Iw2DCreateImage("textures/sparkle_carrots.png");
    Gems[2] = Iw2DCreateImage("textures/sparkle_cauliflower.png");
    Gems[3] = Iw2DCreateImage("textures/sparkle_pepper.png");
    Gems[4] = Iw2DCreateImage("textures/sparkle_tomato.png");
    Grid = Iw2DCreateImage("textures/gamearea.png");
    MenuBG = Iw2DCreateImage("textures/menu_bkg.jpg");
    GameBG = Iw2DCreateImage("textures/bkg.jpg");
    MenuButton = Iw2DCreateImage("textures/button_bg.png");
    Placard = Iw2DCreateImage("textures/placard.png");
    InfoPanel = Iw2DCreateImage("textures/info_panel.png");
    PauseIcon = Iw2DCreateImage("textures/pause_icon.png");
    PlayButton = Iw2DCreateImage("textures/play.png");
    Selector = Iw2DCreateImage("textures/selector.png");
    Explosion = Iw2DCreateImage("textures/smoke_animation.png");
    Facebook = Iw2DCreateImage("textures/facebook_button.png");

    // Load fonts
    Font = Iw2DCreateFont("fonts/arial8.gxfont");

    // Create atlases
    int frame_w = (int)(Gems[0]->GetWidth() / 5);
    int frame_h = (int)(Gems[0]->GetHeight() / 3);
    for (int t = 0; t < MAX_GEM_TYPES; t++)
        GemAtlases[t] = new CAtlas(frame_w, frame_h, 15, Gems[t]);
    frame_w = (int)(Explosion->GetWidth() / 5);
    frame_h = (int)(Explosion->GetHeight() / 3);
    ExplosionAtlas = new CAtlas(frame_w, frame_h, 15, Explosion);
}

Resources::~Resources()
{
    for (int t = 0; t < MAX_GEM_TYPES; t++)
    {
        delete Gems[t];
        delete GemAtlases[t];
    }
    delete ExplosionAtlas;
    delete Grid;
    delete MenuBG;
    delete GameBG;
    delete MenuButton;
    delete InfoPanel;
    delete Placard;
    delete PauseIcon;
    delete PlayButton;
    delete Selector;
    delete Explosion;
    delete Facebook;
    delete Font;
}

// Global resources
Resources* g_pResources = 0;



