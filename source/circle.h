#ifndef __CIRCLE_H__
#define __CIRCLE_H__

class Circle : public GameObject
{
public:
	

private:


public:
	Circle(EGameObjectColor color);
	~Circle();

	void Init();
	void Cleanup();
	void Update();
};

#endif  // __CIRCLE_H__

