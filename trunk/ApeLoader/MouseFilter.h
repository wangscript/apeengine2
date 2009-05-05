#ifndef MOUSEFILTER_H
#define MOUSEFILTER_H

class MouseFilter
{
public:
	MouseFilter();
	MouseFilter(unsigned int length, float weight_modifier);
	~MouseFilter();

	float GetWeightModifier() const	{ 
		return mWeightModifier;		
	}
	
	void SetWeightModifier(float modifier) { 
		mWeightModifier = modifier;	
	}
	
	void updateTime(float modifier) { 
		mTime = modifier;	
	}

	unsigned int	GetHistoryBufferLength()				const	{ return mHistoryBufferLength;	}
	bool			SetHistoryBufferLength(unsigned int length);
			
	void			Apply(float& delta_mouse_x);
	void			Apply(float& delta_mouse_x, float& delta_mouse_y);
	void			Apply(float& delta_mouse_x, float& delta_mouse_y, float& delta_mouse_z);
	void			Apply(float& delta_mouse_x, float& delta_mouse_y, float& delta_mouse_z, float& delta_mouse_w);
	
private:
	float			mWeightModifier;
	unsigned int	mHistoryBufferLength;
	float*			mHistoryBufferX;
	float*			mHistoryBufferY;
	float*			mHistoryBufferZ;
	float*			mHistoryBufferW;
	float			mTime;
};

#endif
