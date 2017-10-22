#include "gameplayscreen.h"
#include "../tins2017.h"
#include "../assets.h"
#include "../gameconstants.h"
#include <allegro5/allegro_primitives.h>
#include <cstdio>

GameplayScreen::GameplayScreen(Tins2017 *game)
    : m_game(game),
      rng(123)
{
    camera.scale(GameConstants::ScaleFactor, GameConstants::ScaleFactor);
}

GameplayScreen::~GameplayScreen()
{

}

void GameplayScreen::show()
{
    playerHealed();
    Assets::instance->update(m_deltaTime);

    //Assets::instance->music->play();
}

void GameplayScreen::hide()
{

}

void GameplayScreen::update(double delta)
{
    Assets::instance->update(m_deltaTime);

    double t = al_get_time();
    m_deltaTime = t - m_previousTime;
    m_previousTime = t;

    if( Input::IsKeyJustPressed(ALLEGRO_KEY_ESCAPE) )
    {
        m_game->close();
    }

    if( isIll() )
    {
        int status = checkCorrectKeyboardIllness();
        if( status == -1 )
        {
            m_gameState = GameState::PlayerDead;
        }
        else if( status == 1 )
        {
            playerHealed();
        }
        else if( status == 0 )
        {
            if( stepTimer() )
            {
                m_gameState = GameState::PlayerDead;
            }
        }
    }
    else if( m_gameState == GameState::PlayerOk )
    {
        m_justDied = true;
        if( stepTimer() )
        {
            setNewIllness();
        }
    }
    else if( m_gameState == GameState::PlayerDead )
    {
        if( m_justDied )
        {
            Assets::instance->die->play();
        }
        m_justDied = false;
        if( Input::IsKeyJustPressed(ALLEGRO_KEY_SPACE) )
        {
            this->resetGame();
        }
    }

}

void GameplayScreen::render()
{
    camera.bind();

    switch(m_gameState)
    {
    case GameState::PlayerFever:
        al_draw_bitmap(Assets::instance->notafever_bitmap, 0, 0, 0);
        break;
    case GameState::PlayerShit:
        al_draw_bitmap(Assets::instance->notacaca_bitmap, 0, 0, 0);
        break;
    case GameState::PlayerHeadache:
        al_draw_bitmap(Assets::instance->notahead_bitmap, 0, 0, 0);
        break;
    case GameState::PlayerOk:
        al_draw_bitmap(Assets::instance->notabien_bitmap, 0, 0, 0);
        break;
    case GameState::PlayerDead:
        al_draw_bitmap(Assets::instance->notamuerto_bitmap, 0, 0, 0);
        al_draw_text(m_game->m_font, al_map_rgba(255, 0, 0, 255), 2, 20, 0, "space = retry");
        Assets::instance->notaDead.data.render(14, 24);
        break;
    }


    if( isIll() )
    {
        float d = 76 * (m_timeToLive / m_currentPassTime);
        al_draw_filled_rectangle(0, 0, d, 1, al_map_rgb(255, 0, 0));
        Assets::instance->notaSick.data.render(3, 10);
    }
    else if( m_gameState == GameState::PlayerOk )
    {
        Assets::instance->notaBien.data.render(3, 10);
    }


    al_draw_text(m_game->m_font, al_map_rgba(0, 0, 0, 255), 2, 0, 0, "Anirameric!");
    al_draw_text(m_game->m_font, al_map_rgba(0, 0, 0, 255), 64, 0, 0, m_scoreString);
}

void GameplayScreen::resetGame()
{
    m_score = 0;
    m_timeToLive = m_currentPassTime;
    m_gameState = GameState::PlayerOk;
}

void GameplayScreen::setNewIllness()
{
    int illness = rng.nextInt(0, 2);
    m_gameState = (GameState)illness;
    m_timeToLive = m_currentPassTime;
}

int GameplayScreen::checkCorrectKeyboardIllness()
{
    bool a_key = Input::IsKeyDown(ALLEGRO_KEY_A);
    bool s_key = Input::IsKeyDown(ALLEGRO_KEY_S);
    bool d_key = Input::IsKeyDown(ALLEGRO_KEY_D);

    switch( m_gameState )
    {
    case GameState::PlayerShit:
        if( s_key || d_key ) return -1;
        else if( a_key ) return 1;
    case GameState::PlayerFever:
        if( a_key || d_key ) return -1;
        else if( s_key ) return 1;
    case GameState::PlayerHeadache:
        if( a_key || s_key ) return -1;
        else if( d_key ) return 1;
    }

    return 0;
}

bool GameplayScreen::isIll()
{
    switch(m_gameState)
    {
    case GameState::PlayerFever:
    case GameState::PlayerHeadache:
    case GameState::PlayerShit:
        return true;
    default:
        return false;
    }
}

bool GameplayScreen::stepTimer()
{
    m_timeToLive -= m_deltaTime;
    return m_timeToLive <= 0;
}

void GameplayScreen::playerHealed()
{
    m_gameState = GameState::PlayerOk;
    m_timeToLive = m_currentPassTime;
    m_score++;
    sprintf(m_scoreString, "%d", m_score);
    Assets::instance->win->play();
}
