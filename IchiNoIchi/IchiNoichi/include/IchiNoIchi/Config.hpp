#pragma once

namespace IchiNoIchi
{
	/// @brief 設定値
	/// @remark
	/// config.tomlの読込と設定値の取得
	/// 設定値の検索には以下3パラメータを使って "クラス名.(テーブル名.)属性名" を検索する
	class Config
	{
	public:

		/// @brief クラス名、テーブル名を指定せず、そのまま設定名を指定できる
		Config();

		/// @param classKey クラス名
		Config(StringView classKey);

		/// @param classKey クラス名
		/// @param tableKey テーブル名
		Config(StringView classKey, StringView tableKey);

		/// @brief config.tomlの読込
		static void load();

		/// @brief Rキーでconfig.tomlの再読込
		static void reloadOnKeyR();

		/// @brief テーブル名を追加したConfigを作成
		/// @param tableKey 追加のテーブル名
		/// @return Config(m_classKey, m_tableKey + tableKey)
		Config addTableConfig(StringView tableKey);

		/// @brief 設定値の取得
		/// @tparam Type 取得する設定値の型
		/// @param valueKey 属性名
		/// @return 設定値
		template<typename Type>
		const Type& get(const String& valueKey) const;

	private:

		/// @brief s_toml[key]を指定した型へ変換し設定値を取得
		/// @tparam Type 変換先の型
		/// @param key 
		/// @return 設定値
		/// @remark
		/// 基本的には s_toml[key].get<Type>() を返す
		/// これで取得できない型の場合は実装が必要
		template<typename Type>
		Type tomlToValue(const String& key) const;

		// config.toml
		static TOMLValue s_toml;

		// ロード番号
		//  これが関数内の数字と一致しないとき保存された設定値をリセット
		static size_t s_loadNum;

		// クラス名
		//  設定値がないとき親のクラス名も検索する
		const String m_classKey;

		// テーブル名
		//  親の検索時も固定されている
		const String m_tableKey;

		// クラス名+テーブル名
		const String m_baseKey;

	};

	template<typename Type>
	inline const Type& Config::get(const String& valueKey) const
	{
		// 設定値を登録するマップ
		//  登録されている値はそのまま返す（検索の手間を省く）
		//  登録されてない値は検索して登録する
		static std::unordered_map<String , Type> configMap;

#ifdef _DEBUG // 再読込を行うのは Debug のみ

		// この関数内で記録しているロード番号
		//  loadNum != s_loadNum （ロード番号が一致しない）場合、
		//  config.toml読込によってconfigMapに登録した内容が古い可能性がある
		//  リセットして設定値の再検索を行う
		static size_t loadNum = 0;
		if (loadNum != s_loadNum)
		{
			loadNum = s_loadNum;
			configMap.clear();
		}

#endif // _DEBUG

		// 登録された設定値を返す
		const String key = m_baseKey + valueKey;
		if (configMap.count(key))
		{
			return configMap[key];
		}

		// 指定したキーで設定値を取得
		if (!s_toml[key].isEmpty())
		{
			configMap[key] = tomlToValue<Type>(key);
			return configMap[key];
		}

		// 親クラス名で設定値を取得（閉路の確認は行っていない）
		const String parentClassKey = s_toml[m_classKey + U"._parent"].getString();
		if (s_toml[parentClassKey].isTable())
		{
			try
			{
				configMap[key] = Config(parentClassKey, m_tableKey).get<Type>(valueKey);
			}
			catch (Error)
			{
				throw Error(U"(Config) 設定値[" + key + U"]が見つからない");
			}
			return configMap[key];
		}

		throw Error(U"(Config) 設定値[" + key + U"]が見つからない");
	}

	template<typename Type>
	inline Type Config::tomlToValue(const String& key) const
	{
		return s_toml[key].get<Type>();
	}

	template<>
	inline Point Config::tomlToValue(const String& key) const
	{
		return Point(
			s_toml[key][U"x"].get<int32>(),
			s_toml[key][U"y"].get<int32>()
		);
	}

	template<>
	inline Vec2 Config::tomlToValue(const String& key) const
	{
		return Vec2(
			s_toml[key][U"x"].get<double>(),
			s_toml[key][U"y"].get<double>()
		);
	}

	template<>
	inline Rect Config::tomlToValue(const String& key) const
	{
		return Rect(
			s_toml[key][U"x"].get<int32>(),
			s_toml[key][U"y"].get<int32>(),
			s_toml[key][U"w"].get<int32>(),
			s_toml[key][U"h"].get<int32>()
		);
	}

	template<>
	inline ColorF Config::tomlToValue(const String& key) const
	{
		return ColorF(
			s_toml[key][U"rgb"].get<double>(),
			s_toml[key][U"a"].getOr<double>(1.0)
		);
	}

	template<>
	inline Array<String> Config::tomlToValue(const String& key) const
	{
		Array<String> rtn;
		for (const auto& toml : s_toml[key].arrayView())
		{
			rtn << toml.getString();
		}
		return rtn;
	}

	template<>
	inline Array<Point> Config::tomlToValue(const String& key) const
	{
		Array<Point> rtn;
		for (const auto& toml : s_toml[key].tableArrayView())
		{
			rtn << Point(toml[U"x"].get<int32>(), toml[U"y"].get<int32>());
		}
		return rtn;
	}

}
