#include "core.h"

InputManager* g_pInput = 0;

void InputManager::TouchButtonCB(s3ePointerEvent* pEvent)
{
    g_pInput->m_prevTouched = g_pInput->m_touched;
	g_pInput->m_touched = pEvent->m_Pressed != 0;
	g_pInput->m_x = pEvent->m_x;
	g_pInput->m_y = pEvent->m_y;
}

void InputManager::TouchMotionCB(s3ePointerMotionEvent* pEvent)
{
	g_pInput->m_x = pEvent->m_x;
	g_pInput->m_y = pEvent->m_y;
}

void InputManager::MultiTouchButtonCB(s3ePointerTouchEvent* pEvent)
{
    g_pInput->m_prevTouched = g_pInput->m_touched;
	g_pInput->m_touched = pEvent->m_Pressed != 0;
	g_pInput->m_x = pEvent->m_x;
	g_pInput->m_y = pEvent->m_y;
}

void InputManager::MultiTouchMotionCB(s3ePointerTouchMotionEvent* pEvent)
{
	g_pInput->m_x = pEvent->m_x;
	g_pInput->m_y = pEvent->m_y;
}

InputManager::InputManager() : m_touched(false), m_prevTouched(false)
{
    // Set touch event callback handlers, single and multi-touch devices have different callbacks assigned
    if (s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE) != 0)
    {
        s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)MultiTouchButtonCB, 0);
        s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)MultiTouchMotionCB, 0);
    }
    else
    {
        s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)TouchButtonCB, 0);
        s3ePointerRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)TouchMotionCB, 0);
    }
}

void InputManager::Update()
{
    s3ePointerUpdate();
}

void InputManager::Reset()
{
    m_prevTouched = false;
    m_touched = false;
}

