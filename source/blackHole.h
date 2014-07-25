#if !defined(__BLACK_HOLE_H__)
#define __BLACK_HOLE_H__

class BlackHole : public GameObject
{
public:


private:

public:
	BlackHole();
	~BlackHole();

	void Init(float posX, float posY, float speedYRatio = 1.0f);
	void Cleanup();
	void Update(float gameSpeed = 0.0f);
};

#endif  // __BLACK_HOLE_H__

