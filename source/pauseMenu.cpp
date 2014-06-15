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

#include "PauseMenu.h"
#include "IwGx.h"
#include "input.h"
#include "resources.h"
#include "game.h"
#include "scene.h"
#include "main.h"

PauseMenu::~PauseMenu()
{
}

void PauseMenu::ContinueGame(CTween* pTween)
{
    // Switch to game scene
    Game* game = (Game*)g_pSceneManager->Find("game");
    g_pSceneManager->SwitchTo(game);

    // Resume game
    game->resumeGame();

    // Restore button alpha state
    PauseMenu* menu = (PauseMenu*)g_pSceneManager->Find("pausemenu");
    menu->getContinueGameButton()->m_Alpha = 1.0f;
}

void PauseMenu::NewGame(CTween* pTween)
{
    // Switch to game scene
    Game* game = (Game*)g_pSceneManager->Find("game");
    g_pSceneManager->SwitchTo(game);

    // Resume game
    game->newGame();

    // Restore button alpha state
    PauseMenu* menu = (PauseMenu*)g_pSceneManager->Find("pausemenu");
    menu->getNewGameButton()->m_Alpha = 1.0f;
}

void PauseMenu::NoAds(CTween* pTween)
{
    // Purchase noads
    Game* game = (Game*)g_pSceneManager->Find("game");
    game->purchaseNoAds();

    // Restore button alpha state
    PauseMenu* menu = (PauseMenu*)g_pSceneManager->Find("pausemenu");
    menu->getNoAdsButton()->m_Alpha = 1.0f;
}

void PauseMenu::Update(float deltaTime, float alphaMul)
{
    if (!m_IsActive)
        return;

    Scene::Update(deltaTime, alphaMul);

    // Detect screen tap
    if (m_IsInputActive && m_Manager->GetCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
    {
        g_pInput->Reset();

        if (continueGameButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
        {
            // Animate button
            m_Tweener.Tween(0.2f,
                            FLOAT, &continueGameButton->m_Alpha, 0.3f,
                            ONCOMPLETE, ContinueGame,
                            END);
        }
        else
        if (newGameButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
        {
            // Animate button
            m_Tweener.Tween(0.2f,
                            FLOAT, &newGameButton->m_Alpha, 0.3f,
                            ONCOMPLETE, NewGame,
                            END);
        }
        else
        if (noAdsButton != 0 && noAdsButton->m_IsVisible && noAdsButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
        {
            // Animate button
            m_Tweener.Tween(0.2f,
                            FLOAT, &noAdsButton->m_Alpha, 0.3f,
                            ONCOMPLETE, NoAds,
                            END);
        }
    }
}

void PauseMenu::Render()
{
    Scene::Render();
}

void PauseMenu::Init()
{
    Game* game = (Game*)g_pSceneManager->Find("game");

    // Create menu background
    CSprite* background = new CSprite();
    background->m_X = (float)IwGxGetScreenWidth() / 2;
    background->m_Y = (float)IwGxGetScreenHeight() / 2;
    background->SetImage(g_pResources->getMenuBG());
    background->m_AnchorX = 0.5;
    background->m_AnchorY = 0.5;
    // Fit background to screen size
    background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
    background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
    AddChild(background);

    // Create Continue Game button
    continueGameButton = new CSprite();
    continueGameButton->SetImage(g_pResources->getMenuButton());
    int button_height = (int)(continueGameButton->GetImage()->GetHeight() * game->getGraphicsScale());
    int y_pos = button_height * 2;
    continueGameButton->m_X = (float)IwGxGetScreenWidth() / 2;
    continueGameButton->m_Y = (float)y_pos;
    continueGameButton->m_AnchorX = 0.5f;
    continueGameButton->m_AnchorY = 0;
    continueGameButton->m_ScaleX = game->getGraphicsScale();
    continueGameButton->m_ScaleY = game->getGraphicsScale();
    AddChild(continueGameButton);

    // Create Continue Game button text
    CLabel* label = new CLabel();
    label->m_X = continueGameButton->m_W / 2;
    label->m_Y = continueGameButton->m_H / 2;
    label->m_W = continueGameButton->m_W;
    label->m_H = continueGameButton->m_H;
    label->m_AnchorX = 0.5f;
    label->m_AnchorY = 0.5f;
    label->m_ScaleX = game->getFontScale() / game->getGraphicsScale();  // Compound scaling factors as label ie child of button
    label->m_ScaleY = label->m_ScaleX;
    label->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
    label->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
    label->m_Font = g_pResources->getFont();
    label->m_Text = "Continue",
    label->m_Color = CColor(0xff, 0xff, 0xff, 0xff);
    continueGameButton->AddChild(label);
    y_pos += button_height;

    // Create New  Game button
    newGameButton = new CSprite();
    newGameButton->SetImage(g_pResources->getMenuButton());
    newGameButton->m_X = (float)IwGxGetScreenWidth() / 2;
    newGameButton->m_Y = (float)y_pos;
    newGameButton->m_W = newGameButton->GetImage()->GetWidth();
    newGameButton->m_H = newGameButton->GetImage()->GetHeight();
    newGameButton->m_AnchorX = 0.5f;
    newGameButton->m_AnchorY = 0;
    newGameButton->m_ScaleX = game->getGraphicsScale();
    newGameButton->m_ScaleY = game->getGraphicsScale();
    AddChild(newGameButton);

    // Create Continue Game button text
    label = new CLabel();
    label->m_X = newGameButton->m_W / 2;
    label->m_Y = newGameButton->m_H / 2;
    label->m_W = newGameButton->m_W;
    label->m_H = newGameButton->m_H;
    label->m_AnchorX = 0.5f;
    label->m_AnchorY = 0.5f;
    label->m_ScaleX = game->getFontScale() / game->getGraphicsScale();  // Compound scaling factors as label ie child of button
    label->m_ScaleY = label->m_ScaleX;
    label->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
    label->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
    label->m_Font = g_pResources->getFont();
    label->m_Text = "New Game",
    label->m_Color = CColor(0xff, 0xff, 0xff, 0xff);
    newGameButton->AddChild(label);
    y_pos += button_height;

    /*if (g_pAds->IsEnabled())
    {
        // Create NoAds button
        noAdsButton = new CSprite();
        noAdsButton->SetImage(g_pResources->getMenuButton());
        noAdsButton->m_X = (float)IwGxGetScreenWidth() / 2;
        noAdsButton->m_Y = (float)y_pos;
        noAdsButton->m_W = noAdsButton->GetImage()->GetWidth();
        noAdsButton->m_H = noAdsButton->GetImage()->GetHeight();
        noAdsButton->m_AnchorX = 0.5f;
        noAdsButton->m_AnchorY = 0;
        noAdsButton->m_ScaleX = game->getGraphicsScale();
        noAdsButton->m_ScaleY = game->getGraphicsScale();
        AddChild(noAdsButton);

        // Create Continue Game button text
        label = new CLabel();
        label->m_X = noAdsButton->m_W / 2;
        label->m_Y = noAdsButton->m_H / 2;
        label->m_W = noAdsButton->m_W;
        label->m_H = noAdsButton->m_H;
        label->m_AnchorX = 0.5f;
        label->m_AnchorY = 0.5f;
        label->m_ScaleX = game->getFontScale() / game->getGraphicsScale();  // Compound scaling factors as label ie child of button
        label->m_ScaleY = label->m_ScaleX;
        label->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
        label->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
        label->m_Font = g_pResources->getFont();
        label->m_Text = "Remove Ads",
        label->m_Color = CColor(0xff, 0xff, 0xff, 0xff);
        noAdsButton->AddChild(label);
    }*/
}

void PauseMenu::RemoveNoAdsButton()
{
    noAdsButton->m_IsVisible = false;
}

