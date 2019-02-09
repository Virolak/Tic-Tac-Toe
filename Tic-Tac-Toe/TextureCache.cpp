// ##############################
// >>>>>| TextureCache.cpp |<<<<<
// ##############################

// Standard Library =============
#include <iterator>
// Project headers ==============
#include "ImageLoader.h"
#include "TextureCache.h"
// ==============================

// Class Constructor
TextureCache::TextureCache()
{ /* Empty */ }

// Class Destructor
TextureCache::~TextureCache()
{ /* Empty */ }

// Grabs a Texture from the texture cache
GLTexture TextureCache::getTexture(const GLchar* filePath) {

	// Iterate through the texture map until the texture is found
	std::map<const GLchar*, GLTexture>::iterator mit = m_textureMap.find(filePath);

	// Texture was not found in map
	if (mit == m_textureMap.end()) {

		// Create a new texture
		GLTexture newTexture = ImageLoader::loadPNG(filePath);

		// Add the texture to the map
		m_textureMap.insert(std::make_pair(filePath, newTexture));

		// Return the texture
		return newTexture;
	}

	// Return texture found in cache
	return mit->second;

}
