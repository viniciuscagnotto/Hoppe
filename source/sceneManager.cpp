#include "header.h"

SceneManager* g_pSceneManager = 0;

Scene::Scene() : m_isActive(true), m_isInputActive(false)
{

}

Scene::Scene(Scene::EScenes sceneType) : m_type(sceneType),  m_isActive(true), m_isInputActive(false)
{

}

Scene::~Scene()
{

}

void Scene::Init()
{
	m_X = 0;
	m_isActive = true;
	m_isInputActive = true;
}

void Scene::Cleanup()
{
	m_isActive = false;
	m_isInputActive = false;
}

void Scene::Update(float deltaTime, float alphaMul)
{
    if (!m_isActive)
        return;

    m_tweener.Update(deltaTime);
    m_timers.Update(deltaTime);

    CNode::Update(deltaTime, alphaMul);
}

void Scene::Render()
{
    CNode::Render();
}

bool Scene::CheckCurrent()
{
	if (g_pSceneManager->GetCurrent() == this && m_isActive)
	{
		return true;
	}
	
	return false;
}

bool Scene::CheckTouch()
{
	if (m_isInputActive && !g_pInput->m_touched && g_pInput->m_prevTouched)
		return true;

	return false;	
}

void Scene::HandleTouch()
{
	g_pInput->Reset();
}

void Scene::SwitchTo(Scene::EScenes sceneType)
{
	g_pSceneManager->SwitchTo(g_pSceneManager->Find(sceneType));
}

void Scene::SafeDeleteObject(SpriteObject *pSpriteObject)
{
	if (!pSpriteObject)
		return;

	if (IsChild(pSpriteObject))
		RemoveChild(pSpriteObject);

	g_pSpriteManager->DeleteSpriteObject(pSpriteObject);
}

SceneManager::SceneManager() : m_pCurrent(0), m_pNext(0)
{
	Init();
}

SceneManager::~SceneManager()
{
	for (std::list<Scene*>::iterator it = m_scenes.begin(); it != m_scenes.end(); ++it)
        delete *it;
}

void SceneManager::Init(){
	Add(new MainMenu());
	Add(new Options());
	Add(new Store());
	Add(new Customize());
	Add(new Items());
	Add(new IAP());
	Add(new Gameplay());
}

void SceneManager::Add(Scene* pScene)
{
	m_scenes.push_back(pScene);
}

void SceneManager::Remove(Scene* pScene)
{
	m_scenes.remove(pScene);
}

Scene* SceneManager::Find(Scene::EScenes type)
{
    for (std::list<Scene*>::iterator it = m_scenes.begin(); it != m_scenes.end(); ++it)
    {
		if ((*it)->GetType() == type)
            return *it;
    }

    return 0;
}

void SceneManager::Update(float deltaTime)
{
	for (std::list<Scene*>::iterator it = m_scenes.begin(); it != m_scenes.end(); ++it)
        (*it)->Update(deltaTime);
}

void SceneManager::Render()
{
	for (std::list<Scene*>::iterator it = m_scenes.begin(); it != m_scenes.end(); ++it)
        (*it)->Render();
}

void SceneManager::Resume()
{
	//TODO Save state check
	//for now, load main menu

	SwitchTo(Find(Scene::kScene_MainMenu));
}

void SceneManager::OnSwitchComplete(CTween* pTween)
{
    g_pSceneManager->FinishSwitch();
}

void SceneManager::FinishSwitch()
{
	//m_Current->Update(0);
	m_pCurrent->Cleanup();
	
	m_pNext->Init();
    m_pCurrent = m_pNext;
    m_pNext = 0;
}

void SceneManager::SwitchTo(Scene* pScene)
{
	if (!pScene)
		return;

	if (pScene == m_pCurrent)
		return;

	m_pNext = pScene;
    if (m_pCurrent == 0)
    {
        m_pCurrent = m_pNext;
		m_pCurrent->Init();
        m_pNext = 0;
    }
    else
    {
        m_pCurrent->SetInputActive(false);
		m_pNext->SetActive(true);
		m_pNext->m_Alpha = 0.0f;

		OnSwitchComplete(0);
     }
}

