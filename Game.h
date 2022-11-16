#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include<SFML/Window.hpp>
#include <SFML/System/Clock.hpp>
#include "PlayScene.h"
#include "Scene.h"
#include <SFML/Window/Event.hpp>
#include "HighScoreManagement.h"

using namespace sf;


class Game {
public:
	Game();
	~Game();
	void run();
	void setScene(Scene *nextScene);
	void close();
	
private:
	RenderWindow w;
	Event ev;
	HighScoreManagement *matchScore;
	Scene *scene;
	Scene *nextScene;

	
	void update();
	void draw();
};

#endif

