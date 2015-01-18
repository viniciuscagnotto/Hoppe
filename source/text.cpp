#include "header.h"

Text::Text(GameObject::ETextType textType, GameObject::EColor textColor, GameObject::EColor color) : GameObject(kGameObjectType_Text)
{
	m_textType = textType;
	m_textColor = textColor;
	m_color = color;
	Init();
}

Text::~Text(){
	Cleanup();
}

void Text::Init(){
	Game::EGameGraphics gameGraphics = Game::kGameGraphics_Count;
	if (m_textType == kText_Stroke){
		gameGraphics = GetStrokeText();
	}else{
		gameGraphics = GetFilledText();
	}

	GameObject::Init(gameGraphics, 0, 0, Game::s_scaleFactor, Game::s_scaleFactor);
}

void Text::Cleanup(){
	GameObject::Cleanup();
}

void Text::Update(float deltaTime){
	GameObject::Update();

}

Game::EGameGraphics Text::GetStrokeText(){
	if (m_textColor == kColor_Red){
		if (m_color == kColor_Red) return Game::kGameGraphics_Entity_RedStrokeRed;
		if (m_color == kColor_Blue) return Game::kGameGraphics_Entity_RedStrokeBlue;
		if (m_color == kColor_Green) return Game::kGameGraphics_Entity_RedStrokeGreen;
		if (m_color == kColor_Indigo) return Game::kGameGraphics_Entity_RedStrokeIndigo;
		if (m_color == kColor_Orange) return Game::kGameGraphics_Entity_RedStrokeOrange;
		if (m_color == kColor_Yellow) return Game::kGameGraphics_Entity_RedStrokeYellow;
		if (m_color == kColor_Violet) return Game::kGameGraphics_Entity_RedStrokeViolet;
	}else if (m_textColor == kColor_Blue){
		if (m_color == kColor_Red) return Game::kGameGraphics_Entity_BlueStrokeRed;
		if (m_color == kColor_Blue) return Game::kGameGraphics_Entity_BlueStrokeBlue;
		if (m_color == kColor_Green) return Game::kGameGraphics_Entity_BlueStrokeGreen;
		if (m_color == kColor_Indigo) return Game::kGameGraphics_Entity_BlueStrokeIndigo;
		if (m_color == kColor_Orange) return Game::kGameGraphics_Entity_BlueStrokeOrange;
		if (m_color == kColor_Yellow) return Game::kGameGraphics_Entity_BlueStrokeYellow;
		if (m_color == kColor_Violet) return Game::kGameGraphics_Entity_BlueStrokeViolet;
	}else if (m_textColor == kColor_Green){
		if (m_color == kColor_Red) return Game::kGameGraphics_Entity_GreenStrokeRed;
		if (m_color == kColor_Blue) return Game::kGameGraphics_Entity_GreenStrokeBlue;
		if (m_color == kColor_Green) return Game::kGameGraphics_Entity_GreenStrokeGreen;
		if (m_color == kColor_Indigo) return Game::kGameGraphics_Entity_GreenStrokeIndigo;
		if (m_color == kColor_Orange) return Game::kGameGraphics_Entity_GreenStrokeOrange;
		if (m_color == kColor_Yellow) return Game::kGameGraphics_Entity_GreenStrokeYellow;
		if (m_color == kColor_Violet) return Game::kGameGraphics_Entity_GreenStrokeViolet;
	}else if (m_textColor == kColor_Indigo){
		if (m_color == kColor_Red) return Game::kGameGraphics_Entity_IndigoStrokeRed;
		if (m_color == kColor_Blue) return Game::kGameGraphics_Entity_IndigoStrokeBlue;
		if (m_color == kColor_Green) return Game::kGameGraphics_Entity_IndigoStrokeGreen;
		if (m_color == kColor_Indigo) return Game::kGameGraphics_Entity_IndigoStrokeIndigo;
		if (m_color == kColor_Orange) return Game::kGameGraphics_Entity_IndigoStrokeOrange;
		if (m_color == kColor_Yellow) return Game::kGameGraphics_Entity_IndigoStrokeYellow;
		if (m_color == kColor_Violet) return Game::kGameGraphics_Entity_IndigoStrokeViolet;
	}else if (m_textColor == kColor_Orange){
		if (m_color == kColor_Red) return Game::kGameGraphics_Entity_OrangeStrokeRed;
		if (m_color == kColor_Blue) return Game::kGameGraphics_Entity_OrangeStrokeBlue;
		if (m_color == kColor_Green) return Game::kGameGraphics_Entity_OrangeStrokeGreen;
		if (m_color == kColor_Indigo) return Game::kGameGraphics_Entity_OrangeStrokeIndigo;
		if (m_color == kColor_Orange) return Game::kGameGraphics_Entity_OrangeStrokeOrange;
		if (m_color == kColor_Yellow) return Game::kGameGraphics_Entity_OrangeStrokeYellow;
		if (m_color == kColor_Violet) return Game::kGameGraphics_Entity_OrangeStrokeViolet;
	}else if (m_textColor == kColor_Yellow){
		if (m_color == kColor_Red) return Game::kGameGraphics_Entity_YellowStrokeRed;
		if (m_color == kColor_Blue) return Game::kGameGraphics_Entity_YellowStrokeBlue;
		if (m_color == kColor_Green) return Game::kGameGraphics_Entity_YellowStrokeGreen;
		if (m_color == kColor_Indigo) return Game::kGameGraphics_Entity_YellowStrokeIndigo;
		if (m_color == kColor_Orange) return Game::kGameGraphics_Entity_YellowStrokeOrange;
		if (m_color == kColor_Yellow) return Game::kGameGraphics_Entity_YellowStrokeYellow;
		if (m_color == kColor_Violet) return Game::kGameGraphics_Entity_YellowStrokeViolet;
	}else if (m_textColor == kColor_Violet){
		if (m_color == kColor_Red) return Game::kGameGraphics_Entity_VioletStrokeRed;
		if (m_color == kColor_Blue) return Game::kGameGraphics_Entity_VioletStrokeBlue;
		if (m_color == kColor_Green) return Game::kGameGraphics_Entity_VioletStrokeGreen;
		if (m_color == kColor_Indigo) return Game::kGameGraphics_Entity_VioletStrokeIndigo;
		if (m_color == kColor_Orange) return Game::kGameGraphics_Entity_VioletStrokeOrange;
		if (m_color == kColor_Yellow) return Game::kGameGraphics_Entity_VioletStrokeYellow;
		if (m_color == kColor_Violet) return Game::kGameGraphics_Entity_VioletStrokeViolet;
	}

	return Game::kGameGraphics_Count;
}

Game::EGameGraphics Text::GetFilledText(){
	if (m_textColor == kColor_Red){
		if (m_color == kColor_Red) return Game::kGameGraphics_Entity_RedFilledRed;
		if (m_color == kColor_Blue) return Game::kGameGraphics_Entity_RedFilledBlue;
		if (m_color == kColor_Green) return Game::kGameGraphics_Entity_RedFilledGreen;
		if (m_color == kColor_Indigo) return Game::kGameGraphics_Entity_RedFilledIndigo;
		if (m_color == kColor_Orange) return Game::kGameGraphics_Entity_RedFilledOrange;
		if (m_color == kColor_Yellow) return Game::kGameGraphics_Entity_RedFilledYellow;
		if (m_color == kColor_Violet) return Game::kGameGraphics_Entity_RedFilledViolet;
	}else if (m_textColor == kColor_Blue){
		if (m_color == kColor_Red) return Game::kGameGraphics_Entity_BlueFilledRed;
		if (m_color == kColor_Blue) return Game::kGameGraphics_Entity_BlueFilledBlue;
		if (m_color == kColor_Green) return Game::kGameGraphics_Entity_BlueFilledGreen;
		if (m_color == kColor_Indigo) return Game::kGameGraphics_Entity_BlueFilledIndigo;
		if (m_color == kColor_Orange) return Game::kGameGraphics_Entity_BlueFilledOrange;
		if (m_color == kColor_Yellow) return Game::kGameGraphics_Entity_BlueFilledYellow;
		if (m_color == kColor_Violet) return Game::kGameGraphics_Entity_BlueFilledViolet;
	}else if (m_textColor == kColor_Green){
		if (m_color == kColor_Red) return Game::kGameGraphics_Entity_GreenFilledRed;
		if (m_color == kColor_Blue) return Game::kGameGraphics_Entity_GreenFilledBlue;
		if (m_color == kColor_Green) return Game::kGameGraphics_Entity_GreenFilledGreen;
		if (m_color == kColor_Indigo) return Game::kGameGraphics_Entity_GreenFilledIndigo;
		if (m_color == kColor_Orange) return Game::kGameGraphics_Entity_GreenFilledOrange;
		if (m_color == kColor_Yellow) return Game::kGameGraphics_Entity_GreenFilledYellow;
		if (m_color == kColor_Violet) return Game::kGameGraphics_Entity_GreenFilledViolet;
	}else if (m_textColor == kColor_Indigo){
		if (m_color == kColor_Red) return Game::kGameGraphics_Entity_IndigoFilledRed;
		if (m_color == kColor_Blue) return Game::kGameGraphics_Entity_IndigoFilledBlue;
		if (m_color == kColor_Green) return Game::kGameGraphics_Entity_IndigoFilledGreen;
		if (m_color == kColor_Indigo) return Game::kGameGraphics_Entity_IndigoFilledIndigo;
		if (m_color == kColor_Orange) return Game::kGameGraphics_Entity_IndigoFilledOrange;
		if (m_color == kColor_Yellow) return Game::kGameGraphics_Entity_IndigoFilledYellow;
		if (m_color == kColor_Violet) return Game::kGameGraphics_Entity_IndigoFilledViolet;
	}else if (m_textColor == kColor_Orange){
		if (m_color == kColor_Red) return Game::kGameGraphics_Entity_OrangeFilledRed;
		if (m_color == kColor_Blue) return Game::kGameGraphics_Entity_OrangeFilledBlue;
		if (m_color == kColor_Green) return Game::kGameGraphics_Entity_OrangeFilledGreen;
		if (m_color == kColor_Indigo) return Game::kGameGraphics_Entity_OrangeFilledIndigo;
		if (m_color == kColor_Orange) return Game::kGameGraphics_Entity_OrangeFilledOrange;
		if (m_color == kColor_Yellow) return Game::kGameGraphics_Entity_OrangeFilledYellow;
		if (m_color == kColor_Violet) return Game::kGameGraphics_Entity_OrangeFilledViolet;
	}else if (m_textColor == kColor_Yellow){
		if (m_color == kColor_Red) return Game::kGameGraphics_Entity_YellowFilledRed;
		if (m_color == kColor_Blue) return Game::kGameGraphics_Entity_YellowFilledBlue;
		if (m_color == kColor_Green) return Game::kGameGraphics_Entity_YellowFilledGreen;
		if (m_color == kColor_Indigo) return Game::kGameGraphics_Entity_YellowFilledIndigo;
		if (m_color == kColor_Orange) return Game::kGameGraphics_Entity_YellowFilledOrange;
		if (m_color == kColor_Yellow) return Game::kGameGraphics_Entity_YellowFilledYellow;
		if (m_color == kColor_Violet) return Game::kGameGraphics_Entity_YellowFilledViolet;
	}else if (m_textColor == kColor_Violet){
		if (m_color == kColor_Red) return Game::kGameGraphics_Entity_VioletFilledRed;
		if (m_color == kColor_Blue) return Game::kGameGraphics_Entity_VioletFilledBlue;
		if (m_color == kColor_Green) return Game::kGameGraphics_Entity_VioletFilledGreen;
		if (m_color == kColor_Indigo) return Game::kGameGraphics_Entity_VioletFilledIndigo;
		if (m_color == kColor_Orange) return Game::kGameGraphics_Entity_VioletFilledOrange;
		if (m_color == kColor_Yellow) return Game::kGameGraphics_Entity_VioletFilledYellow;
		if (m_color == kColor_Violet) return Game::kGameGraphics_Entity_VioletFilledViolet;
	}

	return Game::kGameGraphics_Count;
}