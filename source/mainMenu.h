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

#if !defined(__MAINEMENU_H__)
#define __MAINEMENU_H__

#include "scene.h"

/**
 * @class MainMenu
 *
 * @brief The main menu scene.
 *
 * The main menu scene is a simple scene that contains a background, a button and some text. The main menu is the first scene that is presented to the player upon
 * game boot. The user taps the button to start the game.
 *
 * The main menu scene is responsible for playing the main menu music and in-game music.
 */
class MainMenu : public Scene
{
protected:
    // UI components
    CSprite*    playButton;
    CSprite*    playText;

public:
    MainMenu() {}
    ~MainMenu();

    // initialise the menu
    void            Init();

    // Update the menu
    void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

    // Render the menu
    void            Render();

    // Button callbacks
    static void     startGame(CTween* pTween);

};

#endif  // __MAINEMENU_H__

