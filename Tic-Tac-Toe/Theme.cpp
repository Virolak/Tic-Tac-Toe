// ##############################
// >>>>>>>>| Theme.cpp |<<<<<<<<<
// ##############################

// Dependencies =================
#include <GLM/glm.hpp>
// Project Headers ==============
#include "Theme.h"
#include "ResourceManager.h"
#include "VertexData.h"
// ==============================

// Class Constructor
Theme::Theme()
{ /* Empty */ }

// Class Destructor
Theme::~Theme()
{ /* Empty */ }

// Sets the background image
GLvoid Theme::setBackground(const GLchar* filePath) {

	// Read in the texture
	m_backgroundID = ResourceManager::getTexture(filePath).id;

}

// Renders theme
GLvoid Theme::render(SpriteBatch& spriteBatch) {

	// Destination Rectangle
	glm::vec4 destRect(-1.0f, -1.0f, 2.0f, 2.0f);

	// UV coordinates
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	// Background color
	Color color;

	// Render the background image
	spriteBatch.draw(destRect, uvRect, m_backgroundID, 1.0f, color);

}
