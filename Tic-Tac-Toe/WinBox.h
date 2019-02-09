// ##############################
// >>>>>>>>>| WinBox.h |<<<<<<<<<
// ##############################

#pragma once

// Dependencies =================
#include <GL/glew.h>
// Project Headers ==============
#include "SpriteBatch.h"
// ==============================

// "Win Box" Class
class WinBox {

private:

	// Variables
	GLfloat m_posX; ///< Horizontal position of box
	GLfloat m_posY; ///< Vertical position of box
	GLfloat m_width; ///< width of box
	GLfloat m_height; ///< height of box
	GLuint m_textureID; ///< Texture of box

public:

	// Class Defaults
	WinBox(); ///< Class Constructor
	~WinBox(); ///< Class Destructor

	// Functions
	GLvoid init(GLfloat posX, GLfloat posY, GLfloat width, GLfloat height); ///< Initializes the box
	GLvoid draw(SpriteBatch& spriteBatch); ///< Renders the box
};

