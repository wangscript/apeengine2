#include "CAnimation.h"

void BodyPart::setAnimState(AnimState::animState ms) {
	if(this->mCurrentAnim == ms || ms == AnimState::NONE) //mCurrentAnim == ms || 
		return;
	this->mNextAnim = ms;
	this->getAnim(this->mNextAnim)->getAnimation()->setEnabled(true);
}

ApeAnimation* BodyPart::getAnim(AnimState::animState ms) {
	//return mGOs[id];

	std::map<AnimState::animState, ApeAnimation*>::iterator iter = this->mAnimList.begin();
	iter = this->mAnimList.find(ms);
	if(iter != this->mAnimList.end()) {
		return iter->second;
	}
	return NULL;
}

void BodyPart::updateAnimation() {
	
	OgreRender* mOgre;
	mOgre = OgreRender::getSingleton().getSingletonPtr();

	float time = mOgre->getTimeSinceLastFrame();

	if(this->mCurrentAnim != AnimState::NONE) {
		this->getAnim(this->mCurrentAnim)->getAnimation()->addTime(time * this->getAnim(this->mCurrentAnim)->getSpeedMultipier());
	}
	if(this->mNextAnim != AnimState::NONE) {
		this->getAnim(this->mNextAnim)->getAnimation()->addTime(time * this->getAnim(this->mNextAnim)->getSpeedMultipier()); //* 0.0001
	}

	//mCharacter = dynamic_cast<CCharacter*>(getOwnerObject()->getComponent("CCharacter"));

	if(this->mNextAnim != AnimState::NONE && this->mCurrentAnim != AnimState::NONE)
	{

		Real blendMultip = this->getAnim(this->mNextAnim)->getBlendMultipier();

		float weight = this->getAnim(this->mNextAnim)->getAnimation()->getWeight() + time * blendMultip; //2.0
		if(weight >1)
			weight = 1;
		this->getAnim(this->mCurrentAnim)->getAnimation()->setWeight(1-weight);
		this->getAnim(this->mNextAnim)->getAnimation()->setWeight(weight);

		Real w2 = this->getAnim(this->mNextAnim)->getAnimation()->getWeight();

		if(weight >= 1)
		{

			if(!this->getAnim(this->mCurrentAnim)->getAnimation()->getLoop()) {
				//getAnim(mCurrentAnim)->getAnimation()->setTimePosition(0);
			}
			this->getAnim(this->mCurrentAnim)->getAnimation()->setEnabled(false);

			this->getAnim(this->mNextAnim)->getAnimation()->setEnabled(true); // setWeight(1.0f);
			this->mCurrentAnim = this->mNextAnim;
			this->mNextAnim = AnimState::NONE;

		}

	}


	//////////////////////////////////////////////////////////////////////////
	if(this->mNextAnim == AnimState::NONE) {
		Real l = this->getAnim(this->mCurrentAnim)->getAnimation()->getLength();
		Real tp = this->getAnim(this->mCurrentAnim)->getAnimation()->getTimePosition();

		if(!this->getAnim(this->mCurrentAnim)->getAnimation()->getLoop()) {
			if(tp>=l) {
				if(this->mCurrentAnim == AnimState::START_WALK) {
					this->mNextAnim = AnimState::LOOP_WALK;
					this->getAnim(this->mNextAnim)->getAnimation()->setEnabled(true);
					this->getAnim(this->mNextAnim)->getAnimation()->setWeight(0.0f);
					this->getAnim(this->mCurrentAnim)->getAnimation()->setWeight(1.0f);
				}

				if(this->mCurrentAnim == AnimState::STOP_WALK) {
					this->mNextAnim = AnimState::IDLE;
					this->getAnim(this->mNextAnim)->getAnimation()->setEnabled(true);
					this->getAnim(this->mNextAnim)->getAnimation()->setWeight(0.0f);
					this->getAnim(this->mCurrentAnim)->getAnimation()->setWeight(1.0f);
				}
				if(this->mCurrentAnim == AnimState::START_JUMP) {
					this->mNextAnim = AnimState::IDLE;
					this->getAnim(this->mNextAnim)->getAnimation()->setEnabled(true);
					this->getAnim(this->mNextAnim)->getAnimation()->setWeight(0.0f);
					this->getAnim(this->mCurrentAnim)->getAnimation()->setWeight(1.0f);
				}
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////

}


/*static*/ 
const std::string CAnimation::mFamilyID = "CAnimation";
const std::string CAnimation::mComponentID = "CAnimation";

CAnimation::CAnimation(std::string xmlFileName)
{
	mOgre = OgreRender::getSingleton().getSingletonPtr();
	mXMLFileName = xmlFileName;
}

CAnimation::~CAnimation()
{

}

void CAnimation::update() {

}

Ogre::String CAnimation::getParamValue (Ogre::String paramName,Ogre::String param)
{
	string::size_type loc = param.find(paramName);

	if( loc != string::npos ) {
		Ogre::String paramValue;

		paramValue = param.substr(loc + paramName.length() + 1,paramName.length() - (loc + paramName.length()) );
		Ogre::String res = "";

		if(loc == 0) {
			paramValue = param.substr(paramName.length() + 1,param.length() - paramName.length() + 1);

		}

		Ogre::String::iterator i, iend;
		iend = paramValue.end();
		for (i = paramValue.begin(); i != iend; ++i)
		{
			if (*i != '\n' && (*i != '\r'))
				res += (*i);
			else
				break;
		}

		return res;
	}
	else
	{
		return "";
	}

	//Get rid of junk (with safty check)
	if (param.empty())
		throw Ogre::Exception (100, "Param empty.", "PhysicsCallback::getLastParam (Ogre::String param)");

	//Return
	return "";
}

bool CAnimation::loadSettings() { //std::string characterFileName

	if(mXMLFileName != "") {

		std::string mFilePath = "../../Media/Characters/" + mXMLFileName + ".xml";

		XMLNode xMainNode;

		try {
			xMainNode=XMLNode::openFileHelper(mFilePath.c_str(),"ApeEngine"); //,"PMML"

		} catch(...) {
			Ogre::LogManager::getSingleton().logMessage("*** Error loading character file ***");
			return false;
		}

		XMLNode xCharacterNode = xMainNode.getChildNode("Character");
		
		//Ogre::String


		mPlayerNode = mOgre->getSceneManager()->getRootSceneNode()->createChildSceneNode("playerCharNode");
		mItemHolder = mPlayerNode->createChildSceneNode("itemHolderNode");
		mWeaponHolder = mPlayerNode->createChildSceneNode("weaponHolderNode");
		mWeaponHolder->translate(22,60,-15);

		OgreRender::getSingleton().mWeaponNode = mWeaponHolder;

		Ogre::String charName = xCharacterNode.getAttribute("name");

		std::string mCharFilePath = "../../Media/Characters/" + charName + ".scene.userdata.xml";

		XMLNode xCharNode;

		try {
			xCharNode=XMLNode::openFileHelper(mCharFilePath.c_str(),"userData"); //,"PMML"

			//XMLNode xCharacterNode = xCharNode.getChildNode("Character");
			//xCharacterNode

		} catch(...) {
			Ogre::LogManager::getSingleton().logMessage("*** Error loading character userData xml file ***");
			return false;
		}

		Ogre::Real charDegree1 = Ogre::StringConverter::parseReal(xCharacterNode.getAttribute("mInitRotDegree1"));
		Ogre::Vector3 charDir1 = Ogre::StringConverter::parseVector3(xCharacterNode.getAttribute("mInitRotDir1"));

		Ogre::Real charDegree2 = Ogre::StringConverter::parseReal(xCharacterNode.getAttribute("mInitRotDegree2"));
		Ogre::Vector3 charDir2 = Ogre::StringConverter::parseVector3(xCharacterNode.getAttribute("mInitRotDir2"));


		int partIter = 0;
		Ogre::SceneNode* sn = mPlayerNode->createChildSceneNode(charName + "_playerCharNodeChild");

		if(charDegree1 != 0)
			sn->rotate(Quaternion(Degree(charDegree1), charDir1),Ogre::SceneNode::TransformSpace::TS_WORLD);

		if(charDegree2 != 0)
			sn->rotate(Quaternion(Degree(charDegree2), charDir2),Ogre::SceneNode::TransformSpace::TS_WORLD);

		for(int i = 0;i<xCharacterNode.nChildNode("CharacterPart");i++) 
		{
			XMLNode xCharacterPartNode = xCharacterNode.getChildNode("CharacterPart",&partIter);

			Ogre::String meshName = xCharacterPartNode.getAttribute("mMeshName");

			Ogre::Vector3 position;
			Ogre::Quaternion orientation;

			int userDataIter = 0;
			for(int i = 0;i<xCharNode.nChildNode("object");i++) 
			{
				XMLNode xobjNode = xCharNode.getChildNode("object",&userDataIter);
				XMLClear c = xobjNode.getClear();
				Ogre::String v = c.lpszValue;
				Ogre::String objName = xobjNode.getAttribute("__name");

				if( (objName + ".mesh") == meshName)
					position = Ogre::StringConverter::parseVector3(getParamValue("position",v ) );	
					orientation = Ogre::StringConverter::parseQuaternion(getParamValue("rotation",v ) );	
					//meshName = (objName + ".mesh");
			}



			Ogre::Real degree1 = Ogre::StringConverter::parseReal(xCharacterPartNode.getAttribute("mInitRotDegree1"));
			Ogre::Vector3 dir1 = Ogre::StringConverter::parseVector3(xCharacterPartNode.getAttribute("mInitRotDir1"));
			
			Ogre::Real degree2 = Ogre::StringConverter::parseReal(xCharacterPartNode.getAttribute("mInitRotDegree2"));
			Ogre::Vector3 dir2 = Ogre::StringConverter::parseVector3(xCharacterPartNode.getAttribute("mInitRotDir2"));

			Ogre::Real scale = Ogre::StringConverter::parseReal(xCharacterPartNode.getAttribute("mInitScale"));

			CMesh *mesh = dynamic_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));
			Ogre::Entity* ent = OgreRender::getSingleton().getSceneManager()->createEntity(charName + "_" + meshName + "_entity",meshName);
			//Ogre::Entity* ent = mesh->getEntity();
			mesh->mEntity = ent;
			ent->setMaterialName("narutoMat");

			Ogre::SceneNode* mCharacterMeshNode = sn->createChildSceneNode(charName + "_" + meshName + "_playerCharNodeChil2");
			//Ogre::SceneNode* mCharacterMeshNode = mOgre->getSceneManager()->getRootSceneNode()->createChildSceneNode(charName + "_" + meshName + "_playerCharNodeChil2");
			mCharacterMeshNode->attachObject(ent);
			//mCharacterMeshNode->setOrientation(orientation.w,orientation.x,orientation.y,orientation.z);

			

			//Panda
			if(degree1 != 0)
				mCharacterMeshNode->rotate(Quaternion(Degree(degree1), dir1));

			if(degree2 != 0)
				mCharacterMeshNode->rotate(Quaternion(Degree(degree2), dir2));

			//mCharacterMeshNode->setOrientation(Ogre::Quaternion::IDENTITY);
			//mCharacterMeshNode->setOrientation(Ogre::Quaternion::IDENTITY);
			
			//mCharacterMeshNode->rotate(orientation,Ogre::SceneNode::TransformSpace::TS_PARENT);

			if(scale != 0)
				mCharacterMeshNode->setScale(scale,scale,scale);
			
			//mCharacterMeshNode->setPosition(sn->_getDerivedPosition() + position); //,Ogre::SceneNode::TransformSpace::TS_PARENT

			//mCharacterMeshNode->setScale(scale,scale,scale);

			CCamera* cam = dynamic_cast<CCamera*>(getOwnerObject()->getComponent("CCamera"));
			//cam->mCharacterMeshNode

			//XMLNode xCharacterPartNode = xCharacterNode.getChildNode("CharacterPart");
			//xCharacterPartNode

			//XMLNode xCharacterPartNode = xCharacterNode.getChildNode("CharacterPart");

			BodyPart* bodyPart = new BodyPart();

			int animIter = 0;
			//int TreeIter = 0;
			for(int i = 0;i<xCharacterPartNode.nChildNode("Animation");i++) 
			{
				XMLNode xAnimNode = xCharacterPartNode.getChildNode("Animation",&animIter);

				try {
					
					
					
					Ogre::String animName = xAnimNode.getAttribute("mAnimationName");

					//Real defaultMulpip;
					ApeAnimation* animObj = new ApeAnimation(ent->getAnimationState(animName));
					
					//bodyPart->animObj = animObj;
					
					Ogre::Real speedMultip = Ogre::StringConverter::parseReal(xAnimNode.getAttribute("mSpeedMultip"));
					Ogre::Real blendMultip = Ogre::StringConverter::parseReal(xAnimNode.getAttribute("mBlendMultip"));
					Ogre::Real weight = Ogre::StringConverter::parseReal(xAnimNode.getAttribute("mAnimWeight"));
					bool mIsLooped = Ogre::StringConverter::parseBool(xAnimNode.getAttribute("mLooped"));

					animObj->setSpeedMultipier(speedMultip);
					animObj->setBlendMultipier(blendMultip);
					animObj->getAnimation()->setLoop(mIsLooped);
					animObj->getAnimation()->setWeight(weight);

					//bodyPart->animObj = animObj;

					Ogre::String animType = xAnimNode.getAttribute("mType");

					if(animType == "IDLE") {
						bodyPart->mAnimList[AnimState::IDLE] = animObj;
					} else if(animType == "RUN_START") {
						bodyPart->mAnimList[AnimState::START_WALK] = animObj;
					} else if(animType == "RUN_LOOP") {
						bodyPart->mAnimList[AnimState::LOOP_WALK] = animObj;
					} else if(animType == "RUN_STOP") {
						bodyPart->mAnimList[AnimState::STOP_WALK] = animObj;
					} else if(animType == "JUMP") {
						bodyPart->mAnimList[AnimState::START_JUMP] = animObj;
					}	
					
					bodyPart->mCurrentAnim = IDLE;
					bodyPart->mNextAnim = AnimState::NONE;

				} catch (...) {
					Ogre::LogManager::getSingleton().logMessage("*** Error loading ApeScene data from Character map file ***");
					return false;
				}

			}

			mBodyPartsList.push_back(bodyPart);

			mCurrentAnim = IDLE;
			mNextAnim =	AnimState::NONE;
			//getAnim(mCurrentAnim)->getAnimation()->setEnabled(true);
			//playAnim(mCurrentAnim);
			setAnimState(mCurrentAnim);
		}
	}
	return true;
}

void CAnimation::setup() {

	if(mXMLFileName == "") {
		//CMesh *mesh = dynamic_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));
		//Ogre::Entity* ent = mesh->getEntity();
		//
		//Real defaultMulpip;

		////getting the model's animations
		//ApeAnimation* animIdle1 = new ApeAnimation(ent->getAnimationState("Idle"));
		//ApeAnimation* animRunStart = new ApeAnimation(ent->getAnimationState("RunStart"));
		//ApeAnimation* animRunLoop = new ApeAnimation(ent->getAnimationState("RunLoop"));
		//ApeAnimation* animRunStop = new ApeAnimation(ent->getAnimationState("RunStop"));
		//ApeAnimation* animJump = new ApeAnimation(ent->getAnimationState("Jump2"));

		//defaultMulpip = 0.8f;

		//animIdle1->setSpeedMultipier(0.3);
		//animRunStart->setSpeedMultipier(0.8f);
		//animRunLoop->setSpeedMultipier(defaultMulpip);
		//animRunStop->setSpeedMultipier(defaultMulpip);
		//animJump->setSpeedMultipier(defaultMulpip);

		//defaultMulpip = 2.0f;

		//animIdle1->setBlendMultipier(defaultMulpip);
		//animRunStart->setBlendMultipier(3.0f);
		//animRunLoop->setBlendMultipier(defaultMulpip);
		//animRunStop->setBlendMultipier(defaultMulpip);
		//animJump->setBlendMultipier(8.0f);
		//
		//mAnimList[AnimState::IDLE] = animIdle1;
		//mAnimList[AnimState::START_WALK] = animRunStart;
		//mAnimList[AnimState::LOOP_WALK] = animRunLoop;
		//mAnimList[AnimState::STOP_WALK] = animRunStop;
		//mAnimList[AnimState::START_JUMP] = animJump;

		//mCurrentAnim = IDLE;
		//mNextAnim =	AnimState::NONE;
		//
		//mAnimList[AnimState::IDLE]->getAnimation()->setLoop(true);
		//mAnimList[AnimState::START_WALK]->getAnimation()->setLoop(false);
		//mAnimList[AnimState::LOOP_WALK]->getAnimation()->setLoop(true);
		//mAnimList[AnimState::STOP_WALK]->getAnimation()->setLoop(false);
		//mAnimList[AnimState::START_JUMP]->getAnimation()->setLoop(false);

		//defaultMulpip = 1.0f;

		//mAnimList[AnimState::IDLE]->getAnimation()->setWeight(defaultMulpip);
		//mAnimList[AnimState::START_WALK]->getAnimation()->setWeight(defaultMulpip);
		//mAnimList[AnimState::LOOP_WALK]->getAnimation()->setWeight(defaultMulpip);
		//mAnimList[AnimState::STOP_WALK]->getAnimation()->setWeight(defaultMulpip);
		//mAnimList[AnimState::START_JUMP]->getAnimation()->setWeight(defaultMulpip);


		//getAnim(mCurrentAnim)->getAnimation()->setEnabled(true);

	
	}
}
void CAnimation::updateAnimation() {

	std::list<BodyPart*>::iterator it;
	for(it=mBodyPartsList.begin();it!=mBodyPartsList.end();it++)
	{
		(*it)->updateAnimation();
	}

	//float time = mOgre->getTimeSinceLastFrame();

	//if(mCurrentAnim != AnimState::NONE) {
	//	getAnim(mCurrentAnim)->getAnimation()->addTime(time * getAnim(mCurrentAnim)->getSpeedMultipier());
	//}
	//if(mNextAnim != AnimState::NONE) {
	//	getAnim(mNextAnim)->getAnimation()->addTime(time * getAnim(mNextAnim)->getSpeedMultipier()); //* 0.0001
	//}

	//mCharacter = dynamic_cast<CCharacter*>(getOwnerObject()->getComponent("CCharacter"));

	//if(mNextAnim != AnimState::NONE && mCurrentAnim != AnimState::NONE)
	//{

	//		Real blendMultip = getAnim(mNextAnim)->getBlendMultipier();

	//		float weight = getAnim(mNextAnim)->getAnimation()->getWeight() + time * blendMultip; //2.0
	//		if(weight >1)
	//			weight = 1;
	//		getAnim(mCurrentAnim)->getAnimation()->setWeight(1-weight);
	//		getAnim(mNextAnim)->getAnimation()->setWeight(weight);

	//		Real w2 = getAnim(mNextAnim)->getAnimation()->getWeight();

	//		if(weight >= 1)
	//		{
	//			
	//			if(!getAnim(mCurrentAnim)->getAnimation()->getLoop()) {
	//				//getAnim(mCurrentAnim)->getAnimation()->setTimePosition(0);
	//			}
	//			getAnim(mCurrentAnim)->getAnimation()->setEnabled(false);

	//			getAnim(mNextAnim)->getAnimation()->setEnabled(true); // setWeight(1.0f);
	//			mCurrentAnim = mNextAnim;
	//			mNextAnim = AnimState::NONE;

	//		}

	//}


	////////////////////////////////////////////////////////////////////////////
	//if(mNextAnim == AnimState::NONE) {
	//	Real l = getAnim(mCurrentAnim)->getAnimation()->getLength();
	//	Real tp = getAnim(mCurrentAnim)->getAnimation()->getTimePosition();

	//	if(!getAnim(mCurrentAnim)->getAnimation()->getLoop()) {
	//		if(tp>=l) {
	//			if(mCurrentAnim == AnimState::START_WALK) {
	//				mNextAnim = AnimState::LOOP_WALK;
	//				getAnim(mNextAnim)->getAnimation()->setEnabled(true);
	//				getAnim(mNextAnim)->getAnimation()->setWeight(0.0f);
	//				getAnim(mCurrentAnim)->getAnimation()->setWeight(1.0f);
	//			}
	//			
	//			if(mCurrentAnim == AnimState::STOP_WALK) {
	//				mNextAnim = AnimState::IDLE;
	//				getAnim(mNextAnim)->getAnimation()->setEnabled(true);
	//				getAnim(mNextAnim)->getAnimation()->setWeight(0.0f);
	//				getAnim(mCurrentAnim)->getAnimation()->setWeight(1.0f);
	//			}
	//			if(mCurrentAnim == AnimState::START_JUMP) {
	//				mNextAnim = AnimState::IDLE;
	//				getAnim(mNextAnim)->getAnimation()->setEnabled(true);
	//				getAnim(mNextAnim)->getAnimation()->setWeight(0.0f);
	//				getAnim(mCurrentAnim)->getAnimation()->setWeight(1.0f);
	//			}
	//		}
	//	}
	//}
	//////////////////////////////////////////////////////////////////////////

}
/*
void CAnimation::setAnim_Walk(AnimationState* anim) {
	mAnimList["Walk"] = anim;
}
void CAnimation::setAnim_Run(AnimationState* anim) {
	mAnimList["Run"] = anim;
}
void CAnimation::setAnim_Jump(AnimationState* anim) {
	mAnimList["Jump"] = anim;
}
void CAnimation::setAnim_Crouch(AnimationState* anim) {
	mAnimList["Crouch"] = anim;
}
void CAnimation::setAnim_Idle(AnimationState* anim) {
	mAnimList["Idle"] = anim;
}
*/

void CAnimation::setAnimState(AnimState::animState ms) { //,bool enable
	//if(mCurrentAnim == ms || ms == AnimState::NONE) //mCurrentAnim == ms || 
	//	return;
	//mNextAnim = ms;

	std::list<BodyPart*>::iterator it;
	for(it=mBodyPartsList.begin();it!=mBodyPartsList.end();it++)
	{

		//if((*it)->mCurrentAnim == ms || ms == AnimState::NONE) //mCurrentAnim == ms || 
		//	return;
		//(*it)->mNextAnim = ms;
		//(*it)->getAnim(ms)->getAnimation()->setEnabled(true);
		(*it)->setAnimState(ms);

		//(*it)->setAnimState(ms);
		//(*it)->getAnim(mNextAnim)->getAnimation()->setEnabled(true);
		//if(it->animObj->

		//std::map<AnimState::animState, ApeAnimation*>::iterator iter = it->mAnimList.begin();
		//for(iter=it->mAnimList.begin();iter!=mBodyPartsList.end();iter++)
		//{
		//	iter->
		//}
		//iter = it->mAnimList.find(ms);
		//if(iter != it->mAnimList.end()) {
			//return iter->second;

		//}

		/*it->animObj->getAnimation()->setEnabled(true);*/
	}

	//getAnim(mNextAnim)->getAnimation()->setEnabled(true);
}
/*
void CAnimation::startAnim_Walk() {
	setAnimState("Walk",true,true);
}
void CAnimation::startAnim_Idle() {
	setAnimState("Idle",true,true);
}
void CAnimation::startAnim_Run() {
	setAnimState("Run",true,true); 
}
void CAnimation::startAnim_Jump() {
	setAnimState("Jump",true,true);
}
void CAnimation::startAnim_Crouch() {
	setAnimState("Crouch",true,true);
}
*/

void CAnimation::playAnim(AnimState::animState ms) {
	std::list<BodyPart*>::iterator it;
	for(it=mBodyPartsList.begin();it!=mBodyPartsList.end();it++)
	{
		//delete it;
		
		
		//std::map<AnimState::animState, ApeAnimation*>::iterator iter = it->mAnimList.begin();
		//iter = it->mAnimList.find(ms);
		//if(iter != it->mAnimList.end()) {
		//	return iter->second;
		//}

	}
}

//ApeAnimation* CAnimation::getAnim(AnimState::animState ms) {
//	//return mGOs[id];
//
//	std::map<AnimState::animState, ApeAnimation*>::iterator iter = mAnimList.begin();
//	iter = mAnimList.find(ms);
//	if(iter != mAnimList.end()) {
//		return iter->second;
//	}
//	return NULL;
//}

//Ogre::AnimationState* getAnim