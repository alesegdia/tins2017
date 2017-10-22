#include "tins2017.h"
#include "assets.h"

#include <allegro5/allegro_ttf.h>

Tins2017::Tins2017(int sw, int sh)
	: Game( sw, sh )
{

}

Tins2017::~Tins2017()
{

}

int Tins2017::create(int argc, char **argv)
{
	Assets::Initialize();

    m_gameplayScreen.reset(new GameplayScreen(this));

    setScreen(m_gameplayScreen);

    m_font = al_load_ttf_font("assets/visitor1.ttf", 10, 0);

	return 0;
}

void Tins2017::dispose()
{
	al_destroy_font(m_font);
	al_destroy_font(m_fontBig);

	Assets::Dispose();
}
