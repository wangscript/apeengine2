#ifndef _DebugText_H
#define _DebugText_H

#pragma once

#include <string>
using namespace std;

#include "Ogre.h"

using namespace Ogre;

class DebugText
{

public: 
	DebugText(SceneManager* sm,RenderWindow* window);
	~DebugText();

	//static DebugText& getSingleton(void);
	//static DebugText* getSingletonPtr(void);

	void updateStats(Ogre::String text);
	void addText(String text);
	void printText();
	void toggleFPSWindow();

protected:
	SceneManager* mSceneMgr;
	RenderWindow* mWindow;
	std::list<String>* mDebugLines;

	Overlay* mDebugOverlay;

};
#endif
