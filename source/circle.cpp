#include "header.h"

Circle::Circle(GameObject::EGameObjectColor color) :GameObject(kGameObjectType_Circle),
state(0),
m_speed(0.0f),
m_pReceiver(0)
{
	m_color = color;
	Init();
}

Circle::~Circle()
{
	Cleanup();
}

void Circle::Init()
{
	Game::EGameGraphics gameGraphics = Game::kGameGraphics_Entity_BlackCircle;
	if (m_color == kGameObjectColor_White)
		gameGraphics = Game::kGameGraphics_Entity_WhiteCircle;

	GameObject::Init(gameGraphics, 0, 0);
}

void Circle::Cleanup()
{
	GameObject::Cleanup();
	m_pReceiver = 0;
}

void Circle::Update()
{
	GameObject::Update();

	m_pSprite->m_X += m_speed;
}
