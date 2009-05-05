#include "CAnimation.h"

/*static*/ 
const std::string CAnimation::mFamilyID = "CAnimation";
const std::string CAnimation::mComponentID = "CAnimation";

CAnimation::CAnimation(std::string diagramFileName,std::string animationInfoFileName)
{
	
	mDiagramFileName = diagramFileName;
	mAnimationInfoFileName = animationInfoFileName;

}

CAnimation::~CAnimation()
{

}

void CAnimation::update() {

}


void CAnimation::setup() {

}

void CAnimation::triggerListener( const tecnofreak::ITrigger* trigger )
{
	std::cout << "Received trigger " << trigger->getName() << std::endl;
}

void CAnimation::attackEndTriggerListener( const tecnofreak::ITrigger* trigger )
{
	std::cout << "I only listen to the attack end trigger" << std::endl;
	m_frikiState->setValue( 0 );
}

void CAnimation::footStepStart_TriggerListener( const tecnofreak::ITrigger* trigger ) {
	OgreRender::getSingleton().getDebugText()->addText("footstep trigger!");
	if(mCharacter->isMoving() && mCharacter->isOverObject()) {	
		CSound* tmpObjSound = dynamic_cast<CSound*>(getOwnerObject()->getComponent("CSound")); //->toActor();
		if(tmpObjSound) {
			Ogre::String material = mCharacter->getContactMaterial();
			tmpObjSound->playSound(material);
		}
	}
	//m_frikiState->setValue(1);
}
void CAnimation::footStepEnd_TriggerListener( const tecnofreak::ITrigger* trigger ) {
	//m_frikiState->setValue(1);
}

void CAnimation::jumpPostEnd_TriggerListener( const tecnofreak::ITrigger* trigger ) {
	//m_frikiState->setValue(1);
}

void CAnimation::jumpPreEnd_TriggerListener( const tecnofreak::ITrigger* trigger ) {
	m_frikiState->setValue(5);
}

void CAnimation::jumpImpactEnd_TriggerListener( const tecnofreak::ITrigger* trigger ) {
	if(mCharacter->isMoving())
		m_frikiState->setValue(1);
	else
		m_frikiState->setValue(0);
}

void CAnimation::setAnimationState(const float anim) {
	m_frikiState->setValue(anim);
}

void CAnimation::loadXMLFiles() {
	
	mCharacter = dynamic_cast<CCharacter*>(getOwnerObject()->getComponent("CCharacter"));

	CMesh* mCMesh = dynamic_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));
	if(mCMesh) {

		CMesh *mesh = dynamic_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));
		mEnt = OgreRender::getSingleton().getSceneManager()->createEntity(mCMesh->mEntityName,mCMesh->mMeshName);
		
		mCMesh->mEntity = mEnt;
		
		CRender* mCRender = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));
		if(mCRender) {
			//mCRender->mNode->attachObject(mEnt);
			mCRender->mNode = OgreRender::getSingleton().getSceneManager()->getRootSceneNode()->createChildSceneNode("playerNode");
			
			Ogre::SceneNode* playerNode = mCRender->mNode->createChildSceneNode("playerNode2");
			playerNode->attachObject(mEnt);
			playerNode->setScale(8,8,8);

			m_frikiAnimationSystem = new AnimationSystem( mEnt );
			m_frikiAnimationSystem->loadAnimationTree( mDiagramFileName );
			m_frikiAnimationSystem->loadAnimationInfo( mAnimationInfoFileName ); //"../Media/Characters/"

			m_listener = new TriggerFunctor< CAnimation >( this, &CAnimation::triggerListener );
			m_frikiAnimationSystem->addSubscriber( m_listener );

			//////////////////////////////////////////////////////////////////////////
			// Set triggers

			m_attackListener = new TriggerFunctor< CAnimation >( this, &CAnimation::attackEndTriggerListener );
			m_frikiAnimationSystem->addSubscriber( "attack_end", m_attackListener ); //attack_end
			
			m_footStepStartListener = new TriggerFunctor< CAnimation >( this, &CAnimation::footStepStart_TriggerListener );
			m_frikiAnimationSystem->addSubscriber( "footstep_start", m_footStepStartListener ); //attack_end

			m_footStepEndListener = new TriggerFunctor< CAnimation >( this, &CAnimation::footStepEnd_TriggerListener );
			m_frikiAnimationSystem->addSubscriber( "footstep_end", m_footStepEndListener ); //attack_end

			m_jumpPostEndListener = new TriggerFunctor< CAnimation >( this, &CAnimation::jumpPostEnd_TriggerListener );
			m_frikiAnimationSystem->addSubscriber( "jump_end", m_jumpPostEndListener ); //attack_end

			m_jumpImpactEndListener = new TriggerFunctor< CAnimation >( this, &CAnimation::jumpImpactEnd_TriggerListener );
			m_frikiAnimationSystem->addSubscriber( "jump_end", m_jumpImpactEndListener ); //attack_end
			
			m_jumpPreEndListener = new TriggerFunctor< CAnimation >( this, &CAnimation::jumpPreEnd_TriggerListener );
			m_frikiAnimationSystem->addSubscriber( "jump_pre_end", m_jumpPreEndListener ); //attack_end

			//////////////////////////////////////////////////////////////////////////

			

			m_frikiState = m_frikiAnimationSystem->getParameter( "Animation State" );

			m_frikiState->setValue(0);

			mPlayerNode = mCRender->mNode;

			//if(charDegree1 != 0)
			//playerNode->rotate(Quaternion(Degree(charDegree1), charDir1),Ogre::SceneNode::TransformSpace::TS_WORLD);
			playerNode->rotate(Quaternion(Degree(180), Ogre::Vector3::UNIT_Y),Ogre::SceneNode::TransformSpace::TS_WORLD);

			//if(charDegree2 != 0)
			//	playerNode->rotate(Quaternion(Degree(charDegree2), charDir2),Ogre::SceneNode::TransformSpace::TS_WORLD);

		}
		//mEnt->setMaterialName("narutoMat");
		
	}
}

void CAnimation::updateAnimation() {
	
	Ogre::Real time = OgreRender::getSingleton().getTimeSinceLastFrame();
	m_frikiAnimationSystem->update( time );

}
