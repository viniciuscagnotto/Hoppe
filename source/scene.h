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

#if !defined(__SCENE_H__)
#define __SCENE_H__

#include <list>
#include "Iw2DSceneGraph.h"
#include "IwTween.h"
#include "timer.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;
using namespace IwTween;

class SceneManager;

/**
 * @class Scene
 *
 * @brief A scene acts as a parent of a group of nodes
 *
 * Scenes act as containers that store an hierarchy of CNodes. A scene also contains:
 * - A tweens manager - Enables the scene to create scene local tweens that are updated with the scene
 * - A timers manager - Enables the scene to create scene local timers that are updated with the scene
 *
 * Note that the Init(), Update() and Render() methods are meant to be overidden in your own scene class that is derived from Scene to
 * provide functionality and rendering that is specific to your own scene class.
 */
class Scene : public CNode
{
protected:
    unsigned int        m_NameHash;                     // Hash string representation of scene name
    bool                m_IsActive;                     // Active state
    bool                m_IsInputActive;                // Input active state
    SceneManager*       m_Manager;                      // Scene manager
    CTweenManager       m_Tweener;                      // Scene local tween manager
    TimerManager        m_Timers;                       // Timers manager

public:
    bool                IsActive() const                    { return m_IsActive; }
    void                SetActive(bool active)              { m_IsActive = active; }
    void                SetName(const char* name);
    unsigned int        GetNameHash() const                 { return m_NameHash; }
    void                SetManager(SceneManager* manager)   { m_Manager = manager; }
    void                SetInputActive(bool active)         { m_IsInputActive = active; }
    CTweenManager&      GetTweener()                        { return m_Tweener; }
    TimerManager&       GetTimers()                         { return m_Timers; }

public:
    Scene();
    virtual ~Scene();

    /**
     * @fn    virtual void Scene::Init();
     *
     * @brief Initialise the scene.
     */
    virtual void    Init();
    /**
     * @fn    virtual void Scene::Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
     *
     * @brief Update the scene.
     *
     * @brief Updates this scene, including tweens and animations.
     *
     * @param deltaTime   Number of seconds that has passed since Update() was last called.
     * @param alphaMul    The alpha value being passed down to this node. Default value is 1.
     */
    virtual void    Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
    /**
     * @fn    virtual void Scene::Render();
     *
     * @brief Render the scene.
     */
    virtual void    Render();
};

/**
 * @class SceneManager
 *
 * @brief Manages a collection of scenes.
 *
 * The Scene Manager manages a collection of scenes. It also manages the update and rendering of those scenes and provides a mechanism to
 * easily switch between them.
 *
 * Example usage:
 * @code
 *    // Create scene manager
 *    g_pSceneManager = new SceneManager();
 *
 *    // Create a scene (Game is a class that is derived from Scene)
 *    Game* game = new Game();
 *    game->SetName("game");
 *    g_pSceneManager->Add(game);
 *
 *    while (!s3eDeviceCheckQuitRequest())
 *    {
 *        // Update scene manager
 *        g_pSceneManager->Update(FRAME_TIME);
 *
 *        // Render scene manager
 *        g_pSceneManager->Render();
 *    }
 *
 *    // Cleanup
 *    delete g_pSceneManager;
 * @endcode
 *
 * The scene manager uses teh concept of the "current scene" where only one scene can be active at any given time. To change from one
 * scene to another you use the SwitchTo() method.
 *
 * Note that when a scene is not currently the active scene, all tweens and timers within the scene will pause execution.
 */
class SceneManager
{
protected:
    Scene*              m_Current;              // Currently active scene
    Scene*              m_Next;                 // Next scene (scene that is being switched to)
    std::list<Scene*>   m_Scenes;               // Scenes list
public:
    Scene*  GetCurrent()                { return m_Current; }

public:
    SceneManager();
    ~SceneManager();

    /**
     * @fn    void SceneManager::SwitchTo(Scene* scene);
     *
     * @brief Switch to a new scene.
     *
     * @param scene   Thew new scene.
     */
    void    SwitchTo(Scene* scene);

    /**
     * @fn    void SceneManager::Update(float deltaTime = 0.0f);
     *
     * @brief Updates all scenes managed by the manager
     *
     * @param deltaTime   Number of seconds that has passed since Update() was last called.
     */
    void    Update(float deltaTime = 0.0f);

    /**
     * @fn    void SceneManager::Render();
     *
     * @brief Renders all scenes managed by the manager
     */
    void    Render();

    /**
     * @fn    void SceneManager::Add(Scene* scene);
     *
     * @brief Adds a scene to the manager.
     *
     * @param scene   If non-null, the scene to add.
     */
    void    Add(Scene* scene);

    /**
     * @fn    void SceneManager::Remove(Scene* scene);
     *
     * @brief Removes the given scene from the scene manager.
     *
     * @param scene   If non-null, the scene to remove.
     */
    void    Remove(Scene* scene);

    /**
     * @fn    Scene* SceneManager::Find(const char* name);
     *
     * @brief Searches for the named scene.
     *
     * @param name    The name of the scene to find.
     *
     * @return    null if it fails, else the scene.
     */
    Scene*  Find(const char* name);

    // Internal
    static void OnSwitchComplete(CTween* pTween);
    void    FinishSwitch();

};

extern SceneManager* g_pSceneManager;

#endif  // __SCENE_H__

