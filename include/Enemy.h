//
// Created by Henning Wilmer on 13.02.20.
//

#ifndef FIRSTTEXTURE_ENEMY_H
#define FIRSTTEXTURE_ENEMY_H

#include <raylib.h>
#include "../include/Projectile.h"
#include "GameObject.h"

enum class Direction{RIGHT, LEFT};

class Enemy: public GameObject {
public:
    Enemy(int xStart, int yStart, int movingRange, int type, bool shootingAllowed, Texture2D texture);

    void Draw() override;
    void Update() override;
    Vector2 GetPosition() override;

private:
    float m_Timer;
    int m_Counter;
    int m_xStart;

    Direction m_Direction;
    bool m_AllowedToShoot;

    Texture2D m_EnemyTexture;

    Rectangle m_EnemyRectangle;
    Rectangle m_EnemyRectangle2;
    Rectangle* m_ActiveFrame;
    Vector2 m_EnemyPosition;
};


#endif //FIRSTTEXTURE_ENEMY_H
