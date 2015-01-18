#include "header.h"

Paint::Paint(GameObject::EColor color) : GameObject(kGameObjectType_Paint){
	m_color = color;
	Init();
}

Paint::~Paint(){
	Cleanup();
}

void Paint::Init(){
	//Game::EGameGraphics gameGraphics = (Game::EGameGraphics)L_RandomInt((int)Game::kGameGraphics_Entity_PaintRed_1, (int)Game::kGameGraphics_Entity_PaintViolet_2);
	Game::EGameGraphics gameGraphics = Game::kGameGraphics_Count;
	int type = L_RandomInt(0, 1);
	switch (m_color){
		case kColor_Red:
		{
			gameGraphics = Game::kGameGraphics_Entity_PaintRed_1;
			if (type)
				gameGraphics = Game::kGameGraphics_Entity_PaintRed_2;
			break;
		}
		case kColor_Blue:
		{
			gameGraphics = Game::kGameGraphics_Entity_PaintBlue_1;
			if (type)
				gameGraphics = Game::kGameGraphics_Entity_PaintBlue_2;
		   break;
		}
		case kColor_Green:
		{
			gameGraphics = Game::kGameGraphics_Entity_PaintGreen_1;
			if (type)
				gameGraphics = Game::kGameGraphics_Entity_PaintGreen_2;
		   break;
		}
		case kColor_Indigo:
		{
			gameGraphics = Game::kGameGraphics_Entity_PaintIndigo_1;
			if (type)
				gameGraphics = Game::kGameGraphics_Entity_PaintIndigo_2;
		   break;
		}
		case kColor_Orange:
		{
			gameGraphics = Game::kGameGraphics_Entity_PaintOrange_1;
			if (type)
				gameGraphics = Game::kGameGraphics_Entity_PaintOrange_2;
		   break;
		}
		case kColor_Yellow:
		{
			gameGraphics = Game::kGameGraphics_Entity_PaintYellow_1;
			if (type)
				gameGraphics = Game::kGameGraphics_Entity_PaintYellow_2;
		   break;
		}
		case kColor_Violet:
		{
			gameGraphics = Game::kGameGraphics_Entity_PaintViolet_1;
			if (type)
				gameGraphics = Game::kGameGraphics_Entity_PaintViolet_2;
		   break;
		}
		default:
			break;
	}

	GameObject::Init(gameGraphics, 0, 0, Game::s_scaleFactor, Game::s_scaleFactor);
}

void Paint::Cleanup(){
	GameObject::Cleanup();
}

void Paint::Update(float deltaTime){
	GameObject::Update();

}
