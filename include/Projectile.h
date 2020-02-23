//
// Created by Henning Wilmer on 16.02.20.
//

#ifndef FIRSTTEXTURE_PROJECTILE_H
#define FIRSTTEXTURE_PROJECTILE_H

#include <raylib.h>

enum class ProjectileSource{PLAYER,ENEMY};

class Projectile {
public:
    Projectile(ProjectileSource source, Vector2 position, Texture2D texture);
    void Draw();
    void Update();

    Vector2 GetPosition();
private:

    Texture2D m_Texture;
    Vector2 m_Position;
    ProjectileSource m_Source;
    Rectangle m_ProjectileRectangle;

};


#endif //FIRSTTEXTURE_PROJECTILE_H
