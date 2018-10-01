#include "StdAfx.h"
#include "InputSystemManager.h"

using namespace OIS;

namespace inputsystem {


InputSystemManager::InputSystemManager(void)
{
	pInputManager = 0;
	pKeyboardHandler = 0;
	pMouseHandler = 0;
}

InputSystemManager::~InputSystemManager(void)
{
	if( pInputManager )
    {
        if(pKeyboardHandler)
            pInputManager->destroyInputObject( pKeyboardHandler );
        if(pMouseHandler)
            pInputManager->destroyInputObject( pMouseHandler );
        InputManager::destroyInputSystem(pInputManager);
    }

}

void InputSystemManager::init( HWND hWnd, int mousewidth = 100, int mouseHeight = 100, bool showCursor = false, bool buffered = true, bool debugEnabled = false)
{
	try {
		m_debugEnabled = debugEnabled;
		ParamList pl;
		std::ostringstream wnd;
		wnd << (size_t)hWnd;
		pl.insert(std::make_pair( std::string("WINDOW"), wnd.str() ));
		//Default mode is foreground exclusive..but, we want to show mouse - so nonexclusive
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
	    if(showCursor)
			pl.insert(std::make_pair("w32_mouse", "DISCL_NONEXCLUSIVE"));
		else pl.insert(std::make_pair("w32_mouse", "DISCL_EXCLUSIVE"));

		pInputManager = InputManager::createInputSystem(pl);

		pInputManager->enableAddOnFactory(InputManager::AddOn_All);

		pKeyboardHandler = (Keyboard*)pInputManager->createInputObject( OISKeyboard, buffered );
		pKeyboardHandler->setEventCallback( this );

		pMouseHandler = (Mouse*)pInputManager->createInputObject( OISMouse, buffered );
		pMouseHandler->setEventCallback( this );
		const OIS::MouseState & ms = pMouseHandler->getMouseState();
		ms.width = mousewidth;
		ms.height = mouseHeight;
	} catch ( Exception e ) {
		throw new InputSystemException("Error input system initialiazing");
	}
}

//-----------------------------------------------------------------------
//                        s e t S c r e e n S i z e
//-----------------------------------------------------------------------
void InputSystemManager::setDisplaySize(int width, int height)
{
    pMouseHandler->getMouseState().width = width;
    pMouseHandler->getMouseState().height = height;
}

//-----------------------------------------------------------------------
//                              c a p t u r e
//-----------------------------------------------------------------------
void InputSystemManager::capture( MouseState * mouseState, KeyboardBufferedState * buffState, KeyboardUnbufferedState * unbuffState)
{
	this->mouseState = mouseState;
	this->buffState = buffState;
	this->unbuffState = unbuffState;
    if(pKeyboardHandler)
        pKeyboardHandler->capture();
    if(pMouseHandler)
        pMouseHandler->capture();
	if ( this->unbuffState ) {
		copyKeyStates( this->unbuffState->keys );
	}
	if ( this->mouseState ) {
		OIS::MouseState ms = pMouseHandler->getMouseState();
		this->mouseState->click.buttons = ms.buttons;
		mouseState->moveUnbuffered.xAbs = ms.X.abs;
		mouseState->moveUnbuffered.yAbs = ms.Y.abs;
		mouseState->moveUnbuffered.zAbs = ms.Z.abs;
	}
}

//-----------------------------------------------------------------------
//                         i s K e y D o w n 
//-----------------------------------------------------------------------
bool InputSystemManager::isKeyDown(OIS::KeyCode key)
{
    return pKeyboardHandler->isKeyDown(key);
}

//-----------------------------------------------------------------------
//                           k e y P r e s s e d
//-----------------------------------------------------------------------
bool InputSystemManager::keyPressed( const OIS::KeyEvent& arg ) 
{
    if(m_debugEnabled)
    {
		std::cout << "Key pressed: " << arg.key << "\n";
    }
	if ( buffState ) {
		buffState->keysPressed[arg.key] = 1;
	}
    return m_GUIEnabled;

}

//-----------------------------------------------------------------------
//                        k e y R e l e a s e d
//-----------------------------------------------------------------------
bool InputSystemManager::keyReleased( const OIS::KeyEvent& arg ) 
{
    if(m_debugEnabled)
    {
		std::cout << "Key released: " << arg.key << "\n";
    }
	if ( buffState ) {
		buffState->keysReleased[arg.key] = 1;
	}
    return m_GUIEnabled;
}

//-----------------------------------------------------------------------
//                        m o u s e M o v e d
//-----------------------------------------------------------------------
bool InputSystemManager::mouseMoved( const OIS::MouseEvent &arg ) 
{
    static int lastX=0, lastY=0, lastZ=0;
    bool result=false;

	if(m_debugEnabled)
    {
		std::cout << "Mouse moved, arg.state.XYZ.abs: (" << arg.state.X.abs << "," << arg.state.Y.abs << "," << arg.state.Z.abs << ")\n";
		std::cout << "Mouse moved, arg.state.XYZ.rel: (" << arg.state.X.rel << "," << arg.state.Y.rel << "," << arg.state.Z.rel << ")\n";
    }

	if ( mouseState ) {
		mouseState->moveBuffered.xAbs = arg.state.X.abs;
		mouseState->moveBuffered.yAbs = arg.state.Y.abs;
		mouseState->moveBuffered.zAbs = arg.state.Z.abs;
		mouseState->moveBuffered.xRel = arg.state.X.rel;
		mouseState->moveBuffered.yRel = arg.state.Y.rel;
		mouseState->moveBuffered.zRel = arg.state.Z.rel;
	}
    /*if(m_GUIEnabled)
    {
        irr::SEvent event;
        event.EventType = irr::EET_MOUSE_INPUT_EVENT;

        if (m_gui)
        {
            // post moved event ?
            if( (lastX != arg.state.X.abs) ||
                (lastY != arg.state.Y.abs) )
            {
                event.MouseInput.Event = irr::EMIE_MOUSE_MOVED;
                event.MouseInput.X = arg.state.X.abs;
                event.MouseInput.Y = arg.state.Y.abs;
                result = m_gui->postEventFromUser(event);
                lastX = event.MouseInput.X;
                lastY = event.MouseInput.Y;
            }

            //post wheel event ?
            if( lastZ != arg.state.Z.abs )
            {
                event.EventType = irr::EET_MOUSE_INPUT_EVENT;
                event.MouseInput.Event = EMIE_MOUSE_WHEEL;
                event.MouseInput.Wheel = ((irr::f32)((lastZ - arg.state.Z.abs))) / (irr::f32)WHEEL_DELTA;
                result |= m_gui->postEventFromUser(event);
                lastZ = arg.state.Z.abs;
            }
        }

        if(result || m_GUIExclusive)
            return true;
    }*/

    return false;
}

//-----------------------------------------------------------------------
//                        m o u s e P r e s s e d
//-----------------------------------------------------------------------
bool InputSystemManager::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) 
{
    if(m_debugEnabled)
    {
		std::cout << "Mouse pressed: " << id << ", arg.state.XY.abs: (" << arg.state.X.abs << "," << arg.state.Y.abs << "\n";
    }
	if ( mouseState ) {
		mouseState->click.clicksDown[id].click = true;
		mouseState->click.clicksDown[id].xAbs = arg.state.X.abs;
		mouseState->click.clicksDown[id].yAbs = arg.state.Y.abs;
		mouseState->click.clicksDown[id].zAbs = arg.state.Z.abs;
		mouseState->click.clicksDown[id].xRel = arg.state.X.rel;
		mouseState->click.clicksDown[id].yRel = arg.state.Y.rel;
		mouseState->click.clicksDown[id].zRel = arg.state.Z.rel;
	}
    /*if(m_GUIEnabled)
    {
        irr::SEvent event;
        event.EventType = irr::EET_MOUSE_INPUT_EVENT;
        event.MouseInput.Event = oiMouseMap[1][id];
        event.MouseInput.X = arg.state.X.abs;
        event.MouseInput.Y = arg.state.Y.abs;

        if(m_gui && (m_gui->postEventFromUser(event) || m_GUIExclusive))
            return true;
    }*/

    return false;
}

//-----------------------------------------------------------------------
//                      m o u s e R e l e a s e d
//-----------------------------------------------------------------------
bool InputSystemManager::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) 
{
	if(m_debugEnabled)
    {
		std::cout << "Mouse released: " << id << ", arg.state.XY.abs: (" << arg.state.X.abs << "," << arg.state.Y.abs << "\n";
    }
	if ( mouseState ) {
		mouseState->click.clicksUp[id].click = true;
		mouseState->click.clicksUp[id].xAbs = arg.state.X.abs;
		mouseState->click.clicksUp[id].yAbs = arg.state.Y.abs;
		mouseState->click.clicksUp[id].zAbs = arg.state.Z.abs;
		mouseState->click.clicksUp[id].xRel = arg.state.X.rel;
		mouseState->click.clicksUp[id].yRel = arg.state.Y.rel;
		mouseState->click.clicksUp[id].zRel = arg.state.Z.rel;
	}

    /*if(m_GUIEnabled)
    {
        irr::SEvent event;
        event.EventType = irr::EET_MOUSE_INPUT_EVENT;
        event.MouseInput.Event = oiMouseMap[0][id];
        event.MouseInput.X = arg.state.X.abs;
        event.MouseInput.Y = arg.state.Y.abs;

        if(m_gui && (m_gui->postEventFromUser(event) || m_GUIExclusive))
            return true;
    }*/

    return false;
}

//-----------------------------------------------------------------------
//                     JoyStick b u t t o n P r e s s e d
//-----------------------------------------------------------------------
bool InputSystemManager::buttonPressed( const OIS::JoyStickEvent &arg, int button ) 
{
    return false;
}

//-----------------------------------------------------------------------
//                     JoyStick b u t t o n R e l e a s e d
//-----------------------------------------------------------------------
bool InputSystemManager::buttonReleased( const OIS::JoyStickEvent &arg, int button ) 
{
    return false;
}

//-----------------------------------------------------------------------
//                          JoyStick a x i s M o v e d
//-----------------------------------------------------------------------
bool InputSystemManager::axisMoved( const OIS::JoyStickEvent &arg, int axis )
{
    return false;
}

//-----------------------------------------------------------------------
//                          JoyStick p o v M o v e d
//-----------------------------------------------------------------------
bool InputSystemManager::povMoved( const OIS::JoyStickEvent &arg, int pov )
{
    return false;
}

void InputSystemManager::copyKeyStates( char keys[256] )
{
	pKeyboardHandler->copyKeyStates( keys );
}

}