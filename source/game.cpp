#include "include.h"

// Grid background offset
#define GRID_OFFSET_X           41
#define GRID_OFFSET_Y           37

Game::~Game()
{
    // Cleanup explosion manager
    delete g_pExplosionManager;

    // Cleanup game grid
    if (gemsGrid != 0)
        delete gemsGrid;
}


// Event handler that is called when a gem swap back animation finishes
void Game::gemSwapBackFinished(Timer* timer, void* userData)
{
    // Switch back to waiting for first gem selection game state
    Game* self = (Game*)userData;
    if (self->getGameState() != roundOver)
        self->changeGameState(waitingFirstGem);
}

// Event handler that is called to start the gems falling process (called after 3 or more gems are matched)
void Game::startGemsFalling(Timer* timer, void* userData)
{
    // Change game state to move gems down and new gems in
    Game* self = (Game*)userData;
    if (self->getGameState() != roundOver)
        self->changeGameState(gemsFalling);
}

// Called back when a gem swap animation finishes
void Game::gemSwapFinished(Timer* timer, void* userData)
{
    Game* self = (Game*)userData;
    if (!self->getGrid()->checkMatches())
    {
        // No match found so swap gems back
        self->getGrid()->swapGems(self->getGridTouchesX(), self->getGridTouchesY());

        // Start a timer that expires when gems have been swapped back
        self->GetTimers().Add(new Timer(0.6f, 1, &Game::gemSwapBackFinished, (void*)self));
    }
    else
    {
        // Match found so start a timer to switch to gem falling state (this gives a small delay to allow destroyed gems to clear)
        self->GetTimers().Add(new Timer(0.6f, 1, &Game::startGemsFalling, (void*)self));
    }
}

// Remove a gem from the game
void Game::removeGem(Gem* gem)
{
    gemsGrid->removeGem(gem);
}

// Changes the game state
void Game::changeGameState(eGameState game_state)
{
    gameState = game_state;
    if (gameState == waitingFirstGem)
    {
        // Hide selector
        selector->m_IsVisible = false;
    }
    else
    if (gameState == waitingSecondGem)
    {
        // Show selector
        selector->m_X = (float)gemsGrid->getGridOriginX() + gridTouchesX[0] * gemsGrid->getGemSize() + gemsGrid->getGemSize() / 2;
        selector->m_Y = (float)gemsGrid->getGridOriginY() + gridTouchesY[0] * gemsGrid->getGemSize() + gemsGrid->getGemSize() / 2;
        selector->m_IsVisible = true;
    }
    else
    if (gameState == thinking)
    {
        // Hide selector
        selector->m_IsVisible = false;

        // Swap the gems
        gemsGrid->swapGems(gridTouchesX, gridTouchesY);

        // Start a timer that expires afer the gems have been swapped
        m_Timers.Add(new Timer(0.8f, 1, &Game::gemSwapFinished, (void*)this));
    }
}

// Add to round score
void Game::addToRoundScore(int score, int gem_type)
{
    // Double score if matched gem matches target gem
    if (gem_type == targetGem)
        score *= 2;
    currentRoundScore += score;
    if (currentRoundScore > targetRoundScore)
    {
        // Play sound effect to let player know they reached target score
    }

    char str[16];
    snprintf(str, 16, "%d", currentRoundScore);
    scoreLabel->m_Text = str;
}

// Sets target gem type
void Game::setTargetGem(int type)
{
    // Change target gem sprite to show the new target gem
    targetGem = type;
    targetGemSprite->SetAtlas(g_pResources->getGemAtlas(targetGem));
    targetGemSprite->m_Y = gemsGrid->getGridOriginY() - targetGemSprite->GetAtlas()->GetFrameHeight() * graphicsScale;
    targetGemSprite->m_IsVisible = true;
}

// Choose a random target gem
void Game::chooseTargetGem(Timer* timer, void* userData)
{
    // Select a random target gem
    Game* self = (Game*)userData;
    self->setTargetGem(rand() % MAX_GEM_TYPES);
}

// Shows the info panel
void Game::showInfoPanel(const char* title, const char* info)
{
    infoPanelVisible = true;
    infoPanelTitleLabel->m_Text = title;
    infoPanelMessageLabel->m_Text = info;

    g_pTweener->Tween(1.0f,
                    FLOAT, &infoPanel->m_X, (float)IwGxGetScreenWidth() / 2 - (g_pResources->getInfoPanel()->GetWidth() / 2 * graphicsScale),
                    EASING, Ease::sineIn,
                    END);
}

// Hides the info panel
void Game::hideInfoPanel()
{
    if (infoPanelVisible)
    {
        infoPanelVisible = false;
        g_pTweener->Tween(1.0f,
                        FLOAT, &infoPanel->m_X, (float)IwGxGetScreenWidth(),
                        EASING, Ease::sineOut,
                        END);
    }
}

// Pause game handler that is called when the user taps the pause sprite
void Game::pauseGame()
{
    // Pause timers
    m_Timers.Pause();

    // Store old game state and change to paused game state
    oldGameState = gameState;
    gameState = paused;

    // Switch to pause menu scene
    g_pSceneManager->SwitchTo(g_pSceneManager->Find("pausemenu"));

//  explosion.stopExplosions()
}

// Resumes the game from a previously paused state
void Game::resumeGame()
{
    // Resume timers
    m_Timers.Resume();

    // Restore pre-paused game state
    gameState = oldGameState;
}

// Initialise a round
void Game::initRound()
{
    // Hide info panel if its visible
    hideInfoPanel();

    // Remove all timers and tweens
    m_Tweener.Clear();
    m_Timers.Clear();

    // Release any explosions that are in progress
    g_pExplosionManager->ReleaseAll();

    // Regenrate grid
    gemsGrid->regenerate();

    // Reset round score
    currentRoundScore = 0;

    // Calculate target round score
    targetRoundScore = START_TARGET_SCORE + currentRound * TARGET_SCORE_STEP;

    // Calculate round time
    currentRoundTime = (float)startRoundTime + currentRound * ROUND_TIME_STEP;

    // Set up labels
    char str[32];
    snprintf(str, 32, "%d", currentRoundScore);
    scoreLabel->m_Text = str;
    snprintf(str, 32, "%d", targetRoundScore);
    targetScoreLabel->m_Text = str;
    snprintf(str, 32, "%d", currentRound);
    roundLabel->m_Text = str;
    snprintf(str, 32, "%d", (int)currentRoundTime);
    timerLabel->m_Text = str;

    // Create target gem timer (changes the target gem every 10 seconds)
    m_Timers.Add(new Timer(10.0f, 0, &Game::chooseTargetGem, (void*)this));

    // Set the game going
    changeGameState(waitingFirstGem);
}

// End of round - Called when the round is over (when game timer runs out)
void Game::endOfRound()
{
    // Show end of round info
    char round[8];
    char score[16];
    snprintf(round, 32, "%d", currentRound);
    snprintf(score, 32, "%d", currentRoundScore);
    std::string title = "Round ";
    title += round;
    std::string msg = "Score: ";
    msg += score;
    if (currentRoundScore >= targetRoundScore)
    {
        title += " Complete";
        showInfoPanel(title.c_str(), msg.c_str());
        g_pAudio->PlaySound("audio/round_won.wav");
        // Move to next round number
        currentRound++;
    }
    else
    {
        title += " Failed";
        showInfoPanel(title.c_str(), msg.c_str());
        g_pAudio->PlaySound("audio/round_lost.wav");
    }

    // Change to round over game state
    changeGameState(roundOver);
}

// Starts a new game - Called from the main and pause menus
void Game::newGame()
{
    currentRound = 1;
    initRound();

    // Log new game event
    if (s3eFlurryAvailable())
        s3eFlurryLogEvent("New Game");
}

void Game::Update(float deltaTime, float alphaMul)
{
    if (!m_IsActive)
        return;

    // Update base scene
    Scene::Update(deltaTime, alphaMul);

    // Update falling gems in grid
    if (gameState == gemsFalling)
        gemsGrid->gemsFalling(deltaTime);

    // Update round timer
    if (gameState != roundOver && gameState != paused)
    {
        if ((int)currentRoundTime != (int)(currentRoundTime - deltaTime))
        {
            char str[32];
            snprintf(str, 32, "%d", (int)currentRoundTime);
            timerLabel->m_Text = str;
        }
        currentRoundTime -= deltaTime;
        if (currentRoundTime <= 0)
        {
            currentRoundTime = 0;
            // Allow last played move to finish
            if (gameState == waitingFirstGem || gameState == waitingSecondGem)
                endOfRound();
        }
    }

    // Detect screen tap
    if (m_IsInputActive && m_Manager->GetCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
    {
        g_pInput->Reset();
        if (gameState == roundOver)
        {
            if (facebookSprite != NULL && facebookSprite->HitTest(g_pInput->m_X, g_pInput->m_Y))
                postFacebookUpdate();
            else
            if (infoPanel->HitTest(g_pInput->m_X, g_pInput->m_Y))
                initRound();
        }
        else
        {
            if (g_pInput->m_Y >= gemsGrid->getGridOriginY())
            {
                int grid_x, grid_y;
                gemsGrid->screenToGrid(g_pInput->m_X, g_pInput->m_Y, grid_x, grid_y);
                if (gameState == waitingFirstGem)
                {
                    // In waiting for first gem state we place a selector over the first selected gem
                    gridTouchesX[0] = grid_x;
                    gridTouchesY[0] = grid_y;
                    changeGameState(waitingSecondGem);
                }
                else
                if (gameState == waitingSecondGem)
                {
                    gridTouchesX[1] = grid_x;
                    gridTouchesY[1] = grid_y;
                    int dx = gridTouchesX[1] - gridTouchesX[0];
                    int dy = gridTouchesY[1] - gridTouchesY[0];
                    if ((dx == 0 && (dy == -1 || dy == 1)) || (dy == 0 && (dx == -1 || dx == 1)))
                    {
                        // Second gem is swappable so switch to thinking state
                        changeGameState(thinking);
                        g_pAudio->PlaySound("audio/gem_swap.wav");
                    }
                    else
                    {
                        // Second gem is too far or the same gem, so reset
                        changeGameState(waitingFirstGem);
                        g_pAudio->PlaySound("audio/gem_wrong.wav");
                    }
                }
            }
            else
            {
                if (pauseSprite->HitTest(g_pInput->m_X, g_pInput->m_Y))
                {
                    // Enter pause menu
                    pauseGame();
                }
            }
        }
    }
}

void Game::Render()
{
    Scene::Render();
}

// Initialise the games user interface
void Game::initUI()
{
    // Create background
    CSprite* background = new CSprite();
    background->m_X = (float)IwGxGetScreenWidth() / 2;
    background->m_Y = (float)IwGxGetScreenHeight() / 2;
    background->SetImage(g_pResources->getGameBG());
    background->m_W = background->GetImage()->GetWidth();
    background->m_H = background->GetImage()->GetHeight();
    background->m_AnchorX = 0.5;
    background->m_AnchorY = 0.5;
    // Fit background to screen size
    background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
    background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
    AddChild(background);

    // Create grid background sprite
    gridSprite = new CSprite();
    gridSprite->m_X = 0;
    gridSprite->m_Y = IwGxGetScreenHeight() - g_pResources->getGrid()->GetHeight() * graphicsScale;
    gridSprite->m_ScaleX = graphicsScale;
    gridSprite->m_ScaleY = graphicsScale;
    gridSprite->SetImage(g_pResources->getGrid());
    AddChild(gridSprite);

    // Create left placard
    leftPlacard = new CSprite();
    leftPlacard->SetImage(g_pResources->getPlacard());
    leftPlacard->m_X = 0;
    leftPlacard->m_Y = (float)uiYPosition;
    leftPlacard->m_ScaleX = graphicsScale;
    leftPlacard->m_ScaleY = graphicsScale;
    AddChild(leftPlacard);

    // Create right placard
    rightPlacard = new CSprite();
    rightPlacard->SetImage(g_pResources->getPlacard());
    rightPlacard->m_X = (float)IwGxGetScreenWidth() - rightPlacard->GetImage()->GetWidth() * graphicsScale;
    rightPlacard->m_Y = (float)uiYPosition;
    rightPlacard->m_ScaleX = graphicsScale;
    rightPlacard->m_ScaleY = graphicsScale;
    AddChild(rightPlacard);

    // Create score label text
    scoreLabelText = new CLabel();
    scoreLabelText->m_X = 30 * fontScale;
    scoreLabelText->m_Y = uiYPosition + 10 * fontScale;
    scoreLabelText->m_W = FONT_DESIGN_WIDTH;
    scoreLabelText->m_H = actualFontHeight;
    scoreLabelText->m_Text = "Score:";
    scoreLabelText->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
    scoreLabelText->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
    scoreLabelText->m_Font = g_pResources->getFont();
    scoreLabelText->m_ScaleX = fontScale;
    scoreLabelText->m_ScaleY = fontScale;
    scoreLabelText->m_Color = CColor(0xff, 0xff, 0x30, 0xff);
    AddChild(scoreLabelText);

    // Create score label (displays actual score)
    scoreLabel = new CLabel();
    scoreLabel->m_X = 80 * fontScale;
    scoreLabel->m_Y = uiYPosition + 10 * fontScale;
    scoreLabel->m_W = FONT_DESIGN_WIDTH;
    scoreLabel->m_H = actualFontHeight;
    scoreLabel->m_Text = "0";
    scoreLabel->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
    scoreLabel->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
    scoreLabel->m_Font = g_pResources->getFont();
    scoreLabel->m_ScaleX = fontScale;
    scoreLabel->m_ScaleY = fontScale;
    AddChild(scoreLabel);

    // Create target score label text
    targetScoreLabelText = new CLabel();
    targetScoreLabelText->m_X = 30 * fontScale;
    targetScoreLabelText->m_Y = uiYPosition + 30 * fontScale;
    targetScoreLabelText->m_W = FONT_DESIGN_WIDTH;
    targetScoreLabelText->m_H = actualFontHeight;
    targetScoreLabelText->m_Text = "Target:";
    targetScoreLabelText->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
    targetScoreLabelText->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
    targetScoreLabelText->m_Font = g_pResources->getFont();
    targetScoreLabelText->m_ScaleX = fontScale;
    targetScoreLabelText->m_ScaleY = fontScale;
    targetScoreLabelText->m_Color = CColor(0xff, 0xff, 0x30, 0xff);
    AddChild(targetScoreLabelText);

    //- Create target score label (displays target score)
    targetScoreLabel = new CLabel();
    targetScoreLabel->m_X = 80 * fontScale;
    targetScoreLabel->m_Y = uiYPosition + 30 * fontScale;
    targetScoreLabel->m_W = FONT_DESIGN_WIDTH;
    targetScoreLabel->m_H = actualFontHeight;
    targetScoreLabel->m_Text = "0";
    targetScoreLabel->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
    targetScoreLabel->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
    targetScoreLabel->m_Font = g_pResources->getFont();
    targetScoreLabel->m_ScaleX = fontScale;
    targetScoreLabel->m_ScaleY = fontScale;
    AddChild(targetScoreLabel);

    // Create round label text
    roundLabelText = new CLabel();
    roundLabelText->m_X = IwGxGetScreenWidth() - 100 * fontScale;
    roundLabelText->m_Y = uiYPosition + 10 * fontScale;
    roundLabelText->m_W = FONT_DESIGN_WIDTH;
    roundLabelText->m_H = actualFontHeight;
    roundLabelText->m_Text = "Round:";
    roundLabelText->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
    roundLabelText->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
    roundLabelText->m_Font = g_pResources->getFont();
    roundLabelText->m_ScaleX = fontScale;
    roundLabelText->m_ScaleY = fontScale;
    roundLabelText->m_Color = CColor(0xff, 0xff, 0x30, 0xff);
    AddChild(roundLabelText);

    // Create round label
    roundLabel = new CLabel();
    roundLabel->m_X = -30 * fontScale;
    roundLabel->m_Y = uiYPosition + 10 * fontScale;
    roundLabel->m_W = FONT_DESIGN_WIDTH;
    roundLabel->m_H = actualFontHeight;
    roundLabel->m_Text = "0";
    roundLabel->m_AlignHor = IW_2D_FONT_ALIGN_RIGHT;
    roundLabel->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
    roundLabel->m_Font = g_pResources->getFont();
    roundLabel->m_ScaleX = fontScale;
    roundLabel->m_ScaleY = fontScale;
    AddChild(roundLabel);

    // Create timer label text
    timerLabelText = new CLabel();
    timerLabelText->m_X = IwGxGetScreenWidth() - 100 * fontScale;
    timerLabelText->m_Y = uiYPosition + 30 * fontScale;
    timerLabelText->m_W = FONT_DESIGN_WIDTH;
    timerLabelText->m_H = actualFontHeight;
    timerLabelText->m_Text = "Time:";
    timerLabelText->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
    timerLabelText->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
    timerLabelText->m_Font = g_pResources->getFont();
    timerLabelText->m_ScaleX = fontScale;
    timerLabelText->m_ScaleY = fontScale;
    timerLabelText->m_Color = CColor(0xff, 0xff, 0x30, 0xff);
    AddChild(timerLabelText);

    // Create timer label
    timerLabel = new CLabel();
    timerLabel->m_X = -30 * fontScale;
    timerLabel->m_Y = uiYPosition + 30 * fontScale;
    timerLabel->m_W = FONT_DESIGN_WIDTH;
    timerLabel->m_H = actualFontHeight;
    timerLabel->m_Text = "0";
    timerLabel->m_AlignHor = IW_2D_FONT_ALIGN_RIGHT;
    timerLabel->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
    timerLabel->m_Font = g_pResources->getFont();
    timerLabel->m_ScaleX = fontScale;
    timerLabel->m_ScaleY = fontScale;
    AddChild(timerLabel);

    // Create pause menu sprite (docked to top of screen)
    pauseSprite = new CSprite();
    pauseSprite->SetImage(g_pResources->getPauseIcon());
    pauseSprite->m_X = (float)IwGxGetScreenWidth() / 2;
    pauseSprite->m_Y = (float)uiYPosition;
    pauseSprite->m_W = pauseSprite->GetImage()->GetWidth();
    pauseSprite->m_H = pauseSprite->GetImage()->GetHeight();
    pauseSprite->m_AnchorX = 0.5;
    pauseSprite->m_ScaleX = graphicsScale;
    pauseSprite->m_ScaleY = graphicsScale;
    AddChild(pauseSprite);

    // Create target gem sprite
    targetGemSprite = new CSprite();
    targetGemSprite->SetAtlas(g_pResources->getGemAtlas(0));
    targetGemSprite->SetAnimDuration(2);
    targetGemSprite->m_X = (float)IwGxGetScreenWidth() / 2;
    targetGemSprite->m_Y = 0;
    targetGemSprite->m_AnchorX = 0.5;
    targetGemSprite->m_ScaleX = graphicsScale;
    targetGemSprite->m_ScaleY = graphicsScale;
    targetGemSprite->m_IsVisible = false;
    AddChild(targetGemSprite);
}

void Game::postFacebookUpdate()
{
    /*// Post score and round update to Facebook
    if (g_pSocial != 0)
    {
        char str[256];
        snprintf(str, 64, "I just scored %d points on round %d playing Match-3", currentRoundScore, currentRound);
        g_pSocial->PostUpdate(str);
    }*/
}

// Initialise the Info Panel UI (Info panel shows information such as end of round score and round number)
void Game::initInfoPanelUI()
{
    // Create info panel
    infoPanel = new CSprite();
    infoPanel->SetImage(g_pResources->getInfoPanel());
    float panel_w = infoPanel->GetImage()->GetWidth();
    float panel_h = infoPanel->GetImage()->GetHeight();
    infoPanel->m_X = (float)IwGxGetScreenWidth();
    infoPanel->m_Y = (float)IwGxGetScreenHeight() / 2 - (panel_h / 2) * graphicsScale;
    infoPanel->m_W = panel_w;
    infoPanel->m_H = panel_h;
    infoPanel->m_ScaleX = graphicsScale;
    infoPanel->m_ScaleY = graphicsScale;
    AddChild(infoPanel);

    // Create info panel header
    infoPanelTitleLabel = new CLabel();
    infoPanelTitleLabel->m_X = panel_w / 2;
    infoPanelTitleLabel->m_Y = panel_h / 2 - 100,
    infoPanelTitleLabel->m_W = panel_w;
    infoPanelTitleLabel->m_H = panel_h;
    infoPanelTitleLabel->m_Text = "Round Complete",
    infoPanelTitleLabel->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
    infoPanelTitleLabel->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
    infoPanelTitleLabel->m_Font = g_pResources->getFont();
    infoPanelTitleLabel->m_AnchorX = 0.5f;
    infoPanelTitleLabel->m_AnchorY = 0.5f;
    infoPanelTitleLabel->m_ScaleX = fontScale / graphicsScale;
    infoPanelTitleLabel->m_ScaleY = fontScale / graphicsScale;
    infoPanel->AddChild(infoPanelTitleLabel);

    // Create info panel message
    infoPanelMessageLabel = new CLabel();
    infoPanelMessageLabel->m_X = panel_w / 2;
    infoPanelMessageLabel->m_Y = panel_h / 2 + 100,
    infoPanelMessageLabel->m_W = panel_w;
    infoPanelMessageLabel->m_H = panel_h;
    infoPanelMessageLabel->m_Text = "Score: 1000",
    infoPanelMessageLabel->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
    infoPanelMessageLabel->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
    infoPanelMessageLabel->m_Font = g_pResources->getFont();
    infoPanelMessageLabel->m_AnchorX = 0.5f;
    infoPanelMessageLabel->m_AnchorY = 0.5f;
    infoPanelMessageLabel->m_ScaleX = fontScale / graphicsScale;
    infoPanelMessageLabel->m_ScaleY = fontScale / graphicsScale;
    infoPanel->AddChild(infoPanelMessageLabel);

    /*if (g_pSocial != 0)
    {
        // Create Facebook share button
        facebookSprite = new CSprite();
        facebookSprite->SetImage(g_pResources->getFacebook());
        facebookSprite->m_X = infoPanel->GetImage()->GetWidth() / 2;
        facebookSprite->m_Y = infoPanel->GetImage()->GetHeight();
        facebookSprite->m_W = facebookSprite->GetImage()->GetWidth();
        facebookSprite->m_H = facebookSprite->GetImage()->GetHeight();
        facebookSprite->m_AnchorX = 0.5;
        facebookSprite->m_ScaleX = 2;
        facebookSprite->m_ScaleY = 2;
        infoPanel->AddChild(facebookSprite);
    }*/
}

void Game::disableAds()
{
    // Disable ads
    /*g_pAds->Disable();

    // Remove pause menu Ad button
    ((PauseMenu*)g_pSceneManager->Find("pausemenu"))->RemoveNoAdsButton();

    // Move UI to top of screen
    uiYPosition = 0;
    leftPlacard->m_Y = (float)uiYPosition;
    rightPlacard->m_Y = (float)uiYPosition;
    scoreLabelText->m_Y = uiYPosition + 10 * fontScale;
    scoreLabel->m_Y = uiYPosition + 10 * fontScale;
    targetScoreLabelText->m_Y = uiYPosition + 30 * fontScale;
    targetScoreLabel->m_Y = uiYPosition + 30 * fontScale;
    roundLabelText->m_Y = uiYPosition + 10 * fontScale;
    roundLabel->m_Y = uiYPosition + 10 * fontScale;
    timerLabelText->m_Y = uiYPosition + 30 * fontScale;
    timerLabel->m_Y = uiYPosition + 30 * fontScale;
    pauseSprite->m_Y = (float)uiYPosition;

    // Log ads removed event
    if (s3eFlurryAvailable())
        s3eFlurryLogEvent("Ads Removed");*/
}

void Game::purchaseNoAds()
{
    // Create store and purchase no ads in-app purchase
    /*if (g_pStore == 0)
    {
        g_pStore = new Store();
        if (g_pStore->Init())
            g_pStore->PurchaseNoAds();
    }
    else
        g_pStore->PurchaseNoAds();*/
}

void Game::Init(int grid_width, int grid_height)
{
    Scene::Init();

    facebookSprite = NULL;
    startRoundTime = START_ROUND_TIME;
    fontScale = (float)IwGxGetScreenWidth() / FONT_DESIGN_WIDTH;
    actualFontHeight = FONT_HEIGHT * fontScale;
    graphicsScale = (float)IwGxGetScreenWidth() / GRAPHIC_DESIGN_WIDTH;
    currentRound = 1;
    currentRoundScore = 0;
    currentRoundTime = 0;
    targetRoundScore = 0;
    targetGem = 1;
    gridTouchesX[0] = -1;
    gridTouchesX[1] = -1;
    gridTouchesY[0] = -1;
    gridTouchesY[1] = -1;
    gameState = paused;
    infoPanelVisible = false;
    /*if (g_pAds->IsEnabled())
        uiYPosition = 80;
    else*/
    uiYPosition = 0;

    // Initialise UI
    initUI();

    // Create grid
    gemsGrid = new Grid(this, grid_width, grid_height, (int)(GRID_OFFSET_X * graphicsScale), (int)(GRID_OFFSET_Y * graphicsScale), IwGxGetScreenWidth());

    // initialise info panel UI
    initInfoPanelUI();

    // Create selector
    selector = new CSprite();
    selector->m_X = 0;
    selector->m_Y = 0;
    selector->m_AnchorX = 0.5;
    selector->m_AnchorY = 0.5;
    selector->SetImage(g_pResources->getSelector());
    selector->m_W = selector->GetImage()->GetWidth();
    selector->m_H = selector->GetImage()->GetHeight();
    selector->m_IsVisible = false;
    selector->m_ScaleX = graphicsScale;
    selector->m_ScaleY = graphicsScale;
    AddChild(selector);
    g_pTweener->Tween(1.0f,
                    MIRROR,
                    FLOAT, &selector->m_Alpha, 0.3f,
                    EASING, Ease::sineInOut,
                    END);

    // Create explosion manager
    g_pExplosionManager = new ExplosionManager();


    // Set initial target gem
    setTargetGem(rand() % MAX_GEM_TYPES);

}

