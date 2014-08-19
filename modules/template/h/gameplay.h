#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__

#define FONT_DESIGN_WIDTH       320
#define FONT_HEIGHT             15
#define METER					10

class Gameplay : public Scene
{
public:
	static const uint s_kInitialSpeed = 2;
	static const uint s_kMaxSpeed = 12;
	static const uint s_kMaxGameObjects = 64;
	static const uint s_kMaxVortex = 4;

private:
	//TriggersManager m_triggers;

	ParallaxManager m_background;
	ParallaxManager m_backEarth;
	ParallaxManager m_backSatellite;

	float m_gameSpeedIncrease;
	float m_gameSpeed;
	float m_distance;
	bool m_paused;

	//EasyArray<GameObject *, s_kMaxGameObjects> m_gameObjects;
	//uint m_numGameObjects;
	
	CNode *m_pObjectsContainer;


	CLabel *m_distanceText;

public:
	Gameplay();
	~Gameplay();

    void Init();
	void Cleanup();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	void HandleTouch();

	void ProcessTriggers();
	void CleanupGameObjects();
	void UpdateGameObjects();

	int GetDistance() { return (int)floorf(m_distance / METER); };
};

#endif  // __GAMEPLAY_H__

