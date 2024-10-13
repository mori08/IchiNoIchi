#include <IchiNoIchi/Config.hpp>
#include <IchiNoIchi/Game/SelectingChapterObject.hpp>
#include <IchiNoIchi/MyLibrary.hpp>

namespace
{
	IchiNoIchi::Config config(U"SelectingChapterObject");
}

namespace IchiNoIchi
{
	SelectingChapterObject::SelectingChapterObject()
		: m_selectingCircle(0, 0, 0)
	{
	}

	void SelectingChapterObject::act(const ActParam& actParam, ShareData& shareData)
	{
		if (actParam.count(U"setting"))
		{
			// 各章の状態の設定
			setChapterState(shareData);
			return;
		}

		for (const String& chapter : config.get<Array<String>>(U"chapterList"))
		{
			Config configChapter = config.addTableConfig(chapter);
			Rect chapterRect(
				configChapter.get<Point>(U"pos") * config.get<int32>(U"rectSize"),
				config.get<int32>(U"rectSize")
			);

			if (chapterRect.mouseOver())
			{
				m_selectingCircle.center = chapterRect.center();
				internalDividingPoint(
					m_selectingCircle.r,
					config.get<double>(U"radius"),
					config.get<double>(U"radiusRate")
				);
				return;
			}
		}

		m_selectingCircle.r = 0;
	}

	void SelectingChapterObject::draw2ndLayer() const
	{
		std::unordered_map<ChapterState, Color> STATE_COLOR{
			{ ChapterState::DONE, Color(MyWhite, config.get<uint8>(U"doneAlpha"))},
			{ ChapterState::NEW,  Color(MyWhite, config.get<uint8>(U"newAlpha"))},
			{ ChapterState::LOCK, Color(MyWhite, config.get<uint8>(U"lockAlpha"))},
		};

		m_selectingCircle.drawShadow(
			Vec2::Zero(),
			config.get<double>(U"radiusShadowBlur") * m_selectingCircle.r,
			0.0,
			MyWhite
		);

		for (const String& chapter : config.get<Array<String>>(U"chapterList"))
		{
			Config configChapter = config.addTableConfig(chapter);
			Rect(
				configChapter.get<Point>(U"pos") * config.get<int32>(U"rectSize"),
				config.get<int32>(U"rectSize")
			).draw(STATE_COLOR.at(m_chapterStateMap.at(chapter)));
		}
	}

	void SelectingChapterObject::draw3rdLayer() const
	{
		for (const String& chapter : config.get<Array<String>>(U"chapterList"))
		{
			Config configChapter = config.addTableConfig(chapter);
			Rect rect(
				configChapter.get<Point>(U"pos") * config.get<int32>(U"rectSize"),
				config.get<int32>(U"rectSize")
			);
			if (rect.mouseOver())
			{
				rect.drawFrame(
					config.get<double>(U"frameThickness"),
					MyBlack
				);
				FontAsset(U"10")(
					configChapter.get<String>(U"title")
				).drawAt(config.get<Vec2>(U"titleOffset") + rect.center(), MyBlack);
			}
		}
	}

	void SelectingChapterObject::setChapterState(const ShareData& shareData)
	{
		for (const String& chapter : config.get<Array<String>>(U"chapterList"))
		{
			// クリア済み
			if (shareData.recordSet.getRecord(chapter))
			{
				m_chapterStateMap[chapter] = ChapterState::DONE;
				continue;
			}

			Config configChapter = config.addTableConfig(chapter);
			ChapterState state = ChapterState::NEW;
			for (const String required : configChapter.get<Array<String>>(U"required"))
			{
				if (!shareData.recordSet.getRecord(required))
				{
					state = ChapterState::LOCK; // 開放条件の内一つでも未クリアなら未開放
					break;
				}
			}
			m_chapterStateMap[chapter] = state;
		}
	}
}
