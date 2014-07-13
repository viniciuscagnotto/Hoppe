#if !defined(__STORE_H__)
#define __STORE_H__


class Store : public Scene
{
public:


private:


public:
	Store();
	~Store();

	void Init();
	void Cleanup();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	void HandleTouch();
};

#endif  // __STORE_H__

