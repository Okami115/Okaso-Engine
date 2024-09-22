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

		ShaderProgram(std::string vertexShader, std::string fragmentShader)
		{
			this->vertexShader = vertexShader;
			this->fragmentShader = fragmentShader;
		}
	};


	class EXPORT OkasoUtils
	{
		public:
			static ShaderProgram ParseShader(const std::string& path);

		private:
	};
}