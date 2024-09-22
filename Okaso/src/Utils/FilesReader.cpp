#include "FilesReader.h"
#include "OkasoDebuger.h"
#include <fstream>
#include <string>
#include <sstream>

namespace OkasoEngine_Utilities
{
	ShaderProgram OkasoUtils::ParseShader(const std::string& path)
	{
		std::ifstream stram(path);

		enum class ShaderType
		{
			NONE = -1, VERTEX, FRAGMENT
		};

		std::string line;
		std::stringstream ss[2];
		ShaderType shaderType = ShaderType::NONE;

		while (getline(stram, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					shaderType = ShaderType::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					shaderType = ShaderType::FRAGMENT;
				}
			}
			else
			{
				ss[(int)shaderType] << line << '\n';
			}
		}
		OkasoDebuger::OKE_Debug(ss[0].str(), Info_L);
		OkasoDebuger::OKE_Debug(ss[1].str(), Info_L);

		return {ss[0].str(), ss[1].str()};
	}
}