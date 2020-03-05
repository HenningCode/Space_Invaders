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
#include "ScoreManager.h"

enum class Screens{START, GAME, END, HIGHSCORE};

class Game {

public:
    Game(int, int);
    ~Game();

    void Start();

private:
    void HandleInput();
    void Update();
    void Draw();
    void CheckHit();
    void CreateProjectile(ProjectileSource source ,GameObject* object);

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

    bool GetHighscoreName();
    static int GenerateRandomInt(int a, int b);

    std::list<Enemy*> m_Enemys;
    std::list<Projectile*> m_EnemyProjectiles;
    Projectile* m_PlayerProjectile;
    Player* m_Player;
    ScoreManager* m_ScoreManager;

    int m_ScreenWidth;
    int m_ScreenHeight;
    int m_Score;
    int m_Timer;
    bool m_Quit;
    std::string m_Name;
    std::vector<std::pair<std::string,int>> m_Highscores;

    Texture2D m_Textures;
    Texture2D m_EnemyTexture;
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
