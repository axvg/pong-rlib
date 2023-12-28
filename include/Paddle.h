#pragma once
#include <raylib.h>

struct Paddle{
    float x, y;
    float width, height;
    float speedY;

    void Draw();
};