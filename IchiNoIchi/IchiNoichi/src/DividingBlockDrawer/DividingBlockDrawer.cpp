#include <IchiNoIchi/DividingBlockDrawer.hpp>
#include <IchiNoIchi/Config.hpp>
#include <IchiNoIchi/MyLibrary.hpp>

namespace
{
	IchiNoIchi::Config config(U"DividingBlockDrawer");
}

namespace IchiNoIchi
{
	DividingBlockDrawer::DividingBlockDrawer()
		: m_alphaMap(WIDTH, HEIGHT, 0)
		, m_goalAlphaMap(WIDTH, HEIGHT, 0)
		, m_alphaTexture(Image(BLOCK_LENGTH*Point(WIDTH, HEIGHT)))
	{
		setEnv(U"Default");
	}

	void DividingBlockDrawer::updateBlockAlpha()
	{
		static const Array<Point> ALL_BLOCK = getGridPoint(Rect(WIDTH - 1, HEIGHT - 1));
		const Array<Point>& offset = config.get<Array<Point>>(U"offset");

		// 隣接ブロックの色を m_goalAlphaImage にセット
		for (const Point& block : ALL_BLOCK)
		{
			if (!randomFrequency(m_goalUpdateFrequency)) { continue; }

			const Point neighbor = block + offset[Random(offset.size()-1)];

			m_goalAlphaMap[block]
				= (neighbor.x >= 0 && neighbor.y >= 0 && neighbor.x < WIDTH && neighbor.y < HEIGHT)
				? m_alphaMap[neighbor]
				: m_outsideAlpha
			;
		}

		// m_alphaImage を m_goalAlphaImage に近づける
		Image image(WIDTH, HEIGHT, Alpha(0));
		for (const Point& block : ALL_BLOCK)
		{
			internalDividingPoint(
				m_alphaMap[block],
				m_goalAlphaMap[block],
				m_goalAlphaMap[block] > m_alphaMap[block] ? m_upAlphaRate : m_downAlphaRate
			);
			image[block].a = uint8(0xFF * m_alphaMap[block]);
		}

		m_alphaTexture.fill(image.scaled(BLOCK_LENGTH, InterpolationAlgorithm::Nearest));
	}

	void DividingBlockDrawer::setAlpha(const Vec2& pos, double alpha)
	{
		if (!Scene::Rect().contains(pos)) { return; }

		const Point block = (pos / BLOCK_LENGTH).asPoint();
		m_alphaMap[block] = m_goalAlphaMap[block] = alpha;
	}

	void DividingBlockDrawer::setAlpha(double alpha)
	{
		for (double block : m_alphaMap) { block = alpha; }
		for (double block : m_goalAlphaMap) { block = alpha; }
	}

	void DividingBlockDrawer::setEnv(const String& key)
	{
		const Config config_env = config.addTableConfig(key);

		m_outsideAlpha        = config_env.get<double>(U"outsideAlpha");
		m_goalUpdateFrequency = config_env.get<double>(U"goalUpdateFrequency");
		m_upAlphaRate         = config_env.get<double>(U"upAlphaRate");
		m_downAlphaRate       = config_env.get<double>(U"downAlphaRate");
	}

	void DividingBlockDrawer::draw(const MSRenderTexture& renderTexture) const
	{
		static const PixelShader ps = HLSL{ assetPath(U"shader/DividingBlockDrawer.hlsl"), U"PS"};

		Graphics2D::Flush();
		renderTexture.resolve();

		Graphics2D::SetPSTexture(1, m_alphaTexture);
		{
			const ScopedCustomShader2D shader{ ps };
			renderTexture.draw();
		}
	}
}
