#pragma once

namespace IchiNoIchi
{
	/// @brief ディレクトリ内の全リソース・アセットの登録
	void registerResourceAndAsset();

	/// @brief ビルドごとの参照するパスを取得
	/// @param assetPath assetディレクトリからの相対パス
	FilePath assetPath(const FilePath& assetPath);
}
