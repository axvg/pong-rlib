#pragma once
#include <raylib.h>

struct Ball{
    float x, y;
    float radius;
    float speedX, speedY;

    void Draw();
};