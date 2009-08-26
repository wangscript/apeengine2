#include "WeaponTrail.h"

namespace Nebula {

	//---------------------------------------------------------------------------//
	WeaponTrail::WeaponTrail(const std::string& p_Name) :
	m_TrailObject(0),
	m_MaxSegmentCount(50), //2 50
	m_TrailBase(0),
	m_TrailTip(0),
	m_IsActive(true)
	{
		m_SegmentStartColorChange = Ogre::ColourValue(1.0,1.0,1.0,1.0);
		m_SegmentEndColorChange = Ogre::ColourValue(1.0,1.0,1.0,1.0);
		m_SegmentStartInitialColor = Ogre::ColourValue(0.6,0.5,0.8,1.0);
		m_SegmentEndInitialColor = Ogre::ColourValue(1.0,0.2,1.0,1.0);

		m_SegmentStartColorChange *= 1.5;
		m_SegmentEndColorChange *= 1.5;

		m_Width = 3.0;

		setWeaponEntity(0);
		init();

		mName = p_Name;
	}
	//---------------------------------------------------------------------------//
	WeaponTrail::~WeaponTrail()
	{
		uninit();
	}
	
	void WeaponTrail::setColourChange(const Ogre::ColourValue& start,const Ogre::ColourValue& end) {
		m_SegmentStartColorChange = start;
		m_SegmentEndColorChange = end;
	}

	void WeaponTrail::setColourInitial(const Ogre::ColourValue& start,const Ogre::ColourValue& end) {
		m_SegmentStartInitialColor = start;
		m_SegmentEndInitialColor = end;
	}

	//void WeaponTrail::setWidth(float width) {
	//	m_Width = width;
	//}

	void WeaponTrail::setTrailBaseNode(SceneNode* node) {
		m_TrailBase = node;
	}

	void WeaponTrail::setTrailBaseTip(SceneNode* node) {
		m_TrailTip = node;
	}

	//---------------------------------------------------------------------------//
	void WeaponTrail::init()
	{
		// create object
		m_TrailObject =
			OgreManager::getSingleton().getSceneManager()->createManualObject(mName);
		
		m_TrailObject->estimateVertexCount(m_MaxSegmentCount * 2);
		m_TrailObject->setDynamic(true);

		m_TrailObject->begin("swordMaterial", Ogre::RenderOperation::OT_TRIANGLE_STRIP);

		// fill the object (the actual data does not matter here)
		for(int i=0; i<m_MaxSegmentCount; ++i)
		{
			//m_TrailObject->position(-i*20, 0, 0);
			m_TrailObject->position(0, -i*20, 0);
			m_TrailObject->textureCoord(0,0);
			m_TrailObject->colour(1,0,0,1);
			//m_TrailObject->position(-i*20, 3, 0);
			m_TrailObject->position(0, -i*20, 3);
			m_TrailObject->textureCoord(1,0);
			m_TrailObject->colour(1,0,0,1);
		}
		m_TrailObject->end();

		// create node and attach object
		m_TrailNode =
			OgreManager::getSingleton().getSceneManager()->getRootSceneNode()->createChildSceneNode();
		
		//Ogre::SceneNode* rotNode = m_TrailNode->createChildSceneNode();
		m_TrailNode->attachObject(m_TrailObject);
		
		//rotNode->rotate(Quaternion(Degree(90), Ogre::Vector3::UNIT_Y),Ogre::SceneNode::TransformSpace::TS_WORLD);

		m_TrailObject->setVisible(false);
	}
	//---------------------------------------------------------------------------//
	void WeaponTrail::uninit()
	{
		m_IsActive = false;

		// detach object and remove node
		m_TrailNode->detachObject(m_TrailObject);
		OgreManager::getSingleton().getSceneManager()->getRootSceneNode()->
			removeAndDestroyChild(m_TrailNode->getName());

		// remove object
		m_TrailObject->setVisible(false);
		OgreManager::getSingleton().getSceneManager()->destroyManualObject(m_TrailObject); 
	}
	//---------------------------------------------------------------------------//
	void WeaponTrail::setWeaponEntity(Entity* p_WeaponEntity)
	{
		m_WeaponEntity = p_WeaponEntity;
		if (m_WeaponEntity)
		{   
			m_WeaponNode = m_WeaponEntity->getParentSceneNode();
			//m_WeaponNode = m_WeaponEntity->getParentSceneNode()->createChildSceneNode();
			//Ogre::SceneNode* n = m_WeaponNode->createChildSceneNode();
			//n->getParentSceneNode()->rotate(Quaternion(Degree(90), Ogre::Vector3::UNIT_Y),Ogre::SceneNode::TransformSpace::TS_WORLD);
		}
		else
		{
			m_WeaponNode = 0;
		}
	}
	//---------------------------------------------------------------------------//
	void WeaponTrail::onUpdate(float p_DeltaT)
	{
		// early out
		if(!isActive() && !isVisible())
		{
			return;
		}
		if (!m_WeaponEntity || !m_WeaponNode)
		{
			return;
		}
		if (!m_TrailObject)
		{
			return;
		}

		m_TrailObject->setVisible(true);

		// iterate over the current segments, apply alpha change
		for(TrailSegmentList::iterator it = m_SegmentList.begin();
			it != m_SegmentList.end();)
		{
			(*it).segmentStartColor -= m_SegmentStartColorChange * p_DeltaT * 2.5;
			(*it).segmentEndColor -= m_SegmentEndColorChange * p_DeltaT * 2.5;
			(*it).segmentStartColor.saturate();
			(*it).segmentEndColor.saturate();
			if((*it).segmentStartColor == Ogre::ColourValue::ZERO && (*it).segmentEndColor == Ogre::ColourValue::ZERO)
			{
				it = m_SegmentList.erase(it);
			}
			else
			{
				++it;
			}
		}

		// throw away the last element if the maximum number of segments is used
		unsigned int segSize = (unsigned int)m_MaxSegmentCount;
		if(m_SegmentList.size() >= segSize)
		{
			m_SegmentList.pop_back();
		}

		// only add a new segment if active
		if(isActive())
		{
			//Ogre::Quaternion q = Quaternion(Degree(90), Ogre::Vector3::UNIT_Y);
			//m_WeaponNode->setOrientation(m_WeaponNode->_getDerivedOrientation() * q);

			// the segment to add to the trail
			TrailSegment newSegment;
			// initial the trail
			newSegment.segmentStartColor = getSegmentStartInitialColor();
			newSegment.segmentEndColor = getSegmentEndInitialColor();
			
			if(m_TrailBase) {
				m_TrailBase->_update(true, true);
				newSegment.segmentStart  = m_TrailBase->_getDerivedPosition();
			}

			Vector3 pos = m_WeaponNode->getPosition();
			// probably quite costly way to get the second position
			//m_WeaponNode->translate(Vector3(0, m_Width, 0), SceneNode::TS_LOCAL);

			if(m_TrailTip) {
				m_TrailTip->_update(true, true);
				newSegment.segmentEnd = m_TrailTip->_getDerivedPosition();
			}

			m_WeaponNode->setPosition(pos);
			
			//m_WeaponNode->rotate(Quaternion(Degree(90), Ogre::Vector3::UNIT_Y),Ogre::SceneNode::TransformSpace::TS_WORLD);

			m_SegmentList.push_front(newSegment);
		}
		// update the manual object
		m_TrailObject->beginUpdate(0);
		int segmentCount = 0;
		for(TrailSegmentList::iterator it = m_SegmentList.begin();
			it != m_SegmentList.end(); ++it)
		{
			m_TrailObject->position((*it).segmentStart);
			m_TrailObject->textureCoord(0,0);
			m_TrailObject->colour((*it).segmentStartColor);
			m_TrailObject->position((*it).segmentEnd);
			m_TrailObject->textureCoord(1,0);
			m_TrailObject->colour((*it).segmentEndColor);

			++segmentCount;
		}

		//m_WeaponNode->rotate(Quaternion(Degree(90), Ogre::Vector3::UNIT_Y),Ogre::SceneNode::TransformSpace::TS_WORLD);
		

		// use the last position to render the invisible part of the trail
		// as degenerate triangles
		Vector3 lastPos = Vector3::ZERO;
		if(!m_SegmentList.empty())
		{
			lastPos = m_SegmentList.back().segmentStart;
		}
		for(int i=segmentCount*2;i<m_MaxSegmentCount * 2;++i)
		{
			m_TrailObject->position(lastPos);
		}
		// end the update
		m_TrailObject->end();
	}
	//---------------------------------------------------------------------------//
	void WeaponTrail::setMaterialName(const String& p_MaterialName)
	{
		m_MaterialName = p_MaterialName;
		if(m_TrailObject)
		{
			m_TrailObject->setMaterialName(0, m_MaterialName);
		}
	}
	//---------------------------------------------------------------------------//
	void WeaponTrail::setSegmentStartColorChange(const Ogre::ColourValue& p_ColorChange)
	{
		m_SegmentStartColorChange = p_ColorChange;
	}
	//---------------------------------------------------------------------------//
	const Ogre::ColourValue& WeaponTrail::getSegmentStartColorChange() const
	{
		return m_SegmentStartColorChange;
	}
	//---------------------------------------------------------------------------//
	void WeaponTrail::setSegmentEndColorChange(const Ogre::ColourValue& p_ColorChange)
	{
		m_SegmentEndColorChange = p_ColorChange;
	}
	//---------------------------------------------------------------------------//
	const Ogre::ColourValue& WeaponTrail::getSegmentEndColorChange() const
	{
		return m_SegmentEndColorChange;
	}
	//---------------------------------------------------------------------------//
	void WeaponTrail::setSegmentStartInitialColor(const Ogre::ColourValue& p_Color)
	{
		m_SegmentStartInitialColor = p_Color;
	}
	//---------------------------------------------------------------------------//
	const Ogre::ColourValue& WeaponTrail::getSegmentStartInitialColor() const
	{
		return m_SegmentStartInitialColor;
	}
	//---------------------------------------------------------------------------//
	void WeaponTrail::setSegmentEndInitialColor(const Ogre::ColourValue& p_Color)
	{
		m_SegmentEndInitialColor = p_Color;
	}
	//---------------------------------------------------------------------------//
	const Ogre::ColourValue& WeaponTrail::getSegmentEndInitialColor() const
	{
		return m_SegmentEndInitialColor;
	}
	//---------------------------------------------------------------------------//
	void WeaponTrail::setActive(bool p_Active)
	{
		m_IsActive = p_Active;
	}
	//---------------------------------------------------------------------------//
	bool WeaponTrail::isActive() const
	{
		return m_IsActive;
	}
	//---------------------------------------------------------------------------//
	bool WeaponTrail::isVisible() const
	{
		return !m_SegmentList.empty();
	}
	//---------------------------------------------------------------------------//

} //end namespace