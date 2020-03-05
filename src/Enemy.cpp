//
// Created by Henning Wilmer on 13.02.20.
//

#include "../include/Enemy.h"
#include <random>

Enemy::Enemy(int xStart, int yStart, int movingRange, int type, bool shootingAllowed, Texture2D texture):
m_AllowedToShoot(shootingAllowed),m_xStart(xStart), m_Timer(0.f), m_EnemyTexture(texture),m_Counter(0){

    switch(type){
        case 1:
            m_EnemyRectangle = {0,0,26,18};
            m_EnemyRectangle2 = {32,0,30,20};
            break;
        case 2:
            m_EnemyRectangle = {2,22,22,24};
            m_EnemyRectangle2 = {33,22,26,24};
            break;
        default:
            m_EnemyRectangle = {0,0,26,18};
            m_EnemyRectangle2 = {32,0,30,20};
            break;
    }

    m_Direction = Direction::RIGHT;

    m_ActiveFrame = &m_EnemyRectangle;
    m_EnemyPosition = {(float)xStart,(float)yStart};
}

void Enemy::Update() {
    m_Timer += GetFrameTime();

    if(m_Timer >= 0.6f){
        m_Counter++;
        if (m_ActiveFrame == &m_EnemyRectangle)
            m_ActiveFrame = &m_EnemyRectangle2;
        else
            m_ActiveFrame = &m_EnemyRectangle;
        m_Timer = 0;
        if(m_Counter >= 7) {
            m_EnemyPosition.y += 20;
            m_Counter = 0;
            if(m_Direction == Direction::RIGHT)
                m_Direction = Direction::LEFT;
            else
                m_Direction = Direction::RIGHT;
        }else {
            if (m_Direction == Direction::RIGHT)
                m_EnemyPosition.x += 10;
            else
                m_EnemyPosition.x -= 10;
        }
    }
}

void Enemy::Draw() {
    DrawTextureRec(m_EnemyTexture, *m_ActiveFrame, m_EnemyPosition, WHITE);
}

Vector2 Enemy::GetPosition() {
    return m_EnemyPosition;
}
