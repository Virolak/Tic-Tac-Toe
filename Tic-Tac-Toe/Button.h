// ##############################
// >>>>>>>>>| Button.h |<<<<<<<<<
// ##############################

#pragma once

// Project Headers ==============
#include "SpriteBatch.h"
// ==============================

enum ButtonType {RETRY, QUIT};

// "Button" Class
class Button {

private:

	// Enums
	ButtonType m_type;

	// Variables
	GLuint m_texture;
	GLfloat m_posX;
	GLfloat m_posY;
	GLfloat m_width;
	GLfloat m_height;
	GLboolean m_isClicked;
	

public:

	// Button Class
	Button(); ///< Class Constructor
	~Button(); ///< Class Destructor

	// Functions
	GLvoid init(GLfloat posX, GLfloat posY, GLfloat width, GLfloat height, ButtonType buttonType);
	GLvoid press(GLfloat mouseClickX, GLfloat mouseClickY, GLint screenWidth, GLint screenHeight);
	GLvoid draw(SpriteBatch& spriteBatch);

	// Getters
	GLboolean getClicked() { return m_isClicked; }
	GLvoid setClickedToFalse() { m_isClicked = GL_FALSE; }
};

