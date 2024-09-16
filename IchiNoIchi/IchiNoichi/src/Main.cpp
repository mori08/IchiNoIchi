#include <IchiNoIchi/MyLibrary.hpp>
#include <IchiNoIchi/Config.hpp>

void Main()
{
	IchiNoIchi::registerResourceAndAsset();
	IchiNoIchi::Config::load();

	while (System::Update())
	{
		IchiNoIchi::Config::reloadOnKeyR();
	}
}
