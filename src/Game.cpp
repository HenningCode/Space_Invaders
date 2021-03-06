//
// Created by Henning Wilmer on 13.02.20.
//

#include <iostream>
#include <string>
#include <random>
#include "../include/Game.h"
#include "../include/Enemy.h"
#include "../include/Player.h"
#include "../include/ScoreManager.h"

Game::Game(int width, int height): m_ScreenWidth(width), m_ScreenHeight(height), m_Score(0), m_Quit(false), m_Name(),m_Timer(0) {
    InitWindow(m_ScreenWidth, m_ScreenHeight, "SpaceInvaders");
    SetTargetFPS(300);
    SetTextureFilter(GetFontDefault().texture, FILTER_POINT);

    m_Textures = LoadTexture("../assets/Space_Invaders.png");
    m_EnemyTexture = LoadTexture("../assets/Enemys.png");
    m_StartButton = LoadTexture("../assets/Start_Button.png");
    m_QuitButton = LoadTexture("../assets/Quit_Button.png");
    m_HighscoreButton = LoadTexture("../assets/Highscore_Button.png");
    m_BackButton = LoadTexture("../assets/Back_Button.png");

    m_StartBounds = {(float)m_ScreenWidth / 2 - 34, (float)m_ScreenHeight / 2, 68, 25};
    m_QuitBounds = {(float)m_ScreenWidth / 2 - 23, (float)m_ScreenHeight / 2 + 50, 46, 20};
    m_HighscoreBounds = {(float)m_ScreenWidth - 40, 10, 22, 19};
    m_BackBounds = {(float)10,(float)10,54,22};
    m_MousePosition = {0.f,0.f};


    m_Screen = Screens::START;
    m_PlayerProjectile = nullptr;
    m_ScoreManager = new ScoreManager(m_ScreenWidth, m_ScreenHeight);
}

Game::~Game() {
    for(auto &i: m_Enemys)
        delete i;
    UnloadTexture(m_Textures);
    UnloadTexture(m_StartButton);
    UnloadTexture(m_QuitButton);
    UnloadTexture(m_HighscoreButton);
}

bool Game::GetHighscoreName(){

    bool done = false;
    int key = GetKeyPressed();


    while(key > 0){
        if ((key >= 32) && (key <= 125) && m_Name.size() < 9){
            m_Name += (char)key;
        }
        key = GetKeyPressed();
    }
    if(IsKeyPressed(KEY_BACKSPACE)) {
        m_Name.pop_back();
    }
    if(IsKeyPressed(KEY_ENTER)) {
        done = true;
        std::cout << "WHAT" << std::endl;
    }

    return done;
}

void Game::HandleInput(){
    if(IsKeyDown(KEY_LEFT)) {
        m_Player->ChangeDirection(Direction::LEFT);
        m_Player->Update();
    }
    if(IsKeyDown(KEY_RIGHT)) {
        m_Player->ChangeDirection(Direction::RIGHT);
        m_Player->Update();
    }
    if(IsKeyPressed(KEY_SPACE)) {
        if (m_PlayerProjectile == nullptr) {
            CreateProjectile(ProjectileSource::PLAYER, m_Player);
        }
    }
}

void Game::CreateProjectile(ProjectileSource source,GameObject* object) {
    if(source == ProjectileSource::PLAYER)
        m_PlayerProjectile = new Projectile(ProjectileSource::PLAYER, object->GetPosition(),m_Textures);
    else
        m_EnemyProjectiles.emplace_back(new Projectile(ProjectileSource::ENEMY, object->GetPosition(),m_Textures));
}

void Game::Start() {
    Update();
}

void Game::Update() {

    while(!WindowShouldClose() && !m_Quit) {
        switch(m_Screen){
            case Screens::START:
                UpdateStart();
                break;
            case Screens::GAME:
                UpdateGame();
                break;
            case Screens::END:
                UpdateEndscreen();
                break;
            case Screens::HIGHSCORE:
                UpdateHighscore();
        }
        Draw();
    }
    CloseWindow();
}

void Game::UpdateStart() {
    bool startActive = false;
    bool quitActive = false;
    bool highscoreActive = false;
    m_MousePosition = GetMousePosition();

    if(CheckCollisionPointRec(m_MousePosition,m_StartBounds))
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            m_Enemys.clear();
            m_PlayerProjectile = nullptr;
            m_EnemyProjectiles.clear();
            m_Name.clear();
            m_Player = new Player(m_ScreenWidth / 2, 100, m_Textures);
            CreateLevel1();
            m_Score = 0;

            startActive = true;
        }

    if(CheckCollisionPointRec(m_MousePosition,m_QuitBounds))
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            quitActive = true;
    if(CheckCollisionPointRec(m_MousePosition,m_HighscoreBounds))
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            highscoreActive = true;

    if(startActive)
        m_Screen = Screens::GAME;
    if(quitActive) {
        m_Quit = true;
    }
    if(highscoreActive)
        m_Screen = Screens::HIGHSCORE;
}

//Function that updates Player Enemy and Projectile positions
void Game::UpdateGame(){
    //Temp Variable
    m_Timer++;
    //Check If either an Enemy or the Player got it
    CheckHit();
    //Update Player and if Spacebar got it return a new Projectile
    HandleInput();
    //Update all Enemys
    for(auto &enemy: m_Enemys){
        enemy->Update();
        if(GenerateRandomInt(0, 1000) == 999)
            CreateProjectile(ProjectileSource::ENEMY,enemy);
    }

    //Update Enemy Projectiles and delete them if they are out of the screen
    for(auto pIt = m_EnemyProjectiles.begin(); pIt != m_EnemyProjectiles.end();){
        (*pIt)->Update();
        if((*pIt)->GetPosition().y > (float)m_ScreenHeight){
            delete (*pIt);
            pIt = m_EnemyProjectiles.erase(pIt);
        }else
            ++pIt;
    }
    //Update PlayerProjectile
    if(m_PlayerProjectile != nullptr)
        m_PlayerProjectile->Update();
    //Delete PlayerProjectile if out of screen and let the Player shoot again
    if(m_PlayerProjectile != nullptr && m_PlayerProjectile->GetPosition().y < 0) {
        delete m_PlayerProjectile;
        m_PlayerProjectile = nullptr;
    }

    //If they player got no lives the game is over
    if(m_Player->GetLifes() == 0) {
        delete m_Player;
        m_Screen = Screens::END;
    }
    if (m_Enemys.empty())
        CreateLevel1();

}

void Game::UpdateEndscreen(){
    if(!m_ScoreManager->CheckIfNewHighscore(m_Score)) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            m_Screen = Screens::START;
    }else{
        if(GetHighscoreName()) {
            m_ScoreManager->SaveNewHighscore(m_Name, m_Score);
            m_Screen = Screens::START;
        }
     }
}

void Game::UpdateHighscore(){
    bool backActive = false;
    m_MousePosition = GetMousePosition();

    if(CheckCollisionPointRec(m_MousePosition,m_BackBounds))
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            backActive = true;

    if(backActive) {
        m_Screen = Screens::START;
    }
}

void Game::CheckHit() {
    //Check if the player got it from any of the Enemy bullets
    //and delete the bullet if the player got hit
    for(auto projectile = m_EnemyProjectiles.begin(); projectile != m_EnemyProjectiles.end();) {

        if ((*projectile)->GetPosition().x >= m_Player->GetPosition().x &&
            (*projectile)->GetPosition().x <= m_Player->GetPosition().x + 21 &&
            (*projectile)->GetPosition().y >= m_Player->GetPosition().y &&
            (*projectile)->GetPosition().y <= m_Player->GetPosition().y + 14) {

            delete (*projectile);
            m_Player->PlayerHit();
            projectile = m_EnemyProjectiles.erase(projectile);
        }else
            ++projectile;
    }
    //Check if the player hit any enemy and delete the projectile and the enemy
    if(m_PlayerProjectile != nullptr) {
        for (auto enemy = m_Enemys.begin(); enemy != m_Enemys.end();) {
            if (m_PlayerProjectile->GetPosition().x >= (*enemy)->GetPosition().x &&
                m_PlayerProjectile->GetPosition().x <= (*enemy)->GetPosition().x + 24 &&
                m_PlayerProjectile->GetPosition().y <= (*enemy)->GetPosition().y &&
                m_PlayerProjectile->GetPosition().y >= (*enemy)->GetPosition().y - 15) {
                m_Score += 10;
                delete (*enemy);
                delete(m_PlayerProjectile);
                m_PlayerProjectile = nullptr;
                enemy = m_Enemys.erase(enemy);
                break;
            } else {
                ++enemy;
            }
        }
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    switch(m_Screen){
        case Screens::START:
            DrawStartScreen();
            break;
        case Screens::GAME:
            DrawGameScreen();
            break;
        case Screens::END:
            DrawGameOverScreen();
            break;
        case Screens::HIGHSCORE:
            DrawHighscore();
            break;
    }
    EndDrawing();
}

void Game::DrawStartScreen(){
    int headLine = MeasureText("SPACE INVADERS",40);

    DrawText("SPACE INVADERS",m_ScreenWidth/2-headLine/2,100,40,WHITE);
    DrawTextureRec(m_StartButton,(Rectangle){.x=0,.y=0,.width=68,.height=25},(Vector2){m_StartBounds.x,m_StartBounds.y},WHITE);
    DrawTextureRec(m_QuitButton,(Rectangle){.x=0,.y=0,.width=46,.height=20},(Vector2){m_QuitBounds.x,m_QuitBounds.y},WHITE);
    DrawTextureRec(m_HighscoreButton,(Rectangle){.x=1,.y=0,.width=22,.height=19},(Vector2){m_HighscoreBounds.x,m_HighscoreBounds.y},WHITE);
}

void Game::DrawGameScreen(){
    m_Player->Draw();
    if(m_PlayerProjectile != nullptr)
        m_PlayerProjectile ->Draw();
    for(auto &projectile: m_EnemyProjectiles)
        projectile->Draw();
    for(auto &enemys: m_Enemys)
        enemys->Draw();
    DrawText(FormatText("Score: %05i",m_Score),460,10,20,WHITE);
}

void Game::DrawGameOverScreen(){
    int gameOver = MeasureText("Game Over!",30);
    int returnWord = MeasureText("Click to return to Start screen!",20);
    int score = MeasureText(FormatText("Score: %05i",m_Score),20);

    DrawText("Game Over!", m_ScreenWidth / 2 - gameOver/2, 70, 30, WHITE);
    DrawText(FormatText("Score: %05i",m_Score), m_ScreenWidth/2 - score/2, 170, 20, WHITE);

    if(!m_ScoreManager->CheckIfNewHighscore(m_Score)){
        DrawText("Click to return to Start screen!", m_ScreenWidth / 2 - returnWord/2,300,20,WHITE);
    }
    else{
        int newScore = MeasureText(" New Highscore! Enter your Name!",20);
        int newName = MeasureText(FormatText("%s",m_Name.c_str()),20);
        DrawText(FormatText("%s",m_Name.c_str()),m_ScreenWidth/2-newName/2,300,20,WHITE);
        DrawText("New Highscore! Enter your Name!",m_ScreenWidth/2-newScore/2,250,20,WHITE);
    }
}

void Game::DrawHighscore(){
    DrawTextureRec(m_BackButton,(Rectangle){.x=0,.y=0,.width=54,.height=22},(Vector2){m_BackBounds.x,m_BackBounds.y},WHITE);
    m_ScoreManager->Draw();
}

void Game::CreateLevel1(){
    m_Enemys.emplace_back(new Enemy(100, 50, 50, 1,true, m_EnemyTexture));
    m_Enemys.emplace_back(new Enemy(150, 50, 50, 2,true, m_EnemyTexture));
    m_Enemys.emplace_back(new Enemy(200, 50, 50, 1,true, m_EnemyTexture));
    m_Enemys.emplace_back(new Enemy(250, 50, 50, 2,true, m_EnemyTexture));
    m_Enemys.emplace_back(new Enemy(300, 50, 50, 1,true, m_EnemyTexture));
    m_Enemys.emplace_back(new Enemy(350, 50, 50, 2,true, m_EnemyTexture));
    m_Enemys.emplace_back(new Enemy(400, 50, 50, 1,true, m_EnemyTexture));
    m_Enemys.emplace_back(new Enemy(450, 50, 50, 2,true, m_EnemyTexture));
    m_Enemys.emplace_back(new Enemy(500, 50, 50, 1,true, m_EnemyTexture));

}

int Game::GenerateRandomInt(int a, int b){
    int number = 0;
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(a, b);
    number = distr(eng);

    return number;
}
