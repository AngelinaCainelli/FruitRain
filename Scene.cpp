#include "Scene.h"

Scene::Scene() {
	
}

Scene::~Scene() {
	
}

void Scene::processEvent(sf::Event &ev){
	this->ev=ev;
}
