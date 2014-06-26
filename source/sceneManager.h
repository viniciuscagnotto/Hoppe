#if !defined(__SCENE_H__)
#define __SCENE_H__

class SceneManager;

class Scene : public CNode
{
public:
	enum EScenes{
		kScene_None = 0,
		kScene_MainMenu,
		kScene_Options,
		kScene_Game,
		kScene_Stuff,

		kScene_Count
	};

protected:
    bool m_IsActive; // Active state
    bool m_IsInputActive; // Input active state
    CTweenManager m_Tweener; // Scene local tween manager
    TimerManager m_Timers; // Timers manager
	EScenes m_type;
	
public:
    bool IsActive() const { return m_IsActive; }
    void SetActive(bool active) { m_IsActive = active; }
    void SetInputActive(bool active) { m_IsInputActive = active; }
    CTweenManager& GetTweener() { return m_Tweener; }
    TimerManager& GetTimers() { return m_Timers; }

	void SetType(EScenes sceneType) { m_type = sceneType; };
	EScenes GetType(){ return m_type; };

	bool CheckCurrent();
	bool CheckTouch();
	void SwitchTo(EScenes sceneType);
	void SafeDeleteObject(SpriteObject *pSpriteObject);
	
public:
    Scene();
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
    Scene* m_Current; // Currently active scene
    Scene* m_Next; // Next scene (scene that is being switched to)
    std::list<Scene*> m_Scenes; // Scenes list
public:
    Scene* GetCurrent() { return m_Current; }

public:
    SceneManager();
    ~SceneManager();

	void Init();
    void SwitchTo(Scene* scene);
    void Update(float deltaTime = 0.0f);
    void Render();
	void Add(Scene* scene);
	void Remove(Scene* scene);
    Scene* Find(Scene::EScenes type);

	void Resume();

    // Internal
    static void OnSwitchComplete(CTween* pTween);
    void FinishSwitch();
};

extern SceneManager* g_pSceneManager;

#endif  // __SCENE_H__

