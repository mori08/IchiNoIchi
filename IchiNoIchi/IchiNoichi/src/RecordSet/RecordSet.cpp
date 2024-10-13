#include <IchiNoIchi/Config.hpp>
#include <IchiNoIchi/MyLibrary.hpp>
#include <IchiNoIchi/RecordSet.hpp>

namespace
{
	constexpr int32 BASE    = 0x10;        // 暗号化の基準になる値(何進数で暗号化するか)
	constexpr int32 MUL     = BASE - 1;    // 掛け算のときのかける数
	constexpr int32 HALF    = BASE / 2;    // 基準値の半分
	constexpr int32 MOD     = BASE * BASE; // 余りをとるときの割る数 
	constexpr int32 MAX_KEY = MOD - 1;     // 鍵の最大値

	// 暗号文における1データのとる文字数
	constexpr int32 ONE_DATA_LENGTH = 2;

	IchiNoIchi::Config config(U"RecordSet");
}

namespace IchiNoIchi
{
	RecordSet::RecordSet()
	{
		// Recordについてのtomlファイル
		const TOMLReader toml(assetPath(U"data/record.toml"));
		m_totalDigit = 0;

		for (const auto& obj : toml[U"Record"].tableArrayView())
		{
			m_recordMap.try_emplace
			(
				obj[U"name"].getString(),
				std::move(Record(obj[U"digit"].get<int32>(), obj[U"default"].get<int32>()))
			);

			m_totalDigit += obj[U"digit"].get<int32>();
		}
	}

	void RecordSet::init()
	{
		for (auto& record : m_recordMap)
		{
			record.second.init();
		}
	}

	void RecordSet::setDebug()
	{
#ifdef _DEBUG
		const TOMLReader toml(assetPath(U"data/record.toml"));
		m_totalDigit = 0;

		for (const auto& obj : toml[U"Record"].tableArrayView())
		{
			if (obj[U"debug"].isEmpty()) { continue; }

			m_recordMap.at(obj[U"name"].getString()).set(obj[U"debug"].get<int32>());
		}
#endif // _DEBUG
	}

	void RecordSet::decryption()
	{
		// セーブデータの読み込み
		TextReader reader(config.get<String>(U"fileName"));
		if (!reader) { return; } // ファイルがないとき失敗

		// 暗号化された文字列
		Optional<String> textOpt = reader.readLine();
		if (!textOpt) { return; } // ファイルが1行も取得できないときは失敗

		// 復号用のリスト
		std::list<int32> dataList;

		// 文字列 -> 整数値の配列
		for (size_t i = 0; i < textOpt->length(); i += ONE_DATA_LENGTH)
		{
			auto data = ParseIntOpt<int32>(textOpt->substr(i, ONE_DATA_LENGTH), Arg::radix = BASE);
			if (!data)
			{
				return; // 変換できないとき失敗
			}
			dataList.emplace_back(*data);
		}

		// 前の項の値と mod 0x100 で 減算
		int32 previouseOne = 0;
		for (auto& data : dataList)
		{
			const int32 tmp = data;
			data = (data - previouseOne + MOD) % MOD;
			previouseOne = tmp;
		}

		// 先頭・末尾の鍵を削除
		if (*dataList.begin() != *dataList.rbegin())
		{
			return; // 鍵が一致しないとき失敗
		}
		dataList.pop_front();
		dataList.pop_back();

		// サイズ と レコードの合計桁数 が一致しているか確認
		if (dataList.size() != m_totalDigit)
		{
			return; // 一致しないとき失敗
		}

		// 全てを0xFで割る
		for (auto& data : dataList)
		{
			if (data % MUL != 0)
			{
				return; // 割り切れないとき失敗
			}
			data /= MUL;
			if (data <= 0x0 || data > BASE)
			{
				return; // [0x1,0x10]の範囲にないとき失敗
			}
		}

		// 偶数 -> 0
		// 奇数 -> 1
		for (auto& data : dataList)
		{
			data %= 2;
		}

		// レコードに格納
		for (auto& record : m_recordMap)
		{
			record.second.setValueFromDecryption(dataList);
		}
	}

	void RecordSet::encryption() const
	{
		// 暗号用のリスト
		std::list<int32> dataList;

		// 各レコードから 0,1 のリストを追加
		for (const auto& record : m_recordMap)
		{
			record.second.addRecordToEncryptionList(dataList);
		}

		// 0 -> [0x2,0x10]の範囲の偶数
		// 1 -> [0x1,0xF] の範囲の奇数
		for (auto& data : dataList)
		{
			data = 2 * (Random(0x1, HALF)) - data;
		}

		// 全てを0xFかける
		for (auto& data : dataList)
		{
			data *= MUL;
		}

		// 鍵を生成する 
		const int32 key = Random(0x0, MAX_KEY);

		// リストの先頭と末尾に鍵を追加
		dataList.emplace_front(key);
		dataList.emplace_back(key);

		// 前の項の値を mod 0x100 で加算
		int32 previousOne = 0;
		for (auto& data : dataList)
		{
			data = (data + previousOne) % MOD;
			previousOne = data;
		}

		// 整数値の配列 -> 文字列
		String text;
		for (const auto& data : dataList)
		{
			text += Pad(U"{:x}"_fmt(data), { ONE_DATA_LENGTH, U'0' });
		}

		// 暗号化したセーブデータを書き込み
		TextWriter writer(config.get<String>(U"fileName"));
		writer.writeln(text);
	}

	RecordSet& RecordSet::setRecord(const String& name, int32 value)
	{
		if (!m_recordMap.count(name))
		{
			throw Error(U"(RecordSet) レコード[" + name + U"]が見つからない");
		}
		m_recordMap.at(name).set(value);
		return *this;
	}

	int32 RecordSet::getRecord(const String& name) const
	{
		if (!m_recordMap.count(name))
		{
			throw Error(U"(RecordSet) レコード[" + name + U"]が見つからない");
		}
		return m_recordMap.at(name).get();
	}

	void RecordSet::printDebug() const
	{
#ifdef _DEBUG
		for (const auto& record : m_recordMap)
		{
			Print << Pad(ToString(record.second.get()), { 4,U' ' }) + U" < [" + record.first + U"]";
		}
#endif // _DEBUG
	}
}
