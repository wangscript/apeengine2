#include "CParticle.h"

/*static*/ 
const std::string CParticle::mFamilyID = "CParticle";
const std::string CParticle::mComponentID = "CParticle";

CParticle::CParticle(std::string particleScriptName, std::string particleNodeName)
{
	mParticleName = particleScriptName;

	mParticle = OgreRender::getSingleton().getParticleManager()->createParticleSystem(particleNodeName,mParticleName, 
		OgreRender::getSingleton().getSceneManager());

	
}

CParticle::~CParticle()
{

}

void CParticle::update() {

}

void CParticle::setup() {
	//CPosition *mPosition = dynamic_cast<CPosition*>(getOwnerObject()->getComponent("CPosition"));
	//COrientation *mOrientation = dynamic_cast<COrientation*>(getOwnerObject()->getComponent("COrientation"));
	CRender* mRender = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));
	
	//mPosition->
	mRender->mNode->attachObject(mParticle);
	//mRender->mNode->setScale(0.1,0.1,0.1);
	
	mParticle->start();

	/*
	mMesh = dynamic_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));
	mRender = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));
	*/
}
