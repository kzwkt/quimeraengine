
#ifndef __QKEYBOARD__
#define __QKEYBOARD__

#include "QuimeraEngineIncludesAndUsings.h"
#include <Windows.h>

class QKeyboard
{
    typedef WPARAM OsKeyCode;

public:

    enum EQKeyEventType
    {
        E_KeyPressed,
        E_KeyReleased,
        E_KeyKept
    };

    enum EQKeyCode
    {
        E_UP,
        E_DOWN,
        E_LEFT,
        E_RIGHT,
        E_A,
        E_B,
        E_C,
        E_D,
        E_E,
        E_F,
        E_G,
        E_H,
        E_I,
        E_J,
        E_K,
        E_L,
        E_M,
        E_N,
        E_O,
        E_P,
        E_Q,
        E_R,
        E_S,
        E_T,
        E_U,
        E_V,
        E_W,
        E_X,
        E_Y,
        E_Z,
        E_1,
        E_2,
        E_3,
        E_4,
        E_5,
        E_6,
        E_7,
        E_8,
        E_9,
        E_0,
        E_ENTER,
        E_ESCAPE,
        E_SPACEBAR,
        E_TAB,
        E_LEFTSHIFT,
        E_LEFTCONTROL,
        E_RIGHTSHIFT,
        E_RIGHTCONTROL,
        E_BACK,
        E_LEFTALT,
        E_RIGHTALT
    };

    struct KeyInfo
    {
        QTimeSpan TimeElapsedSinceLastEvent;
        QTimeSpan TimePressed;
        QTimeSpan Timestamp;
        EQKeyCode Code;
        EQKeyEventType EventType;
        char_q Character;
        bool HasCharacter;
    };

public:

    QKeyboard() : m_lastEventTime(0),
                  m_idleTimeBeforeClearing(0, 0, 1, 0, 0, 0, 0) // 1 minute
    {
        m_stopwatch.Set();

        static bool bInitialized = false;

        if (!bInitialized)
        {
            KEY_CODES.Add(VK_UP, E_UP);
            KEY_CODES.Add(VK_DOWN, E_DOWN);
            KEY_CODES.Add(VK_LEFT, E_LEFT);
            KEY_CODES.Add(VK_RIGHT, E_RIGHT);
            KEY_CODES.Add(0x41, E_A);
            KEY_CODES.Add(0x42, E_B);
            KEY_CODES.Add(0x43, E_C);
            KEY_CODES.Add(0x44, E_D);
            KEY_CODES.Add(0x45, E_E);
            KEY_CODES.Add(0x46, E_F);
            KEY_CODES.Add(0x47, E_G);
            KEY_CODES.Add(0x48, E_H);
            KEY_CODES.Add(0x49, E_I);
            KEY_CODES.Add(0x4A, E_J);
            KEY_CODES.Add(0x4B, E_K);
            KEY_CODES.Add(0x4C, E_L);
            KEY_CODES.Add(0x4D, E_M);
            KEY_CODES.Add(0x4E, E_N);
            KEY_CODES.Add(0x4F, E_O);
            KEY_CODES.Add(0x50, E_P);
            KEY_CODES.Add(0x51, E_Q);
            KEY_CODES.Add(0x52, E_R);
            KEY_CODES.Add(0x53, E_S);
            KEY_CODES.Add(0x54, E_T);
            KEY_CODES.Add(0x55, E_U);
            KEY_CODES.Add(0x56, E_V);
            KEY_CODES.Add(0x57, E_W);
            KEY_CODES.Add(0x58, E_X);
            KEY_CODES.Add(0x59, E_Y);
            KEY_CODES.Add(0x5A, E_Z);
            KEY_CODES.Add(VK_LCONTROL, E_LEFTCONTROL);
            KEY_CODES.Add(VK_RCONTROL, E_RIGHTCONTROL);
            KEY_CODES.Add(VK_LMENU, E_LEFTALT);
            KEY_CODES.Add(VK_RMENU, E_RIGHTALT);
            KEY_CODES.Add(VK_TAB, E_TAB);
            KEY_CODES.Add(VK_BACK, E_BACK);
            KEY_CODES.Add(VK_LSHIFT, E_LEFTSHIFT);
            KEY_CODES.Add(VK_RSHIFT, E_RIGHTSHIFT);
            KEY_CODES.Add(VK_ESCAPE, E_ESCAPE);
            KEY_CODES.Add(VK_SPACE, E_SPACEBAR);
            KEY_CODES.Add(VK_RETURN, E_ENTER);

            bInitialized = true;
        }
    }

    bool IsDown(const EQKeyCode keyCode) const
    {
        QArrayDynamic<KeyInfo>::Iterator itLastKeyDown = m_arKeyEvents.GetLast();

        while (!itLastKeyDown.IsEnd() && itLastKeyDown->Code != keyCode)
            --itLastKeyDown;

        return !itLastKeyDown.IsEnd() && itLastKeyDown->EventType != E_KeyReleased;
    }

    bool IsUp(const EQKeyCode keyCode) const
    {
        QArrayDynamic<KeyInfo>::Iterator itLastKeyDown = m_arKeyEvents.GetLast();

        while (!itLastKeyDown.IsEnd() && itLastKeyDown->Code != keyCode)
            --itLastKeyDown;

        return itLastKeyDown.IsEnd() || itLastKeyDown->EventType == E_KeyReleased;
    }

    void Update(UINT message, WPARAM wParam, LPARAM lParam)
    {
        QTimeSpan elapsedTime = m_stopwatch.GetElapsedTimeAsTimeSpan();

        if (elapsedTime - m_lastEventTime >= m_idleTimeBeforeClearing)
        {
            this->Clear();
            m_lastEventTime = elapsedTime;
        }

        switch (message)
        {
        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
        
            // The only way to distinguish among left and right variant is by checking the highest order bit of the state of the key
            if (wParam == VK_SHIFT)
                wParam = ::GetKeyState(VK_LSHIFT) & 0x8000 ? VK_LSHIFT : VK_RSHIFT;
            else if (wParam == VK_MENU)
                wParam = ::GetKeyState(VK_LMENU) & 0x8000 ? VK_LMENU : VK_RMENU;
            else if (wParam == VK_CONTROL)
                wParam = ::GetKeyState(VK_LCONTROL) & 0x8000 ? VK_LCONTROL : VK_RCONTROL;


            if (lParam & (1UL << 30UL)) // The bit 30 indicates what was the previous state of the key (1 == already pressed)
                this->UpdateWhenKeyKept(QKeyboard::TranslateKeyCode(wParam), elapsedTime);
            else
                this->UpdateWhenKeyPressed(QKeyboard::TranslateKeyCode(wParam), elapsedTime);

            m_lastEventTime = elapsedTime;
            break;
        
        case WM_SYSCHAR:
        case WM_UNICHAR:
        case WM_CHAR:

            UpdateCharacter(wParam);
            m_lastEventTime = elapsedTime;
            break;

        case WM_SYSKEYUP:
        case WM_KEYUP:

            // It's not possible to know which of both, left or right keys, was released just using the Windows' message , so it's necessary to figure it out by looking at the event queue
            if (wParam == VK_SHIFT)
                wParam = GetLeftOrRightKey(VK_SHIFT, VK_LSHIFT, VK_RSHIFT);
            else if (wParam == VK_CONTROL)
                wParam = GetLeftOrRightKey(VK_CONTROL, VK_LCONTROL, VK_RCONTROL);
            else if (wParam == VK_MENU)
                wParam = GetLeftOrRightKey(VK_MENU, VK_LMENU, VK_RMENU);

            this->UpdateWhenKeyReleased(QKeyboard::TranslateKeyCode(wParam), elapsedTime);
            m_lastEventTime = elapsedTime;
            break;
        }
    }

    void Clear()
    {
        m_arKeyEvents.Clear();

        QE_LOG("LOG: Keyboard cache cleared.\n");
    }

    QEvent<void(const QKeyboard*, const KeyInfo&)> KeyPressedEvent;
    QEvent<void(const QKeyboard*, const KeyInfo&)> KeyKeptEvent;
    QEvent<void(const QKeyboard*, const KeyInfo&)> KeyReleasedEvent;

protected:

    void UpdateCharacter(const WPARAM wParam)
    {
        QArrayDynamic<KeyInfo>::Iterator lastKeyEvent = m_arKeyEvents.GetLast();
        lastKeyEvent->HasCharacter = true;
        lastKeyEvent->Character = (u32_q)wParam;

        if (lastKeyEvent->EventType == E_KeyPressed)
        {
            this->KeyPressedEvent.Raise(this, *lastKeyEvent);
        }
        else if (lastKeyEvent->EventType == E_KeyKept)
        {
            this->KeyKeptEvent.Raise(this, *lastKeyEvent);
        }
    }

    void UpdateWhenKeyReleased(const EQKeyCode keyCode, const QTimeSpan elapsedTime)
    {
        QArrayDynamic<KeyInfo>::Iterator itLastKeyDown = m_arKeyEvents.GetLast();

        while (!itLastKeyDown.IsEnd() && itLastKeyDown->Code != keyCode)
            --itLastKeyDown;

        QE_ASSERT_WARNING(!itLastKeyDown.IsEnd(), "There is an inconsistency in the keyboard event queue.");

        KeyInfo info;
        info.Code = keyCode;
        info.EventType = E_KeyReleased;
        info.Character = 0;
        info.HasCharacter = false;
        info.Timestamp = elapsedTime;
        info.TimeElapsedSinceLastEvent = elapsedTime - m_lastEventTime;
        info.TimePressed = itLastKeyDown->TimePressed + elapsedTime - itLastKeyDown->Timestamp;

        m_arKeyEvents.Add(info);
        this->KeyReleasedEvent.Raise(this, info);
    }

    void UpdateWhenKeyPressed(const EQKeyCode keyCode, const QTimeSpan elapsedTime)
    {
        KeyInfo info;
        info.Code = keyCode;
        info.EventType = E_KeyPressed;
        info.Character = 0;
        info.HasCharacter = false;
        info.Timestamp = elapsedTime;
        info.TimeElapsedSinceLastEvent = elapsedTime - m_lastEventTime;
        info.TimePressed = QTimeSpan(0);

        m_arKeyEvents.Add(info);
        this->KeyPressedEvent.Raise(this, info);
    }

    void UpdateWhenKeyKept(const EQKeyCode keyCode, const QTimeSpan elapsedTime)
    {
        QArrayDynamic<KeyInfo>::Iterator itLastKeyDown = m_arKeyEvents.GetLast();

        while (!itLastKeyDown.IsEnd() && itLastKeyDown->Code != keyCode)
            --itLastKeyDown;

        QE_ASSERT_WARNING(!itLastKeyDown.IsEnd(), "There is an inconsistency in the keyboard event queue.");

        if (!itLastKeyDown.IsEnd())
        {
            if (itLastKeyDown->EventType == E_KeyPressed)
            {
                KeyInfo info;
                info.Code = keyCode;
                info.EventType = E_KeyKept;
                info.Character = 0;
                info.HasCharacter = false;
                info.Timestamp = elapsedTime;
                info.TimeElapsedSinceLastEvent = elapsedTime - m_lastEventTime;
                info.TimePressed = elapsedTime - itLastKeyDown->Timestamp;

                m_arKeyEvents.Add(info);
                this->KeyKeptEvent.Raise(this, info);
            }
            else if (itLastKeyDown->EventType == E_KeyKept)
            {
                itLastKeyDown->TimeElapsedSinceLastEvent = elapsedTime - m_lastEventTime;
                itLastKeyDown->TimePressed += elapsedTime - itLastKeyDown->Timestamp;
                itLastKeyDown->Timestamp = elapsedTime;

                this->KeyKeptEvent.Raise(this, *itLastKeyDown);
            }
        }
    }

    static EQKeyCode TranslateKeyCode(OsKeyCode uKeyCode)
    {
        return KEY_CODES[uKeyCode];
    }

    WPARAM GetLeftOrRightKey(const WPARAM uKeyCode, const WPARAM uLeftKeyCode, const WPARAM uRightKeyCode) const
    {
        WPARAM uResult = uKeyCode;

        // Checks which is the last event of both, right and left keys
        const EQKeyCode LEFT_KEY = QKeyboard::TranslateKeyCode(uLeftKeyCode);
        const EQKeyCode RIGHT_KEY = QKeyboard::TranslateKeyCode(uRightKeyCode);

        QArrayDynamic<KeyInfo>::Iterator itLastLeftKeyDown = m_arKeyEvents.GetLast();

        while (!itLastLeftKeyDown.IsEnd() && itLastLeftKeyDown->Code != LEFT_KEY)
            --itLastLeftKeyDown;

        QArrayDynamic<KeyInfo>::Iterator itLastRightKeyDown = m_arKeyEvents.GetLast();

        while (!itLastRightKeyDown.IsEnd() && itLastRightKeyDown->Code != RIGHT_KEY)
            --itLastRightKeyDown;

        bool bLeftIsUp = itLastLeftKeyDown.IsEnd() || itLastLeftKeyDown->EventType == E_KeyReleased;
        bool bRightIsUp = itLastRightKeyDown.IsEnd() || itLastRightKeyDown->EventType == E_KeyReleased;

        // Both keys should not be already released, it makes no sense
        QE_ASSERT_ERROR(!bLeftIsUp || bLeftIsUp != bRightIsUp, "There is an inconsistency int he keyboard event queue, a \"Key released\" event arrived but both, left and right keys, are already up.");

        if (!bLeftIsUp && !bRightIsUp)
        {
            // If both are pressed until now, check which is still pressed, so the key-up event corresponds to the other key
            uResult = ::GetKeyState(uLeftKeyCode) & 0x8000 ? uLeftKeyCode : uRightKeyCode;
        }
        else
        {
            // If a key-released event is found before a key-pressed or key-kept event, that key is already released so the event corresponds to the other key
            uResult = bLeftIsUp ? uRightKeyCode : uLeftKeyCode;
        }

        return uResult;
    }


    static QDictionary<OsKeyCode, EQKeyCode> KEY_CODES;
    QArrayDynamic<KeyInfo> m_arKeyEvents;
    QStopwatch m_stopwatch;
    QTimeSpan m_lastEventTime;
    QTimeSpan m_idleTimeBeforeClearing;

};

#endif // __QKEYBOARD__