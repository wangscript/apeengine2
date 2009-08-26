/*
Nebula Engine
http://code.google.com/p/apeengine2/

Copyright (c) 2008 Pablo Santiago Nuñez

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

#ifndef _WEAPON_TRAIL_H
#define _WEAPON_TRAIL_H

#include "EnginePrerequisites.h"

namespace Nebula {

	using namespace Ogre;
	
	class Ogre::Node;
	/** @brief WeaponTrail class, responsible for automatically creating a trail
	*         "behind" a weapon
	*/
	class WeaponTrail
	{
	public:
		/** @brief constructor */
		WeaponTrail(const std::string& p_Name);
		/** @brief deconstructor */
		virtual ~WeaponTrail();

		void setColourChange(const Ogre::ColourValue& start,const Ogre::ColourValue& end);
		void setColourInitial(const Ogre::ColourValue& start,const Ogre::ColourValue& end);
		//void setWidth(float width);

		/// Set the weapon entity to which the trail is attached
		void setWeaponEntity(Entity* p_WeaponEntity);
		/// update the weapon trail
		void onUpdate(float p_DeltaT);
		/// Set the name of the material to use for the trail
		void setMaterialName(const String& p_MaterialName);
		/// set the initial color of the start of segments
		void setSegmentStartInitialColor(const Ogre::ColourValue& p_Color);
		/// get the initial color of the start of segments
		const Ogre::ColourValue& getSegmentStartInitialColor() const;
		/// set the initial color of the end of segments
		void setSegmentEndInitialColor(const Ogre::ColourValue& p_Color);
		/// get the initial color of the end of segments
		const Ogre::ColourValue& getSegmentEndInitialColor() const;
		/// set how the color of the start of segments will change over time
		void setSegmentStartColorChange(const Ogre::ColourValue& p_ColorChange);
		/// get how the color of the start of segments will change over time
		const Ogre::ColourValue& getSegmentStartColorChange() const;
		/// set how the color of the start of segments will change over time
		void setSegmentEndColorChange(const Ogre::ColourValue& p_ColorChange);
		/// get how the color of the start of segments will change over time
		const Ogre::ColourValue& getSegmentEndColorChange() const;
		/// Return the max vertex count of the trail
		inline int getMaxSegmentCount() const {return m_MaxSegmentCount;}
		/// set the width
		void setWidth(float p_Width) {m_Width = p_Width;}
		/// get the width
		float getWidth() const {return m_Width;}
		/// Set whether new segments are added
		void setActive(bool p_Active = true);
		/// Get whether new segments are added
		bool isActive() const;
		/// Get whether there are currently segments in the list
		bool isVisible() const;
		
		void setTrailBaseNode(SceneNode*);
		void setTrailBaseTip(SceneNode*);

	protected:

		/// a trail segment
		struct TrailSegment
		{
			/// start position
			Vector3 segmentStart;
			/// end position
			Vector3 segmentEnd;
			/// current segment start color
			Ogre::ColourValue segmentStartColor;
			/// current segment end color
			Ogre::ColourValue segmentEndColor;
		}; // end TrailSegment struct declaration

		/// typedef for a list of trail segments
		typedef std::list<TrailSegment> TrailSegmentList;
		/// the list of currently active trail segments
		TrailSegmentList m_SegmentList;

		/// Initializes the manual object
		void init();
		/// Uninitializes the manual object
		void uninit();
		
		std::string mName;

		SceneNode* m_TrailBase;
		SceneNode* m_TrailTip;

		ManualObject* m_TrailObject;        //!< the dynamically changed mesh representing the trail
		Entity* m_WeaponEntity;             //!< the entity representing the weapon;
		SceneNode* m_WeaponNode;                 //!< the node the tracked entity is attached to
		SceneNode* m_TrailNode;             //!< the node the manual object is attached to
		String m_MaterialName;              //!< the name of the material to use
		const int m_MaxSegmentCount;        //!< the maximum number of segments the trail will consist of
		Ogre::ColourValue m_SegmentStartInitialColor;   //!< the initial color of start segments
		Ogre::ColourValue m_SegmentEndInitialColor;     //!< the initial color of end segments
		Ogre::ColourValue m_SegmentStartColorChange;    //!< how the color of start segments will change over time
		Ogre::ColourValue m_SegmentEndColorChange;      //!< how the color of end segments will change over time
		float m_Width;                      //!< the width of the trail
		bool m_IsActive;                    //!< flag indicating whether new segments are generated

	}; // end of WeaponTrail class declaration


} //end namespace

#endif
