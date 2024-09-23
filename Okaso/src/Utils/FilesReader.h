#pragma once
#include <iostream>
#include <string>
#include "Utils.h"

namespace OkasoEngine_Utilities
{
	struct EXPORT ShaderProgram
	{
		std::string vertexShader;
		std::string fragmentShader;

		/// <summary>
		/// Set Vertex and Fragment Shader
		/// <para> vertexShader : Vertex Shader Program
		/// <para> fragmentShader : Fragment Shader Program
		/// </summary>
		ShaderProgram(std::string vertexShader, std::string fragmentShader)
		{
			this->vertexShader = vertexShader;
			this->fragmentShader = fragmentShader;
		}
	};


	class EXPORT OkasoUtils
	{
		public:
		/// <summary>
		/// Reads the shader archive
		/// <para> path : path to the shader archive
		/// </summary>
			static ShaderProgram ParseShader(const std::string& path);

		private:
	};
}