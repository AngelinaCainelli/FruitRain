#ifndef HIGHSCORESCENE_H
#define HIGHSCORESCENE_H
#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "HighScoreManagement.h"

class HighScoreScene:public Scene {
public:
	HighScoreScene(RenderWindow &w, HighScoreManagement *hs);
	~HighScoreScene();
	void update(Game &game) override;
	void draw() override;
private:
	Music music;
	Text title;
	Font font;
	Texture hsBgTex;
	Sprite hsBgSpr;
	HighScoreManagement* hs;
	vector<Text> v;
	
};

#endif

