#include <IchiNoIchi/Config.hpp>
#include <IchiNoIchi/Game/TitleButtonObject.hpp>
#include <IchiNoIchi/MyLibrary.hpp>

namespace
{
	IchiNoIchi::Config config(U"TitleButtonObject");
}

namespace IchiNoIchi
{
	void TitleButtonObject::act(const ActParam&, ShareData& shareData)
	{
		if (config.get<Rect>(U"startRect").mouseOver())
		{
			if (!m_selected) { AudioAsset(U"select").playOneShot(); }
			m_selected = U"startRect";

			if (MouseL.down())
			{
				// 決定音
				AudioAsset(U"push").playOneShot();
				shareData.blockDrawer.setAlpha(Cursor::PosF(), 1.0);
				shareData.control = ControllerList{ ControlStack::CHAPTER };
			}
		}
		else if (config.get<Rect>(U"exitRect").mouseOver())
		{
			if (!m_selected) { AudioAsset(U"select").playOneShot(); }
			m_selected = U"exitRect";

			if (MouseL.down())
			{
				System::Exit();
			}
		}
		else
		{
			m_selected = none;
		}
	}

	void TitleButtonObject::draw1stLayer() const
	{
		const String& fontName = config.get<String>(U"font");
		FontAsset(fontName)(U"Start").drawAt(config.get<Rect>(U"startRect").center(), MyBlack);
		FontAsset(fontName)(U"Exit").drawAt(config.get<Rect>(U"exitRect").center(), MyBlack);

		if (m_selected)
		{
			config.get<Rect>(m_selected.value()).drawFrame(
				config.get<double>(U"selectedThickness"),
				MyBlack
			);
		}
	}
}
