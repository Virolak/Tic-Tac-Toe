// ##############################
// >>>| ResourceManager.cpp |<<<<
// ##############################

// Standard Library =============
#include <iterator>
// Project Headers ==============
#include "ResourceManager.h"
// ==============================

// Map of textures associated with a filepath
TextureCache ResourceManager::m_textureCache;

// Class Constructor
ResourceManager::ResourceManager()
{ /* Empty */ }

// Class Destructor
ResourceManager::~ResourceManager()
{ /* Empty */ }

// Finds a texture in the map
GLTexture ResourceManager::getTexture(const GLchar* filePath) {

	return m_textureCache.getTexture(filePath);

}
