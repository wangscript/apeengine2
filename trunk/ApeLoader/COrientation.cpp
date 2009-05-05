#include "COrientation.h"

/*static*/ 
std::string COrientation::mFamilyID = "COrientation";
std::string COrientation::mComponentID = "COrientation";

COrientation::COrientation()
{
	Orientation = Quaternion::IDENTITY;
}
COrientation::COrientation(Ogre::Quaternion q)
{
	Orientation = q;
}

COrientation::~COrientation()
{

}

void COrientation::update() {

}

void COrientation::setup() {
	
}
