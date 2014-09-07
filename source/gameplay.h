#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__

#define SPRITE_SIZE 10
#define BOTTOM_HUD_HEIGHT 7
#define TOP_ADS_HEIGHT 15
#define SQUARE_WIDTH 13
#define SPACEMENT 2

class Gameplay : public Scene
{
public:
	static const uint s_kDefaultLines = 5;
	static const uint s_kMaxLines = 8;
	static uint s_numLines;
	static bool s_isPaused;

	struct SLine{
		SquareObject *pLeft;
		SquareObject *pRight;
		bool isBusy;

		SLine(){
			pLeft = new SquareObject(true);
			pRight = new SquareObject(false);
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

		void Update(){
			pLeft->Update();
			pRight->Update();
		};

		void Shoot(float speed){
			if (pLeft->IsShooter()){
				pLeft->Shoot(speed, pRight);
			}else{
				pRight->Shoot(-speed, pLeft);
			}
		};
	};

private:
	EasyArray<SLine*, s_kMaxLines> m_lines;
	CNode *m_pCirclesContainer;

	float m_bottomHudHeight;
	float m_topAdsHeight;

	uint m_points;

public:
	Gameplay();
	~Gameplay();

	void Init();
	void Cleanup();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	void HandleTouch();

	void Pause();
};

#endif  // __GAMEPLAY_H__

