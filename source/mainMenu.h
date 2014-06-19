#if !defined(__MAINEMENU_H__)
#define __MAINEMENU_H__

class MainMenu : public Scene
{
protected:
    // UI components
    CSprite*    playButton;
    CSprite*    playText;

public:
    MainMenu() {}
    ~MainMenu();

    void Init();
    void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
    void Render();
    static void startGame(CTween* pTween);

};

#endif  // __MAINEMENU_H__

