#if !defined(__GAME_H__)
#define __GAME_H__

// Constants that change the games behaviour
#define START_ROUND_TIME 110
#define ROUND_TIME_STEP 10
#define START_TARGET_SCORE 600
#define TARGET_SCORE_STEP 100

// Constants that are used to fit the game to different screen sizes
#define FONT_HEIGHT 15
#define FONT_DESIGN_WIDTH 320
#define GRAPHIC_DESIGN_WIDTH 768

enum eGameState
{
    paused = 0, // The game is paused
    waitingFirstGem, // The game is waiting for first gem selection
    waitingSecondGem, // The game is waiting for second gem selection
    thinking, // The game is analysing the move and removing blocks / adding new blocks
    gemsFalling, // The game is waiting for gems to stop falling
    roundOver, // The game round is over
};

class Game : public Scene
{
protected:
    Grid*               gemsGrid;                       // Game grid
    int                 currentRound;                   // Current tound that is in play
    int                 currentRoundScore;              // Current round score
    float               currentRoundTime;               // Current round time (this counts downwards)
    int                 targetRoundScore;               // Target round score (player must beat this to win round)
    int                 targetGem;                      // Current target gem to destroy to gain bonus points
    int                 gridTouchesX[2];                // First and second grid touch pos on x-axis
    int                 gridTouchesY[2];                // First and second grid touch pos on y-axis
    eGameState          gameState;                      // Current game state
    eGameState          oldGameState;                   // Previous game state
    bool                infoPanelVisible;               // Info panel visible state

    int                 startRoundTime;                 // Players time limit for first round

    float               fontScale;                      // Font is correct size on 320 wide screen so we scale to match native screen size
    float               actualFontHeight;               // The actual pixel height of the font
    float               graphicsScale;                  // Graphics are designed for 768 wide screen so we scale to native screen size

    // UI components
    CSprite*            gridSprite;
    CSprite*            leftPlacard;
    CSprite*            rightPlacard;
    CLabel*             scoreLabelText;
    CLabel*             scoreLabel;
    CLabel*             targetScoreLabelText;
    CLabel*             targetScoreLabel;
    CSprite*            targetGemSprite;
    CLabel*             roundLabelText;
    CLabel*             roundLabel;
    CLabel*             timerLabelText;
    CLabel*             timerLabel;
    CSprite*            pauseSprite;
    CSprite*            facebookSprite;
    CSprite*            infoPanel;
    CLabel*             infoPanelTitleLabel;
    CLabel*             infoPanelMessageLabel;
    CSprite*            selector;
    int                 uiYPosition;

public:
    Grid*               getGrid()               { return gemsGrid; }
    eGameState          getGameState() const    { return gameState; }
    int*                getGridTouchesX()       { return gridTouchesX; }
    int*                getGridTouchesY()       { return gridTouchesY; }
    void                setTargetGem(int type);
    float               getGraphicsScale()      { return graphicsScale; }
    float               getFontScale()          { return fontScale; }

private:
    void            initUI();
public:
    Game() : gemsGrid(0) {}
    ~Game();

    // initialise the game
    void            Init(int grid_width, int grid_height);

    // Update the game
    void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

    // Render the game
    void            Render();

    void            switchToScene(const char* scene_name);
    static void     gemSwapBackFinished(Timer* timer, void* userData);
    static void     startGemsFalling(Timer* timer, void* userData);
    static void     gemSwapFinished(Timer* timer, void* userData);
    static void     chooseTargetGem(Timer* timer, void* userData);
    void            removeGem(Gem* gem);
    void            changeGameState(eGameState game_state);
    void            addToRoundScore(int score, int gem_type);
    void            showInfoPanel(const char* title, const char* info);
    void            hideInfoPanel();
    void            pauseGame();
    void            resumeGame();
    void            initRound();
    void            endOfRound();
    void            newGame();
    void            postFacebookUpdate();
    void            initInfoPanelUI();
    void            disableAds();
    void            purchaseNoAds();
};

#endif  // __GAME_H__

