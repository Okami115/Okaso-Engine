#pragma once
#include "../glm/glm.hpp"

class Frame
{
private :
    const static int maxFrameSize = 4;
    glm::vec2 uvCoord[maxFrameSize];

public:
    glm::vec2 get_uv_coord(int id);
    Frame(glm::vec2 first_uv_coord_uv, glm::vec2 secondUV, glm::vec2 thirdUV, glm::vec2 fourthUV);
};
