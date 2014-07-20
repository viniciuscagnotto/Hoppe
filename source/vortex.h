#if !defined(__VORTEX_H__)
#define __VORTEX_H__

class Vortex : public GameObject
{
public:


private:


public:
	Vortex();
	~Vortex();

	void Init(float posX, float posY);
	void Cleanup();
	void Update();
};

#endif  // __VORTEX_H__

