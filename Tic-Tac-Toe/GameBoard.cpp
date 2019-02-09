// ##############################
// >>>>>>| GameBoard.cpp |<<<<<<<
// ##############################

// Standard Library =============
#include <cstdlib>
// Project Headers ==============
#include "VertexData.h"
#include "GameBoard.h"
#include "ResourceManager.h"
// ==============================

// Class Constructor
GameBoard::GameBoard() :
	m_posX(0.0f),
	m_posY(0.0f),
	m_width(0.0f),
	m_height(0.0f)
{ /* Empty */ }

// Class Destructor
GameBoard::~GameBoard()
{ /* Empty */ }

// Initializes the Game Board
GLvoid GameBoard::init(GLfloat width, GLfloat height) {

	// Set properties
	m_width = width; ///< Set horizontal position of board
	m_height = height; ///< Set vertical position of board
	m_sectionPosX = -(m_width / 3.0f); ///< Horizontal position of first tile space
	m_sectionPosY = -(m_height / 3.0f); ///< Vertical position of first tile space

	// Set the texture of the board
	m_texture = ResourceManager::getTexture("assets/images/game_board.png").id;

}

// Finds next horizontal position of a section
GLfloat GameBoard::findSectionPosX() {

	// Set the value of the X position to grab
	GLfloat currentPos = m_sectionPosX;

	// Find the X position of the next section
	m_sectionPosX += m_width / 3.0f;

	// Return the X position
	return currentPos;

}

// Finds next vertical position of a section
GLfloat GameBoard::findSectionPosY() {

	// Only increase Y position if Horizontal sections are filled
	if (m_sectionPosX >= m_width / 3.0f * 2) {

		// Increase the height of the Y position
		m_sectionPosY += m_height / 3.0f;

		// Reset the X position
		m_sectionPosX = -m_width / 3.0f;
	}

	// Return the Y position
	return m_sectionPosY;

}

// Renders the Game Board
GLvoid GameBoard::draw(SpriteBatch& spriteBatch) {

	// Set Position and size of board
	glm::vec4 destRect(-0.5f, -0.5f, m_width, m_height);

	// Set image UV-Wrapping
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	// Set color
	Color color(188, 175, 101, 255);

	// Render using a sprite batch
	spriteBatch.draw(destRect, uvRect, m_texture, 2.0f, color);

}
