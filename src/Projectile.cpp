//
// Created by Henning Wilmer on 16.02.20.
//

#include "../include/Projectile.h"

Projectile::Projectile(ProjectileSource source, Vector2 position, Texture2D texture):m_Source(source),m_Texture(texture) {
    if(m_Source == ProjectileSource::PLAYER) {
        m_ProjectileRectangle = {26, 0, 1, 5};
        m_Position = {position.x +10 , position.y};
    }
    else {
        m_ProjectileRectangle = {29, 0, 2, 8};
        m_Position = {position.x+ 11,position.y + 13};
    }
}

void Projectile::Update() {
    if(m_Source == ProjectileSource::PLAYER)
        m_Position.y -= 2;
    else
        m_Position.y +=2;
}

void Projectile::Draw() {
    DrawTextureRec(m_Texture,m_ProjectileRectangle,m_Position,WHITE);
}

Vector2 Projectile::GetPosition() {
    return m_Position;
}