// ##############################
// >>>>>>>>>| Tile.cpp |<<<<<<<<<
// ##############################

// Standard Library =============
#include <math.h>
#include <iostream>
// Project Headers ==============
#include "ResourceManager.h"
#include "Tile.h"
#include "VertexData.h"
// ==============================

// Class Constructor
Tile::Tile() :
	m_tileType(TileType::NONE),
	m_isPlaced(GL_FALSE),
	m_wasHit(GL_FALSE)
{ /* Empty */ }

// Class Destructor
Tile::~Tile()
{ /* Empty */ }

const GLfloat PI = 3.14159265359f;

// Initializes a tile
GLvoid Tile::init(GLfloat posX, GLfloat posY, GLfloat width, GLfloat height) {

	// Set Properties
	m_posX = posX; ///< Set Horizontal Position of Tile
	m_posY = posY; ///< Set Vertical Position of Tile
	m_width = width; ///< Set width of tile
	m_height = height; ///< Set height of tile

}

// Initializes the tile
GLvoid Tile::placeTile(TileType tileType) {

	if (m_isPlaced == GL_FALSE) {

		m_tileType = tileType;

		if (m_tileType == TileType::CROSS) {

			// Set X Texture
			m_texture = ResourceManager::getTexture("assets/images/Xs.png").id;

		}

		else if (m_tileType == TileType::CIRCLE) {

			// Set O Texture
			m_texture = ResourceManager::getTexture("assets/images/Os.png").id;

		}

		m_isPlaced = GL_TRUE;

	}
}

// Checks if the mouse clicked within the area of the tile
GLboolean Tile::update(GLfloat mouseClickX, GLfloat mouseClickY, GLint screenWidth, GLint screenHeight, TileType tileType) {

	if (m_gotHit == GL_FALSE) {

		// Find bottom left position of area
		GLfloat bottomLeftX = m_posX - (m_width / 2.0f);
		GLfloat bottomLeftY = m_posY - (m_height / 2.0f);

		// Convert Window Coordinates to Space Coordinates
		mouseClickX = ((mouseClickX - (screenWidth / 2)) / screenWidth) * 2.0f;
		mouseClickY = (((mouseClickY - (screenHeight / 2)) / screenHeight) * 2.0f) * -1;

		// Check if mouseclick is within the area
		if (mouseClickX > bottomLeftX && mouseClickX < (bottomLeftX + m_width)) {
			if (mouseClickY > bottomLeftY && mouseClickY < (bottomLeftY + m_height)) {
				placeTile(tileType);
				m_gotHit = GL_TRUE;
				return GL_TRUE;
			}
		}
	}
	
	// Button did not get clicked
	return GL_FALSE;
}

// Renders the tile
GLvoid Tile::draw(SpriteBatch& spriteBatch) {

	// Set position and size of tile
	glm::vec4 destRect(m_posX - (m_width / 2.0f), m_posY - (m_height / 2.0f), m_width, m_height);

	// Set UV Wrapping coordinates
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	// Choose color
	Color color;

	// Only draw the tile if it is either an X or an O
	if (m_isPlaced == GL_TRUE) {
		spriteBatch.draw(destRect, uvRect, m_texture, 3.0f, color);
	}

}
