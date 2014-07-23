#if !defined(__STAR_H__)
#define __STAR_H__

class Star : public GameObject
{
public:


private:

public:
	Star();
	~Star();

	void Init(float posX, float posY, float speedYRatio = 1.0f);
	void Cleanup();
	void Update(float gameSpeed = 0.0f);
};

#endif  // __STAR_H__

