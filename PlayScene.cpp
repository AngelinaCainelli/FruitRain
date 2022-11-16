#include "PlayScene.h"
#include <sstream>
#include "GameOverScene.h"
#include "Menu.h"
#include <algorithm>
using namespace std;

PlayScene::PlayScene(RenderWindow& w,HighScoreManagement *hs) {
	//Constructor
	
	this->w=&w;
	this->hs = hs;
	
	texBackground.loadFromFile("Assets/Images/background.png");
	spBackground.setTexture(texBackground);
	
	music.openFromFile("Assets/Audio/chocobo.ogg");
	music.setVolume(25);
	music.setLoop(true);
	music.play();
	
	player= new Player();
	lifeBarMax.setSize(Vector2f(200,25));
	lifeBarMax.setFillColor(Color(50,50,50));
	lifeBarMax.setPosition(Vector2f(580,10));
	lifeBar.setSize(Vector2f(200,25));
	lifeBar.setFillColor(Color(200,50,0));
	lifeBar.setPosition(Vector2f(580,10));
	
	vFruitTex[0].loadFromFile("Assets/Images/Strawberry.png");
	vFruitTex[1].loadFromFile("Assets/Images/Watermelon.png");
	vFruitTex[2].loadFromFile("Assets/Images/Orange.png");
	
	heartTex.loadFromFile("Assets/Images/Heart.png");
	bombTex.loadFromFile("Assets/Images/Bomb.png");
	
	comboMax=0;
	combo=0;
	
	spawnTimerMax = 25.f;
	spawnTimer = spawnTimerMax;
	
	srand(time(0));
	
	bufferCatch.loadFromFile("Assets/Audio/catch.wav");
	Catch.setBuffer(bufferCatch);
	Catch.setVolume(25);
	bufferHit.loadFromFile("Assets/Audio/charDeath.wav");
	charHit.setBuffer(bufferHit);
	charHit.setVolume(25);
	
	points=0;
	difficulty=1000;
	speedMult=1;
	spawnTimerMult=1;
	
	font.loadFromFile("Assets/Fonts/ARCADECLASSIC.ttf");
	this->pointsText.setFont(font);
	this->pointsText.setScale(0.8,0.8);
	this->pointsText.setPosition(10,10);
	this->comboText.setFont(font);
	this->comboText.setScale(0.8,0.8);
	this->comboText.setPosition(Vector2f(450,10));
}

PlayScene::~PlayScene() {
	
	delete this->player;
	
	for(auto *fruit:vFruit){
		delete fruit;
	}
	
	for(auto *heart:vHeart){
		delete heart;
	}
	
	for(auto *bomb:vBomb){
		delete bomb;
	}
	
	delete this->hs;
}

void PlayScene::checkDifficulty(){
	//actualiza parametros de velocidad de las frutas por cada 1000 puntos ganados
	if(points>difficulty){
		speedMult+=0.5;
		difficulty+=1000;
		spawnTimerMult+=0.5;
	}
}

void PlayScene::spawnFruit(){
	spawnTimer += 0.5f * spawnTimerMult;
	float posI=(float)(rand()%(w->getSize().x - 30));
	float posF=w->getSize().x - 30.f;
	if(spawnTimer >= spawnTimerMax){
		int option = rand()%3;
		this->vFruit.push_back(new Fruit((posF-posI), -100.f, vFruitTex[option],option, speedMult));
		spawnTimer = 0.f;
	}
}

void PlayScene::spawnHeart(){
	spawnTimerHeart+=0.08;
	float aux=rand()%100;
	float posI=(float)(rand()%(w->getSize().x - 30));
	float posF=w->getSize().x - 30.f;
	if(aux<=20 && spawnTimerHeart>=spawnTimerMax){
		this->vHeart.push_back(new Heart((posF-posI), -100.f, heartTex));
		spawnTimerHeart=0.f;
	}
	
}
void PlayScene::spawnBomb(){
	spawnTimerBomb+=0.3;
	float aux=rand()%100;
	float posI=(float)(rand()%(w->getSize().x - 30));
	float posF=w->getSize().x - 30.f;
	if(aux<=80 && spawnTimerBomb>=spawnTimerMax){
		this->vBomb.push_back(new Bomb((posF-posI), -100.f, bombTex));
		spawnTimerBomb=0.f;
	}
}

void PlayScene::updateFruit(){
	
	for(list<Fruit*>::iterator fruit = vFruit.begin(); fruit!=vFruit.end(); fruit++){
		
		(*fruit)->update();
		
		if((*fruit)->getBounds().top > w->getSize().y){
			//Borra la fruta
			delete *fruit;
			fruit=this->vFruit.erase(fruit);
			combo=0;
		}
		else if((*fruit)->getBounds().intersects(player->getBounds())){
			//borra la fruta y agrega puntos
			points+=(*fruit)->getPoints();
			Catch.play();
			delete *fruit;
			fruit=this->vFruit.erase(fruit);					
			combo+=1;
	}
	}
	
//	unsigned counter=0;
//	for(auto *fruit:this->vFruit){
//		fruit->update();
//		
//		if(fruit->getBounds().top > w->getSize().y){
//			
//			//borra la fruta y resetea el combo
//			delete this->vFruit.at(counter);
//			this->vFruit.erase(this->vFruit.begin() + counter);
//			--counter;
//			combo=0;
//		}
//		else if(fruit->getBounds().intersects(player->getBounds())){
//			
//			//borra la fruta y agrega puntos
//			points+=fruit->getPoints();
//			Catch.play();
//			delete this->vFruit.at(counter);
//			this->vFruit.erase(this->vFruit.begin() + counter);
//			--counter;
//			combo+=1;
//			
//		}
//		
//		++counter;
//	}
}

void PlayScene::updateBomb(){
	
	for(list<Bomb*>::iterator bomb = vBomb.begin(); bomb!=vBomb.end(); bomb++){
		
		(*bomb)->update();
		
		if((*bomb)->getBounds().top > w->getSize().y){
			//borra bomba
			delete *bomb;
			bomb=this->vBomb.erase(bomb);
		}
		else if((*bomb)->getBounds().intersects(player->getBounds())){
			//borra bomba cuando choca con el jugador y le quita hp
			getsDamaged(**bomb);
			charHit.play();
			delete *bomb;
			bomb=this->vBomb.erase(bomb);					
			combo=0;
		}
	}
	
//	int counter=0;
//	for(auto *bomb:this->vBomb){
//		bomb->update();
//		if(bomb->getBounds().top > w->getSize().y){
//			
//			//borra bomba
//			delete this->vBomb.at(counter);
//			this->vBomb.erase(this->vBomb.begin() + counter);
//			--counter;
//		}
//		else if(bomb->getBounds().intersects(player->getBounds())){
//			
//			//borra bomba cuando choca con el jugador
//			charHit.play();
//			getsDamaged(*bomb);
//			delete this->vBomb.at(counter);
//			this->vBomb.erase(this->vBomb.begin() + counter);
//			--counter;
//			combo=0;
//			
//		}
//		++counter;
//	}	
}


void PlayScene::updateHeart(){
	
	for(list<Heart*>::iterator heart = vHeart.begin(); heart!=vHeart.end(); heart++){
		
		(*heart)->update();
		
		if((*heart)->getBounds().top > w->getSize().y){
			//borra corazon
			delete *heart;
			heart=this->vHeart.erase(heart);
		}
		else if((*heart)->getBounds().intersects(player->getBounds())){
			//borra corazon cuando choca con el jugador y le regenera hp
			getsHealed(**heart);
			Catch.play();
			delete *heart;
			heart=this->vHeart.erase(heart);					
		}
	}
	
//	int counter=0;
//	for(auto *heart:this->vHeart){
//		heart->update();
//		if(heart->getBounds().top > w->getSize().y){
//			//borra corazon
//			delete this->vHeart.at(counter);
//			this->vHeart.erase(this->vHeart.begin() + counter);
//			--counter;
//		}
//		else if (heart->getBounds().intersects(player->getBounds())){
//			//borra corazon cuando choca con el jugador y le regenera hp
//			Catch.play();
//			getsHealed(*heart);
//			delete this->vHeart.at(counter);
//			this->vHeart.erase(this->vHeart.begin() + counter);
//			--counter;
//		}
//		++counter;
//	}
}

void PlayScene::updateGUI(){
	//actualiza los puntos y combo
	stringstream ss;
	ss<<"Points   "<<this->points;
	this->pointsText.setString(ss.str());
	
	stringstream ss2;
	ss2<<"Combo "<<this->combo;
	this->comboText.setString(ss2.str());
	
}

void PlayScene::getsDamaged(Bomb& bomb){
	//quita vida al jugador
	this->player->setHp(-bomb.getDamage());
	float hp=this->player->getHp();
	float hpMax=this->player->getHpMax();
	if(hp<=0) {
		hp=0;
		lifeBar.setSize(Vector2f(hp,25)); 
	}
	lifeBar.setSize(Vector2f(hp,25));
}

void PlayScene::getsHealed(Heart& heart){
	//cura al jugador
	if(this->player->getHp()<this->player->getHpMax()) this->player->setHp(heart.getLifePoints());
	float hp=this->player->getHp();
	float hpMax=this->player->getHpMax();
	if(hp>=hpMax){
		this->player->setHp(hpMax-hp);
		lifeBar.setSize(Vector2f(hpMax,25));
	}
	else 	lifeBar.setSize(Vector2f(hp,25));
}

void PlayScene::update(Game &game){
	checkDifficulty();
	//Checkea colision con la ventana
	if(player->getBounds().left<=0.f){
		player->setPos(player->getBounds().width/2, player->getPos().y);
	}
	else if(player->getBounds().left + player->getBounds().width >= w->getSize().x){
		player->setPos(w->getSize().x - player->getBounds().width/2 , player->getPos().y);
	}
	
	//Spawning
	
	
	spawnFruit();
	spawnBomb();
	spawnHeart();
	
	
	player->update();
	
	//cambio de escena si el jugador se queda sin hp
	if(!(this->player->isAlive())){
		music.stop();
		hs->setScore(points,comboMax);
		game.setScene(new GameOverScene(*w,hs));
	};
	
	updateFruit();
	
	//boost de velocidad si el combo es mayor o igual a 10
	if (combo>comboMax) comboMax=combo;
	if(combo >= 10){
		this->player->setSpeed(2);
	}
	else		this->player->setSpeed(1);
	
	
	
	updateHeart();
	updateBomb();
	updateGUI();
	
	//cambio de escena si se presiona la tecla escape
	if(Keyboard::isKeyPressed(Keyboard::Escape)){
		music.stop();
		game.setScene(new Menu(*w,hs));
	};
	
}

void PlayScene::draw(){
	w->draw(spBackground);
	player->draw(*w);
	
	for(auto *fruit:this->vFruit){
		fruit->draw(*w);
	}
	
	for(auto *heart:this->vHeart){
		heart->draw(*w);
	}
	
	for(auto *bomb:this->vBomb){
		bomb->draw(*w);
	}
	w->draw(this->pointsText);
	w->draw(this->lifeBarMax);
	w->draw(this->lifeBar);
	w->draw(this->comboText);
	
}
