// ##############################
// >>>>>>| ImageLoader.h |<<<<<<<
// ##############################

#pragma once

// Project Headers ==============
#include "GLTexture.h"
// ==============================

// Image Loader Class
class ImageLoader {

public:

	// Class Defaults
	ImageLoader(); ///< Class Constructor
	~ImageLoader(); ///< Class Destructor

	// Functions
	static GLTexture loadPNG(const GLchar* filePath); ///< Reads in a .png file
};

