#ifndef __CUSTOMIZE_H__
#define __CUSTOMIZE_H__

class Customize : public Scene
{
public:


private:


public:
	Customize();
	~Customize();

	void Init();
	void Cleanup();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	void HandleTouch();
};

#endif  // __CUSTOMIZE_H__

