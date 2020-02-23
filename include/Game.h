//
// Created by Henning Wilmer on 13.02.20.
//

#ifndef FIRSTTEXTURE_GAME_H
#define FIRSTTEXTURE_GAME_H

#include <list>
#include <unordered_map>
#include <vector>
#include <string>
#include "Enemy.h"
#include "Player.h"

enum class Screens{START, GAME, END, HIGHSCORE};

class Game {

public:
    Game(int, int);
    ~Game();

    void Start();


private:
    void Update();
    void Draw();
    void CheckHit();

    void DrawStartScreen();
    void DrawGameScreen();
    void DrawGameOverScreen();
    void DrawHighscore();
    void CreateLevel1();
    void CreateLevel2();

    void UpdateStart();
    void UpdateGame();
    void UpdateHighscore();
    void UpdateEndscreen();

    void LoadHighscores();
    void CheckIfNewHighscore();
    void SaveNewHighscore();
    bool GetHighscoreName();

    std::list<Enemy*> m_Enemys;
    std::list<Projectile*> m_EnemyProjectiles;
    Projectile* m_PlayerProjectile;
    Player* m_Player;

    int m_ScreenWidth;
    int m_screenHeight;
    int m_Score;
    bool m_Quit;
    bool m_NewHighscore;
    std::string m_Name;
    std::vector<std::pair<std::string,int>> m_Highscores;

    Texture2D m_Textures;
    Texture2D m_StartButton;
    Texture2D m_QuitButton;
    Texture2D m_HighscoreButton;
    Texture2D m_BackButton;
    Screens m_Screen;

    Rectangle m_StartBounds;
    Rectangle m_QuitBounds;
    Rectangle m_HighscoreBounds;
    Rectangle m_BackBounds;
    Vector2 m_MousePosition;



};


#endif //FIRSTTEXTURE_GAME_H
