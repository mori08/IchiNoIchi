#include <IchiNoIchi/MyLibrary.hpp>
#include <IchiNoIchi/Config.hpp>
#include <IchiNoIchi/DividingBlockDrawer.hpp>
#include <IchiNoIchi/Game.hpp>

void Main()
{
	Scene::SetBackground(IchiNoIchi::MyWhite);

	IchiNoIchi::registerResourceAndAsset();
	IchiNoIchi::Config::load();

	IchiNoIchi::Game game;

	while (System::Update())
	{
		IchiNoIchi::Config::reloadOnKeyR();

		game.updateAndDraw();
	}
}
