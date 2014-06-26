#if !defined(__OPTIONS_H__)
#define __OPTIONS_H__


class Options : public Scene
{
public:


private:
	

public:
	Options();
	~Options();

	void Init();
	void Cleanup();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	void HandleTouch();
};

#endif  // __OPTIONS_H__

