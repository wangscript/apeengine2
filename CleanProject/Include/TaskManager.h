/*!
	@file
	@author		Pablo Nuñez
	@date		13/2009
	@module
*//*
	This file is part of the Nebula Engine.
	
	Nebula Engine is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	Nebula Engine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.
	
	You should have received a copy of the GNU Lesser General Public License
	along with Nebula Engine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _TASK_MANAGER_H
#define _TASK_MANAGER_H

#include "EnginePrerequisites.h"

namespace Nebula
{
	class ITask;

	class NebulaDllPrivate TaskManager : public Ogre::Singleton<TaskManager>,
										 public ITask
	{
	public:
		TaskManager();
		virtual ~TaskManager();

		static TaskManager& getSingleton(void);
		static TaskManager* getSingletonPtr(void);

		/**
		Execute Task.

		@return Task Response.
		*/
		int execute();

		bool addTask(ITask* t);
		void suspendTask(ITask* t);
		void resumeTask(ITask* t);
		void removeTask(ITask* t);
		void killAllTasks();

		std::map<const std::string, GameObject*> getGameObjects();

		GameObject* getGameObject(const std::string &id);
		void deleteGameObject(const std::string &id);
		GameObject* addGameObject(GameObject *go);
		void clearGameObjects();
		void updateGameObjects();
		void setupGameObjects();

		bool setAllBindings();

	private:

		bool start();
		void onSuspend();
		void update();
		void onResume();
		void stop();

		//Set Lua bindings
		void setBindings();
				
		std::list< ITask* > taskList;
		std::list< ITask* > pausedTaskList;
		std::map<const std::string, GameObject*> mGOs; 
	};

} //end namespace


#endif
