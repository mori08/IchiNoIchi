#pragma once
#include <IchiNoIchi/Game/Controller.hpp>

namespace IchiNoIchi
{
	class TitleController : public Controller
	{
	public:

		void onAfterPush(Object::Map& objectMap, ShareData& shareData) override;

		void control(Object::Map& objectMap, ShareData& shareData) override;

		void onBeforePop(Object::Map& objectMap, ShareData& shareData) override;
	};
}
