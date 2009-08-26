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

#ifndef _CLIGHT_H_
#define _CLIGHT_H_

#include "EnginePrerequisites.h"

namespace Nebula {

	using namespace Ogre;
	class IGameComponent;
	
	struct NebulaDllPrivate CLightDesc
	{
		CLightDesc()
		{

		}

		std::string name;

		std::string parentRoom;

		Ogre::Light::LightTypes lightType;
		Ogre::Vector3 direction;
		Ogre::Radian innerAngle;
		Ogre::Radian outterAngle;
		
		Ogre::Real attenuationRange;
		Ogre::Real attenuationConstant;
		Ogre::Real attenuationLinear;
		Ogre::Real attenuationQuadratic;

		Ogre::ColourValue diffuseColour;
		Ogre::ColourValue specularColour;
	};
	
	class NebulaDllPrivate CLight : public IGameComponent {
	public:
		CLight();
		CLight(const CLightDesc&);
		~CLight();

		void update();
		void setup();

		std::string getName() {
			return mDesc.name;
		}
		
		Ogre::Light* getLight() {
			return mLight;
		}
		void setLight(Ogre::Light* light) {
			mLight = light;
		}

		CLightDesc& getDescription() {
			return mDesc;
		}

		void callLuaFunction(const std::string func );

		virtual const std::string& componentID() const { 
			return mComponentID; 
		}
	private:
		std::string mComponentID;
		Ogre::Light* mLight;
		
		CLightDesc mDesc;
	};


} //end namespace

#endif
