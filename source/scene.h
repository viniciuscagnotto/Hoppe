#if !defined(__SCENE_H__)
#define __SCENE_H__

class SceneManager;

class Scene : public CNode
{
protected:
    unsigned int m_NameHash; // Hash string representation of scene name
    bool m_IsActive; // Active state
    bool m_IsInputActive; // Input active state
    SceneManager* m_Manager; // Scene manager
    CTweenManager m_Tweener; // Scene local tween manager
    TimerManager m_Timers; // Timers manager

public:
    bool IsActive() const { return m_IsActive; }
    void SetActive(bool active) { m_IsActive = active; }
    void SetName(const char* name);
    unsigned int GetNameHash() const { return m_NameHash; }
    void SetManager(SceneManager* manager) { m_Manager = manager; }
    void SetInputActive(bool active) { m_IsInputActive = active; }
    CTweenManager& GetTweener() { return m_Tweener; }
    TimerManager& GetTimers() { return m_Timers; }

public:
    Scene();
    virtual ~Scene();

    virtual void Init();
    virtual void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
    virtual void Render();
};

class SceneManager
{
protected:
    Scene* m_Current; // Currently active scene
    Scene* m_Next; // Next scene (scene that is being switched to)
    std::list<Scene*> m_Scenes; // Scenes list
public:
    Scene*  GetCurrent() { return m_Current; }

public:
    SceneManager();
    ~SceneManager();

	void Init();
    void SwitchTo(Scene* scene);
    void Update(float deltaTime = 0.0f);
    void Render();
	void Add(Scene* scene);
	void Remove(Scene* scene);
    Scene* Find(const char* name);

    // Internal
    static void OnSwitchComplete(CTween* pTween);
    void FinishSwitch();
};

extern SceneManager* g_pSceneManager;

#endif  // __SCENE_H__

