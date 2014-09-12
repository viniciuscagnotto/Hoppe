#ifndef __OPTIONS_H__
#define __OPTIONS_H__

class Options : public Scene
{
public:


private:
	SpriteObject *m_pBack;
	SpriteObject *m_pTitle;

	SpriteObject *m_pSound;
	SpriteObject *m_pOn;
	SpriteObject *m_pOff;

	SpriteObject *m_pWhiteCircle;
	SpriteObject *m_pBlackCircle;
	

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

