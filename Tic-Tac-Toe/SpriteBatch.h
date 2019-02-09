// ##############################
// >>>>>>| SpriteBatch.h |<<<<<<<
// ##############################

#pragma once

// Standard Library =============
#include <vector>
// Dependencies =================
#include <GLM/glm.hpp>
// Project Headers ==============
#include "VertexData.h"
// ==============================

// "Glyph Sort Type" Enum
enum class GlyphSortType { FRONT_TO_BACK, BACK_TO_FRONT, POSITION, TEXTURE };

// "Glyph" Struct
struct Glyph {

public:

	// Glyph Constructor
	Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint textureID, GLfloat depth, Color& color);

	// Structs
	VertexData topLeft; ///< Top Left Vertex
	VertexData topRight; ///< Top Right Vertex
	VertexData bottomLeft; ///< Bottom Left Vertex
	VertexData bottomRight; ///< Bottom right vertex

	// Variables
	GLfloat glyphDepth; ///< Texture layer
	GLuint glyphTextureID; ///< Texture ID

};

// "Render Batch" struct
struct RenderBatch {

	// RenderBatch Constructor
	RenderBatch(GLint offset, GLint numVertices, GLuint textureID) :
		vertexOffset(offset), numBatchVerts(numVertices),  batchTexture(textureID)
	{ /* Empty */ }

	// Variables
	GLint vertexOffset; ///< how many vertices after last batch
	GLint numBatchVerts; ///< total number of vertices in the batch
	GLuint batchTexture; ///< Texture used in batch

};

// "Sprite Batch" Class
class SpriteBatch {

private:

	// Objects
	std::vector<Glyph> m_glyphs; ///< Vector of glyphs
	std::vector<Glyph*> m_glyphPtrs; ///< Vector of pointers to glyph
	std::vector<RenderBatch> m_renderBatches; ///< Vector of rendering batches

	// Enums
	GlyphSortType m_sortType; ///< How the glyphs are sorted

	// Variables
	GLuint m_vaoID; ///< Vertex Array Object ID
	GLuint m_vboID; ///< Vertex Buffer Object ID

	// Functions
	GLvoid createVertexArrays(); ///< Creates Vertex arrays for batch
	GLvoid createRenderBatches(); ///< Creates Rendering Batches
	GLvoid sortGlyphs(); ///< Sorts the glyphs
	static GLboolean compareFrontToBack(Glyph* a, Glyph* b) { return a->glyphDepth > b->glyphDepth; }
	static GLboolean compareBackToFront(Glyph* a, Glyph* b) { return a->glyphDepth < b->glyphDepth; }
	static GLboolean comparePosition(Glyph* a, Glyph* b) { return a->bottomLeft.position.y > b->bottomLeft.position.y; }
	static GLboolean compareTexture(Glyph*a, Glyph* b) { return a->glyphTextureID > b->glyphTextureID; }

public:

	// Class Defaults
	SpriteBatch(); ///< Class Constructor
	~SpriteBatch(); ///< Class Destructor

	// Functions
	GLvoid init(); ///< Initializes the Sprite Batch
	GLvoid destroy(); ///< Clears Batches
	GLvoid start(GlyphSortType sortType = GlyphSortType::POSITION); ///< Clears the previous batch to make room for new sprites
	GLvoid stop(); ///< Adds all sprites to batch that have been created with the draw funciton
	GLvoid render(); ///< Renders all sprites in the batch
	GLvoid draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, GLfloat depth, Color& color); ///< Adds a sprite to the batch
};

