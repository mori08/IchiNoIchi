#pragma once
#include <IchiNoIchi/Game/Object.hpp>

namespace IchiNoIchi
{
	/// @brief タイトル画面で使用
	/// ロゴの表示と雨の演出
	class TitleLogoObject : public Object
	{
	public:

		void act(const ActParam& actParam, ShareData& shareData) override;

		void draw1stLayer() const override;

		void draw2ndLayer() const override;

	private:

		// 雨演出用（雨の着地点、高さ）
		std::list<std::pair<Vec2, double>> m_rainList;

	};
}
