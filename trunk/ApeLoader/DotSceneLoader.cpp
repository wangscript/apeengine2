#include "DotSceneLoader.h"
//#include "GameSystemManager.h"
#include "NxOgreHelpers.h"

#include "Physics.h"
#include "CRender.h"
#include "CMesh.h"
#include "CPosition.h"
#include "COrientation.h"
#include "CRoom.h"
#include "CPortal.h"
#include "CActor.h"
#include "CAnimation.h"
#include "CCAmera.h"
#include "CCharacter.h"
#include "CLight.h"
#include "CWeapon.h"
#include "CSound.h"
#include "CParticle.h"

#include "OgreRender.h"

class OgreRender;

OgreMaxSceneCallbacks::OgreMaxSceneCallbacks(NxOgre::Scene* s) : OgreMaxSceneCallback ()
{
	//Copy scene
	NxScene = s;
	NxWorld = NULL;
}

OgreMaxSceneCallbacks::OgreMaxSceneCallbacks(Ogre::Vector3 initPos) : OgreMaxSceneCallback ()
{
	//Set the variables
	NxWorld = Physics::getSingleton().getWorld();
	NxScene = Physics::getSingleton().getScene();
	mScenePosition = initPos;
}

void OgreMaxSceneCallbacks::LoadedUserData (const OgreMax::OgreMaxScene *scene, const Ogre::String &userDataReference, const Ogre::String &userData)
{
//	CreateWorld (userData);
}

void OgreMaxSceneCallbacks::LoadingSceneFile(const OgreMaxScene* scene, const Ogre::String& fileName, Ogre::String& resourceGroupName) 
{
	/*
	if (allParams != "") {
		Ogre::String objectType = getParamValue("sceneInitPos",allParams);
		mScenePosition = Ogre::StringConverter::parseVector3(objectType);
	}
	*/
}

void OgreMaxSceneCallbacks::CreatedCamera(const OgreMaxScene* scene, Ogre::Camera* camera) {
	Ogre::String mParentRoom;
	Ogre::String entireParam = scene->GetObjectExtraData(camera)->userData; 

	Ogre::LogManager::getSingleton().logMessage("||Creating Camera...             ||");

	//It will only add if there is existing data
	if (entireParam != "")
	{
		
	}
}

void OgreMaxSceneCallbacks::CreatedLight(const OgreMax::OgreMaxScene* scene, Ogre::Light* light) {
	Ogre::String mParentRoom;
	Ogre::String entireParam = scene->GetObjectExtraData(light)->userData; 

	Ogre::LogManager::getSingleton().logMessage("||Creating light...             ||");

	//It will only add if there is existing data
	if (entireParam != "")
	{
		mParentRoom = getParamValue("parentRoom",entireParam);
	
		if(getParamValue("enabled",entireParam) != "")
			return;

		GameObject *GO = new GameObject(light->getName());
		
		CPosition *mPos = new CPosition(light->getParentNode()->_getDerivedPosition());
		GO->setComponent(mPos);

		COrientation *mOr = new COrientation(light->getParentSceneNode()->_getDerivedOrientation());
		GO->setComponent(mOr);		

		//if(mStatic != "yes") {
		CRender *mMov = new CRender(light->getName(),mParentRoom);
		//mMov->mNode = light->getParentNode();
		GO->setComponent(mMov);

		CLight *mLight = new CLight(light);
		GO->setComponent(mLight);

		mChildNodes[light->getName()] = GO;


	}

}

void OgreMaxSceneCallbacks::CreatedEntity (const OgreMax::OgreMaxScene* scene, Ogre::Entity* entity)
{
	Ogre::LogManager::getSingleton().logMessage("||Creating body...             ||");
	//It will only add if there is existing data
	if (scene->GetObjectExtraData(entity)->userData != "")
	{
		//Contains the entire param
		Ogre::String entireParam = scene->GetObjectExtraData(entity)->userData; 
		//Get params
		//Ogre::String firstParam = getFirstParam (entireParam);	//Ex. "Box01;Box01.mesh"
		NxOgre::Shape* shape; // = getShape (entireParam);			//Ex. "Sphere" or "Sphere.nxs"
		//Ogre::String lastParam = getLastParam (entireParam);	//Ex. "mass: 10"
		
		Vector3 mShapeSize;
		Ogre::Quaternion mOrientation;
		Ogre::Vector3 mPosition;
		Ogre::String mEntityName;
		Ogre::String mMeshName;
		Ogre::String mShapeType;
		Ogre::String mStatic;
		Ogre::String mBodyType;
		Ogre::String mPhysicsMeshType;
		Ogre::String mParentRoom;
		Ogre::String mMass;

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

		//////////////////////////////////////////////////////////////////////////
		//Get parameters from User Data.
		mEntityName = getParamValue("entityName",entireParam);
		mMeshName = getParamValue("meshName",entireParam);
		mShapeType = getParamValue("shapeType",entireParam);
		mStatic = getParamValue("static",entireParam);
		mBodyType = getParamValue("bodyType",entireParam);
		mPhysicsMeshType = getParamValue("physicsMeshType",entireParam);
		mParentRoom = getParamValue("parentRoom",entireParam);
		mMass = getParamValue("mass",entireParam);
		mPosition =  mScenePosition + entity->getParentSceneNode()->_getDerivedPosition();
		mOrientation = entity->getParentSceneNode()->_getDerivedOrientation(); // getOrientation()
		
		mSoundFileName = getParamValue("soundName",entireParam);
		mSoundType = getParamValue("soundType",entireParam);
		mSoundSize = getParamValue("soundSize",entireParam);

		mRestitution = Ogre::StringConverter::parseReal(getParamValue("restitution",entireParam));
		mStaticFriction = Ogre::StringConverter::parseReal(getParamValue("staticFriction",entireParam));
		mDynamicFriction = Ogre::StringConverter::parseReal(getParamValue("dynamicFriction",entireParam));
		mLinearDamping = Ogre::StringConverter::parseReal(getParamValue("linearDamping",entireParam));
		mAngularDamping = Ogre::StringConverter::parseReal(getParamValue("angularDamping",entireParam));
		mDensity = Ogre::StringConverter::parseReal(getParamValue("density",entireParam));
		
		mTextureFileName = getParamValue("texFileName",entireParam);

		mCameraRoomName = getParamValue("cameraName",entireParam);

		mTextureTilingU = getParamValue("texU_Tiling",entireParam);
		mTextureTilingV = getParamValue("texV_Tiling",entireParam);

		mIsParticle = Ogre::StringConverter::parseBool(getParamValue("isParticle",entireParam));
		mParticleScriptName = getParamValue("particleName",entireParam);

		Ogre::Quaternion physicsRot = Ogre::StringConverter::parseQuaternion(getParamValue("rotation",entireParam));

		Ogre::String childName = getParamValue("childNode1",entireParam);
		if(childName != "")
			mIsParent = true;
		else
			mIsParent = false;

		mShapeSize = Vector3::ZERO;
		if(mShapeType == "Portal") {
			Vector2 ps = Ogre::StringConverter::parseVector2(getParamValue("size",entireParam));
			mShapeSize = Vector3(ps.x,ps.y,0);
		}
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


		//////////////////////////////////////////////////////////////////////////
		if(mShapeType != "ParentRoom" && mShapeType != "Portal" && (mBodyType == "Actor" || mBodyType == "Body") ) {
			Ogre::String lastParams = "";

			if(mMass != "")
				lastParams = "mass:" + mMass;

			if(mStatic == "yes") {
				if(lastParams != "")
					lastParams += ",";

				lastParams += "static:yes";
			}

			NxOgre::ActorParams ap(lastParams);
			
			//NxOgre::ActorParams ap;
			ap.mAngularDamping = mAngularDamping;
			ap.mLinearDamping = mLinearDamping;
			ap.mDensity = mDensity;
			//ap.mMass = ;

			PhysicsActor* actor = new PhysicsActor(mBodyType,getShape(mMeshName + ".nxs",mShapeType,mShapeSize),mEntityName,mMeshName,mPosition,mOrientation,mRestitution,mStaticFriction ,mDynamicFriction,ap); //lastParams
			if(mStatic != "yes") {
				mActors[mEntityName] = actor;
			} else {
				
				//////////////////////////////////////////////////////////////////////////
				if(mSoundType != "undefined" && mSoundSize != "undefined" && mSoundFileName != "undefined") {

					GameObject *GO = new GameObject(mEntityName);
					
					CActor* mCActor = new CActor(mBodyType,mEntityName,mMeshName,mPosition,mOrientation,lastParams);
					
					actor->setOwnerObject(GO);
					
					mCActor->mPhysicsActor = actor;
					mCActor->mPhysicsActor->setModel("",mPosition,mOrientation);
					mCActor->mPhysicsActor->setup();

					GO->setComponent(mCActor);
					
					
					CSound* objSound = new CSound(mSoundType,mSoundSize,mSoundFileName);
					GO->setComponent(objSound);
					

					//CRender *mMov = new CRender(mEntityName,"defaultZone");
					//GO->setComponent(mMov);

					mDefaultNodes[mEntityName] = GO;

				}
				//////////////////////////////////////////////////////////////////////////

			}

			return;
		}

		GameObject *GO = new GameObject(mEntityName);

		if(mEntityName == "AK_Mesh") {
			CWeapon* mCWeapon = new CWeapon(weaponType::MACHINEGUN,mEntityName);
			GO->setComponent(mCWeapon);
		}
		if(mEntityName == "FlameThrower_Mesh") {
			CWeapon* mCWeapon = new CWeapon(weaponType::FLAME_THROWER,mEntityName);
			GO->setComponent(mCWeapon);
		}

		if(mShapeType != "ParentRoom" && mShapeType != "Portal") { // && mBodyType != "Mesh"
			
			Ogre::String lastParams = "";

			if(mMass != "")
				lastParams = "mass:" + mMass;

			if(mStatic == "yes") {
				if(lastParams != "")
					lastParams += ",";

				lastParams += "static:yes";
			}
			
			Ogre::String childObject = getParamValue("childNode1",entireParam);
			if(childObject != "") {
				CActor* actor = new CActor(mBodyType,mEntityName,mMeshName,mPosition,mOrientation,lastParams);
				
				unsigned int i = 1;
				while(childObject != "") {
					
					actor->mActors[childObject] = NULL; //when finish loading the scene we add them...
					actor->mNumActors = i;
					
					i++;
					childObject = getParamValue("childNode" + Ogre::StringConverter::toString(i),entireParam);
					
				}

				GO->setComponent(actor);
			}

		}

		CPosition *mPos = new CPosition(mPosition);
		GO->setComponent(mPos);

		COrientation *mOr = new COrientation(mOrientation);
		GO->setComponent(mOr);		

		CMesh *mMesh;
		if(mBodyType == "Actor" || mBodyType == "" || mStatic == "yes") {
			mMesh = new CMesh(mMeshName,mEntityName);
		} else {
			mMesh = new CMesh(mMeshName,mEntityName);
		}
		GO->setComponent(mMesh);

		CRender *mMov = new CRender(mEntityName,mParentRoom);
		
		mMov->mTextureFileName = mTextureFileName;
		mMov->mTextureTiling_U = mTextureTilingU;
		mMov->mTextureTiling_V = mTextureTilingV;

		GO->setComponent(mMov);

		if(mIsParticle) {
			CParticle* mCParticle = new CParticle(mParticleScriptName,mEntityName);
			GO->setComponent(mCParticle);
		}

		if(mSoundType != "undefined" && mSoundSize != "undefined" && mSoundFileName != "undefined") {
			CSound* objSound = new CSound(mSoundType,mSoundSize,mSoundFileName);
			GO->setComponent(objSound);
		}

		if(mShapeType == "Portal") {
			Ogre::String room1 = getParamValue("parentRoom1",entireParam);
			Ogre::String room2 = getParamValue("parentRoom2",entireParam);

			CPortal* mPortal = new CPortal(mShapeSize.x,mShapeSize.y,room1,room2);
			GO->setComponent(mPortal);
		}

		if(mShapeType == "ParentRoom") {
			CRoom *room = new CRoom(mShapeSize,mEntityName,mCameraRoomName);
			GO->setComponent(room);

			//NxOgre::ActorParams ap("static:yes");

			//PhysicsActor* actor = new PhysicsActor("Actor",getShape(mMeshName + ".nxs","Box",mShapeSize),mEntityName,mMeshName,mPosition,mOrientation,mRestitution,mStaticFriction ,mDynamicFriction,ap,true); //lastParams
			
			//PhysicsActor* actor = new PhysicsActor(mBodyType,getShape(mMeshName + ".nxs",mShapeType,mShapeSize),mEntityName,mMeshName,mPosition,mOrientation,mRestitution,mStaticFriction ,mDynamicFriction,ap); //lastParams
			//actor->setOwnerObject(GO);
			//CActor* mCActor = new CActor("Actor",mEntityName,mMeshName,mPosition,mOrientation,"static:yes");
			//mCActor->mPhysicsActor = actor;
			////mCActor->mPhysicsActor->setModel("",mPosition,mOrientation);
			////mCActor->mPhysicsActor->setup();
			//CObjectSound* objSound = new CObjectSound("predefined","light","stone");
			//GO->setComponent(objSound);
			//GO->setComponent(mCActor);


		}

		entity->getParentSceneNode()->detachObject(entity);				

		if(mShapeType == "ParentRoom")
			mDefaultNodes[mEntityName] = GO;
		else
			mChildNodes[mEntityName] = GO;
		
	}
	
}

void OgreMaxSceneCallbacks::FinishedLoad (const OgreMax::OgreMaxScene* scene, bool success)
{
	if (success)
		Ogre::LogManager::getSingleton().logMessage("||Load successful!             ||");
	else
		Ogre::LogManager::getSingleton().logMessage("||Load failed!                 ||");
	Ogre::LogManager::getSingleton().logMessage("=================================");


	Ogre::String nname;
	OgreMaxScene* maxScene = (OgreMaxScene*)scene; // -> GetSceneManager()->destroySceneNode(entity->getParentSceneNode());
	//maxScene->GetSceneManager()->destroySceneNode(entity->getParentSceneNode());
	
	//maxScene->GetSceneManager()->destroyAllEntities();
	//maxScene->GetSceneManager()->destroyAllMovableObjects();

	//maxScene->GetSceneManager()->

	

	std::map<const std::string, GameObject*>::iterator iter;
	for(iter = mDefaultNodes.begin(); iter != mDefaultNodes.end(); iter++) {

		iter->second->setup();
		ObjectManager::getSingleton().addObject(iter->second);
	}
	//std::map<const std::string, GameObject*>::iterator iter;
	for(iter = mChildNodes.begin(); iter != mChildNodes.end(); iter++) {
		iter->second->setup();
		ObjectManager::getSingleton().addObject(iter->second);
	}
	
	//return;

	//Set childs to parent map
	std::map<const std::string, GameObject*> gos;
	gos = ObjectManager::getSingleton().getGOs();
	for(iter = gos.begin(); iter != gos.end(); iter++) {
		CActor *mCActor = dynamic_cast<CActor*>(iter->second->getComponent("CActor"));
		CRender *mCRender = dynamic_cast<CRender*>(iter->second->getComponent("CRender"));
		if(mCActor && mCRender) {

			std::map<const std::string, PhysicsActor*>::iterator ActorsIter;

			bool matchFound = false;

			for(ActorsIter = mActors.begin(); ActorsIter != mActors.end(); ActorsIter++) {
				//ActorsIter->second->setup();
				const std::string ActListName = ActorsIter->first;
				
				

				std::map<const std::string, PhysicsActor*>::iterator GOActorsIter;
				for(GOActorsIter = mCActor->mActors.begin(); GOActorsIter != mCActor->mActors.end(); GOActorsIter++) {
					std::string name = GOActorsIter->first;
					if(name == ActListName) {
						mCActor->mActors[ActListName] = ActorsIter->second;
						matchFound = true;
					}
				}


			}
			if(matchFound)
				mCActor->linkActors();
		}

		//iter->second->setup();

	}

	//std::map<const std::string, GameObject*> gos;
	gos = ObjectManager::getSingleton().getGOs();
	for(iter = gos.begin(); iter != gos.end(); iter++) {
		CRoom *mCRoom = dynamic_cast<CRoom*>(iter->second->getComponent("CRoom"));
		//CRender *mCRender = dynamic_cast<CRender*>(iter->second->getComponent("CRender"));
		if(mCRoom) {
			
			//Ogre::Root::getSingleton().getSceneManager()
			//mCRoom->mCamera = OgreRender::getSingleton().getSceneManager()->getCamera(mCRoom->mCameraName);
			mCRoom->mCamera = maxScene->GetSceneManager()->getCamera(mCRoom->mCameraName);

		}
	}

	//static Ogre::Timer timer;
	//Physics::getSingleton().simulate(timer.getMilliseconds() * 0.01);


}

NxOgre::Shape* OgreMaxSceneCallbacks::getShape (Ogre::String mMeshName,Ogre::String mShapeType,Ogre::Vector3 mShapeSize)
{
	if (mShapeType == "EditableMesh")
	{
		return getTriangle(mMeshName);
	}
	if (mShapeType == "Box")
	{
		return new NxOgre::Cube(mShapeSize.x,mShapeSize.y,mShapeSize.z);
	}

	if (mShapeType == "Sphere")
	{
		return new NxOgre::Sphere(mShapeSize.x);
	}
	if (mShapeType == "Capsule")
	{
 		return new NxOgre::Capsule(mShapeSize.x,mShapeSize.y);
	}
	Ogre::LogManager::getSingleton().logMessage("||WARNING! Default shape used. ||");
	return new NxOgre::Cube (10);
}


Ogre::String OgreMaxSceneCallbacks::getParamValue (Ogre::String paramName,Ogre::String param)
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

NxOgre::Convex* OgreMaxSceneCallbacks::getConvex(Ogre::String &param)
{
	//Ogre::String meshName = getMeshName(param);
	Ogre::String outFile = param;
	Ogre::String mpath = "file://../../media/models/" + outFile;

	try {
		NxOgre::Resources::ResourceSystem::getSingleton()->addMeshAs(mpath,outFile); 
	} catch (exception& e) {
		Ogre::LogManager::getSingleton().logMessage("||ERROR - addMeshAs() - path:" + mpath + " - outFile: " + outFile);
	}

	//Ogre::String path = "../../media/models/Penalty/" + meshName + "nxs";
	NxOgre::Convex* _mesh;
	try {
		_mesh = new NxOgre::Convex(NxOgre::Resources::ResourceSystem::getSingleton()->getMesh(outFile));
	} catch(exception& e) {
		//return false;
		Ogre::LogManager::getSingleton().logMessage("||ERROR - getMesh() - Convex mesh. FileName:" + mpath + " - Mesh Name: " + outFile);
	}
	return _mesh;
}
NxOgre::TriangleMesh* OgreMaxSceneCallbacks::getTriangle(Ogre::String &param)
{
	//Ogre::String meshName = getMeshName(param);
	Ogre::String outFile = param;
	Ogre::String mpath = "file://../../media/models/" + outFile;

	try {
		NxOgre::Resources::ResourceSystem::getSingleton()->addMeshAs(mpath,outFile); 
	} catch (exception& e) {
		Ogre::LogManager::getSingleton().logMessage("||ERROR - addMeshAs() - path:" + mpath + " - outFile: " + outFile);
	}

	//Ogre::String path = "../../media/models/Penalty/" + meshName + "nxs";
	NxOgre::TriangleMesh* _mesh;
	try {
		_mesh = new NxOgre::TriangleMesh(NxOgre::Resources::ResourceSystem::getSingleton()->getMesh(outFile));
	} catch(exception& e) {
		//return false;
		Ogre::LogManager::getSingleton().logMessage("||ERROR - getMesh() - Triangle mesh. FileName:" + mpath + " - Mesh Name: " + outFile);
	}
	return _mesh;
}
