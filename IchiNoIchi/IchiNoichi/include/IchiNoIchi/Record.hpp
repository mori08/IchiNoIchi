#pragma once

namespace IchiNoIchi
{
	/// @brief セーブデータ内の値1つを管理
	class Record
	{
	public:

		/// @param digit 桁数
		/// @param defaultValue 初期値
		/// @remark
		/// 0以下やint32に収まらない桁数を設定してはいけない
		/// チェック等はしないので実装者が注意する
		Record(int32 digit, int32 defaultValue);

		/// @brief 初期値で値を更新
		void init();

		/// @brief 値の設定
		/// @param value 値
		void set(int32 value);

		/// @brief 値の取得
		/// @return 値
		int32 get() const;

		/// @brief 暗号化用のリストに値を追加
		/// @param dataList 暗号化用のリスト
		void addRecordToEncryptionList(std::list<int32>& dataList) const;

		/// @brief 復号化用のリストから値を取得
		/// @param dataList 復号化用のリスト
		void setValueFromDecryption(std::list<int32>& dataList);

	private:

		// 桁数
		const int32 m_digit;

		// 最大値
		const int32 m_maxValue;

		// 初期値
		const int32 m_defaultValue;

		// 値
		int32 m_value;

	};
}
