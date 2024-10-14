#include <IchiNoIchi/Game/Game.hpp>
#include <IchiNoIchi/MyLibrary.hpp>
#include <IchiNoIchi/Game/SelectingChapterController.hpp>
#include <IchiNoIchi/Game/TitleController.hpp>

namespace IchiNoIchi
{
	Game::Game()
	{
		m_shareData.control = ControllerList{ ControlStack::TITLE };
		m_shareData.recordSet.decryption();
	}

	void Game::updateAndDraw()
	{
		update();
		draw();
	}

	void Game::update()
	{
		updateController();

		m_shareData.blockDrawer.updateBlockAlpha();
	}

	void Game::updateController()
	{
		if (!m_controller.empty())
		{
			m_controller.top()->control(m_objectMap, m_shareData);
		}

		if (m_shareData.control.empty()) { return; }
		for (ControlStack control : m_shareData.control)
		{
			if (control == ControlStack::POP)
			{
				m_controller.top()->onBeforePop(m_objectMap, m_shareData);
				m_controller.pop();
				continue;
			}

			if (control == ControlStack::CLEAR)
			{
				while (!m_controller.empty())
				{
					m_controller.top()->onBeforePop(m_objectMap, m_shareData);
					m_controller.pop();
				}
				continue;
			}

			static std::unordered_map<ControlStack, std::function<Controller::Ptr()>> CREATING_CONTROLLER_MAP
			{
				{ControlStack::TITLE  , []() {return std::make_shared<TitleController>(); }},
				{ControlStack::CHAPTER, []() {return std::make_shared<SelectingChapterController>(); }}
				// TODO: Controllerの派生クラスを作成したときここにも追加する
			};

			if (!CREATING_CONTROLLER_MAP.count(control))
			{
				throw Error(U"(Game) 登録されていないControllerが指定された");
			}

			m_controller.push(CREATING_CONTROLLER_MAP[control]());
			m_controller.top()->onAfterPush(m_objectMap, m_shareData);
		}

		m_shareData.control.clear();
	}

	void Game::draw() const
	{
		for (const auto& object : m_objectMap)
		{
			object.second->draw1stLayer();
		}

		static MSRenderTexture renderTexture(Scene::Size());
		renderTexture.clear(MyBlack);
		{
			const ScopedRenderTarget2D target{ renderTexture };
			for (const auto& object : m_objectMap)
			{
				object.second->draw2ndLayer();
			}

			for (const auto& object : m_objectMap)
			{
				object.second->draw3rdLayer();
			}
		}
		m_shareData.blockDrawer.draw(renderTexture);

		for (const auto& object : m_objectMap)
		{
			object.second->draw4thLayer();
		}
	}
}
