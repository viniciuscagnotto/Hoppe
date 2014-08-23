#ifndef __TIMER_H__
#define __TIMER_H__

class TimerManager;

class Timer
{
public:
    typedef void (*Callback)(Timer* pTimer, void* pUserData);

protected:
    unsigned int m_nameHash; // Timer name
    TimerManager* m_pManager; // Timer manager
    float m_length; // Timer length
    float m_timeLeft; // Current time left on timer
    Callback m_onTimeout; // Timer timeout callback
    void* m_pUserData; // Timer timeout callback user data
    int m_repeatCount; // Number of times to repeat timer
	bool m_paused; // Paused state

public:
	void setManager(TimerManager* pManager)  { m_pManager = pManager; }
    unsigned int getNameHash() const { return m_nameHash; }
    void setLength(float length) { m_length = length; m_timeLeft = length; }
    void setOnTimeout(Callback callback) { m_onTimeout = callback; }
    float getLength() const { return m_length; }
    float getTimeLeft() const { return m_timeLeft; }
    void setRepeatCount(int count) { m_repeatCount = count; }
    bool isPaused() const { return m_paused; }

public:
    Timer() : m_pManager(0), m_length(0), m_timeLeft(0), m_onTimeout(0), m_pUserData(0), m_repeatCount(1), m_paused(false) {}
    Timer(float length, int repeatCount = 1, Callback onTimeout = 0, void* pUserData = 0);

    bool Update(float deltaTime = 0.0f);
	void Pause();
    void Resume();

};

class TimerManager
{
protected:
    std::list<Timer*> m_timers; // Timers list

public:
    TimerManager();
    ~TimerManager();

    void Update(float deltaTime = 0.0f);
    void Add(Timer* pTimer);
	void Cancel(Timer* pTimer);
	void Clear();
	Timer* Find(const char* name);
	void Pause();
	void Resume();
};


#endif  // __TIMER_H__
