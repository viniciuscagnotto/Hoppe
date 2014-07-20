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
		if (m_pSprite1->m_X - m_pSprite1->RealW() * 0.5f > IwGxGetScreenWidth())
			m_pSprite1->m_X = m_pSprite2->m_X - IwGxGetScreenWidth();

		if (m_pSprite2->m_X - m_pSprite2->RealW() * 0.5f > IwGxGetScreenWidth())
			m_pSprite2->m_X = m_pSprite1->m_X - IwGxGetScreenWidth();

	}else if (m_speed < 0){ // Going Left
		if (m_pSprite1->m_X + m_pSprite1->RealW() * 0.5f < 0)
			m_pSprite1->m_X = m_pSprite2->m_X + IwGxGetScreenWidth();

		if (m_pSprite2->m_X + m_pSprite2->RealW() * 0.5f < 0)
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

void GameObject::AddAlpha(float amount){
	if (!m_pSprite1 || !m_pSprite2)
		return;

	m_pSprite1->m_Alpha += amount;
	m_pSprite2->m_Alpha += amount;

	if (m_pSprite1->m_Alpha < 0){
		m_pSprite1->m_Alpha = 0;
		m_pSprite2->m_Alpha = 0;
	}else if (m_pSprite1->m_Alpha > 1.0f){
		m_pSprite1->m_Alpha = 1.0f;
		m_pSprite2->m_Alpha = 1.0f;
	}
}

void GameObject::SetAlpha(float newAlpha){
	if (!m_pSprite1 || !m_pSprite2)
		return;

	m_pSprite1->m_Alpha = newAlpha;
	m_pSprite2->m_Alpha = newAlpha;

	if (m_pSprite1->m_Alpha < 0){
		m_pSprite1->m_Alpha = 0;
		m_pSprite2->m_Alpha = 0;
	}else if (m_pSprite1->m_Alpha > 1.0f){
		m_pSprite1->m_Alpha = 1.0f;
		m_pSprite2->m_Alpha = 1.0f;
	}
}

bool GameObject::CheckHit(GameObject* gameObject){

	if (g_pSpriteManager->Intersects(m_pSprite1, gameObject->GetSprite1()) ||
		g_pSpriteManager->Intersects(m_pSprite1, gameObject->GetSprite2()) ||
		g_pSpriteManager->Intersects(m_pSprite2, gameObject->GetSprite1()) ||
		g_pSpriteManager->Intersects(m_pSprite2, gameObject->GetSprite2()))
		return true;

	return false;
}

float GameObject::GetDistanceX(GameObject* gameObject){
	SpriteObject *pInSceneObject = 0;
	SpriteObject *pInSceneObject2 = 0;

	if (m_pSprite1->IsInScene() && m_pSprite2->IsInScene()){
		if (gameObject->GetSprite1()->IsInScene() && gameObject->GetSprite2()->IsInScene()){
			pInSceneObject = m_pSprite1;
			pInSceneObject2 = gameObject->GetSprite1();
			float distance = fabsf(pInSceneObject->m_X - gameObject->GetSprite1()->m_X);
			if (fabsf(pInSceneObject->m_X - gameObject->GetSprite2()->m_X) < distance)
				pInSceneObject2 = gameObject->GetSprite2();
		}else{
			pInSceneObject2 = gameObject->GetSprite1();
			if (gameObject->GetSprite2()->IsInScene())
				pInSceneObject2 = gameObject->GetSprite2();
			
			pInSceneObject = m_pSprite1;
			float distance = fabsf(pInSceneObject2->m_X - m_pSprite1->m_X);
			if (fabsf(pInSceneObject2->m_X - m_pSprite2->m_X) < distance)
				pInSceneObject = m_pSprite2;
		}
	}else{
		pInSceneObject = m_pSprite1;
		if (m_pSprite2->IsInScene())
			pInSceneObject = m_pSprite2;

		if (gameObject->GetSprite1()->IsInScene() && gameObject->GetSprite2()->IsInScene()){
			pInSceneObject2 = gameObject->GetSprite1();
			float distance = fabsf(pInSceneObject->m_X - gameObject->GetSprite1()->m_X);
			if (fabsf(pInSceneObject->m_X - gameObject->GetSprite2()->m_X) < distance)
				pInSceneObject2 = gameObject->GetSprite2();
		}else{
			pInSceneObject2 = gameObject->GetSprite1();
			if (gameObject->GetSprite2()->IsInScene())
				pInSceneObject2 = gameObject->GetSprite2();
		}
	}
	
	if (pInSceneObject && pInSceneObject2)
		return pInSceneObject2->m_X - pInSceneObject->m_X;
	return 0;
}