#pragma once

#include <IchiNoIchi/Game/Object.hpp>

namespace IchiNoIchi
{
	/// @brief 章選択画面Object
	class SelectingChapterObject : public Object
	{
	public:

		SelectingChapterObject();

		/// @remark
		/// [U"setting"] = Any : 章の状態を設定
		void act(const ActParam& actParam, ShareData& shareData) override;

		void draw2ndLayer() const override;

		void draw3rdLayer() const override;

	private:

		/// @brief 各章のクリア状況を設定
		void setChapterState(const ShareData& shareData);

		/// @brief 章の状態
		enum class ChapterState
		{
			DONE, // クリア済み
			NEW,  // 未クリア＆開放済み
			LOCK, // 未開放
		};

		// 各章のクリア状況
		std::unordered_map<String, ChapterState> m_chapterStateMap;

		// 章選択時に表示する光の円
		Circle m_selectingCircle;

	};
}
