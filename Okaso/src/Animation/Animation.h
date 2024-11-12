#pragma once

#include <vector>

#include "Frame.h"
#include "../Utils/Utils.h"


class EXPORT Animation
{
public:
    Animation(int initialX, int initialY, int maxFrames, float maxAnimationTime, int spriteWidth, int spriteHeight, int frameWidth, int frameHeight);
    Animation();
    bool hasFrames();
    void addFrames();
    void update();
    Frame* currentFrame;
    std::vector<Frame*> totalFrames;
    
private:
    std::vector<Frame> framesInAnimation;
    int spriteWidth;
    int spriteHeight;
    int frameWidth;
    int frameHeight;
    int currentFrameCounter;
    int maxFramesInAnimation;
    float maxAnimationTime;
    float currentTime;
    int initialX;
    int initialY;
};
