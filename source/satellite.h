#if !defined(__SATELLITE_H__)
#define __SATELLITE_H__

class Satellite : public GameObject
{
public:


private:

public:
	Satellite();
	~Satellite();

	void Init(float posX, float posY, float speedYRatio = 1.0f);
	void Cleanup();
	void Update(float gameSpeed = 0.0f);
};

#endif  // __SATELLITE_H__

