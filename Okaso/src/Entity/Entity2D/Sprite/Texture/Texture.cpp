﻿#include "Texture.h"

Texture::Texture(const string& FilePath) : m_RendererID(0),m_FilePath(FilePath), m_LocalBuffer(nullptr), m_Width(0), m_Height(0),
                                           m_BPP(0)
{
    rende
    GLCALL(glGenTextures(1,&m_RendererID));
    GLCALL(glBindTexture(GL_TEXTURE_2D,m_RendererID));
}

Texture::~Texture()
{
    
}

void Texture::Bind(unsigned int slot /*= 0*/) const
{
    
}

void Texture::Unbind()
{
    
}
