#pragma once
#include <IchiNoIchi/Game/Object.hpp>
#include <IchiNoIchi/Game/ShareData.hpp>

namespace IchiNoIchi
{
	/// @brief オブジェクトを操作する
	class Controller
	{
	public:

		using Ptr = std::shared_ptr<Controller>;

		using Stack = std::stack<Ptr>;

		/// @brief push後の処理
		/// @param objectMap オブジェクトのマップ
		/// @param shareData オブジェクトの共有データ
		virtual void onAfterPush(Object::Map& objectMap, ShareData& shareData) = 0;

		/// @brief オブジェクトと共有データの更新
		/// @param objectMap オブジェクトのマップ
		/// @param shareData オブジェクトの共有データ
		virtual void control(Object::Map& objectMap, ShareData& shareData) = 0;

		/// @brief pop前の処理
		/// @param objectMap オブジェクトのマップ
		/// @param shareData オブジェクトの共有データ
		virtual void onBeforePop(Object::Map& objectMap, ShareData& shareData) = 0;

	};
}
