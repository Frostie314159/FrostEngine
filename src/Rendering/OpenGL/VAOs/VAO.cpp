#include "VAO.hpp"

VAO::~VAO() {
	this->deleteVAO();
}

void VAO::deleteVAO() {
	glDeleteBuffers(static_cast<GLsizei>(this->m_vbos.size()), this->getVBOIDs().data());
	glDeleteVertexArrays(1, &this->m_vaoID);
}
std::vector<GLuint> VAO::getVBOIDs() {
	std::vector<GLuint> m_temp;
	for (OpenGLBuffer m_iterator : this->m_vbos)
		m_temp.push_back(m_iterator.getBufferID());
	return m_temp;
}
GLuint VAO::getVAOID() {
	return this->m_vaoID;
}
void VAO::bind() {
	glBindVertexArray(this->m_vaoID);
	for (OpenGLBuffer m_iterator : this->m_vbos) {
		glEnableVertexAttribArray(m_iterator.getBufferIndex());
		m_iterator.bind();
	}
}
void VAO::unbind() {
	for (GLuint m_iterator : this->getVBOIDs()) {
		glDisableVertexAttribArray(m_iterator);
	}
	for (OpenGLBuffer m_iterator : this->m_vbos) {
		m_iterator.unbind();
	}
	glBindVertexArray(0);
}