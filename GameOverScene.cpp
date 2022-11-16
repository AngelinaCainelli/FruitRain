#include "GameOverScene.h"
#include <string>
#include "Menu.h"
using namespace std;

GameOverScene::GameOverScene(RenderWindow& w, HighScoreManagement* hs)  : input(inputFont,30,Color(255,255,255)) {
	//Constructor
	this->w = &w;
	inputFont.loadFromFile("Assets/Fonts/ARCADECLASSIC.ttf");
	this->hs=hs;
	
	input.setMaxChars(10);
	input.setSingleWord(true);
	input.setPosition(380,470);
	
	insertName.setFont(inputFont);
	string s1="Enter  name ";
	insertName.setString(s1);
	insertName.setPosition(200,470);
	
	font.loadFromFile("Assets/Fonts/Vintagio Classico.ttf");
	string s="Press ENTER to continue";
	continueText.setFont(font);
	continueText.setString(s);
	continueText.setPosition(200,550);
	
	GameOver.loadFromFile("Assets/Images/GameOver.png");
	gameOver.setTexture(GameOver);
	gameOver.setScale(0.7f,0.7f);
	gameOver.setPosition(200,150);
	
	
	
}

GameOverScene::~GameOverScene() {
	
}

void GameOverScene::update(Game &game){
	//Si se suelta el boton Return, se guarda el puntaje y vuelve al menu
	if((ev.type == Event::KeyReleased) && (ev.key.code == Keyboard::Return)){
		this->hs->setUsername(input.getValue());
		this->hs->saveScore();
		game.setScene(new Menu(*w,hs));
	}
	input.update();
}

void GameOverScene::draw(){
	this->w->draw(this->gameOver);
	this->w->draw(this->continueText);
	this->w->draw(this->insertName);
	w->draw(input);
}

void GameOverScene::processEvent(Event &ev){
	this->ev=ev;
	this->input.processEvent(ev);
}
