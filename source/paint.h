#ifndef __PAINT_H__
#define __PAINT_H__

//#define DEFAULT_PAINT_WIDTH 96

class Paint : public GameObject
{
public:


private:


public:
	Paint(EColor color);
	~Paint();

	void Init();
	void Cleanup();
	void Update(float deltaTime);
};

#endif  // __PAINT_H__

