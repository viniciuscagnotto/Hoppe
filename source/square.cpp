#include "header.h"

//- Square ------------------------------------------------------------
Square::Square(GameObject::EGameObjectColor color) :GameObject(kGameObjectType_Square)
{
	m_color = color;
	Init();
}

Square::~Square()
{
	Cleanup();
}

void Square::Init()
{
	Game::EGameGraphics gameGraphics = Game::kGameGraphics_Entity_BlackSquare;
	if (m_color == kGameObjectColor_White)
		gameGraphics = Game::kGameGraphics_Entity_WhiteSquare;

	GameObject::Init(gameGraphics, 0, 0);

	for (uint i = 0; i < s_kMaxCircles; i++)
		m_circles[i] = new Circle(m_color);
}

void Square::Cleanup()
{
	for (uint i = 0; i < s_kMaxCircles; i++){
		delete m_circles[i]; m_circles[i] = 0;
	}

	GameObject::Cleanup();
}

void Square::Update()
{
	GameObject::Update();

	for (uint i = 0; i < s_kMaxCircles; i++){
		if (!m_circles[i]->IsActive())
			continue;

		if (m_circles[i]->IsTapped()){
			if (m_circles[i]->GetColor() == m_circles[i]->GetReceiver()->GetFrontSquare()->GetColor()){
				float circleScale = m_circles[i]->GetSprite()->m_ScaleX;
				Gameplay::s_isPaused = true;
				g_pTweener->Tween(2.0f, FLOAT, &m_circles[i]->GetSprite()->m_ScaleX, circleScale + 1.5f,
										FLOAT, &m_circles[i]->GetSprite()->m_ScaleY, circleScale + 1.5f,
										ONCOMPLETE, Square::OnGameOver, END);
				return;
			}else{
				m_circles[i]->AddAlpha(-0.05f);
				
				float circleScale = m_circles[i]->GetSprite()->m_ScaleX;
				m_circles[i]->SetScale(circleScale + 0.05f, circleScale + 0.05f);
				
				if (m_circles[i]->GetAlpha() <= 0.0f){
					m_circles[i]->Reset();
					m_circles[i]->GetSprite()->m_X = m_circleInitialPos;
					m_circles[i]->SetScale(m_circleInitialScale, m_circleInitialScale);
				}
			}

			continue;
		}

		m_circles[i]->Update();
		bool reachedDestination = false;
		if (m_circles[i]->GetSpeed() > 0.0f){
			if (m_circles[i]->GetColor() == m_circles[i]->GetReceiver()->GetFrontSquare()->GetColor()){
				if (m_circles[i]->GetSprite()->m_X >= m_circles[i]->GetReceiver()->GetFrontSquare()->GetSprite()->m_X)
					reachedDestination = true;
			}else{
				if (m_circles[i]->GetSprite()->m_X >= m_circles[i]->GetReceiver()->GetFrontSquare()->GetSprite()->m_X - m_circles[i]->GetReceiver()->GetFrontSquare()->GetWidth(true)){
					float circleScale = m_circles[i]->GetSprite()->m_ScaleX;
					Gameplay::s_isPaused = true;
					g_pTweener->Tween(2.0f, FLOAT, &m_circles[i]->GetSprite()->m_ScaleX, circleScale + 1.5f,
						FLOAT, &m_circles[i]->GetSprite()->m_ScaleY, circleScale + 1.5f,
						ONCOMPLETE, Square::OnGameOver, END);
					return;
				}
			}
		}else{
			if (m_circles[i]->GetColor() == m_circles[i]->GetReceiver()->GetFrontSquare()->GetColor()){
				if (m_circles[i]->GetSprite()->m_X <= m_circles[i]->GetReceiver()->GetFrontSquare()->GetSprite()->m_X)
					reachedDestination = true;
			}else{
				if (m_circles[i]->GetSprite()->m_X <= m_circles[i]->GetReceiver()->GetFrontSquare()->GetSprite()->m_X + m_circles[i]->GetReceiver()->GetFrontSquare()->GetWidth(true)){
					float circleScale = m_circles[i]->GetSprite()->m_ScaleX;
					Gameplay::s_isPaused = true;
					g_pTweener->Tween(2.0f, FLOAT, &m_circles[i]->GetSprite()->m_ScaleX, circleScale + 1.5f,
						FLOAT, &m_circles[i]->GetSprite()->m_ScaleY, circleScale + 1.5f,
						ONCOMPLETE, Square::OnGameOver, END);
					return;
				}
			}
		}

		if (reachedDestination){
			m_circles[i]->Reset();
			m_circles[i]->GetSprite()->m_X = m_circleInitialPos;
			m_circles[i]->SetScale(m_circleInitialScale, m_circleInitialScale);
		}
	}
}

void Square::SetReceiver(SquareObject* pReceiver){
	for (uint i = 0; i < s_kMaxCircles; i++){
		m_circles[i]->SetReceiver(pReceiver);
	}
}

void Square::AddCirclesTo(CNode *pContainer, float posX){
	m_circleInitialPos = posX;
	m_circleInitialScale = GetSprite()->m_ScaleX * 0.7f;
	for (uint i = 0; i < s_kMaxCircles; i++){
		m_circles[i]->SetPosition(posX, GetSprite()->m_Y);
		m_circles[i]->SetScale(m_circleInitialScale, m_circleInitialScale);
		m_circles[i]->Reset();
		m_circles[i]->AddTo(pContainer);
	}
}

void Square::RemoveCirclesFromParent(){
	for (uint i = 0; i < s_kMaxCircles; i++){
		m_circles[i]->Reset();
		m_circles[i]->RemoveFromParent();
	}
}

void Square::Shoot(float speed){	
	for (uint i = 0; i < s_kMaxCircles; i++){
		if (!m_circles[i]->IsActive()){
			m_circles[i]->SetSpeed(speed);
			m_circles[i]->SetIsActive(true);
			m_circles[i]->SetTapped(false);
			return;
		}
	}
}

void Square::CheckTap(float x, float y){
	for (uint i = 0; i < s_kMaxCircles; i++){
		if (m_circles[i]->IsActive() && !m_circles[i]->IsTapped()){
			if (m_circles[i]->GetSprite()->HitTest(x, y, 15.0f, 5.0f)){
				m_circles[i]->SetTapped(true);
				return;
			}
		}
	}
}

void Square::OnGameOver(CTween *pTween){
	g_pSceneManager->Find(Scene::kScene_Gameplay)->SwitchTo(Scene::kScene_MainMenu);
}


//- Square Object ------------------------------------------------------------
SquareObject::SquareObject(bool leftSide):m_front(GameObject::kGameObjectColor_Black),
m_isShooter(false),
m_isSwitching(false),
m_frontPosX(0.0f),
m_backPosX(0.0f),
m_switchSpeed(0.0f),
m_shootSpeed(0.0f)
{
	m_pWhite = new Square(GameObject::kGameObjectColor_White);
	m_pBlack = new Square(GameObject::kGameObjectColor_Black);
	m_left = leftSide;
}

SquareObject::~SquareObject(){
	delete m_pWhite; m_pWhite = 0;
	delete m_pBlack; m_pBlack = 0;
}

void SquareObject::SetReceiver(SquareObject *pReceiver){
	m_pWhite->SetReceiver(pReceiver);
	m_pBlack->SetReceiver(pReceiver);
}

void SquareObject::AddTo(CNode *pParent){
	if (!m_pWhite || !m_pBlack)
		return;

	m_pWhite->AddTo(pParent);
	m_pBlack->AddTo(pParent);
}

void SquareObject::RemoveFromParent(){
	if (!m_pWhite || !m_pBlack)
		return;

	m_pWhite->RemoveCirclesFromParent();
	m_pWhite->RemoveFromParent();
	
	m_pBlack->RemoveCirclesFromParent();
	m_pBlack->RemoveFromParent();
}

void SquareObject::SetScale(float scaleX, float scaleY){
	m_pBlack->SetScale(scaleX, scaleY);
	m_pWhite->SetScale(scaleX, scaleY);
}

void SquareObject::SetPosition(float posX, float posY){
	m_frontPosX = posX;
	m_backPosX = posX - m_pBlack->GetWidth();
	if (!m_left)
		m_backPosX = posX + m_pBlack->GetWidth();

	if (m_front == GameObject::kGameObjectColor_Black){
		m_pBlack->SetPosition(m_frontPosX, posY);
		m_pWhite->SetPosition(m_backPosX, posY);
	}else{
		m_pBlack->SetPosition(m_backPosX, posY);
		m_pWhite->SetPosition(m_frontPosX, posY);
	}
}

float SquareObject::GetWidth(bool half){
	return m_pBlack->GetWidth(half);
}

float SquareObject::GetHeight(bool half){
	return m_pBlack->GetWidth(half);
}

void SquareObject::SetInitialParams(){
	m_front = (GameObject::EGameObjectColor)L_RandomInt(0, 1);
	m_isShooter = (bool)L_RandomInt(0, 1);

	m_switchSpeed = 10.0f;
}

void SquareObject::Update(){
	if (m_isSwitching){
		Switch();
		//return;
	}

	m_pBlack->Update();
	m_pWhite->Update();
}

void SquareObject::SetupCircles(CNode *pContainer){
	m_pBlack->AddCirclesTo(pContainer, m_frontPosX);
	m_pWhite->AddCirclesTo(pContainer, m_frontPosX);
}

void SquareObject::Switch(){
	Square *pFrontSquare = m_pWhite;
	Square *pBackSquare = m_pBlack;
	if (m_front == GameObject::kGameObjectColor_Black){
		pFrontSquare = m_pBlack;
		pBackSquare = m_pWhite;
	}

	if (pFrontSquare->GetSprite()->m_X != m_backPosX){
		if (m_left){
			pFrontSquare->GetSprite()->m_X -= m_switchSpeed;
			if (pFrontSquare->GetSprite()->m_X <= m_backPosX)
				pFrontSquare->GetSprite()->m_X = m_backPosX;
		}
		else{
			pFrontSquare->GetSprite()->m_X += m_switchSpeed;
			if (pFrontSquare->GetSprite()->m_X >= m_backPosX)
				pFrontSquare->GetSprite()->m_X = m_backPosX;
		}

		return;
	}

	if (pBackSquare->GetSprite()->m_X != m_frontPosX){
		if (m_left){
			pBackSquare->GetSprite()->m_X += m_switchSpeed;
			if (pBackSquare->GetSprite()->m_X >= m_frontPosX)
				pBackSquare->GetSprite()->m_X = m_frontPosX;
		}
		else{
			pBackSquare->GetSprite()->m_X -= m_switchSpeed;
			if (pBackSquare->GetSprite()->m_X <= m_frontPosX)
				pBackSquare->GetSprite()->m_X = m_frontPosX;
		}

		return;
	}

	m_isSwitching = false;
	m_front = (m_front == GameObject::kGameObjectColor_Black ? GameObject::kGameObjectColor_White : GameObject::kGameObjectColor_Black);
}

void SquareObject::Shoot(float speed){
	GetFrontSquare()->Shoot(speed);
}

Square *SquareObject::GetFrontSquare(){
	if (m_front == GameObject::kGameObjectColor_Black)
		return m_pBlack;
	return m_pWhite;
}

void SquareObject::CheckTap(float x, float y){
	m_pBlack->CheckTap(x, y);
	m_pWhite->CheckTap(x, y);
}