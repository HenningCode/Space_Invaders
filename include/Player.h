//
// Created by Henning Wilmer on 13.02.20.
//

#ifndef FIRSTTEXTURE_PLAYER_H
#define FIRSTTEXTURE_PLAYER_H

#include <raylib.h>
#include "../include/Projectile.h"
#include "GameObject.h"
#include "Enemy.h"

class Player: public GameObject {
public:
    Player(int,int, Texture2D);

    void Update() override;
    void Draw() override;

    void ChangeDirection(Direction dir);

    void PlayerHit();

    int GetLifes();
    Vector2 GetPosition() override;


private:
    int m_xPosition;
    int m_yPosition;
    int m_PlayerWidth;
    int m_PlayerHeight;
    int m_Lives;
    Direction m_Direction;

    Texture2D m_PlayerTexture;

    Rectangle m_HeartFull;
    Rectangle m_HeartGone;

    Rectangle m_PlayerRectangle;
    Vector2 m_PlayerPosition;

    bool m_BulletActive;
};


#endif //FIRSTTEXTURE_PLAYER_H
