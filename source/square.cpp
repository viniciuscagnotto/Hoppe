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

			continue;
		}

		m_circles[i]->Update();
		bool reachedDestination = false;
		//if (m_circles[i]->GetColor() == m_circles[i]->GetReceiver()->GetColor()){

		//}
		//else
		//{
			//if (m_circles[i]->CheckHit(m_circles[i]->GetReceiver())){

			//}
		//}

		if (m_circles[i]->GetSpeed() > 0.0f){
			if (m_circles[i]->GetSprite()->m_X >= m_circles[i]->GetReceiver()->GetSprite()->m_X)
				reachedDestination = true;
		}else{
			if (m_circles[i]->GetSprite()->m_X <= m_circles[i]->GetReceiver()->GetSprite()->m_X)
				reachedDestination = true;
		}

		if (reachedDestination){
			m_circles[i]->SetIsActive(false);
			m_circles[i]->GetSprite()->m_X = m_circleInitialPos;
		}
	}
}

void Square::AddCirclesTo(CNode *pContainer, float posX){
	m_circleInitialPos = posX;
	for (uint i = 0; i < s_kMaxCircles; i++){
		m_circles[i]->SetPosition(posX, GetSprite()->m_Y);
		m_circles[i]->SetScale(GetSprite()->m_ScaleX * 0.7f, GetSprite()->m_ScaleX * 0.7f);

		m_circles[i]->SetIsActive(false);
		m_circles[i]->SetReceiver(0);

		m_circles[i]->AddTo(pContainer);
	}
}

void Square::RemoveCirclesFromParent(){
	for (uint i = 0; i < s_kMaxCircles; i++){
		m_circles[i]->SetIsActive(false);
		m_circles[i]->SetReceiver(0);
		m_circles[i]->RemoveFromParent();
	}
}

void Square::Shoot(float speed, Square *pReceiver){	
	for (uint i = 0; i < s_kMaxCircles; i++){
		if (!m_circles[i]->IsActive()){
			m_circles[i]->SetSpeed(speed);
			m_circles[i]->SetReceiver(pReceiver);
			m_circles[i]->SetIsActive(true);
			return;
		}
	}
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
		return;
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

void SquareObject::Shoot(float speed, SquareObject *pReceiver){
	if (m_front == GameObject::kGameObjectColor_Black){
		m_pBlack->Shoot(speed, pReceiver->GetFrontSquare());
	}else{
		m_pWhite->Shoot(speed, pReceiver->GetFrontSquare());
	}
}

Square *SquareObject::GetFrontSquare(){
	if (m_front == GameObject::kGameObjectColor_Black)
		return m_pBlack;
	return m_pWhite;
}