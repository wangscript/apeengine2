/*
TecnoFreak Animation System
http://sourceforge.net/projects/tecnofreakanima/

Copyright (c) 2008 Pau Novau Lebrato

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

#include "ExampleAnimation.h"

#include <cassert>

using namespace tecnofreak;

ExampleAnimation::ExampleAnimation()
: m_activeReferencingNodesCount( 0 )
, m_accumulatedWeight( 0 )
, m_accumulatedSpeed( 0 )
, m_triggerSystem( NULL )
, m_synched( false )
, m_preUpdateTriggersRelativeTime( 0 )
{
}

ExampleAnimation::~ExampleAnimation()
{
	delete m_triggerSystem;
	m_triggerSystem = NULL;
}


int ExampleAnimation::getActiveReferencingNodesCount() const
{
	return m_activeReferencingNodesCount;
}

void ExampleAnimation::resetActiveReferencingNodesCount()
{
	m_activeReferencingNodesCount = 0;
}

void ExampleAnimation::increaseActiveReferencingNodeCount()
{
	m_activeReferencingNodesCount++;
}

float ExampleAnimation::getAccumulatedWeight() const
{
	return m_accumulatedWeight;
}

void ExampleAnimation::resetAccumulatedWeight()
{
	m_accumulatedWeight = 0;
}

void ExampleAnimation::increaseAccumulatedWeight( const float weightIncrease )
{
	m_accumulatedWeight += weightIncrease;
}

float ExampleAnimation::getAccumulatedSpeed() const
{
	return m_accumulatedSpeed;
}

void ExampleAnimation::resetAccumulatedSpeed()
{
	m_accumulatedSpeed = 0;
}

void ExampleAnimation::increaseAccumulatedSpeed( const float speedIncrease )
{
	m_accumulatedSpeed += speedIncrease;
}

float ExampleAnimation::calculateRealWeight() const
{
	assert( getActiveReferencingNodesCount() != 0 );
	return ( getAccumulatedWeight() / getActiveReferencingNodesCount() );
}

float ExampleAnimation::calculateRealSpeed() const
{
	assert( getActiveReferencingNodesCount() != 0 );
	return ( getAccumulatedSpeed() / getActiveReferencingNodesCount() );
}

void ExampleAnimation::clearTriggers()
{
	delete m_triggerSystem;
	m_triggerSystem = NULL;
}

void ExampleAnimation::addTrigger( Trigger* trigger )
{
	if ( m_triggerSystem == NULL )
	{
		m_triggerSystem = new AnimationTriggerSystem();
	}

	m_triggerSystem->addTrigger( trigger );
}

void ExampleAnimation::updateTriggers( const float currentRelativeTime, const float nextRelativeTime )
{
	if ( m_triggerSystem == NULL )
	{
		return;
	}

	m_triggerSystem->update( currentRelativeTime, nextRelativeTime, getWeight() );
}

void ExampleAnimation::addTriggerSubscriber( ITriggerSubscriber* subscriber )
{
	if ( m_triggerSystem == NULL )
	{
		m_triggerSystem = new AnimationTriggerSystem();
	}

	m_triggerSystem->addSubscriber( subscriber );
}

void ExampleAnimation::addTriggerSubscriber( const std::string& triggerName, ITriggerSubscriber* subscriber )
{
	if ( m_triggerSystem == NULL )
	{
		m_triggerSystem = new AnimationTriggerSystem();
	}

	m_triggerSystem->addSubscriber( triggerName, subscriber );

}

void ExampleAnimation::removeTriggerSubscriber( ITriggerSubscriber* subscriber )
{
	if ( m_triggerSystem == NULL )
	{
		return;
	}

	m_triggerSystem->removeSubscriber( subscriber );
}

void ExampleAnimation::removeTriggerSubscriber( const std::string& triggerName )
{
	if ( m_triggerSystem == NULL )
	{
		return;
	}

	m_triggerSystem->removeSubscriber( triggerName );
}

void ExampleAnimation::removeTriggerSubscriber( const std::string& triggerName, ITriggerSubscriber* subscriber )
{
	if ( m_triggerSystem == NULL )
	{
		return;
	}

	m_triggerSystem->removeSubscriber( triggerName, subscriber );
}

void ExampleAnimation::clearTriggerSubscribers()
{
	if ( m_triggerSystem == NULL )
	{
		return;
	}

	m_triggerSystem->removeAllSubscribers();
}

void ExampleAnimation::setSynched( const bool synched )
{
	m_synched = synched;
}

bool ExampleAnimation::getSynched() const
{
	return m_synched;
}

void ExampleAnimation::addSynchedChild( IAnimation* synchedAnimation )
{
	assert( synchedAnimation != NULL );
	if ( synchedAnimation == NULL )
	{
		return;
	}

	synchedAnimation->setSynched( true );

	m_synchedChildren.push_back( synchedAnimation );
}

void ExampleAnimation::clearSynchedChildren()
{
	for ( unsigned int i = 0; i < m_synchedChildren.size(); i++ )
	{
		IAnimation* synchedChild = getSynchedChild( i );
		synchedChild->setSynched( false );
	}

	m_synchedChildren.clear();
}

unsigned int ExampleAnimation::getSynchedChildrenCount() const
{
	return ( unsigned int )( m_synchedChildren.size() );
}

IAnimation* ExampleAnimation::getSynchedChild( const unsigned int synchedChildrenId )
{
	if ( m_synchedChildren.size() <= synchedChildrenId )
	{
		return NULL;
	}

	return m_synchedChildren[ synchedChildrenId ];
}

void ExampleAnimation::preUpdateSynchChildren()
{
	const float relativeTime = getRelativeTimePosition();
	for ( unsigned int i = 0; i < m_synchedChildren.size(); i++ )
	{
		IAnimation* synchedChild = m_synchedChildren[ i ];
		synchedChild->setRelativeTimePosition( relativeTime );
	}
}

void ExampleAnimation::postUpdateSynchChildren()
{
	float relativeTime = getRelativeTimePosition();
	for ( unsigned int i = 0; i < m_synchedChildren.size(); i++ )
	{
		IAnimation* synchedChild = m_synchedChildren[ i ];
		synchedChild->setSpeed( 1 );

		float childRelativeTime = synchedChild->getRelativeTimePosition();
		float synchDifference = relativeTime - childRelativeTime;
		float childUpdateTime = synchDifference * synchedChild->getLength();

		synchedChild->update( childUpdateTime );
	}

	clearSynchedChildren();
}

void ExampleAnimation::preUpdateTriggers()
{
	m_preUpdateTriggersRelativeTime = getRelativeTimePosition();
}

void ExampleAnimation::postUpdateTriggers( const float animationUpdateSeconds )
{
	float postUpdateRelativeTime = getRelativeTimePosition();

	float animationAdvancing = ( 0 <= animationUpdateSeconds );
	if ( animationAdvancing )
	{
		updateTriggers( m_preUpdateTriggersRelativeTime, postUpdateRelativeTime );
	}
	else
	{
		// FIXME: Update order within the trigger update won't be 100% correct, as they will
		// still be called in chronological order instead of reverse chronological order.
		updateTriggers( postUpdateRelativeTime, m_preUpdateTriggersRelativeTime );
	}
}