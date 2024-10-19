#pragma once
#include <IchiNoIchi/DividingBlockDrawer.hpp>
#include <IchiNoIchi/RecordSet.hpp>

namespace IchiNoIchi
{
	class Object;
	class Controller;
	class ShareData;

	/// @brief Controller::Stackへの操作
	/// @remarks
	/// void(Controller::Stack&, Object::Map&, ShareData&)
	using ControllerOperation = std::function<
		void(
			std::stack<std::shared_ptr<Controller>>&,
			std::unordered_map<String, std::shared_ptr<Object>>&,
			ShareData&
		)
	>;

	/// @brief オブジェクト間で共有するデータ置き場
	class ShareData
	{
	public:

		// ブロックごとに不透明度を変更・更新し、画像を描画
		DividingBlockDrawer blockDrawer;

		// m_controllerへの操作
		std::list<ControllerOperation> control;

		// セーブデータ
		RecordSet recordSet;

	};
}
