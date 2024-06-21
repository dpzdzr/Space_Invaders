#include "HighScoreManager.h"

void HighScoreManager::initVariables()
{
}

void HighScoreManager::initHighScores()
{
}

void HighScoreManager::initFileName()
{
}

HighScoreManager::HighScoreManager()
{
}

HighScoreManager::~HighScoreManager()
{
}

void HighScoreManager::addScore(std::string userName, int score)
{
    highScores.push_back(ScoreEntry(userName, score));
}

void HighScoreManager::saveToFile()
{
    std::ofstream ofs("HighScore.txt");

    if (ofs.is_open())
    {
        for (auto &score : highScores)
        {
            ofs << score.userName << " " << score.score << "\n";
        }
    }

    ofs.close();
}
