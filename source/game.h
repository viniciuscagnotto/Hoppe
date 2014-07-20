#if !defined(__GAME_H__)
#define __GAME_H__


class Game : public Scene
{
public:
	static const int s_kMaxVortex = 8;

private:
	ParallaxManager m_background;
	ParallaxManager m_backEarth;
	ParallaxManager m_backSatellite;

	Vortex* m_vortexList[s_kMaxVortex];
	unsigned int m_numVortex;
	Player m_player;

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

