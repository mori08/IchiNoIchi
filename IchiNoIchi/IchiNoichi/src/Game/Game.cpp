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
		// TODO 外

		static MSRenderTexture renderTexture(Scene::Size());
		renderTexture.clear(MyBlack);
		{
			const ScopedRenderTarget2D target{ renderTexture };
			// TODO 頭の中
		}
		m_shareData.blockDrawer.draw(renderTexture);

		// TODO UI
	}
}
