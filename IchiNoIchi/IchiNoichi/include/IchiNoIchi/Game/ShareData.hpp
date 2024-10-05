#pragma once
#include<IchiNoIchi/DividingBlockDrawer.hpp>
#include<IchiNoIchi/RecordSet.hpp>

namespace IchiNoIchi
{
	/// @brief m_controllerへの操作
	enum class ControlStack
	{
		POP, // 先頭を取り出す
		TITLE, // タイトル画面
	};

	/// @brief オブジェクト間で共有するデータ置き場
	class ShareData
	{
	public:

		// ブロックごとに不透明度を変更・更新し、画像を描画
		DividingBlockDrawer blockDrawer;

		// m_controllerへの操作
		Optional<ControlStack> control;

		// セーブデータ
		RecordSet recordSet;

	};
}
