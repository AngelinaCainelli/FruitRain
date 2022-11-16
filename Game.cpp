#include "Game.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include "Menu.h"

using namespace std;

Game::Game() {
	//Constructor
	w.create(VideoMode(800,600),"Fruit Rain");
	w.setFramerateLimit(60);
	matchScore=new HighScoreManagement;
	this->scene=new Menu(w,matchScore);
	this->nextScene=nullptr;
}



Game::~Game(){
	//Destructor
	delete this->scene;
	delete this->nextScene;
	delete this->matchScore;
	
}

void Game::run(){
	
	while(w.isOpen()) {
		while(w.pollEvent(ev)) {
			if(ev.type == Event::Closed)
				w.close();	
			else this->scene->processEvent(ev);
		}
		//Si nextScene no es null, cambia de escena
		if(this->nextScene){
			delete this->scene;
			this->scene=this->nextScene;
			this->nextScene=nullptr;
		}
		update();
		draw();
	}
	
	
}

void Game::setScene(Scene *nextScene){
	
	this->nextScene = nextScene;
	
}

void Game::close(){
	w.close();
}

void Game::update(){
	scene->update(*this);
}
	
void Game::draw(){
	w.clear();
	scene->draw();
	w.display();
}

