#include "assets.h"
#include <iostream>

Assets* Assets::instance = nullptr;



Assets::~Assets()
{
    al_destroy_bitmap(notabien_bitmap);
    al_destroy_bitmap(notahead_bitmap);
    al_destroy_bitmap(notacaca_bitmap);
    al_destroy_bitmap(notafever_bitmap);
    delete(music);
    delete(die);
    delete(win);
}

void Assets::Initialize()
{
	Assets::instance = new Assets();
}

void Assets::Dispose()
{
	delete instance;
}
