#if !defined(__ASTEROID_H__)
#define __ASTEROID_H__

class Asteroid : public GameObject
{
public:


private:

public:
	Asteroid();
	~Asteroid();

	void Init(float posX, float posY, float speedYRatio = 1.0f);
	void Cleanup();
	void Update(float gameSpeed = 0.0f);
};

#endif  // __ASTEROID_H__

