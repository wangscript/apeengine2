#include "DebugText.h"

namespace Nebula {

	DebugText::DebugText(SceneManager* sm,RenderWindow* window) : mSceneMgr(0),
																  mWindow(0),
																  //mDebugLines(0),
																  mDebugOverlay(0)

	{
		mSceneMgr = sm;
		mWindow = window;
		mDebugLines = new std::list<String>;
		
		mDebugOverlay = OverlayManager::getSingleton().getByName("Core/DebugOverlay");
		
	}

	DebugText::~DebugText(){
		if (mDebugLines)
			delete mDebugLines;
	}

	void DebugText::addText(String text){
		mDebugLines->push_back(text);
	}

	void DebugText::toggleFPSWindow() {
		if(mDebugOverlay->isVisible())
			mDebugOverlay->hide();
		else
			mDebugOverlay->show();
	}

	void DebugText::updateStats(Ogre::String text)
	{
		static String currFps = "Current FPS: ";
		//static String avgFps = "Average FPS: ";
		//static String bestFps = "Best FPS: ";
		//static String worstFps = "Worst FPS: ";
		//static String tris = "Triangle Count: ";

		// update stats when necessary
		OverlayElement* guiAvg = OverlayManager::getSingleton().getOverlayElement("Core/AverageFps");
		OverlayElement* guiCurr = OverlayManager::getSingleton().getOverlayElement("Core/CurrFps");
		OverlayElement* guiBest = OverlayManager::getSingleton().getOverlayElement("Core/BestFps");
		OverlayElement* guiWorst = OverlayManager::getSingleton().getOverlayElement("Core/WorstFps");
		
		guiAvg->hide();
		//guiCurr->hide();
		guiBest->hide();
		guiWorst->hide();

		//OverlayElement* guiWorst = OverlayManager::getSingleton().getOverlayElement("Core/WorstFps");

		/*guiAvg->setCaption(avgFps + StringConverter::toString(mWindow->getAverageFPS()));*/
		guiCurr->setCaption(currFps + StringConverter::toString(mWindow->getLastFPS()));
		//guiBest->setCaption(bestFps + StringConverter::toString(mWindow->getBestFPS())
		//	+" "+StringConverter::toString(mWindow->getBestFrameTime())+" ms");
		//guiWorst->setCaption(worstFps + StringConverter::toString(mWindow->getWorstFPS())
		//	+" "+StringConverter::toString(mWindow->getWorstFrameTime())+" ms");

		//OverlayElement* guiTris = OverlayManager::getSingleton().getOverlayElement("Core/NumTris");
		//guiTris->setCaption(tris + StringConverter::toString(mWindow->getTriangleCount()));

		OverlayElement* guiDbg = OverlayManager::getSingleton().getOverlayElement("Core/DebugText");
		guiDbg->setCaption(text);
		//guiDbg->setPosition(0,0);

		
		//mDebugOverlay->

	}

	void DebugText::printText(){
		String output;
		std::list<String>::iterator itr = mDebugLines->begin();
		std::list<String>::iterator itrEnd = mDebugLines->end();
		for (;itr!=itrEnd;itr++){
			output += (*itr) + " " + "\n";
		}

		updateStats(output);

		mDebugLines->clear();
	}

} //end namespace
