#ifndef _INPUT_MANAGER_H__
#define _INPUT_MANAGER_H__

#define MAX_TOUCHES 10

class InputManager
{
public:
    int m_X, m_Y; // Touched position
    bool m_Touched; // Touched status
    bool m_PrevTouched; // Previous touched status

public:
	InputManager();

    void Update();
    void Reset();

    // Callbacks
    static void TouchButtonCB(s3ePointerEvent* event);
    static void TouchMotionCB(s3ePointerMotionEvent* event);
    static void MultiTouchButtonCB(s3ePointerTouchEvent* event);
    static void MultiTouchMotionCB(s3ePointerTouchMotionEvent* event);
};

extern InputManager* g_pInput;

#endif  // _INPUT_MANAGER_H__
