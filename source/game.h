#if !defined(__GAME_H__)
#define __GAME_H__


class Game : public Scene
{
public:
	static const uint s_kGameInitialSpeed = 2.0f;
	static const uint s_kMaxVortex = 1;

private:
	ParallaxManager m_background;
	ParallaxManager m_backEarth;
	ParallaxManager m_backSatellite;

	float m_gameSpeed;

	EasyArray<Vortex, s_kMaxVortex> m_arrayVortex;
	uint m_numVortex;
	Player m_player;

	CNode *m_pObjectsContainer;

public:
	Game();
    ~Game();

    void Init();
	void Cleanup();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	void HandleTouch();

	void CleanupVortexList();
	void UpdateVortexList();
};

#endif  // __GAME_H__

