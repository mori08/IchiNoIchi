#pragma once
#include <IchiNoIchi/Game/ShareData.hpp>

namespace IchiNoIchi
{
	/// @brief Gameに置くオブジェクト
	class Object
	{
	public:

		using ActParam = std::unordered_map<String, String>;

		/// @brief オブジェクトへの命令
		/// @param actParam 命令内容
		/// @param shareData Gameに置かれている共有データ
		virtual void act(const ActParam& actParam, ShareData& shareData) = 0;

		/// @brief 一層目の描画
		/// @ramarks #6 参照
		virtual void draw1stLayer() const {}

		/// @brief 二層目の描画
		/// @ramarks #6 参照
		virtual void draw2ndLayer() const {}

		/// @brief 三層目の描画
		/// @ramarks #6 参照
		virtual void draw3rdLayer() const {}

		/// @brief 四層目の描画
		/// @ramarks #6 参照
		virtual void draw4thLayer() const {}

	};
}
