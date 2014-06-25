#if !defined(__MAINEMENU_H__)
#define __MAINEMENU_H__

class MainMenu : public Scene
{
protected:
   

public:
	MainMenu();
    ~MainMenu();

    void Init();
	void Cleanup();
    void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
    void Render();

};

#endif  // __MAINEMENU_H__

