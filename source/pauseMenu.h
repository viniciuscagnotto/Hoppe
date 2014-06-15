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

#if !defined(__PAUSEMENU_H__)
#define __PAUSEMENU_H__

#include "scene.h"

/**
 * @class PauseMenu
 *
 * @brief The pause menu scene.
 *
 * The pause menu scene is a simple sceve that containsa number of buttons:
 * - Continue - Will return to the currently playing game
 * - New Game - Will start a new game
 * - Remove Ads - Removes ads
 *
 * The pause menu is entered from the main game scene when the user taps the pause button icon.
 */
class PauseMenu : public Scene
{
protected:
    // UI components
    CSprite*    continueGameButton;
    CSprite*    newGameButton;
    CSprite*    noAdsButton;
public:
    CSprite*    getContinueGameButton()     { return continueGameButton; }
    CSprite*    getNewGameButton()          { return newGameButton; }
    CSprite*    getNoAdsButton()            { return noAdsButton; }

public:
    PauseMenu() : noAdsButton(0) {}
    ~PauseMenu();

    // initialise the menu
    void            Init();

    // Update the menu
    void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

    // Render the menu
    void            Render();

    void            RemoveNoAdsButton();

    // Button callbacks
    static void     ContinueGame(CTween* pTween);
    static void     NewGame(CTween* pTween);
    static void     NoAds(CTween* pTween);
};

#endif  // __PAUSEMENU_H__

