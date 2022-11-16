#include "Menu.h"
#include <sstream>
#include <string>
#include "PlayScene.h"
#include "HighScoreScene.h"
#include "HighScoreManagement.h"
using namespace std;
using namespace sf;

Menu::Menu(RenderWindow &w,HighScoreManagement *hs){
	//Constructor
	this->w=&w;
	matchScore=hs;
	
	
	titleFont.loadFromFile("Assets/Fonts/Vintagio Classico.ttf");
	titleText.setFont(titleFont);
	string s="Fruit Rain";
	this->titleText.setString(s);
	this->titleText.setPosition(140,100);
	this->titleText.setScale(3.f,3.f);
	this->titleText.setFillColor(Color::Black);
	this->titleText.setOutlineColor(Color::White);
	this->titleText.setOutlineThickness(2);
	
	menuMusic.openFromFile("Assets/Audio/menuMusic.ogg");
	menuMusic.setLoop(true);
	menuMusic.setVolume(25);
	menuMusic.play();
	
	bg.loadFromFile("Assets/Images/menuBackground.png");
	sprBg.setTexture(bg);
	sprBg.setScale(1.5f,1.5f);
	
	buttonPlay.loadFromFile("Assets/Images/buttonPlay.png");
	buttonHS.loadFromFile("Assets/Images/buttonHS.png");
	buttonExit.loadFromFile("Assets/Images/buttonExit.png");
	sprButton.resize(3);
	
	
	
	sprButton[0].setTexture(buttonPlay);
	sprButton[0].setPosition(PosSelected,300.f);
	sprButton[0].setScale(SizeSelected, SizeSelected);
	sprButton[1].setTexture(buttonHS);
	sprButton[1].setPosition(PosDeselected,380.f);
	sprButton[1].setScale(SizeDeselected,SizeDeselected);
	sprButton[2].setTexture(buttonExit);
	sprButton[2].setPosition(PosDeselected,460.f);
	sprButton[2].setScale(SizeDeselected,SizeDeselected);
	
	opcion = 1;
	
	clock.restart();
	delay = 0.1f;
	time= 0 + delay;
	
}

void Menu::update(Game &game){
	
	//Cambia el boton seleccionado
	sprBg.setPosition(0.f,0.f);
	if(clock.getElapsedTime().asSeconds()>=time){
		switch(opcion){
		case 1:
			if(Keyboard::isKeyPressed(Keyboard::Down)){
				sprButton[0].setPosition(PosDeselected,300.f);
				sprButton[0].setScale(SizeDeselected, SizeDeselected);
				sprButton[1].setPosition(PosSelected, 380.f);
				sprButton[1].setScale(SizeSelected, SizeSelected);
				opcion = 2;
			break;}
		case 2:
			if(Keyboard::isKeyPressed(Keyboard::Down)){
			   sprButton[1].setPosition(PosDeselected,380.f);
			   sprButton[1].setScale(SizeDeselected, SizeDeselected);
			   sprButton[2].setPosition(PosSelected, 460.f);
			   sprButton[2].setScale(SizeSelected, SizeSelected);
			   opcion = 3;
			   
			  }
			break;
		case 3:
			if(Keyboard::isKeyPressed(Keyboard::Down)){
				sprButton[2].setPosition(PosDeselected,460.f);
				sprButton[2].setScale(SizeDeselected, SizeDeselected);
				sprButton[0].setPosition(PosSelected, 300.f);
				sprButton[0].setScale(SizeSelected, SizeSelected);
				opcion = 1;
				
			}
			break;
		}
		
	
	switch(opcion){
	case 1:
		if(Keyboard::isKeyPressed(Keyboard::Up)){
			sprButton[0].setPosition(PosDeselected,300.f);
			sprButton[0].setScale(SizeDeselected, SizeDeselected);
			sprButton[2].setPosition(PosSelected, 460.f);
			sprButton[2].setScale(SizeSelected, SizeSelected);
			opcion = 3;
			break;}
	case 2:
		if(Keyboard::isKeyPressed(Keyboard::Up)){
		  sprButton[1].setPosition(PosDeselected,380.f);
		  sprButton[1].setScale(SizeDeselected, SizeDeselected);
		  sprButton[0].setPosition(PosSelected, 300.f);
		  sprButton[0].setScale(SizeSelected, SizeSelected);
		  opcion = 1;
		  
		 }
		 break;
	case 3:
		if(Keyboard::isKeyPressed(Keyboard::Up)){
			sprButton[2].setPosition(PosDeselected,460.f);
			sprButton[2].setScale(SizeDeselected, SizeDeselected);
			sprButton[1].setPosition(PosSelected, 380.f);
			sprButton[1].setScale(SizeSelected, SizeSelected);
			opcion = 2;
			
		}
		break;
		
	}
	time=clock.getElapsedTime().asSeconds() + delay;
	
	}
	
	//Si se presiona la tecla Return, cambia a la escena correspondiente al boton seleccionado
	if(Keyboard::isKeyPressed(Keyboard::Return) && opcion==1){
		menuMusic.stop();
		game.setScene(new PlayScene(*w,matchScore));
	}
	if(Keyboard::isKeyPressed(Keyboard::Return) && opcion==2){
		menuMusic.stop();
		game.setScene(new HighScoreScene(*w,matchScore));
	}
	if(Keyboard::isKeyPressed(Keyboard::Return) && opcion==3){
		menuMusic.stop();
		game.close();
	}

}

void Menu::draw(){
	w->draw(this->sprBg);
	w->draw(this->titleText);

	for(size_t i=0; i<sprButton.size(); i++){
		w->draw(this->sprButton[i]);
	}
}

Menu::~Menu() {
	
}

