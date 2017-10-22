#pragma once

#include <memory>
#include <allegro5/allegro.h>

#include <alligator/graphics/spritesheet.h>
#include <alligator/graphics/animation.h>
#include <alligator/audio/audiosample.h>
#include <alligator/audio/audiostream.h>

class Assets
{
public:

	// singleton interface
	static Assets* instance;

	static void Initialize();
	static void Dispose();

    Assets()
    {
        notabien_bitmap = al_load_bitmap("assets/bg_notabien.png");
        notahead_bitmap = al_load_bitmap("assets/bg_notahead.png");
        notafever_bitmap = al_load_bitmap("assets/bg_notafever.png");
        notacaca_bitmap = al_load_bitmap("assets/bg_notacaca.png");
        notamuerto_bitmap = al_load_bitmap("assets/bg_notamuerto.png");
        //music = new AudioStream("assets/theme.ogg", ALLEGRO_PLAYMODE_LOOP);
        //win = new AudioSample("assets/heal.ogg");
        //die = new AudioSample("assets/die.ogg");
    }
	~Assets();

    ALLEGRO_BITMAP* notabien_bitmap;
    ALLEGRO_BITMAP* notacaca_bitmap;
    ALLEGRO_BITMAP* notafever_bitmap;
    ALLEGRO_BITMAP* notahead_bitmap;
    ALLEGRO_BITMAP* notamuerto_bitmap;

    AudioStream* music;
    AudioSample* die;
    AudioSample* win;

};
