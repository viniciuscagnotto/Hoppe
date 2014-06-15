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

#include "MainMenu.h"
#include "IwGx.h"
#include "input.h"
#include "audio.h"
#include "resources.h"
#include "game.h"

MainMenu::~MainMenu()
{
}

void MainMenu::startGame(CTween* pTween)
{
    // Switch to game scene
    Game* game = (Game*)g_pSceneManager->Find("game");
    g_pSceneManager->SwitchTo(game);

    // Start game music
    Audio::PlayMusic("audio/in_game.mp3", true);

    // Create new game
    game->newGame();
}

void MainMenu::Update(float deltaTime, float alphaMul)
{
    if (!m_IsActive)
        return;

    Scene::Update(deltaTime, alphaMul);

    // Detect screen tap
    if (m_IsInputActive && m_Manager->GetCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
    {
        g_pInput->Reset();
        if (playButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
        {
            // Animate the play button
            m_Tweener.Tween(0.5f,
                            FLOAT, &playText->m_Angle, 360.0f,
                            FLOAT, &playText->m_Alpha, 0.3f,
                            END);
            m_Tweener.Tween(0.2f,
                            FLOAT, &playButton->m_Alpha, 0.3f,
                            DELAY, 0.25f,
                            EASING, Ease::powIn,
                            ONCOMPLETE, startGame,
                            END);
        }
    }
}

void MainMenu::Render()
{
    Scene::Render();
}

void MainMenu::Init()
{
    Scene::Init();

    Game* game = (Game*)g_pSceneManager->Find("game");

    // Create menu background
    CSprite* background = new CSprite();
    background->m_X = (float)IwGxGetScreenWidth() / 2;
    background->m_Y = (float)IwGxGetScreenHeight() / 2;
    background->SetImage(g_pResources->getMenuBG());
    background->m_W = background->GetImage()->GetWidth();
    background->m_H = background->GetImage()->GetHeight();
    background->m_AnchorX = 0.5;
    background->m_AnchorY = 0.5;
    // Fit background to screen size
    background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
    background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
    AddChild(background);

    // Create Start Game button
    float y_pos = (float)IwGxGetScreenHeight() * 0.66f;
    playButton = new CSprite();
    playButton->SetImage(g_pResources->getPlacard());
    playButton->m_X = IwGxGetScreenWidth() / 2.0f;
    playButton->m_Y = y_pos;
    playButton->m_W = playButton->GetImage()->GetWidth();
    playButton->m_H = playButton->GetImage()->GetHeight();
    playButton->m_AnchorX = 0.5f;
    playButton->m_AnchorY = 0.5f;
    playButton->m_ScaleX = game->getGraphicsScale() * 1.5f;
    playButton->m_ScaleY = game->getGraphicsScale() * 1.5f;
    AddChild(playButton);

    // Create Start Game button text
    playText = new CSprite();
    playText->SetImage(g_pResources->getPlayButton());
    playText->m_X = (float)IwGxGetScreenWidth() / 2;
    playText->m_Y = y_pos;
    playText->m_W = playText->GetImage()->GetWidth();
    playText->m_H = playText->GetImage()->GetHeight();
    playText->m_AnchorX = 0.5f;
    playText->m_AnchorY = 0.5f;
    playText->m_ScaleX = game->getGraphicsScale();
    playText->m_ScaleY = game->getGraphicsScale();
    AddChild(playText);

    // Start menu music
    Audio::PlayMusic("audio/frontend.mp3");

}

