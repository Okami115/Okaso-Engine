﻿#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "../../src/Renderer/Renderer.h"
#include "../../src/Utils/Utils.h"

class Texture
{
private:
    unsigned int m_RendererID;
    string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
public:
    Texture(const string& FilePath);
    ~Texture();
    void Bind(unsigned int slot = 0) const;
    void Unbind() const;
    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
};
