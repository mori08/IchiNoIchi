#include <IchiNoIchi/Config.hpp>
#include <IchiNoIchi/Game/TitleLogoObject.hpp>
#include <IchiNoIchi/MyLibrary.hpp>

namespace
{
	IchiNoIchi::Config config(U"TitleLogoObject");
}

namespace IchiNoIchi
{
	void TitleLogoObject::act(const ActParam&, ShareData& shareData)
	{
		if (randomFrequency(config.get<double>(U"rainFrequency")))
		{
			const Vec2 pos = RandomVec2(Scene::Rect());
			const double height = config.get<double>(U"height");
			m_rainList.emplace_back(pos, height);
		}

		for (auto itr = m_rainList.begin(); itr != m_rainList.end();)
		{
			itr->second -= Scene::DeltaTime() * config.get<double>(U"speed");
			if (itr->second < 0)
			{
				shareData.blockDrawer.setAlpha(itr->first, 1);
				itr = m_rainList.erase(itr); continue;
			}
			++itr;
		}
	}

	void TitleLogoObject::draw1stLayer() const
	{
		TextureAsset(U"TitleLogo").drawAt(config.get<Point>(U"pos"));

		for (const auto& rain : m_rainList)
		{
			Line(
				rain.first + Vec2::Up(rain.second),
				rain.first + Vec2::Up(rain.second + config.get<double>(U"length"))
			).draw(config.get<ColorF>(U"color"));
		}
	}

	void TitleLogoObject::draw2ndLayer() const
	{
		TextureAsset(U"TitleLogoBack").drawAt(config.get<Point>(U"pos"));
	}
}
