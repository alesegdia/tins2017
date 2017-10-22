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
        notamuerto_bitmap = al_load_bitmap("assets/bg_notabien.png");
        music = new AudioStream("assets/theme.ogg", ALLEGRO_PLAYMODE_LOOP);
        win = new AudioSample("assets/heal.ogg");
        die = new AudioSample("assets/die.ogg");
        notaSick.load("assets/kuteSick.png", 0.2f, 4, 3, 0, 8);
        notaBien.load("assets/kute.png", 0.08f, 2, 2, 0, 3);
        notaDead.load("assets/notamuerto.png", 0.1f, 1, 1, 0, 0);
        music->play();
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

    struct AnimationEntry
    {
        void load(std::string filename, float duration, int sheetw, int sheeth, int framestart, int frameend)
        {
            this->bitmap = al_load_bitmap(filename.c_str());
            this->sheet.reset(new Spritesheet(sheetw, sheeth, this->bitmap));
            this->anim.reset(new Animation(duration, frameend - framestart + 1));
            this->anim->addFrames(this->sheet->getFrames(framestart, frameend));
        }

        void update(double t)
        {
            data.update(t);
            anim->updateData(data);
        }

        ALLEGRO_BITMAP* bitmap;
        Spritesheet::SharedPtr sheet;
        Animation::SharedPtr anim;
        AnimationData data;
    };

    void update(double dt)
    {
        notaDead.update(dt);
        notaBien.update(dt);
        notaSick.update(dt);
    }

    AnimationEntry notaDead;
    AnimationEntry notaBien;
    AnimationEntry notaSick;



};
