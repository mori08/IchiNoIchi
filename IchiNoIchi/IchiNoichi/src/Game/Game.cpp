#include <IchiNoIchi/Game/Game.hpp>
#include <IchiNoIchi/MyLibrary.hpp>
#include <IchiNoIchi/Game/SelectingChapterController.hpp>
#include <IchiNoIchi/Game/TitleController.hpp>

namespace IchiNoIchi
{
	Game::Game()
	{
		m_shareData.control =
		{
			pushCtrlr<TitleController>()
		};
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

		for (const auto& stackOperation : m_shareData.control)
		{
			stackOperation(m_controller, m_objectMap, m_shareData);
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
