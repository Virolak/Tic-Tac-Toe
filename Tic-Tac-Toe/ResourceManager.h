// ##############################
// >>>>| ResourceManager.h |<<<<<
// ##############################

#pragma once

// Standard Library =============
#include <map>
// Project Headers ==============
#include "GLTexture.h"
#include "TextureCache.h"
// ==============================

// "Resource Manager" Class
class ResourceManager {

private:

	// Objects
	static TextureCache m_textureCache; ///< Cache of textures
	

public:

	// Class Defaults
	ResourceManager(); ///< Class Constructor
	~ResourceManager(); ///< Class Destructor

	// Functions
	static GLTexture getTexture(const GLchar* filePath); ///< Finds a texture in the map
};

