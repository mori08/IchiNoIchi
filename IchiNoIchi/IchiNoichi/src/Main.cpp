#include <IchiNoIchi/MyLibrary.hpp>
#include <IchiNoIchi/Config.hpp>
#include <IchiNoIchi/DividingBlockDrawer.hpp>
#include <IchiNoIchi/Game/Game.hpp>

namespace
{
	IchiNoIchi::Config config_window(U"Window");
}

void Main()
{
	// IchiNoIchi
	IchiNoIchi::registerResourceAndAsset();
	IchiNoIchi::Config::load();
	IchiNoIchi::Game game;

	// System
	System::SetTerminationTriggers(UserAction::CloseButtonClicked);

	// Window
	Window::Resize(config_window.get<Point>(U"size"));
	Window::SetTitle(config_window.get<String>(U"title"));

	// Scene
	Scene::SetBackground(IchiNoIchi::MyWhite);

	while (System::Update())
	{
		IchiNoIchi::Config::reloadOnKeyR();

		game.updateAndDraw();
	}
}
