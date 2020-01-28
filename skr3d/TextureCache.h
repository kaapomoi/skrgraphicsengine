#pragma once
#include <map>
#include <string>

#include "ImageLoader.h"
#include "GLTexture.h"
namespace skrengine
{
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(std::string texturePath);

	private:
		std::map<std::string, GLTexture> _textureMap;

	};

}