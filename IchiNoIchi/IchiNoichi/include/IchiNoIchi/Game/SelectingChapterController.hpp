#pragma once

#include <IchiNoIchi/Game/Controller.hpp>

namespace IchiNoIchi
{
	/// @brief 章選択画面 Controller
	class SelectingChapterController : public Controller
	{
	public:

		void onAfterPush(Object::Map& objectMap, ShareData& shareData) override;

		void control(Object::Map& objectMap, ShareData& shareData) override;

		void onBeforePop(Object::Map& objectMap, ShareData& shareData) override;

	};
}
