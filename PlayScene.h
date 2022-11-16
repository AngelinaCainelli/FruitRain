#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include "Scene.h"
#include "Game.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Player.h"
#include "Fruit.h"
#include <vector>
#include "Heart.h"
#include "Bomb.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Audio/Music.hpp>
#include "HighScoreManagement.h"
#include <list>
using namespace std;
class Scene;

class PlayScene:public Scene{
public:
	PlayScene(RenderWindow& w, HighScoreManagement* hs);
	~PlayScene();
	void update(Game &game) override;
	void draw() override;
	
private:
	void checkDifficulty();
	void spawnFruit();
	void spawnHeart();
	void spawnBomb();
	void updateFruit();
	void updateBomb();
	void updateHeart();
	void updateGUI();
	void getsDamaged(Bomb& bomb);
	void getsHealed(Heart& heart);
	
	Texture texBackground;
	Sprite spBackground;
	
	//Player
	Player* player;
	int combo;
	int comboMax;
	
	
	//Fruits
	float spawnTimer;
	float spawnTimerMax;
	Texture vFruitTex[3];
	list<Fruit*> vFruit;
	
	//Extras
	Texture heartTex;
	list<Heart*> vHeart;
	Texture bombTex;
	list<Bomb*> vBomb;
	float spawnTimerHeart;
	float spawnTimerBomb;
	
	//Sound
	SoundBuffer bufferCatch;
	SoundBuffer bufferHit;
	Sound Catch;
	Sound charHit;
	
	//Music
	Music music;
	
	//GUI
	Font font;
	Text pointsText;
	Text comboText;
	RectangleShape lifeBar;
	RectangleShape lifeBarMax;
	HighScoreManagement* hs;
	
	int points;
	int difficulty;
	float speedMult;
	float spawnTimerMult;
};

#endif

