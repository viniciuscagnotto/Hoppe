/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */

#include "scene.h"
#include "IwGx.h"
#include "input.h"
#include "main.h"

SceneManager* g_pSceneManager = 0;


//
//
// Scene class
//
//

Scene::Scene() : m_NameHash(0), m_IsActive(true), m_IsInputActive(false)
{
    m_X = -(float)IwGxGetScreenWidth();
}

Scene::~Scene()
{
}

void Scene::SetName(const char* name)
{
    m_NameHash = IwHashString(name);
}

void Scene::Init()
{
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

//
//
// SceneManager class
//
//
SceneManager::SceneManager() : m_Current(0), m_Next(0)
{
}

SceneManager::~SceneManager()
{
    for (std::list<Scene*>::iterator it = m_Scenes.begin(); it != m_Scenes.end(); ++it)
        delete *it;
}

void SceneManager::Add(Scene* scene)
{
    m_Scenes.push_back(scene);
    scene->SetManager(this);
}

void SceneManager::Remove(Scene* scene)
{
    m_Scenes.remove(scene);
}

Scene* SceneManager::Find(const char* name)
{
    unsigned int name_hash = IwHashString(name);
    for (std::list<Scene*>::iterator it = m_Scenes.begin(); it != m_Scenes.end(); ++it)
    {
        if ((*it)->GetNameHash() == name_hash)
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

void SceneManager::OnSwitchComplete(CTween* pTween)
{
    g_pSceneManager->FinishSwitch();
}

void SceneManager::FinishSwitch()
{
    m_Next->SetInputActive(true);
    m_Next->SetActive(true);
    m_Current->Update(0);           // Update one last time to ensure that last tweened values get set because on the next frame the scene will inactive
    m_Current->SetActive(false);
    m_Current = m_Next;
    m_Next = 0;
}

void SceneManager::SwitchTo(Scene* scene)
{
    m_Next = scene;
    if (m_Current == 0)
    {
        m_Current = m_Next;
        m_Current ->m_X = 0;
        m_Current->SetActive(true);
        m_Current->SetInputActive(true);
        m_Next = 0;
    }
    else
    {
        m_Current->SetInputActive(false);
        m_Next->SetActive(true);
        m_Next->m_X = -(float)IwGxGetScreenWidth();
        g_pTweener->Tween(0.5f,
                        FLOAT, &m_Next->m_X, 0.0f,
                        FLOAT, &m_Current->m_X, (float)IwGxGetScreenWidth(),
                        EASING, Ease::sineIn,
                        ONCOMPLETE, OnSwitchComplete,
                        END);
    }
}

