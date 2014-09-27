#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__

//#define EXTRA_CIRCLE_DIM 3.5f
#define EXTRA_SQUARE_DIM 3.5f 
#define MAX_SCORE 999999999
#define POINTS_PER_TAP 100

class Gameplay : public Scene
{
public:
	static const uint s_kDefaultLines = 5;
	static const uint s_kMaxLines = 8;
	static const int s_kMinSquaresShooting = 2;
	static const int s_kCircleSpeed = 5;

	static const int s_kTapsToLevel2 = 2;
	static const int s_kTapsToLevel3 = 5;
	static const int s_kTapsToLevel4 = 9;

	static uint s_numLines;
	static bool s_paused;
	static int s_correctTaps;
	static bool s_newSquare;
	static int s_actualScore;
	static bool s_gameOver;
	static bool s_canTap;
	static bool s_isShowingTutorial;
	
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

		void Shoot(float speed, bool front = true){
			if (pLeft->IsShooter()){
				pLeft->Shoot(speed, front);
			}else{
				pRight->Shoot(-speed, front);
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

		void SwitchBoth(){
			pLeft->SetToSwitch();
			pRight->SetToSwitch();
		};

		void SlideIn(){
			pLeft->SetToSlideIn();
			pRight->SetToSlideIn();
		}

		void SetAllCirclesToFade(){
			pLeft->SetAllCirclesToFade();
			pRight->SetAllCirclesToFade();
		}

		SquareObject *GetShooter(){
			if (pLeft->IsShooter())
				return pLeft;
			return pRight;
		};
	};

	
private:
	EasyArray<SLine*, s_kMaxLines> m_lines;
	CNode *m_pCirclesContainer;
	TimerManager m_timers;

	float m_bottomHudHeight;
	float m_topAdsHeight;

	float m_circleSpeed;
	int m_numSquaresShooting;
	
	CLabel *m_pYourScore;

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
	SpriteObject *m_pOnText;
	SpriteObject *m_pOffText;

	//Tutorial
	SpriteObject *m_pTutorial;
	SpriteObject *m_pArrow;
	float m_arrowStartX;
	float m_arrowEndX;
	bool m_isAdvancingArrow;
	bool m_isRetreatingArrow;
	float m_arrowSpeed;

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
	void RandomSwitch();
	void CheckNextLevel();
	void SetAllCirclesToFade();
	void ShowTutorial();
	void RemoveTutorial();

	static void ResetVariables() { s_actualScore = 0; s_correctTaps = 0; s_paused = false; s_gameOver = false; s_newSquare = false; };

	void AdvanceArrow();
	void RetreatArrow();
};

#endif  // __GAMEPLAY_H__

