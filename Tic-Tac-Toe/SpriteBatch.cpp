// ##############################
// >>>>>| SpriteBatch.cpp |<<<<<<
// ##############################

// Standard Library =============
#include <algorithm>
// Project Headers ==============
#include "SpriteBatch.h"
// ==============================

// Glyph Constructor
Glyph::Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint textureID, GLfloat depth, Color& color) :
	glyphDepth(depth), glyphTextureID(textureID)
{

	// Set the top left vertex properties
	topLeft.setPosition(destRect.x, destRect.y + destRect.w);
	topLeft.setColor(color.r, color.g, color.b, color.a);
	topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	// Set the top right vertex properties
	topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
	topRight.setColor(color.r, color.g, color.b, color.a);
	topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	// Set the bottom left vertex properties
	bottomLeft.setPosition(destRect.x, destRect.y);
	bottomLeft.setColor(color.r, color.g, color.b, color.a);
	bottomLeft.setUV(uvRect.x, uvRect.y);

	// Set the bottom right vertex properties
	bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
	bottomRight.setColor(color.r, color.g, color.b, color.a);
	bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
}

// Class Constructor
SpriteBatch::SpriteBatch()
{ /* Empty */ }

// Class Destructor
SpriteBatch::~SpriteBatch()
{ /* Empty */ }

// Initializes the Sprite Batch
GLvoid SpriteBatch::init() {

	// Create Vertex Arrays
	createVertexArrays();

}

// Clears Batches
GLvoid SpriteBatch::destroy() {



}

// Creates Vertex Arrays for Batch
GLvoid SpriteBatch::createVertexArrays() {

	// Generate Vertex Array Object
	if (m_vaoID == 0) glGenVertexArrays(1, &m_vaoID);

	// Generate Vertex Buffer Object
	if (m_vboID == 0) glGenBuffers(1, &m_vboID);

	// Bind the Vertex Array Object
	glBindVertexArray(m_vaoID);

	// Bind Vertex Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	// Enable shader attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// Tell OpenGL how to render data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)offsetof(VertexData, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexData), (GLvoid*)offsetof(VertexData, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)offsetof(VertexData, uv));

	// Unbind the Vertex Array Object
	glBindVertexArray(0);

}

// Creates Rendering Batches
GLvoid SpriteBatch::createRenderBatches() {

	// Array of vertices
	std::vector<VertexData> vertices;

	// Resize Vertex Array to 6 times the number of glyphs
	vertices.resize(m_glyphPtrs.size() * 6);

	// Exit out of the function if no glyphs exist
	if (m_glyphPtrs.empty()) return;

	// Add first glyph to render batch
	m_renderBatches.emplace_back(0, 6, m_glyphPtrs[0]->glyphTextureID);
	GLint offset = 0;

	// Define All corners of first box using 2 triangles
	GLint currentVertex = 0;
	vertices[currentVertex++] = m_glyphPtrs[0]->topLeft;
	vertices[currentVertex++] = m_glyphPtrs[0]->bottomLeft;
	vertices[currentVertex++] = m_glyphPtrs[0]->bottomRight;
	vertices[currentVertex++] = m_glyphPtrs[0]->topLeft;
	vertices[currentVertex++] = m_glyphPtrs[0]->topRight;
	vertices[currentVertex++] = m_glyphPtrs[0]->bottomRight;
	offset += 6;

	// Define all vertices for all other glyphs
	for (size_t currentGlyph = 1; currentGlyph < m_glyphPtrs.size(); currentGlyph++) {

		// Add a new batch for any new textures
		if (m_glyphPtrs[currentGlyph]->glyphTextureID != m_glyphPtrs[currentGlyph - 1]->glyphTextureID) {
			m_renderBatches.emplace_back(offset, 6, m_glyphPtrs[currentGlyph]->glyphTextureID);
		}

		// Add vertices to current batch
		else {
			m_renderBatches.back().numBatchVerts += 6;
		}

		// Define four corners of current glyph
		vertices[currentVertex++] = m_glyphPtrs[currentGlyph]->topLeft;
		vertices[currentVertex++] = m_glyphPtrs[currentGlyph]->bottomLeft;
		vertices[currentVertex++] = m_glyphPtrs[currentGlyph]->bottomRight;
		vertices[currentVertex++] = m_glyphPtrs[currentGlyph]->topLeft;
		vertices[currentVertex++] = m_glyphPtrs[currentGlyph]->topRight;
		vertices[currentVertex++] = m_glyphPtrs[currentGlyph]->bottomRight;
		offset += 6;
	}

	// Bind the Vertex Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	// Upload the data after orphaning the buffer
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(VertexData), vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

// Sorts the glyphs
GLvoid SpriteBatch::sortGlyphs() {

	// Look at the sort type
	switch (m_sortType) {

	// Sort the glyphs by layer from top to bottom
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(m_glyphPtrs.begin(), m_glyphPtrs.end(), compareFrontToBack);
		break;

	// Sort the glyphs by layer from bottom to top
	case GlyphSortType::BACK_TO_FRONT:
		std::stable_sort(m_glyphPtrs.begin(), m_glyphPtrs.end(), compareBackToFront);
		break;

	// Sort the glyphs by vertical position
	case GlyphSortType::POSITION:
		std::stable_sort(m_glyphPtrs.begin(), m_glyphPtrs.end(), comparePosition);
		break;

		// Sort the glyphs by texture ID
	case GlyphSortType::TEXTURE:
		std::stable_sort(m_glyphPtrs.begin(), m_glyphPtrs.end(), compareTexture);
		break;
	}


}

// Clears the previous batch to make room for new sprites
GLvoid SpriteBatch::start(GlyphSortType sortType /* = GlyphSortType::POSITION */) {

	// Set the sort type
	m_sortType = sortType;

	// Clear the batches
	m_renderBatches.clear();

	// Clear the glyphs
	m_glyphs.clear();

}

// Adds all sprites to batch that have been created with the draw function
GLvoid SpriteBatch::stop() {

	// Set size of glyph pointers to size of glyphs
	m_glyphPtrs.resize(m_glyphs.size());

	// Set glyph pointers to glyphs
	for (size_t i = 0; i < m_glyphs.size(); i++) {
		m_glyphPtrs[i] = &m_glyphs[i];
	}

	// Sort the glyphs
	sortGlyphs();

	// Create batches for rendering
	createRenderBatches();

}

// Renders all sprites in the batch
GLvoid SpriteBatch::render() {

	// Bind the vertex array object
	glBindVertexArray(m_vaoID);

	// Draw the glyphs
	for (GLint i = 0; i < m_renderBatches.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].batchTexture);
		glDrawArrays(GL_TRIANGLES, m_renderBatches[i].vertexOffset, m_renderBatches[i].numBatchVerts);
	}

	// Unbind the Vertex array object
	glBindVertexArray(0);

}

// Adds a sprite to the batch
GLvoid SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint textureID, GLfloat depth, Color& color) {

	// Add sprite to the list of glyphs
	m_glyphs.emplace_back(destRect, uvRect, textureID, depth, color);

}
