// ##############################
// >>>>>>>| GameBoard.h |<<<<<<<<
// ##############################

#pragma once

// Dependencies =================
#include <GL/glew.h>
// Project Headers ==============
#include "SpriteBatch.h"
// ==============================

// "GameBoard" Class
class GameBoard {

private:

	// Variables
	GLfloat m_posX; ///< Horizontal position of board
	GLfloat m_posY; ///< Vertical position of board
	GLfloat m_width; ///< Width of board
	GLfloat m_height; ///< Height of board
	GLfloat m_sectionPosX; ///< Vertical Position of section
	GLfloat m_sectionPosY; ///< Horizontal position of sectoin
	GLuint m_texture; ///< Image the board uses

public:

	// Class Defaults
	GameBoard(); ///< Class Constructor
	~GameBoard(); ///< Class Destructor

	// Functions
	GLvoid init(GLfloat width, GLfloat height); ///< Initializes the Game board
	GLfloat findSectionPosX(); ///< Finds next Horizontal position of section
	GLfloat findSectionPosY(); ///< Finds next Vertical position of section
	GLvoid draw(SpriteBatch& spriteBatch); ///< Renders the game board

	// Getters
	GLfloat getWidth() { return m_width; } ///< Return width of board
	GLfloat getHeight() { return m_height; } ///< Return height of board
};

