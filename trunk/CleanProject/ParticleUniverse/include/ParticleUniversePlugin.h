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

#ifndef __PARTICLE_UNIVERSE_PLUGIN_H__
#define __PARTICLE_UNIVERSE_PLUGIN_H__

#include "OgrePlugin.h"
#include "ParticleUniverseSystemManager.h"
#include "ParticleUniverseRendererFactory.h"
#include "ParticleUniverseEmitterFactory.h"
#include "ParticleUniverseAffectorFactory.h"
#include "ParticleUniverseObserverFactory.h"
#include "ParticleUniverseEventHandlerFactory.h"
#include "ParticleUniverseExternFactory.h"
#include "ParticleUniverseBehaviourFactory.h"
#include "ParticleUniverseScriptTokeniser.h"
#include "ParticleUniverseGrammar.h"

#include "Externs/ParticleUniverseGravityExternFactory.h"
#include "Externs/ParticleUniverseSphereColliderExternFactory.h"
#include "Externs/ParticleUniverseBoxColliderExternFactory.h"
#include "Externs/ParticleUniverseVortexExternFactory.h"

#include "ParticleRenderers/ParticleUniverseBillboardRendererFactory.h"
#include "ParticleRenderers/ParticleUniverseBoxRendererFactory.h"
#include "ParticleRenderers/ParticleUniverseSphereRendererFactory.h"
#include "ParticleRenderers/ParticleUniverseEntityRendererFactory.h"
#include "ParticleRenderers/ParticleUniverseRibbonTrailRendererFactory.h"
#include "ParticleRenderers/ParticleUniverseLightRendererFactory.h"

#include "ParticleEmitters/ParticleUniversePointEmitterFactory.h"
#include "ParticleEmitters/ParticleUniverseLineEmitterFactory.h"
#include "ParticleEmitters/ParticleUniverseBoxEmitterFactory.h"
#include "ParticleEmitters/ParticleUniverseCircleEmitterFactory.h"
#include "ParticleEmitters/ParticleUniverseSphereSurfaceEmitterFactory.h"
#include "ParticleEmitters/ParticleUniverseVertexEmitterFactory.h"
#include "ParticleEmitters/ParticleUniverseMeshSurfaceEmitterFactory.h"
#include "ParticleEmitters/ParticleUniversePositionEmitterFactory.h"
#include "ParticleEmitters/ParticleUniverseSlaveEmitterFactory.h"

#include "ParticleAffectors/ParticleUniverseForceAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseLinearForceAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseVortexAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseGravityAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseParticleFollowerFactory.h"
#include "ParticleAffectors/ParticleUniverseRandomiserFactory.h"
#include "ParticleAffectors/ParticleUniverseLineAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseScaleAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseGeometryRotatorFactory.h"
#include "ParticleAffectors/ParticleUniverseTextureRotatorFactory.h"
#include "ParticleAffectors/ParticleUniverseJetAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseAlignAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseFlockCenteringAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseCollisionAvoidanceAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseVelocityMatchingAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseColourAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseSineForceAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseSphereColliderFactory.h"
#include "ParticleAffectors/ParticleUniversePlaneColliderFactory.h"
#include "ParticleAffectors/ParticleUniverseBoxColliderFactory.h"
#include "ParticleAffectors/ParticleUniverseInterParticleColliderFactory.h"
#include "ParticleAffectors/ParticleUniversePathFollowerFactory.h"
#include "ParticleAffectors/ParticleUniverseColliderFactory.h"

#include "ParticleObservers/ParticleUniverseOnExpireObserverFactory.h"
#include "ParticleObservers/ParticleUniverseOnEmissionObserverFactory.h"
#include "ParticleObservers/ParticleUniverseOnCountObserverFactory.h"
#include "ParticleObservers/ParticleUniverseOnEventFlagObserverFactory.h"
#include "ParticleObservers/ParticleUniverseOnCollisionObserverFactory.h"
#include "ParticleObservers/ParticleUniverseOnVelocityObserverFactory.h"
#include "ParticleObservers/ParticleUniverseOnTimeObserverFactory.h"
#include "ParticleObservers/ParticleUniverseOnPositionObserverFactory.h"
#include "ParticleObservers/ParticleUniverseOnClearObserverFactory.h"
#include "ParticleObservers/ParticleUniverseOnQuotaObserverFactory.h"
#include "ParticleObservers/ParticleUniverseOnRandomObserverFactory.h"

#include "ParticleEventHandlers/ParticleUniverseDoExpireEventHandlerFactory.h"
#include "ParticleEventHandlers/ParticleUniverseDoFreezeEventHandlerFactory.h"
#include "ParticleEventHandlers/ParticleUniverseDoPlacementParticleEventHandlerFactory.h"
#include "ParticleEventHandlers/ParticleUniverseDoStopSystemEventHandlerFactory.h"
#include "ParticleEventHandlers/ParticleUniverseDoEnableComponentEventHandlerFactory.h"
#include "ParticleEventHandlers/ParticleUniverseDoAffectorEventHandlerFactory.h"
#include "ParticleEventHandlers/ParticleUniverseDoScaleEventHandlerFactory.h"

#include "ParticleBehaviours/ParticleUniverseSlaveBehaviourFactory.h"

namespace ParticleUniverse
{
	/** Plugin instance for Particle Universe */
	class ParticleUniversePlugin : public Ogre::Plugin
	{
	public:
		ParticleUniversePlugin();

		/// @copydoc Plugin::getName
		const Ogre::String& getName() const;

		/// @copydoc Plugin::install
		void install();

		/// @copydoc Plugin::initialise
		void initialise();

		/// @copydoc Plugin::shutdown
		void shutdown();

		/// @copydoc Plugin::uninstall
		void uninstall();

	protected:
		ParticleScriptTokeniser* mParticleScriptTokeniser;
		Grammar* mGrammar;
		ParticleSystemManager* mParticleSystemManager;

		std::vector<ParticleRendererFactory*> mRendererFactories;
		std::vector<ParticleEmitterFactory*> mEmitterFactories;
		std::vector<ParticleAffectorFactory*> mAffectorFactories;
		std::vector<ParticleObserverFactory*> mObserverFactories;
		std::vector<ParticleEventHandlerFactory*> mEventHandlerFactories;
		std::vector<ExternFactory*> mExternFactories;
		std::vector<ParticleBehaviourFactory*> mBehaviourFactories;
	};
}

#endif
