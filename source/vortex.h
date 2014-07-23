#if !defined(__VORTEX_H__)
#define __VORTEX_H__

class Vortex : public GameObject
{
public:


private:
	float m_alphaDeduction;

public:
	Vortex();
	~Vortex();

	void Init(float posX, float posY, float speedYRatio = 1.0f);
	void Cleanup();
	void Update(float gameSpeed = 0.0f);
};

#endif  // __VORTEX_H__

