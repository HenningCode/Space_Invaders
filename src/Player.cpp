//
// Created by Henning Wilmer on 13.02.20.
//

#include "../include/Player.h"
#include "../include/Projectile.h"
#include <raylib.h>
#include <iostream>

Player::Player(int xPosition, int yPosition, Texture2D texture): m_xPosition(xPosition), m_yPosition(yPosition), m_BulletActive(false), m_Lives(3),m_PlayerTexture(texture)
,m_Direction(),m_PlayerWidth(21),m_PlayerHeight(14) {

    m_PlayerRectangle = {0,0,(float)m_PlayerWidth,(float)m_PlayerHeight};
    m_PlayerPosition = {300-10,350};

    m_HeartFull = {4,17,21,20};
    m_HeartGone = {25,17,21,20};

}

void Player::Update() {
    if(m_Direction == Direction::RIGHT && m_PlayerPosition.x < 550)
        m_PlayerPosition.x++;
    else if(m_Direction == Direction::LEFT && m_PlayerPosition.x > 50)
        m_PlayerPosition.x--;

}

void Player::Draw() {
    switch(m_Lives){
        case 0:
            DrawTextureRec(m_PlayerTexture,m_HeartGone,(Vector2){10,10},WHITE);
            DrawTextureRec(m_PlayerTexture,m_HeartGone,(Vector2){38,10},WHITE);
            DrawTextureRec(m_PlayerTexture,m_HeartGone,(Vector2){66,10},WHITE);
            break;
        case 1:
            DrawTextureRec(m_PlayerTexture,m_HeartFull,(Vector2){10,10},WHITE);
            DrawTextureRec(m_PlayerTexture,m_HeartGone,(Vector2){38,10},WHITE);
            DrawTextureRec(m_PlayerTexture,m_HeartGone,(Vector2){66,10},WHITE);
            break;
        case 2:
            DrawTextureRec(m_PlayerTexture,m_HeartFull,(Vector2){10,10},WHITE);
            DrawTextureRec(m_PlayerTexture,m_HeartFull,(Vector2){38,10},WHITE);
            DrawTextureRec(m_PlayerTexture,m_HeartGone,(Vector2){66,10},WHITE);
            break;
        case 3:
            DrawTextureRec(m_PlayerTexture,m_HeartFull,(Vector2){10,10},WHITE);
            DrawTextureRec(m_PlayerTexture,m_HeartFull,(Vector2){38,10},WHITE);
            DrawTextureRec(m_PlayerTexture,m_HeartFull,(Vector2){66,10},WHITE);
            break;

    }
    DrawTextureRec(m_PlayerTexture,m_PlayerRectangle,m_PlayerPosition,WHITE);
}

void Player::ChangeDirection(Direction dir) {
    if(dir == Direction::RIGHT)
        m_Direction = Direction::RIGHT;
    else
        m_Direction = Direction::LEFT;
}

void Player::PlayerHit() {
    m_Lives--;
}

int Player::GetLifes() {
    return m_Lives;
}

Vector2 Player::GetPosition() {
    return m_PlayerPosition;
}