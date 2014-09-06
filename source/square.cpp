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
}

void Square::Cleanup()
{
	GameObject::Cleanup();

}

void Square::Update()
{
	GameObject::Update();

}


//- Square Object ------------------------------------------------------------

SquareObject::SquareObject(bool leftSide):m_front(GameObject::kGameObjectColor_Black),
m_isShooter(false),
m_isSwitching(false),
m_frontPosX(0.0f),
m_backPosX(0.0f)
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

	m_pWhite->RemoveFromParent();
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
}

void SquareObject::Update(){
	

}

void SquareObject::Switch(){
	Square *pFrontSquare = m_pWhite;
	Square *pBackSquare = m_pBlack;
	if (m_front == GameObject::kGameObjectColor_Black){
		pFrontSquare = m_pBlack;
		pBackSquare = m_pWhite;
	}

	m_isSwitching = true;
	m_front = (m_front == GameObject::kGameObjectColor_Black ? GameObject::kGameObjectColor_White : GameObject::kGameObjectColor_Black);
	
	g_pTweener->Tween(0.2f, FLOAT, &pFrontSquare->GetSprite()->m_X, m_backPosX, END);
	g_pTweener->Tween(0.2f, DELAY, 0.2f, FLOAT, &pBackSquare->GetSprite()->m_X, m_frontPosX, BOOL, &m_isSwitching, false, END);
}

void SquareObject::onFrontRetreat(CTween *pTween){
	Square *pSquare = m_pBlack;
	if (m_front == GameObject::kGameObjectColor_Black)
		pSquare = m_pWhite;

	g_pTweener->Tween(0.2f, ONCOMPLETE, &SquareObject::onBackAdvance, FLOAT, &pSquare->GetSprite()->m_X, m_frontPosX, END);
}

void SquareObject::onBackAdvance(CTween *pTween){
	m_isSwitching = false;
}