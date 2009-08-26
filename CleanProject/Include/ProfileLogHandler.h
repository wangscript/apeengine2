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

#ifndef _PROFILER_LOG_HANDLER_H
#define _PROFILER_LOG_HANDLER_H

//#include "profiler.h"
#include "EnginePrerequisites.h"

namespace Nebula
{

	class NebulaDllPrivate CProfileLogHandler : public IProfilerOutputHandler  
	{
	public:
		void BeginOutput(float tTime);
		void EndOutput();
		void Sample(float fMin, float fAvg, float fMax, float tAvg, int callCount, std::string name, int parentCount);
	};

} //end namespace

#endif // !defined(AFX_PROFILELOGHANDLER_H__CAD57C2F_2BF7_492C_8ED3_EFE606EF3EAC__INCLUDED_)
