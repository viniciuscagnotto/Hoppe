#if !defined(__GAME_H__)
#define __GAME_H__


class Game : public Scene
{
public:


private:
	SpriteObject* m_pStar;

public:
	Game();
    ~Game();

    void Init();
	void Cleanup();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	void HandleTouch();
};

#endif  // __GAME_H__

