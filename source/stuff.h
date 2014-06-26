#if !defined(__STUFF_H__)
#define __STUFF_H__


class Stuff : public Scene
{
public:


private:


public:
	Stuff();
	~Stuff();

	void Init();
	void Cleanup();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	void HandleTouch();
};

#endif  // __STUFF_H__

