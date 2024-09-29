﻿#include <IchiNoIchi/Game/TitleController.hpp>
#include <IchiNoIchi/Game/TitleLogoObject.hpp>

namespace IchiNoIchi
{
	void TitleController::onAfterPush(Object::Map& objectMap, ShareData& shareData)
	{
		objectMap[U"TitleLogo"] = std::make_shared<TitleLogoObject>();
		shareData.blockDrawer.setEnv(U"Click");
	}

	void TitleController::control(Object::Map& objectMap, ShareData& shareData)
	{
		objectMap[U"TitleLogo"]->act(Object::ActParam(), shareData);
	}

	void TitleController::onBeforePop(Object::Map& objectMap, ShareData& shareData)
	{
		objectMap.erase(U"TitleLogo");
	}
}
