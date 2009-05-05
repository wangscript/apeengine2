#include "CPosition.h"

/*static*/ 
const std::string CPosition::mFamilyID = "CPosition";
const std::string CPosition::mComponentID = "CPosition";

CPosition::CPosition()
{
	Position = Vector3(0,0,0);
}
CPosition::CPosition(Ogre::Vector3 vec)
{
	Position = vec;
}
CPosition::~CPosition()
{

}

void CPosition::update() {

}

void CPosition::setup() {
	
}
