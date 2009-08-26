#include "CPosition.h"

namespace Nebula {
	CPosition::CPosition()
	{
		mComponentID = "CPosition";
	}

	CPosition::CPosition(const CPositionDesc& desc) : Ogre::Vector3(Ogre::Vector3::ZERO)
	{
		mComponentID = "CPosition";
		mDesc = desc;
	}

	CPosition::~CPosition()
	{

	}

	void CPosition::update() {

	}

	void CPosition::setup() {
		
	}

} //end namespace
