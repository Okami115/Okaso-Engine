#pragma once
#include "../Entity2D.h"

class Sprite : public Entity2D
{
private:
    float _width;
    float _height;
    float _channelsCount;
public:
    Sprite(float width = 10.0f, float height = 10.0f, float channelsCount = 4);
    ~Sprite();
};
