#include "TaskManager.h"

template<> Nebula::TaskManager* Ogre::Singleton<Nebula::TaskManager>::ms_Singleton = 0;

namespace Nebula {

	TaskManager* TaskManager::getSingletonPtr(void)
	{
		return ms_Singleton;
	}
	TaskManager& TaskManager::getSingleton(void)
	{
		assert( ms_Singleton );  
		return ( *ms_Singleton );
	}

	TaskManager::TaskManager()
	{

	}

	TaskManager::~TaskManager()
	{

	}

	void TaskManager::setBindings() {
		//lua_State* lua = LuaStateManager::getSingleton().getState();
		//module( lua )
		//	[
		//		class_< GuiManager >( "GuiManager" )
		//		.def("setWallpaper", (void(GuiManager::*)(const std::string&))&GuiManager::setWallpaper )
		//		.def( "getSingleton", &GuiManager::getSingleton ) // like this
		//	];

	 //   getConsole()->registerConsoleDelegate("GuiManager", MyGUI::newDelegate(this, &GuiManager::command));
		////getConsole()->registerConsoleDelegate("GuiManager:", MyGUI::newDelegate(this, &GuiManager::command));
		//getConsole()->registerConsoleDelegate("GuiManager:setWallpaper", MyGUI::newDelegate(this, &GuiManager::command));

		//object global_vars = globals(lua);
		//global_vars["GuiManager"] = &GuiManager::getSingleton(); 
	}

	bool TaskManager::start() {
		
		return true;
	}

	bool TaskManager::setAllBindings() {
		
		//std::list< ITask* >::iterator it;
		//for(it=taskList.begin();it!=taskList.end();)
		//{
		//	ITask *t=(*it);
		//	++it;
		//	if(!t->canKill)
		//		t->setBindings();
		//}
		return true;
	}

	void TaskManager::onSuspend() {


	}
	
	void TaskManager::update()  {
		updateGameObjects();
	}

	void TaskManager::onResume()  {


	}

	void TaskManager::stop()  {


	}

	int TaskManager::execute()
	{
		while(!taskList.empty())
		{
			{
				PROFILE("Engine task loop");

				std::list< ITask* >::iterator it, thisIt;
				for(it=taskList.begin();it!=taskList.end();)
				{
					ITask *t=(*it);
					++it;
					if(!t->canKill)t->update();
				}
				//loop again to remove dead tasks
				for(it=taskList.begin();it!=taskList.end();)
				{
					ITask *t=(*it);
					thisIt=it; ++it;
					if(t->canKill)
					{
						t->stop();
						// 25-07-03 - updated this to use erase() rather than remove()
						taskList.erase(thisIt);
						t=0;
					}
				}
				//IMMObject::CollectGarbage();
			}
	#ifdef PROFILER
			CProfileSample::Output();
	#endif
		}

		return 0;
	}

	bool TaskManager::addTask(ITask* t)
	{
		if(!t->start())return false;

		//keep the order of priorities straight
		std::list< ITask* >::iterator it;
		for(it=taskList.begin();it!=taskList.end();it++)
		{
			ITask *comp=(*it);
			if(comp->priority>t->priority)break;
		}
		taskList.insert(it,t);
		return true;
	}

	void TaskManager::suspendTask(ITask* t)
	{
		//check that this task is in our list - we don't want to suspend a task that isn't running
		if(std::find(taskList.begin(),taskList.end(),t)!=taskList.end())
		{
			t->onSuspend();
			taskList.remove(t);
			pausedTaskList.push_back(t);
		}
	}

	void TaskManager::resumeTask(ITask* t)
	{
		if(std::find(pausedTaskList.begin(),pausedTaskList.end(),t)!=pausedTaskList.end())
		{
			t->onResume();
			pausedTaskList.remove(t);
			//keep the order of priorities straight
			std::list< ITask* >::iterator it;
			for(it=taskList.begin();it!=taskList.end();it++)
			{
				ITask *comp=(*it);
				if(comp->priority>t->priority)break;
			}
			taskList.insert(it,t);
		}
	}

	void TaskManager::removeTask(ITask* t)
	{
		assert(!t && "Tried to remove a null task.");
		if(std::find(taskList.begin(),taskList.end(),t)!=taskList.end())
		{
			t->canKill=true;
			return;
		}
		//check the suspended list
		std::list< ITask* >::iterator it;
		if((it=std::find(pausedTaskList.begin(),pausedTaskList.end(),t))!=taskList.end())
		{
			//kill the task immediately
			t->stop();
			pausedTaskList.erase(it);
			return;
		}

	}

	void TaskManager::killAllTasks()
	{
		for(std::list< ITask* >::iterator it=taskList.begin();it!=taskList.end();it++)
		{
			(*it)->canKill=true;
		}
		//kill all paused tasks right now
		std::list< ITask* >::iterator it;
		for(it=pausedTaskList.begin();it!=pausedTaskList.end();it++)
		{
			(*it)->stop();
		}
		pausedTaskList.clear();
	}

	std::map<const std::string, GameObject*> TaskManager::getGameObjects() { 
		return mGOs;
	}

	//Retrieve a Game Object
	GameObject* TaskManager::getGameObject(const std::string &id) {
		//return mGOs[id];

		std::map<const std::string, GameObject*>::iterator iter = mGOs.begin();
		iter = mGOs.find(id);
		if(iter != mGOs.end()) {
			return iter->second;
		}
		return NULL;
	}
	void TaskManager::deleteGameObject(const std::string &id) {
		std::map<const std::string, GameObject*>::iterator iter = mGOs.begin();
		iter = mGOs.find(id);

		if(iter != mGOs.end()) {
			iter->second->clearComponents();
			mGOs.erase(iter);
		}
	}

	GameObject* TaskManager::addGameObject(GameObject *go) {
		mGOs[go->getID()] = go;

		go->setLuaState(LuaStateManager::getSingleton().getState());

		return mGOs[go->getID()];
	}


	void TaskManager::clearGameObjects() {
		std::map<const std::string, GameObject*>::iterator iter;
		for(iter = mGOs.begin(); iter != mGOs.end(); iter++) {
			iter->second->clearComponents();
		}
		mGOs.clear();
	}

	void TaskManager::updateGameObjects() { 
		std::map<const std::string, GameObject*>::iterator iter;
		for(iter = mGOs.begin(); iter != mGOs.end(); iter++) {
			
			//if(iter->second->getID() == "Box05") {

			//	OgreManager::getSingleton().getDebugText()->addText( "update: yes " );
			//}

			iter->second->update();
		}
	}
	void TaskManager::setupGameObjects() {
		std::map<const std::string, GameObject*>::iterator iter;
		for(iter = mGOs.begin(); iter != mGOs.end(); iter++) {
			iter->second->setup();
		}
	}


} //end namespace