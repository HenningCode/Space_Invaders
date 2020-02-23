//
// Created by Henning Wilmer on 13.02.20.
//

#ifndef FIRSTTEXTURE_ENEMY_H
#define FIRSTTEXTURE_ENEMY_H

#include <raylib.h>
#include "../include/Projectile.h"

enum class Direction{RIGHT, LEFT};

class Enemy {
public:
    Enemy(int xStart, int yStart, int movingRange, bool shootingAllowed, Texture2D texture);

    void Draw();
    Projectile* Update();
    void BulletHit();
    Vector2 GetPosition();

private:
    int m_Width;
    int m_Height;
    float m_Timer;
    int m_MovingRange;
    int m_xStart;

    Direction m_Direction;
    bool m_AllowedToShoot;

    Texture2D m_EnemyTexture;

    Rectangle m_EnemyRectangle;
    Vector2 m_EnemyPosition;
};


#endif //FIRSTTEXTURE_ENEMY_H
