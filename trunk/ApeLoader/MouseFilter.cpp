// Mouse filter from ICE, refactored a bit

#include <stdio.h>
#ifdef WIN32 
	#define NOMINMAX
	#include <windows.h>
#elif LINUX
#endif
#include "Nx.h"
#include "MouseFilter.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Constructor.
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MouseFilter::MouseFilter() : mHistoryBufferX(0),
							mHistoryBufferY(0),
							mHistoryBufferZ(0),
							mWeightModifier(0.0f),
							mHistoryBufferLength(0)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Constructor.
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MouseFilter::MouseFilter(unsigned int length, float weight_modifier) : mHistoryBufferX(0),
																	   mHistoryBufferY(0),
																	   mHistoryBufferZ(0),
																	   mHistoryBufferLength(0),
																	   mWeightModifier(weight_modifier),
																	   mTime(0)
{											
	SetHistoryBufferLength(length);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Destructor.
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MouseFilter::~MouseFilter()
{
	NX_DELETE_ARRAY(mHistoryBufferX);
	NX_DELETE_ARRAY(mHistoryBufferY);
	NX_DELETE_ARRAY(mHistoryBufferZ);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Sets the length of the history buffer.
 *	\param		length	[in] buffer length
 *	\return		true if success
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MouseFilter::SetHistoryBufferLength(unsigned int length)
{
	NX_DELETE_ARRAY(mHistoryBufferX);
	NX_DELETE_ARRAY(mHistoryBufferY);
	NX_DELETE_ARRAY(mHistoryBufferZ);

	mHistoryBufferLength = length;
	
	if(length)
	{
		mHistoryBufferX = new float[length];	
        memset(mHistoryBufferX, 0, length*sizeof(float)); 
		mHistoryBufferY = new float[length];	
        memset(mHistoryBufferY, 0, length*sizeof(float));		
		mHistoryBufferZ = new float[length];	
		memset(mHistoryBufferZ, 0, length*sizeof(float));		

	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Filters mouse motion.
 *	\param		delta_mouse_x	[in/out] delta mouse position
 *	\param		delta_mouse_y	[in/out] delta mouse position
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MouseFilter::Apply(float& delta_mouse_x, float& delta_mouse_y)
{
	// Checkings
	if(!mHistoryBufferX || !mHistoryBufferY)	return;

	// Shift the buffer around. If you want performance from this, be sure
	// to use a circular buffer than these slow memmove()s.
	memmove(mHistoryBufferX+1, mHistoryBufferX, (mHistoryBufferLength-1)*sizeof(float));
	memmove(mHistoryBufferY+1, mHistoryBufferY, (mHistoryBufferLength-1)*sizeof(float));
	
	// Put the current values at the front of the history buffer
	*mHistoryBufferX = delta_mouse_x;
	*mHistoryBufferY = delta_mouse_y;

	// Filter the mouse
	float CurAverageX	= 0.0f;
	float CurAverageY	= 0.0f;
	float AverageTot	= 0.0f;
	float CurrentWeight	= 1.0f;
	for(unsigned int i=0;i<mHistoryBufferLength;i++)
	{
		CurAverageX += mHistoryBufferX[i] * (CurrentWeight - mTime);
		CurAverageY += mHistoryBufferY[i] * (CurrentWeight - mTime);

		// Note! Our total is also weighted
		AverageTot += (1.0f - mTime) * CurrentWeight;

		// The weight for the next entry in the history buffer
		//float test = mTime;
		CurrentWeight *= (mWeightModifier);
	}

	// Calculate the final weighted value
	delta_mouse_x = CurAverageX / AverageTot;
	delta_mouse_y = CurAverageY / AverageTot;
}
void MouseFilter::Apply(float& delta_mouse_x, float& delta_mouse_y,float& delta_mouse_z)
{
	// Checkings
	if(!mHistoryBufferX || !mHistoryBufferY || !mHistoryBufferZ)	return;

	// Shift the buffer around. If you want performance from this, be sure
	// to use a circular buffer than these slow memmove()s.
	memmove(mHistoryBufferX+1, mHistoryBufferX, (mHistoryBufferLength-1)*sizeof(float));
	memmove(mHistoryBufferY+1, mHistoryBufferY, (mHistoryBufferLength-1)*sizeof(float));
	memmove(mHistoryBufferZ+1, mHistoryBufferZ, (mHistoryBufferLength-1)*sizeof(float));

	// Put the current values at the front of the history buffer
	*mHistoryBufferX = delta_mouse_x;
	*mHistoryBufferY = delta_mouse_y;
	*mHistoryBufferZ = delta_mouse_z;

	// Filter the mouse
	float CurAverageX	= 0.0f;
	float CurAverageY	= 0.0f;
	float CurAverageZ	= 0.0f;
	float AverageTot	= 0.0f;
	float CurrentWeight	= 1.0f; // - mTime;
	//mTime
	for(unsigned int i=0;i<mHistoryBufferLength;i++)
	{
		CurAverageX += mHistoryBufferX[i] * CurrentWeight;
		CurAverageY += mHistoryBufferY[i] * CurrentWeight;
		CurAverageZ += mHistoryBufferZ[i] * CurrentWeight;

		// Note! Our total is also weighted
		AverageTot += 1.0f * CurrentWeight;

		// The weight for the next entry in the history buffer
		CurrentWeight *= (mWeightModifier);
	}

	// Calculate the final weighted value
	delta_mouse_x = CurAverageX / AverageTot;
	delta_mouse_y = CurAverageY / AverageTot;
	delta_mouse_z = CurAverageZ / AverageTot;
}
void MouseFilter::Apply(float& delta_mouse_x, float& delta_mouse_y,float& delta_mouse_z,float& delta_mouse_w)
{
	// Checkings
	if(!mHistoryBufferX || !mHistoryBufferY || !mHistoryBufferZ || !mHistoryBufferW)	return;

	// Shift the buffer around. If you want performance from this, be sure
	// to use a circular buffer than these slow memmove()s.
	memmove(mHistoryBufferX+1, mHistoryBufferX, (mHistoryBufferLength-1)*sizeof(float));
	memmove(mHistoryBufferY+1, mHistoryBufferY, (mHistoryBufferLength-1)*sizeof(float));
	memmove(mHistoryBufferZ+1, mHistoryBufferZ, (mHistoryBufferLength-1)*sizeof(float));
	memmove(mHistoryBufferW+1, mHistoryBufferW, (mHistoryBufferLength-1)*sizeof(float));

	// Put the current values at the front of the history buffer
	*mHistoryBufferX = delta_mouse_x;
	*mHistoryBufferY = delta_mouse_y;
	*mHistoryBufferZ = delta_mouse_z;
	*mHistoryBufferW = delta_mouse_w;

	// Filter the mouse
	float CurAverageX	= 0.0f;
	float CurAverageY	= 0.0f;
	float CurAverageZ	= 0.0f;
	float CurAverageW	= 0.0f;
	float AverageTot	= 0.0f;
	float CurrentWeight	= 1.0f; // - mTime;
	//mTime
	for(unsigned int i=0;i<mHistoryBufferLength;i++)
	{
		CurAverageX += mHistoryBufferX[i] * CurrentWeight;
		CurAverageY += mHistoryBufferY[i] * CurrentWeight;
		CurAverageZ += mHistoryBufferZ[i] * CurrentWeight;
		CurAverageW += mHistoryBufferW[i] * CurrentWeight;

		// Note! Our total is also weighted
		AverageTot += 1.0f * CurrentWeight;

		// The weight for the next entry in the history buffer
		CurrentWeight *= (mWeightModifier);
	}

	// Calculate the final weighted value
	delta_mouse_x = CurAverageX / AverageTot;
	delta_mouse_y = CurAverageY / AverageTot;
	delta_mouse_z = CurAverageZ / AverageTot;
	delta_mouse_w = CurAverageW / AverageTot;
}

void MouseFilter::Apply(float& delta_mouse_x)
{
	// Checkings
	if(!mHistoryBufferX)	return;

	// Shift the buffer around. If you want performance from this, be sure
	// to use a circular buffer than these slow memmove()s.
	memmove(mHistoryBufferX+1, mHistoryBufferX, (mHistoryBufferLength-1)*sizeof(float));

	// Put the current values at the front of the history buffer
	*mHistoryBufferX = delta_mouse_x;

	// Filter the mouse
	NxF32 CurAverageX	= 0.0f;
	NxF32 AverageTot	= 0.0f;
	NxF32 CurrentWeight	= 1.0f;
	for(unsigned int i=0;i<mHistoryBufferLength;i++)
	{
		CurAverageX += mHistoryBufferX[i] * CurrentWeight;

		// Note! Our total is also weighted
		AverageTot += 1.0f * CurrentWeight;

		// The weight for the next entry in the history buffer
		CurrentWeight *= mWeightModifier;
	}

	// Calculate the final weighted value
	delta_mouse_x = CurAverageX / AverageTot;
}
