#pragma once
#include "Utils.h"

static class EXPORT TextureImporter
{
public:
    static void InitTexture(const char* path, unsigned int* texture, bool invertTexture);
};
