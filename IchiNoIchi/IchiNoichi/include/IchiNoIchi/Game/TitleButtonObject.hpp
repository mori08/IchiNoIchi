#pragma once
#include <IchiNoIchi/Game/Object.hpp>

namespace IchiNoIchi
{
	class TitleButtonObject : public Object
	{
	public:

		void act(const ActParam& actParam, ShareData& shareData) override;

		void draw1stLayer() const override;

	private:

		// 選択中のボタン名、未選択のときは none
		Optional<String> m_selected;

	};
}
