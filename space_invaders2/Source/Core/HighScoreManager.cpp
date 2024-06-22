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
    loadFromFile();
}

HighScoreManager::~HighScoreManager()
{
    saveToFile();
}

void HighScoreManager::addScore(std::string userName, int score)
{
    highScores.push_back(ScoreEntry(userName, score));
    std::sort(highScores.begin(), highScores.end(), [](const ScoreEntry &a, const ScoreEntry &b)
              { return a.score > b.score; });
}

void HighScoreManager::saveToFile()
{
    std::ofstream ofs(RESOURCES "HighScore/HighScore.txt");

    if (ofs.is_open())
    {
        for (auto &score : highScores)
        {
            ofs << score.userName << " " << score.score << "\n";
        }
    }

    ofs.close();
}

void HighScoreManager::loadFromFile()
{
    std::ifstream ifs(RESOURCES "HighScore/HighScore.txt");

    if (ifs.is_open())
    {
        std::string userName;
        int score;

        while (ifs >> userName >> score)
        {
            highScores.push_back(ScoreEntry(userName, score));
        }
    }

    ifs.close();
}

void HighScoreManager::clearHighScoreFile()
{
    std::filesystem::resize_file(RESOURCES "HighScore/HighScore.txt", 0);
    highScores.clear();
}