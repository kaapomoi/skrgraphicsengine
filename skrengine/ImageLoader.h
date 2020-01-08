#pragma once
#include "GLTexture.h"
#include <string>

namespace skrengine
{
	class ImageLoader
	{
	public:
		static GLTexture loadPNG(std::string filePath);
	};

}