#if !defined(__ITEMS_H__)
#define __ITEMS_H__


class Items : public Scene
{
public:


private:


public:
	Items();
	~Items();

	void Init();
	void Cleanup();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	void HandleTouch();
};

#endif  // __ITEMS_H__

