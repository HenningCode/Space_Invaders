//
// Created by Henning Wilmer on 24.02.20.
//

#include "../include/ScoreManager.h"
#include <raylib.h>
#include <iostream>
#include <fstream>
#include <sstream>

ScoreManager::ScoreManager(int width, int height): m_ScreenWidth(width),m_ScreenHeight(height) {
    LoadHighscores();
}

void ScoreManager::SaveNewHighscore(const std::string &name, int score) {
    std::ofstream file;

    for(auto it = m_Highscores.end(); it != m_Highscores.begin(); --it){
        if(it->second > score){
            m_Highscores.insert(it+1,std::make_pair(name,score));
            m_Highscores.pop_back();
            break;
        }
    }

    file.open("Highscores.txt", std::ios::out);

    if(!file.is_open())
        return;
    for(auto &highscore: m_Highscores){
        file << highscore.first << " " << highscore.second << std::endl;
    }
}

bool ScoreManager::CheckIfNewHighscore(int score) {
    return (m_Highscores.end() - 1)->second < score;
}

void ScoreManager::Draw() {
    int i = 1;
    int offset = 40;
    int longest_text = 0;

    for(auto &scores:m_Highscores){
        if(MeasureText(scores.first.c_str(),20) > longest_text)
            longest_text = MeasureText(scores.first.c_str(),20);
    }

    for(auto &scores:m_Highscores){

        DrawText(FormatText("%i. %s",i,scores.first.c_str()), m_ScreenWidth / 2 - longest_text, 20 + ((i - 1) * offset), 20, WHITE);
        DrawText(FormatText("%i",scores.second), m_ScreenWidth / 2 + longest_text, 20 + ((i - 1) * offset), 20, WHITE);
        ++i;
    }
}

void ScoreManager::LoadHighscores() {
    std::ifstream file;
    file.open("Highscores.txt");

    std::string line;
    std::string name;
    int score;


    if(!file.is_open())
        return;
    while(!file.eof()){
        getline(file,line);
        std::stringstream ss(line);
        ss >> name >> score;
        m_Highscores.emplace_back(std::make_pair(name,score));
    }
 }