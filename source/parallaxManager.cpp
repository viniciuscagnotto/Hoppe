#include "include.h"

ParallaxManager::ParallaxManager() : m_pContainer(0),
m_pSprite1(0),
m_pSprite2(0),
m_pSprite3(0),
m_speedRatio(0.0f),
m_isInitiated(false){

}

void ParallaxManager::Create(ResourceManager::EResources id, float speedRatio){
	if (m_isInitiated)
		return;

	m_speedRatio = speedRatio;
	m_pContainer = new CSprite();

	m_pSprite1 = g_pSpriteManager->CreateSpriteObject(id);
	m_pSprite1->m_AnchorX = m_pSprite1->m_AnchorY = 0;
	m_pContainer->AddChild(m_pSprite1);
	m_pSprite1->m_Y = -(m_pSprite1->m_H - IwGxGetScreenHeight());

	m_pSprite2 = g_pSpriteManager->CreateSpriteObject(id);
	m_pSprite2->m_AnchorX = m_pSprite2->m_AnchorY = 0;
	m_pContainer->AddChild(m_pSprite2);
	m_pSprite2->m_Y = m_pSprite1->m_Y - m_pSprite1->m_H;

	m_pSprite3 = g_pSpriteManager->CreateSpriteObject(id);
	m_pSprite3->m_AnchorX = m_pSprite3->m_AnchorY = 0;
	m_pContainer->AddChild(m_pSprite3);
	m_pSprite3->m_Y = m_pSprite2->m_Y - m_pSprite2->m_H;

	m_isInitiated = true;
}

void ParallaxManager::Update(float gameSpeed){
	if (!m_isInitiated)
		return;

	m_pSprite1->m_Y += (gameSpeed * m_speedRatio);
	m_pSprite2->m_Y += (gameSpeed * m_speedRatio);
	m_pSprite3->m_Y += (gameSpeed * m_speedRatio);
	
	if (m_pSprite1->m_Y > IwGxGetScreenHeight())
		m_pSprite1->m_Y = m_pSprite3->m_Y - m_pSprite3->m_H;

	if (m_pSprite2->m_Y > IwGxGetScreenHeight())
		m_pSprite2->m_Y = m_pSprite1->m_Y - m_pSprite1->m_H;

	if (m_pSprite3->m_Y > IwGxGetScreenHeight())
		m_pSprite3->m_Y = m_pSprite2->m_Y - m_pSprite2->m_H;

}

void ParallaxManager::Reset(){
	if (!m_isInitiated)
		return;

}

void ParallaxManager::Destroy(){
	if (!m_isInitiated)
		return;

	m_isInitiated = false;
	if (!m_pContainer)
		return;

	if (m_pSprite1){
		if (m_pContainer->IsChild(m_pSprite1))
			m_pContainer->RemoveChild(m_pSprite1);
		g_pSpriteManager->DeleteSpriteObject(m_pSprite1);
	}
	
	if (m_pSprite2){
		if (m_pContainer->IsChild(m_pSprite2))
			m_pContainer->RemoveChild(m_pSprite2);
		g_pSpriteManager->DeleteSpriteObject(m_pSprite2);
	}

	if (m_pSprite3){
		if (m_pContainer->IsChild(m_pSprite3))
			m_pContainer->RemoveChild(m_pSprite3);
		g_pSpriteManager->DeleteSpriteObject(m_pSprite3);
	}

	delete m_pContainer;
}