#pragma once
#include <IchiNoIchi/Game/ShareData.hpp>
#include <IchiNoIchi/Game/Object.hpp>
#include <IchiNoIchi/Game/Controller.hpp>

namespace IchiNoIchi
{
	/// @brief Main関数に置く
	class Game
	{
	public:

		Game();

		void updateAndDraw();

	private:

		/// @brief 更新系の処理まとめ
		void update();

		/// @brief m_controllerの更新
		void updateController();

		/// @brief 描画系の処理まとめ
		void draw() const;

		// オブジェクト間の共有データ
		ShareData m_shareData;

		// オブジェクトのマップ
		Object::Map m_objectMap;

		// オブジェクトの操作
		Controller::Stack m_controller;

	};
}
