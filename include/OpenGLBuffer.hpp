#ifndef OPENGL_BUFFER_HPP_
#define OPENGL_BUFFER_HPP_

#include <iostream>
#include <vector>
#include <tuple>
#if  defined _WIN32 || defined __CYGWIN__
	#include <windef.h>
#endif

#include "GL/glew.h"
#include "OpenGLUtil.hpp"

class OpenGLBuffer
{
private:
	GLuint m_bufferID;
	GLuint m_bufferIndex;
	GLenum m_bufferDataType;
	GLenum m_bufferType;
	GLsizei m_bufferSize;
public:
	template<typename T>
	OpenGLBuffer(std::tuple<std::vector<T>,GLint> t_bufferData, GLenum t_bufferType, GLuint t_index) {
		glGenBuffers(1, &this->m_bufferID);
		glBindBuffer(t_bufferType, this->m_bufferID);
		glBufferData(t_bufferType, std::get<0>(t_bufferData).size(), std::get<0>(t_bufferData).data(), GL_STATIC_DRAW);
		glGetBufferParameteriv(t_bufferType, GL_BUFFER_SIZE, &this->m_bufferSize);
		this->m_bufferDataType = OpenGLUtil::getTypenameAsOpenGLType(std::get<0>(t_bufferData).at(0));
		this->m_bufferIndex = t_index;
		this->m_bufferType = t_bufferType;
		if (t_bufferType != GL_ARRAY_BUFFER) {
			glEnableVertexAttribArray(0);
			glBindBuffer(t_bufferType,this->m_bufferID);
			glVertexAttribPointer(t_index, std::get<1>(t_bufferData), this->m_bufferDataType, GL_FALSE, 0, (void*)0);
		}
		//glBindBuffer(t_bufferType, 0);
	}
	~OpenGLBuffer();

	void bind();
	void unbind();
	void deleteBuffer();
	GLuint getBufferID();
	GLuint getBufferIndex();
	GLenum getBufferDataType();
	GLenum getBufferType();
	GLsizei getBufferSize();
};

#endif