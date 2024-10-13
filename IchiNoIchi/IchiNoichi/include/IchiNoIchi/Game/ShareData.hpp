#pragma once
#include<IchiNoIchi/DividingBlockDrawer.hpp>
#include<IchiNoIchi/RecordSet.hpp>

namespace IchiNoIchi
{
	/// @brief m_controllerへの操作
	enum class ControlStack
	{
		POP,     // 先頭を取り出す
		CLEAR,   // 全て取り出す
		TITLE,   // タイトル画面
		CHAPTER, // 章選択画面
	};

	/// @brief オブジェクト間で共有するデータ置き場
	class ShareData
	{
	public:

		// ブロックごとに不透明度を変更・更新し、画像を描画
		DividingBlockDrawer blockDrawer;

		// m_controllerへの操作
		std::list<ControlStack> control;

		// セーブデータ
		RecordSet recordSet;

	};
}
