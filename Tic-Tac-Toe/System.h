// ##############################
// >>>>>>>>>| System.h |<<<<<<<<<
// ##############################

#pragma once

// Standard Library =============
#include <string>
// Dependencies =================
#include <GL/glew.h>
#include <SDL/SDL.h>
// Project Headers ==============
#include "Button.h"
#include "GameBoard.h"
#include "GLSLProgram.h"
#include "SpriteBatch.h"
#include "Tile.h"
#include "Theme.h"
#include "WinBox.h"
#include "Window.h"
// ==============================

// "GameState" Enum
enum GameState {RUNNING = 0x01, QUITTING = 0x02};
enum Player {PLAYER1, PLAYER2};

// "System" class
class System {

private:

	// Enums
	GameState m_gameState;
	Player m_player;
	TileType m_lastType;
	Theme m_theme;

	// Objects
	GameBoard m_board;
	WinBox m_winBox;
	Window m_window;
	GLSLProgram m_program;
	SpriteBatch m_spriteBatch;
	Tile m_tiles[9];
	Button m_retryButton;
	Button m_quitButton;

	// Variables
	GLfloat m_mouseCoordX;
	GLfloat m_mouseCoordY;
	GLint m_sameCounter;
	GLboolean m_isTurnOver;
	GLboolean m_didWin;
	GLboolean m_isClicked;
	GLuint m_winBanner;

	// Functions
	GLvoid init(); ///< Assigns Data
	GLvoid destroy(); ///< Clears Data
	GLvoid proccessInput(); ///< Proccesses User Input
	GLvoid update(); ///< Circulates Logic
	GLvoid draw(); ///< Renders Graphics

public:

	// Class Defaults
	System(); ///< Class Constructor
	~System(); ///< Class Destructor

	// Functions
	GLvoid execute(); ///< Runs the program
	
};

