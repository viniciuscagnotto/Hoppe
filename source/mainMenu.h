#ifndef __MAINEMENU_H__
#define __MAINEMENU_H__

class MainMenu : public Scene
{
public:


private:
	SpriteObject* m_pStartGame;
	
	SpriteObject* m_pFazendeiroRun1;
	SpriteObject* m_pFazendeiroRun2;
	SpriteObject* m_pFazendeiroRun3;
	SpriteObject* m_pFazendeiroRun4;
	SpriteObject* m_pFazendeiroRun5;

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

