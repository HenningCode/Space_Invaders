//
// Created by Henning Wilmer on 27.02.20.
//

#ifndef SPACE_GAMEOBJECT_H
#define SPACE_GAMEOBJECT_H

#include <raylib.h>

class GameObject {

public:

    GameObject() = default;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual Vector2 GetPosition() = 0;
};


#endif //SPACE_GAMEOBJECT_H
