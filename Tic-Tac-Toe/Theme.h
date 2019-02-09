// ##############################
// >>>>>>>>>| Theme.h |<<<<<<<<<<
// ##############################

#pragma once

// Dependencies ==================
#include <GL/glew.h>
// Project Headers ===============
#include "SpriteBatch.h"
// ===============================

// Theme Class
class Theme {

private:

	// Variables
	GLuint m_backgroundID;

public:

	// Class Defaults
	Theme(); ///< Class Constructor
	~Theme(); ///< Class Destructor

	// Functions
	GLvoid setBackground(const GLchar* filePath); ///< Sets the background image
	GLvoid render(SpriteBatch& spriteBatch); ///< Renders theme
};

