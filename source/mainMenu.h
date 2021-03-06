#ifndef __MAINEMENU_H__
#define __MAINEMENU_H__

class MainMenu : public Scene
{
public:


private:
	SpriteObject* m_pPlay;
	SpriteObject* m_pLogo;
	SpriteObject* m_pSettings;
	CLabel *m_pBestScore;

public:
	MainMenu();
    ~MainMenu();

    void Init();
	void Cleanup();
    void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
    void Render();
	void HandleTouch();

};

#endif  // __MAINEMENU_H__

