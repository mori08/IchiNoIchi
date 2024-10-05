#pragma once

#include <IchiNoIchi/Record.hpp>

namespace IchiNoIchi
{
	/// <summary>
	/// 複数のRecordを管理し、
	/// 文字列との変換、各Recordの変更/取得を行う
	/// </summary>

	/// @brief 複数のRecordの管理、暗号・復号化
	class RecordSet
	{
	public:

		/// @brief 全Recordを初期値で設定
		RecordSet();

		/// @brief 全Recordを初期値で更新
		void init();

		/// @brief デバッグ用の値でRecordを更新
		void setDebug();

		/// @brief 暗号化されたセーブデータを復号し、各Recordに設定する
		/// @remark 失敗したときはRecordはそのまま
		void decryption();

		/// @brief Recordを暗号化し、セーブデータに保存する
		void encryption() const;

		/// @brief Record値の変更
		/// @param name Record名
		/// @param value 変更後の値
		/// @return *this
		RecordSet& setRecord(const String& name, int32 value);

		/// @brief Record値を取得
		/// @param name Record名
		/// @return Record値
		int32 getRecord(const String& name) const;

		/// @brief デバッグ用のRecord表示
		void printDebug() const;

	private:

		// Recordのマップ
		std::map<String, Record> m_recordMap;

		// 桁の合計値
		int32 m_totalDigit;

	};
}
