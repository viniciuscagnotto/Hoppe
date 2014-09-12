#ifndef __TUTORIAL_H__
#define __TUTORIAL_H__

class Tutorial : public Scene
{
public:


private:
	SpriteObject *m_pTutorial;

public:
	Tutorial();
	~Tutorial();

	void Init();
	void Cleanup();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	void HandleTouch();
};

#endif  // __TUTORIAL_H__

