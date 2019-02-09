// ##############################
// >>>>>>>>>>| Tile.h |<<<<<<<<<<
// ##############################

#pragma once

// Dependencies =================
#include <GL/glew.h>
// Project Headers ==============
#include "SpriteBatch.h"
// ==============================


// "Tile Type" Class
enum class TileType {NONE, CROSS, CIRCLE};

// Tile Class
class Tile {

private:

	// Enums
	TileType m_tileType;

	// Variables
	GLfloat m_posX;
	GLfloat m_posY;
	GLfloat m_width;
	GLfloat m_height;
	GLboolean m_isPlaced;
	GLuint m_vboID;
	GLuint m_vaoID;
	GLboolean m_gotHit;
	GLboolean m_wasHit;
	GLuint m_texture;

public:

	// Class Defaults
	Tile(); ///< Class Constructor
	~Tile(); ///< Class Destructor

	// Functions
	GLvoid init(GLfloat posX, GLfloat posY, GLfloat width, GLfloat height); ///< Initializes position of tiles
	GLvoid placeTile(TileType tileType); ///< Sets the Tile as either an X or an O
	GLboolean update(GLfloat mouseClickX, GLfloat mouseClickY, GLint screenWidth, GLint screenHeight, TileType tileType); ///< Checks if the mouse clicked within the area
	GLvoid draw(SpriteBatch& spriteBatch); ///< Renders the tile

	// Setters
	GLvoid setType(TileType tileType) {
		m_tileType = tileType; 
		if (m_tileType == TileType::NONE) {
			m_gotHit = GL_FALSE; 
			m_isPlaced = GL_FALSE;
		}
	}
	GLvoid setHitToFalse() { m_gotHit = GL_FALSE; }

	// Getters
	GLfloat getPosX() { return m_posX; }
	GLfloat getPosY() { return m_posY; }
	GLfloat getWidth() { return m_width; }
	GLfloat getHeight() { return m_height; }
	TileType getType() { return m_tileType; }
	GLboolean getHit() { return m_gotHit; }
};

