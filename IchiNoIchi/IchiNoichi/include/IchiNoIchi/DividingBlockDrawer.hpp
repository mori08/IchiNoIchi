#pragma once

namespace IchiNoIchi
{
	/// @brief ブロックごとに不透明度を変更・更新し、画像を描画
	class DividingBlockDrawer
	{
	public:

		DividingBlockDrawer();

		/// @brief 各ブロックの不透明度の更新
		void updateBlockAlpha();

		/// @brief 指定した座標のブロックの不透明度を変更する
		/// @param pos 座標
		/// @param alpha 不透明度
		void setAlpha(const Vec2& pos, double alpha);

		/// @brief 全ブロックの不透明度を変更する
		/// @param alpha 不透明度
		void setAlpha(double alpha);

		/// @brief ブロックの不透明度を変更するためのパラメータ変更
		/// @param key Configのテーブル名
		void setEnv(const String& key);

		/// @brief レンダーテクスチャを各ブロックごとに設定した不透明度で描画
		/// @param renderTexture 描画するレンダーテクスチャ
		void draw(const MSRenderTexture& renderTexture) const;

	private:

		// ブロックの１辺の長さ
		static constexpr int32 BLOCK_LENGTH = 20;

		// 横方向のブロック数
		static constexpr int32 WIDTH = 800 / BLOCK_LENGTH;

		// 縦方向のブロック数
		static constexpr int32 HEIGHT = 600 / BLOCK_LENGTH;

		// 各ブロック描画の不透明度を登録するImage
		Grid<double> m_alphaMap;

		// m_alphaMapをこのImageに近づける
		Grid<double> m_goalAlphaMap;

		// 枠外の不透明度
		double m_outsideAlpha;

		// m_goalAlpha更新の頻度
		double m_goalUpdateFrequency;

		// 不透明度を上げる度合（内分比）
		double m_upAlphaRate;

		// 不透明度を下げる度合（内分比）
		double m_downAlphaRate;

		// 不透明度を表した画像
		DynamicTexture m_alphaTexture;
	};
}
