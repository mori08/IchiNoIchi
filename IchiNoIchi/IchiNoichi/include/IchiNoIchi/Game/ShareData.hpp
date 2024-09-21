#pragma once
#include<IchiNoIchi/DividingBlockDrawer.hpp>

namespace IchiNoIchi
{
	/// @brief オブジェクト間で共有するデータ置き場
	class ShareData
	{
	public:

		// ブロックごとに不透明度を変更・更新し、画像を描画
		DividingBlockDrawer blockDrawer;

	};
}
