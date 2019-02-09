// ##############################
// >>>>>>>>| Window.cpp |<<<<<<<<
// ##############################

// Project Headers ==============
#include "Fritz.h"
#include "Window.h"
// ==============================

// Class Constructor
Window::Window() : 
	m_posX(SDL_WINDOWPOS_CENTERED),
	m_posY(SDL_WINDOWPOS_CENTERED),
	m_width(800),
	m_height(480),
	m_window(nullptr)
{ /* Empty */ }

// Class Destructor
Window::~Window()
{ /* Empty */ }

// Creates the window
GLvoid Window::create(const GLchar* title, GLfloat width, GLfloat height, WindowFlags windowFlags) {

	// Set window properties
	m_width = width;
	m_height = height;

	// Set flags
	Uint32 flags = SDL_WINDOW_OPENGL;

	// Hide the window
	if (windowFlags == WindowFlags::HIDDEN) {
		flags |= SDL_WINDOW_HIDDEN;
	}

	// Remove Borders
	if (windowFlags == WindowFlags::BORDERLESS) {
		flags |= SDL_WINDOW_BORDERLESS;
	}

	// Use Full Screen
	if (windowFlags == WindowFlags::FULLSCREEN) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	// Create the window using SDL
	m_window = SDL_CreateWindow(title, m_posX, m_posY, m_width, m_height, flags);

	// Create the openGL context
	m_context = SDL_GL_CreateContext(m_window);

	// Initialize glew
	if (glewInit() != GLEW_OK) {
		printError("Failed to intialze glew", "", 201);
	}

}

// Remove the window
GLvoid Window::destroy() {

	// Use SDL to destroy the window
	SDL_DestroyWindow(m_window);

	// Delete the context
	SDL_GL_DeleteContext(m_context);

}

// Swaps the windows buffer
GLvoid Window::swapBuffer() {

	// Swap the buffer on the SDL window
	SDL_GL_SwapWindow(m_window);

}
