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

#ifndef PROFILER_OUTPUT_HANDLER_H_INCLUDED
#define PROFILER_OUTPUT_HANDLER_H_INCLUDED

#include "EnginePrerequisites.h"

namespace Nebula
{

	class NebulaDllPrivate IProfilerOutputHandler
	{
	public:
		virtual void BeginOutput(float tTotal)=0;
		virtual void Sample(float fMin, float fAvg, float fMax, float tAvg, int callCount, std::string name, int parentCount)=0;
		virtual void EndOutput()=0;
	};

} //end namespace

#endif