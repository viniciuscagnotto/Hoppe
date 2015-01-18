#include "header.h"

const float Line::s_kMinSlideSpeed = 0.03f;
const float Line::s_kMaxSlideSpeed = 0.09f;
const float Line::s_kMinFadeSpeed = 0.01f;
const float Line::s_kMaxFadeSpeed = 0.8f;

Line::Line():m_pText(0),
m_state(0),
m_posY(0.0f),
m_slideSpeed(0.0f),
m_fadeSpeed(0.0f){
	for (uint i = 0; i < s_kMaxPaintsEachSide; i++){
		m_leftPaints[i] = 0;
		m_rightPaints[i] = 0;
	}
}

Line::~Line(){

}

void Line::Update(float deltaTime){
	if (!IsActive())
		return;
	
	if (IsFading()){
		m_pText->AddAlpha(-m_fadeSpeed);
		if (m_pText->GetAlpha() <= 0){
			m_pText->SetAlpha(0.0f);
		
			SetFading(false);
			SetSlidingOut(true);

			//CHECK IF HAS COLOR
			//IF TRUE, GAME OVER
			//ELSE SLIDE OUT
		}

		return;
	}

	if (IsSlidingIn()){
		float leftPaintStartX = -m_leftPaints[0]->GetWidth(true);
		float rightPaintStartX = Iw2DGetSurfaceWidth() + m_rightPaints[0]->GetWidth(true);

		float leftPaintFinalX = m_leftPaints[0]->GetWidth(true);
		float rightPaintFinalX = Iw2DGetSurfaceWidth() - m_rightPaints[0]->GetWidth(true);
		float textFinalScale = Game::s_scaleFactor;

		if (m_pText->GetSprite()->m_ScaleX < textFinalScale){
			float newScale = m_pText->GetSprite()->m_ScaleX + m_slideSpeed;
			m_pText->SetScale(newScale, newScale);

			float paintSpeed = fabsf(leftPaintStartX - leftPaintFinalX) / (textFinalScale / m_slideSpeed);
			m_leftPaints[0]->SetPosition(m_leftPaints[0]->GetSprite()->m_X + paintSpeed, m_posY);
			m_rightPaints[0]->SetPosition(m_rightPaints[0]->GetSprite()->m_X - paintSpeed, m_posY);

			if (m_pText->GetSprite()->m_ScaleX >= textFinalScale){
				m_pText->SetScale(textFinalScale, textFinalScale);
				m_leftPaints[0]->SetPosition(leftPaintFinalX, m_posY);
				m_rightPaints[0]->SetPosition(rightPaintFinalX, m_posY);
				SetSlidingIn(false);
				SetFading(true);
			}
		}

		return;
	}

	if (IsSlidingOut()){


		return;
	}

}

void Line::GenerateRandomLine(){
	Clean();

	GameObject::ETextType textType = (GameObject::ETextType)L_RandomInt(0, GameObject::kText_Count - 1);
	GameObject::EColor textColor = (GameObject::EColor)L_RandomInt(0, Gameplay::s_colorsLimit);
	GameObject::EColor color = (GameObject::EColor)L_RandomInt(0, Gameplay::s_colorsLimit);

	m_pText = new Text(textType, textColor, color);
	m_pText->SetPosition(Iw2DGetSurfaceWidth() * 0.5f, m_posY);
	m_pText->AddTo(Gameplay::s_pSelf);
	m_pText->SetScale(0.0f, 0.0f);

	bool hasCorrectPaint = (L_Random() > 0.2f);

	GameObject::EColor color1 = GameObject::kColor_Count;
	GameObject::EColor color2 = GameObject::kColor_Count;
	GameObject::EColor color3 = GameObject::kColor_Count;
	GameObject::EColor color4 = GameObject::kColor_Count;
	if (hasCorrectPaint){
		

	}else{


	}



	GameObject::EColor leftColor = textColor;
	GameObject::EColor rightColor = color;
	if (L_Random() > 0.5f){
		leftColor = color;
		rightColor = textColor;
	}

	m_leftPaints[0] = new Paint(leftColor);
	m_leftPaints[0]->SetPosition(-m_leftPaints[0]->GetWidth(true), m_posY);
	m_leftPaints[0]->AddTo(Gameplay::s_pSelf);

	m_rightPaints[0] = new Paint(rightColor);
	m_rightPaints[0]->SetPosition(Iw2DGetSurfaceWidth() + m_rightPaints[0]->GetWidth(true), m_posY);
	m_rightPaints[0]->AddTo(Gameplay::s_pSelf);

	m_slideSpeed = s_kMinSlideSpeed;
	m_fadeSpeed = s_kMinFadeSpeed;

	SetActive(true);
	SetSlidingIn(true);
}

GameObject::EColor Line::ChooseColor(GameObject::EColor color1, GameObject::EColor color2, GameObject::EColor color3, GameObject::EColor color4){
	GameObject::EColor color = (GameObject::EColor)L_RandomInt(0, Gameplay::s_colorsLimit);
	while (color == color1 || color == color2 || color == color3 || color == color4)
		color = (GameObject::EColor)L_RandomInt(0, Gameplay::s_colorsLimit);
	return color;
}

void Line::Clean(){
	if (m_pText)
		delete m_pText;
	m_pText = 0;

	for (uint i = 0; i < s_kMaxPaintsEachSide; i++){
		if (m_leftPaints[i])
			delete m_leftPaints[i];
		m_leftPaints[i] = 0;

		if (m_rightPaints[i])
			delete m_rightPaints[i];
		m_rightPaints[i] = 0;
	}
}