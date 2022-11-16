#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Game.h"
#include "InputBox.h"

using namespace std;
using namespace sf;

class GameOverScene:public Scene {
public:
	GameOverScene(RenderWindow& w, HighScoreManagement* hs);
	~GameOverScene();
	void update(Game &game) override;
	void draw() override;
	void processEvent(Event &ev) override;
private:
	InputText input;
	Font inputFont;
	HighScoreManagement *hs;
	Text insertName;
	Texture GameOver;
	Sprite gameOver;
	Font font;
	Text continueText;
};

#endif

