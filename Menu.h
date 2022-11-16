#ifndef MENU_H
#define MENU_H
#include "Scene.h"
#include <SFML/Graphics.hpp>
//#include "PlayScene.hpp"
#include <vector>
#include <SFML/System/Clock.hpp>
#include "HighScoreManagement.h"
#include <SFML/Audio/Music.hpp>

using namespace std;
using namespace sf;

class Menu:public Scene {
public:
	Menu(RenderWindow &w,HighScoreManagement *hs);
	void update(Game &game) override;
	void draw() override;
	~Menu();
private:
	HighScoreManagement *matchScore;
	Clock clock;
	float time, delay;
	Music menuMusic;
	Text titleText;
	Font titleFont;
	
	Texture bg;
	Texture buttonPlay;
	Texture buttonHS;
	Texture buttonExit;
	vector<Sprite> sprButton;
	Sprite sprBg;
	float PosSelected=315.f;
	float SizeSelected=0.3f;
	float PosDeselected=330.f;
	float SizeDeselected=0.25f;
	int opcion;
};

#endif

