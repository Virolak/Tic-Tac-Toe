// ##############################
// >>>>>>>>| WinBox.cpp |<<<<<<<<
// ##############################

// Standard Library =============
#include <cstdlib>
// Project Headers ==============
#include "ResourceManager.h"
#include "WinBox.h"
// ==============================

// Class Constructor
WinBox::WinBox() :
	m_posX(0.0f),
	m_posY(0.0f),
	m_width(1.5f),
	m_height(1.0f)
{ /* Empty */ }

// Class Destructor
WinBox::~WinBox()
{ /* Empty */ }

// Initializes the box
GLvoid WinBox::init(GLfloat posX, GLfloat posY, GLfloat width, GLfloat height) {

	// Set position
	m_posX = posX - (width / 2.0f);
	m_posY = posY - (height / 2.0f);

	// Set size
	m_width = width;
	m_height = height;

	// Set texture
	m_textureID = ResourceManager::getTexture("assets/images/scroll.png").id;

}

// Renders the box
GLvoid WinBox::draw(SpriteBatch& spriteBatch) {

	// Set rendering position and size
	glm::vec4 destRect(m_posX, m_posY, m_width, m_height);

	// UV wrapping coordinates
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	// Choose color
	Color color;

	// Render using a sprite batch
	spriteBatch.draw(destRect, uvRect, m_textureID, 4.0f, color);

}
