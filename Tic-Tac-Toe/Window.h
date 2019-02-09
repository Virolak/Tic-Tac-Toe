// ##############################
// >>>>>>>>>| Window.h |<<<<<<<<<
// ##############################

#pragma once

// Dependencies =================
#include <GL/glew.h>
#include <SDL/SDL.h>
// ==============================

// "Window Flags" enum
enum class WindowFlags {HIDDEN = 0x01, BORDERLESS = 0x02, FULLSCREEN = 0x04, NONE = 0x08};

// "Window" Class
class Window {

private:

	// Graphics Objects
	SDL_Window* m_window; ///< SDL Window
	SDL_GLContext m_context; ///< The OpenGL window context

	// Variables
	GLint m_posX; ///< Horizontal position of screen
	GLint m_posY; ///< Vertical position of screen
	GLint m_width; ///< Width of screen
	GLint m_height; ///< Height of screen


public:

	// Class Defaults
	Window(); ///< Class Constructor
	~Window(); ///< Class Destructor

	// Functions
	GLvoid create(const GLchar* title, GLfloat width, GLfloat height, WindowFlags windowFlags); ///< Creates the window
	GLvoid destroy(); ///< Remove the window
	GLvoid swapBuffer(); ///< Swaps the window's buffer

	// Getters
	GLint getWidth() { return m_width; } ///< Returns width of screen
	GLint getHeight() { return m_height; } ///< Returns height of screen
};

