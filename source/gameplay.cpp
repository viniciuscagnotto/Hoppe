#include "header.h"

uint Gameplay::s_numLines = Gameplay::s_kDefaultLines;
bool Gameplay::s_isPaused = false;

Gameplay::Gameplay() : Scene(kScene_Gameplay),
m_topAdsHeight(0.0f),
m_bottomHudHeight(0.0f)
{
	for (uint i = 0; i < s_kMaxLines; i++)
		m_lines[i] = new SLine();

	for (uint i = 0; i < s_kMaxCircles; i++){
		m_whiteCircles[i] = new Circle(GameObject::kGameObjectColor_White);
		m_blackCircles[i] = new Circle(GameObject::kGameObjectColor_Black);
	}

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

	for (uint i = 0; i < s_kMaxCircles; i++){
		delete m_whiteCircles[i]; m_whiteCircles[i] = 0;
		delete m_blackCircles[i]; m_blackCircles[i] = 0;
	}
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
	
	for (uint i = 0; i < s_numLines; i++){
		float yPosition = m_topAdsHeight + (squareHeight * 0.5f) + (squareHeight * i) + SPACEMENT + (SPACEMENT * i);

		m_lines[i]->pLeft->SetInitialParams();
		m_lines[i]->pLeft->SetScale(scaleX, scaleY);
		m_lines[i]->pLeft->SetPosition(squareWidth * 0.5f, yPosition);
		m_lines[i]->pLeft->AddTo(this);

		m_lines[i]->pRight->SetInitialParams();
		m_lines[i]->pRight->SetScale(scaleX, scaleY);
		m_lines[i]->pRight->SetPosition(IwGxGetScreenWidth() - squareWidth * 0.5f, yPosition);
		m_lines[i]->pRight->AddTo(this);
		m_lines[i]->pRight->SetIsShooter(!m_lines[i]->pLeft->IsShooter());
	}
}

void Gameplay::Cleanup(){
	for (uint i = 0; i < s_kMaxLines; i++){
		m_lines[i]->isBusy = false;
		m_lines[i]->pLeft->RemoveFromParent();
		m_lines[i]->pRight->RemoveFromParent();
	}

	for (uint i = 0; i < s_kMaxCircles; i++){
		m_whiteCircles[i]->RemoveFromParent();
		m_blackCircles[i]->RemoveFromParent();
	}

	Scene::Cleanup();
}

void Gameplay::Update(float deltaTime, float alphaMul)
{
	if (!CheckCurrent())
		return;

	Scene::Update(deltaTime, alphaMul);
	
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
	SwitchTo(kScene_MainMenu);
}