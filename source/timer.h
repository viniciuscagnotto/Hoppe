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

#if !defined(__TIMER_H__)
#define __STIMER_H__

#include <list>

class TimerManager;

/**
 * @class Timer
 *
 * @brief A Timer.
 *
 * Timers are objects that are used to sleep for a specified period of time then awake and notify the system that they have timed out.
 * Timers can be one shot (by default) or made to repeat any number of times, including an infinite number of times.
 *
 * Example usage:
 *
 *    void TimerTimedOut(Timer* timer, void* userData)
 *    {
 *        printf("Timer timed out\n");
 *    }
 *    MyTimerManager.Add(new Timer(2.0f, 5, &TimerTimedOut));
 *
 * The above timer will print "Timer timedout" every two seconds for 10 seconds.
 *
 */

class Timer
{
public:
    typedef void (*Callback)(Timer* pTimer, void* userData);

protected:
    unsigned int    m_NameHash;         // Timer name
    TimerManager*   m_Manager;          // Timer manager
    float           m_Length;           // Timer length
    float           m_TimeLeft;         // Current time left on timer
    Callback        m_OnTimeout;        // Timer timeout callback
    void*           m_UserData;         // Timer timeout callback user data
    int             m_RepeatCount;      // Number of times to repeat timer
    bool            m_Paused;           // Paused state

public:
    void            setManager(TimerManager* manager)       { m_Manager = manager; }
    unsigned int    getNameHash() const                     { return m_NameHash; }
    void            setLength(float length)                 { m_Length = length; m_TimeLeft = length; }
    void            setOnTimeout(Callback callback)         { m_OnTimeout = callback; }
    float           getLength() const                       { return m_Length; }
    float           getTimeLeft() const                     { return m_TimeLeft; }
    void            setRepeatCount(int count)               { m_RepeatCount = count; }
    bool            isPaused() const                        { return m_Paused; }

public:
    Timer() : m_Manager(0), m_Length(0), m_TimeLeft(0), m_OnTimeout(0), m_UserData(0), m_RepeatCount(1), m_Paused(false) {}
    Timer(float length, int repeat_count = 1, Callback on_timeout = 0, void* user_data = 0);

    /**
     * @fn    bool Timer::Update(float deltaTime = 0.0f);
     *
     * @brief Update the timer.
     *
     * @param deltaTime   (optional) amount of time that has passed since Update() was last called.
     *
     * @return    true if it succeeds, false if it fails.
     */
    bool    Update(float deltaTime = 0.0f);

    /**
     * @fn    void Timer::Pause();
     *
     * @brief Pauses this timer.
     */
    void    Pause();

    /**
     * @fn    void Timer::Resume();
     *
     * @brief Resumes this timer.
     */
    void    Resume();

};

/**
 * @class TimerManager
 *
 * @brief Manages a collection of timers.
 */
class TimerManager
{
protected:
    std::list<Timer*>   m_Timers;       // Timers list

public:
    TimerManager();
    ~TimerManager();

    /**
     * @fn    void TimerManager::Update(float deltaTime = 0.0f);
     *
     * @brief Updates all timers that are managed by this this timer manager.
     *
     * @param deltaTime   (optional) time of the delta.
     */
    void    Update(float deltaTime = 0.0f);
    /**
     * @fn    void TimerManager::Add(Timer* timer);
     *
     * @brief Adds a timer to this manager.
     *
     * @param timer   If non-null, the timer to add.
     */
    void    Add(Timer* timer);

    /**
     * @fn    void TimerManager::Cancel(Timer* timer);
     *
     * @brief Cancels the supplied timer and destroys it.
     *
     * @param timer   If non-null, the timer.
     */
    void    Cancel(Timer* timer);

    /**
     * @fn    void TimerManager::Clear();
     *
     * @brief Cancels and destroys all timers managed by this manager.
     */
    void    Clear();

    /**
     * @fn    Timer* TimerManager::Find(const char* name);
     *
     * @brief Finds the named timer.
     *
     * @param name    The name of the timer.
     *
     * @return    null if it fails, else the timer.
     */
    Timer*  Find(const char* name);

    /**
     * @fn    void TimerManager::Pause();
     *
     * @brief Pauses all timers managed by this timer manager.
     */
    void    Pause();

    /**
     * @fn    void TimerManager::Resume();
     *
     * @brief Resumes all timers managed by this timer manager.
     */
    void    Resume();

};


#endif  // __SCENE_H__


