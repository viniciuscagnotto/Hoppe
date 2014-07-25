#if !defined(__GAME_H__)
#define __GAME_H__


#define FONT_DESIGN_WIDTH       320
#define FONT_HEIGHT             15

#define METER					10



class Game : public Scene
{
public:
	static const uint s_kInitialSpeed = 2;
	static const uint s_kMaxSpeed = 10;
	static const uint s_kMaxGameObjects = 64;
	static const uint s_kMaxVortex = 1;

private:
	TriggersManager m_triggers;

	ParallaxManager m_background;
	ParallaxManager m_backEarth;
	ParallaxManager m_backSatellite;

	float m_gameSpeedIncrease;
	float m_gameSpeed;
	float m_distance;
	bool m_paused;

	EasyArray<GameObject *, s_kMaxGameObjects> m_gameObjects;
	uint m_numGameObjects;
	uint m_numVortex;
	//Player *m_pPlayer;

	CNode *m_pObjectsContainer;


	CLabel *m_distanceText;

public:
	Game();
    ~Game();

    void Init();
	void Cleanup();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	void HandleTouch();

	void CleanupGameObjects();
	void UpdateGameObjects();
};

#endif  // __GAME_H__

