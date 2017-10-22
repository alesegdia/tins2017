#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <alligator/game/iscreen.h>
#include <alligator/camera/camera.h>
#include <alligator/input/input.h>
#include <alligator/util/rng.h>

#include <memory>
#include <stack>

class Tins2017;

class GameplayScreen : public IScreen
{
public:
    GameplayScreen( Tins2017* game);

    virtual ~GameplayScreen();

	void show();
	void hide();
	void update(double delta);
	void render();

    void resetGame();

private:

    enum class GameState : uint8_t {
        PlayerShit = 0,
        PlayerFever,
        PlayerHeadache,
        PlayerOk,
        PlayerDead
    };

    void setNewIllness();
    int checkCorrectKeyboardIllness();
    bool isIll();
    bool stepTimer();
    void playerHealed();

	Tins2017* m_game;

    GameState m_gameState = GameState::PlayerOk;

    double m_timeToLive = 0;
    int m_score = 0;
    char m_scoreString[8];
    double m_currentPassTime = 1.f;

    double m_previousTime = 0.f;
    double m_deltaTime;
    bool m_justDied = false;

    Camera camera;

    RNG rng;



};

#endif // MENUSCREEN_H
