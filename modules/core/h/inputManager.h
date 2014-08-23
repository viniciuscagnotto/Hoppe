#ifndef _INPUT_MANAGER_H__
#define _INPUT_MANAGER_H__

#define MAX_TOUCHES 10

class InputManager
{
public:
    int m_x, m_y; // Touched position
    bool m_touched; // Touched status
    bool m_prevTouched; // Previous touched status

public:
	InputManager();

    void Update();
    void Reset();

    // Callbacks
    static void TouchButtonCB(s3ePointerEvent* pEvent);
    static void TouchMotionCB(s3ePointerMotionEvent* pEvent);
    static void MultiTouchButtonCB(s3ePointerTouchEvent* pEvent);
    static void MultiTouchMotionCB(s3ePointerTouchMotionEvent* pEvent);
};

extern InputManager* g_pInput;

#endif  // _INPUT_MANAGER_H__
