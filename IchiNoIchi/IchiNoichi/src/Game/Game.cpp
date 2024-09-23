#include <IchiNoIchi/Game/Game.hpp>
#include <IchiNoIchi/MyLibrary.hpp>

namespace IchiNoIchi
{
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
		if (m_controller.empty()) { return; }

		m_controller.top()->control(m_objectMap, m_shareData);

		if (!m_shareData.control) { return; }

		if (m_shareData.control.value() == ControlStack::POP)
		{
			m_controller.top()->onBeforePop(m_objectMap, m_shareData);
			m_controller.pop();
			return;
		}

		static std::unordered_map<ControlStack, std::function<Controller::Ptr()>> CREATING_CONTROLLER_MAP
		{
			// TODO: Controllerの派生クラスを作成したときここにも追加する
		};
		m_controller.push(CREATING_CONTROLLER_MAP[m_shareData.control.value()]());
		m_controller.top()->onAfterPush(m_objectMap, m_shareData);
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
