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

#ifndef PROFILER_H_INCLUDED
#define PROFILER_H_INCLUDED

#define MAX_PROFILER_SAMPLES 50

#include "EnginePrerequisites.h"

namespace Nebula
{

	class IProfilerOutputHandler;
	class CProfileSample;

	class NebulaDllPrivate CProfileSample
	{
	public:
		CProfileSample(std::string sampleName);
		~CProfileSample();

		void Output();

		void ResetSample(std::string sampleName);
		void ResetAll();

		IProfilerOutputHandler *outputHandler;

		bool bProfilerIsRunning;

	protected:
		//index into the array of samples
		int iSampleIndex;
		int iParentIndex;

		inline float GetTime() { 
			//return ((float)SDL_GetTicks())/1000.0f; 
			return 0;
		}

		struct profileSample
		{
			profileSample()
			{
				bIsValid=false; 
				dataCount=0;
				averagePc=minPc=maxPc=-1;
			}

			bool bIsValid;		//whether or not this sample is valid (for use with fixed-size arrays)
			bool bIsOpen;		//is this sample currently being profiled?
			unsigned int callCount;	//number of times this sample has been profiled this frame
			std::string name;	//name of the sample
			
			float startTime;	//starting time on the clock, in seconds
			float totalTime;	//total time recorded across all profiles of this sample
			float childTime;	//total time taken by children of this sample

			int parentCount;	//number of parents this sample has (useful for indenting)

			float averagePc;	//average percentage of game loop time taken up
			float minPc;		//minimum percentage of game loop time taken up
			float maxPc;		//maximum percentage of game loop time taken up
			unsigned long dataCount;//number of percentage values that have been stored
		} samples[MAX_PROFILER_SAMPLES];
		int lastOpenedSample;
		int openSampleCount;
		float rootBegin, rootEnd;
	};


	#ifdef PROFILER
	#define PROFILE(name) CProfileSample _profile_sample(name);
	#else
	#define PROFILE(name)
	#endif

} //end namespace

#endif