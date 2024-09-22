#pragma once
#include <IchiNoIchi/Game/ShareData.hpp>
#include <IchiNoIchi/Game/Object.hpp>

namespace IchiNoIchi
{
	/// @brief Main関数に置く
	class Game
	{
	public:

		void updateAndDraw();

	private:

		/// @brief 更新系の処理まとめ
		void update();

		/// @brief 描画系の処理まとめ
		void draw() const;

		// オブジェクト間の共有データ
		ShareData m_shareData;

		// オブジェクトのマップ
		std::map<String, std::shared_ptr<Object>> m_objectMap;

	};
}
