#include "Frame.h"
#include "../Utils/OkasoDebuger.h"

glm::vec2 Frame::get_uv_coord(int id)
{
    if (id >= maxFrameSize && id < 0)
    {
        OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("ERROR :: Id UV outside range", OkasoEngine_Utilities::Error_L);
        return {0, 0};
    }
    else
        return uvCoord[id];
}

Frame::Frame(glm::vec2 first_uv_coord, glm::vec2 second_uv_coord, glm::vec2 third_uv_coord, glm::vec2 fourth_uv_coord)
{
    uvCoord[0] = first_uv_coord;
    uvCoord[1] = second_uv_coord;
    uvCoord[2] = third_uv_coord;
    uvCoord[3] = fourth_uv_coord;
}