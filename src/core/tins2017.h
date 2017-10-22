
#pragma once

#include <memory>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include <alligator/game/game.h>

#include "screen/gameplayscreen.h"

class Tins2017 : public Game {

public:

    Tins2017 ( int sw, int sh );
    virtual ~Tins2017();

	int create( int argc, char** argv ) override ;
	void dispose() override ;

    std::shared_ptr<GameplayScreen> m_gameplayScreen;

	ALLEGRO_FONT* m_font = nullptr;
	ALLEGRO_FONT* m_fontBig = nullptr;


};

