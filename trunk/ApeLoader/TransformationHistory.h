#ifndef __TRANFORMATION_HISTORY_H
#define __TRANFORMATION_HISTORY_H

//#include "RakNetTypes.h"
#include "OgreVector3.h"
#include "OgreQuaternion.h"
//#include "DS_Queue.h"

struct TransformationHistoryCell
{
	TransformationHistoryCell();
	TransformationHistoryCell(unsigned long t, const Ogre::Vector3& pos, const Ogre::Vector3& vel, const Ogre::Quaternion& quat  );

	unsigned long time;
	Ogre::Vector3 position;
	Ogre::Quaternion orientation;
	Ogre::Vector3 velocity;
};

class TransformationHistory
{
public:
	void Init(unsigned long maxWriteInterval, unsigned long maxHistoryTime);
	void Write(const Ogre::Vector3 &position, const Ogre::Vector3 &velocity, const Ogre::Quaternion &orientation, unsigned long curTimeMS);
	void Overwrite(const Ogre::Vector3 &position, const Ogre::Vector3 &velocity, const Ogre::Quaternion &orientation, unsigned long when);
	// Parameters are in/out, modified to reflect the history
	void Read(Ogre::Vector3 *position, Ogre::Vector3 *velocity, Ogre::Quaternion *orientation,
		unsigned long when, unsigned long curTime);
	void Clear(void);
	//void set
protected:
	DataStructures::Queue<TransformationHistoryCell> history;
	unsigned maxHistoryLength;
	unsigned long writeInterval;
	//unsigned long elapsedTime;
};

#endif
