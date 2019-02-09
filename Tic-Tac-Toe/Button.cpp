// ##############################
// >>>>>>>>| Button.cpp |<<<<<<<<
// ##############################

// Project Headers ==============
#include "Button.h"
#include "ResourceManager.h"
// ==============================

// Class Constructor
Button::Button() :
	m_isClicked(GL_FALSE)
{ /* Empty */ }

// Class Destructor
Button::~Button()
{ /* Empty */ }

// Initialize the button
GLvoid Button::init(GLfloat posX, GLfloat posY, GLfloat width, GLfloat height, ButtonType buttonType) {

	m_posX = posX - width / 2.0f;
	m_posY = posY - width / 2.0f;
	m_width = width;
	m_height = height;
	m_type = buttonType;
	
	// Set texture
	if (buttonType == RETRY) {
		m_texture = ResourceManager::getTexture("assets/images/retry_button.png").id;
	} 

	if (buttonType == QUIT) {
		m_texture = ResourceManager::getTexture("assets/images/quit_button.png").id;
	}


}

// Take action on button press
GLvoid Button::press(GLfloat mouseClickX, GLfloat mouseClickY, GLint screenWidth, GLint screenHeight) {

	// Convert Window Coordinates to Space Coordinates
	mouseClickX = ((mouseClickX - (screenWidth / 2)) / screenWidth) * 2.0f;
	mouseClickY = (((mouseClickY - (screenHeight / 2)) / screenHeight) * 2.0f) * -1;

	if (mouseClickX > m_posX && mouseClickX < m_posX + m_width) {
		if (mouseClickY > m_posY && mouseClickY < m_posY + m_height) {
			m_isClicked = GL_TRUE;
		}
	}


}

// Render the button
GLvoid Button::draw(SpriteBatch& spriteBatch) {

	glm::vec4 destRect(m_posX, m_posY, m_width, m_height);
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	Color color;

	spriteBatch.draw(destRect, uvRect, m_texture, 5.0f, color);

}
