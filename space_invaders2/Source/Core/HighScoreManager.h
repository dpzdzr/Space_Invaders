#ifndef HIGHSCOREMANAGER_H
#define HIGHSCOREMANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

struct ScoreEntry
{
    std::string userName;
    int score;

    ScoreEntry(std::string userName, int score)
        : userName(userName), score(score) {}
    bool operator<(const ScoreEntry &other) const { return score < other.score; }
};

class HighScoreManager
{
private:
    // Variables
    std::vector<ScoreEntry> highScores;
    std::string fileName;

    // Functions
    void initVariables();
    void initHighScores();
    void initFileName();

public:
    HighScoreManager();
    ~HighScoreManager();
    void addScore(std::string userName, int score);
    void saveToFile();
    void loadFromFile();
    std::vector<ScoreEntry> &getHighScores() { return highScores; }  
};

#endif