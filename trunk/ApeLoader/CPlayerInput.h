#ifndef _CPLAYER_INPUT_H_
#define _CPLAYER_INPUT_H_

#include "GameComponent.h"
#include "Ogre.h"
#include "InputHandler.h"
#include "CCharacter.h"
#include "CCamera.h"
#include "OgreRender.h"
#include "CAnimation.h"

using namespace Ogre;

class GameComponent;
class OgreRender;
class InputHandler;
class CCharacter;
class CCamera;
class OgreRender;
class CAnimation;

class CPlayerInput : public GameComponent ,
					public OIS::MouseListener, 
					public OIS::KeyListener, 
					public OIS::JoyStickListener
{
public:
	
	//static Ogre::Vector3 Position;
	//Ogre::Vector3 Position;

	CPlayerInput();
	~CPlayerInput();

	void update();
	void setup();
	bool IsDirectionalKeyDown();

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


	virtual const std::string& familyID() const { 
		return mFamilyID; 
	}
	virtual const std::string& componentID() const { 
		return mComponentID; 
	}
private:
	static const std::string mFamilyID;
	static const std::string mComponentID;

	//bool mDirKeys;

	InputHandler* mInput;
	OgreRender* mOgre;
	CCharacter *mCharacter;
	CCamera *mCamera;
	CAnimation *mCAnim;
	//bool mIsKeyPressed;

	//OIS::Keyboard* mKeyboard;
};

#endif
