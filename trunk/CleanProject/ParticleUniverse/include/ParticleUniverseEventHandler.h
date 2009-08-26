/*
-----------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2006-2008 Henry van Merode

Usage of this program is free for non-commercial use and licensed under the
the terms of the GNU Lesser General Public License.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
-----------------------------------------------------------------------------
*/

#ifndef __PU_EVENT_HANDLER_H__
#define __PU_EVENT_HANDLER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseIAlias.h"
#include "ParticleUniverseIElement.h"

namespace ParticleUniverse
{
	/** A ParticleEventHandlers is used to perform a task in case a certain event happens.
	@remarks
		A ParticleEventHandler is associated with a ParticleObserver; The ParticleObserver signals what event occurs,
		while the ParticleEventHandler performs some action.
	*/
	class _ParticleUniverseExport ParticleEventHandler : public IAlias, public IElement
	{
		protected:
			// Observer to which the eventhandler is associated.
			ParticleObserver* mParentObserver;

			// Type of event handler
			Ogre::String mEventHandlerType;

			// Name of the eventHandler (optional)
			Ogre::String mName;

			/** Although the scale is on a Particle System level, it is stored here also, because this value is often 
				used. It is a derived value, so it has not get a get and set function.
			*/
			Ogre::Vector3 _mParticleSystemScale;

		public:
			ParticleEventHandler(void) : 
				IElement(),
				mParentObserver(0),
				mName(Ogre::StringUtil::BLANK),
				_mParticleSystemScale(Ogre::Vector3::UNIT_SCALE)
			{
				mAliasType = AT_HANDLER;
			};
			virtual ~ParticleEventHandler(void) {};

			/** 
	        */
			const Ogre::String& getName(void) const {return mName;};
			void setName(const Ogre::String& name) {mName = name;};

			/** 
	        */
			ParticleObserver* getParentObserver(void) const {return mParentObserver;};
			void setParentObserver(ParticleObserver* parentObserver) {mParentObserver = parentObserver;};

			/** 
	        */
			const Ogre::String& getEventHandlerType(void) const {return mEventHandlerType;};
			void setEventHandlerType(const Ogre::String& eventHandlerType) {mEventHandlerType = eventHandlerType;};

			/** Notify that the Particle System is rescaled.
	        */
			virtual void _notifyRescaled(const Ogre::Vector3& scale){_mParticleSystemScale = scale;};

			/** 
	        */
			virtual void _handle(ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed) = 0;

			/** Copy attributes to another event handler.
	        */
			virtual void copyAttributesTo (ParticleEventHandler* eventHandler)
			{
				eventHandler->setName(mName);
				eventHandler->mParentObserver = mParentObserver;
				eventHandler->_mParticleSystemScale = _mParticleSystemScale;
			};
	};

}
#endif
