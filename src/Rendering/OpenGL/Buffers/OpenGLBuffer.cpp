#include "OpenGLBuffer.hpp"

OpenGLBuffer::~OpenGLBuffer() {
	this->deleteBuffer();
}

void OpenGLBuffer::bind() {
	glBindBuffer(this->m_bufferType, this->m_bufferID);
}
void OpenGLBuffer::unbind() {
	glBindBuffer(this->m_bufferType, 0);
}
void OpenGLBuffer::deleteBuffer() {
	glDeleteBuffers(1, &this->m_bufferID);
}


GLuint OpenGLBuffer::getBufferID() {
	return this->m_bufferID;
}
GLuint OpenGLBuffer::getBufferIndex() {
	return this->m_bufferIndex;
}
GLenum OpenGLBuffer::getBufferDataType() {
	return this->m_bufferDataType;
}
GLenum OpenGLBuffer::getBufferType() {
	return this->m_bufferType;
}
GLsizei OpenGLBuffer::getBufferSize() {
	return this->m_bufferSize;
}