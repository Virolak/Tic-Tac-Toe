// ##############################
// >>>>>>| IOManager.cpp |<<<<<<<
// ##############################

// Standard Library =============
#include <fstream>
// Project Headers ==============
#include "IOManager.h"
// ==============================

// Class Constructor
IOManager::IOManager()
{ /* Empty */ }

// Class Destructor
IOManager::~IOManager()
{ /* Empty */ }

// Reads file data into a vector of unsigned characters
GLboolean IOManager::readFileToBuffer(std::string filePath, std::vector<GLubyte>& buffer) {

	// Open a file
	std::ifstream file(filePath, std::ios::binary);

	// Throw an error if the file cannot be found
	if (file.fail()) {
		perror(filePath.c_str());
		return GL_FALSE;
	}

	// Scan to the end of the file
	file.seekg(0, std::ios::end);

	// Get the size of the file
	GLint fileSize = file.tellg();

	// Remove header bytes from file
	file.seekg(0, std::ios::beg);
	fileSize -= file.tellg();

	// Set the size of the buffer to size of the file
	buffer.resize(fileSize);

	// Read the file
	file.read((GLchar*)&(buffer[0]), fileSize);

	// Close the file
	file.close();

	// File has been read successfully
	return GL_TRUE;
}

// Reads file data into a string
GLboolean IOManager::readFileToBuffer(std::string filePath, std::string& buffer) {

	// Read in the file as binary data
	std::ifstream file(filePath, std::ios::binary);

	// Throw an error if the file cannot be found
	if (file.fail()) {
		perror(filePath.c_str());
		return GL_FALSE;
	}

	// Seek to the end of the file
	file.seekg(0, std::ios::end);

	// Get the size of the file
	GLfloat fileSize = file.tellg();

	// Remove header bytes of file from buffer
	file.seekg(0, std::ios::beg);
	fileSize -= file.tellg();

	// Set size of buffer to size of file
	buffer.resize(fileSize);

	// Read the file data into the buffer
	file.read((GLchar*)&(buffer[0]), fileSize);

	// Close the file
	file.close();

	// File read successfully
	return GL_TRUE;

}
