#ifndef __OPTIONS_H__
#define __OPTIONS_H__

class Options : public Scene
{
public:


private:
	SpriteObject *m_pBack;
	SpriteObject *m_pTitle;

	SpriteObject *m_pSound;
	SpriteObject *m_pSoundOn;
	SpriteObject *m_pSoundOff;
	//SpriteObject *m_pSoundWhiteCircle;
	//SpriteObject *m_pSoundBlackCircle;

	SpriteObject *m_pTutorial;
	SpriteObject *m_pTutorialOn;
	SpriteObject *m_pTutorialOff;
	//SpriteObject *m_pTutorialWhiteCircle;
	//SpriteObject *m_pTutorialBlackCircle;
	

public:
	Options();
	~Options();

	void Init();
	void Cleanup();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	void HandleTouch();
};

#endif  // __OPTIONS_H__

