// ##############################
// >>>>>>| TextureCache.h |<<<<<<
// ##############################

#pragma once

// Standard Library =============
#include <map>
// Project Headers ==============
#include "GLTexture.h"
// ==============================

// "Texture Cache" Class
class TextureCache {

private:

	// Variables
	std::map<const GLchar*, GLTexture> m_textureMap; ///< Map containing a texture

public:

	// Class Defaults
	TextureCache(); ///< Class Constructor
	~TextureCache(); ///< Class Destructor

	// Functions
	GLTexture getTexture(const GLchar* filePath); ///< Grabs a texture from the texture cache
};

