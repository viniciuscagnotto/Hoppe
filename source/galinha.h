#ifndef __GALINHA_H__
#define __GALINHA_H__

class Galinha : public GameObject
{
public:
	enum EAnimationStates{
		kAnimationStates_Run = 0,
		kAnimationStates_Run_Catarro,
		kAnimationStates_Damage,
		kAnimationStates_Apaixonada,

		kAnimationStates_Count
	};

private:
	

public:
	Galinha();
	~Galinha();

	void Init();
	void Cleanup();
	void Update();
};

#endif  // __GALINHA_H__

