#ifndef __IAP_H__
#define __IAP_H__

class IAP : public Scene
{
public:


private:


public:
	IAP();
	~IAP();

	void Init();
	void Cleanup();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	void HandleTouch();
};

#endif  // __IAP_H__

