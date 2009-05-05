#ifndef _CANIMATION_H_
#define _CANIMATION_H_

#include "GameComponent.h"
#include "Ogre.h"
#include "OgreRender.h"
#include "CCharacter.h"
#include "ApeManager.h"
#include "CMesh.h"

#include <map>

#include <Ogre/AnimationSystem.h>
#include <TriggerFunctor.h>
#include <NodeFactory.h>

//using namespace Ogre;

class OgreRender;
class CMesh;
class ApeManager;
class CCharacter;
class GameComponent;

using namespace tecnofreak;
using namespace tecnofreak::ogre;

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

class CAnimation : public GameComponent {
public:

	CAnimation(std::string diagramFileName,std::string animationInfoFileName);
	~CAnimation();

	void update();
	void setup();
	void updateAnimation();
	void loadXMLFiles();

	void setAnimationState(const float anim);

	void triggerListener( const tecnofreak::ITrigger* trigger );
	
	void attackEndTriggerListener( const tecnofreak::ITrigger* trigger );
	
	void footStepStart_TriggerListener( const tecnofreak::ITrigger* trigger );
	void footStepEnd_TriggerListener( const tecnofreak::ITrigger* trigger );
	
	void jumpPostEnd_TriggerListener( const tecnofreak::ITrigger* trigger );
	void jumpImpactEnd_TriggerListener( const tecnofreak::ITrigger* trigger );
	void jumpPreEnd_TriggerListener( const tecnofreak::ITrigger* trigger );
	

	//void jumpEnd_TriggerListener( const tecnofreak::ITrigger* trigger );
	//void jumpEnd_TriggerListener( const tecnofreak::ITrigger* trigger );
	//void jumpEnd_TriggerListener( const tecnofreak::ITrigger* trigger );
	//void jumpEnd_TriggerListener( const tecnofreak::ITrigger* trigger );

	virtual const std::string& familyID() const { 
		return mFamilyID; 
	}
	virtual const std::string& componentID() const { 
		return mComponentID; 
	}

	Ogre::SceneNode* mPlayerNode;
	//Ogre::SceneNode* mItemHolder;
	//Ogre::SceneNode* mWeaponHolder;

private:
	static const std::string mFamilyID;
	static const std::string mComponentID;

	OgreRender* mOgre;

	CCharacter* mCharacter;

	std::string mDiagramFileName;
	std::string mAnimationInfoFileName;
	
	
	Ogre::Entity* mEnt;
	
	AnimationSystem* m_frikiAnimationSystem;
	IParameter* m_frikiState;
	
	ITriggerSubscriber* m_attackListener;
	ITriggerSubscriber* m_footStepStartListener;
	ITriggerSubscriber* m_footStepEndListener;

	ITriggerSubscriber* m_jumpPostEndListener;
	ITriggerSubscriber* m_jumpImpactEndListener;
	ITriggerSubscriber* m_jumpPreEndListener;


	ITriggerSubscriber* m_listener;

};

#endif
