#if !defined(__COMET_H__)
#define __COMET_H__

class Comet : public GameObject
{
public:


private:

public:
	Comet();
	~Comet();

	void Init(float posX, float posY, float speedYRatio = 1.5f);
	void Cleanup();
	void Update(float gameSpeed = 0.0f);
};

#endif  // __COMET_H__

