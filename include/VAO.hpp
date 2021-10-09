#ifndef VAO_HPP_
#define VAO_HPP_

#include <iostream>
#include <vector>
#if  defined _WIN32 || defined __CYGWIN__
	#include <windef.h>
#endif

#include "GL/glew.h"
#include "OpenGLBuffer.hpp"

class VAO
{
private:
	std::vector<OpenGLBuffer> m_vbos;
	GLuint m_vaoID;
public:
	template<typename T>
	VAO(std::vector<std::tuple<std::vector<T>, GLint>> t_data) {
		glGenVertexArrays(1, &this->m_vaoID);
		glBindVertexArray(this->m_vaoID);
		size_t i = 0;
		for (std::tuple<std::vector<T>, GLint> m_iterator : t_data) {
			this->m_vbos.push_back(OpenGLBuffer(std::make_tuple(std::get<0>(m_iterator), std::get<1>(m_iterator)), (i == t_data.size()-1 && t_data.size() != 1) ? GL_ELEMENT_ARRAY_BUFFER : GL_ARRAY_BUFFER, i));
			i++;
		}
	}
	template<typename T>
	VAO(std::tuple<std::vector<T>, GLint> t_data) {
		glGenVertexArrays(1, &this->m_vaoID);
		glBindVertexArray(this->m_vaoID);
		this->m_vbos.push_back(OpenGLBuffer(std::make_tuple(std::get<0>(t_data), std::get<1>(t_data)), GL_ARRAY_BUFFER, 0));
	}
	~VAO();
	void deleteVAO();
	std::vector<GLuint> getVBOIDs();
	GLuint getVAOID();
	void bind();
	void unbind();
};

#endif