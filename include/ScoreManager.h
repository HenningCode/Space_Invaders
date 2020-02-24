//
// Created by Henning Wilmer on 24.02.20.
//

#ifndef SPACE_SCOREMANAGER_H
#define SPACE_SCOREMANAGER_H

#include <vector>
#include <string>


class ScoreManager {
public:
    ScoreManager(int width, int height);

    void SaveNewHighscore(const std::string &name, int score);
    bool CheckIfNewHighscore(int score);
    void Draw();


private:
    void LoadHighscores();
    int m_ScreenWidth;
    int m_ScreenHeight;
    std::vector<std::pair<std::string,int>> m_Highscores;

};


#endif //SPACE_SCOREMANAGER_H
