/*!
@file
@author		Pablo Nuñez
@date		13/2009
@module
*//*
This file is part of the Nebula Engine.

Nebula Engine is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Nebula Engine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Nebula Engine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _CCharacterController_H_
#define _CCharacterController_H_

#include "EnginePrerequisites.h"

class NxScene;
class ErrorStream;
class UserAllocator;
class NxUserAllocator;
class NxController;
class NxControllerManager;

namespace Nebula {

	class CPhysicsActor;
	class CPhysicsTrigger;
	class CAnimation;

	struct NebulaDllPrivate CCharacterControllerDesc
	{
		CCharacterControllerDesc()
		{

		}

		std::string name;
		std::string resourceFileName; //XML Definition of the character

		Ogre::Real speed; //Maximum speed of the character
		Ogre::Real speedMultiplier;
		Ogre::Real acceleration; //Acceleration rate
		Ogre::Real initialRadius; //initial rarius of the capsule shape
		Ogre::Real initialHeight; //Initial height of the capsule shape
		Ogre::Real scale;
		Ogre::Real skinWidth; 
		Ogre::Real jumpStrength; //Jump power
		Ogre::Real turnReactionSpeed; //Velocity of wich the character turns his body.
		Ogre::Real timestepMultiplier; //
		Ogre::Vector3 gravity;

	};

	class NebulaDllPrivate CCharacterController : public IGameComponent, 
												  public NxUserControllerHitReport
	{
	private:
		std::string mComponentID;

		CCharacterControllerDesc mDesc;

		Ogre::Vector3 mExternalForces;

		bool mIsPlayer;
		bool mIsOnElevator;
		
		CAnimation* mElevator;

		GameObject* mItemInHand;
		
		bool mWalk;
		Real mWalkTime;
		bool mStopWalk;
		bool mIsOnAir;
		bool mIsFalling;

		//The material wich the character is touching
		Ogre::String mContactMaterial;

		NxVec3 mStartPos;
		UserAllocator* mMyAllocator;
		ErrorStream	mErrorStream;
		NxPhysicsSDK* mPhysicsSDK;

		bool mPause;
		NxF32 G;
		bool mApplyGravity;
		bool mDrawSkinWidth;
		bool mMotion;
		NxF32 mV0;
		NxF32 mJumpTime;
		NxF32 mFallTime;
		bool mJump;
		bool mFall;
		bool mRotating;

		//bool mIsOverObject;
		bool mIsTouchingFloor;
		bool mIsTouchingCeiling;
		bool mIsTouchingSides;

		NxRay mWorldRay;
		NxControllerManager* mManager;
		NxScene* mScene;
		
		Ogre::Vector3 mNextMovement;
		Ogre::Quaternion mDirection;
		NxSceneQuery* mSceneQueryObject;
		
		void startFall(NxF32 v0);
		void stopFall();

		void startWalking(NxF32 v0);
		void stopWalking();

		void enableMotion(bool _motion);
		void enableRotation(bool _rotation);

		void setWalkState(bool state);

		NxF32 rayHitGroundDistance();
		NxF32 rayHitDistance(Vector3 cpos, Vector3 dir);

		void createControllerManager(NxUserAllocator* a);
		void releaseControllerManager();
		void updateControllers();

		NxActor* getCharacterActor(NxU32 characterIndex);
		bool resetCharacterPos(NxU32 index, const NxVec3& pos);
		bool updateCharacterExtents(NxU32 index, bool& increase);

		void updateCharacter();
		
		NxControllerAction  onShapeHit(const NxControllerShapeHit& hit);
		NxControllerAction  onControllerHit(const NxControllersHit& hit);

		NxController* initCharacterControllers(const NxVec3 startPos, NxReal scale, NxScene& scene);
		void releaseCharacterControllers(NxScene& scene);

		void registerEvents();

		Ogre::Real getVelocity();

	public:
		
		CCharacterController(const CCharacterControllerDesc&);
		
		//GameObject* character,GameObject* object , Ogre::Vector3 position
		//CppEvent3<bool,GameObject*,GameObject*,const Vector3&> eventCharacterMouseMovedOverObject;
		//CppEvent3<bool,GameObject*,GameObject*,const Vector3&> eventCharacterMouseMovedEnterOverObject;
		//CppEvent3<bool,GameObject*,GameObject*,const Vector3&> eventCharacterMouseMovedLeaveOverObject;
		//CppEvent4<bool,GameObject*,GameObject*,const Vector3&, int> eventCharacterMousePressedObject;
		//CppEvent4<bool,GameObject*,GameObject*,const Vector3&, int> eventCharacterMouseReleasedObject;

		CppEvent1<bool,const bool&> eventTouchedObject;
		CppEvent1<bool,const bool&> eventTouchedController;
		CppEvent1<bool,const bool&> eventStartFalling; //
		CppEvent1<bool,const bool&> eventHitGround; //
		CppEvent1<bool,const bool&> eventStartMoving; //
		CppEvent1<bool,const bool&> eventStopMoving;
		CppEvent1<bool,const bool&> eventMaxSpeedReached;
		CppEvent1<bool,const bool&> eventJumped; //

		//CppEvent1<void,CPhysicsActor*> eventPickedUpObject;
		//CppEvent1<void,CPhysicsActor*> eventThrowObject;
		//CppEvent1<void,CPhysicsActor*> eventHitObject;

		CppEvent1<bool, const bool& > eventStartCrouching;
		CppEvent1<bool, const bool& > eventCrouching;
		CppEvent1<bool, const bool& > eventEndCrouching;

		CppEvent1<bool, const bool& > eventStartAttack;
		CppEvent1<bool, CPhysicsActor* > eventStartThrow;


		virtual const std::string& componentID() const { 
			return mComponentID; 
		}

		GameObject* getItemInHand() {
			return mItemInHand;
		}

		bool isOnElevator() {
			return mIsOnElevator;
		}

		bool isPlayer() {
			return mIsPlayer;
		}
		
		void setAsPlayer(bool value) {
			mIsPlayer = value;
		}
		
		Real getDistanceToActor(CPhysicsActor* actor);
		Real getDistanceToCharacter(CCharacterController* character);
		Real getDistanceToTrigger(CPhysicsTrigger* trigger);

		bool OnMouseMovedOverObject(GameObject* object, Ogre::Vector3 position);
		
		bool OnMouseMovedEnterOverObject(GameObject* object, Ogre::Vector3 position);
		bool OnMouseMovedLeaveOverObject(GameObject* object, Ogre::Vector3 position);

		bool OnMousePressedObject(GameObject* object, Ogre::Vector3 position, int mouseButton);
		bool OnMouseReleasedObject(GameObject* object, Ogre::Vector3 position, int mouseButton);

		void OnTriggerEnter(CPhysicsTrigger* trigger);
		void OnTriggerStay(CPhysicsTrigger* trigger);
		void OnTriggerLeave(CPhysicsTrigger* trigger);

		void OnActorStartTouch(CPhysicsActor*);
		void OnActorTouch(CPhysicsActor*);
		void OnActorEndTouch(CPhysicsActor*);

		void OnControllerStartTouch(CCharacterController*);
		void OnControllerTouch(CCharacterController*);
		void OnControllerEndTouch(CCharacterController*);

		bool OnMouseMoved( const OIS::MouseEvent &arg );
		bool OnMousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
		bool OnMouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
		bool OnKeyPressed( const OIS::KeyEvent &arg );
		bool OnKeyReleased( const OIS::KeyEvent &arg );

		bool loadSettings();

		void update();
		void setup();
		
		void setPosition(Vector3 position);

		Ogre::String getContactMaterial() {
			return mContactMaterial;
		}

		bool isRotating();
		bool isMoving();
		bool isFalling();
		bool isOnAir();
		
		//bool isOverObject();
		bool isTouchingFloor();
		bool isTouchingCeiling();
		bool isTouchingSides();

		Real getTurnReactionSpeed();
		Ogre::Vector3 getDisplacement();
		Ogre::Quaternion getDirection();

		void setDisplacement(Ogre::Vector3 dispVector);

		void setDirection(Ogre::Quaternion q);

		bool startJump(NxF32 v0);
		void stopJump();
		
		void setSpeed(Ogre::Real speed) {
			mDesc.speed = speed;
		}

		Ogre::Real getSpeed() {
			return mDesc.speed;
		}

		void addExternalForce(Vector3 force);

		Vector3 getExternalForces() {
			return mExternalForces;
		}

		NxF32 getJumpHeight(NxF32 elapsedTime);
		NxF32 getFallHeight(NxF32 elapsedTime);
		
		const NxVec3& getCharacterPos();
		Ogre::Vector3 getCharacterPosOgre();

		CCharacterControllerDesc& getDescription() {
			return mDesc;
		}

		void callLuaFunction(const std::string func );

	};

} //end namespace

#endif

