#include "core.h"

SpriteManager* g_pSpriteManager = 0;

//Sprite Object --------------------------------------------------------------
SpriteObject::SpriteObject():m_animationState(0){
	for (uint i = 0; i < s_kMaxAnimations; i++)
		m_animations[i] = SAnimation();
	Cleanup();
}

void SpriteObject::Cleanup(){
	for (uint i = 0; i < s_kMaxAnimations; i++)
		m_animations[i].Cleanup();
	m_animationState = 0;

	m_Atlas = 0;
	m_AnimDuration = 0.0f;
	m_AnimRepeat = 0;
	
	m_Image = 0;
	m_W = 0;
	m_H = 0;
	m_AnchorX = 0.5f;
	m_AnchorY = 0.5f;
}

bool SpriteObject::IsInScene(){
	if (m_X + RealW() * 0.5f > 0 &&
		m_X - RealW() * 0.5f < IwGxGetScreenWidth() &&
		m_Y + RealH() * 0.5f > 0 &&
		m_Y - RealH() * 0.5f < IwGxGetScreenHeight())
		return true;

	return false;
}

void SpriteObject::AddAnimation(uint animationState, uint atlasIndex, float duration, int repeat){
	SAnimation *pAnimation = &m_animations[animationState];
	pAnimation->animationAtlas = (CAtlas *)g_pResourceManager->GetAtlas(atlasIndex);
	pAnimation->duration = duration;
	pAnimation->repeat = repeat;
}

void SpriteObject::RunAnimation(uint animationState){
	SetAtlas(m_animations[animationState].animationAtlas);
	SetAnimDuration(m_animations[animationState].duration);
	SetAnimRepeat(m_animations[animationState].repeat);
}

bool SpriteObject::HitTest(int posX, int posY, float extraW, float extraH){

	float left = m_X - (RealW() * 0.5f) - extraW;
	float right = m_X + (RealW() * 0.5f) + extraW;
	float up = m_Y + (RealH() * 0.5f) + extraH;
	float down = m_Y - (RealH() * 0.5f) - extraH;

	if (posX < left || posX > right || posY < down || posY > up)
		return false;

	return true;
}


//Sprite Manager --------------------------------------------------------
SpriteObject* SpriteManager::CreateSpriteObject(){
	SpriteObject *pSpriteObject = new SpriteObject();
	return pSpriteObject;
}

SpriteObject* SpriteManager::CreateSpriteObject(uint resourceIndex)
{
	SpriteObject *pSpriteObject = new SpriteObject();
	pSpriteObject->SetImage(g_pResourceManager->GetGraphic(resourceIndex));
	return pSpriteObject;
}

void SpriteManager::DeleteSpriteObject(SpriteObject *pSpriteObject)
{
	if (!pSpriteObject)
		return;

	pSpriteObject->Cleanup();
	delete pSpriteObject;
	pSpriteObject = 0;
}

bool SpriteManager::Intersects(SpriteObject* pObject1, SpriteObject* pObject2){

	float obj1Left = pObject1->m_X - pObject1->RealW() * 0.5f;
	float obj1Right = pObject1->m_X + pObject1->RealW() * 0.5f;
	float obj1Up = pObject1->m_Y - pObject1->RealH() * 0.5f;
	float obj1Down = pObject1->m_Y + pObject1->RealH() * 0.5f;

	float obj2Left = pObject2->m_X - pObject2->RealW()* 0.5f;
	float obj2Right = pObject2->m_X + pObject2->RealW() * 0.5f;
	float obj2Up = pObject2->m_Y - pObject2->RealH() * 0.5f;
	float obj2Down = pObject2->m_Y + pObject2->RealH() * 0.5f;

	if (obj1Left > obj2Right || obj1Right < obj2Left ||
		obj1Up > obj2Down || obj1Down < obj2Up){
		return false;
	}

	return true;
}