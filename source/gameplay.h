#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__

class Gameplay : public Scene
{
public:

private:
	ParallaxManager m_background;
	
public:
	Gameplay();
	~Gameplay();

    void Init();
	void Cleanup();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	void HandleTouch();

};

#endif  // __GAMEPLAY_H__

