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

#ifndef CPP_EVENT_HEADER
#define CPP_EVENT_HEADER

#include "EnginePrerequisites.h"
//#include <map>

namespace Nebula {

	typedef  int CppEventHandler;

	template <typename ReturnT,typename ParamT>
	class EventHandlerBase1
	{
	public:
		virtual ReturnT notify(ParamT param) = 0;
	};

	template <typename ListenerT,typename ReturnT,typename ParamT>
	class EventHandler1 : public EventHandlerBase1<ReturnT,ParamT>
	{
		typedef ReturnT (ListenerT::*PtrMember)(ParamT);
		ListenerT* m_object;
		PtrMember m_member;
		
	public:

		EventHandler1(ListenerT* object, PtrMember member)
			: m_object(object), m_member(member)
		{}

		ReturnT notify(ParamT param)
		{
			return (m_object->*m_member)(param);		
		}	
	};

	template <typename ReturnT,typename ParamT>
	class CppEvent1
	{
		typedef std::map<int,EventHandlerBase1<ReturnT,ParamT> *> HandlersMap;
		HandlersMap m_handlers;
		int m_count;

	public:


		CppEvent1()
			: m_count(0) {}

		template <typename ListenerT>
		CppEventHandler attach(ListenerT* object,ReturnT (ListenerT::*member)(ParamT))
		{
			typedef ReturnT (ListenerT::*PtrMember)(ParamT);	
			m_handlers[m_count] = (new EventHandler1<ListenerT,ReturnT,ParamT>(object,member));
			m_count++;	
			return m_count-1;
		}

		bool detach(CppEventHandler id)
		{
			HandlersMap::iterator it = m_handlers.find(id);

			if(it == m_handlers.end())
				return false;
			
			delete it->second;
			m_handlers.erase(it);				
			return true;
		}

		bool detachAll()
		{
			m_handlers.clear();
			return true;
		}

		ReturnT notify(ParamT param)
		{
			HandlersMap::iterator it = m_handlers.begin();
			for(; it != m_handlers.end(); it++)
			{
				it->second->notify(param);
			}

			return true;
		}
	};

	// do the same for delegates with 2 parameters
	template <typename ReturnT,typename ParamT,typename ParamT1>
	class EventHandlerBase2
	{
	public:
		virtual ReturnT notify(ParamT param,ParamT1 param1) = 0;
	};

	template <typename ListenerT,typename ReturnT,typename ParamT,typename ParamT1>
	class EventHandler2 : public EventHandlerBase2<ReturnT, ParamT, ParamT1>
	{
		typedef ReturnT (ListenerT::*PtrMember)(ParamT,ParamT1);
		ListenerT* m_object;
		PtrMember m_member;
		
	public:

		EventHandler2(ListenerT* object, PtrMember member)
			: m_object(object), m_member(member)
		{}

		ReturnT notify(ParamT param,ParamT1 param1)
		{
			return (m_object->*m_member)(param,param1);		
		}	
	};

	template <typename ReturnT,typename ParamT,typename ParamT1>
	class CppEvent2
	{
		typedef std::map<int,EventHandlerBase2<ReturnT,ParamT,ParamT1> *> HandlersMap;
		HandlersMap m_handlers;
		int m_count;

	public:

		
		CppEvent2()
			: m_count(0) {}

		template <typename ListenerT>
		CppEventHandler attach(ListenerT* object,ReturnT (ListenerT::*member)(ParamT,ParamT1))
		{
			typedef ReturnT (ListenerT::*PtrMember)(ParamT,ParamT1);	
			m_handlers[m_count] = (new EventHandler2<ListenerT,ReturnT,ParamT,ParamT1>(object,member));
			m_count++;	
			return m_count-1;
		}

		bool detach(CppEventHandler id)
		{
			HandlersMap::iterator it = m_handlers.find(id);

			if(it == m_handlers.end())
				return false;
			
			delete it->second;
			m_handlers.erase(it);
			return true;
		}
		bool detachAll()
		{
			m_handlers.clear();
			return true;
		}
		ReturnT notify(ParamT param,ParamT1 param1)
		{
			HandlersMap::iterator it = m_handlers.begin();
			for(; it != m_handlers.end(); it++)
			{
				it->second->notify(param,param1);
			}

			return true;
		}
	};

	// do the same for delegates with 3 parameters
	template <typename ReturnT,typename ParamT,typename ParamT1,typename ParamT2>
	class EventHandlerBase3
	{
	public:
		virtual ReturnT notify(ParamT param,ParamT1 param1,ParamT2 param2) = 0;
	};

	template <typename ListenerT,typename ReturnT,typename ParamT,typename ParamT1,typename ParamT2>
	class EventHandler3 : public EventHandlerBase3<ReturnT,ParamT,ParamT1,ParamT2>
	{
		typedef ReturnT (ListenerT::*PtrMember)(ParamT,ParamT1,ParamT2);
		ListenerT* m_object;
		PtrMember m_member;
		
	public:

		EventHandler3(ListenerT* object, PtrMember member)
			: m_object(object), m_member(member)
		{}

		ReturnT notify(ParamT param,ParamT1 param1,ParamT2 param2)
		{
			return (m_object->*m_member)(param,param1,param2);		
		}	
	};

	template <typename ReturnT,typename ParamT,typename ParamT1,typename ParamT2>
	class CppEvent3
	{
		typedef std::map<int,EventHandlerBase3<ReturnT,ParamT,ParamT1,ParamT2> *> HandlersMap;
		HandlersMap m_handlers;
		int m_count;

	public:

		
		CppEvent3()
			: m_count(0) {}

		template <typename ListenerT>
		CppEventHandler attach(ListenerT* object,ReturnT (ListenerT::*member)(ParamT,ParamT1,ParamT2))
		{
			typedef ReturnT (ListenerT::*PtrMember)(ParamT,ParamT1,ParamT2);	
			m_handlers[m_count] = (new EventHandler3<ListenerT,ReturnT,ParamT,ParamT1,ParamT2>(object,member));
			m_count++;	
			return m_count-1;
		}

		bool detach(CppEventHandler id)
		{
			HandlersMap::iterator it = m_handlers.find(id);

			if(it == m_handlers.end())
				return false;
			
			delete it->second;
			m_handlers.erase(it);
			return true;
		}
		bool detachAll()
		{
			m_handlers.clear();
			return true;
		}
		ReturnT notify(ParamT param,ParamT1 param1,ParamT2 param2)
		{
			HandlersMap::iterator it = m_handlers.begin();
			for(; it != m_handlers.end(); it++)
			{
				it->second->notify(param,param1,param2);
			}

			return true;
		}
	};

}

#endif
