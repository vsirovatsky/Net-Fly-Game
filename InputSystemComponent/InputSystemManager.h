#pragma once

#include "inputsystemabstractmanager.h"
#include "InputSystemException.h"
#include "InputSystemTypeDefs.h"

#include "OISInputManager.h"
#include "OISException.h"
#include "OISKeyboard.h"
#include "OISMouse.h"
#include "OISJoyStick.h"
#include "OISEvents.h"

#include "OISForceFeedback.h"

#include <iostream>
#include <vector>
#include <sstream>
#include "windows.h"

using namespace OIS;

namespace inputsystem {

class InputSystemManager : public InputSystemAbstractManager, public KeyListener, public MouseListener, public JoyStickListener
{
public:
	InputSystemManager(void);
	virtual ~InputSystemManager(void);
public:
	virtual void init( HWND hWnd, int, int, bool showCursor, bool buffered, bool debugEnabled );
	virtual void capture( MouseState*, KeyboardBufferedState*, KeyboardUnbufferedState* );
public:
	//! Checks if a specific OIS key is down.
    bool isKeyDown(OIS::KeyCode key);

    //! Sets the display size to be used by OIS.
    void setDisplaySize(int width, int height);

    //! Invoked when a key is pressed.
    virtual bool keyPressed( const OIS::KeyEvent& arg );

    //! Invoked when a key is released.
    virtual bool keyReleased( const OIS::KeyEvent& arg );

    //! Invoked when the mouse is moved.
    virtual bool mouseMoved( const OIS::MouseEvent &arg );

    //! Invoked when a mouse button is pressed.
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

    //! Invoked when a mouse button is released.
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ); 

    //! Invoked when a joystick button is pressed.
    virtual bool buttonPressed( const OIS::JoyStickEvent &arg, int button );

    //! Invoked when a joystick button is released.
    virtual bool buttonReleased( const OIS::JoyStickEvent &arg, int button );

    //! Invoked when a joystick axis is moved.
    virtual bool axisMoved( const OIS::JoyStickEvent &arg, int axis );

    //! Invoked when a joystick pov is moved.
    virtual bool povMoved( const OIS::JoyStickEvent &arg, int pov );

	virtual void copyKeyStates( char keys[256] );
private:
	InputManager * pInputManager;
	Keyboard * pKeyboardHandler;
	Mouse	 * pMouseHandler;
	bool m_debugEnabled;
	bool m_GUIEnabled;
	MouseState * mouseState;
	KeyboardBufferedState * buffState;
	KeyboardUnbufferedState * unbuffState;
};

}