// ##############################
// >>>>>>>>| System.cpp |<<<<<<<<
// ##############################

// Project Headers ==============
#include "Fritz.h"
#include "ResourceManager.h"
#include "System.h"
#include <SDL/SDL_ttf.h>
// ==============================

// Class Constructor
System::System() :
	m_gameState(GameState::RUNNING),
	m_player(PLAYER1),
	m_lastType(TileType::NONE),
	m_isTurnOver(GL_FALSE),
	m_sameCounter(0),
	m_didWin(GL_FALSE)
{ /* Empty */ }

// Class Destructor
System::~System()
{ /* Empty */ }

// Assigns Data
GLvoid System::init() {

	// Set SDL Attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); ///< Use openGL version 3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3); ///< Use openGL revision 3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); ///< Use core profile mode

	// Initialize SDL with everything
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printError("SDL failed to initiailze!", SDL_GetError(), 101);
	}

	// Create the window
	m_window.create("Tic-Tac-Toe", 480, 480, WindowFlags::NONE);

	// Copmiles shaders from files
	m_program.compileFiles("assets/shaders/basic_shader.vert", "assets/shaders/basic_shader.frag");

	// Add attributes found in shader
	m_program.addAttributes("vertexPosition");
	m_program.addAttributes("vertexColor");
	m_program.addAttributes("vertexUV");

	// Link the shaders to the shader program
	m_program.link();

	// Initialize the Sprite batch
	m_spriteBatch.init();

	// Set line draw width
	glLineWidth(2.0f);

	// Get Center position of bottom left tile space
	GLfloat boardStartX = m_board.getWidth() / 3.3f / 2.0f;
	GLfloat boardStartY = m_board.getHeight() / 3.3f / 2.0f;

	// Enable Alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize the board
	m_board.init(1.0f, 1.0f);

	// Initialize a tile
	for (int i = 0; i < 9; i++) {
		m_tiles[i].init(m_board.findSectionPosX(), m_board.findSectionPosY(), 0.25f, 0.25f);
	}

	// Initialize the Win Box
	m_winBox.init(0.0f, 0.0f, 1.5f, 1.5f);

	// Set the background image
	m_theme.setBackground("assets/images/wood_background.png");

	// Initialize menu buttons
	m_retryButton.init(-0.33f, -0.20f, 0.3f, 0.2f, RETRY);
	m_quitButton.init(0.33f, -0.2f, 0.3f, 0.2f, QUIT);

}

// Clears Data
GLvoid System::destroy() {

	// Destroy the window
	m_window.destroy();

	// Quit out of SDL
	SDL_Quit();

}

// Proccesses User Input
GLvoid System::proccessInput() {

	// SDL Event instance
	SDL_Event evnt;

	// Scan for SDL Events
	while (SDL_PollEvent(&evnt)) {

		// Look at the type of SDL event
		switch (evnt.type) {

		// Window's X buttton clicked
		case SDL_QUIT:
			m_gameState = GameState::QUITTING;
			break;

		// Key down
		case SDL_KEYDOWN:
			break;

		// Key released
		case SDL_KEYUP:
			evnt.button.button = GL_FALSE;
			break;

		// Motion Detected from mouse
		case SDL_MOUSEMOTION:
			m_mouseCoordX = (GLfloat)evnt.motion.x;
			m_mouseCoordY = (GLfloat)evnt.motion.y;
			break;

		// Mouse Button Pressed
		case SDL_MOUSEBUTTONDOWN:
			if (evnt.button.button = SDL_BUTTON_LEFT) {
				m_isClicked = GL_TRUE;
			}
			break;

		// Mouse Button relased
		case SDL_MOUSEBUTTONUP:
			m_isClicked = GL_FALSE;
			break;

		}

	}

}

// Circulates Logic
GLvoid System::update() {

	// Keep the program running in a loop until there is a call to exit
	while (m_gameState != GameState::QUITTING) {

		// Check for button presses when the game is over
		if (m_didWin == GL_TRUE) {
			if (m_isClicked == GL_TRUE) {

				// Check if the Retry button has been clicked
				m_retryButton.press(m_mouseCoordX, m_mouseCoordY, 480, 480);
				if (m_retryButton.getClicked() == GL_TRUE) {

					// Reset all tiles
					for (GLint i = 0; i < 9; i++) {
						m_tiles[i].setType(TileType::NONE);
						m_tiles[i].setHitToFalse();
					}

					// Set Player to player 1 and stop registering clicks this frame
					m_player = PLAYER1;
					m_isClicked = GL_FALSE;
					m_didWin = GL_FALSE;
					m_isTurnOver = GL_FALSE;
					m_retryButton.setClickedToFalse();
				}

				// Check if the quit button has been clicked
				m_quitButton.press(m_mouseCoordX, m_mouseCoordY, 480, 480);

				// Quit the game
				if (m_quitButton.getClicked() == GL_TRUE) {
					return;
				}
			}
		}

		// Mouse button has been clicked
		if (m_isClicked == GL_TRUE) {

			// Loop through all the tiles
			for (int i = 0; i < 9; i++) {

				// Draw the tile as an X if Player 1 clicks on it
				if (m_player == PLAYER1) {

					// Check if the click was within the tile position
					if (m_tiles[i].update(m_mouseCoordX, m_mouseCoordY, m_window.getWidth(), m_window.getHeight(), TileType::CROSS) == GL_TRUE) {

						// Status update
						std::printf("Player 1 placed an X at (%f,%f)\n", m_tiles[i].getPosX(), m_tiles[i].getPosY());

						// Turn is now over
						m_isTurnOver = GL_TRUE;
					}
				}

				// Draw the tile as an X if Player 2 clicks on it
				else if (m_player == PLAYER2) {

					// Check if the click was within the tile position
					if (m_tiles[i].update(m_mouseCoordX, m_mouseCoordY, m_window.getWidth(), m_window.getHeight(), TileType::CIRCLE) == GL_TRUE) {

						// Status update
						std::printf("Player 2 placed an O at (%f,%f)\n", m_tiles[i].getPosX(), m_tiles[i].getPosY());

						// Turn is now over
						m_isTurnOver = GL_TRUE;
					}
				}
			}

			// Check for Horizontal win
			for (int i = 0; i <= 6; i += 3) {

				// Loop through X positions in single row
				for (int j = i; j < i + 3; j++) {

					// Count Number of Xs
					if (m_tiles[j].getType() == m_lastType && m_tiles[j].getHit() == GL_TRUE && m_tiles[j].getType() != TileType::NONE) {
						m_sameCounter++;

						// THere is a win if there are 3 Xs in a row
						if (m_sameCounter >= 2) {
							m_didWin = GL_TRUE;
						}
					}

					// Check if last tile is an X or an O
					m_lastType = m_tiles[j].getType();
				}

				// Reset the counter
				m_sameCounter = 0;
				m_lastType = TileType::NONE;
			}

			// Check for Vertical win
			for (int i = 0; i < 3; i++) {

				// Loop through Y positions in single row
				for (int j = i; j <= i + 6; j += 3) {

					// Count Number of Xs
					if (m_tiles[j].getType() == m_lastType && m_tiles[j].getHit() == GL_TRUE && m_tiles[j].getType() != TileType::NONE) {
						m_sameCounter++;

						// THere is a win if there are 3 Xs in a row
						if (m_sameCounter >= 2) {
							m_didWin = GL_TRUE;
						}
					}

					// Check if last tile is an X or an O
					m_lastType = m_tiles[j].getType();
				}

				// Reset the counter
				m_sameCounter = 0;
				m_lastType = TileType::NONE;
			}

			// Check for Diagnal win from bottom left
			for (int i = 0; i < 9; i += 4) {

				if (m_tiles[i].getType() == m_lastType && m_tiles[i].getHit() == GL_TRUE && m_tiles[i].getType() != TileType::NONE) {
					m_sameCounter++;

					// THere is a win if there are 3 Xs in a row
					if (m_sameCounter >= 2) {
						m_didWin = GL_TRUE;
					}
				}

				// Check if last tile is an X or an O
				m_lastType = m_tiles[i].getType();
			}

			// Reset the counter
			m_sameCounter = 0;
			m_lastType = TileType::NONE;

			// Check for Diagnal win from bottom right
			for (int i = 2; i <= 6; i += 2) {
				if (m_tiles[i].getType() == m_lastType && m_tiles[i].getHit() == GL_TRUE && m_tiles[i].getType() != TileType::NONE) {
					m_sameCounter++;

					// THere is a win if there are 3 Xs in a row
					if (m_sameCounter >= 2) {
						m_didWin = GL_TRUE;
					}
				}

				// Check which tile type came last
				m_lastType = m_tiles[i].getType();
			}

			// Reset the counter
			m_sameCounter = 0;
			m_lastType = TileType::NONE;

			// Set win banner to winning player
			if (m_didWin == GL_TRUE) {

				// Player X Wins banner
				if (m_player == PLAYER1) {
					m_winBanner = ResourceManager::getTexture("assets/images/xwins.png").id;
				}

				// Player O Wins banner
				else {
					m_winBanner = ResourceManager::getTexture("assets/images/owins.png").id;
				}
			}

			// Switch player after turn is over
			if (m_didWin == GL_FALSE) {
				if (m_isTurnOver == GL_TRUE) {

					// Switch to player 2
					if (m_player == PLAYER1) {
						m_player = PLAYER2;
					}

					// Switch to player 1
					else {
						m_player = PLAYER1;
					}

					// Players turn is starting
					m_isTurnOver = GL_FALSE;
				}
			}

			// Prevent proccessing on another click
			m_isClicked = GL_FALSE;
		}

		// Check if the board is filled
		GLfloat fillCount = 0;

		for (GLint i = 0; i < 9; i++) {
			if (m_tiles[i].getType() != TileType::NONE) {
				fillCount++;
			}
		}

		if (fillCount == 9 && m_didWin == GL_FALSE) {
			for (GLint i = 0; i < 9; i++) {
				m_tiles[i].setType(TileType::NONE);
				m_tiles[i].setHitToFalse();
			}
			m_player = PLAYER1;
			m_isClicked = GL_FALSE;
		}

		// Proccess User Input
		proccessInput();

		// Render graphics
		draw();

	}

}

// Renders Graphics
GLvoid System::draw() {

	// Clear the screen for drawing
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use the shader program
	m_program.bind();

	glUniform1i(m_program.getUniformLocation("textureSampler"), 0);
	glActiveTexture(GL_TEXTURE0);

	// Clear previous batch
	m_spriteBatch.start(GlyphSortType::BACK_TO_FRONT);

	// Draw the background
	m_theme.render(m_spriteBatch);

	// Draw the Game board
	m_board.draw(m_spriteBatch);

	// Draw each tile on the game board
	for (int i = 0; i < 9; i++) {
		m_tiles[i].draw(m_spriteBatch);
	}

	// Draw a Win Box if a player has won the game
	if (m_didWin == GL_TRUE) {
		m_winBox.draw(m_spriteBatch);
		m_retryButton.draw(m_spriteBatch);
		m_quitButton.draw(m_spriteBatch);
		Color color;
		m_spriteBatch.draw(glm::vec4(-0.2f, 0.0f, 0.4f, 0.2f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), m_winBanner, 5.0f, color);
	}

	//
	m_spriteBatch.stop();
	m_spriteBatch.render();

	m_program.unbind();

	// Swap the window's buffer
	m_window.swapBuffer();

}

// Runds the Program
GLvoid System::execute() {

	// Assign Data
	init();

	// Circulate Logic
	update();

	// Clear Data
	destroy();

}
