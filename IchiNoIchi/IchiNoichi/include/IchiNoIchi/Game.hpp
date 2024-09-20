#pragma once
#include <IchiNoIchi/DividingBlockDrawer.hpp>

namespace IchiNoIchi
{
	class Game
	{
	public:

		void updateAndDraw();

	private:

		/// @brief 更新系の処理まとめ
		void update();

		/// @brief 描画系の処理まとめ
		void draw() const;

	};
}
