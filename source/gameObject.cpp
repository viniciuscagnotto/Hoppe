#include "include.h"

GameObject::GameObject() :m_pParent(0),
m_pSprite1(0),
m_pSprite2(0),
m_speed(0.0f),
m_destroyMe(false)
{

}

GameObject::~GameObject()
{
	Cleanup();
}

void GameObject::Init(ResourceManager::EResources id, float posX, float posY, float scaleX = 1.0f, float scaleY = 1.0f)
{
	m_pSprite1 = g_pSpriteManager->CreateSpriteObject(id);
	m_pSprite1->m_X = posX;
	m_pSprite1->m_Y = posY;
	m_pSprite1->m_ScaleX = scaleX;
	m_pSprite1->m_ScaleY = scaleY;

	m_pSprite2 = g_pSpriteManager->CreateSpriteObject(id);
	m_pSprite2->m_X = posX - IwGxGetScreenWidth();
	m_pSprite2->m_Y = posY;
	m_pSprite2->m_ScaleX = scaleX;
	m_pSprite2->m_ScaleY = scaleY;
}

void GameObject::Cleanup()
{
	if (!m_pSprite1 || !m_pSprite2 || !m_pParent)
		return;

	m_pParent->SafeDeleteObject(m_pSprite1);
	m_pParent->SafeDeleteObject(m_pSprite2);

	m_pSprite1 = 0;
	m_pSprite2 = 0;
	m_pParent = 0;
}

void GameObject::Update()
{
	if (!m_pSprite1 || !m_pSprite2)
		return; 

	m_pSprite1->m_X += m_speed;
	m_pSprite2->m_X += m_speed;

	if (m_speed > 0){ // Going Right
		if (m_pSprite1->m_X - m_pSprite1->m_W * 0.5f > IwGxGetScreenWidth())
			m_pSprite1->m_X = m_pSprite2->m_X - IwGxGetScreenWidth();

		if (m_pSprite2->m_X - m_pSprite2->m_W * 0.5f > IwGxGetScreenWidth())
			m_pSprite2->m_X = m_pSprite1->m_X - IwGxGetScreenWidth();

	}else if (m_speed < 0){ // Going Left
		if (m_pSprite1->m_X + m_pSprite1->m_W * 0.5f < 0)
			m_pSprite1->m_X = m_pSprite2->m_X + IwGxGetScreenWidth();

		if (m_pSprite2->m_X + m_pSprite2->m_W * 0.5f < 0)
			m_pSprite2->m_X = m_pSprite1->m_X + IwGxGetScreenWidth();
	}else{
		if (m_pSprite1->m_X > IwGxGetScreenWidth() * 0.5f)
			m_pSprite2->m_X = m_pSprite1->m_X - IwGxGetScreenWidth();

		if (m_pSprite1->m_X < IwGxGetScreenWidth() * 0.5f)
			m_pSprite2->m_X = m_pSprite1->m_X + IwGxGetScreenWidth();
	}

}


void GameObject::AddTo(Scene *pScene)
{
	if (!m_pSprite1 || !m_pSprite2)
		return;

	pScene->AddChild(m_pSprite1);
	pScene->AddChild(m_pSprite2);
	
	m_pParent = pScene;
}

void GameObject::ChangeAlpha(float amount){
	if (!m_pSprite1 || !m_pSprite2)
		return;

	m_pSprite1->m_Alpha += amount;
	m_pSprite2->m_Alpha += amount;
}

bool GameObject::CheckHit(GameObject* gameObject){

	if (CheckHit(gameObject->GetSprite1()))
		return true;

	if (CheckHit(gameObject->GetSprite2()))
		return true;

	return false;
}

bool GameObject::CheckHit(SpriteObject* spriteObject){

	float leftPosX = spriteObject->m_X - spriteObject->m_W * 0.5f;
	float rightPosX = spriteObject->m_X + spriteObject->m_W * 0.5f;

	float upPosX = spriteObject->m_Y - spriteObject->m_H * 0.5f;
	float downPosX = spriteObject->m_Y + spriteObject->m_H * 0.5f;

	if (m_pSprite1->HitTest(leftPosX, upPosX) ||
		m_pSprite1->HitTest(leftPosX, downPosX) ||
		m_pSprite1->HitTest(rightPosX, upPosX) ||
		m_pSprite1->HitTest(rightPosX, downPosX) ||
		m_pSprite2->HitTest(leftPosX, upPosX) ||
		m_pSprite2->HitTest(leftPosX, downPosX) ||
		m_pSprite2->HitTest(rightPosX, upPosX) ||
		m_pSprite2->HitTest(rightPosX, downPosX))
		return true;

	return false;
}