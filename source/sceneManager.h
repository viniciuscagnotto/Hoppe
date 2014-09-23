#ifndef __SCENE_H__
#define __SCENE_H__

class Scene : public CNode
{
public:
	enum EScenes{
		kScene_None = 0,
		kScene_MainMenu,
		kScene_Options,
		kScene_Gameplay,
		kScene_Store,
		kScene_Tutorial,
		kScene_GameOver,
		kScene_IAP,

		kScene_Count
	};

protected:
	SpriteObject *m_pBackground;

    bool m_isActive; // Active state
    bool m_isInputActive; // Input active state
    CTweenManager m_tweener; // Scene local tween manager
    TimerManager m_timers; // Timers manager
	EScenes m_type;
	
public:
    bool IsActive() const { return m_isActive; }
    void SetActive(bool active) { m_isActive = active; }
    void SetInputActive(bool active) { m_isInputActive = active; }
    CTweenManager& GetTweener() { return m_tweener; }
    TimerManager& GetTimers() { return m_timers; }

	void SetType(EScenes sceneType) { m_type = sceneType; };
	EScenes GetType(){ return m_type; };

	bool CheckCurrent();
	bool CheckTouch();
	void SwitchTo(EScenes sceneType);
	void SafeDeleteObject(SpriteObject *pSpriteObject);
	
public:
    Scene();
	Scene(EScenes sceneType);
    virtual ~Scene();

    virtual void Init();
	virtual void Cleanup();
    virtual void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
    virtual void Render();
	virtual void HandleTouch();

};

class SceneManager
{
protected:
    Scene* m_pCurrent; // Currently active scene
    Scene* m_pNext; // Next scene (scene that is being switched to)
    std::list<Scene*> m_scenes; // Scenes list
public:
    Scene* GetCurrent() { return m_pCurrent; }

public:
    SceneManager();
    ~SceneManager();

	void Init();
    void SwitchTo(Scene* pScene);
    void Update(float deltaTime = 0.0f);
    void Render();
	void Add(Scene* pScene);
	void Remove(Scene* pScene);
    Scene* Find(Scene::EScenes type);

	void Resume();

    // Internal
    static void OnSwitchComplete(CTween* pTween);
    void FinishSwitch();
};

extern SceneManager* g_pSceneManager;

#endif  // __SCENE_H__

