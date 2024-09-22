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
		m_shareData.blockDrawer.updateBlockAlpha();
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
