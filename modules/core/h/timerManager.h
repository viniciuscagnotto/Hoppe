#ifndef __TIMER_H__
#define __TIMER_H__

class TimerManager;

class Timer
{
public:
    typedef void (*Callback)(Timer* pTimer, void* userData);

protected:
    unsigned int m_NameHash; // Timer name
    TimerManager* m_Manager; // Timer manager
    float m_Length; // Timer length
    float m_TimeLeft; // Current time left on timer
    Callback m_OnTimeout; // Timer timeout callback
    void* m_UserData; // Timer timeout callback user data
    int m_RepeatCount; // Number of times to repeat timer
	bool m_Paused; // Paused state

public:
    void setManager(TimerManager* manager)  { m_Manager = manager; }
    unsigned int getNameHash() const { return m_NameHash; }
    void setLength(float length) { m_Length = length; m_TimeLeft = length; }
    void setOnTimeout(Callback callback) { m_OnTimeout = callback; }
    float getLength() const { return m_Length; }
    float getTimeLeft() const { return m_TimeLeft; }
    void setRepeatCount(int count) { m_RepeatCount = count; }
    bool isPaused() const { return m_Paused; }

public:
    Timer() : m_Manager(0), m_Length(0), m_TimeLeft(0), m_OnTimeout(0), m_UserData(0), m_RepeatCount(1), m_Paused(false) {}
    Timer(float length, int repeat_count = 1, Callback on_timeout = 0, void* user_data = 0);

    bool Update(float deltaTime = 0.0f);
	void Pause();
    void Resume();

};

class TimerManager
{
protected:
    std::list<Timer*> m_Timers; // Timers list

public:
    TimerManager();
    ~TimerManager();

    void Update(float deltaTime = 0.0f);
    void Add(Timer* timer);
	void Cancel(Timer* timer);
	void Clear();
	Timer* Find(const char* name);
	void Pause();
	void Resume();
};


#endif  // __TIMER_H__
