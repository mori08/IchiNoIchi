#include <IchiNoIchi/Game/SelectingChapterController.hpp>
#include <IchiNoIchi/Game/SelectingChapterObject.hpp>

namespace IchiNoIchi
{
	void SelectingChapterController::onAfterPush(Object::Map& objectMap, ShareData& shareData)
	{
		objectMap[U"Chapter"] = std::make_shared<SelectingChapterObject>();
		objectMap[U"Chapter"]->act(Object::ActParam{ {U"setting", U""} }, shareData);
		shareData.blockDrawer.setEnv(U"BlackIn");
	}

	void SelectingChapterController::control(Object::Map& objectMap, ShareData& shareData)
	{
		objectMap[U"Chapter"]->act(Object::ActParam(), shareData);
	}

	void SelectingChapterController::onBeforePop(Object::Map& objectMap, ShareData&)
	{
		objectMap.erase(U"Chapter");
	}
}
