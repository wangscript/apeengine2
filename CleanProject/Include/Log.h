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

#ifndef _LOG_H
#define _LOG_H

#include "EnginePrerequisites.h"

const int LOG_APP=1;
const int LOG_CLIENT=2;
const int LOG_SERVER=4;
const int LOG_USER=8;

#define MAX_LOG_STRINGS 256

namespace Nebula
{
	class NebulaDllPrivate CLog  
	{
	protected:
		CLog();

		std::ofstream appLog;
		//std::ofstream clientLog;
		//std::ofstream serverLog;

		std::string logStrings[MAX_LOG_STRINGS];
		bool LoadStrings();

	public:
		static CLog &Get();

		bool Init();
		void Shutdown();

		void Write(int target, const char *msg, ...);
		void Write(int target, unsigned long msgID, ...);
	};

} //end namespace

#endif

