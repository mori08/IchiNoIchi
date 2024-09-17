#pragma once

namespace IchiNoIchi
{
	// 白 #F0F0F0
	constexpr Color MyWhite(0xF0);

	// 黒 #0F0F0F
	constexpr Color MyBlack(0x0F);

	/// @brief ディレクトリ内の全リソース・アセットの登録
	void registerResourceAndAsset();

	/// @brief ビルドごとの参照するパスを取得
	/// @param assetPath assetディレクトリからの相対パス
	FilePath assetPath(const FilePath& assetPath);

	/// @brief 長方形内にある格子点のリストの取得
	/// @param rect 長方形
	/// @return 格子点のリスト
	Array<Point> getGridPoint(const Rect& rect);

	/// @brief 指定した頻度でランダムに1を出力
	/// @param frequency 頻度(回/s)
	/// @return ランダムで 1 or 0
	/// @remarks
	/// 頻度がフレームレートを超えることは想定していない
	int32 randomFrequency(double frequency);

	/// @brief 内分点を使った値の変更
	/// @param x 変更したい値
	/// @param a 目的地
	/// @param r 内分比(/s) （0.0 ~ 1.0 で指定）
	/// @remark
	/// 1秒後にxとaの距離がr倍になるように値を変更するため、
	/// r が小さいほど値は速く変化する
	template<typename TYPE_X, typename TYPE_A>
	void internalDividingPoint(TYPE_X& x, const TYPE_A& a, double r)
	{
		r = Pow(r, Scene::DeltaTime()); x = r * x + (1 - r) * a;
	}
}


