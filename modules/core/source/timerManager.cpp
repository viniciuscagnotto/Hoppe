#include "core.h"

Timer::Timer(float length, int repeatCount, Callback onTimeout, void* pUserData) : m_pManager(0)
{
    m_length = length;
    m_timeLeft = length;
    m_onTimeout = onTimeout;
    m_pUserData = pUserData;
    m_repeatCount = repeatCount;
    m_paused = false;
}

bool Timer::Update(float deltaTime)
{
    if (m_paused)
        return false;

    m_timeLeft -= deltaTime;
    if (m_timeLeft <= 0)
    {
        if (m_onTimeout != 0)
            m_onTimeout(this, m_pUserData);
        if (m_repeatCount > 0)
        {
            m_repeatCount--;
            if (m_repeatCount == 0)
                return true;
        }
        m_timeLeft += m_length;
    }

    return false;
}

void Timer::Pause()
{
    m_paused = true;
}

void Timer::Resume()
{
    m_paused = false;
}


TimerManager::TimerManager()
{
}

TimerManager::~TimerManager()
{
    for (std::list<Timer*>::iterator it = m_timers.begin(); it != m_timers.end(); ++it)
        delete *it;
}

void TimerManager::Update(float deltaTime)
{
    for (std::list<Timer*>::iterator it = m_timers.begin(); it != m_timers.end(); ++it)
    {
        if ((*it)->Update(deltaTime))
        {
            delete *it;
            it = m_timers.erase(it);
        }
    }
}

void TimerManager::Add(Timer* pTimer)
{
    m_timers.push_back(pTimer);
    pTimer->setManager(this);
}

void TimerManager::Cancel(Timer* pTimer)
{
    m_timers.remove(pTimer);
}

void TimerManager::Clear()
{
    for (std::list<Timer*>::iterator it = m_timers.begin(); it != m_timers.end(); ++it)
        delete *it;
    m_timers.clear();
}

Timer* TimerManager::Find(const char* name)
{
    unsigned int nameHash = IwHashString(name);
    for (std::list<Timer*>::iterator it = m_timers.begin(); it != m_timers.end(); ++it)
    {
        if ((*it)->getNameHash() == nameHash)
            return *it;
    }

    return NULL;
}

void TimerManager::Pause()
{
    for (std::list<Timer*>::iterator it = m_timers.begin(); it != m_timers.end(); ++it)
        (*it)->Pause();
}

void TimerManager::Resume()
{
    for (std::list<Timer*>::iterator it = m_timers.begin(); it != m_timers.end(); ++it)
        (*it)->Resume();
}
