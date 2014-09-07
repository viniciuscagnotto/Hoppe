#include "header.h"

uint Gameplay::s_numLines = Gameplay::s_kDefaultLines;
bool Gameplay::s_isPaused = false;

Gameplay::Gameplay() : Scene(kScene_Gameplay),
m_topAdsHeight(0.0f),
m_bottomHudHeight(0.0f),
m_pCirclesContainer(0),
m_points(0)
{
	for (uint i = 0; i < s_kMaxLines; i++)
		m_lines[i] = new SLine();

	m_pCirclesContainer = new CNode();
 
	s_numLines = s_kDefaultLines;
}

Gameplay::~Gameplay()
{
	Cleanup();

	for (uint i = 0; i < s_kMaxLines; i++){
		delete m_lines[i]->pRight; m_lines[i]->pRight = 0;
		delete m_lines[i]->pLeft; m_lines[i]->pLeft = 0;
		delete m_lines[i]; m_lines[i] = 0;
	}

	delete m_pCirclesContainer;
	m_pCirclesContainer = 0;
}

void Gameplay::Init(){
	Scene::Init();

	int totalSpace = (SPACEMENT * s_numLines) + SPACEMENT;
	m_topAdsHeight = IwGxGetScreenHeight() * (TOP_ADS_HEIGHT / 100.0f);
	m_bottomHudHeight = IwGxGetScreenHeight() * (BOTTOM_HUD_HEIGHT / 100.0f);
	float squareWidth = IwGxGetScreenWidth() * (SQUARE_WIDTH / 100.0f);

	float squareHeight = (IwGxGetScreenHeight() - m_bottomHudHeight - m_topAdsHeight - totalSpace) / s_numLines;
	float scaleX = squareWidth / SPRITE_SIZE;
	float scaleY = squareHeight / SPRITE_SIZE;
	
	m_points = 0;
	AddChild(m_pCirclesContainer);

	for (uint i = 0; i < s_numLines; i++){
		float yPosition = m_topAdsHeight + (squareHeight * 0.5f) + (squareHeight * i) + SPACEMENT + (SPACEMENT * i);

		m_lines[i]->pLeft->SetInitialParams();
		m_lines[i]->pLeft->SetScale(scaleX, scaleY);
		m_lines[i]->pLeft->SetPosition(squareWidth * 0.5f, yPosition);
		m_lines[i]->pLeft->AddTo(this);
		m_lines[i]->pLeft->SetupCircles(m_pCirclesContainer);

		m_lines[i]->pRight->SetInitialParams();
		m_lines[i]->pRight->SetScale(scaleX, scaleY);
		m_lines[i]->pRight->SetPosition(IwGxGetScreenWidth() - squareWidth * 0.5f, yPosition);
		m_lines[i]->pRight->AddTo(this);
		m_lines[i]->pRight->SetIsShooter(!m_lines[i]->pLeft->IsShooter());
		m_lines[i]->pRight->SetupCircles(m_pCirclesContainer);
	}
}

void Gameplay::Cleanup(){
	for (uint i = 0; i < s_kMaxLines; i++){
		m_lines[i]->isBusy = false;
		m_lines[i]->pLeft->RemoveFromParent();
		m_lines[i]->pRight->RemoveFromParent();
	}

	if (IsChild(m_pCirclesContainer))
		RemoveChild(m_pCirclesContainer);
	
	Scene::Cleanup();
}

void Gameplay::Update(float deltaTime, float alphaMul)
{
	if (!CheckCurrent())
		return;

	Scene::Update(deltaTime, alphaMul);
	
	if (!s_isPaused){
		for (uint i = 0; i < s_numLines; i++)
			m_lines[i]->Update();
	}

	if (CheckTouch())
		HandleTouch();
}

void Gameplay::Render()
{
	Scene::Render();
	
}

void Gameplay::HandleTouch()
{
	Scene::HandleTouch();
	
	if (s_isPaused){
		
	}else{
		for (uint i = 0; i < s_numLines; i++)
			m_lines[i]->Shoot(7.0f);
	}

}

void Gameplay::Pause(){
	if (s_isPaused){

	}else{

	}

	s_isPaused = !s_isPaused;
}