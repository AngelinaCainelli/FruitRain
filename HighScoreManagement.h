#ifndef HIGHSCOREMANAGEMENT_H
#define HIGHSCOREMANAGEMENT_H
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Score{
	int points, comboMax;
	char name[10];
	
	
};

inline bool operator<(Score &s1,Score &s2){
	if(s1.points<s2.points) return true;
	return false;}

class HighScoreManagement {
public:
	HighScoreManagement();
	~HighScoreManagement();
	void openFile();
	void createFile();
	void saveScore();
	void setScore(int p, int c);
	void setUsername(string name);
	string getScore(int pos);
	void readScores();
private:
	vector<Score> scores;
	string nameFile;
	Score scoreAux;
	ifstream fileRead;
	ofstream fileWrite;
	
};

#endif

