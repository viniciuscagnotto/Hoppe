#if !defined(__GET_STARS_H__)
#define __GET_STARS_H__


class GetStars : public Scene
{
public:


private:


public:
	GetStars();
	~GetStars();

	void Init();
	void Cleanup();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	void HandleTouch();
};

#endif  // __GET_STARS_H__

