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

#include "timer.h"
#include "IwHashString.h"

Timer::Timer(float length, int repeat_count, Callback on_timeout, void* user_data) : m_Manager(0)
{
    m_Length = length;
    m_TimeLeft = length;
    m_OnTimeout = on_timeout;
    m_UserData = user_data;
    m_RepeatCount = repeat_count;
    m_Paused = false;
}

bool Timer::Update(float deltaTime)
{
    if (m_Paused)
        return false;

    m_TimeLeft -= deltaTime;
    if (m_TimeLeft <= 0)
    {
        if (m_OnTimeout != 0)
            m_OnTimeout(this, m_UserData);
        if (m_RepeatCount > 0)
        {
            m_RepeatCount--;
            if (m_RepeatCount == 0)
                return true;
        }
        m_TimeLeft += m_Length;
    }

    return false;
}

void Timer::Pause()
{
    m_Paused = true;
}

void Timer::Resume()
{
    m_Paused = false;
}


TimerManager::TimerManager()
{
}

TimerManager::~TimerManager()
{
    for (std::list<Timer*>::iterator it = m_Timers.begin(); it != m_Timers.end(); ++it)
        delete *it;
}

void TimerManager::Update(float deltaTime)
{
    for (std::list<Timer*>::iterator it = m_Timers.begin(); it != m_Timers.end(); ++it)
    {
        if ((*it)->Update(deltaTime))
        {
            delete *it;
            it = m_Timers.erase(it);
        }
    }
}

void TimerManager::Add(Timer* timer)
{
    m_Timers.push_back(timer);
    timer->setManager(this);
}

void TimerManager::Cancel(Timer* timer)
{
    m_Timers.remove(timer);
}

void TimerManager::Clear()
{
    for (std::list<Timer*>::iterator it = m_Timers.begin(); it != m_Timers.end(); ++it)
        delete *it;
    m_Timers.clear();
}

Timer* TimerManager::Find(const char* name)
{
    unsigned int name_hash = IwHashString(name);
    for (std::list<Timer*>::iterator it = m_Timers.begin(); it != m_Timers.end(); ++it)
    {
        if ((*it)->getNameHash() == name_hash)
            return *it;
    }

    return NULL;
}

void TimerManager::Pause()
{
    for (std::list<Timer*>::iterator it = m_Timers.begin(); it != m_Timers.end(); ++it)
        (*it)->Pause();
}

void TimerManager::Resume()
{
    for (std::list<Timer*>::iterator it = m_Timers.begin(); it != m_Timers.end(); ++it)
        (*it)->Resume();
}
