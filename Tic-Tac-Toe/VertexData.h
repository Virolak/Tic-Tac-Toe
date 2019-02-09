// ##############################
// >>>>>>>| VertexData.h |<<<<<<<
// ##############################

#pragma once

// Dependencies =================
#include <GL/glew.h>

// Position Struct
struct Position {

	// Variables
	GLfloat x; ///< horizontal position of point
	GLfloat y; ///< vertical position of point
	GLfloat z; ///< depth of point

};

// Color Struct
struct Color {

	// Default Constructors
	Color() : r(255), g(255), b(255), a(255) { /* Empty */ }
	Color(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) : r(red), g(green), b(blue), a(alpha) { /* Empty */ }

	// Variables
	GLubyte r; ///< Red value of point
	GLubyte g; ///< Green value of point
	GLubyte b; ///< Blue value of point
	GLubyte a; ///< Alpha value of point
};

// UV struct
struct UV {

	// Variables
	GLfloat u; ///< horizontal coordinate of texture
	GLfloat v; ///< vertical coordinate of texture

};

// Vertex Data Struct
struct VertexData {

	// Data
	Position position; ///< position struct
	Color color; ///< Color struct
	UV uv; ///< UV struct

	// Set the position
	GLvoid setPosition(GLfloat posX, GLfloat posY, GLfloat posZ = 0.0f) {
		position.x = posX; position.y = posY; position.z = posZ;
	}

	// Set the color
	GLvoid setColor(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) {
		color.r = red; color.g = green; color.b = blue; color.a = alpha;
	}

	// Set the UV wrapping coordinates
	GLvoid setUV(GLfloat xCoord, GLfloat yCoord) {
		uv.u = xCoord; uv.v = yCoord;
	}

};
