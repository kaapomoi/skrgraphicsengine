#include "TextureCache.h"
namespace skrengine
{
	TextureCache::TextureCache()
	{
	}

	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string texturePath)
	{
		// Lookup texturemap
		auto mit = _textureMap.find(texturePath);

		// If its not in the map
		if (mit == _textureMap.end())
		{
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			// Insert it into the map
			_textureMap.insert(make_pair(texturePath, newTexture));
			return newTexture;
		}

		return mit->second;
	}
}