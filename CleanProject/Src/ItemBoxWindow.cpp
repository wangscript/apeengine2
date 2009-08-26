/*!
	@file
	@author		Albert Semenov
	@date		07/2008
	@module
*/

#include "ItemBoxWindow.h"
//#include "EnginePrerequisites.h"

namespace Nebula
{

	ItemBoxWindow::ItemBoxWindow(const std::string& _layout) : BaseLayout(_layout)
	{
		assignBase(mItemBox, "box_Items");
	}

} // namespace demo
