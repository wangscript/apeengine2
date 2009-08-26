#include "LuaStateManager.h"

//#include "NebulaBindings.cpp"

//#include "NxController.h"
#include "luabind/operator.hpp"

template<> Nebula::LuaStateManager* Ogre::Singleton<Nebula::LuaStateManager>::ms_Singleton = 0;

//#include "luabind/operator.hpp"
//
//std::ostream& operator<<( std::ostream& stream, const Ogre::Entity ent );
//
//// Some helpful macros for defining constants (sort of) in Lua.  Similar to this code:
//// object g = globals(L);
//// object table = g["class"];
//// table["constant"] = class::constant;
//
//#define LUA_CONST_START( class ) { object g = globals(L); object table = g[#class];
//#define LUA_CONST( class, name ) table[#name] = class::name
//#define LUA_CONST_END }

//#include "bindings.cpp"
#define LUA_CONST_START( class ) { object g = globals(L); object table = g[#class];
#define LUA_CONST( class, name ) table[#name] = class::name
#define LUA_CONST_END }


namespace Nebula
{
	using namespace luabind;
	using namespace Ogre;

	//class NxUserControllerHitReport;

	LuaStateManager::LuaStateManager() : L(0)
										 //log(0)
	{
		L = lua_open();	
		luaL_openlibs(L);

		//luaopen_base(L);
		//luaopen_string(L);
		//luaopen_table(L);
		//luaopen_math(L);
		//luaopen_io(L);
		
		luabind::open(L);
		
		//bindVector3(L);

		//CLog::Get().Write(LOG_USER,"hola soy un log","caca");
		CLog::Get().Write(LOG_APP,"Lua Initialized");
	}

	LuaStateManager::~LuaStateManager()
	{
		lua_close(L);
	}

	//void LuaStateManager::SetBackgroundColour( ) //ColourValue &colour
	//{
	//	//if( mCamera )
	//	//{
	//	//	Viewport *vp = mCamera->getViewport();

	//	//	if( vp )
	//	//		vp->setBackgroundColour(colour);
	//	//}
	//	return;
	//}

	//void LuaStateManager::bindApplication( lua_State* L )
	//{
	//	module( L )
	//		[
	//			class_< GuiManager >( "guiManager" )
	//			//.def( "donothing", &singleton::donothing )
	//			.def("setWallpaper", (void(GuiManager::*)(const std::string&))&GuiManager::setWallpaper )
	//			.def( "getSingleton", &GuiManager::getSingleton ) // like this
	//		];

	//	object global_vars = globals(L);
	//	global_vars["guiManager"] = &GuiManager::getSingleton(); 

	//}

	//void LuaStateManager::bindLua( lua_State* L )
	//{
	//	bindApplication( L );

	//}

	LuaStateManager* LuaStateManager::getSingletonPtr(void)
	{
		return ms_Singleton;
	}
	LuaStateManager& LuaStateManager::getSingleton(void)
	{
		assert( ms_Singleton );  
		return ( *ms_Singleton );
	}

	bool LuaStateManager::start() {
		//setBindings();
		return true;
	}
	void LuaStateManager::onSuspend() {

		
	}
	void LuaStateManager::update()  {

		
	}
	void LuaStateManager::onResume()  {


	}
	void LuaStateManager::stop()  {


	}

	CCharacterAnimation* LuaStateManager::getCharacterAnimationComponent(GameObject* obj) {
		CCharacterAnimation* comp = static_cast<CCharacterAnimation*>(obj->getComponent("CCharacterAnimation"));
		
		if(comp)
			return comp;

		return NULL;
	}

	CCharacterController* LuaStateManager::getCharacterControllerComponent(GameObject* obj) {
		CCharacterController* comp = static_cast<CCharacterController*>(obj->getComponent("CCharacterController"));

		if(comp)
			return comp;

		return NULL;
	}

	CRender* LuaStateManager::getRenderComponent(GameObject* obj) {
		CRender* comp = static_cast<CRender*>(obj->getComponent("CRender"));

		if(comp)
			return comp;

		return NULL;
	}

	CAnimation* LuaStateManager::getAnimationComponent(GameObject* obj) {
		CAnimation* comp = static_cast<CAnimation*>(obj->getComponent("CAnimation"));

		if(comp)
			return comp;

		return NULL;
	}

	CHealth* LuaStateManager::getHealthComponent(GameObject* obj) {
		CHealth* comp = static_cast<CHealth*>(obj->getComponent("CHealth"));

		if(comp)
			return comp;

		return NULL;
	}

	CInventory* LuaStateManager::getInventoryComponent(GameObject* obj) {
		CInventory* comp = static_cast<CInventory*>(obj->getComponent("CInventory"));

		if(comp)
			return comp;

		return NULL;
	}

	CLight* LuaStateManager::getLightComponent(GameObject* obj) {
		CLight* comp = static_cast<CLight*>(obj->getComponent("CLight"));

		if(comp)
			return comp;

		return NULL;
	}

	CMesh* LuaStateManager::getMeshComponent(GameObject* obj) {
		CMesh* comp = static_cast<CMesh*>(obj->getComponent("CMesh"));

		if(comp)
			return comp;

		return NULL;
	}

	COrientation* LuaStateManager::getOrientationComponent(GameObject* obj) {
		COrientation* comp = static_cast<COrientation*>(obj->getComponent("COrientation"));

		if(comp)
			return comp;

		return NULL;
	}

	CPosition* LuaStateManager::getPositionComponent(GameObject* obj) {
		CPosition* comp = static_cast<CPosition*>(obj->getComponent("CPosition"));

		if(comp)
			return comp;

		return NULL;
	}

	CRoom* LuaStateManager::getRoomComponent(GameObject* obj) {
		CRoom* comp = static_cast<CRoom*>(obj->getComponent("CRoom"));

		if(comp)
			return comp;

		return NULL;
	}

	CWeapon* LuaStateManager::getWeaponComponent(GameObject* obj) {
		CWeapon* comp = static_cast<CWeapon*>(obj->getComponent("CWeapon"));

		if(comp)
			return comp;

		return NULL;
	}

	CPhysicsActor* LuaStateManager::getPhysicsActorComponent(GameObject* obj) {
		CPhysicsActor* comp = static_cast<CPhysicsActor*>(obj->getComponent("CPhysicsActor"));

		if(comp)
			return comp;

		return NULL;
	}

	CPhysicsTrigger* LuaStateManager::getPhysicsTriggerComponent(GameObject* obj) {
		CPhysicsTrigger* comp = static_cast<CPhysicsTrigger*>(obj->getComponent("CPhysicsTrigger"));

		if(comp)
			return comp;

		return NULL;
	}
	
	CItem* LuaStateManager::getItemComponent(GameObject* obj) {
		CItem* comp = static_cast<CItem*>(obj->getComponent("CItem"));

		if(comp)
			return comp;

		return NULL;
	}

	CDoor* LuaStateManager::getDoorComponent(GameObject* obj) {
		CDoor* comp = static_cast<CDoor*>(obj->getComponent("CDoor"));

		if(comp)
			return comp;

		return NULL;
	}

	CElevator* LuaStateManager::getElevatorComponent(GameObject* obj) {
		CElevator* comp = static_cast<CElevator*>(obj->getComponent("CElevator"));

		if(comp)
			return comp;

		return NULL;
	}

	CEventZone* LuaStateManager::getEventZoneComponent(GameObject* obj) {
		CEventZone* comp = static_cast<CEventZone*>(obj->getComponent("CEventZone"));

		if(comp)
			return comp;

		return NULL;
	}

	CQuest* LuaStateManager::getQuestComponent(GameObject* obj) {
		CQuest* comp = static_cast<CQuest*>(obj->getComponent("CQuest"));

		if(comp)
			return comp;

		return NULL;
	}

	CSwitch* LuaStateManager::getSwitchComponent(GameObject* obj) {
		CSwitch* comp = static_cast<CSwitch*>(obj->getComponent("CSwitch"));

		if(comp)
			return comp;

		return NULL;
	}
	
	CHumanoid* LuaStateManager::getHumanoidComponent(GameObject* obj) {
		CHumanoid* comp = static_cast<CHumanoid*>(obj->getComponent("CHumanoid"));

		if(comp)
			return comp;

		return NULL;
	}

	CSmallCreature* LuaStateManager::getSmallCreatureComponent(GameObject* obj) {
		CSmallCreature* comp = static_cast<CSmallCreature*>(obj->getComponent("CSmallCreature"));

		if(comp)
			return comp;

		return NULL;
	}

	CCamera* LuaStateManager::getCameraComponent(GameObject* obj) {
		CCamera* comp = static_cast<CCamera*>(obj->getComponent("CCamera"));

		if(comp)
			return comp;

		return NULL;
	}
	
	Ogre::Real convertToDegrees(const Ogre::Real& degrees) {
		Ogre::Degree deg = Ogre::Degree(degrees);
		//Quaternion(
		//Ogre::Degree
		return deg.valueRadians();
	}

	void LuaStateManager::setBindings() {
		lua_State* lua = getState();
		object global_vars = globals(lua);
		
		//////////////////////////////////////////////////////////////////////////
		// Vector2
	
		module(lua)
			[
				class_<Vector2>( "Vector2" )
				.def(tostring(self))
				.def_readwrite( "x", &Vector2::x )
				.def_readwrite( "y", &Vector2::y )
				.def(constructor<>())
				.def(constructor<Vector2&>())
				.def(constructor<Real, Real>())
				.def("length", &Vector2::length )
				.def( self + other<Vector2>() )
				.def( self - other<Vector2>() )
				.def( self * other<Vector2>() )
				.def( self * Real() )
			];

		LUA_CONST_START( Vector2 )
		LUA_CONST( Vector2, ZERO);
		LUA_CONST( Vector2, UNIT_X);
		LUA_CONST( Vector2, UNIT_Y);
		LUA_CONST( Vector2, NEGATIVE_UNIT_X);
		LUA_CONST( Vector2, NEGATIVE_UNIT_Y);
		LUA_CONST( Vector2, UNIT_SCALE);
		LUA_CONST_END;

		//////////////////////////////////////////////////////////////////////////
		// Vector3

		module(lua)
			[
				class_<Vector3>( "Vector3" )
				.def(tostring(self))
				.def_readwrite( "x", &Vector3::x )
				.def_readwrite( "y", &Vector3::y )
				.def_readwrite( "z", &Vector3::z )
				.def(constructor<>())
				.def(constructor<Vector3&>())
				.def(constructor<Real, Real, Real>())
				.def("absDotProduct", &Vector3::absDotProduct)
				.def("crossProduct", &Vector3::crossProduct )
				.def("directionEquals", &Vector3::directionEquals )
				.def("distance", &Vector3::distance )
				.def("dotProduct", &Vector3::dotProduct )
				.def("getRotationTo", &Vector3::getRotationTo )
				.def("isZeroLength", &Vector3::isZeroLength )
				.def("length", &Vector3::length )
				.def("makeCeil", &Vector3::makeCeil )
				.def("makeFloor", &Vector3::makeFloor )
				.def("midPoint", &Vector3::midPoint )
				.def("normalise", &Vector3::normalise )
				.def("nornaliseCopy", &Vector3::normalisedCopy )
				.def("perpendicular", &Vector3::perpendicular )
				.def("positionCloses", &Vector3::positionCloses )
				.def("positionEquals", &Vector3::positionEquals )
				//.def("ptr", &Vector3::ptr )
				.def("randomDeviant", &Vector3::randomDeviant )
				.def("reflect", &Vector3::reflect )
				.def("squaredDistance", &Vector3::squaredDistance )
				.def("squaredLength", &Vector3::squaredLength )

				// Operators
				
				.def( self + other<Vector3>() )
				.def( self - other<Vector3>() )
				.def( self * other<Vector3>() )
				.def( self * Real() )
			];

		LUA_CONST_START( Vector3 )
			LUA_CONST( Vector3, ZERO);
		LUA_CONST( Vector3, UNIT_X );
		LUA_CONST( Vector3, UNIT_X);
		LUA_CONST( Vector3, UNIT_Y);
		LUA_CONST( Vector3, UNIT_Z);
		LUA_CONST( Vector3, NEGATIVE_UNIT_X);
		LUA_CONST( Vector3, NEGATIVE_UNIT_Y);
		LUA_CONST( Vector3, NEGATIVE_UNIT_Z);
		LUA_CONST( Vector3, UNIT_SCALE);
		LUA_CONST_END;
		
		//////////////////////////////////////////////////////////////////////////
		// Degree

		module(lua)
			[
				class_<Ogre::Radian>("Radian")
				.def(constructor<Ogre::Real>())
			];

		//////////////////////////////////////////////////////////////////////////
		// Quaternion

		module(lua)
			[
				class_<Quaternion>( "Quaternion" )
				.def(tostring(self))
				.def_readwrite( "w", &Quaternion::w )
				.def_readwrite( "x", &Quaternion::x )
				.def_readwrite( "y", &Quaternion::y )
				.def_readwrite( "z", &Quaternion::z )
				.def(constructor<>())
				.def(constructor<Quaternion&>())
				.def(constructor<Real, Real, Real, Real>())
				.def(constructor<const Ogre::Radian&, const Ogre::Vector3&>())
				.def("Dot", &Quaternion::Dot)
				.def("equals", &Quaternion::equals )
				.def("Exp", &Quaternion::Exp )
				.def("FromAngleAxis", &Quaternion::FromAngleAxis )
				//.def("FromAxes", &Quaternion::FromAxes )
				.def("getPitch", &Quaternion::getPitch )
				.def("getRoll", &Quaternion::getRoll )
				.def("getYaw", &Quaternion::getYaw )
				.def("Inverse", &Quaternion::Inverse )
				.def("nlerp", &Quaternion::nlerp )
				.def("Norm", &Quaternion::Norm )
				.def("normalise", &Quaternion::normalise )
				.def("Slerp", &Quaternion::Slerp )
				.def("Squad", &Quaternion::Squad )
				//.def("ToAngleAxis", &Quaternion::ToAngleAxis )
				//.def("ToAxes", &Quaternion::ToAxes )
				//.def("ptr", &Vector3::ptr )
				.def("UnitInverse", &Quaternion::UnitInverse )
				//.def("reflect", &Quaternion::reflect )
				//.def("squaredDistance", &Quaternion::squaredDistance )
				//.def("squaredLength", &Quaternion::squaredLength )

				// Operators
				
				//.def( self != other<Quaternion>() )
				.def( self == other<Quaternion>() )
				//.def( self [] other<Quaternion>() )
				//.def( self = other<Quaternion>() )
				//.def( self + other<Quaternion>() )
				//.def( self - other<Quaternion>() )
				.def( self * other<Quaternion>() )
				.def( self * other<Vector3>() )

				//.def( self * Real() )
			];

		LUA_CONST_START( Quaternion )
		LUA_CONST( Quaternion, ZERO);
		LUA_CONST( Quaternion, IDENTITY );
		LUA_CONST_END;

		//////////////////////////////////////////////////////////////////////////
		// ColourValue

		module(lua)
			[
				class_<ColourValue>("ColourValue")
				.def(constructor<>())
				.def(constructor<Real, Real, Real, Real>())
				.def(constructor<Real, Real, Real>())
//				.def(tostring(self))
				.def_readwrite( "r", &ColourValue::r)
				.def_readwrite( "g", &ColourValue::g )
				.def_readwrite( "b", &ColourValue::b )
				.def_readwrite( "a", &ColourValue::a )
				.def( "saturate", &ColourValue::saturate )

				// Operators

				.def( self + other<ColourValue>() )
				.def( self - other<ColourValue>() )
				.def( self * other<ColourValue>() )
				.def( self * Real() )
				.def( self / Real() )

			];

		LUA_CONST_START( ColourValue )
			LUA_CONST( ColourValue, ZERO);
		LUA_CONST( ColourValue, Black);
		LUA_CONST( ColourValue, White);
		LUA_CONST( ColourValue, Red);
		LUA_CONST( ColourValue, Green);
		LUA_CONST( ColourValue, Blue);
		LUA_CONST_END;
		
		//////////////////////////////////////////////////////////////////////////
		// Real

		//module(lua)
		//	[
		//		class_<Ogre::Real>("Real")
		//		.def(constructor<>())
		//		.def(constructor<const float&>())
		//	];

		//////////////////////////////////////////////////////////////////////////
		// Degree

		module(lua)
			[
				class_<Ogre::Degree>("Degree")
				.def(constructor<Ogre::Real>())
				.def(constructor<const Ogre::Radian&>())
			];
		
		//////////////////////////////////////////////////////////////////////////
		// Entity

		module(lua)
			[
				class_<MovableObject>("MovableObject"),
				class_<Entity, MovableObject>("Entity")
//				.def(tostring(self))
				.def("setMaterialName", &Entity::setMaterialName )
				.def("setDisplaySkeleton", &Entity::setDisplaySkeleton )
			];

		//////////////////////////////////////////////////////////////////////////
		// SceneNode

		module(lua)
		[
		class_<Ogre::Node>("Node")
        .enum_("TransformSpace")
			[
				value("TS_LOCAL", 0),
				value("TS_PARENT", 1),
				value("TS_WORLD", 2)
			]
		];


		module(lua)
			[
				class_<SceneNode>("SceneNode")
				.def("attachObject", &SceneNode::attachObject )
				.def("setPosition", (void( SceneNode::*)(const Vector3&))&SceneNode::setPosition )
				.def("setPosition", (void( SceneNode::*)(Real,Real,Real))&SceneNode::setPosition )
				.def("setOrientation", (void( SceneNode::*)(Real,Real,Real,Real))&SceneNode::setOrientation)
				.def("setOrientation", (void( SceneNode::*)(const Quaternion&))&SceneNode::setOrientation)
				.def("getPosition", &SceneNode::getPosition )
				.def("getOrientation", &SceneNode::getOrientation)
				.def("_getDerivedPosition", &SceneNode::_getDerivedPosition)
				.def("_getDerivedOrientation", &SceneNode::_getDerivedOrientation)
				.def("setScale", (void(SceneNode::*)(Real,Real,Real))&SceneNode::setScale )

				//.def("createChildSceneNode", (void(SceneNode::*)(const Ogre::String&,const Vector3&,const Quaternion&))&SceneNode::createChildSceneNode )
				//.def("createChildSceneNode", (void(SceneNode::*)(const Vector3&,const Quaternion&))&SceneNode::createChildSceneNode)

				//.def("createChildSceneNode", ( SceneNode(*)(SceneNode::*)(const Ogre::String&) ) &SceneNode::createChildSceneNode )
				//.def("createChildSceneNode", ( SceneNode(*)(SceneNode::*)(const Vector3&,const Quaternion&) ) &SceneNode::createChildSceneNode )

				//.def("createChildSceneNode", ( SceneNode(*)( SceneNode::*)(const Ogre::String&,const Vector3&,const Quaternion&) )&SceneNode::createChildSceneNode )
				//.def("createChildSceneNode", ( SceneNode(*)( SceneNode::*)(const Vector3&,const Quaternion&) )&SceneNode::createChildSceneNode )

				//.def("createChildSceneNode", ( SceneNode(*)(const std::string&) )&SceneNode::createChildSceneNode ) //,const Vector3&,const Quaternion&

				//.def("translate", (void( SceneNode::*)(Real,Real,Real))&SceneNode::translate )
				.def("translate", (void( SceneNode::*)(const Vector3&,Ogre::Node::TransformSpace))&SceneNode::translate )
				.def("rotate", (void( SceneNode::*)(const Quaternion&,Ogre::Node::TransformSpace))&SceneNode::rotate )
			];

		//////////////////////////////////////////////////////////////////////////
		// Camera

		module(lua)
			[
				class_<Camera>("Camera")
				.def("setPosition", (void( Camera::*)(const Vector3&))&Camera::setPosition )
				.def("setPosition", (void( Camera::*)(Real,Real,Real))&Camera::setPosition )
				.def("setOrientation", (void( Camera::*)(Real,Real,Real,Real))&Camera::setOrientation)
				.def("setOrientation", (void( Camera::*)(const Quaternion&))&Camera::setOrientation)
				.def("getPosition", &Camera::getPosition )
				.def("getOrientation", &Camera::getOrientation)
				.def("getParentSceneNode", &Camera::getParentSceneNode)
				.def("lookAt", (void( Camera::*)(const Vector3&))&Camera::lookAt )
				.def("lookAt", (void( Camera::*)(Real,Real,Real))&Camera::lookAt )
				.def("setNearClipDistance", &Camera::setNearClipDistance )
				.def("setFarClipDistance", &Camera::setFarClipDistance )
			];

		//////////////////////////////////////////////////////////////////////////
		// StringConverter
		
		//Ogre::Bone
		module(lua)
			[
				class_<Bone, bases<Ogre::Node> >("Bone")
				//.def(constructor<const CCharacterAnimationDesc&>())
			];

		//////////////////////////////////////////////////////////////////////////
		// StringConverter

		module(lua)
			[
				//static String toString(const Vector3& val);
				class_<StringConverter>("StringConverter")
				//.def("toString", &StringConverter::toString )
				//def("toString", (Ogre::String(*)(const char*)) &f),
				.def("toString", ( Ogre::String(*)(const Vector2&) ) &StringConverter::toString )
				.def("toString", ( Ogre::String(*)(const Vector3&) ) &StringConverter::toString )
				.def("toString", ( Ogre::String(*)(const Vector4&) ) &StringConverter::toString )
				//.def("toString", ( Ogre::String(*)(float) ) &StringConverter::toString )
				//.def("toString", ( Ogre::String(*)(Radian) ) &StringConverter::toString )
				//.def("toString", ( Ogre::String(*)(Degree) ) &StringConverter::toString )
				//.def("toString", ( Ogre::String(*)(int) ) &StringConverter::toString )
				//.def("toString", ( Ogre::String(*)(unsigned long) ) &StringConverter::toString )
				//.def("toString", ( Ogre::String(*)(long) ) &StringConverter::toString )
				//.def("toString", ( Ogre::String(*)(Ogre::Real) ) &StringConverter::toString )
				//.def("toString", ( Ogre::String(*)(bool) ) &StringConverter::toString )
				.def("toString", ( Ogre::String(*)(const Quaternion&) ) &StringConverter::toString )
				.def("toString", ( Ogre::String(*)(const ColourValue&) ) &StringConverter::toString )
				
				.def("parseAngle", ( Ogre::Radian(*)(const Ogre::String&) ) &StringConverter::parseAngle )
				.def("parseBool", ( bool(*)(const Ogre::String&) ) &StringConverter::parseBool )
				.def("parseColourValue", ( ColourValue(*)(const Ogre::String&) ) &StringConverter::parseColourValue )
				.def("parseInt", ( int(*)(const Ogre::String&) ) &StringConverter::parseInt )
				.def("parseLong", ( long(*)(const Ogre::String&) ) &StringConverter::parseLong )
				.def("parseQuaternion", ( Quaternion(*)(const Ogre::String&) ) &StringConverter::parseQuaternion )
				.def("parseReal", ( Real(*)(const Ogre::String&) ) &StringConverter::parseReal )
				.def("parseUnsignedInt", ( unsigned int(*)(const Ogre::String&) ) &StringConverter::parseUnsignedInt )
				.def("parseUnsignedLong", ( unsigned long(*)(const Ogre::String&) ) &StringConverter::parseUnsignedLong )
				.def("parseVector2", ( Vector2(*)(const Ogre::String&) ) &StringConverter::parseVector2 )
				.def("parseVector3", ( Vector3(*)(const Ogre::String&) ) &StringConverter::parseVector3 )
				.def("parseVector4", ( Vector4(*)(const Ogre::String&) ) &StringConverter::parseVector4 )

			];

		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// NxF32

		module(lua)
			[
				class_<NxF32>("NxF32")
				//.def("getName", &NxVec3::getName )

			];

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		// NxReal

		//module(lua)
		//	[
				//class_<NxReal>("NxReal")
				//.def("getName", &NxVec3::getName )

		//	];

		//////////////////////////////////////////////////////////////////////////



		//////////////////////////////////////////////////////////////////////////
		// NxQuat

		module(lua)
			[
				class_<NxQuat>("NxQuat")
				//.def("getName", &NxVec3::getName )
				//.def("setGlobalPosition", &NxActor::setGlobalPosition )
			];

		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// NxVec3

		module(lua)
			[
				class_<NxVec3>("NxVec3")
				//.def("getName", &NxVec3::getName )
				//.def("setGlobalPosition", &NxActor::setGlobalPosition )
			];

		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// NxActor

		//module(lua)
		//	[
		//		class_<NxShape>("NxShape")
		//	];

		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// NxActor

		//module(lua)
		//	[
		//		class_<NxJoint>("NxJoint")
		//	];

		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// NxActor

		//module(lua)
		//	[
		//		class_<NxBodyDesc>("NxBodyDesc")
		//	];

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		// NxActor

		//module(lua)
		//	[
		//		class_<NxShapeDesc>("NxShapeDesc")
		//	];

		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// NxActor

		//module(lua)
		//	[
		//		class_<NxActor>("NxActor")
		//		//.def(constructor<void>())
		//		//.def("getName", &NxActor::getName )
		//		//.def("setGlobalPosition", &NxActor::setGlobalPosition )
		//		//.def("setGlobalOrientationQuat", &NxActor::setGlobalOrientationQuat )
		//		//.def("getGlobalPosition", &NxActor::getGlobalPosition )
		//		//.def("getGlobalOrientationQuat", &NxActor::getGlobalOrientationQuat )

		//	];

		//////////////////////////////////////////////////////////////////////////
		// ConvertionTool

		module(lua)
			[
				class_<NxTools>("NxTools")
				//.def("convert", &NxTools::convert )
				.def("convert", ( Ogre::Vector3(*)(const NxVec3&) ) &NxTools::convert )
			];

		//////////////////////////////////////////////////////////////////////////
		// Nebula Objects
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// IGameComponent
		module( lua )
			[
				class_<IGameComponent>("IGameComponent")
				//.def(constructor<const CCharacterAnimationDesc&>())
			];
		//////////////////////////////////////////////////////////////////////////
		// CCharacterAnimation
		module( lua )
			[
				class_<CCharacterAnimation, bases<IGameComponent> >("CCharacterAnimation")
				.def(constructor<const CCharacterAnimationDesc&>())
				.def("createLuaTriggerFunctor",(void(CCharacterAnimation::*)(const std::string, const luabind::object&)) &CCharacterAnimation::createLuaTriggerFunctor )
				.def("setAnimationState"      , (void(CCharacterAnimation::*)(const float)) &CCharacterAnimation::setAnimationState )
				.def("addItemHolderBone"      , (void(CCharacterAnimation::*)(std::string)) &CCharacterAnimation::addItemHolderBone )
				.def("attachItemToBone", &CCharacterAnimation::attachItemToBone )
				.def("updateAttachedItems", &CCharacterAnimation::updateAttachedItems )
				.def("getObjectAttachedToBone", &CCharacterAnimation::getObjectAttachedToBone)
				
			];
		//////////////////////////////////////////////////////////////////////////
		// CCharacterController
		module( lua )
			[
				class_<CCharacterController, bases<IGameComponent> >("CCharacterController")
				.def(constructor<const CCharacterControllerDesc&>())
				.def("isMoving", &CCharacterController::isMoving )
				.def("isOnElevator", &CCharacterController::isOnElevator )
				.def("isPlayer", &CCharacterController::isPlayer )
				.def("setAsPlayer", &CCharacterController::setAsPlayer )
				.def("getDistanceToActor", &CCharacterController::getDistanceToActor )
				.def("getDistanceToCharacter", &CCharacterController::getDistanceToCharacter )
				.def("getDistanceToCharacter", &CCharacterController::getDistanceToCharacter )
				.def("getDistanceToTrigger", &CCharacterController::getDistanceToTrigger )
				.def("isRotating", &CCharacterController::isRotating )
				.def("isFalling", &CCharacterController::isFalling )
				.def("isOnAir", &CCharacterController::isOnAir )
				.def("isTouchingFloor", &CCharacterController::isTouchingFloor )
				.def("isTouchingCeiling", &CCharacterController::isTouchingCeiling )
				.def("isTouchingSides", &CCharacterController::isTouchingSides )
				.def("getDisplacement", &CCharacterController::getDisplacement )
				.def("getDirection", &CCharacterController::getDirection )
				.def("setDisplacement", &CCharacterController::setDisplacement )
				.def("setDirection", &CCharacterController::setDirection )
				.def("setSpeed", &CCharacterController::setSpeed )
				.def("getSpeed", &CCharacterController::getSpeed )
				.def("addExternalForce", &CCharacterController::addExternalForce )
				.def("getExternalForces", &CCharacterController::getExternalForces )
				.def("getCharacterPosOgre", &CCharacterController::getCharacterPosOgre )

			];
		//////////////////////////////////////////////////////////////////////////
		// GameObject
		module( lua )
			[
				class_<CRender, bases<IGameComponent> >("CRender")
				.def(constructor<const CRenderDesc&>())
				.def("getRotationSpeed", &CRender::getRotationSpeed )
				.def("setRotationSpeed", &CRender::setRotationSpeed )
				.def("getNode", &CRender::getNode )
				.def("getDistanceToActor", &CRender::getDistanceToActor )
				.def("getDistanceToCharacter", &CRender::getDistanceToCharacter )
				.def("getDistanceToTrigger", &CRender::getDistanceToTrigger )
			];
		//////////////////////////////////////////////////////////////////////////
		module( lua )
			[
				class_<CAnimation, bases<IGameComponent> >("CAnimation")
				.def(constructor<const CAnimationDesc&>())
				
				.def("getNumberOfAnimations", &CAnimation::getNumberOfAnimations )
				.def("getAnimationSpeed", &CAnimation::getAnimationSpeed )
				.def("setAnimationSpeed", &CAnimation::setAnimationSpeed )
				.def("isRunningAnimation", &CAnimation::isRunningAnimation )
				.def("getCurrentAnimationIndex", &CAnimation::getCurrentAnimationIndex )
				.def("playAnimation", &CAnimation::playAnimation )
				.def("stopAnimation", &CAnimation::stopAnimation )
				.def("pauseAnimation", &CAnimation::pauseAnimation )
				.def("setAnimationNode", &CAnimation::setAnimationNode )
				.def("updateNode", &CAnimation::updateNode )
				.def("getAnimationNode", &CAnimation::getAnimationNode )
				.def("setAnimationTimePosition", &CAnimation::setAnimationTimePosition )

			];
		//////////////////////////////////////////////////////////////////////////
		module( lua )
			[
				class_<CHealth, bases<IGameComponent> >("CHealth")
				.def(constructor<const CHealthDesc&>())
				.def("setMaxHitPoints", &CHealth::setMaxHitPoints )
				//.def("getMaxHitPoints", &CHealth::getMaxHitPoints )
				.def("setCurrentHitPoints", &CHealth::setCurrentHitPoints )
				//.def("getCurrentHitPoints", &CHealth::getCurrentHitPoints )
				//.def("removeHitPoint", &CHealth::removeHitPoint )
				//.def("addHitPoint", &CHealth::addHitPoint )
				//.def("addHitPoints", &CHealth::addHitPoints )
				.def("createHealthBar", &CHealth::createHealthBar )
				//.def("refreshHealthBar", &CHealth::refreshHealthBar )
			];
		//////////////////////////////////////////////////////////////////////////
		
		module( lua )
			[
			class_<CInventoryDesc>("CInventoryDesc")
			    //.def("plus", &plus)
			];

		module( lua )
			[
				class_<CInventory, bases<IGameComponent> >("CInventory")
				.def(constructor<const CInventoryDesc&>())
				.def("getDescription",(CInventoryDesc&(CInventory::*)(void)) &CInventory::getDescription )
				//.def("setCurrentTemplate"      , (void(CCharacterAnimation::*)(luabind::object)) &CCharacterAnimation::setCurrentTemplate )
				.def("addItem", &CInventory::addItem )
				.def("hideInventoryImage", &CInventory::hideInventoryImage )
				.def("showInventoryImage", &CInventory::showInventoryImage )
				.def("createInventoryImage", &CInventory::createInventoryImage )
				.def("destroyInventoryImage", &CInventory::destroyInventoryImage )
			];
		//////////////////////////////////////////////////////////////////////////
		module( lua )
			[
				class_<CLight, bases<IGameComponent> >("CLight")
				.def(constructor<const CLightDesc&>())
			];
		//////////////////////////////////////////////////////////////////////////
		module( lua )
			[
				class_<CMesh, bases<IGameComponent> >("CMesh")
				.def(constructor<const CMeshDesc&>())
				.def("setMeshAmbientColour", &CMesh::setMeshAmbientColour )
				.def("getOffsetNode", &CMesh::getOffsetNode )
				.def("getDistanceToActor", &CMesh::getDistanceToActor )
				.def("getDistanceToCharacter", &CMesh::getDistanceToCharacter )
				.def("getDistanceToTrigger", &CMesh::getDistanceToTrigger )
			];
		//////////////////////////////////////////////////////////////////////////
		module( lua )
			[
				class_<COrientation, bases<IGameComponent> >("COrientation")
			];
		//////////////////////////////////////////////////////////////////////////
		module( lua )
			[
				class_<CPosition, bases<IGameComponent> >("CPosition")
				.def(constructor<const CPositionDesc&>())
			];
		//////////////////////////////////////////////////////////////////////////
		module( lua )
			[
				class_<CRoom, bases<IGameComponent> >("CRoom")
				.def(constructor<const CRoomDesc&>())
				.def("getCamera", &CRoom::getCamera)
			];
		//////////////////////////////////////////////////////////////////////////
		module( lua )
			[
				class_<CWeapon, bases<IGameComponent> >("CWeapon")
				.def(constructor<const CWeaponDesc&>())
				.def("getRibbonTrailNodeTip", &CWeapon::getRibbonTrailNodeTip)
				.def("getRibbonTrailNodeBase", &CWeapon::getRibbonTrailNodeBase)
				.def("setRibbonTrailVisible", &CWeapon::setRibbonTrailVisible)
				.def("setRibbonTrailMaterial", &CWeapon::setRibbonTrailMaterial)
				.def("setRibbonTrailNodeTip", &CWeapon::setRibbonTrailNodeTip)
				.def("setRibbonTrailNodeBase", &CWeapon::setRibbonTrailNodeBase)
				.def("setRibbonTrailWidth", &CWeapon::setRibbonTrailWidth)
				
				.def("setSegmentStartInitialColor", &CWeapon::setSegmentStartInitialColor)
				.def("setSegmentEndInitialColor", &CWeapon::setSegmentEndInitialColor)
				.def("setSegmentStartColorChange", &CWeapon::setSegmentStartColorChange)
				.def("setSegmentEndColorChange", &CWeapon::setSegmentEndColorChange)

			];
		//////////////////////////////////////////////////////////////////////////
		
		module( lua )
			[
				class_<CItem, bases<IGameComponent> >("CItem")
				.def(constructor<const CItemDesc&>())
			];
		//////////////////////////////////////////////////////////////////////////	

		module( lua ) //: public IGameComponent, public NxOgre::Actor, public NxOgre::RenderableSource 
			[
				class_<CPhysicsActor, bases<IGameComponent> >("CPhysicsActor")
				.def(constructor<const CPhysicsActorDesc&>())
				.def("isKinematic", &CPhysicsActor::isKinematic )
				.def("isStatic", &CPhysicsActor::isStatic )
				.def("isDynamic", &CPhysicsActor::isDynamic )
				.def("getDistanceToActor", &CPhysicsActor::getDistanceToActor )
				.def("getDistanceToCharacter", &CPhysicsActor::getDistanceToCharacter )
				.def("getDistanceToTrigger", &CPhysicsActor::getDistanceToTrigger )
				//.def("getNode", &CHealth::getNode )
			];
		//////////////////////////////////////////////////////////////////////////

		//module( lua ) //: public IGameComponent, public NxOgre::Actor, public NxOgre::RenderableSource 
		//	[
		//		//NxOgre::Actor
		//		//const NxString& Identifier, Scene*, Shape*, const Pose&, const ActorParams& = ActorParams()

		//		class_<NxUserControllerHitReport>("NxUserControllerHitReport")
		//		//.def(constructor<const std::string,)
		//		//.def("getRotationSpeed", &CHealth::getRotationSpeed )
		//		//.def("getNode", &CHealth::getNode )
		//	];

		module( lua )
			[
				//public NxUserControllerHitReport

				class_<CPhysicsTrigger, bases<IGameComponent> >("CPhysicsTrigger")
				.def(constructor<const CPhysicsTriggerDesc&>())
			];
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		module( lua )
			[
				class_<CDoor, bases<IGameComponent> >("CDoor")
				.def(constructor<const CDoorDesc&>())
			];

		//////////////////////////////////////////////////////////////////////////
		module( lua )
			[
				class_<CElevator, bases<IGameComponent> >("CElevator")
				.def(constructor<const CElevatorDesc&>())
			];
		
		//////////////////////////////////////////////////////////////////////////
		module( lua )
			[
				class_<CEventZone, bases<IGameComponent> >("CEventZone")
				.def(constructor<const CEventZoneDesc&>())
			];

		//////////////////////////////////////////////////////////////////////////
		module( lua )
			[
				class_<CQuest, bases<IGameComponent> >("CQuest")
				.def(constructor<const CQuestDesc&>())
			];

		//////////////////////////////////////////////////////////////////////////
		module( lua )
			[
				class_<CSwitch, bases<IGameComponent> >("CSwitch")
				.def(constructor<const CSwitchDesc&>())
			];
		//////////////////////////////////////////////////////////////////////////
		module( lua )
			[
				class_<CHumanoid, bases<IGameComponent> >("CHumanoid")
				.def(constructor<const CHumanoidDesc&>())
				.def("hideCharacterPaper", &CHumanoid::hideCharacterPaper )
				.def("showCharacterPaper", &CHumanoid::showCharacterPaper )
				.def("createCharacterPaper", &CHumanoid::createCharacterPaper )
				.def("destroyCharacterPaper", &CHumanoid::destroyCharacterPaper )
			];
		//////////////////////////////////////////////////////////////////////////
		module( lua )
			[
				class_<CSmallCreature, bases<IGameComponent> >("CSmallCreature")
				.def(constructor<const CSmallCreatureDesc&>())
				.def("hideCreaturePaper", &CSmallCreature::hideCreaturePaper )
				.def("showCreaturePaper", &CSmallCreature::showCreaturePaper )
				.def("createCreaturePaper", &CSmallCreature::createCreaturePaper )
				.def("destroyCreaturePaper", &CSmallCreature::destroyCreaturePaper )
			];
		//////////////////////////////////////////////////////////////////////////
		module( lua )
			[
				class_<CCamera, bases<IGameComponent> >("CCamera")
				.def(constructor<const CCameraDesc&>())
				.def("setCamera", &CCamera::setCamera )
				.def("getCamera", &CCamera::getCamera )
				.def("enableAnimation", &CCamera::enableAnimation )
				.def("isCameraEnabled", &CCamera::isCameraEnabled )
				
			];

		//////////////////////////////////////////////////////////////////////////
		// GameObject
		module( lua )
			[
				class_<GameObject>("GameObject")
				.def(constructor<const std::string&>())
				.def("getID", &GameObject::getID)

			];

		//////////////////////////////////////////////////////////////////////////
		// Set lua bindings

		module( lua )
			[
				class_< DebugText >( "DebugText" )
				.def("toggleFPSWindow", &DebugText::toggleFPSWindow)
				.def("addText", &DebugText::addText)
//				.def( "getSingleton", &DebugText::getSingleton ) // like this
			];

		//////////////////////////////////////////////////////////////////////////
		// Set lua bindings

		module( lua )
			[
				class_< OgreManager >( "OgreManager" )
				.def("getDebugText", &OgreManager::getDebugText)
				.def("getCamera", &OgreManager::getCamera)
				.def("setCamera", &OgreManager::setCamera)
				.def("createChildSceneNode", &OgreManager::createChildSceneNode)
				.def("getRootSceneNode", &OgreManager::getRootSceneNode)
				.def( "getSingleton", &OgreManager::getSingleton ) // like this
			];
		global_vars["OgreManager"] = &OgreManager::getSingleton(); 

		//////////////////////////////////////////////////////////////////////////
		//global_vars["convertToDegrees"] = &convertToDegrees; 
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//module( lua )
		//	[
		//		class_<ParticleUniverse::Particle> >("Particle")
		//		.def(constructor<>())
		//	];
		//module( lua )
		//	[
		//		class_<ParticleUniverse::IElement> >("IElement")
		//		.def(constructor<>())
		//	];
		//
		//module( lua )
		//	[
		//		class_<ParticleUniverse::ParticleSystem, bases<Ogre::MovableObject,ParticleUniverse::Particle,ParticleUniverse::IElement> >("ParticleSystem")
		//		.def(constructor<const Ogre::String&>())
		//		.def(constructor<const Ogre::String&,const Ogre::String&>())
		//	];

		//////////////////////////////////////////////////////////////////////////
		// Particle Manager

		module( lua )
			[
				class_< ParticleManager >( "ParticleManager" )
				.def("createParticle", &ParticleManager::createParticle)
				.def("attachParticleToNode", &ParticleManager::attachParticleToNode)
				.def("detachParticleFromNode", &ParticleManager::detachParticleFromNode)
				.def("startParticle", &ParticleManager::startParticle)
				.def("stopParticle", &ParticleManager::stopParticle)
				//.def("getParticle", &ParticleManager::getParticle)

			];
		global_vars["ParticleManager"] = &ParticleManager::getSingleton(); 

		//////////////////////////////////////////////////////////////////////////
		// Set lua bindings
		
		module( lua )
			[
				class_< LuaStateManager >( "LuaStateManager" )
				.def("runFile", (void(LuaStateManager::*)(const char*))&LuaStateManager::runFile )
				.def("getCharacterAnimationComponent", &LuaStateManager::getCharacterAnimationComponent)
				.def("getCharacterControllerComponent", &LuaStateManager::getCharacterControllerComponent)
				.def("getRenderComponent", &LuaStateManager::getRenderComponent)
				.def("getAnimationComponent", &LuaStateManager::getAnimationComponent)
				.def("getHealthComponent", &LuaStateManager::getHealthComponent)
				.def("getInventoryComponent", &LuaStateManager::getInventoryComponent)
				.def("getLightComponent", &LuaStateManager::getLightComponent)
				.def("getMeshComponent", &LuaStateManager::getMeshComponent)
				.def("getOrientationComponent", &LuaStateManager::getOrientationComponent)
				.def("getPositionComponent", &LuaStateManager::getPositionComponent)
				.def("getRoomComponent", &LuaStateManager::getRoomComponent)
				.def("getWeaponComponent", &LuaStateManager::getWeaponComponent)
				.def("getPhysicsActorComponent", &LuaStateManager::getPhysicsActorComponent)
				.def("getPhysicsTriggerComponent", &LuaStateManager::getPhysicsTriggerComponent)
				.def("getItemComponent", &LuaStateManager::getItemComponent)
				.def("getDoorComponent", &LuaStateManager::getDoorComponent)
				.def("getElevatorComponent", &LuaStateManager::getElevatorComponent)
				.def("getEventZoneComponent", &LuaStateManager::getEventZoneComponent)
				.def("getQuestComponent", &LuaStateManager::getQuestComponent)
				.def("getSwitchComponent", &LuaStateManager::getSwitchComponent)
				.def("getHumanoidComponent", &LuaStateManager::getHumanoidComponent)
				.def("getSmallCreatureComponent", &LuaStateManager::getSmallCreatureComponent)
				.def("getCameraComponent", &LuaStateManager::getCameraComponent)
				
				.def( "getSingleton", &LuaStateManager::getSingleton ) // like this
			];
		global_vars["LuaStateManager"] = &LuaStateManager::getSingleton(); 

		//////////////////////////////////////////////////////////////////////////
		// TaskManager

		module( lua )
			[
				class_< TaskManager >( "TaskManager" )
				.def("getGameObject", &TaskManager::getGameObject)
				.def( "getSingleton", &TaskManager::getSingleton ) // like this
			];
		global_vars["TaskManager"] = &TaskManager::getSingleton(); 

		//////////////////////////////////////////////////////////////////////////
		// MyGUI
		module( lua )
			[
				class_< GuiManager >( "GuiManager" )
				.def("setWallpaper", (void(GuiManager::*)(const std::string&))&GuiManager::setWallpaper )
				.def( "getSingleton", &GuiManager::getSingleton ) // like this
				
				.enum_("WindowPosition")
				[
					value("ALIGN_TOP_LEFT", 0),
					value("ALIGN_TOP_CENTER", 1),
					value("ALIGN_TOP_RIGHT", 2),
					value("ALIGN_MIDDLE_LEFT", 3),
					value("ALIGN_MIDDLE", 4),
					value("ALIGN_MIDDLE_RIGHT", 5),
					value("ALIGN_BOTTOM_LEFT", 6),
					value("ALIGN_BOTTOM", 7),
					value("ALIGN_BOTTOM_RIGHT", 8)
				]
			];
		
		GuiManager::getSingleton().getConsole()->registerConsoleDelegate("GuiManager", 
			MyGUI::newDelegate(GuiManager::getSingletonPtr(), &GuiManager::command));
		
		GuiManager::getSingleton().getConsole()->registerConsoleDelegate("GuiManager:setWallpaper", 
			MyGUI::newDelegate(GuiManager::getSingletonPtr(), &GuiManager::command));

		global_vars["GuiManager"] = &GuiManager::getSingleton(); 

		//////////////////////////////////////////////////////////////////////////

		module( lua )
			[
				class_< OgreMaxManager >( "OgreMaxManager" )
				.def("loadSceneFile", (bool(OgreMaxManager::*)(const std::string&))&OgreMaxManager::loadSceneFile )
				.def( "getSingleton", &OgreMaxManager::getSingleton ) // like this
			];

		//void(OgreMaxManager::*)

		GuiManager::getSingleton().getConsole()->registerConsoleDelegate("OgreMaxManager:loadSceneFile(<file.scene>)", 
			MyGUI::newDelegate(GuiManager::getSingletonPtr(), &GuiManager::command));

		global_vars["OgreMaxManager"] = &OgreMaxManager::getSingleton(); 

		//////////////////////////////////////////////////////////////////////////

		// Set lua bindings
		//module( lua )
		//	[
		//		class_< irrklang::ISound >( "ISound" )
		//		//.def(constructor<const std::string&>())
		//		//.def("addSoundSourceFromFile", &irrklang::ISoundSource::getCharacterAnimation)
		//		//.def( "getSingleton", &SoundManager::getSingleton ) // like this
		//	];

		//module( lua )
		//	[
		//		class_< irrklang::ISoundSource >( "ISoundSource" )
		//		//.def(constructor<const std::string&>())
		//		//.def("addSoundSourceFromFile", &irrklang::ISoundSource::getCharacterAnimation)
		//		//.def( "getSingleton", &SoundManager::getSingleton ) // like this
		//	];

			//module( lua )
			//[
			//	class_< irrklang::ISoundEngine >( "ISoundEngine" )
			//	//.def(constructor<const std::string&>())
			//	//.def("play",&irrklang::ISoundEngine::play2D) //(void (irrklang::ISoundEngine::*) (const bool, const bool,const bool,const bool)) 
			//	//.def( "getSingleton", &SoundManager::getSingleton ) // like this
			//];

		

		module( lua )
			[
				class_< SoundManager >( "SoundManager" )
				.def("getManager", &SoundManager::getManager)
				//.def("createSingleSound", &SoundManager::createSound)
				.def("play",&SoundManager::play)
				.def("createSingleSound",&SoundManager::createSingleSound)
				.def( "getSingleton", &SoundManager::getSingleton ) // like this
			];
		global_vars["SoundManager"] = &SoundManager::getSingleton(); 
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		//Register console commands
		GuiManager::getSingleton().getConsole()->registerConsoleDelegate(
			"LuaStateManager:", MyGUI::newDelegate(GuiManager::getSingletonPtr(), &GuiManager::command));
		
		GuiManager::getSingleton().getConsole()->registerConsoleDelegate(
			"LuaStateManager:runFile(<Script.lua>)", MyGUI::newDelegate(GuiManager::getSingletonPtr(), &GuiManager::command));


		

		//module(lua)
			//[
			//	def("getCharacterAnimation", &getCharacterAnimation)
			//];

		//global_vars["getCharAnimation"] = &getCharacterAnimation; 
		
		//////////////////////////////////////////////////////////////////////////
	}

	lua_State* LuaStateManager::getState() const
	{
		return L;
	}
	
	int LuaStateManager::runFile( const char *fname )
	{
		int ret;

		std::string msg;
		msg += "Lua - Loading File: ";
		msg += fname;

		CLog::Get().Write(LOG_APP,msg.c_str());

		if( ret = luaL_loadfile(L, fname) || lua_pcall( L, 0 ,0 ,0 ))
			errorHandler();

		return ret;
	}
	int LuaStateManager::errorHandler()
	{
		object error_msg(from_stack(L, -1));
		std::stringstream ss; 

		ss << error_msg << std::endl;

		//log->logMessage( ss.str(), Ogre::LML_CRITICAL );
		//log->Write(0,ss.str().c_str());
		CLog::Get().Write(LOG_USER,ss.str().c_str(),"");

		return 0;
	}
	void LuaStateManager::forceGarbageCollect()
	{
		lua_gc(L, LUA_GCCOLLECT, 0);
	}

	int LuaStateManager::runSource( const char *source )
	{
		int ret;
		if( ret = luaL_dostring(L, source) )
			errorHandler(); 

		return ret;
	}

	bool LuaStateManager::funcExist( lua_State* L, const char *name )
	{

		object g = globals(L);
		object func = g[name];

		if( func )
		{
			if( luabind::type(func) == LUA_TFUNCTION )
				return true;
		}

		return false;
	}

}
