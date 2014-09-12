#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__

class Gameplay : public Scene
{
public:
	static const uint s_kDefaultLines = 5;
	static const uint s_kMaxLines = 8;
	static uint s_numLines;
	static bool s_paused;
	static int s_actualScore;
	static bool s_gameOver;

	struct SLine{
		SquareObject *pLeft;
		SquareObject *pRight;
		bool isBusy;

		SLine(){
			pLeft = new SquareObject(true);
			pRight = new SquareObject(false);

			pLeft->SetReceiver(pRight);
			pRight->SetReceiver(pLeft);

			isBusy = false;
		};

		void ChangeShooter(){
			bool rightValue = pRight->IsShooter();
			pLeft->SetIsShooter(rightValue);
			pRight->SetIsShooter(!rightValue);
		};

		bool IsSwitching(){
			return (pLeft->IsSwitching() || pRight->IsSwitching());
		};

		void Update(float deltaTime){
			pLeft->Update(deltaTime);
			pRight->Update(deltaTime);
		};

		void Shoot(float speed){
			if (pLeft->IsShooter()){
				pLeft->Shoot(speed);
			}else{
				pRight->Shoot(-speed);
			}
		};

		void CheckTap(float x, float y){
			pLeft->CheckTap(x, y);
			pRight->CheckTap(x, y);
		};

		void RandomSwitch(){
			if (L_Random() >= 0.5f){
				if (pLeft->CanSwitch(GetShooter()))
					pLeft->SetToSwitch();
				return;
			}

			if (pLeft->CanSwitch(GetShooter()))
				pRight->SetToSwitch();
		};

		SquareObject *GetShooter(){
			if (pLeft->IsShooter())
				return pLeft;
			return pRight;
		};
	};

	
private:
	EasyArray<SLine*, s_kMaxLines> m_lines;
	CNode *m_pCirclesContainer;

	float m_bottomHudHeight;
	float m_topAdsHeight;

	TimerManager m_timers;

	const int m_kMaxEquals = 2;

	const float m_kStartingCircleSpeed = 4.0f;
	const float m_kMaxCircleSpeed = 20.0f;
	const float m_kCircleSpeedRange = 1.0f;
	float m_circleSpeed;
	
	const float m_kStartingShootRate = 3.5f;
	const float m_kMinShootRate = 0.75f;
	const float m_kShootRateRange = 0.4f;
	float m_shootRate;
	
	const float m_kStartingSwitchRate = 6.2f;
	const float m_kMinSwitchRate = 3.0f;
	const float m_kSwitchRateRange = 0.2f;
	float m_switchRate;

	const float m_kStartingDoubleShotChance = 0.0f;
	const float m_kMaxDoubleShotChance = 1.0f;
	const float m_kDoubleShotChanceRange = 0.015f;
	float m_doubleShotChance;

	//Bottom HUD
	SpriteObject *m_pBottomHUD;
	SpriteObject *m_pPauseBtn;

	//Pause Stuff
	SpriteObject *m_pResumeBtn;
	SpriteObject *m_pExitBtn;
	SpriteObject *m_pAlphaLayer;
	SpriteObject *m_pPauseScreen;

	SpriteObject *m_pSound;
	SpriteObject *m_pOn;
	SpriteObject *m_pOff;


public:
	Gameplay();
	~Gameplay();

	void Init();
	void Cleanup();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	void HandleTouch();

	void Pause(bool pause);

	static void Shoot(Timer* pTimer, void* pUserData);
	void RandomShoot();

	static void Switch(Timer* pTimer, void* pUserData);
	void RandomSwitch();

	static void ResetVariables() { s_actualScore = 0; s_paused = false; s_gameOver = false;};
};

#endif  // __GAMEPLAY_H__

