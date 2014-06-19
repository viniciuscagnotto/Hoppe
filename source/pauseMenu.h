#if !defined(__PAUSEMENU_H__)
#define __PAUSEMENU_H__

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

    void Init();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
    void Render();
    void RemoveNoAdsButton();

	static void ContinueGame(CTween* pTween);
    static void NewGame(CTween* pTween);
    static void NoAds(CTween* pTween);
};

#endif  // __PAUSEMENU_H__

