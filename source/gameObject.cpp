#include "header.h"

GameObject::GameObject() : m_pParent(0),
m_pSprite(0),
m_destroyMe(false),
m_type(kGameObjectType_Count)
{

}

GameObject::GameObject(GameObject::EGameObjectType gameObjectType) : m_pParent(0),
m_pSprite(0),
m_destroyMe(false),
m_type(gameObjectType)
{

}

GameObject::~GameObject()
{

	Cleanup();
}

void GameObject::Init(Game::EGameGraphics id, float posX, float posY, float scaleX, float scaleY)
{
	m_pSprite = g_pSpriteManager->CreateSpriteObject((uint)id);
	m_pSprite->m_X = posX;
	m_pSprite->m_Y = posY;
	m_pSprite->m_ScaleX = scaleX;
	m_pSprite->m_ScaleY = scaleY;
}

void GameObject::Cleanup()
{
	if (!m_pSprite ||  !m_pParent)
		return;

	if (m_pParent->IsChild(m_pSprite))
		m_pParent->RemoveChild(m_pSprite);

	g_pSpriteManager->DeleteSpriteObject(m_pSprite);
	
	m_pSprite = 0;
	m_pParent = 0;
	m_destroyMe = false;
}

void GameObject::Update()
{
	if (m_destroyMe || !m_pSprite)
		return;

}


void GameObject::AddTo(CNode *pContainer)
{
	if (!m_pSprite || !pContainer)
		return;

	pContainer->AddChild(m_pSprite);
	m_pParent = pContainer;
}

void GameObject::AddAlpha(float amount){
	if (!m_pSprite)
		return;

	m_pSprite->m_Alpha += amount;
	if (m_pSprite->m_Alpha < 0){
		m_pSprite->m_Alpha = 0;
	}else if (m_pSprite->m_Alpha > 1.0f){
		m_pSprite->m_Alpha = 1.0f;
	}
}

void GameObject::SetAlpha(float newAlpha){
	if (!m_pSprite)
		return;

	m_pSprite->m_Alpha = newAlpha;
	if (m_pSprite->m_Alpha < 0){
		m_pSprite->m_Alpha = 0;
	}else if (m_pSprite->m_Alpha > 1.0f){
		m_pSprite->m_Alpha = 1.0f;
	}
}

void GameObject::SetVisible(bool visible){
	if (!m_pSprite)
		return;

	m_pSprite->m_IsVisible = visible;
}

bool GameObject::CheckHit(GameObject* pGameObject){
	if (g_pSpriteManager->Intersects(m_pSprite, pGameObject->GetSprite()))
		return true;
	return false;
}