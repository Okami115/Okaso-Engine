#pragma once
#include <iostream>
#include <string>

namespace OkasoEngine_Utilities
{
	struct ShaderProgram
	{
		std::string vertexShader;
		std::string fragmentShader;

		ShaderProgram(std::string vertexShader, std::string fragmentShader)
		{
			this->vertexShader = vertexShader;
			this->fragmentShader = fragmentShader;
		}
	};


	class OkasoUtils
	{
		public:
			static ShaderProgram ParseShader(const std::string& path);

		private:
	};
}