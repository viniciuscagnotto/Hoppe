#include "include.h"

Input* g_pInput = 0;

void Input::TouchButtonCB(s3ePointerEvent* event)
{
    g_pInput->m_PrevTouched = g_pInput->m_Touched;
    g_pInput->m_Touched = event->m_Pressed != 0;
    g_pInput->m_X = event->m_x;
    g_pInput->m_Y = event->m_y;
}

void Input::TouchMotionCB(s3ePointerMotionEvent* event)
{
    g_pInput->m_X = event->m_x;
    g_pInput->m_Y = event->m_y;
}

void Input::MultiTouchButtonCB(s3ePointerTouchEvent* event)
{
    g_pInput->m_PrevTouched = g_pInput->m_Touched;
    g_pInput->m_Touched = event->m_Pressed != 0;
    g_pInput->m_X = event->m_x;
    g_pInput->m_Y = event->m_y;
}

void Input::MultiTouchMotionCB(s3ePointerTouchMotionEvent* event)
{
    g_pInput->m_X = event->m_x;
    g_pInput->m_Y = event->m_y;
}

Input::Input() : m_Touched(false), m_PrevTouched(false)
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

void Input::Update()
{
    s3ePointerUpdate();
}

void Input::Reset()
{
    m_PrevTouched = false;
    m_Touched = false;
}

