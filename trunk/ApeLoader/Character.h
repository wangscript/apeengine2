#include "Ogre.h"

// Generic Character class
class Character {
	// Attributes ------------------------------------------------------------------------------
protected:
	SceneNode *mMainNode; // Main character node
	SceneNode *mSightNode; // "Sight" node - The character is supposed to be looking here
	SceneNode *mCameraNode; // Node for the chase camera
	Entity *mEntity; // Character entity
	SceneManager *mSceneMgr;
public:
	// Methods ---------------------------------------------------------------------------------
protected:
public:
	// Updates the character (movement...)
	virtual void update (Real elapsedTime, OIS::Keyboard *input) = 0;
	// The three methods below returns the two camera-related nodes, 
	// and the current position of the character (for the 1st person camera)
	SceneNode *getSightNode () {
		return mSightNode;
	}
	SceneNode *getCameraNode () {
		return mCameraNode;
	}
	Vector3 getWorldPosition () {
		return mMainNode->_getDerivedPosition();
	}
};

// Specialization of the Character class - Our dear Ogre :D
class OgreCharacter : public Character {
	// Attributes ------------------------------------------------------------------------------
protected:
	String mName;
public:
	// Methods ---------------------------------------------------------------------------------
protected:
public:
	OgreCharacter (String name, SceneManager *sceneMgr,Vector3 pos) {
		// Setup basic member references
		mName = name;
		mSceneMgr = sceneMgr;

		// Setup basic node structure to handle 3rd person cameras
		mMainNode = mSceneMgr->getRootSceneNode ()->createChildSceneNode (mName,pos);
		mSightNode = mMainNode->createChildSceneNode (mName + "_sight", Vector3 (0, 0, 50));
		mCameraNode = mMainNode->createChildSceneNode (mName + "_camera", Vector3 (0, 1, -3));

		// Give this character a shape :)
		mEntity = mSceneMgr->createEntity (mName, "ninja.mesh");
		mMainNode->attachObject (mEntity);
		mMainNode->setScale(0.1,0.1,0.1);

		Light* l = mSceneMgr->createLight("MainLight");
		// Accept default settings: point light, white diffuse, just set position
		// NB I could attach the light to a SceneNode if I wanted it to move automatically with
		//  other objects, but I don't
		l->setType(Light::LT_DIRECTIONAL);
		l->setPosition(pos.x,pos.y+40,pos.z);
		l->setDirection(0.0, -1.0, 0);

	}
	~OgreCharacter () {
		mMainNode->detachAllObjects ();
		delete mEntity;
		mMainNode->removeAndDestroyAllChildren ();
		mSceneMgr->destroySceneNode (mName);
	}

	void update (Real elapsedTime, OIS::Keyboard *input) {
		// Handle movement
		if (input->isKeyDown (OIS::KC_W)) {
			mMainNode->translate (mMainNode->getOrientation () * Vector3 (0, 0, 50 * elapsedTime));
		}
		if (input->isKeyDown (OIS::KC_S)) {
			mMainNode->translate (mMainNode->getOrientation () * Vector3 (0, 0, -50 * elapsedTime));
		}
		if (input->isKeyDown (OIS::KC_A)) {
			mMainNode->yaw (Radian (2 * elapsedTime));
		}
		if (input->isKeyDown (OIS::KC_D)) {
			mMainNode->yaw (Radian (-2 * elapsedTime));
		}
		Ogre::Light *light = mSceneMgr->getLight("flashLightNode");
		Vector3 p = mSceneMgr->getSceneNode("Ogre 1")->getPosition();
		p.y = p.y + 30;
		light->setPosition(p); // mOgre->getCamera()->getPosition()

	}

	// Change visibility - Useful for 1st person view ;)
	void setVisible (bool visible) {
		mMainNode->setVisible (visible);
	}
};

// Our extended camera class
class ExtendedCamera {
	// Attributes ------------------------------------------------------------------------------
protected:
	SceneNode *mTargetNode; // The camera target
	SceneNode *mCameraNode; // The camera itself
	Camera *mCamera; // Ogre camera

	SceneManager *mSceneMgr;
	String mName;

	bool mOwnCamera; // To know if the ogre camera binded has been created outside or inside of this class

	Real mTightness; // Determines the movement of the camera - 1 means tight movement, while 0 means no movement
public:
	// Methods ---------------------------------------------------------------------------------
protected:
public:
	ExtendedCamera (String name, SceneManager *sceneMgr, Camera *camera = 0) {
		// Basic member references setup
		mName = name;
		mSceneMgr = sceneMgr;

		// Create the camera's node structure
		mCameraNode = mSceneMgr->getRootSceneNode ()->createChildSceneNode (mName);
		mTargetNode = mSceneMgr->getRootSceneNode ()->createChildSceneNode (mName + "_target");
		mCameraNode->setAutoTracking (true, mTargetNode); // The camera will always look at the camera target
		mCameraNode->setFixedYawAxis (true); // Needed because of auto tracking

		// Create our camera if it wasn't passed as a parameter
		if (camera == 0) {
			mCamera = mSceneMgr->createCamera (mName);
			mOwnCamera = true;
		}
		else {
			mCamera = camera;
			// just to make sure that mCamera is set to 'origin' (same position as the mCameraNode)
			mCamera->setPosition(0.0,0.0,0.0);
			mOwnCamera = false;
		}
		// ... and attach the Ogre camera to the camera node
		mCameraNode->attachObject (mCamera);

		// Default tightness
		mTightness = 0.01f;
	}
	~ExtendedCamera () {
		mCameraNode->detachAllObjects ();
		if (mOwnCamera)
			delete mCamera;
		mSceneMgr->destroySceneNode (mName);
		mSceneMgr->destroySceneNode (mName + "_target");
	}

	void setTightness (Real tightness) {
		mTightness = tightness;
	}

	Real getTightness () {
		return mTightness;
	}

	Vector3 getCameraPosition () {
		return mCameraNode->getPosition ();
	}

	void instantUpdate (Vector3 cameraPosition, Vector3 targetPosition) {
		mCameraNode->setPosition (cameraPosition);
		mTargetNode->setPosition (targetPosition);
	}

	void update (Real elapsedTime, Vector3 cameraPosition, Vector3 targetPosition) {
		// Handle movement
		Vector3 displacement;

		displacement = (cameraPosition - mCameraNode->getPosition ()) * mTightness;
		mCameraNode->translate (displacement);

		displacement = (targetPosition - mTargetNode->getPosition ()) * mTightness;
		mTargetNode->translate (displacement);
	}
};
