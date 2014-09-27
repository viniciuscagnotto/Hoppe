#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

class GameOver : public Scene
{
public:


private:
	SpriteObject *m_pFacebook;
	SpriteObject *m_pMainMenu;
	SpriteObject *m_pPlayAgain;

	SpriteObject *m_pBestScoreTitle;
	SpriteObject *m_pYourScoreTitle;

	CLabel *m_pBestScore;
	CLabel *m_pYourScore;

	int m_actualScore;

public:
	GameOver();
	~GameOver();

	void Init();
	void Cleanup();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	void HandleTouch();
};

#endif  // __GAME_OVER_H__

