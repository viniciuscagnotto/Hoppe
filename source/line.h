#ifndef __LINE_H__
#define __LINE_H__

#define kLine_Active		(1<<0)
#define kLine_Tappable		(1<<1)
#define kLine_SlidingIn		(1<<2)
#define kLine_SlidingOut	(1<<3)
#define kLine_Fading		(1<<4)

class Line
{
public:
	static const int s_kMaxPaintsEachSide = 2;

	static const float s_kMinSlideSpeed;
	static const float s_kMaxSlideSpeed;
	static const float s_kMinFadeSpeed;
	static const float s_kMaxFadeSpeed;

private:
	Text *m_pText;
	EasyArray<Paint *, s_kMaxPaintsEachSide> m_leftPaints;
	EasyArray<Paint *, s_kMaxPaintsEachSide> m_rightPaints;

	int m_state;
	float m_posY;

	float m_slideSpeed;
	float m_fadeSpeed;

public:
	Line();
	~Line();

	void Update(float deltaTime = 0.0f);
	void Clean();

	void GenerateRandomLine();
	GameObject::EColor ChooseColor(GameObject::EColor color1, GameObject::EColor color2, GameObject::EColor color3, GameObject::EColor color4 = GameObject::kColor_Count);

	bool IsActive() { return L_GetBitState(m_state, kLine_Active); };
	void SetActive(bool active){ L_SetBitState(&m_state, kLine_Active, active); };
	bool IsTappable() { return L_GetBitState(m_state, kLine_Tappable); };
	void SetTappable(bool tappable) { L_SetBitState(&m_state, kLine_Tappable, tappable); };
	bool IsSlidingIn() { return L_GetBitState(m_state, kLine_SlidingIn); };
	void SetSlidingIn(bool slidingIn) { L_SetBitState(&m_state, kLine_SlidingIn, slidingIn); };
	bool IsSlidingOut() { return L_GetBitState(m_state, kLine_SlidingOut); };
	void SetSlidingOut(bool slidingOut) { L_SetBitState(&m_state, kLine_SlidingOut, slidingOut); };
	bool IsFading() { return L_GetBitState(m_state, kLine_Fading); };
	void SetFading(bool fading) { L_SetBitState(&m_state, kLine_Fading, fading); };
	
	void SetPosY(float posY){ m_posY = posY; };
};

#endif  // __LINE_H__

