/*!
	@file
	@author		Albert Semenov
	@date		07/2008
	@module
*/
#ifndef __ITEM_DATA_H__
#define __ITEM_DATA_H__

//#include "EnginePrerequisites.h"

#include <Ogre.h>
#include "ResourceItemInfo.h"
#include "MyGUI_ResourceManager.h"

//#include "IGameComponent.h"
//#include "GameObject.h"

namespace Nebula
{

	//class IGameComponent;
	//class GameObject;

	class ItemData
	{
	public:
		ItemData() :
			count(0),
			mResourceInfo(nullptr),
			mResourceImage(nullptr)
		{
		}

			ItemData(const std::string & _resource, size_t _count, std::string owner) :
			count(_count),
			mResourceInfo(nullptr),
			mResourceImage(nullptr)
		{
			MyGUI::ResourceManager & manager = MyGUI::ResourceManager::getInstance();
			mResourceInfo = manager.getResource(_resource)->castType<ResourceItemInfo>();
			mResourceImage = manager.getResource(mResourceInfo->getItemResourceImage())->castType<MyGUI::ResourceImageSet>();
			mOwnerObject = owner;
		}

		bool isEmpty()
		{
			return mResourceInfo == 0;
		}
		
		std::string getOwnerObjectName() {
			return mOwnerObject;
		}

		void setOwnerObjectName(std::string owner) {
			mOwnerObject = owner;
		}

		bool compare(ItemData * _data)
		{
			return mResourceInfo == _data->mResourceInfo;
		}

		void add(ItemData * _data)
		{
			count += _data->count;
			mResourceInfo = _data->mResourceInfo;
			mResourceImage = _data->mResourceImage;
		}

		void clear()
		{
			mResourceInfo = nullptr;
			mResourceImage = nullptr;
			count = 0;
		}

		size_t getCount() { return count; }
		ResourceItemInfoPtr getInfo() { return mResourceInfo; }
		MyGUI::ResourceImageSetPtr getImage() { return mResourceImage; }

	private:
		size_t count;
		ResourceItemInfoPtr mResourceInfo;
		MyGUI::ResourceImageSetPtr mResourceImage;
		std::string mOwnerObject;

	};

} // namespace demo

#endif // __ITEM_DATA_H__
