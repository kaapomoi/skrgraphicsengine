#pragma once
#include <vector>
#include <string>
#include <fstream>

namespace skrengine
{
	class IOManager
	{
	public:
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);

	};

}