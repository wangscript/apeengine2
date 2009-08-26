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
#ifndef __ITASK_HPP__
#define __ITASK_HPP__

namespace Nebula
{

	class NebulaDllPrivate ITask
	{
	public:
		ITask(){canKill=false;priority=5000;}
		virtual bool start()=0;
		virtual void onSuspend(){};
		virtual void update()=0;
		virtual void onResume(){};
		virtual void stop()=0;
		//virtual void setBindings()=0;
		bool canKill;
		long priority;
	};

} //end namespace

#endif