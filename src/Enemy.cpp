//
// Created by Henning Wilmer on 13.02.20.
//

#include "../include/Enemy.h"
#include "../include/Projectile.h"
#include <iostream>
#include <random>

Enemy::Enemy(int xStart, int yStart, int movingRange, bool shootingAllowed, Texture2D texture): m_AllowedToShoot(shootingAllowed), m_MovingRange(movingRange),
m_xStart(xStart), m_Timer(0.f), m_EnemyTexture(texture){

    m_Width = 24;
    m_Height = 15;

    m_Direction = Direction::RIGHT;

    m_EnemyRectangle = {33,0,(float)m_Width,(float)m_Height};
    m_EnemyPosition = {(float)xStart,(float)yStart};
}

Projectile* Enemy::Update() {
    m_Timer += GetFrameTime();

    if(m_Timer >= 0.05f){
        m_Timer = 0;
        if(m_Direction == Direction::RIGHT){
            if(((int)m_EnemyPosition.x - m_xStart) >= m_MovingRange)
                m_Direction = Direction::LEFT;
            else
                m_EnemyPosition.x ++;
        } else
            if((m_xStart - (int)m_EnemyPosition.x) >= m_MovingRange)
                m_Direction = Direction::RIGHT;
            else
                m_EnemyPosition.x --;
    }

    if(m_AllowedToShoot){
        std::random_device r;

        // Choose a random mean between 1 and 6
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_dist(1, 1000);
        int mean = uniform_dist(e1);
        if(mean == 10){
            return new Projectile(ProjectileSource::ENEMY,m_EnemyPosition,m_EnemyTexture);
        }

    }
    return nullptr;
}


void Enemy::Draw() {
    DrawTextureRec(m_EnemyTexture,m_EnemyRectangle,m_EnemyPosition,WHITE);
}

Vector2 Enemy::GetPosition() {
    return m_EnemyPosition;
}
