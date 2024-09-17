#include <IchiNoIchi/Config.hpp>
#include <IchiNoIchi/MyLibrary.hpp>

namespace IchiNoIchi
{
	TOMLValue Config::s_toml;

	size_t Config::s_loadNum = 0;

	Config::Config()
		: Config(U"", U"")
	{
	}

	Config::Config(StringView classKey)
		: Config(classKey, U"")
	{
	}

	Config::Config(StringView classKey, StringView tableKey)
		: m_classKey(classKey)
		, m_tableKey(tableKey)
		, m_baseKey(
			U""
			+ (m_classKey.empty() ? U"" : classKey + U".")
			+ (m_tableKey.empty() ? U"" : tableKey + U".")
		)
	{
	}

	void Config::load()
	{
		++s_loadNum;
		s_toml = TOMLReader(assetPath(U"data/config.toml"));
	}

	void Config::reloadOnKeyR()
	{
#ifdef _DEBUG
		if (KeyR.down())
		{
			load();
		}
#endif // _DEBUG
	}

	Config Config::addTableConfig(StringView tableKey)
	{
		return Config(
			m_classKey,
			(m_tableKey.empty() ? U"" : m_tableKey + U".") + tableKey
		);
	}
}
