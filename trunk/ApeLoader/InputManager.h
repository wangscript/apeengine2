#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H

//#include "ApePrerequisites.h"
#include "Ogre.h"
#include "InputHandler.h"
#include "OgreRender.h"


#include "OIS/OISEvents.h"
#include "OIS/OISInputManager.h"
#include "OIS/OISMouse.h"
#include "OIS/OISKeyboard.h"
#include "OIS/OISJoystick.h"
//#include "OgreStringConverter.h"

class OgreRender;

//class GameSystemManager;
using namespace Ogre;

class InputManager : 
	public OIS::MouseListener, 
	public OIS::KeyListener, 
	public OIS::JoyStickListener,
	public Ogre::Singleton<InputManager>
	
{
private:
	OIS::InputManager *mInputManager;
	OIS::Mouse *mMouse;
	OIS::Keyboard *mKeyboard;
	//OIS:: mJoy
	unsigned long m_hWnd;
	
	// MouseListener
	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID);
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID);

	// KeyListener
	bool keyPressed(const OIS::KeyEvent &evt);
	bool keyReleased(const OIS::KeyEvent &evt);
	
	// JoyStickListener
	bool buttonPressed(const OIS::JoyStickEvent &evt, int index);
	bool buttonReleased(const OIS::JoyStickEvent &evt, int index);
	bool axisMoved(const OIS::JoyStickEvent &evt, int index);
	bool povMoved(const OIS::JoyStickEvent &evt, int index);

	void setWindowExtents(int width, int height) ;

	void makeConnections();

	OgreRender* mOgre;

public:
	InputManager(); 
	~InputManager();

	static InputManager& getSingleton(void);
	static InputManager* getSingletonPtr(void);

	void handleCamera(float dt);
	
	//void OnOgreRender_Created(OgreRender* ogre);
	

	OIS::Keyboard* getKeyboard();
	//OIS::Mouse* GetMouse();

	void initialize();
	void capture();
	void updateMouseMetrics(int width,int height);
	
	bool isRightButtonDown();
	bool isLeftButtonDown();
	bool isMiddleButtonDown();

	const OIS::MouseState getMouseStat();
	
	OIS::Mouse* getMouseObj();

	bool shutDown;

	bool	up;
	bool	down;
	bool	left;
	bool	right;
	bool	forward;
	bool	backward;
	bool	esc;
	
	bool mouseLeftButton;
	bool mouseRightButton;
	bool mouseMiddleButton;

	Radian Pitch,Yaw;
};

#endif