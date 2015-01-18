#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__

#define BOTTOM_HUD_HEIGHT 10

class Gameplay : public Scene
{
public:
	static Gameplay *s_pSelf;

	static const int s_kStartingLines = 1;
	static const int s_kMaxLines = 5;
	static const int s_kStartColorsLimit = GameObject::kColor_Yellow;

	static bool s_isShowingTutorial;
	static bool s_paused;
	static bool s_canTap;
	static int s_paintsEachSide;
	static int s_colorsLimit;

private:
	EasyArray<Line, s_kMaxLines> m_lines;
	uint m_numActiveLines;

	TimerManager m_timers;


public:
	Gameplay();
	~Gameplay();

	void Init();
	void Cleanup();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	void HandleTouch();

	static void ShowLine(Timer* pTimer, void* pUserData);
	void SlideLineIn();

	void CheckNextLevel();
	void Pause(bool pause);
};

#endif  // __GAMEPLAY_H__

