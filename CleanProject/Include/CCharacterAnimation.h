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

#ifndef _CCharacterAnimation_H_
#define _CCharacterAnimation_H_

/*
Animation States:
ID 0: Idle
ID 1: Run
ID 2: Die
ID 3: Attack_01
ID 4: Jump_Pre
ID 5: Jump_Loop
ID 6: Jump_Post
ID 7: Hit_02
ID 8: Hit_03
ID 9: Fall_Loop
ID 10: Attack_02_Post
ID 11: Attack_03
ID 12: Fall_Post
*/

#include "EnginePrerequisites.h"

namespace Nebula {

	using namespace tecnofreak;
	using namespace tecnofreak::ogre;
	
	struct NebulaDllPrivate ItemHolderBone
	{
		ItemHolderBone()
		{

		}

		std::string boneName;
		std::string itemName;
		Ogre::Bone* bone;
		bool isHoldingItem;
		bool isWeapon;
		bool isItem;

		GameObject* object;
	};

	struct NebulaDllPrivate CCharacterAnimationDesc
	{
		CCharacterAnimationDesc()
		{

		}

		std::string name;
		std::string diagramFileName;
		std::string animationFileName;
		
		std::string templateName;
	};

	class NebulaDllPrivate CCharacterAnimation : public IGameComponent {
	public:

		CCharacterAnimation(const CCharacterAnimationDesc&);
		~CCharacterAnimation();


		void update();
		void setup();

		void updateAnimation();
		void setupAnimationSystem();
		void setAnimationState(const float anim);

		float getCurrentAnimationState();
		bool isPlayingAnimation();
		
		void triggerListener( const tecnofreak::ITrigger* trigger );

		void registerEvents();
		void setBindings();
		void createLuaTriggerFunctor(const std::string, const luabind::object&); //const luabind::object

		bool OnStartFalling( const bool& );
		bool OnHitGround( const bool& );
		bool OnStartMoving( const bool& );
		bool OnStopMoving( const bool& );
		bool OnMaxSpeedReached( const bool& );
		bool OnJumped( const bool& );
		bool OnStartThrow(CPhysicsActor*);
		bool OnStartAttack(const bool&);

		//////////////////////////////////////////////////////////////////////////////////////////
		
		void addItemHolderBone(std::string bone);
		void attachItemToBone(std::string bone, GameObject* object);
		void detachItemFromBone(GameObject* object);
		std::string getBoneAttachedToObject(GameObject* object);
		
		GameObject* getObjectAttachedToBone(std::string bone);

		void updateAttachedItems();
		
		//Ogre::Bone* getItemHolderBone(std::string bone);
		//Ogre::Bone* getItemHolderBone();
		//bool isHoldingItem() {
		//	return mIsHoldingItem;
		//}
		//bool hasItemHolderBone() {
		//	return mHasItemHolderBone;
		//}
		//Vector3 getOffsetItemPosition() {
		//	return mOffsetItemPosition;
		//}
		//Quaternion getOffsetItemOrientation() {
		//	return mOffsetItemOrientation;
		//}
		//void setOffsetItemPosition(Vector3 pos) {
		//	mOffsetItemPosition = pos;
		//}
		//void setOffsetItemOrientation(Quaternion orientation) {
		//	mOffsetItemOrientation = orientation;
		//}
		//////////////////////////////////////////////////////////////////////////////////////////

		virtual const std::string& componentID() const { 
			return mComponentID; 
		}

		CCharacterAnimationDesc& getDescription() {
			return mDesc;
		}

		//void setCurrentTemplate(luabind::object);
		void callLuaFunction(const std::string func);
		

	private:
		std::string mComponentID;
		CCharacterAnimationDesc mDesc;
		
		std::map<const std::string, ItemHolderBone > mItemHolderBones;

		std::map<const std::string, LuaTriggerFunctor > mTriggerFunctors;
		
		AnimationSystem* m_frikiAnimationSystem;
		IParameter* m_frikiState;
		
		ITriggerSubscriber* m_listener;

	};

} //end namespace

#endif
