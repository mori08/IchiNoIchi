#include <IchiNoIchi/MyLibrary.hpp>
#include <IchiNoIchi/Config.hpp>
#include <IchiNoIchi/DividingBlockDrawer.hpp>

void Main()
{
	Scene::SetBackground(IchiNoIchi::MyWhite);

	IchiNoIchi::registerResourceAndAsset();
	IchiNoIchi::Config::load();

	while (System::Update())
	{
		IchiNoIchi::Config::reloadOnKeyR();
	}
}
