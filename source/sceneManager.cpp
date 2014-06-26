#include "include.h"

SceneManager* g_pSceneManager = 0;

Scene::Scene() : m_IsActive(true), m_IsInputActive(false)
{

}

Scene::~Scene()
{

}

void Scene::Init()
{
	m_X = 0;
	m_IsActive = true;
	m_IsInputActive = true;
}

void Scene::Cleanup()
{
	m_IsActive = false;
	m_IsInputActive = false;
}

void Scene::Update(float deltaTime, float alphaMul)
{
    if (!m_IsActive)
        return;

    m_Tweener.Update(deltaTime);
    m_Timers.Update(deltaTime);

    CNode::Update(deltaTime, alphaMul);
}

void Scene::Render()
{
    CNode::Render();
}

bool Scene::CheckCurrent()
{
	if (g_pSceneManager->GetCurrent() == this && m_IsActive)
	{
		return true;
	}
	
	return false;
}

bool Scene::CheckTouch()
{
	if (m_IsInputActive && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
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

SceneManager::SceneManager() : m_Current(0), m_Next(0)
{
	Init();
}

SceneManager::~SceneManager()
{
	for (std::list<Scene*>::iterator it = m_Scenes.begin(); it != m_Scenes.end(); ++it)
        delete *it;
}

void SceneManager::Init(){
	Add(new MainMenu());
	Add(new Options());
	Add(new Stuff());
	Add(new Game());
}

void SceneManager::Add(Scene* scene)
{
    m_Scenes.push_back(scene);
}

void SceneManager::Remove(Scene* scene)
{
    m_Scenes.remove(scene);
}

Scene* SceneManager::Find(Scene::EScenes type)
{
    for (std::list<Scene*>::iterator it = m_Scenes.begin(); it != m_Scenes.end(); ++it)
    {
		if ((*it)->GetType() == type)
            return *it;
    }

    return 0;
}

void SceneManager::Update(float deltaTime)
{
    for (std::list<Scene*>::iterator it = m_Scenes.begin(); it != m_Scenes.end(); ++it)
        (*it)->Update(deltaTime);
}

void SceneManager::Render()
{
    for (std::list<Scene*>::iterator it = m_Scenes.begin(); it != m_Scenes.end(); ++it)
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
	m_Current->Update(0); // Update one last time to ensure that last tweened values get set because on the next frame the scene will inactive
	m_Current->Cleanup();
	
	m_Next->Init();
    m_Current = m_Next;
    m_Next = 0;
}

void SceneManager::SwitchTo(Scene* scene)
{
	if (!scene)
		return;

	if (scene == m_Current)
		return;

    m_Next = scene;
    if (m_Current == 0)
    {
        m_Current = m_Next;
		m_Current->Init();
        m_Next = 0;
    }
    else
    {
        m_Current->SetInputActive(false);
		m_Next->SetActive(true);
		m_Next->m_Alpha = 0.0f;
		g_pTweener->Tween(0.5f,
						  FLOAT, &m_Current->m_Alpha, 0.0f,
						  FLOAT, &m_Next->m_Alpha, 1.0f,
						  EASING, Ease::zero,
						  ONCOMPLETE, OnSwitchComplete,
						  END);
     }
}

