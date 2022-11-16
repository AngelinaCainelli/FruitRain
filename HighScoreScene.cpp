#include "HighScoreScene.h"
#include "Menu.h"
#include "Game.h"
using namespace std;

HighScoreScene::HighScoreScene(RenderWindow &w, HighScoreManagement *hs){
	//Constructor
	this->w= &w;
	this->hs=hs;
	music.openFromFile("Assets/Audio/hsMusic.ogg");
	music.setLoop(true);
	music.setVolume(25);
	music.play();
	
	hsBgTex.loadFromFile("Assets/Images/hsBg.jpg");
	hsBgSpr.setTexture(hsBgTex);
	
	font.loadFromFile("Assets/Fonts/gomarice_game_music_love.ttf");
	title.setFont(font);
	title.setString("HighScores");
	title.setPosition(300.f,10.f);
	v.resize(10);
	for(int i=0;i<v.size()/2;i++) { 
		v[i].setFont(font);
		v[i].setScale(0.8,0.8);
		v[i].setPosition(110,100*(i+1));
	}
	for(int i=v.size()/2;i<v.size();i++) { 
		v[i].setFont(font);
		v[i].setScale(0.8,0.8);
		v[i].setPosition(430,100*(i-4));
	}
}

HighScoreScene::~HighScoreScene() {
	
}

void HighScoreScene::update(Game &game){
	
	//Si se presiona la tecla Escape, se retorna al menu
	if(Keyboard::isKeyPressed(Keyboard::Escape)){
		music.stop();
		game.setScene(new Menu(*w,hs));
	}
	
	//Muestra los puntajes en el menu de puntajes
	string aux;
	for(unsigned i=0;i<v.size();i++) {
		aux = to_string(i+1) + "  " + hs->getScore(i);
		v[i].setString(aux);
	}
}

void HighScoreScene::draw(){
	w->draw(hsBgSpr);
	w->draw(title);
	for(int i=0;i<v.size();i++) { 
		w->draw(v[i]);
	}
}
