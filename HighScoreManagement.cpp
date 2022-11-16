#include "HighScoreManagement.h"
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

HighScoreManagement::HighScoreManagement() {
	//Constructor
	scores.resize(10);
	nameFile="Highscores/Highscores.dat";
	
	openFile();
	
}

HighScoreManagement::~HighScoreManagement() {
	
}

void HighScoreManagement::setScore(int p, int c){
	scoreAux.points=p;
	scoreAux.comboMax=c;
}

void HighScoreManagement::setUsername(string username){
	strcpy(scoreAux.name,username.c_str());
}

string HighScoreManagement::getScore(int pos){
	//Retorna string con los datos
	string s;
	stringstream aux;
	aux<<"Name: "<<scores[pos].name<<"\nPoints: "<<scores[pos].points<<"\nCombo: "<<scores[pos].comboMax;
	s=aux.str();
	return s;
}

void HighScoreManagement::openFile(){
	//Abre el archivo binario, si no existe lo crea, y guarda los puntajes en un vector
	fileRead.open(nameFile, ios::binary|ios::ate);
	if(!fileRead.is_open()){
		cerr<<"Error: no se pudo abrir el archivo"<<endl;
		createFile();
		openFile();
		return;
	}
	readScores();
	fileRead.close();
}

void HighScoreManagement::createFile(){
	//Crea el archivo binario
	fileWrite.open(nameFile, ios::binary|ios::trunc);
	fileWrite.seekp(0);
	string name="Default";
	strcpy(scoreAux.name,name.c_str());
	scoreAux.points=0;
	scoreAux.comboMax=0;
	
	
	for(unsigned int i=0; i<scores.size(); i++) {
		fileWrite.write(reinterpret_cast<char*> (&scoreAux), sizeof(scoreAux));
	}
	fileWrite.close();
}

void HighScoreManagement::saveScore(){
	//Guarda los datos en el archivo
	scores.push_back(scoreAux);
	sort(scores.begin(),scores.end());
	reverse(scores.begin(), scores.end());
	scores.pop_back();
	
	fileWrite.open(nameFile, ios::binary);
	if(!fileWrite.is_open()) {
		cerr << "Error: no se pudo abrir el archivo" << endl;
		return;
	}
	fileWrite.seekp(0);
	for(unsigned int i=0; i<scores.size(); i++) {
		fileWrite.write(reinterpret_cast<char*>(&scores[i]),sizeof(scores[i]));
	}
	fileWrite.close();
	
	
}

void HighScoreManagement::readScores(){
	//Carga los datos al vector de Scores
	int tamanio=fileRead.tellg();
	int cantidad=tamanio/sizeof(Score);
	
	fileRead.seekg(0);
	
	Score aux;
	if(cantidad!=0){
		for(unsigned i=0;i<scores.size();i++){
			fileRead.read(reinterpret_cast<char*>(&aux), sizeof(aux));
			scores[i]=aux;
		}
	}

}
