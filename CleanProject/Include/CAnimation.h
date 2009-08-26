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

#ifndef _CANIMATION_H_
#define _CANIMATION_H_

#include "EnginePrerequisites.h"

namespace Nebula {

	using namespace Ogre;
	class IGameComponent;
	
	class Ogre::Animation;
	class Ogre::AnimationState;
	class Ogre::AnimationTrack;
	//class SceneNode;

	struct NebulaDllPrivate CAnimationDesc
	{
		CAnimationDesc()
		{

		}

		std::string name;

	};
	
	class NebulaDllPrivate CAnimation : public IGameComponent
	{
	public:
		CAnimation();
		CAnimation(const CAnimationDesc&);
		~CAnimation();

		void update();
		void setup();

		CAnimationDesc& getDescription() {
			return mDesc;
		}
		
		void callLuaFunction(const std::string func );

		virtual const std::string& componentID() const { 
			return mComponentID; 
		}
		
		int getNumberOfAnimations() {
			return mNumberOfAnimations;
		}

		void setAnimationSpeed(int animIndex, Real speed);
		Real getAnimationSpeed(int animIndex);

		void OnAnimationStarted();
		void OnAnimationEnded();
		void OnAnimationUpdated();

		AnimationState* getAnimationState(int animIndex);
		Animation* getAnimation(int animIndex);
		
		int getCurrentAnimationIndex() {
			return mCurrentAnimation;
		}

		void addAnimationState(AnimationState*);
		void addAnimation(Animation* animation, bool enabled, bool loop);

		void playAnimation(int animIndex);
		void stopAnimation(int animIndex);
		void pauseAnimation();
		
		void setAnimationTimePosition(int animIndex, Real time);

		void setAnimationNode(SceneNode* node);
		void updateNode();
		SceneNode* getAnimationNode();

		bool isRunningAnimation() {
			return mIsRunningAnimation;
		}

		Ogre::Vector3 getVelocity() {
			return mVelocity;
		}

	private:
		std::string mComponentID;

		CAnimationDesc mDesc;

		std::vector<AnimationState*> mAnimStates;
		std::vector<AnimationTrack*> mAnimationTracks;
		std::vector<Animation*> mAnimations;
		
		std::vector<Real> mAnimVelocity;

		Ogre::SceneNode* mAnimationNode;
		
		Ogre::Vector3 mLastPosition;
		Ogre::Vector3 mVelocity;

		int mCurrentAnimation;
		bool mIsPaused;
		int mNumberOfAnimations;
		Real mAnimationSpeed;

		bool mIsRunningAnimation;
	};

} //end namespace

#endif
