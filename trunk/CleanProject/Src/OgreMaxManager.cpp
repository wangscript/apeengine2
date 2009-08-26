#include "OgreMaxManager.h"

template<> Nebula::OgreMaxManager* Ogre::Singleton<Nebula::OgreMaxManager>::ms_Singleton = 0;

namespace Nebula {

	OgreMaxManager::OgreMaxManager() : OgreMaxSceneCallback ()
	{
		//Set the variables
		//NxWorld = PhysicsManager::getSingleton().getWorld();
		//NxScene = PhysicsManager::getSingleton().getScene();
	}

	OgreMaxManager* OgreMaxManager::getSingletonPtr(void)
	{
		return ms_Singleton;
	}

	OgreMaxManager& OgreMaxManager::getSingleton(void)
	{
		assert( ms_Singleton );  
		return ( *ms_Singleton );
	}

	bool OgreMaxManager::start() {
		//setBindings();
		return true;
	}
	void OgreMaxManager::onSuspend() {


	}
	void OgreMaxManager::update()  {


	}
	void OgreMaxManager::onResume()  {


	}
	void OgreMaxManager::stop()  {


	}

	void OgreMaxManager::setBindings() {

	}

	bool OgreMaxManager::loadSceneFile(const std::string& fileName) {

		mSceneName = fileName;
		mSceneFileName = fileName + ".scene";
		mSceneDirName = fileName;

		std::string scenePath = "../Media/scenes/" + mSceneDirName;
		std::string bakedPath = "../Media/scenes/" + mSceneDirName + "/baked";

		if ( !boost::filesystem::exists( "../Media/scenes/" + mSceneDirName ) ) {
			CLog::Get().Write(LOG_APP,std::string("*** Error cant find location: " + scenePath ).c_str() );
		} else {
			ResourceGroupManager::getSingleton().addResourceLocation(scenePath, "FileSystem", "General");
		}
		
		if ( !boost::filesystem::exists( "../Media/scenes/" + mSceneDirName ) ) {
			CLog::Get().Write(LOG_APP,std::string("*** Error cant find location: " + bakedPath ).c_str() );
		} else {
			ResourceGroupManager::getSingleton().addResourceLocation(bakedPath, "FileSystem", "General");
		}

		if ( !boost::filesystem::exists( "../Media/scenes/" + mSceneDirName + "/" + mSceneFileName ) ) {
			CLog::Get().Write(LOG_APP,std::string("*** Error cant find scene file: " + mSceneFileName ).c_str() );
		} else {
			mOgreMaxScene = new OgreMax::OgreMaxScene ();
			mOgreMaxScene->Load(mSceneFileName, OgreManager::getSingleton().getRoot()->getAutoCreatedWindow(),
			OgreMax::OgreMaxScene::NO_OPTIONS, NULL, NULL, this);
		}
		
		return true;
	}

	void OgreMaxManager::LoadedUserData (const OgreMax::OgreMaxScene *scene, const Ogre::String &userDataReference, const Ogre::String &userData)
	{

	}

	void OgreMaxManager::LoadingSceneFile(const OgreMaxScene* scene, const Ogre::String& fileName, Ogre::String& resourceGroupName) 
	{

	}

	void OgreMaxManager::CreatedCamera(const OgreMax::OgreMaxScene* scene, Ogre::Camera* camera) {
		Ogre::String mParentRoom;
		Ogre::String mTemplateName;
		Ogre::String entireParam = scene->GetObjectExtraData(camera)->userData; 
		
		Ogre::LogManager::getSingleton().logMessage("||Creating Camera...             ||");

		//It will only add if there is existing data
		if (entireParam != "")
		{
			ChildCamera cam;
		
			Ogre::String parentRoom = getParamValue("parentRoom",entireParam);


			cam.name = camera->getName();
			cam.parentName = parentRoom;
			cam.camera = camera;

			mChildCameraList[camera->getName()] = cam;

			Vector3 position = camera->getParentSceneNode()->_getDerivedPosition();
			Quaternion orientation = camera->getParentSceneNode()->_getDerivedOrientation();

			std::string entityName = getParamValue("entityName",entireParam);
			
			mTemplateName = getParamValue("templateName",entireParam);

			//////////////////////////////////////////////////////////////////////////
			// Creation of the Game Object

			std::string objName = camera->getName(); // getParentSceneNode();

			GameObject* go = new GameObject(objName);

			if(mTemplateName != "" && mTemplateName != "undefined")
				go->setTemplateName(mTemplateName);

			CPositionDesc position_desc;
			CPosition *mPos = new CPosition(position_desc);
			Vector3* vec = static_cast<Ogre::Vector3*>(mPos);
			*vec = position;

			go->setComponent(mPos);

			COrientationDesc orientation_desc;
			COrientation *mOr = new COrientation(orientation_desc);
			Quaternion* orient = static_cast<Ogre::Quaternion*>(mOr);
			*orient = orientation;

			go->setComponent(mOr);		

			CRenderDesc renderDesc;
			renderDesc.name = objName + "_SceneNode";

			CRender* render = new CRender(renderDesc);
			go->setComponent(render);

			CCameraDesc camDesc;
			camDesc.name = objName + "_Camera";
			camDesc.initialPosition = position;
			camDesc.initialOrientation = orientation;

			CCamera *camComp = new CCamera(camDesc);
			camComp->setCamera(camera);
			
			go->setComponent(camComp);

			TaskManager::getSingleton().addGameObject(go);


		}
	}

	void OgreMaxManager::CreatedNodeAnimation(const OgreMaxScene* scene, Ogre::SceneNode* Node, Ogre::Animation* animation) {

		Ogre::String animName = animation->getName();
	
		ChildAnimation anim;
		
		anim.node = Node;
		anim.parentName = Node->getName();
		anim.animation = animation;

		mChildAnimationList[animName] = anim;

	}

	void OgreMaxManager::CreatedNodeAnimationTrack(const OgreMaxScene* scene, Ogre::SceneNode* node, Ogre::AnimationTrack* animationTrack, bool enabled, bool looping) {

		Ogre::String animName = animationTrack->getParent()->getName();

		mChildAnimationList[animName].animationTrack = animationTrack;
		mChildAnimationList[animName].loop = looping;
		mChildAnimationList[animName].enabled = enabled;

	}

	void OgreMaxManager::CreatedNodeAnimationState(const OgreMaxScene* scene, Ogre::SceneNode* node, Ogre::AnimationState* animationState) {

		Ogre::String animName = animationState->getAnimationName();
		mChildAnimationList[animName].animState = animationState;
		
	}

	void OgreMaxManager::UpdatedLoadProgress(const OgreMaxScene* scene, Ogre::Real progress) {

	}

	void OgreMaxManager::CreatedLight(const OgreMaxScene* _scene, Ogre::Light* _light) {
		Ogre::String parentRoom;
		Ogre::Quaternion rot;

		Ogre::String mTemplateName;

		Ogre::String entireParam = _scene->GetObjectExtraData(_light)->userData; 

		//Ogre::LogManager::getSingleton().logMessage("||Creating light...             ||");		

		//It will only add if there is existing data
		if (entireParam != "")
		{
			parentRoom = getParamValue("parentRoom",entireParam);
			rot = Ogre::StringConverter::parseQuaternion(getParamValue("rotation",entireParam));
		
			if(getParamValue("enabled",entireParam) == "false")
				return;

			CLog::Get().Write(LOG_APP,"*** Creating Light");

			Vector3 position = _light->getParentSceneNode()->_getDerivedPosition();
			Quaternion orientation = _light->getParentSceneNode()->_getDerivedOrientation();

			std::string entityName = getParamValue("entityName",entireParam);

			mTemplateName = getParamValue("templateName",entireParam);

			//////////////////////////////////////////////////////////////////////////
			// Creation of the Game Object
			std::string objName = _light->getName();

			GameObject* go = new GameObject(objName);
			
			if(mTemplateName != "" && mTemplateName != "undefined")
				go->setTemplateName(mTemplateName);

			CPositionDesc position_desc;
			CPosition *mPos = new CPosition(position_desc);
			Vector3* vec = static_cast<Ogre::Vector3*>(mPos);
			*vec = position;

			go->setComponent(mPos);

			COrientationDesc orientation_desc;
			COrientation *mOr = new COrientation(orientation_desc);
			Quaternion* orient = static_cast<Ogre::Quaternion*>(mOr);
			*orient = orientation;

			go->setComponent(mOr);		

			CRenderDesc renderDesc;
			renderDesc.name = objName + "_SceneNode";

			CRender* render = new CRender(renderDesc);
			go->setComponent(render);

			CLightDesc lightDesc;
			
			lightDesc.name = objName + "_Light";
			
			lightDesc.parentRoom = parentRoom;

			lightDesc.lightType = _light->getType();

			lightDesc.attenuationRange = _light->getAttenuationRange();
			lightDesc.attenuationConstant = _light->getAttenuationConstant();
			lightDesc.attenuationLinear = _light->getAttenuationLinear();
			lightDesc.attenuationQuadratic = _light->getAttenuationQuadric();
			
			lightDesc.diffuseColour = _light->getDiffuseColour();
			lightDesc.specularColour = _light->getSpecularColour();

			if(_light->getType() == Ogre::Light::LT_SPOTLIGHT) {
				lightDesc.innerAngle = _light->getSpotlightInnerAngle();
				lightDesc.outterAngle = _light->getSpotlightOuterAngle();
			}

			if(_light->getType() == Ogre::Light::LT_SPOTLIGHT || _light->getType() == Ogre::Light::LT_DIRECTIONAL) {
				lightDesc.direction = Vector3::UNIT_Z; // getDirection();
				//lightDesc.direction = _light->getParentSceneNode()->_getDerivedOrientation() * Vector3::UNIT_Z; // getDirection();
				//lightDesc.direction = _light->getDirection(); // getDirection();
			}

			CLight* light = new CLight(lightDesc);
			
			go->setComponent(light);

			TaskManager::getSingleton().addGameObject(go);

		}

	}

	void OgreMaxManager::CreatedEntity (const OgreMax::OgreMaxScene* scene, Ogre::Entity* entity)
	{
		//Ogre::LogManager::getSingleton().logMessage("||Creating body...             ||");
		//It will only add if there is existing data
		if (scene->GetObjectExtraData(entity)->userData != "")
		{
			Ogre::String entireParam = scene->GetObjectExtraData(entity)->userData; 
			
			Vector3 mShapeSize;
			Ogre::Quaternion mOrientation;
			Ogre::Vector3 mPosition;
			Ogre::String mEntityName;
			Ogre::String mMeshFileName;
			Ogre::String mShapeType;
			Ogre::String mStatic;
			Ogre::String mBodyType;
			
			Ogre::String mParentRoom;

			Ogre::String mParentNode;
			Ogre::String mChildNode;

			Ogre::Real mMass;

			Ogre::String mSoundFileName;
			Ogre::String mSoundType;
			Ogre::String mSoundSize;

			Ogre::Real mRestitution;
			Ogre::Real mStaticFriction;
			Ogre::Real mDynamicFriction;
			Ogre::Real mLinearDamping;
			Ogre::Real mAngularDamping;
			Ogre::Real mDensity;
			
			bool mIsParent;

			Ogre::String mTextureFileName;
			Ogre::String mCameraRoomName;
			Ogre::String mTextureTilingU;
			Ogre::String mTextureTilingV;

			bool mIsParticle;
			Ogre::String mParticleScriptName;

			bool mIsCharacter;
			Ogre::String mCharacterName;
			Ogre::String mDiagramFileName;
			Ogre::String mAnimationFileName;
			Ogre::String mCharacterMeshName;

			Ogre::String mPhysicsShapeType;
			Ogre::String mTemplateName;

			Ogre::String mIsRoom;
			Ogre::String mIsWeapon;
			Ogre::String mIsPickableItem;

			Ogre::String mIsSwitch;
			Ogre::String mIsDoor;
			Ogre::String mIsElevator;
			Ogre::String mIsQuestItem;

			Ogre::String mIsHumanoid;
			Ogre::String mIsSmallCreature;

			//////////////////////////////////////////////////////////////////////////
			//Get parameters from User Data.
			
			//Game Object Name
			mEntityName = getParamValue("entityName",entireParam);

			//Mesh File Name
			mMeshFileName = getParamValue("meshName",entireParam);

			//1: "ParentRoom"
			//2: "Portal"
			mShapeType = getParamValue("shapeType",entireParam);

			//Tells if the entity is static or dynamic:
			//1: "yes"
			//2: "no"
			mStatic = getParamValue("static",entireParam);

			//1: "Actor"
			//2: "Body"
			//3: "Mesh"
			//4: "Shape"
			mBodyType = getParamValue("bodyType",entireParam);

			//Name of the parent of this object
			mParentRoom = getParamValue("parentRoom",entireParam); //
			
			mParentNode = getParamValue("parentNode",entireParam);
			//mChildNode = getParamValue("childNode",entireParam);

			//Mass of the object
			mMass = Ogre::StringConverter::parseReal(getParamValue("mass",entireParam));

			//Position
			mPosition =  entity->getParentSceneNode()->_getDerivedPosition();

			//Orientation
			mOrientation = entity->getParentSceneNode()->_getDerivedOrientation(); // getOrientation()
			
			//Sound File Name
			mSoundFileName = getParamValue("soundName",entireParam);

			//Sound type:
			//1: predefined
			//2: custom
			mSoundType = getParamValue("soundType",entireParam);

			//Weight of the object emmiting sound:
			//1: light
			//2: medium
			//3: heavy
			mSoundSize = getParamValue("soundSize",entireParam);

			//Restitution of the physical material
			mRestitution = Ogre::StringConverter::parseReal(getParamValue("restitution",entireParam));

			//Static Friction of the physical material
			mStaticFriction = Ogre::StringConverter::parseReal(getParamValue("staticFriction",entireParam));

			//Dynamic friction of the material
			mDynamicFriction = Ogre::StringConverter::parseReal(getParamValue("dynamicFriction",entireParam));

			//Linear Damping of the object
			mLinearDamping = Ogre::StringConverter::parseReal(getParamValue("linearDamping",entireParam));

			//Angular Damping of the object
			mAngularDamping = Ogre::StringConverter::parseReal(getParamValue("angularDamping",entireParam));

			//Density of the object
			mDensity = Ogre::StringConverter::parseReal(getParamValue("density",entireParam));
			
			//File name of the texture of this object
			mTextureFileName = getParamValue("texFileName",entireParam);

			//Name of the room wich this camera belong to (if there is one)
			mCameraRoomName = getParamValue("cameraName",entireParam);

			//Tiling of the texture of this materials object
			mTextureTilingU = getParamValue("texU_Tiling",entireParam);
			mTextureTilingV = getParamValue("texV_Tiling",entireParam);

			//Is this a Particle?
			mIsParticle = Ogre::StringConverter::parseBool(getParamValue("isParticle",entireParam));

			//Particle Script Name (not the file name)
			mParticleScriptName = getParamValue("particleName",entireParam);

			mIsCharacter = Ogre::StringConverter::parseBool(getParamValue("isCharacter",entireParam));
			mCharacterName = getParamValue("characterName",entireParam);
			mCharacterMeshName = getParamValue("characterMeshName",entireParam);
			mDiagramFileName = getParamValue("diagramFile",entireParam);
			mAnimationFileName = getParamValue("animationFile",entireParam);

			mPhysicsShapeType = getParamValue("physicsMeshType",entireParam);

			//Rotation of the object
			Ogre::Quaternion physicsRot = Ogre::StringConverter::parseQuaternion(getParamValue("rotation",entireParam));

			mTemplateName = getParamValue("templateName",entireParam);
			
			mIsRoom = getParamValue("isRoom",entireParam);

			mIsWeapon = getParamValue("isWeapon",entireParam);

			mIsPickableItem = getParamValue("isPickableItem",entireParam);

			mIsSwitch = getParamValue("isSwitch",entireParam);
			mIsDoor = getParamValue("isDoor",entireParam);
			mIsElevator = getParamValue("isElevator",entireParam);
			mIsQuestItem = getParamValue("isQuestItem",entireParam);

			mIsHumanoid = getParamValue("isHumanoid",entireParam);
			mIsSmallCreature = getParamValue("isSmallCreature",entireParam);

			Ogre::String childName = getParamValue("childNode1",entireParam);
			if(childName != "")
				mIsParent = true;
			else
				mIsParent = false;

			mShapeSize = Vector3::ZERO;
			if(mShapeType == "Sphere") {
				Real ps = Ogre::StringConverter::parseReal(getParamValue("size",entireParam));
				mShapeSize = Vector3(ps,0,0);
			}
			if(mShapeType == "Capsule") {
				Vector2 ps = Ogre::StringConverter::parseVector2(getParamValue("size",entireParam));
				mShapeSize = Vector3(ps.x,ps.y,0);
			}
			if(mShapeType == "Box") {
				Vector3 ps = Ogre::StringConverter::parseVector3(getParamValue("size",entireParam));
				mShapeSize = Vector3(ps.x,ps.y,ps.z);
			}
			if(mShapeType == "ParentRoom") {
				Vector3 ps = Ogre::StringConverter::parseVector3(getParamValue("size",entireParam));
				mShapeSize = Vector3(ps.x,ps.y,ps.z);
			}
			
			if(mShapeType == "Portal")
				return;

			//////////////////////////////////////////////////////////////////////////
			// Creation of the Game Object

			GameObject* go = new GameObject(mEntityName);

			CPositionDesc position_desc;
			CPosition *mPos = new CPosition(position_desc);

			mPos->x = mPosition.x;
			mPos->y = mPosition.y;
			mPos->z = mPosition.z;
						
			go->setComponent(mPos);

			COrientationDesc orientation_desc;
			COrientation *mOr = new COrientation(orientation_desc);

			mOr->w = mOrientation.w;
			mOr->x = mOrientation.x;
			mOr->y = mOrientation.y;
			mOr->z = mOrientation.z;
			
			go->setComponent(mOr);		

			CRenderDesc renderDesc;
			renderDesc.name = mEntityName + "_SceneNode";

			CRender* render = new CRender(renderDesc);
			go->setComponent(render);

			if( mBodyType == "Shape" ) {
				
				CLog::Get().Write(LOG_APP,std::string("Creating Shape " + mEntityName).c_str());

				if(mParentNode != "undefined" && mParentNode != "") {
				
					ChildShape cd;
					
					cd.parentName = mParentNode;
					cd.name = mEntityName + "_Shape";
				
					cd.shapeType = mShapeType;
					cd.shapeFileType = mPhysicsShapeType;
					cd.path = mEntityName + ".mesh.nxs";
					cd.shapeSize = mShapeSize;
					cd.position = entity->getParentSceneNode()->getPosition(); //Relative position to the parent, since shapes MUST be childs
					cd.orientation = mOrientation;
					cd.mass = mMass;
					cd.skinWidth = 0.0f;
					cd.restitution = mRestitution;
					cd.dynamicFriction = mDynamicFriction;
					cd.staticFriction = mStaticFriction;

					mChildShapeList[cd.name] = cd;

				}
				
				return;
			
			}

			if(mTemplateName != "" && mTemplateName != "undefined")
				go->setTemplateName(mTemplateName);

			if(mIsSwitch != "" && mIsSwitch != "undefined") {
				CSwitchDesc desc;
				desc.name = mEntityName + "_Switch";
				
				CSwitch* comp = new CSwitch(desc);
				go->setComponent(comp);
			}
			if(mIsDoor != "" && mIsDoor != "undefined") {
				CDoorDesc desc;
				desc.name = mEntityName + "_Door";
				
				CDoor* comp = new CDoor(desc);
				go->setComponent(comp);
			}
			if(mIsElevator != "" && mIsElevator != "undefined") {
				CElevatorDesc desc;
				desc.name = mEntityName + "_Elevator";
				
				CElevator* comp = new CElevator(desc);
				go->setComponent(comp);
			}
			if(mIsQuestItem != "" && mIsQuestItem != "undefined") {
				CQuestDesc desc;
				desc.name = mEntityName + "_QuestItem";
				
				CQuest* comp = new CQuest(desc);
				go->setComponent(comp);
			}

			//Its a character
			if(mIsCharacter) {

				CLog::Get().Write(LOG_APP,std::string("Creating Character " + mEntityName).c_str());

				CMeshDesc meshDesc;
				meshDesc.name = mEntityName + "_Mesh";
				meshDesc.fileName = mCharacterMeshName;
				meshDesc.materialName = "";

				CMesh* mesh = new CMesh(meshDesc);

				go->setComponent(mesh);

				CCharacterControllerDesc characterDesc;
				characterDesc.name = mCharacterName;
				characterDesc.resourceFileName = "CharacterExample";

				CCharacterController* character = new CCharacterController(characterDesc);
				go->setComponent(character);
				
				CCharacterAnimationDesc animationDesc;
				animationDesc.name = mCharacterName + "_Anim";
				animationDesc.diagramFileName = mDiagramFileName;
				animationDesc.animationFileName = mAnimationFileName;

				CCharacterAnimation* anim = new CCharacterAnimation(animationDesc);
				go->setComponent(anim);

				CInventoryDesc invDesc;

				CInventory* inventory = new CInventory(invDesc);
				go->setComponent(inventory);

				CHealthDesc healthDesc;
				CHealth* health = new CHealth(healthDesc);
				go->setComponent(health);

				if(mIsHumanoid != "" && mIsHumanoid != "undefined") {
					CHumanoidDesc humanDesc;
					humanDesc.name = mEntityName + "_Humanoid";

					CHumanoid* human = new CHumanoid(humanDesc);
					go->setComponent(human);
				}
				if(mIsSmallCreature != "" && mIsSmallCreature != "undefined") {
					CSmallCreatureDesc creatureDesc;
					creatureDesc.name = mEntityName + "_Creature";

					CSmallCreature* creature = new CSmallCreature(creatureDesc);
					go->setComponent(creature);
				}

				TaskManager::getSingleton().addGameObject(go);
				return;

			}

			//Its a trigger
			if(mShapeType == "ParentRoom") {
				
				CLog::Get().Write(LOG_APP,std::string("Creating Room " + mEntityName).c_str());

				CPhysicsTriggerDesc triggerDesc;

				CPhysicsTrigger* trigger = new CPhysicsTrigger(triggerDesc);
				
				trigger->getDescription().name = mEntityName + "_Trigger";
				trigger->getDescription().initialPosition = mPosition;
				
				if(mStatic == "yes") {
					trigger->getDescription().isStatic = true;
				} else {

					//trigger->getDescription().bodyDesc.flags |= NX_BF_KINEMATIC;

					trigger->getDescription().bodyDesc.angularDamping = mAngularDamping;
					trigger->getDescription().bodyDesc.linearDamping = mLinearDamping;
					trigger->getDescription().actorDesc.body = &trigger->getDescription().bodyDesc;
					trigger->getDescription().actorDesc.density = mDensity;
					
				}

				trigger->getDescription().actorDesc.globalPose.t = NxTools::convert(mPosition);

				go->setComponent(trigger);
				
				CMeshDesc meshDesc;
				meshDesc.name = mEntityName + "_Mesh";
				meshDesc.fileName = mMeshFileName;
				meshDesc.materialName = "";

				CMesh* mesh = new CMesh(meshDesc);
				
				go->setComponent(mesh);

				CRoomDesc roomDesc;
				roomDesc.name = mEntityName + "_Room";
				roomDesc.mainCameraName = mCameraRoomName;
				CRoom* room = new CRoom(roomDesc);
				go->setComponent(room);

				//If its a trigger im done, quit.
				TaskManager::getSingleton().addGameObject(go);
				return;

			}

			if(mIsParticle) {
				CLog::Get().Write(LOG_APP,std::string("Creating Particle " + mEntityName).c_str());
				
				CParticleDesc partDesc;
				partDesc.name = mEntityName + "_Particle";
				partDesc.particleScriptName = mParticleScriptName;

				CParticle* particle = new CParticle(partDesc);
				go->setComponent(particle);

				TaskManager::getSingleton().addGameObject(go);
				return;
			}
			
			//Its an actor (only physical entity)
			if( mBodyType == "Actor" ) {

				CLog::Get().Write(LOG_APP,std::string("Creating Actor " + mEntityName).c_str());

				CPhysicsActorDesc physics_desc;

				CPhysicsActor* actor = new CPhysicsActor(physics_desc);

				actor->getDescription().name = mEntityName + "_Actor";
				actor->getDescription().initialPosition = mPosition;
				//actor->getDescription().initialOrientation  = mOrientation;

				if(mStatic == "yes") {
					actor->getDescription().isStatic = true;
				} else {
					actor->getDescription().bodyDesc.angularDamping = mAngularDamping;
					actor->getDescription().bodyDesc.linearDamping = mLinearDamping;
					actor->getDescription().actorDesc.body = &actor->getDescription().bodyDesc;
					actor->getDescription().actorDesc.density = mDensity;
				}
				
				actor->getDescription().actorDesc.globalPose.t = NxTools::convert(mPosition);
				//actor->getDescription().actorDesc.globalPose.M.fromQuat(NxTools::convert(mOrientation));

				NxShapeDesc* shape = getShapeDesc(Ogre::Vector3::ZERO,mShapeType,mPhysicsShapeType,mEntityName + ".mesh.nxs",mShapeSize,Ogre::Vector3::ZERO,mOrientation,mMass,mDensity,0.0f,mRestitution,mDynamicFriction,mStaticFriction);
				actor->getDescription().actorDesc.shapes.pushBack(shape);

				go->setComponent(actor);

				TaskManager::getSingleton().addGameObject(go);

				//////////////////////////////////////////////////////////////////////////
				if(mIsWeapon != "" && mIsWeapon != "undefined") {
					CWeaponDesc wd;

					CWeapon* weapon = new CWeapon(wd);

					go->setComponent(weapon);
				} else {
					if(mIsPickableItem != "" && mIsPickableItem != "undefined") {
						CItemDesc wd;

						CItem* item = new CItem(wd);

						go->setComponent(item);
					}
				}
				//////////////////////////////////////////////////////////////////////////

				return;

			}

			//Its a body (Visual representation and Actor)
			if( mBodyType == "Body" ) {

				CLog::Get().Write(LOG_APP,std::string("Creating Body " + mEntityName).c_str());

				CMeshDesc meshDesc;
				meshDesc.name = mEntityName + "_Mesh";
				meshDesc.fileName = mMeshFileName;
				meshDesc.materialName = "";
				
				meshDesc.textureFileName = mTextureFileName;
				meshDesc.textureTileU = mTextureTilingU;
				meshDesc.textureTileV = mTextureTilingV;

				CMesh* mesh = new CMesh(meshDesc);

				go->setComponent(mesh);

				CPhysicsActorDesc physics_desc;
				
				CPhysicsActor* actor = new CPhysicsActor(physics_desc);

				actor->getDescription().name = mEntityName + "_Actor";
				actor->getDescription().initialPosition = mPosition;

				if(mStatic == "yes") {
					actor->getDescription().isStatic = true;
				} else {
					actor->getDescription().bodyDesc.angularDamping = mAngularDamping;
					actor->getDescription().bodyDesc.linearDamping = mLinearDamping;
					actor->getDescription().actorDesc.body = &actor->getDescription().bodyDesc;
					actor->getDescription().actorDesc.density = mDensity;
				}
				
				actor->getDescription().actorDesc.globalPose.t = NxTools::convert(mPosition);
				//actor->getDescription().actorDesc.globalPose.M.fromQuat(NxTools::convert(mOrientation));

				NxShapeDesc* shape = getShapeDesc(Ogre::Vector3::ZERO,mShapeType,mPhysicsShapeType,mEntityName + ".mesh.nxs",mShapeSize,Ogre::Vector3::ZERO,mOrientation,mMass,mDensity,0.0f,mRestitution,mDynamicFriction,mStaticFriction);
				actor->getDescription().actorDesc.shapes.pushBack(shape);

				go->setComponent(actor);

				TaskManager::getSingleton().addGameObject(go);

				//////////////////////////////////////////////////////////////////////////
				if(mIsWeapon != "" && mIsWeapon != "undefined") {
					CWeaponDesc wd;

					CWeapon* weapon = new CWeapon(wd);

					go->setComponent(weapon);
				} else {
					if(mIsPickableItem != "" && mIsPickableItem != "undefined") {
						CItemDesc wd;

						CItem* item = new CItem(wd);

						go->setComponent(item);
					}
				}
				//////////////////////////////////////////////////////////////////////////

				return;
			}


			//Not a particle, but a mesh
			if( mBodyType == "Mesh" ) { //!mIsParticle &&

				CLog::Get().Write(LOG_APP,std::string("Creating Mesh " + mEntityName).c_str());

				CMeshDesc meshDesc;
				meshDesc.name = mEntityName + "_Mesh";
				meshDesc.fileName = mMeshFileName;
				meshDesc.materialName = "";
				
				meshDesc.textureFileName = mTextureFileName;
				meshDesc.textureTileU = mTextureTilingU;
				meshDesc.textureTileV = mTextureTilingV;

				CMesh* mesh = new CMesh(meshDesc);

				go->setComponent(mesh);

				std::string childNode1 = getParamValue("childNode1",entireParam);
				
				//If the mesh has child objects then it means its has a CPhysicsActor
				if(childNode1 != "undefined" && childNode1 != "") {
					
					CPhysicsActorDesc physics_desc;

					CPhysicsActor* actor = new CPhysicsActor(physics_desc);

					actor->getDescription().name = mEntityName + "_Actor";
					actor->getDescription().initialPosition = mPosition;

					if(mStatic == "yes") {
						actor->getDescription().isStatic = true;
					} else {
						actor->getDescription().bodyDesc.angularDamping = mAngularDamping;
						actor->getDescription().bodyDesc.linearDamping = mLinearDamping;
						actor->getDescription().actorDesc.body = &actor->getDescription().bodyDesc;
						actor->getDescription().actorDesc.density = mDensity;
					}

					actor->getDescription().actorDesc.globalPose.t = NxTools::convert(mPosition);
					//actor->getDescription().actorDesc.globalPose.M.fromQuat(NxTools::convert(mOrientation));

					go->setComponent(actor);
					
				}
				TaskManager::getSingleton().addGameObject(go);

				//////////////////////////////////////////////////////////////////////////
				if(mIsWeapon != "" && mIsWeapon != "undefined") {
					CWeaponDesc wd;

					CWeapon* weapon = new CWeapon(wd);

					go->setComponent(weapon);
				} else {
					if(mIsPickableItem != "" && mIsPickableItem != "undefined") {
						CItemDesc wd;

						CItem* item = new CItem(wd);

						go->setComponent(item);
					}
				}
				//////////////////////////////////////////////////////////////////////////

			}
			

			
		}
		
	}

	void OgreMaxManager::FinishedLoad (const OgreMax::OgreMaxScene* scene, bool success)
	{
		if (success)
			Ogre::LogManager::getSingleton().logMessage("||Load successful!             ||");
		else
			Ogre::LogManager::getSingleton().logMessage("||Load failed!                 ||");
		Ogre::LogManager::getSingleton().logMessage("=================================");

		Ogre::String nname;
		OgreMaxScene* maxScene = (OgreMaxScene*)scene; // -> GetSceneManager()->destroySceneNode(entity->getParentSceneNode());
	
		setChildShapesToParents(maxScene);

		TaskManager::getSingleton().setupGameObjects();

		setCamerasToObjects(maxScene);

		//Ogre::Camera* cam = maxScene->GetSceneManager()->getCamera("Camera01_Level01");
		//Ogre::Camera* myCam = OgreManager::getSingleton().getCamera();
		//
		//myCam->setPosition(cam->getParentSceneNode()->_getDerivedPosition());
		//myCam->setOrientation(cam->getParentSceneNode()->_getDerivedOrientation());
		//myCam->setFOVy(cam->getFOVy());
		//myCam->setAspectRatio(1.33333);
		//
		//myCam->setNearClipDistance(0.01);
		//myCam->setFarClipDistance(1000);

		//Ogre::Camera* cam = OgreManager::getSingleton().getCamera();
		//cam = myCam;

		//We set Game Object herarchy used in 3Ds Max.
		//std::map<std::string, GameObject*>::iterator iter;
		//for(iter = mChildGameObjectsList.begin(); iter != mChildGameObjectsList.end(); iter++) {
		//	
		//	CRender *mCRender = dynamic_cast<CRender*>(iter->second->getComponent("CRender"));
		//	
		//	//If parent object name is not empty assign the parent and child
		//	if(iter->first != "" && iter->first != "undefined") {
		//		GameObject* tmpParent = TaskManager::getSingleton().getGameObject(iter->first);
		//		iter->second->setParent(tmpParent);
		//		tmpParent->setChild(iter->second);
		//	}
		//}
		
		

	}
	
	void OgreMaxManager::setChildShapesToParents(OgreMaxScene* maxScene) {
		std::map<const std::string, GameObject*> gos;
		gos  = TaskManager::getSingleton().getGameObjects();
		std::map<const std::string, GameObject*>::iterator iter;

		for(iter = gos.begin(); iter != gos.end(); iter++) {

			CMesh *mesh = dynamic_cast<CMesh*>(iter->second->getComponent("CMesh"));
			CPosition *pos = dynamic_cast<CPosition*>(iter->second->getComponent("CPosition"));
			COrientation *orient = dynamic_cast<COrientation*>(iter->second->getComponent("COrientation"));
			CPhysicsActor *actor = dynamic_cast<CPhysicsActor*>(iter->second->getComponent("CPhysicsActor"));
			CPhysicsTrigger *trigger = dynamic_cast<CPhysicsTrigger*>(iter->second->getComponent("CPhysicsTrigger"));
			CRender *render = dynamic_cast<CRender*>(iter->second->getComponent("CRender"));
			//CRoom *room = dynamic_cast<CRoom*>(iter->second->getComponent("CRoom"));

			//////////////////////////////////////////////////////////////////////////
			// For Actors/Bodies
			if(mesh && pos && orient && actor) {
				
				std::map<const std::string, ChildShape>::iterator shapeIter;
				for(shapeIter = mChildShapeList.begin(); shapeIter != mChildShapeList.end(); shapeIter++) {

					std::string objName = actor->getOwnerObject()->getID();
					std::string parentName = shapeIter->second.parentName;
					if( objName == parentName) {

						Ogre::Vector3 parentPosition = NxTools::convert(actor->getDescription().actorDesc.globalPose.t);
						NxVec3 parentPos = NxVec3( actor->getDescription().actorDesc.globalPose.t );

						std::string type = shapeIter->second.shapeType;
						std::string physicsType = shapeIter->second.shapeFileType;
						std::string path = shapeIter->second.path;
						Vector3 position = shapeIter->second.position;
						Quaternion quat = shapeIter->second.orientation;
						Vector3 shapeSize = shapeIter->second.shapeSize;
						Real mass = shapeIter->second.mass;
						Real density = shapeIter->second.density;
						Real restitution = shapeIter->second.restitution;
						Real dynamicFriction = shapeIter->second.dynamicFriction;
						Real staticFriction = shapeIter->second.staticFriction;

						NxShapeDesc* shape = getShapeDesc(parentPosition,type,physicsType,path,shapeSize,position,quat,mass,density,0.0f,restitution,dynamicFriction,staticFriction);

						actor->getDescription().actorDesc.shapes.pushBack(shape);

					}
				}
			}

			//////////////////////////////////////////////////////////////////////////
			// For triggers
			if(pos && orient && trigger) {

				std::map<const std::string, ChildShape>::iterator shapeIter;
				for(shapeIter = mChildShapeList.begin(); shapeIter != mChildShapeList.end(); shapeIter++) {

					std::string objName = trigger->getOwnerObject()->getID();
					std::string parentName = shapeIter->second.parentName;
					if( objName == parentName) {
						
						Ogre::Vector3 parentPosition = NxTools::convert(trigger->getDescription().actorDesc.globalPose.t);
						NxVec3 parentPos = NxVec3( trigger->getDescription().actorDesc.globalPose.t );

						std::string type = shapeIter->second.shapeType;
						std::string physicsType = shapeIter->second.shapeFileType;
						std::string path = shapeIter->second.path;
						Vector3 position = shapeIter->second.position;
						Quaternion quat = shapeIter->second.orientation;
						Vector3 shapeSize = shapeIter->second.shapeSize;
						Real mass = shapeIter->second.mass;
						Real density = shapeIter->second.density;
						Real restitution = shapeIter->second.restitution;
						Real dynamicFriction = shapeIter->second.dynamicFriction;
						Real staticFriction = shapeIter->second.staticFriction;

						NxShapeDesc* shape = getShapeDesc(parentPosition,type,physicsType,path,shapeSize,position,quat,mass,density,0.0f,restitution,dynamicFriction,staticFriction);

						shape->shapeFlags |= NX_TRIGGER_ENABLE;

						trigger->getDescription().actorDesc.shapes.pushBack(shape);

					}
				}
			}
			//////////////////////////////////////////////////////////////////////////
			// Animations
			if(pos && orient && render) {
		
				CAnimation *animation = NULL;

				std::string n = render->getOwnerObject()->getID();

				std::map<const std::string, ChildAnimation>::iterator shapeIter;
				for(shapeIter = mChildAnimationList.begin(); shapeIter != mChildAnimationList.end(); shapeIter++) {
					std::string objName = render->getOwnerObject()->getID();
					std::string parentName = shapeIter->second.parentName;
					if( objName == parentName) {

						CAnimationDesc ad;
						ad.name = objName + "_Anim";

						animation = new CAnimation(ad);

						break;
					}

				}

				for(shapeIter = mChildAnimationList.begin(); shapeIter != mChildAnimationList.end(); shapeIter++) {

					std::string objName = render->getOwnerObject()->getID();
					std::string parentName = shapeIter->second.parentName;
					if( objName == parentName) {

						Ogre::Animation* anim = shapeIter->second.animation;
						Ogre::AnimationTrack* track = shapeIter->second.animationTrack;
						Ogre::AnimationState* animState = shapeIter->second.animState;
						Ogre::SceneNode* node = shapeIter->second.node;
						
						if(animation)
							animation->addAnimation(anim, animState->getEnabled(), animState->getLoop() );

					}
				}

				if(animation)
					render->getOwnerObject()->setComponent(animation);
			}
			//////////////////////////////////////////////////////////////////////////

		}

	}

	void OgreMaxManager::setCamerasToObjects(OgreMaxScene* maxScene) {
		std::map<const std::string, GameObject*> gos;
		gos  = TaskManager::getSingleton().getGameObjects();
		std::map<const std::string, GameObject*>::iterator iter;
		for(iter = gos.begin(); iter != gos.end(); iter++) {

			CRoom *room = dynamic_cast<CRoom*>(iter->second->getComponent("CRoom"));
			if(room) {
				std::map<const std::string, ChildCamera>::iterator camIter;
				for(camIter = mChildCameraList.begin(); camIter != mChildCameraList.end(); camIter++) {
					std::string objName = iter->second->getID();
					std::string parentName = camIter->second.parentName;
					if( objName == parentName) {
						if(camIter->second.camera)
							room->setCamera(camIter->second.camera);
					}
				}
			} else {
				//no room

			}
		}
	}

	Ogre::String OgreMaxManager::getParamValue (Ogre::String paramName,Ogre::String param)
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

	NxShapeDesc* OgreMaxManager::getShapeDesc(Ogre::Vector3 parentPos, std::string shapeType,std::string shapeFileType,std::string path, Ogre::Vector3 shapeSize,Ogre::Vector3 position, Ogre::Quaternion orientation, Ogre::Real mass, Ogre::Real density, Ogre::Real skinWidth, Ogre::Real restitution, Ogre::Real dynamicFriction, Ogre::Real staticFriction) {

		if (shapeType == "EditableMesh")
		{
			if(shapeFileType == "Convex") {
				NxConvexShapeDesc* shape = new NxConvexShapeDesc();
				shape->meshData	= getConvexMesh(path);

				shape->mass = mass;
				shape->density = density;
				shape->skinWidth = skinWidth;
				//shape.shapeFlags = sd.shapeFlags;
				//shape.localPose.t = NxTools::convert(position);
				
				NxVec3 offset = NxTools::convert(position); // - NxTools::convert(parentPos)
				shape->localPose.t = offset;
				shape->localPose.M.fromQuat(NxTools::convert(orientation));

				NxMaterialDesc  m;
				m.restitution   = restitution;
				m.staticFriction  = staticFriction;
				m.dynamicFriction = dynamicFriction;

				NxMaterialIndex mat = PhysicsManager::getSingleton().getScene()->createMaterial(m)->getMaterialIndex();
				shape->materialIndex = mat;

				return ( static_cast<NxShapeDesc*>(shape) );

			} else if(shapeFileType == "Triangle") {

				NxTriangleMeshShapeDesc* shape = new NxTriangleMeshShapeDesc();
				shape->meshData	= getTriangleMesh(path);

				shape->mass = mass;
				shape->density = density;
				shape->skinWidth = skinWidth;
				//shape.shapeFlags = sd.shapeFlags;
				NxVec3 offset = NxTools::convert(position); // - NxTools::convert(parentPos)
				shape->localPose.t = offset;
				shape->localPose.M.fromQuat(NxTools::convert(orientation));

				NxMaterialDesc  m;
				m.restitution   = restitution;
				m.staticFriction  = staticFriction;
				m.dynamicFriction = dynamicFriction;

				NxMaterialIndex mat = PhysicsManager::getSingleton().getScene()->createMaterial(m)->getMaterialIndex();
				shape->materialIndex = mat;

				return ( static_cast<NxShapeDesc*>(shape) );
				//return (NxShapeDesc&)(shape);
			}

			//////////////////////////////////////////////////////////////////////////

		} else if (shapeType == "Box") {

			NxBoxShapeDesc* shape = new NxBoxShapeDesc();
			shape->dimensions = NxVec3(shapeSize.x,shapeSize.y,shapeSize.z);

			shape->mass = mass;
			shape->density = density;
			shape->skinWidth = skinWidth;
			//shape.shapeFlags = sd.shapeFlags;
			//shape.localPose.t = NxTools::convert(position);
			NxVec3 offset = NxTools::convert(position); // - NxTools::convert(parentPos)
			shape->localPose.t = offset;
			shape->localPose.M.fromQuat(NxTools::convert(orientation));

			NxMaterialDesc  m;
			m.restitution   = restitution;
			m.staticFriction  = staticFriction;
			m.dynamicFriction = dynamicFriction;

			NxMaterialIndex mat = PhysicsManager::getSingleton().getScene()->createMaterial(m)->getMaterialIndex();
			shape->materialIndex = mat;

			return ( static_cast<NxShapeDesc*>(shape) );
			//return ( static_cast<NxShapeDesc&>(shape) );

			//////////////////////////////////////////////////////////////////////////

		} else if (shapeType == "Sphere") {
			NxSphereShapeDesc* shape = new NxSphereShapeDesc();
			shape->radius = shapeSize.x;

			shape->mass = mass;
			shape->density = density;
			shape->skinWidth = skinWidth;
			//shape.shapeFlags = sd.shapeFlags;
			//shape.localPose.t = NxTools::convert(position);
			NxVec3 offset = NxTools::convert(position); // - NxTools::convert(parentPos)
			shape->localPose.t = offset;
			shape->localPose.M.fromQuat(NxTools::convert(orientation));

			NxMaterialDesc  m;
			m.restitution   = restitution;
			m.staticFriction  = staticFriction;
			m.dynamicFriction = dynamicFriction;

			NxMaterialIndex mat = PhysicsManager::getSingleton().getScene()->createMaterial(m)->getMaterialIndex();
			shape->materialIndex = mat;

			return ( static_cast<NxShapeDesc*>(shape) );

			//////////////////////////////////////////////////////////////////////////

		} if (shapeType == "Capsule") {

			NxCapsuleShapeDesc* shape = new NxCapsuleShapeDesc();
			shape->radius = shapeSize.x;
			shape->height = shapeSize.y;

			shape->mass = mass;
			shape->density = density;
			shape->skinWidth = skinWidth;
			//shape.shapeFlags = sd.shapeFlags;
			//shape.localPose.t = NxTools::convert(position);
			NxVec3 offset = NxTools::convert(position); // - NxTools::convert(parentPos)
			shape->localPose.t = offset;
			shape->localPose.M.fromQuat(NxTools::convert(orientation));

			NxMaterialDesc  m;
			m.restitution   = restitution;
			m.staticFriction  = staticFriction;
			m.dynamicFriction = dynamicFriction;

			NxMaterialIndex mat = PhysicsManager::getSingleton().getScene()->createMaterial(m)->getMaterialIndex();
			shape->materialIndex = mat;

			return ( static_cast<NxShapeDesc*>(shape) );

		}
		return NULL;
	}

	MeshType OgreMaxManager::getMeshTypeFromResource(FileResource* resource) {

		if (resource->size() < 8)
			return MT_Unknown;

		// Read the "NXS" Header.
		{
			char header[3] = {0, 0, 0};
			resource->get(&header, 3);
			if (!(header[0] == 'N' && header[1] == 'X' && header[2] == 'S'))
				return MT_Unknown;
		}

		// Skip forward a Byte (Usually x01)
		resource->skip(1);

		char mesh_header[4] = {0, 0, 0, 0};
		resource->get(&mesh_header, 4);

		resource->rewind();


		if (mesh_header[0] == 'M' &&
			mesh_header[1] == 'E' &&
			mesh_header[2] == 'S' &&
			mesh_header[3] == 'H')
		{
			return MT_Triangle;
		}
		else if (mesh_header[0] == 'C' &&
			mesh_header[1] == 'V' &&
			mesh_header[2] == 'X' &&
			mesh_header[3] == 'M')
		{
			return MT_Convex;
		}
		/** More here */
		else
		{
			return MT_Unknown;
		}

	}

	NxTriangleMesh* OgreMaxManager::getTriangleMesh(const std::string& fileName) {

		Ogre::String path = "../media/scenes/" + mSceneDirName + "/" + fileName;

		if ( !boost::filesystem::exists( path ) ) {
			CLog::Get().Write(LOG_APP,std::string("*** Error with Triangle Mesh file, file not found. File: " + path).c_str() );
		}

		FileResource* resource = new FileResource(path,RA_Read);

		if(!resource)
			return NULL;

		MeshType mt = getMeshTypeFromResource(resource);

		if(mt == MT_Triangle) {
			NxTriangleMesh* mesh = PhysicsManager::getSingleton().getSDK()->createTriangleMesh(*resource);
			return mesh;
		}

		return NULL;
	}

	NxConvexMesh* OgreMaxManager::getConvexMesh(const std::string& fileName) {

		Ogre::String path = "../media/scenes/" + mSceneDirName + "/" + fileName;

		if ( !boost::filesystem::exists( path ) ) {
			CLog::Get().Write(LOG_APP,std::string("*** Error with Convex Mesh file, file not found. File: " + path).c_str() );
		}

		FileResource* resource = new FileResource(path,RA_Read);

		if(!resource)
			return NULL;

		MeshType mt = getMeshTypeFromResource(resource);

		if(mt == MT_Convex) {
			NxConvexMesh* mesh = PhysicsManager::getSingleton().getSDK()->createConvexMesh(*resource);
			return mesh;
		}

		return NULL;
	}

	

} //end namespace