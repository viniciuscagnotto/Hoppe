#include "header.h"

Circle::Circle(GameObject::EGameObjectColor color) :GameObject(kGameObjectType_Circle)
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

}

void Circle::Update()
{
	GameObject::Update();

}
