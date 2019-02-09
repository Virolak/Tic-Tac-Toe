// ##############################
// >>>>>| ImageLoader.cpp |<<<<<<
// ##############################

// Standard Library =============
#include <vector>
// Dependencies =================
#include <GLM/glm.hpp>
#include <SOIL/SOIL.h>
// Project Headers ==============
#include "Fritz.h"
#include "ImageLoader.h"
#include "IOManager.h"
// ==============================

// Class Constructor
ImageLoader::ImageLoader()
{ /* Empty */ }

// Class Destructor
ImageLoader::~ImageLoader()
{ /* Empty */ }

// Reads in a .png file
GLTexture ImageLoader::loadPNG(const GLchar* filePath) {

	// Create an empty OpenGL Texture struct
	GLTexture texture = {};

	// Create a buffer
	std::vector<GLubyte> buffer;

	GLint width = 0;
	GLint height = 0;
	GLint channels = 0;

	// Read the file data into the buffer
	if (IOManager::readFileToBuffer(filePath, buffer) == GL_FALSE) {
		std::string filePathString = filePath;
		printError("Cannot find file " + filePathString);
	}

	// Initialize the image to Null
	GLubyte* image = nullptr;
	
	// Load the image from a buffer
	image = SOIL_load_image_from_memory(&buffer[0], buffer.size(), &width, &height, &channels, SOIL_LOAD_RGBA);

	// Check if the image has been loaded properly
	if (image == nullptr) {
		std::string filePathString = filePath;
		printError("Failed to read PNG file " + filePathString);
	}

	// Generate texture
	glGenTextures(1, &texture.id);

	// Bind the texture
	glBindTexture(GL_TEXTURE_2D, texture.id);

	// Load the texture to openGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// Generate MipMaps
	glGenerateMipmap(GL_TEXTURE_2D);

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	// Free the SOIL image data
	SOIL_free_image_data(image);

	// Get size of loaded image
	texture.width = (GLfloat)width;
	texture.height = (GLfloat)height;

	// Return the texture
	return texture;
}
