#include <IchiNoIchi/MyLibrary.hpp>
#include <IchiNoIchi/Config.hpp>
#include <IchiNoIchi/DividingBlockDrawer.hpp>
#include <IchiNoIchi/Game/Game.hpp>

void Main()
{
	// System
	System::SetTerminationTriggers(UserAction::CloseButtonClicked);

	// Scene
	Scene::SetBackground(IchiNoIchi::MyWhite);

	// IchiNoIchi
	IchiNoIchi::registerResourceAndAsset();
	IchiNoIchi::Config::load();
	IchiNoIchi::Game game;

	while (System::Update())
	{
		IchiNoIchi::Config::reloadOnKeyR();

		game.updateAndDraw();
	}
}
